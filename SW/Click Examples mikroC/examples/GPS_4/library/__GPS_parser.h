/*

    __GPS_parser.h

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

------------------------------------------------------------------------------*/

/**
 * @file                                            __GPS_parser.h
 * @brief                     GPS parser library
 *
 * Global Library Prefix : **GPS**
 *
 *  @mainpage GPS Parser
 *
 *  @section Intro
 *  Parsing multiple GPS strings in an application can add
 *  acuracy and depth to the application available data.  This
 *  library is a simple parser that suports multiple strings as
 *  defined in the NMEA 0183 standards.
 *
 *  @section Usage
 *  Configuration of the parser is found in the gps_config.h.
 *  Uncomment the type of GPS you are using or define your
 *  own using the availabe sentence types as defined there.
 *
 *  As data is incoming into the interface, feed each char to
 *  the <type>GPS_put</type> function.  Then, in the application
 *  loop, call the <type>GPS_parse</type> function.  The parse
 *  function will only parse if the buffer contains a valid sentence.
 *
 ******************************************************************************/

#ifndef GPS_PARSER_H_
#define GPS_PARSER_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "__GPS_defs.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/



/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief GPS_put
 *
 * Can be placed in either polling or interrupt based
 * rx.  Place each char from the feed with this function.
 *
 * @code
 * if (UART1_Data_Ready)
 *     GPS_put (UART1_Read()) ;
 * @endcode
 *
 * @code
 * void UART3_RX_ISR() iv IVT_INT_USART3 ics ICS_AUTO
 * {
 *   if (RXNE_USART3_SR_bit)
 *   {
 *       GPS_put_char (UART3_DR) ;
 *   }
 * }
 * @endcode
 *
 * @param input - individual char from GPS feed
 */
void GPS_put (char input) ;

/**
 * @brief GPS_parse
 *
 * Checks if a valid sentence exists on the buffer.  If
 * one exists then parses into respective data.
 */
void GPS_parse();


/**
 * @brief GPS_init
 *
 * Sets all the data fields to initial value. Should be called before other
 * functions.
 */
void GPS_init();


/***************** Common ***************/
/*
 * Converts longitude or latitude from Degrees, Minutes format to
 * Degrees, Decimal degrees format, which is also commonly used
 */
double GPS_convertToDecimalDegrees  (uint8_t degrees, double minutes);

/**
 * @brief Current longitude
 *
 * @return T_GPS_location * - location with both degrees, minutes, and azmuth
 */
T_GPS_location * GPS_getLongitude () ;

/**
 * @brief Current latitude
 *
 * @return T_GPS_location * - location with both degrees, minutes, and azmuth
 */
T_GPS_location * GPS_getLatitude () ;

/**
 * @brief Current time
 *
 * @return T_GPS_time * - UTC time in hours, minutes, seconds
 * as well as month, day, and year.
 */
T_GPS_time * GPS_getTime () ;

/**
 * @brief Current fix time
 *
 * @return T_GPS_utcTime * - Most current fix time in hours, minutes, seconds
 */
T_GPS_utcTime * GPS_getFix () ;

/****************** GGA ******************/
/**
 * @brief GGA sentence with quality of fix from
 * most recent fix
 *
 * @return T_GPS_fix - Fix quality
 * @retval GPS_FIX_INVALID = 0
 * @retval GPS_FIX_GPS_FIX = 1   (SPS)
 * @retval GPS_FIX_DGPS_FIX = 2
 * @retval GPS_FIX_PPS_FIX = 3
 * @retval GPS_FIX_REAL_TIME_KINEMATIC = 4
 * @retval GPS_FIX_FLOAT_RTK = 5
 * @retval GPS_FIX_ESTIMATED = 6
 * @retval GPS_FIX_MANUAL_MODE = 7
 * @retval GPS_FIX_SIMULATION_MODE = 8
 */
T_GPS_fix GPS_getGgaFixQuality () ;

/**
 * @brief GGA sentence with number of sat fixes
 *
 * @return uint8_t
 * @retval 0 - number of supported channels
 */
uint8_t GPS_getGgaSatCount () ;

/**
 * @brief GGA sentence horizontalDilution dilution
 *
 * Geometric DOP is to state how errors in the measurement
 * will affect the final state estimation
 *
 * @return float
 */
float GPS_getGgaHorizontalDilution () ;

/**
 * @brief GGA sentence altitude dilution
 *
 * Geometric DOP is to state how errors in the measurement
 * will affect the final state estimation
 *
 * @return double
 */
double GPS_getGgaAltitude () ;

/**
 * @brief GGA sentence altitude above mean seal level
 *
 * @return double
 */
double GPS_getGgaMsl () ;

/**
 * @brief GGA sentence time since last update
 *
 * @return unint16_t
 */
uint16_t GPS_getGgaLastUpdateDGPS () ;

/**
 * @brief GGA sentence station ID of reporting station
 *
 * @return uint16_t
 */
uint16_t GPS_getGgaStationID () ;

/***************** GLL ******************/
/**
 * @brief GLL sentence state of Loran
 *
 * @return T_GPS_loran
 * @retval GPS_LORAN_UNKNOWN = 0
 * @retval GPS_LORAN_ACTIVE = 1
 * @retval GPS_LORAN_VOID = 2
 */
T_GPS_loran GPS_getGllActive () ;

/***************** GSA ******************/
/**
 * @brief GSA sentence mode of sat
 *
 * @return T_GPS_gsaMode
 * @retval GPS_GSA_UNKNOWN = 0
 * @retval GPS_GSA_AUTO_MODE = 4
 * @retval GPS_GSA_MANUAL_MODE = 5
 */
T_GPS_gsaMode GPS_getGsaMode () ;

/**
 * @brief GSA sentence fix type
 *
 * @return T_GPS_gsaMode
 * @retval GPS_GSA_UNKNOWN = 0
 * @retval GPS_GSA_NO_FIX = 1
 * @retval GPS_GSA_2D_FIX = 2
 * @retval GPS_GSA_3D_FIX = 3
 */
T_GPS_gsaMode GPS_getGsaFixType () ;

/**
 * @brief GSA sentence prns of reporting sats
 *
 * @return uint8_t - upto 12 prns
 */
uint8_t *GPS_getGsaSatPrns () ;

/**
 * @brief GSA sentence dilution of precision
 *
 * Geometric DOP is to state how errors in the measurement
 * will affect the final state estimation
 *
 * @return float
 */
float GPS_getGsaPrecisionDilution () ;

/**
 * @brief GSA sentence dilution of precision
 *
 * Geometric DOP is to state how errors in the measurement
 * will affect the final state estimation
 *
 * @return float
 */
float GPS_getGsaHorizontalDilution () ;

/**
 * @brief GSA sentence dilution of precision
 *
 * Geometric DOP is to state how errors in the measurement
 * will affect the final state estimation
 *
 * @return float
 */
float GPS_getGsaVerticalDilution () ;

/***************** GSV *****************/

/**
 * @brief GSV number of tracked sattelites
 *
 * @return uint8_t
 * @retval 0 - number of tracked sattelites
 */
uint8_t GPS_getGsvSatCount() ;

/**
 * @brief GSV number of tracked sattelites
 *
 * @return uint8_t
 * @retval 0 - number of tracked sattelites
 */
T_GPS_gsvSattelites *GPS_getGsvSats();
/***************** RMC *****************/
/**
 * @brief RMC sentence status of sat
 *
 * @return T_GPS_status
 * @retval GPS_RMC_UKNOWN = 0
 * @retval GPS_RMC_ACTIVE = 1
 * @retval GPS_RMC_VOID = 2
 * @retval GPS_RMC_AUTONOMOUS = 3
 * @retval GPS_RMC_DIFFERENTIAL = 4
 * @retval GPS_RMC_NOT_VALID = 5
 */
T_GPS_status GPS_getRmcStatus () ;

/**
 * @brief RMC sentence speed in knots
 *
 * @return double
 */
double GPS_getRmcSpeed () ;

/**
 * @brief RMC sentence track angle in degrees
 *
 * @return double
 */
double GPS_getRmcTrack () ;

/**
 * @brief RMC sentence magnetic variation
 *
 * @return double
 */
double GPS_getRmcMagneticVariation () ;

/**
 * @brief RMC sentence direction of magnetic variation
 *
 * @return T_GPS_azimuth
 * @retval GPS_AZIMUTH_UNKNOWN = 0
 * @retval GPS_AZIMUTH_NORTH = 1
 * @retval GPS_AZIMUTH_SOUTH = 2
 * @retval GPS_AZIMUTH_EAST = 3
 * @retval GPS_AZIMUTH_WEST = 4
 */
T_GPS_azimuth GPS_getRmcDirection () ;

/**
 * @brief RMC sentence mode
 *
 * @return T_GPS_status
 * @retval GPS_RMC_UKNOWN = 0
 * @retval GPS_RMC_ACTIVE = 1
 * @retval GPS_RMC_VOID = 2
 * @retval GPS_RMC_AUTONOMOUS = 3
 * @retval GPS_RMC_DIFFERENTIAL = 4
 * @retval GPS_RMC_NOT_VALID = 5
 */
T_GPS_status GPS_getRmcMode () ;

/**************** VTG *****************/
/**
 * @brief VTG sentence track
 *
 * @return double
 */
double GPS_getVtgTrack () ;

/**
 * @brief VTG sentence magnetic track
 *
 * @return double
 */
double GPS_getVtgMagneticTrack () ;

/**
 * @brief VTG sentence speed in knots
 *
 * @return double
 */
double GPS_getVtgSpeedKnots () ;

/**
 * @brief VTG sentence speed km
 *
 * @return double
 */
double GPS_getVtgSpeedKmh () ;

#ifdef DTM
/**
 * @brief DTM sentence local datum
 *
 * @return T_GPS_datumCode
 * @retval GPS_DTM_UNKNOWN = 0
 * @retval GPS_DTM_WGS84 = 1
 * @retval GPS_DTM_WGS72 = 2
 * @retval GPS_DTM_SGS85 = 3
 * @retval GPS_DTM_PE90 = 4
 * @retval GPS_DTM_USER_DEFINED = 5
 * @retval GPS_DTM_IHO = 6
 */
T_GPS_datumCode GPS_getDtmLocal () ;

/**
 * @brief DTM sentence local datum subdivision code
 *
 * @return char *
 */
char *GPS_getDtmLocalOffset () ;

/**
 * @brief DTM sentence latitude offset in minutes
 *
 * @return double
 */
double GPS_getDtmLatitudeOffset () ;

/**
 * @brief DTM sentence azmuth of latitude offset
 *
 * @return T_GPS_azimuth
 * @retval GPS_AZIMUTH_UNKNOWN = 0
 * @retval GPS_AZIMUTH_NORTH = 1
 * @retval GPS_AZIMUTH_SOUTH = 2
 * @retval GPS_AZIMUTH_EAST = 3
 * @retval GPS_AZIMUTH_WEST = 4
 */
T_GPS_azimuth GPS_getDtmLatitudeOffsetDirection () ;

/**
 * @brief DTM sentence longitude offset
 *
 * @return double
 */
double GPS_getDtmLongitudeOffset () ;

/**
 * @brief DTM sentence azmuth of longitude offset
 *
 * @return T_GPS_azimuth
 * @retval GPS_AZIMUTH_UNKNOWN = 0
 * @retval GPS_AZIMUTH_NORTH = 1
 * @retval GPS_AZIMUTH_SOUTH = 2
 * @retval GPS_AZIMUTH_EAST = 3
 * @retval GPS_AZIMUTH_WEST = 4
 */
T_GPS_azimuth GPS_getDtmLongitudeOffsetDirection () ;

/**
 * @brief DTM sentence altitude offset
 *
 * @return double
 */
double GPS_getDtmAltitudeOffset () ;

/**
 * @brief DTM sentence datum
 *
 * @return T_GPS_datumCode
 * @retval GPS_DTM_UNKNOWN = 0
 * @retval GPS_DTM_WGS84 = 1
 * @retval GPS_DTM_WGS72 = 2
 * @retval GPS_DTM_SGS85 = 3
 * @retval GPS_DTM_PE90 = 4
 * @retval GPS_DTM_USER_DEFINED = 5
 * @retval GPS_DTM_IHO = 6
 */
T_GPS_datumCode GPS_getDtmDatum () ;
#endif

#ifdef GBS
/**
 * @brief GBS sentence latitude error
 *
 * @return float
 */
float GPS_getGbsLatitudeError () ;

/**
 * @brief GBS sentence longitude
 *
 * @return float
 */
float GPS_getGbsLongitudeError () ;

/**
 * @brief GBS altitude error
 *
 * @return float
 */
float GPS_getGbsAltitudeError () ;

/**
 * @brief GBS sentence satellite id of failed satellite
 *
 * @return uint8_t
 */
uint8_t GPS_getGbsSateliteId () ;

/**
 * @brief GBS sentence probability of missed detection
 *
 * @return float
 */
float GPS_getGbsMissProbability () ;

/**
 * @brief GBS sentence Estimate on most likely failed satellite
 *
 * @return double
 */
double GPS_getGbsFailedEstimation () ;

/**
 * @brief GBS sentence standard deviation of estimate
 *
 * @return float
 */
float GPS_getGbsStandardDeviation () ;
#endif

#ifdef GPQ
/**
 * @brief GPQ sentence identifier
 *
 * @return char * - 2 chars
 */
char *GPS_getGpqMessage () ;
#endif

#ifdef GRS
/**
 * @brief GRS sentence mode
 *
 * Mode u-blox receivers will always output Mode 1
 * residuals
 *
 * @return uint8_t
 */
uint8_t GPS_getGrsMode () ;

/**
 * @brief GRS sentence range of residuals
 *
 * @return float
 */
float GPS_getGrsRange () ;
#endif

#ifdef GST
/**
 * @brief GST sentence rms value of standard
 * deviation
 *
 * @return float
 */
float GPS_getGstRms () ;

/**
 * @brief GST sentence standard deviation major axis
 *
 * @return float
 */
float GPS_getGstStandardDeviationMajor () ;

/**
 * @brief GST sentence standard deviation of minor axis
 *
 * @return float
 */
float GPS_getGstStandardDeviationMinor () ;

/**
 * @brief GST sentence orientation of semi-major axis
 *
 * @return float
 */
float GPS_getGstOrientation () ;

/**
 * @brief GST sentence standard deviation of latitude
 *
 * @return float
 */
float GPS_getGstStandardDeviationLatitude () ;

/**
 * @brief GST sentence standard deviation of longitude
 *
 * @return float
 */
float GPS_getGstStandardDeviationLongitude () ;

/**
 * @brief GST sentence standard deviation of altitude
 *
 * @return float
 */
float GPS_getGstStandardDeviationAltitude () ;
#endif

#ifdef THS
/**
 * @brief THS sentence heading of vehicle
 *
 * @return double
 */
double GPS_getThsHeading () ;

/**
 * @brief THS sentence status of vehicle mode
 *
 * @return T_GPS_vehicleStatus
 * @retval GPS_VEHICLE_UKNOWN = 0
 * @retval GPS_VEHICLE_AUTONOMOUS = 1
 * @retval GPS_VEHICLE_ESTIMATED = 2
 * @retval GPS_VEHICLE_MANUAL = 3
 * @retval GPS_VEHICLE_SIMULATOR = 4
 * @retval GPS_VEHICLE_NOT_VALID = 5
 */
T_GPS_vehicleStatus GPS_getThsStatus () ;
#endif

#ifdef TXT
// TODO
#endif

#ifdef ZDA
// TODO
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*GPS_PARSER_H_*/

/*------------------------------------------------------------------------------

  __CIC_PREFIX_Driver.h

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/