
/**
  * @file                        ac_current.h
  * @brief                       AC Current driver
  *
  * @defgroup click AC Current
  * @brief	 AC Current driver  
  *
  * @{
  *  
  * This is driver for AC Current click board.
  * ### Device Description ###
  *
  * AC Current click board contains MCP3201, a
  * 2.7V 12-Bit A/D Converter with SPI™ Serial Interface
  *
  * ### Features ###
  *
  * - Supply voltage range: 2.7V to 5.5V
  * - SPI serial interface
  * - Simple functions for measuring AC current values with
  *   standard power supplies as arguments
  *
  *
  * ### Library Description ###
  *      This library provides initialization and getters for calculating AC
  *      current, using SPI on-board communication
  *
  *
  * @example AC_Current_ARM.c
  * @example AC_Current_PIC.c
  * @example AC_Current_PIC32.c
  * @example AC_Current_dsPIC.c
  * @example AC_Current_AVR.c
  * @example AC_Current_FT90x.c
  *
 /*****************************************************************************/

  #ifndef _AC_CURRENT_H_
  #define _AC_CURRENT_H_
  
  #include <stdint.h>
  #include <stdbool.h>
  #include <stddef.h>

  /**
  * @name 		Functions
  *****************************************************************************/
  ///@{
  #ifdef __cplusplus
  extern "C"{
  #endif

  /**
   * @brief Wrapper for HAL Initialization
   *
   * Initialization
   *
   * @note Initializes function pointers and must be called first
   */
  void ac_current_init ( void );

  /**
   * @brief Gets current value of AC Current in mA
   *
   * @param[in]   voltage_supply  Single-phase voltage
   *
   * @retval      Returns float value of current in mA
   */
  float ac_current_get_mA( uint8_t voltage_supply );

  /**
   * @brief Gets current value of AC Current in  A
   *
   * @param[in]   voltage_supply  Single-phase voltage
   *
   * @retval      Returns float value of current in A
   */
  float ac_current_get_A( uint8_t voltage_supply );

  #ifdef __cplusplus
  } // extern "C"
  #endif
  #endif
 ///@}
 /**
  * @} 
                                                                 End of File
   ****************************************************************************/