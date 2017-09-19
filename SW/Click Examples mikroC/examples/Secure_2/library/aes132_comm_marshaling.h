/** \file
 *  \brief  Definitions and Prototypes for Command Marshaling Layer of ATAES132 Library
 *  \author Atmel Crypto Products
 *  \date   June 08, 2015

* \copyright Copyright (c) 2015 Atmel Corporation. All rights reserved.
*
* \atmel_crypto_device_library_license_start
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* 4. This software may only be redistributed and used in connection with an
*    Atmel integrated circuit.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \atmel_crypto_device_library_license_stop
 *
   <table>
     <caption align="top">Command Packet Structure</caption>
     <tr>
       <th width=25%>Byte #</th> <th width=25%>Name</th> <th>Meaning</th>
     </tr>
     <tr>
       <td>0</td>
       <td>Count</td>
       <td>Number of bytes in the packet, includes the count byte, body and the checksum</td>
     </tr>
     <tr>
       <td>1</td>
       <td>Op-Code</td>
       <td>Indicates type of command</td>
     </tr>
     <tr>
       <td>2</td>
       <td>Mode</td>
       <td>Command Modifier</td>
     </tr>
	 <tr>
       <td>3 and 4</td>
       <td>Parameter 1</td>
       <td>First Command Parameter</td>
     </tr>
     <tr>
       <td>5 and 6</td>
       <td>Parameter 2</td>
       <td>Second Command Parameter</td>
     </tr>
     <tr>
       <td>7 to n</td>
       <td>Data (not for every command)</td>
       <td>Optional Input Data</td>
     </tr>
     <tr>
       <td>n+1 to n+2</td>
       <td>Checksum</td>
       <td>Checksum of the command packet</td>
     </tr>
   </table>

   <table>
     <caption align="top">Response Packet Structure</caption>
     <tr>
       <th width=25%>Byte #</th> <th width=25%>Name</th> <th>Meaning</th>
     </tr>
     <tr>
       <td>0</td>
       <td>Count</td>
       <td>Number of bytes in the packet, includes the count byte, body and the checksum</td>
     </tr>
     <tr>
       <td>1</td>
       <td>Status</td>
       <td>Command return code</td>
     </tr>
     <tr>
       <td>2 to n</td>
       <td>Data</td>
       <td>Optional Output Data</td>
     </tr>
     <tr>
       <td>n+1 to n+2</td>
       <td>Checksum</td>
       <td>Checksum of the command packet</td>
     </tr>
   </table>
 */

#ifndef AES132_COMM_MARSHALING_H
#   define AES132_COMM_MARSHALING_H

#include "aes132_comm.h" // definitions and declarations for the communication module


/** \defgroup ataes132_command_marshaling Module 01: Command Marshaling
 \brief
 * A function is provided for every ATAES132 command. These functions check the parameters,
 * assemble a command packet, send it, receive its response, and return the status of the operation
 * and the response.
@{ */

/** \name OpCodes for ATAES132 Commands
@{ */
#define AES132_AUTH              ((uint8_t) 0x03)       //!< Auth command op-code
#define AES132_AUTH_CHECK        ((uint8_t) 0x15)       //!< AuthCheck command op-code
#define AES132_AUTH_COMPUTE      ((uint8_t) 0x14)       //!< AuthCompute command op-code
#define AES132_BLOCK_READ        ((uint8_t) 0x10)       //!< BlockRead command op-code
#define AES132_COUNTER           ((uint8_t) 0x0A)       //!< Counter command op-code
#define AES132_CRUNCH            ((uint8_t) 0x0B)       //!< Crunch command op-code
#define AES132_DECRYPT           ((uint8_t) 0x07)       //!< Decrypt command op-code
#define AES132_ENC_READ          ((uint8_t) 0x04)       //!< EncRead command op-code
#define AES132_ENCRYPT           ((uint8_t) 0x06)       //!< Encrypt command op-code
#define AES132_ENC_WRITE         ((uint8_t) 0x05)       //!< EncWrite command op-code
#define AES132_INFO              ((uint8_t) 0x0C)       //!< Info command op-code
#define AES132_KEY_CREATE        ((uint8_t) 0x08)       //!< KeyCreate command op-code
#define AES132_KEY_IMPORT        ((uint8_t) 0x19)       //!< KeyImport command op-code
#define AES132_KEY_LOAD          ((uint8_t) 0x09)       //!< KeyLoad command op-code
#define AES132_KEY_TRANSFER      ((uint8_t) 0x1A)       //!< KeyTransfer command op-code
#define AES132_LEGACY            ((uint8_t) 0x0F)       //!< Legacy command op-code
#define AES132_LOCK              ((uint8_t) 0x0D)       //!< Lock command op-code
#define AES132_NONCE             ((uint8_t) 0x01)       //!< Nonce command op-code
#define AES132_NONCE_COMPUTE     ((uint8_t) 0x13)       //!< NonceCompute command op-code
#define AES132_RANDOM            ((uint8_t) 0x02)       //!< Random command op-code
#define AES132_RESET             ((uint8_t) 0x00)       //!< Reset command op-code
#define AES132_SLEEP             ((uint8_t) 0x11)       //!< Sleep command op-code
#define AES132_TEMP_SENSE        ((uint8_t) 0x0E)       //!< TempSense command op-code
/** @} */

uint8_t aes132m_read_memory(uint8_t count, uint16_t word_address, uint8_t *data);
uint8_t aes132m_write_memory(uint8_t count, uint16_t word_address, uint8_t *data);
uint8_t aes132m_execute(uint8_t op_code, uint8_t mode, uint16_t param1, uint16_t param2,
			uint8_t datalen1, uint8_t *data1, uint8_t datalen2, uint8_t *data2,
			uint8_t datalen3, uint8_t *data3, uint8_t datalen4, uint8_t *data4,
			uint8_t *tx_buffer, uint8_t *rx_buffer);

/** @} */

#endif
