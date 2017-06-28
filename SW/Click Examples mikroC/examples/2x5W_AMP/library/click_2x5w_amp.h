/**
 * @file    click_2x5w_amp.h
 * @brief   Library for 2x5W AMP click.
 *
 * @defgroup    lib2x5wamp    Library for 2x5W AMP click
 * @brief This is driver for 2x5W AMP click.
 *
 * @{
 *
 * ### Device Description ###
 * On board IC TDA7491LP is a dual BTL class-D audio amplifier with single power
 * supply designed for LCD TVs and monitors.
 * 
 *
 * ### Features ###
 * -5 W + 5 W continuous output power:
 *  RL = 8 Ω, THD = 10% at VCC = 9 V
 * -5 W + 5 W continuous output power:
 *  RL = 4 Ω, THD = 10% at VCC = 6.6 V
 * -Wide range single supply operation (5 V - 14 V)
 * -High efficiency (η = 90%)
 * -Four selectable, fixed gain settings of
 *  nominally 20 dB, 26 dB, 30 dB and 32 dB
 * -Differential inputs minimize common-mode
 *  noise
 * -Filterless operation
 * -No ‘pop’ at turn-on/off
 * -Standby and mute features
 * -Short-circuit protection
 * -Thermal overload protection
 * -Externally synchronizable
 *
 * ### Library Description
 * The library has two helper function to set gain and mode.
 *
 * @example click_2x5W_AMP_ARM.c
 * @example click_2x5W_AMP_PIC.c
 * @example click_2x5W_AMP_PIC32.c
 * @example click_2x5W_AMP_AVR.c
 * @example click_2x5W_AMP_FT90x.c
 *
 ******************************************************************************/


#ifndef CLICK_2X5_AMP_H
#define CLICK_2X5_AMP_H


/**
 * @name                 Types
 ******************************************************************************/
///@{

/**
 * @enum click_2x5w_amp_mode_t
 * @brief Mode selection.
 * Use to select mode.
 */
typedef enum 
{
    CLICK_2X5W_AMP_MODE_STBY = 0x00,
    CLICK_2X5W_AMP_MODE_MUTE = 0x02,
    CLICK_2X5W_AMP_MODE_PLAY = 0x03,
} click_2x5w_amp_mode_t;

/**
 * @enum click_2x5w_amp_gain_t
 * @brief Gain setting.
 * Use to set gain.
 */
typedef enum 
{
    CLICK_2X5W_AMP_20_DB = 0x00,
    CLICK_2X5W_AMP_26_DB = 0x01,
    CLICK_2X5W_AMP_30_DB = 0x02,
    CLICK_2X5W_AMP_32_DB = 0x03
} click_2x5w_amp_gain_t;

///@}
/**
 * @name                 Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif


/**
 * @brief <h3> 2x5W AMP click initialization </h3>
 *
 *
 * The function initializes click to work in standby mode, and with nominal gain
 * of 20 dB.
 *
 */
void click_2x5W_init( void );


/**
 * @brief <h3> Gain setting. </h3>
 *
 * @param[in]   gain  Gain.
 *
 * The function sets gain.
 */
void click_2x5W_gain( click_2x5w_amp_gain_t gain );


/**
 * @brief <h3> Mode selection </h3>
 *
 * @param[in]   mode  Mode.
 *
 * The function selects mode.
 *
 */
void click_2x5W_mode( click_2x5w_amp_mode_t mode );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CLICK_2X5_AMP_H
///@}
/**
 * @}                                                                 End of File
 ******************************************************************************/