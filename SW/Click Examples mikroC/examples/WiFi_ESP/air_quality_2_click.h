/**
 * @file        air_quality_2_click.h
 * @brief       
 *
 * @defgroup    airq2 Air quality 2 click
 * @brief       Air quality 2 click Driver
 *
 *
 * @{
 *
 * ### Device Description ###
 * 
 * The iAQ-Core sensor module is used to measure VOC levels and provide CO2 
 * equivalent and TVOC equivalent predictions. The data is available via I²C 
 * bus. The sensor itself is protected by a plastic cap and a filter membrane. 
 * The sensor module can be soldered directly to a host circuit board with 
 * selective or reflow soldering via the edge connectors. The sensor is 
 * protected by a membrane, which should not be removed. 
 * 
 *
 * ### Features ###
 *
 * - Output of relative CO2 equivalents (ppm) and TVOC equivalents (ppb)
 * - Sensing range: 450 – 2000 ppm CO2 equivalents 125 – 600 ppb TVOC 
 *   equivalents
 * - I²C interface
 * - MEMS metal oxide sensor technology
 * - SMD type package
 * - Reflow capable
 * - Module with automatic baseline correction
 * - 66 mW (maximum in continuous mode)
 *
 * ### Library Description
 * 
 * The library simplifies reading measurements from iAQ CORE sensor.
 *
 * @example air_quality_2_ARM.c
 * @example air_quality_2_PIC.c
 * @example air_quality_2_AVR.c
 * @example air_quality_2_FT90x.c
 *
 ******************************************************************************/

#ifndef AIR_QUALITY_2_CLICK_H
#define AIR_QUALITY_2_CLICK_H

#include <stdint.h>

/**
 * @name                 I2C Address.
 ******************************************************************************/
///@{

#define AIR_QUAL_I2C_ADDRESS                0x5A

///@}



/**
 * @name                 Types
 ******************************************************************************/
///@{

/**
 * @brief   Enumerate status messages.
 */
typedef enum 
{
    IAQ_OK = 0x00,
    IAQ_BUSY = 0x01,
    IAQ_RUNIN = 0x10,
    IAQ_ERROR = 0x80

} iaq_status_t;    

/**
 * @brief   Structure to hold measured values.
 */
typedef struct
{
    uint16_t co2_eq; /*!< CO2 equivalent. */
    uint16_t tvoc_eq; /*!< TVOC equivalent. */

    int32_t resistance; /*!< Sensor resistance. */

} iaq_info_t;

///@}
/**
 * @name                 Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> Air quality 2 click initialization </h3>
 *
 * Initializes Air quality 2 click.
 *
 * @note
 * This function must be called first.
 *
 */
void air_quality_2_click_init( void );

/**
 * @brief <h3> Read information. </h3>
 *
 * @param[out]  *info   Structure which holds indoor air quality values.
 *
 * @retval      IAQ_OK      Ok.
 * @retval      IAQ_ERROR   Error.
 * @retval      IAQ_BUSY    Busy.
 * @retval      IAQ_RUNIN   Sensor heating.
 *
 * Reads information about the indoor air quality.
 *
 * @note
 * Call air_quality_2_click_init function before using this function.
 *
 */
iaq_status_t air_quality_2_click_info( iaq_info_t* info );

#ifdef __cplusplus
} // extern "C"
#endif
#endif // AIR_QUALITY_2_CLICK_H
///@}
/**
 * @}                                                                 End of File
 ******************************************************************************/