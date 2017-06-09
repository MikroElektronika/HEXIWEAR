/**
 * \file MAXIM_info.h
 * \version 1.00
 * \brief this file contains sensor MAX30101's general info and constants
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
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
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#pragma once

//#define MAXIM_DEBUG

#define MAXIM_I2C_ADDRESS         ( 0x57 )
#define MAXIM_I2C_BAUDRATE        ( I2C_BAUDRATE )
#define MAXIM_BYTES_PER_ADC_VALUE ( 3 )
#define MAXIM_FIFO_DEPTH          ( 128 )


#define MAXIM_NEW_SAMPLE_CHUNK    ( 256 )
#define MAXIM_INIT_SAMPLE_SIZE 	  ( MAXIM_NEW_SAMPLE_CHUNK )    // 256
#define MAXIM_FINAL_SAMPLE_SIZE   ( MAXIM_NEW_SAMPLE_CHUNK*8 )  // 2048

#define MAXIM_HR_FREQ_MIN ( 0.75 )
#define MAXIM_HR_FREQ_MAX ( 3 )
#define MAXIM_PEAK_THRESHOLD ( 1000 )
#define MAXIM_FIFO_OVERFLOW  ( -1 )

// FIFO bit-mask
#define MAXIM_FIFO_BITMASK ( 0x0003FFFF )

// FIFO bit-shifts, depending on the ADC resolution
#define MAXIM_FIFO_BITSHIFT_18 ( 0 )
#define MAXIM_FIFO_BITSHIFT_17 ( 1 )
#define MAXIM_FIFO_BITSHIFT_16 ( 2 )
#define MAXIM_FIFO_BITSHIFT_15 ( 3 )

/** registers info */

#define MAXIM_REG_INT_STATUS_1 ( 0x00 )
#define MAXIM_REG_INT_STATUS_2 ( 0x01 )

#define MAXIM_REG_INTERRUPT_ENABLE_1 ( 0x02 )
#define MAXIM_REG_INTERRUPT_ENABLE_2 ( 0x03 )

#define MAXIM_REG_FIFO_WR_PTR ( 0x04 )
#define MAXIM_REG_FIFO_OV_PTR ( 0x05 )
#define MAXIM_REG_FIFO_RD_PTR ( 0x06 )
#define MAXIM_REG_FIFO_DATA   ( 0x07 )

#define MAXIM_REG_FIFO_CFG ( 0x8 )
#define MAXIM_REG_MODE_CFG ( 0x9 )
#define MAXIM_REG_SPO2_CFG ( 0xA )

#define MAXIM_REG_LED_RED_PA   ( 0xC )
#define MAXIM_REG_LED_IR_PA    ( 0xD )
#define MAXIM_REG_LED_GREEN_PA ( 0xE )
#define MAXIM_REG_PROXY_PA     ( 0x10 )

#define MAXIM_PROXY_THR        ( 1000 )

#define MAXIM_REG_MULTILED_MODE_CR_12 ( 0x11 )
#define MAXIM_REG_MULTILED_MODE_CR_34 ( 0x12 )

#define MAXIM_REG_TEMP_INT    ( 0x1F )
#define MAXIM_REG_TEMP_FRAC   ( 0x20 )
#define MAXIM_REG_TEMP_CONFIG ( 0x21 )

#define MAXIM_REG_PROXY_INT_THR ( 0x30 )

#define MAXIM_REG_ID_REV  ( 0xFE )
#define MAXIM_REG_ID_PART ( 0xFF )

#define MAXIM_SLOT_NUM ( 4 )
/** bit fields info */

/** interrupt enable */

#define MAXIM_EN_IRQ_BIT_FIFO_ALMOST_FULL ( 1 << 7 )
#define MAXIM_EN_IRQ_BIT_NEW_SAMPLE_RDY   ( 1 << 6 )
#define MAXIM_EN_IRQ_BIT_AMBIENT_OVF      ( 1 << 5 )
#define MAXIM_EN_IRQ_BIT_PROX_INT         ( 1 << 4 )
#define MAXIM_EN_IRQ_BIT_INT_TEMP_RDY     ( 1 << 1 )

/** interrupt status */

#define MAXIM_DATA_RDY_BIT_FIFO_ALMOST_FULL ( 1 << 7 )
#define MAXIM_DATA_RDY_BIT_NEW_SAMPLE_RDY   ( 1 << 6 )
#define MAXIM_DATA_RDY_BIT_AMBIENT_OVF      ( 1 << 5 )
#define MAXIM_DATA_RDY_BIT_PROX_INT         ( 1 << 4 )
#define MAXIM_DATA_RDY_BIT_INT_TEMP_RDY     ( 1 << 1 )

/** FIFO pointers */

#define MAXIM_FIFO_WR_PTR_SHIFT ( 0 )
#define MAXIM_FIFO_WR_PTR_MASK  ( 0x1F << MAXIM_FIFO_WR_PTR_SHIFT )

#define MAXIM_FIFO_RD_PTR_SHIFT ( 0 )
#define MAXIM_FIFO_RD_PTR_MASK  ( 0x1F << MAXIM_FIFO_RD_PTR_SHIFT )

#define MAXIM_FIFO_OVF_CNT_PTR_SHIFT ( 0 )
#define MAXIM_FIFO_OVF_CNT_PTR_MASK  ( 0x1F << MAXIM_FIFO_OVF_CNT_PTR_SHIFT )

/** FIFO configuration */

#define MAXIM_FIFO_CFG_A_FULL_SHIFT ( 0 )
#define MAXIM_FIFO_CFG_A_FULL_MASK  ( 0xF << MAXIM_FIFO_CFG_A_FULL_SHIFT )

#define MAXIM_FIFO_CFGBIT_FIFO_ROLLOVER ( 1 << 4 )

#define MAXIM_FIFO_CFG_FIFO_OVS_SHIFT ( 5 )
#define MAXIM_FIFO_CFG_FIFO_OVS_MASK  ( 0x7 << MAXIM_FIFO_CFG_FIFO_OVS_SHIFT )

/** mode configuration */

#define MAXIM_MODE_CFGBIT_SLEEP ( 1 << 7 )
#define MAXIM_MODE_CFGBIT_RST   ( 1 << 6 )

#define MAXIM_MODE_SHIFT ( 0 )
#define MAXIM_MODE_MASK  ( 0x7 << MAXIM_MODE_SHIFT )

// sample rate in sample/sec
#define MAXIM_CFG_SR_SHIFT ( 2 )
#define MAXIM_CFG_SR_MASK  ( 0x7 << MAXIM_CFG_SR_SHIFT )

// ADC range
#define MAXIM_CFG_ADC_SHIFT ( 5 )
#define MAXIM_CFG_ADC_MASK  ( 0x3 << MAXIM_CFG_ADC_SHIFT )

/** LED pulse amplitude */

// pulse width is in [us] and also determines the ADC resolution
#define MAXIM_CFG_LED_PW_SHIFT ( 0 )
#define MAXIM_CFG_LED_PW_MASK  ( 0x3 << MAXIM_CFG_LED_PW_SHIFT )

/** Multi-LED mode control registers */

// slot modes
#define MAXIM_SLOT_1_3_SHIFT ( 0 )
#define MAXIM_SLOT_1_3_MASK  ( 0x7 << MAXIM_SLOT_1_3_SHIFT )
#define MAXIM_SLOT_2_4_SHIFT ( 4 )
#define MAXIM_SLOT_2_4_MASK  ( 0x7 << MAXIM_SLOT_2_4_SHIFT )

/** temperature data */
#define MAXIM_TEMP_EN ( 1 )
