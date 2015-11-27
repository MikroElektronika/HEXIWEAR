/**
 * MAXIM-related info
 * Project HEXIWEAR, 2015
 */

#ifndef HG_MAXIM_INFO
#define HG_MAXIM_INFO

#define MAXIM_I2C_ADDRESS      ( 0x57 )
#define MAXIM_BYTES_PER_SAMPLE ( 3 )
#define MAXIM_FIFO_DEPTH       ( 32 )

/**
 * registers info
 */

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

#define MAXIM_REG_LED1_PA ( 0xC )
#define MAXIM_REG_LED2_PA ( 0xD )
#define MAXIM_REG_LED3_PA ( 0xE )

#define MAXIM_REG_PROXY_PULSE_AMPLITUDE ( 0x10 )

#define MAXIM_REG_MULTILED_MODE_CR_12 ( 0x11 )
#define MAXIM_REG_MULTILED_MODE_CR_34 ( 0x12 )

#define MAXIM_REG_DIE_TEMP_INT    ( 0x1F )
#define MAXIM_REG_DIE_TEMP_FRAC   ( 0x20 )
#define MAXIM_REG_DIE_TEMP_CONFIG ( 0x21 )

#define MAXIM_REG_PROXY_INT_THR ( 0x30 )

#define MAXIM_REG_ID_REV  ( 0xFE )
#define MAXIM_REG_ID_PART ( 0xFF )

/**
 * bit fields info
 */

/**
 * interrupt enable
 */

#define MAXIM_EN_IRQ_FIFO_ALMOST_FULL_BIT ( 1 << 7 )
#define MAXIM_EN_IRQ_NEW_SAMPLE_RDY_BIT   ( 1 << 6 )
#define MAXIM_EN_IRQ_AMBIENT_OVF_BIT      ( 1 << 5 )
#define MAXIM_EN_IRQ_PROX_INT_BIT         ( 1 << 4 )
#define MAXIM_EN_IRQ_INT_TEMP_RDY_BIT     ( 1 << 1 )

/**
 * interrupt status
 */

#define MAXIM_DATA_RDY_FIFO_ALMOST_FULL_BIT ( 1 << 7 )
#define MAXIM_DATA_RDY_NEW_SAMPLE_RDY_BIT   ( 1 << 6 )
#define MAXIM_DATA_RDY_AMBIENT_OVF_BIT      ( 1 << 5 )
#define MAXIM_DATA_RDY_PROX_INT_BIT         ( 1 << 4 )
#define MAXIM_DATA_RDY_INT_TEMP_RDY_BIT     ( 1 << 1 )

/**
 * FIFO pointers
 */

#define MAXIM_FIFO_WR_PTR_MASK  ( 0x1F )
#define MAXIM_FIFO_WR_PTR_SHIFT ( 0 )

#define MAXIM_FIFO_RD_PTR_MASK  ( 0x1F )
#define MAXIM_FIFO_RD_PTR_SHIFT ( 0 )

#define MAXIM_FIFO_OVF_CNT_PTR_MASK  ( 0x1F )
#define MAXIM_FIFO_OVF_CNT_PTR_SHIFT ( 0 )

/**
 * FIFO configuration
 */

#define MAXIM_REG_
#define MAXIM_FIFO_CFG_A_FULL_MASK  ( 0xF )
#define MAXIM_FIFO_CFG_A_FULL_SHIFT ( 0 )
#define MAXIM_FIFO_CFG_FIFO_ROLLOVER_EN_BIT ( 1 << 4 )

#define MAXIM_FIFO_CFG_FIFO_SMP_AVE_MASK  ( 0x7 )
#define MAXIM_FIFO_CFG_FIFO_SMP_AVE_SHIFT ( 5 )
#define MAXIM_FIFO_CFG_SMP_AVE_2  ( 0x0 )
#define MAXIM_FIFO_CFG_SMP_AVE_4  ( 0x1 )
#define MAXIM_FIFO_CFG_SMP_AVE_6  ( 0x2 )
#define MAXIM_FIFO_CFG_SMP_AVE_8  ( 0x3 )
#define MAXIM_FIFO_CFG_SMP_AVE_16 ( 0x4 )
#define MAXIM_FIFO_CFG_SMP_AVE_32 ( 0x5 )

/**
 * mode configuration
 */

#define MAXIM_MODE_SHDN_BIT ( 1 << 7 )
#define MAXIM_MODE_RST_BIT  ( 1 << 6 )

#define MAXIM_MODE_MASK  ( 0x7 )
#define MAXIM_MODE_SHIFT ( 0 )

/**
 * SpO2 Configuration
 */

#define MAXIM_SPO2_ADC_RANGE_MASK  ( 0x3 )
#define MAXIM_SPO2_ADC_RANGE_SHIFT ( 5 )
#define MAXIM_SPO2_ADC_RANGE_0 ( 0x0 ) //
#define MAXIM_SPO2_ADC_RANGE_1 ( 0x1 ) //
#define MAXIM_SPO2_ADC_RANGE_2 ( 0x2 ) //
#define MAXIM_SPO2_ADC_RANGE_3 ( 0x3 ) //

// sample rate in sample/sec
#define MAXIM_SPO2_SR_MASK  ( 0x7 )
#define MAXIM_SPO2_SR_SHIFT ( 2 )

/**
 * LED pulse amplitude
 */

// pulse width is in [us] and also determines the ADC resolution
#define MAXIM_SPO2_LED_PW_MASK  ( 0x3 )
#define MAXIM_SPO2_LED_PW_SHIFT ( 0 )

/**
 * Multi-LED mode control registers
 */

// slot modes
#define MAXIM_SLOT_MASK ( 0x7 )
#define MAXIM_SLOT_1_3_SHIFT ( 0 )
#define MAXIM_SLOT_2_4_SHIFT ( 4 )
#define MAXIM_SLOT_PROX_SHIFT ( 4 )

/**
 * temperature data
 */

#define MAXIM_TEMP_FRAC_MASK  ( 0xF )
#define MAXIM_TEMP_FRAC_SHIFT ( 0 )
#define MAXIM_TEMP_EN         ( 1 )

#endif
