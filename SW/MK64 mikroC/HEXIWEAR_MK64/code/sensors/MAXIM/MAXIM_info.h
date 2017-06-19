// File: MAXIM_info.h

// Some commonly used macros in the MAXIM sensor module.

#ifndef _MAXIM_info_h_
#define _MAXIM_info_h_

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define MAXIM_I2C_ADDRESS         ( 0x57 )
#define MAXIM_I2C_BAUDRATE        ( I2C_BAUDRATE )
#define MAXIM_BYTES_PER_ADC_VALUE ( 3 )
#define MAXIM_FIFO_DEPTH          ( 32 )


#define MAXIM_NEW_SAMPLE_CHUNK    ( 256 )
#define MAXIM_INIT_SAMPLE_SIZE    ( MAXIM_NEW_SAMPLE_CHUNK )     // 256
#define MAXIM_FINAL_SAMPLE_SIZE   ( MAXIM_NEW_SAMPLE_CHUNK * 8 ) // 2048

#define MAXIM_HR_FREQ_MIN ( 0.75 )
#define MAXIM_HR_FREQ_MAX ( 3 )
#define MAXIM_PEAK_THRESHOLD ( 1000 )
#define MAXIM_FIFO_OVERFLOW  ( -1 )

// FIFO bit-mask.
#define MAXIM_FIFO_BITMASK ( 0x0003FFFF )

// FIFO bit-shifts, depending on the ADC resolution.
#define MAXIM_FIFO_BITSHIFT_18 ( 0 )
#define MAXIM_FIFO_BITSHIFT_17 ( 1 )
#define MAXIM_FIFO_BITSHIFT_16 ( 2 )
#define MAXIM_FIFO_BITSHIFT_15 ( 3 )

// Registers info.

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

// Bit fields info.

// Interrupt enable.

#define MAXIM_EN_IRQ_BIT_FIFO_ALMOST_FULL ( 1 << 7 )
#define MAXIM_EN_IRQ_BIT_NEW_SAMPLE_RDY   ( 1 << 6 )
#define MAXIM_EN_IRQ_BIT_AMBIENT_OVF      ( 1 << 5 )
#define MAXIM_EN_IRQ_BIT_PROX_INT         ( 1 << 4 )
#define MAXIM_EN_IRQ_BIT_INT_TEMP_RDY     ( 1 << 1 )

// Interrupt status.

#define MAXIM_DATA_RDY_BIT_FIFO_ALMOST_FULL ( 1 << 7 )
#define MAXIM_DATA_RDY_BIT_NEW_SAMPLE_RDY   ( 1 << 6 )
#define MAXIM_DATA_RDY_BIT_AMBIENT_OVF      ( 1 << 5 )
#define MAXIM_DATA_RDY_BIT_PROX_INT         ( 1 << 4 )
#define MAXIM_DATA_RDY_BIT_INT_TEMP_RDY     ( 1 << 1 )

// FIFO pointers.

#define MAXIM_FIFO_WR_PTR_SHIFT ( 0 )
#define MAXIM_FIFO_WR_PTR_MASK  ( 0x1F << MAXIM_FIFO_WR_PTR_SHIFT )

#define MAXIM_FIFO_RD_PTR_SHIFT ( 0 )
#define MAXIM_FIFO_RD_PTR_MASK  ( 0x1F << MAXIM_FIFO_RD_PTR_SHIFT )

#define MAXIM_FIFO_OVF_CNT_PTR_SHIFT ( 0 )
#define MAXIM_FIFO_OVF_CNT_PTR_MASK  ( 0x1F << MAXIM_FIFO_OVF_CNT_PTR_SHIFT )

// FIFO configuration.

#define MAXIM_FIFO_CFG_A_FULL_SHIFT ( 0 )
#define MAXIM_FIFO_CFG_A_FULL_MASK  ( 0xF << MAXIM_FIFO_CFG_A_FULL_SHIFT )

#define MAXIM_FIFO_CFGBIT_FIFO_ROLLOVER ( 1 << 4 )

#define MAXIM_FIFO_CFG_FIFO_OVS_SHIFT ( 5 )
#define MAXIM_FIFO_CFG_FIFO_OVS_MASK  ( 0x7 << MAXIM_FIFO_CFG_FIFO_OVS_SHIFT )

// Mode configuration.

#define MAXIM_MODE_CFGBIT_SLEEP ( 1 << 7 )
#define MAXIM_MODE_CFGBIT_RST   ( 1 << 6 )

#define MAXIM_MODE_SHIFT ( 0 )
#define MAXIM_MODE_MASK  ( 0x7 << MAXIM_MODE_SHIFT )

// Sample rate in sample/sec.
#define MAXIM_CFG_SR_SHIFT ( 2 )
#define MAXIM_CFG_SR_MASK  ( 0x7 << MAXIM_CFG_SR_SHIFT )

// ADC range.
#define MAXIM_CFG_ADC_SHIFT ( 5 )
#define MAXIM_CFG_ADC_MASK  ( 0x3 << MAXIM_CFG_ADC_SHIFT )

// LED pulse amplitude.

// Pulse width is in [us] and also determines the ADC resolution.
#define MAXIM_CFG_LED_PW_SHIFT ( 0 )
#define MAXIM_CFG_LED_PW_MASK  ( 0x3 << MAXIM_CFG_LED_PW_SHIFT )

// Multi-LED mode control registers.

// Slot modes.
#define MAXIM_SLOT_1_3_SHIFT ( 0 )
#define MAXIM_SLOT_1_3_MASK  ( 0x7 << MAXIM_SLOT_1_3_SHIFT )
#define MAXIM_SLOT_2_4_SHIFT ( 4 )
#define MAXIM_SLOT_2_4_MASK  ( 0x7 << MAXIM_SLOT_2_4_SHIFT )

// Temperature data.
#define MAXIM_TEMP_EN ( 1 )

#endif