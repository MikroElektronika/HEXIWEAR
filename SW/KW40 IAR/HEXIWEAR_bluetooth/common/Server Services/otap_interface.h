 /**
 *    @file otap_service.h
 */

/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file otap_interface.h
 * This file is the interface file for the BLE OTAP Service/Profile
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

#ifndef _OTAP_INTERFACE_H_
#define _OTAP_INTERFACE_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/

/*! BLE OTAP Protocol definitions. */
#define gOtap_CmdIdFieldSize_c              (1U)
#define gOtap_ImageIdFieldSize_c            (2U)
#define gOtap_ImageVersionFieldSize_c       (8U)
#define gOtap_ChunkSeqNumberSize_c          (1U)
#define gOtap_MaxChunksPerBlock_c           (256U)

/*!< ATT_MTU - 3 - 1 - 1 = 23 - 3 - 1 - 1 = 20 - 2 = 18 for ATT Write Without Response */  
#define gOtap_ImageChunkDataSizeAtt_c       (20U - gOtap_CmdIdFieldSize_c - gOtap_ChunkSeqNumberSize_c)
#define gOtap_ImageChunkDataSizeL2capCoc_c  (111U)  /* Exactly 5 full 23 byte HCI packets for each L2CAP Packet */

#define gOtap_L2capLePsm_c                  (0x004F)

/*! BLE OTAP Image File Format Definitions */

/*! Enumerated type for the recognized image file header versions. */
typedef enum bleOtaFileHeaderVersion_tag
{
    gbleOtapHeaderVersion0100_c             = 0x0100,
} bleOtaFileHeaderVersion_t;

#define gBleOtaFileHeaderIdentifier_c           (0x0B1EF11E)
#define gBleOtaFileHeaderDefaultFieldControl_c  (0x0000)
#define gBleOtaCompanyIdentifier_c              (0x01FF)
#define gBleOtaHeaderStrLength_c                (32)

#define gBleOtaImageIdCurrentRunningImage_c     (0x0000)
#define gBleOtaImageIdNoImageAvailable_c        (0xFFFF)

/*! BLE OTAP Image File Header */
typedef PACKED_STRUCT bleOtaImageFileHeader_tag
{
  uint32_t  fileIdentifier;                     /*!< 0x0B1EF11E - Magic number to identify an image file as being a BLE upgrade image file. */
  uint16_t  headerVersion;                      /*!< Version of the header. */
  uint16_t  headerLength;                       /*!< Header length. */
  uint16_t  fieldControl;                       /*!< Header field control - shows if any onther non-default fields are presetn in the header.*/
  uint16_t  companyId;                          /*!< 0x01FF - FSL Company Identifier. */
  uint8_t   imageId[gOtap_ImageIdFieldSize_c];  /*!< Should be unique for each image on an OTAP Server. */
  uint8_t   imageVersion[gOtap_ImageVersionFieldSize_c];
  uint8_t   headerString[gBleOtaHeaderStrLength_c];
  uint32_t  totalImageFileSize;                 /*!< Total image file size including the header. */
} bleOtaImageFileHeader_t;

/*! BLE OTAP Image File Sub-element tag id enumeration. */
typedef enum bleOtaImageFileSubElementTagId_tag
{
    /* Reserved sub-element tags */
    gBleOtaSubElemTagIdUpgradeImage_c       = 0x0000,   /*!< Sub-element contains the actual upgrade image. */
    /* Manufacturer specific sub-element tags */
    gBleOtaSubElemTagIdSectorBitmap_c       = 0xF000,   /*!< Sub-element contains the sector bitmap specific to the FLASH memory of a the target device.
                                                         *   The size of this sub-element value is implementation specific. */
    gBleOtaSubElemTagIdImageFileCrc_c       = 0xF100,   /*!< Sub-element contains the CRC of the image file (The CRC does not cover this sub-element)
                                                         *   The size of this sub-element value is implementation specific. */
} bleOtaImageFileSubElementTagId_t;

typedef PACKED_STRUCT subElementHeader_tag
{
  uint16_t tagId;       /*!< Sub-element tag identifier. */
  uint32_t dataLen;     /*!< Sub-element value field length. */
} subElementHeader_t;


/************************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
************************************************************************************/

/*! OTAP Client (Target) - Configuration */
typedef struct otapClientConfig_tag
{
    uint16_t    hService;
} otapClientConfig_t;

/*! OTAP Server (Source) - Configuration */
typedef struct otapServerConfig_tag
{
    uint16_t    hService;
    uint16_t    hControlPoint;
    uint16_t    hControlPointCccd;
    uint16_t    hData;
} otapServerConfig_t;

/*! BLE OTAP Protocol statuses. */
typedef enum otapStatus_tag
{
    gOtapStatusSuccess_c                        = 0x00, /*!< The operation was successful. */
    gOtapStatusImageDataNotExpected_c           = 0x01, /*!< The OTAP Server tried to send an image data chunk to the OTAP Client but the Client was not expecting it. */
    gOtapStatusUnexpectedTransferMethod_c       = 0x02, /*!< The OTAP Server tried to send an image data chunk using a transfer method the OTAP Client does not support/expect. */
    gOtapStatusUnexpectedCmdOnDataChannel_c     = 0x03, /*!< The OTAP Server tried to send an unexpected command (different from a data chunk) on a data Channel (ATT or CoC) */
    gOtapStatusUnexpectedL2capChannelOrPsm_c    = 0x04, /*!< The selected channel or PSM is not valid for the selected transfer method (ATT or CoC). */
    gOtapStatusUnexpectedOtapPeer_c             = 0x05, /*!< A command was received from an unexpected OTAP Server or Client device. */
    gOtapStatusUnexpectedCommand_c              = 0x06, /*!< The command sent from the OTAP peer device is not expected in the current state. */
    gOtapStatusUnknownCommand_c                 = 0x07, /*!< The command sent from the OTAP peer device is not known. */
    gOtapStatusInvalidCommandLength_c           = 0x08, /*!< Invalid command length. */
    gOtapStatusInvalidCommandParameter_c        = 0x09, /*!< A parameter of the command was not valid. */
    gOtapStatusFailedImageIntegrityCheck_c      = 0x0A, /*!< The image integrity check has failed. */
    gOtapStatusUnexpectedSequenceNumber_c       = 0x0B, /*!< A chunk with an unexpected sequence number has been received. */
    gOtapStatusImageSizeTooLarge_c              = 0x0C, /*!< The upgrade image size is too large for the OTAP Client. */
    gOtapStatusUnexpectedDataLength_c           = 0x0D, /*!< The length of a Data Chunk was not expected. */
    gOtapStatusUnknownFileIdentifier_c          = 0x0E, /*!< The image file identifier is not recognized. */
    gOtapStatusUnknownHeaderVersion_c           = 0x0F, /*!< The image file header version is not recognized. */
    gOtapStatusUnexpectedHeaderLength_c         = 0x10, /*!< The image file header length is not expected for the current header version. */
    gOtapStatusUnexpectedHeaderFieldControl_c   = 0x11, /*!< The image file header field control is not expected for the current header version. */
    gOtapStatusUnknownCompanyId_c               = 0x12, /*!< The image file header company identifier is not recognized. */
    gOtapStatusUnexpectedImageId_c              = 0x13, /*!< The image file header image identifier is not as expected. */
    gOtapStatusUnexpectedImageVersion_c         = 0x14, /*!< The image file header image version is not as expected. */
    gOtapStatusUnexpectedImageFileSize_c        = 0x15, /*!< The image file header image file size is not as expected. */
    gOtapStatusInvalidSubElementLength_c        = 0x16, /*!< One of the sub-elements has an invalid length. */
    gOtapStatusImageStorageError_c              = 0x17, /*!< An image storage error has occurred. */
    gOtapStatusInvalidImageCrc_c                = 0x18, /*!< The computed CRC does not match the received CRC. */
    gOtapStatusInvalidImageFileSize_c           = 0x19, /*!< The image file size is not valid. */
    gOtapStatusInvalidL2capPsm_c                = 0x1A, /*!< A block transfer request has been made via the L2CAP CoC method but the specified Psm is not known. */
    gOtapStatusNoL2capPsmConnection_c           = 0x1B, /*!< A block transfer request has been made via the L2CAP CoC method but there is no valid PSM connection. */
    gOtapNumberOfStatuses_c,
} otapStatus_t;

/*! OTAP Server storage mode type ennumeration. */
typedef enum otapServerStorageMode_tag
{
    gOtapServerStoargeNone_c            = 0x00, /*!< The OTAP Server does not have internal storage and all commands will be relayed between the OTAP Client and the PC (or other serial connected device). */
    gOtapServerStoargeInternal_c        = 0x01, /*!< The OTAP Server has internal storage. It will download an image from a PC (or other serial connected device) and it will then send it to the OTAP Client. */
} otapServerStorageMode_t;

/*! OTAP Transfer Methods type defintion */
typedef enum otapTransferMethod_tag
{
    gOtapTransferMethodAtt_c            = 0x00,
    gOtapTransferMethodL2capCoC_c       = 0x01,
} otapTransferMethod_t;

/*! OTAP Protocol Command Id ennumeration */
typedef enum otapCmdIdt_tag
{
    gOtapCmdIdNoCommand_c               = 0x00, /*!< No command. */
    gOtapCmdIdNewImageNotification_c    = 0x01, /*!< OTAP Server -> OTAP Client - A new image is available on the OTAP Server */
    gOtapCmdIdNewImageInfoRequest_c     = 0x02, /*!< OTAP Client -> OTAP Server - The OTAP Client requests image information from the OTAP Server */
    gOtapCmdIdNewImageInfoResponse_c    = 0x03, /*!< OTAP Server -> OTAP Client - The OTAP Server sends requested image information to the OTAP Client */
    gOtapCmdIdImageBlockRequest_c       = 0x04, /*!< OTAP Client -> OTAP Server - The OTAP Client requests an image block from the OTAP Server */
    gOtapCmdIdImageChunk_c              = 0x05, /*!< OTAP Server -> OTAP Client - The OTAP Server sends an image chunk to the OTAP Client */
    gOtapCmdIdImageTransferComplete_c   = 0x06, /*!< OTAP Client -> OTAP Server - The OTAP Client notifies the OTAP Server that an image transfer was completed*/
    gOtapCmdIdErrorNotification_c       = 0x07, /*!< Bidirectional - An error has occurred */
    gOtapCmdIdStopImageTransfer_c       = 0x08, /*!< OTAP Client -> OTAP Server - The OTAP Client request the OTAP Server to stop an image transfer. */
} otapCmdIdt_t;

/*! OTAP New Image Notification Command */
typedef PACKED_STRUCT otapCmdNewImgNotification_tag
{
    uint8_t     imageId[gOtap_ImageIdFieldSize_c];
    uint8_t     imageVersion[gOtap_ImageVersionFieldSize_c];
    uint32_t    imageFileSize;
} otapCmdNewImgNotification_t;

/*! OTAP New Image Info Request Command */
typedef PACKED_STRUCT otapCmdNewImgInfoReq_tag
{
    uint8_t     currentImageId[gOtap_ImageIdFieldSize_c];
    uint8_t     currentImageVersion[gOtap_ImageVersionFieldSize_c];
} otapCmdNewImgInfoReq_t;

/*! OTAP New Image Info Response Command */
typedef PACKED_STRUCT otapCmdNewImgInfoRes_tag
{
    uint8_t     imageId[gOtap_ImageIdFieldSize_c];
    uint8_t     imageVersion[gOtap_ImageVersionFieldSize_c];
    uint32_t    imageFileSize;
} otapCmdNewImgInfoRes_t;

/*! OTAP Image Block Request Command */
typedef PACKED_STRUCT otapCmdImgBlockReq_tag
{
    uint8_t     imageId[gOtap_ImageIdFieldSize_c];
    uint32_t    startPosition;
    uint32_t    blockSize;
    uint16_t    chunkSize;
    uint8_t     transferMethod;     /*!< otapTransferMethod_t - ATT or L2CAP Credit Oriented Channels (CoC) */
    uint16_t    l2capChannelOrPsm;
} otapCmdImgBlockReq_t;

/*! OTAP Image Chunk Command - for ATT transfer method only. */
typedef PACKED_STRUCT otapCmdImgChunkAtt_tag
{
    uint8_t     seqNumber;  /*!< The sequence number of the sent chunk. Max 256 chunks per block. */
    uint8_t     data[gOtap_ImageChunkDataSizeAtt_c];
} otapCmdImgChunkAtt_t;

/*! OTAP Image Chunk Command - for CoC transfer method only. */
typedef PACKED_STRUCT otapCmdImgChunkCoc_tag
{
    uint8_t     seqNumber;  /*!< The sequence number of the sent chunk. Max 256 chunks per block. */
    uint8_t     data[gOtap_ImageChunkDataSizeL2capCoc_c];
} otapCmdImgChunkCoc_t;

/*! OTAP Image Transfer Complete Command */
typedef PACKED_STRUCT otapCmdImgTransferComplete_tag
{
    uint8_t     imageId[gOtap_ImageIdFieldSize_c];
    uint8_t     status;     /*!< otapStatus_t */
} otapCmdImgTransferComplete_t;

/*! OTAP Error Notification Command */
typedef PACKED_STRUCT otapErrNotification_tag
{
    uint8_t     cmdId;      /*!< otapCmdIdt_t - The command which caused the error. */
    uint8_t     errStatus;  /*!< otapStatus_t */
} otapErrNotification_t;

/*! OTAP Stop Image Transfer Command */
typedef PACKED_STRUCT otapCmdStopImgTransfer_tag
{
    uint8_t     imageId[gOtap_ImageIdFieldSize_c];
} otapCmdStopImgTransfer_t;

/*! General OTAP Command type struncture.
 *  Only the ATT Chunk command is included here. */
typedef PACKED_STRUCT otapCommand_tag
{
    uint8_t   cmdId;
    PACKED_UNION
    {
        /* Pairing Methods */
        otapCmdNewImgNotification_t         newImgNotif;
        otapCmdNewImgInfoReq_t              newImgInfoReq;
        otapCmdNewImgInfoRes_t              newImgInfoRes;
        otapCmdImgBlockReq_t                imgBlockReq;
        otapCmdImgChunkAtt_t                imgChunkAtt;
        otapCmdImgTransferComplete_t        imgTransComplete;
        otapErrNotification_t               errNotif;
        otapCmdStopImgTransfer_t            stopImgTransf;
    } cmd;
} otapCommand_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/*! OTAP Protocol Command Id to Command Length table.
 *  The length includes the Command Id and the Command Payload. */
static const uint8_t  cmdIdToCmdLengthTable[] = 
{
    [gOtapCmdIdNoCommand_c]             = 0,
    [gOtapCmdIdNewImageNotification_c]  = sizeof(otapCmdNewImgNotification_t) + gOtap_CmdIdFieldSize_c,
    [gOtapCmdIdNewImageInfoRequest_c]   = sizeof(otapCmdNewImgInfoReq_t) + gOtap_CmdIdFieldSize_c,
    [gOtapCmdIdNewImageInfoResponse_c]  = sizeof(otapCmdNewImgInfoRes_t) + gOtap_CmdIdFieldSize_c,
    [gOtapCmdIdImageBlockRequest_c]     = sizeof(otapCmdImgBlockReq_t) + gOtap_CmdIdFieldSize_c,
    [gOtapCmdIdImageChunk_c]            = sizeof(otapCmdImgChunkAtt_t) + gOtap_CmdIdFieldSize_c, /*!< For ATT transfer method only. */
    [gOtapCmdIdImageTransferComplete_c] = sizeof(otapCmdImgTransferComplete_t) + gOtap_CmdIdFieldSize_c,
    [gOtapCmdIdErrorNotification_c]     = sizeof(otapErrNotification_t) + gOtap_CmdIdFieldSize_c,
    [gOtapCmdIdStopImageTransfer_c]     = sizeof(otapCmdStopImgTransfer_t) + gOtap_CmdIdFieldSize_c,
};

#define gOtapCmdImageChunkCocLength_c   (sizeof(otapCmdImgChunkCoc_t) + gOtap_CmdIdFieldSize_c)

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!**********************************************************************************
* \brief        Starts the OTAP Client Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server 
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t OtapCS_Start(otapClientConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Stops the OTAP Client Service functionality
*
* \param[in]    pServiceConfig  Pointer to structure that contains server 
*                               configuration information.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t OtapCS_Stop(otapClientConfig_t *pServiceConfig);

/*!**********************************************************************************
* \brief        Subscribes a GATT client to the OTAP Client Service
*
* \param[in]    pClient  Client Id in Device DB.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t OtapCS_Subscribe(deviceId_t clientDeviceId);

/*!**********************************************************************************
* \brief        Unsubscribes a GATT client from the OTAP Client Service
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t OtapCS_Unsubscribe();

/*!**********************************************************************************
* \brief        Sends a command to the OTAP Server via ATT indications if the server
*               has enabled indications for the proper attribute.
*
* \param[in]    serviceHandle   Service handle.
* \param[in]    pCommand        Pointer to the OTAP command.
* \param[in]    cmdLength       Length of the command.
*
* \return       gBleSuccess_c or error.
************************************************************************************/
bleResult_t OtapCS_SendCommandToOtapServer (uint16_t serviceHandle,
                                            void* pCommand,
                                            uint16_t cmdLength);

//bleResult_t Tms_RecordTemperatureMeasurement (uint16_t serviceHandle, int16_t temperature);

#ifdef __cplusplus
}
#endif

#endif /* _OTAP_INTERFACE_H_ */

/*! **********************************************************************************
 * @}
 ************************************************************************************/
