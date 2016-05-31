/**
 * MPL3115A2 driver functions
 */

#ifndef HG_MPL_DRIVER
#define HG_MPL_DRIVER

#include "MPL_info.h"
#include "MPL_types.h"

/**
 * initialize underlying protocol and other stuff
 */
mpl_status_t MPL_Init(
                              handleMPL_t* mplHandle,
		      const settingsMPL_t* mplSettings
                    );

/**
 * shutdown the sensor
 */
mpl_status_t MPL_Deinit();

/**
 * software reset
 * the reset mechanism can be enabled in standby and active mode
 * when this bit is enabled, the reset mechanism resets all functional block registers and loads the respective internal registers
 * with default values
 * if the system was already in standby mode, the reboot process will immediately begin; else if the system was in active
 * mode, the boot mechanism will automatically transition the system from active mode to standby mode, and only then can the
 * reboot process begin
 *
 */
mpl_status_t MPL_SoftReset();

/**
  * clears then sets the OST bit which causes the sensor to immediately take another reading
  * necessary to sample faster than 1Hz
  */
mpl_status_t MPL_ToggleOneShot();

/**
 * set the device to be barometer or altimeter
 *
 * @param mode    1 - barometer,
 *                0 - altimeter
 */
mpl_status_t MPL_SetMode (
                          modeMPL_t mode
                        );

/**
 * put the sensor in stand-by mode
 * this is needed so that we can modify the major control registers
 */
mpl_status_t MPL_GotoStandby ();

/**
 * put the sensor in active mode
 */
mpl_status_t MPL_SetActive();

/**
 * set the over-sample rate
 * datasheet calls for 128, but you can set it from 1 to 128 samples
 * The higher the oversample rate, the greater the time between data samples
 */
mpl_status_t MPL_SetOversampleRate (
                                    uint8_t sampleRate
                                  );

/**
 * enables the pressure and temp measurement event flags so that we can test against them
 * this is recommended in datasheet during setup
 */
mpl_status_t MPL_EnableEventFlags();

/**
 * read sensor raw data
 */
mpl_status_t MPL_ReadRawData (
                               modeMPL_t mode,
                                int16_t* sensorData
                            );

/**
 * format raw to float
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void pres_fmtDef2Float(
                        const void* src,
                              void* dst,
                           uint32_t idx
                      );

/**
 * format raw to mE format
 * @param src original data array
 * @param dst new format data array
 * @param idx index of the sample to be formatted
 */
void pres_fmtDef2Me (
                      const void* src,
                            void* dst,
                         uint32_t idx
                    );

/**
 * format raw to byte - currently unimplemented
 */
void pres_fmtDef2Byte(
						const void* src,
							  void* dst,
						   uint32_t idx
					);

#endif
