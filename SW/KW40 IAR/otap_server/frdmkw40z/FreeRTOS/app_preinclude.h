/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * \file app_preinclude.h
 * This file is the app configuration file which is pre included.
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

#ifndef _APP_PREINCLUDE_H_
#define _APP_PREINCLUDE_H_

/*! *********************************************************************************
 * 	Drivers Configuration
 ********************************************************************************** */
 /* Defines the number of available keys for the keyboard module */
#define gKBD_KeysCount_c        2

/* Specifies the number of physical LEDs on the target board */
#define gLEDsOnTargetBoardCnt_c 4

/* Specifies the type of EEPROM available on the target board */
#define gEepromType_d           gEepromDevice_M25P80_c

/*! *********************************************************************************
 * 	Framework Configuration
 ********************************************************************************** */
/* Defines a smaller FWK configuration */
#define FWK_SMALL_RAM_CONFIG

/* Defines Rx Buffer Size for Serial Manager */
#define gSerialMgrRxBufSize_c   128

/* Defines Tx Queue Size for Serial Manager */
#define gSerialMgrTxQueueSize_c 5

/* Defines Size for Serial Manager Task*/
#define gSerialTaskStackSize_c  1000

/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.*/
#define PoolsDetails_c \
         _block_size_  32  _number_of_blocks_    8 _eol_  \
         _block_size_  64  _number_of_blocks_    12 _eol_  \
         _block_size_ 128  _number_of_blocks_    3 _eol_  \
         _block_size_ 256  _number_of_blocks_    1 _eol_

/* Defines number of timers needed by the application */
#define gTmrApplicationTimers_c         4

/* Defines number of timers needed by the protocol stack */
#define gTmrStackTimers_c               5

/* Set this define TRUE if the PIT frequency is an integer number of MHZ */
#define gTMR_PIT_FreqMultipleOfMHZ_d    0

/* Enables / Disables the precision timers platform component */
#define gTimestamp_Enabled_d            0

/* Enable/Disable Low Power Timer */
#define gTMR_EnableLowPowerTimers       0

/* Enable/Disable PowerDown functionality in PwrLib */
#define cPWR_UsePowerDownMode           0

/* Enable/Disable BLE Link Layer DSM */
#define cPWR_BLE_LL_Enable              0

/* Default Deep Sleep Mode */
#define cPWR_DeepSleepMode              3
             
/* Enable/Diable FSCI */
#define gFsciIncluded_c                 1
             
/* Enable/Disable FSCI 2 byte command length */
#define gFsciLenHas2Bytes_c             1
             
/* Enable/Disable the FSCI BLE OTAP module */
#define gFsciBleOtapEnabled_d           1

/*! *********************************************************************************
 * 	RTOS Configuration
 ********************************************************************************** */
/* Defines the RTOS used */
#define FSL_RTOS_FREE_RTOS

/* Defines number of OS events used */
#define osNumberOfEvents        4

/* Defines number of OS semaphores used */
#define osNumberOfSemaphores    1

/* Defines main task stack size */
#define gMainThreadStackSize_c  1024
           
/* Defines total heap size used by the OS */
#define gTotalHeapSize_c        9000
           
/*! *********************************************************************************
 * 	BLE Stack Configuration
 ********************************************************************************** */
/* Defines Host task stack size */
#define gHost_TaskStackSize_c 1280

/* Defines L2cap task stack size */
#define gL2ca_TaskStackSize_c 1280

#define BD_ADDR             0x12,0x00,0x00,0x9F,0x04,0x00


#endif /* _APP_PREINCLUDE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */
