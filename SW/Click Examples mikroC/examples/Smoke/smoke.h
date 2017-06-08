
/**
  * @file                        smoke.h
  * @brief                       Smoke driver
  *
  * @defgroup click Smoke
  * @brief         Smoke driver
  *
  * @{
  *
  * This is driver for Smoke click board.
  *
  * ### Device Description ###
  *
  * Smoke click board contains MAX30105 module, a
  * High-Sensitivity Optical Sensor for Smoke Detection Applications.
  * Digital output data can be stored in a 32-deep FIFO within the IC.
  * The FIFO allows the MAX30105 to be connected to a microcontroller
  * or processor on a shared bus, where the data is not being read continuously 
  * from the MAX30105’s registers.It also contains temperature sensor for calibrating the 
  * temperature dependence of the particle-sensing subsystem, with an inherent
  * resolution of 0.0625°C
  *
  * ### Features ###
  *
  * - Supply voltage range: 2.7V to 5.5V
  * - MAX30105 operates on a single 1.8V power supply
  *    and a separate 5.0V power supply for the internal LEDs.
  * - 400kHz I2C-compatible interface
  * - 32-deep storage with FIFO policy for output data
  * - Particle sensing subsystem
  * - ADC sampling rate is 10.24MHz.The ADC output data rate 
  *    can be programmed from 50sps (samples per second) to 3200sps
  * - LED Driver: RED, GREEN and IR LEDs 
  * - Proximity Function
  *
  *
  * ### Library Description ###
  *      The library provides initialization and data collection from sensor in 
  *      different working modes, with setters and getters for all registers
  *      of IC.
  *
  *
  * @example Smoke_ARM.c
  * @example Smoke_PIC.c
  * @example Smoke_PIC32.c
  * @example Smoke_dsPIC.c
  * @example Smoke_AVR.c
  * @example Smoke_FT90x.c
  *
 /*****************************************************************************/
 /*****************************************************************************/

  #ifndef _SMOKE_H_
  #define _SMOKE_H_

  #include <stdint.h>
  #include <stdbool.h>
  #include <stddef.h>
   /*                 Preprocessors
 ******************************************************************************/
  //
  // SMOKE I2C Address (7-bit)
  //

  #define SMOKE_ADDRESS                   0x57    

  //
  // SMOKE I2C Register Addresses
  //

  // Status Registers
  #define SMOKE_INTSTAT1                  0x00
  #define SMOKE_INTSTAT2                  0x01
  #define SMOKE_INTENABLE1                0x02
  #define SMOKE_INTENABLE2                0x03

  // FIFO Registers
  #define SMOKE_FIFOWRITEPTR              0x04
  #define SMOKE_FIFOOVERFLOW              0x05
  #define SMOKE_FIFOREADPTR               0x06
  #define SMOKE_FIFODATA                  0x07
  #define SMOKE_BUFFER_LENGTH               32

  // Configuration Registers
  #define SMOKE_FIFOCONFIG                0x08
  #define SMOKE_MODECONFIG                0x09
  #define SMOKE_PARTICLECONFIG            0x0A    // Sometimes listed as "SPO2"
  #define SMOKE_LED1_PULSEAMP             0x0C
  #define SMOKE_LED2_PULSEAMP             0x0D
  #define SMOKE_LED3_PULSEAMP             0x0E
  #define SMOKE_LED_PROX_AMP              0x10
  #define SMOKE_MULTILEDCONFIG1           0x11
  #define SMOKE_MULTILEDCONFIG2           0x12
  #define SMOKE_MIN_POWER_LEVEL           0x01   // Minimum LED current (0.2 mA)
  #define SMOKE_AVG_POWER_LEVEL           0x1F   // Average LED current (6.4 mA)
  #define SMOKE_MAX_POWER_LEVEL           0xFF   // Maximum LED current (50 mA)

  // Die Temperature Registers
  #define SMOKE_DIETEMPINT                0x1F
  #define SMOKE_DIETEMPFRAC               0x20
  #define SMOKE_DIETEMPCONFIG             0x21

  // Proximity Function Registers
  #define SMOKE_PROXINTTHRESH             0x30

  // Part ID Registers
  #define SMOKE_REVISIONID                0xFE
  #define SMOKE_PARTID                    0xFF    

  //
  // SMOKE Commands
  //

  // Interrupt configuration
  #define SMOKE_INT_A_FULL_MASK          (uint8_t)~0b10000000
  #define SMOKE_INT_A_FULL_ENABLE         0x80
  #define SMOKE_INT_A_FULL_DISABLE        0x00

  #define SMOKE_INT_DATA_RDY_MASK        (uint8_t)~0b01000000
  #define SMOKE_INT_DATA_RDY_ENABLE       0x40
  #define SMOKE_INT_DATA_RDY_DISABLE      0x00

  #define SMOKE_INT_ALC_OVF_MASK         (uint8_t)~0b00100000
  #define SMOKE_INT_ALC_OVF_ENABLE        0x20
  #define SMOKE_INT_ALC_OVF_DISABLE       0x00

  #define SMOKE_INT_PROX_INT_MASK        (uint8_t)~0b00010000
  #define SMOKE_INT_PROX_INT_ENABLE       0x10
  #define SMOKE_INT_PROX_INT_DISABLE      0x00

  #define SMOKE_INT_DIE_TEMP_RDY_MASK    (uint8_t)~0b00000010
  #define SMOKE_INT_DIE_TEMP_RDY_ENABLE   0x02
  #define SMOKE_INT_DIE_TEMP_RDY_DISABLE  0x00

  // FIFO configuration commands
  #define SMOKE_SAMPLEAVG_MASK           (uint8_t)~0b11100000
  #define SMOKE_SAMPLEAVG_1               0x00
  #define SMOKE_SAMPLEAVG_2               0x20
  #define SMOKE_SAMPLEAVG_4               0x40
  #define SMOKE_SAMPLEAVG_8               0x60
  #define SMOKE_SAMPLEAVG_16              0x80
  #define SMOKE_SAMPLEAVG_32              0xA0

  #define SMOKE_ROLLOVER_MASK             0xEF
  #define SMOKE_ROLLOVER_ENABLE           0x10
  #define SMOKE_ROLLOVER_DISABLE          0x00
  #define SMOKE_A_FULL_MASK               0xF0

  // Mode configuration commands
  #define SMOKE_SHUTDOWN_MASK             0x7F
  #define SMOKE_SHUTDOWN                  0x80
  #define SMOKE_WAKEUP                    0x00

  #define SMOKE_RESET_MASK                0xBF
  #define SMOKE_RESET                     0x40

  #define SMOKE_MODE_MASK                 0xF8
  #define SMOKE_MODE_REDONLY              0x02
  #define SMOKE_MODE_REDIRONLY            0x03
  #define SMOKE_MODE_MULTILED             0x07

  // Particle sensing configuration commands
  #define SMOKE_ADCRANGE_MASK             0x9F
  #define SMOKE_ADCRANGE_2048             0x00
  #define SMOKE_ADCRANGE_4096             0x20
  #define SMOKE_ADCRANGE_8192             0x40
  #define SMOKE_ADCRANGE_16384            0x60

  #define SMOKE_SAMPLERATE_MASK           0xE3
  #define SMOKE_SAMPLERATE_50             0x00
  #define SMOKE_SAMPLERATE_100            0x04
  #define SMOKE_SAMPLERATE_200            0x08
  #define SMOKE_SAMPLERATE_400            0x0C
  #define SMOKE_SAMPLERATE_800            0x10
  #define SMOKE_SAMPLERATE_1000           0x14
  #define SMOKE_SAMPLERATE_1600           0x18
  #define SMOKE_SAMPLERATE_3200           0x1C

  #define SMOKE_PULSEWIDTH_MASK           0xFC
  #define SMOKE_PULSEWIDTH_69             0x00
  #define SMOKE_PULSEWIDTH_118            0x01
  #define SMOKE_PULSEWIDTH_215            0x02
  #define SMOKE_PULSEWIDTH_411            0x03

  // Multi-LED Mode configuration
  #define SMOKE_SLOT1_MASK                0xF8
  #define SMOKE_SLOT2_MASK                0x8F
  #define SMOKE_SLOT3_MASK                0xF8
  #define SMOKE_SLOT4_MASK                0x8F

  #define SMOKE_SLOT_NONE                 0x00
  #define SMOKE_SLOT_RED_LED              0x01
  #define SMOKE_SLOT_IR_LED               0x02
  #define SMOKE_SLOT_GREEN_LED            0x03
  #define SMOKE_SLOT_NONE_PILOT           0x04
  #define SMOKE_SLOT_RED_PILOT            0x05
  #define SMOKE_SLOT_IR_PILOT             0x06
  #define SMOKE_SLOT_GREEN_PILOT          0x07

  //
  // SMOKE Other Defines
  //

  #define SMOKE_EXPECTEDPARTID            0x15

  
  /**
  * @name                 Functions
  *****************************************************************************/
  ///@{
  #ifdef __cplusplus
  extern "C"{
  #endif
  
  /**
   * @brief Software Reset
   *
   * Reset
   *
   * @note Reseting MAX30105 Sensor via Polling 
   */
  void smoke_reset ( void );

  /**
   * @brief Initializes function pointers and resets sensor
   *
   * Initialization
   *
   * @note Making the MAX30105 Sensor Ready for Work. Always called first.
   */
  void smoke_init ( void );
  
   //
   // Configuration
   //

 /**
   * @brief Configures Registers via I2C using default setting  ( MultiLED )
   *
   * Default Register Configuration ( Use if you are new to sensor )
   *
   * @note Default MAX30105 Settings: MultiLED mode. Called after initialization.
   * Sample Average = 4
   * Mode = MultiLED
   * ADC Range = 16384 (62.5pA per LSB)
   * Sample rate = 50
   */
  void smoke_set_registers_default( void );  

  /**
   * @brief Configures Registers via I2C using any setting
   *
   * Register Configuration
   *
   * @note Configure using provided constants. Called after initialization.
   * 
   */
  void smoke_set_registers( uint16_t avg_sample,
                            uint16_t mode,
                            uint16_t adc_range,
                            uint16_t sample_rate,
                            uint16_t pulse_width,
                            uint16_t led_power_level                   
                          );  

  /**
   * @brief Putting I2C in Low Power Mode
   *
   * Shut Down
   *
   * @note During smoke_shutdown the IC will continue to respond to I2C commands
   *  but will not update with or take new readings ( such as temperature )
   */
  void smoke_shutdown( void );

  /**
   * @brief Putting I2C out of Low Power Mode
   *
   * Wake Up
   *
   * @note Enabling Reading
   *  
   */
  void smoke_wakeup( void );

  /**
   * @brief Setting desired LED Mode For Sampling
   *
   * @param[in]   modes: RED only, RED and IR or custom
   *
   * @note       
   */
  void smoke_set_LED_mode( uint8_t mode );
  
  /**
   * @brief Setting ADC Range
   *
   * @param[in]   adc_range Particle-Sensing ADC Range ( 18-Bit Resolution )
   *
   * @note       
   */
  void smoke_set_ADC_range( uint8_t adc_range );

  /**
   * @brief Setting Number of Samples in Particle Sensing Mode
   *
   * @param[in]   sample_rate  Setting number of samples per second
   *
   * @note 
   */
  void smoke_set_sample_rate( uint8_t sample_rate );

  /**
   * @brief Setting Pulse Width in ms for MultiLED mode
   *
   * @param[in]   pulse_width  Predefined constants are expected
   *
   * @note for MultiLED Slot Timing
   */
  void smoke_set_pulse_width( uint8_t pulse_width );

  /**
   * @brief Setting RED LED Pulse Amplitude
   *
   * @param[in]   value  Predefined constants are expected
   *
   * @note 
   */
  void smoke_set_pulse_amplitude_red( uint8_t value );

  /**
   * @brief Setting IR LED Pulse Amplitude
   *
   * @param[in]   value  Predefined constants are expected
   *
   * @note 
   */
  void smoke_set_pulse_amplitude_IR( uint8_t value );

  /**
   * @brief Setting GREEN LED Pulse Amplitude
   *
   * @param[in]   value  Predefined constants are expected
   *
   * @note 
   */
  void smoke_set_pulse_amplitude_green( uint8_t value );

  /**
   * @brief Setting Proximity Pulse Amplitude
   *
   * @param[in]   value  Predefined constants are expected
   *
   * @note 
   */
  void smoke_set_pulse_amplitude_proximity( uint8_t value );

  /**
   * @brief Setting Proximity Threshold
   *
   * @param[in]   thresh_MSB  Set threshold value
   *
   * @note        Proximity interrupt is triggered when threshold is reached
   */
  void smoke_set_proximity_threshold( uint8_t thresh_MSB );

  // Multi-led configuration mode

  /**
   * @brief Enabling one of four slots in MultiLED mode for the given device
   *
   * @param[in]   slot_number  2 slots per 2 control registers ( 1, 2, 3 or 4)
   *
   * @param[in]   device       Set which LED is active ( RED, GREEN and/or IR )
   *
   * @note        Enabling slot for MultiLED mode
   */
  void smoke_enable_slot( uint8_t slot_number, uint8_t device ); 
  
  
  /**
   * @brief Disabling of slots
   *
   * Multi-LED slot disabling
   *
   * @note        Disabling slot for MultiLED mode
   */
  void smoke_disable_slots( void );

  //Interrupts 

  /**
   * @brief Returns the main interrupt group
   *
   * @note
   */
  uint8_t smoke_get_INT1( void ); 
  
  /**
   * @brief Returns the temporary ready interrupt
   *
   * @note
   */
  uint8_t smoke_get_INT2( void ); 
  
  /**
   * @brief Enable individual interrupts
   *
   * @note
   */
  void smoke_enable_AFULL( void );
  
  /**
   * @brief Disable individual interrupts
   *
   * @note
   */
  void smoke_disable_AFULL( void );
  
  /**
   * @brief Enable interrupt when there is a new sample in the data FIFO.
   *
   * @note This interrupt triggers when there is a new sample in the data FIFO.
   */
  void smoke_enable_DATARDY( void );
  
  /**
   * @brief Disable interrupt when there is a new sample in the data FIFO. 
   *
   * @note
   */
  void smoke_disable_DATARDY( void );
  
  /**
   * @brief Enabling Ambient Light Cancellation Overflow
   *
   * Ambient Light Cancellation Overflow
   *
   * @note Triggers when the ambient light cancellation function has reached maximum
   */
  void smoke_enable_ALCOVF( void );
  
  /**
   * @brief Disabling Ambient Light Cancellation Overflow
   *
   * Ambient Light Cancellation Overflow
   *
   * @note 
   */
  void smoke_disable_ALCOVF( void );
  
  /**
   * @brief Enable Proximity Threshold Triggering and Particle Sensing Mode has begun
   *
   *   Proximity Threshold Triggered
   *
   * @note Triggers when the ambient light cancellation function has reached maximum
   */
  void smoke_enable_PROXINT( void );
  
  /**
   * @brief  Disabling Proximity Threshold Triggering
   *
   *  Proximity Threshold Triggered
   *
   * @note
   */
  void smoke_disable_PROXINT( void );
  
  /**
   * @brief Enabling the interrupt when internal die temperature conversion is finished
   *
   * @note 
   */
  void smoke_enable_DIETEMPRDY( void );
  
  /**
   * @brief Disabling the interrupt when internal die temperature conversion is finished
   *
   * @note The interrupt is cleared by reading either Status Register or TFRAC
   */
  void smoke_disable_DIETEMPRDY( void );

  //FIFO Configuration  

  /**
   * @brief Sample averaging
   *
   * @param[in]   samples  number of sample averaging  
   *
   * @note To reduce the amount of data throughput, adjacent samples are averaged
   */
  void smoke_set_FIFO_Average( uint8_t samples );
  
  /**
   * @brief Controls the behavior of the FIFO when the it becomes completely filled with data
   *
   * Enabling FIFO Rolls on Full
   *
   * @note FIFO Address rolls over to zero and the FIFO continues to fill with new data
   */
  void smoke_enable_FIFO_rollover( void );
  
  /**
   * @brief Controls the behavior of the FIFO when the it becomes completely filled with data
   *
   * Disabling FIFO Rolls on Full
   *
   * @note FIFO is not updated until FIFO_DATA is read or the WRITE/READ pointer positions are changed   
   */
  void smoke_disable_FIFO_rollover( void );
  
  /**
   * @brief Setting the trigger for the FIFO_A_FULL interrupt
   *
   * @param[in]   samples  Setting value within range of 0x0 and 0xF
   *
   * @note If set to 0x0F, the interrupt triggers when there are 15 empty space left 
   */
  void smoke_set_FIFO_almost_full( uint8_t samples );

  //FIFO Reading

  /**
   * @brief Reads the oldest 3B data from channel 
   *
   * Reading Data in Multi-LED mode
   *
   * @note Stores 3B for RED, IR and GREEN LED samples, respectively 
   */
  void smoke_read_data( void );

  /**
   * @brief Getting Write Pointer ( Controls the Flow of Data in FIFO )
   *
   * Write Pointer
   *
   * @note The write pointer increments every time a new sample is added to the FIFO
   */
  uint8_t smoke_get_write_pointer( void );

  /**
   * @brief Getting Read Pointer ( Controls the Flow of Data in FIFO )
   *
   * Read Pointer
   *
   * @note The read pointer is incremented every time a sample is read from the FIFO
   */
  uint8_t smoke_get_read_pointer( void );

  /**
   * @brief Clearing FIFO pointers
   *
   * Clearing FIFO
   *
   * @note Sets the read/write pointers to zero
   */
  void smoke_clear_FIFO( void ); 

  /**
   * @brief Gets the oldest value of RED LED
   *
   * @retval      Returns the oldest RED value in 4B
   */
  uint32_t smoke_get_red( void ); 

  /**
   * @brief Gets the oldest value of IR LED
   *
   * @retval      Returns the oldest IR value in 4B
   */
  uint32_t smoke_get_IR( void ); 

  /**
   * @brief Gets the oldest value of GREEN LED
   *
   * @retval      Returns the oldest GREEN value in 4B
   */
  uint32_t smoke_get_green( void ); 


  //Proximity Mode Interrupt Threshold

  /**
   * @brief Setting of Proximity Mode Interrupt Threshold 
   *
   * @param[in]   val  byte value of threshold
   *
   * @note Sets the IR ADC count that will trigger the beginning of particle-sensing mode
   */
  void smoke_set_PROXINTTHRESH( uint8_t val );

  // Die Temperature

  /**
   * @brief Reads Current IC’s internal Temperature 
   *
   * Temperature reading ( F )
   *
   * @retval      Returns float value of temperature in celsius
   */
  float smoke_read_temp( void );

  /**
   * @brief Reads Current IC’s internal Temperature 
   *
   * Temperature reading ( C )
   *
   * @retval      Returns float value of temperature in fahrenheit
   */
  float smoke_read_tempF( void );

  // Detecting ID/Revision

  /**
   * @brief Gets the revision of the sensor
   *
   * MAX10305' Revision
   *
   * @retval      Returns uint8_t value revision
   */
  uint8_t smoke_get_revisionID( void );

  /**
   * @brief Gets product's revision number
   *
   * Revision ID
   *
   * @retval      Returns revision identification ( 0x00 to 0xFF )
   */
  uint8_t smoke_read_partID( void );

  // Low-level I2C communication

  /**
   * @brief Reads one byte from register
   *
   * @param[in]   address  sensor slave address
   * @param[in]   reg  register address
   *
   * @retval      Returns register value
   */
  uint8_t smoke_read_byte( uint8_t address, uint8_t reg );

  /**
   * @brief Writes one byte to register
   *
   * @param[in]   address  slave address
   * @param[in]   reg  register address
   * @param[in]   value  value to be set
   *
   * @note
   */
  void smoke_write_byte( uint8_t address, uint8_t reg, uint8_t value );

  /**
   * @brief Function Enabler / Disabler
   *
   * @param[in]   reg  register address
   * @param[in]   mask  mask for appropriate register
   * @param[in]   thing enabling/disabling sensor's function, or selecting device 
   *
   * @note
   */
  void smoke_set_new_value( uint8_t reg, uint8_t mask, uint8_t thing );


  #ifdef __cplusplus
  } // extern "C"
  #endif
  #endif
 ///@}
 /**
  * @}                                                              End of File
   ****************************************************************************/