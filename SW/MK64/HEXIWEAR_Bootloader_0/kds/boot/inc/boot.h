#ifndef HG_BOOT
#define HG_BOOT

#include "boot_types.h"

#include "MK64F12_add.h"
#include "MK64F12_cfg.h"

extern uint32_t __region_BOOT_ROM_start__[];
extern uint32_t __region_BOOT_ROM_end__[];
extern vector_entry __sp_init__;

extern uint32_t* const
  firstTimeBoot;

/**
 * load the new image
 */
void Boot_LoadImage();

/**
 * reset the MCU
 */
void Boot_ResetMCU();

/**
 * [Boot_GetInternalStorageStartAddr description]
 * @return [description]
 */
uint32_t Boot_GetInternalStorageStartAddr();

/**
 * [Boot_InitExternalStorage description]
 * @return  [description]
 */
uint8_t Boot_InitExternalStorage();

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
                                );

void Boot_JumpToApplication( volatile uint32_t userStartup );

#endif
