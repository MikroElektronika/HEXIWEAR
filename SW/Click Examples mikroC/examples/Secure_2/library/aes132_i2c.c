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
 *  \brief         This file contains implementations of I2C functions.
 *  \author Atmel Crypto Products
 *  \date         June 16, 2011
 */

#include <stdint.h>                    //!< C type definitions
#include <string.h>
#include "aes132_i2c.h"                //!< I2C library definitions
#include "__SECURE2_Driver.h"

/** \brief These enumerations are flags for I2C read or write addressing. */
enum aes132_i2c_read_write_flag {
        I2C_WRITE_BIT = (uint8_t) 0x00,        //!< write command id
        I2C_READ_BIT  = (uint8_t) 0x01   //! read command id
};

/** \brief This function initializes and enables the I2C hardware peripheral. */
void aes132p_enable_interface(void)
{
        i2c_enable_phys();
}


/** \brief This function disables the I2C hardware peripheral. */
void aes132p_disable_interface(void)
{
        i2c_disable_phys();
}

/** \brief This function selects a I2C AES132 device.
 *
 * @param[in] device_id I2C address
 * @return always success
 */
uint8_t aes132p_select_device(uint8_t device_id)
{
        return i2c_select_device_phys(device_id);
}


/** \brief This function writes bytes to the device.
 * \param[in] count number of bytes to write
 * \param[in] word_address word address to write to
 * \param[in] data pointer to tx buffer
 * \return status of the operation
 */
uint8_t aes132p_write_memory_physical(uint8_t count, uint16_t word_address, uint8_t *data)
{
        // In both, big-endian and little-endian systems, we send MSB first.
        uint8_t word_address_buffer[2];
        uint8_t data_buffer[258];
        uint8_t aes132_lib_return;
        word_address_buffer [1] = (uint8_t) (word_address & 0xFF);
        word_address_buffer [0] = (uint8_t) (word_address >> 8);

        

        memcpy(&data_buffer[0], word_address_buffer, 2);
        memcpy(&data_buffer[2], data, count);
        
        
        aes132_lib_return = i2c_send_slave_address(I2C_WRITE_BIT);
        if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
                // There is no need to create a Stop condition, since function
                // aes132p_send_slave_address does that already in case of error.
                return aes132_lib_return;
                
        aes132_lib_return = i2c_send_bytes(count+2, (uint8_t *) data_buffer);
        if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) {
                // Don't override the return code from i2c_send_bytes in case of error.
               (void) i2c_send_stop();
                return aes132_lib_return;
        }
        
        // success
        return i2c_send_stop();
}


/** \brief This function reads bytes from the device.
 * \param[in] size number of bytes to write
 * \param[in] word_address word address to read from
 * \param[out] data pointer to rx buffer
 * \return status of the operation
 */
uint8_t aes132p_read_memory_physical(uint8_t size, uint16_t word_address, uint8_t *data)
{
        // Random read:
        // Start, I2C address with write bit, word address,
        // Start, I2C address with read bit

        uint8_t word_address_buffer[2];
        uint8_t aes132_lib_return;
        word_address_buffer [0] = (uint8_t) (word_address >> 8);
        word_address_buffer [1] = (uint8_t) (word_address & 0xFF);



        aes132_lib_return = i2c_send_slave_address(I2C_WRITE_BIT);
        if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
                // There is no need to create a Stop condition, since function
                // aes132p_send_slave_address does that already in case of error.
                return aes132_lib_return;

        aes132_lib_return = i2c_send_bytes(2, (uint8_t *) word_address_buffer);
        if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) {
                // Don't override the return code from i2c_send_bytes in case of error.
                (void) i2c_send_stop();
                return aes132_lib_return;
        }

        aes132_lib_return = i2c_send_slave_address(I2C_READ_BIT);
        if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS)
                return aes132_lib_return;

        return i2c_receive_bytes(size, data);

}


/** \brief This function resynchronizes communication.
 * \return status of the operation
 */
uint8_t aes132p_resync_physical(void)
{
        uint8_t nine_clocks = 0xFF;
        uint8_t n_retries = 2;
        uint8_t aes132_lib_return;

        do {
                aes132_lib_return = i2c_send_start();
                if (aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS) {
                        // If a device is holding SDA or SCL, disabling and
                        // re-enabling the I2C peripheral might help.
                        i2c_disable_phys();
                        i2c_enable_phys();
                }
                if (--n_retries == 0)
                        return aes132_lib_return;

                // Retry creating a Start condition if it failed.
        } while(aes132_lib_return != AES132_FUNCTION_RETCODE_SUCCESS);

        // Do not evaluate the return code which most likely indicates error,
        // since nine_clocks is unlikely to be acknowledged.
        (void) i2c_send_bytes(1, &nine_clocks);

        return i2c_send_stop();
}