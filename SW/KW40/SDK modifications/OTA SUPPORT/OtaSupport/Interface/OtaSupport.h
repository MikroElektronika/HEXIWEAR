/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file OtaSupport.h
* This is the header file for the OTA Programming Support.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _OTA_SUPPORT_H_
#define _OTA_SUPPORT_H_

#ifdef __cplusplus
    extern "C" {
#endif

/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
************************************************************************************/

#ifndef gEnableOTAServer_d
#define gEnableOTAServer_d                 (0)
#endif

#ifndef gUpgradeImageOnCurrentDevice_d
#define gUpgradeImageOnCurrentDevice_d     (0)
#endif

#define gOtaVersion_c                      (0x01)

#ifndef gOtaVerifyWrite_d
#define gOtaVerifyWrite_d                  (1)
#endif

#define gBootValueForTRUE_c                (0x00)
#define gBootValueForFALSE_c               (0xFF)

#define gBootData_ImageLength_Offset_c     (0x00)
#define gBootData_ImageLength_Size_c       (0x04)
#define gBootData_SectorsBitmap_Offset_c   gEepromAlignAddr_d(gBootData_ImageLength_Offset_c + \
                                                              gBootData_ImageLength_Size_c)
#define gBootData_SectorsBitmap_Size_c     (32)
#define gBootData_Image_Offset_c           gEepromAlignAddr_d(gBootData_SectorsBitmap_Offset_c + \
                                                              gBootData_SectorsBitmap_Size_c)

/* The maximum amount of MCU Flash memory */
#define gFlashParams_MaxImageLength_c      (P_FLASH_SIZE)

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/
typedef enum {
  gOtaSucess_c = 0,
  gOtaNoImage_c,
  gOtaUpdated_c,
  gOtaError_c,
  gOtaCrcError_c,
  gOtaInvalidParam_c,
  gOtaInvalidOperation_c,
  gOtaExternalFlashError_c,
  gOtaInternalFlashError_c,
} otaResult_t;


/* OTA server - operating modes */
typedef enum {
  gUpgradeImageOnCurrentDevice_c = 0,
  gUseExternalMemoryForOtaUpdate_c,
  gDoNotUseExternalMemoryForOtaUpdate_c,
  gOtaTestingProcess
}otaMode_t;

typedef otaResult_t (*pfOTA_Callback_t)(uint8_t* pBuffer, uint8_t len);

typedef struct otaServer_AppCB_tag{
    pfOTA_Callback_t otaServerImgNotifyCnf;
    pfOTA_Callback_t otaServerSetModeCnf;
    pfOTA_Callback_t otaServerQueryImageCnf;
    pfOTA_Callback_t otaServerPushChunkCnf;
    pfOTA_Callback_t otaServerCancelImgCnf;
    pfOTA_Callback_t otaServerAbortProcessCnf;
    pfOTA_Callback_t otaServerSetFileVersPoliciesCnf;
}otaServer_AppCB_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
extern otaMode_t gUpgradeMode;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*  Registers the OTA component to FSCI
*
*  Input parameters:
*  - fsciInterface: the id of the FSCI interface used
*  Return:

************************************************************************************/
otaResult_t OTA_RegisterToFsci(uint32_t fsciInterface, otaServer_AppCB_t *pCB);

/************************************************************************************
*  Starts the process of writing a new image to the external EEPROM.
*
*  Input parameters:
*  - lenght: the lenght of the image to be written in the EEPROM
*  Return:
*  - gOtaInvalidParam_c: the intended lenght is bigger than the FLASH capacity
*  - gOtaInvalidOperation_c: the process is already started (can be cancelled)
*  - gOtaEepromError_c: can not detect extrenal EEPROM
************************************************************************************/
otaResult_t OTA_StartImage(uint32_t length, uint32_t maxLength);

/************************************************************************************
*  Places the next image chunk into the external FLASH. The CRC will not be computed.
*
*  Input parameters:
*  - pData: pointer to the data chunk
*  - length: the length of the data chunk
*  - pImageLength: if it is not null and the function call is sucessfull, it will be
*       filled with the current lenght of the image
*  Return:
*  - gOtaInvalidParam_c: pData is NULL or the resulting image would be bigger than the 
*       final image length specified with OTA_StartImage()
*  - gOtaInvalidOperation_c: the process is not started
************************************************************************************/
otaResult_t OTA_PushImageChunk(uint8_t* pData, uint8_t length, uint32_t* pImageLength);

/************************************************************************************
*  Finishes the writing of a new image to the external EEPROM.
*  It will write the image header (signature and lenght) and footer (sector copy bitmap).
*
*  Input parameters:
*  - bitmap: pointer to a  byte array indicating the sector erase pattern for the
*       internal FLASH before the image update.
*  Return:
*  - gOtaInvalidOperation_c: the process is not started,
*  - gOtaEepromError_c: error while trying to write the EEPROM 
************************************************************************************/
otaResult_t OTA_CommitImage(uint8_t* bitmap);

/************************************************************************************
*  Cancels the process of writing a new image to the external EEPROM.
*
*  Input parameters:
*  - None
*  Return:
*  - None
************************************************************************************/
void OTA_CancelImage(void);

/*****************************************************************************
*  OTA_SetNewImageFlag
*  
*  Input parameters:
*  - None
*  Return:
*  - None
*  It is called in idle task to write flags from flash - new image present
*****************************************************************************/
void OTA_SetNewImageFlag(void);

/*****************************************************************************
*  It is called to init external eeprom or flash
*  
*  Input parameters:
*  - None
*  Return:
*  - None
*****************************************************************************/
otaResult_t OTA_InitExternalMemory(void);

/************************************************************************************
*  Read from  the external EEPROM or flash.
*
* *  Input parameters:
*  - pData: pointer to the data chunk
*  - length: the length of the data chunk
*  - address: address in external memory
*  Return:
*  - gOtaInvalidParam_c
************************************************************************************/
otaResult_t OTA_ReadExternalMemory(uint8_t* pData, uint8_t length, uint32_t address);

/************************************************************************************
*  Write from the external EEPROM or flash..
*
* *  Input parameters:
*  - pData: pointer to the data chunk
*  - length: the length of the data chunk
*  - address: address in external memory
*  Return:
*  - gOtaInvalidParam_c
************************************************************************************/
otaResult_t OTA_WriteExternalMemory(uint8_t* pData, uint8_t length, uint32_t address);

/************************************************************************************
*  OTA_CrcCompute
*
* *  Input parameters:
*  - pData: pointer to the data chunk
*  - lenData: the length of the data chunk
*  - crcValueOld: crc old value
*  Return:
*  - computed crc
************************************************************************************/
uint16_t OTA_CrcCompute(uint8_t *pData, uint16_t lenData, uint16_t crcValueOld);

/*****************************************************************************
*  OTA_EraseMemory
*
*  This function is called in order to erase external flash or eeprom
*
*****************************************************************************/
otaResult_t OTA_EraseExternalMemory(void);

/*****************************************************************************
*  OTA_EraseBlock
*
*  This function is called in order to erase a block of memory (flash sector)
*
*****************************************************************************/
otaResult_t OTA_EraseBlock(uint32_t address);

/*****************************************************************************
*  OTA_ImageChunkReq
*
*  This function sends a request for a new image chunk over the serial interface
*
*****************************************************************************/
void OTA_ImageChunkReq(uint32_t offset, uint8_t len, uint16_t devId);

/*****************************************************************************
*  OTA_QueryImageReq
*
*  This function sends over the serial interface a query for a specific image
*
*****************************************************************************/
void OTA_QueryImageReq(uint16_t devId, uint16_t manufacturer, uint16_t imgType, uint32_t fileVersion);

#ifdef __cplusplus
}
#endif

#endif /* _OTA_SUPPORT_H_ */
