/**
 * boot functions
 */

#include "boot.h"
#include "error.h"
#include "flash_boot_kinetis.h"

/**
 * load the new image
 */
void Boot_LoadImage()
{
  static uint8_t
    bitmapBuffer[ gBootData_SectorsBitmap_Size_c ];

  bootInfo_t
    flags;

  uint8_t
    buffer[ FLASH_ERASE_PAGE ];

  uint32_t
    remaingImgSize,
    len;

  volatile uint32_t
    imgAddr   = 0,
    flashAddr = FLASH_APP_START_ADDRESS;

  uint8_t
    bitMask = gBitMaskInit_c;
  uint8_t*
    bitmapPtr = &(bitmapBuffer[0]);

  // initialize the flash module
  FlashInitialization();

  // initialize the external storage
  Boot_InitExternalStorage();

  // read image size
  if  (
        0 != Boot_ReadExternalStorage (
                                        gBootData_ImageLength_Size_c,
                                        imgAddr + gBootData_ImageLength_Offset_c,
                                        (uint8_t*)(&remaingImgSize)
                                      )
      )
  {
    catch();
  }

  // read sector bitmap
  if  (
        0 != Boot_ReadExternalStorage (
                                        gBootData_SectorsBitmap_Size_c,
                                        imgAddr + gBootData_SectorsBitmap_Offset_c,
                                        (uint8_t*)&(bitmapBuffer[0])
                                      )
      )
  {
    catch();
  }

  /**
   * start writing the image into the internal flash
   * do not alter the last sector which contains HW specific data!
   */

  while (1)
  {
    if ( remaingImgSize > FLASH_ERASE_PAGE )
    {
      len = FLASH_ERASE_PAGE;
    }

    else
    {
      len = remaingImgSize;
    }

    /**
     * check the bitmap to see if this sector is write protected
     * and shouldn't be updated
     */

    if ( 0 != len )
    {
      if ( 0 != ( *bitmapPtr & bitMask ) )
      {
        // erase this sector
        if ( FLASH_OK != FLASH_EraseSector( flashAddr ) )
        {
          catch();
        }

        // read the new image block
        if  ( 0 != Boot_ReadExternalStorage (
                                              len,
                                              flashAddr + gBootData_Image_Offset_c,
                                              buffer
                                            )
            )
        {
          catch();
        }

        // program the image block to Flash
        if  (
              FLASH_OK != FLASH_Program (
                                          flashAddr,
                                          (uint32_t)( &buffer[0] ),
                                          len
                                        )
            )
        {
          catch();
        }
      }

      // update the remaining bytes
      if ( 0 != remaingImgSize )
      {
        remaingImgSize -= len;
        imgAddr        += len;
      }

      // update the bit-mask
      bitMask <<= 1;
      if ( 0 == bitMask )
      {
        // this was last bit in the current bitmap byte. Move to the next bitmap byte
        bitMask = gBitMaskInit_c;
        bitmapPtr++;
      }

      // update the current flash address
      flashAddr += FLASH_ERASE_PAGE;
    }

    else
    {
      break;
    }
  }

  // set the bBootProcessCompleted flag
  flags.newBootImageAvailable[ 0 ] = 0x00;

  if ( FLASH_OK != FLASH_EraseSector( (uint32_t)BOOT_IMAGE_FLAGS_ADDRESS ) )
  {
    catch();
  }

  if  (
        FLASH_OK != FLASH_Program (
                                    (uint32_t)BOOT_IMAGE_FLAGS_ADDRESS,
                                    (uint32_t)&flags,
                                    sizeof(flags)
                                  )
      )
  {
    catch();
  }

  // if first time, clear the flag
  if ( BOOT_FIRST_TIME_IMAGE_FLAG == *firstTimeBoot )
  {
    uint32_t
      foo = 0xAA00A0A0;

    if  (
          FLASH_OK != FLASH_Program (
                                      (uint32_t)firstTimeBoot,
                                      (uint32_t)&foo,
                                      sizeof(foo)
                                    )
        )
    {
      catch();
    }
  }

  // reset the MCU
  Boot_ResetMCU();
}

/**
 * reset the MCU
 */
void Boot_ResetMCU()
{
  SCB_AIRCR = SCB_AIRCR_VECTKEY(0x5FA) | SCB_AIRCR_SYSRESETREQ_MASK;
}

/**
 * [Boot_InitExternalStorage description]
 * @return  [description]
 */
uint8_t Boot_InitExternalStorage()
{
  return EEPROM_Init();
}

/**
 * [Boot_ReadExternalStorage description]
 * @param  NoOfBytes [description]
 * @param  Addr      [description]
 * @param  outbuf    [description]
 * @return           [description]
 */
uint8_t Boot_ReadExternalStorage(
                                  uint16_t byteNum,
                                  uint32_t address,
                                   uint8_t *buffer
                                )
{
  return EEPROM_ReadData( byteNum, address, buffer );
}

/**
 * jump to an address and run the function from there
 */
void Boot_JumpToApplication (
                              volatile uint32_t userStartup
                            )
{
  /* Enable ALL interrupts */
  asm("     cpsie   i       ");

  /* set up stack pointer */
  asm("LDR      r1,  [r0]");
  asm("MSR      MSP, r1");

  /* jump to application reset vector */
  asm("ADDS     r0, r0, #0x04 ");
  asm("LDR      r0, [r0]");
  asm("BX       r0");
}
