// ----------------------------------------------------------------------------
//         ATMEL Crypto-Devices Software Support  -  Colorado Springs, CO -
// ----------------------------------------------------------------------------
// DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

/** \file
 *  \brief Command Marshaling Layer of ATAES132 Library
 *  \author Atmel Crypto Products
 *  \date   June 08, 2015
 */


#include <string.h>                    // needed for memcpy()
#include "aes132_comm_marshaling.h"    // definitions and declarations for the Command Marshaling module


/** \brief This function sends data to the device.
 * \param[in] count number of bytes to send
 * \param[in] word_address word address
 * \param[in] data pointer to tx data
 * \return status of the operation
 */
uint8_t aes132m_write_memory(uint8_t count, uint16_t word_address, uint8_t *data)
{
        return aes132c_access_memory(count, word_address, data,  AES132_WRITE);
}


/** \brief This function reads data from the device.
 * \param[in] size number of bytes to read
 * \param[in] word_address pointer to word address
 * \param[out] data pointer to rx data
 * \return status of the operation
*/
uint8_t aes132m_read_memory(uint8_t size, uint16_t word_address, uint8_t *data)
{
        return aes132c_access_memory(size, word_address, data, AES132_READ);
}


/** \brief This function creates a command packet, sends it, and receives its response.
 *         The caller has to allocate enough space for txBuffer and rxBuffer so that
 *         the generated command and the expected response respectively do not overflow
 *         these buffers.
 *
 * \param[in] op_code command op-code
 * \param[in] mode command mode
 * \param[in] param1 first parameter
 * \param[in] param2 second parameter
 * \param[in] datalen1 number of bytes in first data block
 * \param[in] data1 pointer to first data block
 * \param[in] datalen2 number of bytes in second data block
 * \param[in] data2 pointer to second data block
 * \param[in] datalen3 number of bytes in third data block
 * \param[in] data3 pointer to third data block
 * \param[in] datalen4 number of bytes in fourth data block
 * \param[in] data4 pointer to fourth data block
 * \param[in] tx_buffer pointer to command buffer
 * \param[out] rx_buffer pointer to response buffer
 * \return status of the operation
 */
uint8_t aes132m_execute(uint8_t op_code, uint8_t mode, uint16_t param1, uint16_t param2,
                        uint8_t datalen1, uint8_t *data1, uint8_t datalen2, uint8_t *data2,
                        uint8_t datalen3, uint8_t *data3, uint8_t datalen4, uint8_t *data4,
                        uint8_t *tx_buffer, uint8_t *rx_buffer)
{
        uint8_t *p_buffer;
        uint8_t len;

        // Assemble command.
        len = datalen1 + datalen2 + datalen3 + datalen4 + AES132_COMMAND_SIZE_MIN;
        p_buffer = tx_buffer;
        *p_buffer++ = len;
        *p_buffer++ = op_code;
        *p_buffer++ = mode;
        *p_buffer++ = param1 >> 8;
        *p_buffer++ = param1 & 0xFF;
        *p_buffer++ = param2 >> 8;
        *p_buffer++ = param2 & 0xFF;

        if (datalen1 > 0) {
                memcpy(p_buffer, data1, datalen1);
                p_buffer += datalen1;
        }
        if (datalen2 > 0) {
                memcpy(p_buffer, data2, datalen2);
                p_buffer += datalen2;
        }
        if (datalen3 > 0) {
                memcpy(p_buffer, data3, datalen3);
                p_buffer += datalen3;
        }
        if (datalen4 > 0) {
                memcpy(p_buffer, data4, datalen4);
                p_buffer += datalen4;
        }

        // Send command and receive response.
        return aes132c_send_and_receive(&tx_buffer[0], AES132_RESPONSE_SIZE_MAX,
                                &rx_buffer[0], AES132_OPTION_DEFAULT);
}