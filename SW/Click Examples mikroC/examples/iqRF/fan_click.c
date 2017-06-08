/*******************************************************************************
* Title                 :   Hardware implementation for FAN Click
* Filename              :   fan_click.c
* Author                :   RBL
* Origin Date           :   16/11/2015
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  16/11/2015    .1               RBL      Initial Test
*
*******************************************************************************/
/**
 *  @brief This module contains the hardware implementations for the FAN Click
 *  board produced by MikroElektronika.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "fan_click.h"
#include "fan_click_hal.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define TACH_CONSTANT 3932160
#define SEC_MIN 60

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define EN_ALGO ( 1 << 7 )
#define RANGE ( 1 << 5 ) | ( 1 << 6 )
#define RANGE_BIT 5
#define EDGES ( 1 << 3 ) | ( 1 << 4 )
#define EDGES_BIT 3
#define UPDATE ( 1 << 0 ) | ( 1 << 1 ) | ( 1 << 2 )
#define UPDATE_BIT 0
#define EN_RAMP ( 1 << 6 )
#define GLITCH_EN ( 1 << 5 )
#define DER_OPT ( 1 << 3 ) | ( 1 << 4 )
#define DER_OPT_BIT 3
#define ERR_RNG ( 1 << 2 ) | ( 1 << 1 )
#define ERR_RNG_BIT 1
#define GAIND ( 1 << 5 ) | ( 1 << 4 )
#define GAIND_BIT 4
#define GAINI ( 1 << 3 ) | ( 1 << 2 )
#define GAINI_BIT 2
#define GAINP ( 1 << 1 ) | ( 1 << 0 )
#define GAINP_BIT 0

#define NOKICK ( 1 << 5 )
#define DRIVE_FAIL_CNT ( 1 << 7 ) | ( 1 << 6 )
#define DRIVE_FAIL_CNT_BIT 6
#define SPIN_LVL ( 1 << 4 ) | ( 1 << 3 ) | ( 1 << 2 )
#define SPIN_LVL_BIT 2
#define SPINUP_TIME ( 1 << 1 ) | ( 1 << 0 )
#define SPINUP_TIME_BIT 0

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t readbuffer[2];
static uint8_t _numberOfPoles;
static uint8_t _numberOfEdges;
static fan_range_t _range;
static uint8_t mul;              // Multiplier for tach calculation
static double _frequency;
static bool fsc_mode;
static bool software_lock;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void update_multiplier( void );

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void update_multiplier()
{
    switch( _range )
    {
        case RPM_MIN_500:
            mul = 1;
            break;
        case RPM_MIN_1000:
            mul = 2;
            break;
        case RPM_MIN_2000:
            mul = 4;
            break;
        case RPM_MIN_4000:
            mul = 8;
            break;
    }
}



int fan_click_init( uint8_t address )
{
    if( fan_i2c_init( address ) )
        return -1;
    else
    {
        _numberOfPoles = EDGE_2_POLE;
        _numberOfEdges = 5;
        _range = RPM_MIN_1000;
        update_multiplier();
        _frequency = 32768.00f;
        fsc_mode = false;
        software_lock = false;
        return 0;
    }
}

void fan_click_ext_clock( double freq )
{
    _frequency = freq;
}

void fan_click_config( uint8_t config )
{
    fan_i2c_hal_read( EMC2301_CONFIGURATION, 1, readbuffer );

    readbuffer[0] |= config;

    fan_i2c_hal_write( EMC2301_CONFIGURATION, 1, readbuffer );
}

fan_status_t fan_click_get_status()
{
    fan_i2c_hal_read( EMC2301_FAN_STATUS, 1, readbuffer );
    return ( fan_status_t )readbuffer[0];
}

fan_status_t fan_click_get_stall_status()
{
    fan_i2c_hal_read( EMC2301_FAN_STALL_STATUS, 1, readbuffer );
    return ( fan_status_t )readbuffer[0];
}

uint8_t fan_click_get_spin_status()
{
    fan_i2c_hal_read( EMC2301_FAN_SPIN_STATUS, 1, readbuffer );
    return readbuffer[0];
}

uint8_t fan_click_get_drive_fail()
{
    fan_i2c_hal_read( EMC2301_DRIVE_FAIL_STATUS, 1, readbuffer );
    return readbuffer[0];
}

void fan_click_interrupts( bool enable )
{
    readbuffer[0] = ( enable == true ) ? 0x01 : 0x00;
    fan_i2c_hal_write( EMC2301_FAN_INTERRUPT_ENABLE, 1, readbuffer );
}

void fan_click_polarity( bool inverted )
{
    readbuffer[0] = ( inverted == true ) ? 0x01 : 0x00;
    fan_i2c_hal_write( EMC2301_PWM_POLARITY, 1, readbuffer );

}

void fan_click_pwm_config( bool push_pull )
{
    readbuffer[0] = ( push_pull == true ) ? 0x01 : 0x00;
    fan_i2c_hal_write( EMC2301_PWM_OUTPUT_CONFIG, 1, readbuffer );
}

void fan_click_pwm_base( fan_base_freq_t freq )
{
    if( freq > FAN_FREQ_2_441HZ ) return;
    fan_i2c_hal_write( EMC2301_PWM_BASE_FREQ, 1, ( uint8_t * )&freq );
}

// Controls
void fan_click_settings( double percentage )
{
    if( percentage > 100.0f )
        percentage = 100.0f;

    if( percentage < 0.0f )
        percentage = 0.0f;

    readbuffer[0] = ( percentage / 100.0f ) * 255.0f;

    if( !fsc_mode )
        fan_i2c_hal_write( EMC2301_FAN_SETTING, 1, readbuffer );
}


double fan_click_get_settings()
{
    double drive;

    fan_i2c_hal_read( EMC2301_FAN_SETTING, 1, readbuffer );

    drive = ( ( double )readbuffer[0] / 255.0f ) * 100.0f;

    return drive;
}


void fan_click_set_PWM_divide( uint8_t divide )
{
    fan_i2c_hal_write( EMC2301_PWM_DIVIDE, 1, &divide );
}

/******************************************
 *********** FSC Configuration ************
 *****************************************/
void fan_click_config_enableFSC( bool fsc )
{
    fan_i2c_hal_read( EMC2301_FAN_CONFIG1, 1, readbuffer );

    if( fsc )
    {
        readbuffer[0] |= EN_ALGO;
        fsc_mode = true;
    }
    else
    {
        readbuffer[0] &= ~EN_ALGO;
        fsc_mode = false;
    }

    fan_i2c_hal_write( EMC2301_FAN_CONFIG1, 1, readbuffer );
}


void fan_click_config_range( fan_range_t range )
{
    if( range > RPM_MIN_4000 ) return;

    _range = range;
    update_multiplier();

    fan_i2c_hal_read( EMC2301_FAN_CONFIG1, 1, readbuffer );

    readbuffer[0] &= ~RANGE;
    readbuffer[0] |= ( uint8_t )range << RANGE_BIT;

    fan_i2c_hal_write( EMC2301_FAN_CONFIG1, 1, readbuffer );
}


void fan_click_config_edges( fan_edges_t edges )
{
    if( edges > EDGE_4_POLE ) return;

    _numberOfEdges = 3 + ( edges * 2 );
    _numberOfPoles = edges + 1;

    fan_i2c_hal_read( EMC2301_FAN_CONFIG1, 1, readbuffer );

    readbuffer[0] &= ~EDGES;
    readbuffer[0] |= ( uint8_t )edges << EDGES_BIT;

    fan_i2c_hal_write( EMC2301_FAN_CONFIG1, 1, readbuffer );
}


void fan_click_config_update( fan_update_t update )
{
    if( update > UPDATE_1600MS ) return;

    fan_i2c_hal_read( EMC2301_FAN_CONFIG1, 1, readbuffer );

    readbuffer[0] &= ~UPDATE;
    readbuffer[0] |= ( uint8_t )update << UPDATE_BIT;

    fan_i2c_hal_write( EMC2301_FAN_CONFIG1, 1, readbuffer );
}


void fan_click_config_enableRamp( bool rampControl )
{
    fan_i2c_hal_read( EMC2301_FAN_CONFIG2, 1, readbuffer );

    if( rampControl )
        readbuffer[0] |= EN_RAMP;
    else
        readbuffer[0] &= ~EN_RAMP;

    fan_i2c_hal_write( EMC2301_FAN_CONFIG2, 1, readbuffer );
}


void fan_click_config_enableGlitch( bool glitch )
{
    fan_i2c_hal_read( EMC2301_FAN_CONFIG2, 1, readbuffer );

    if( glitch )
        readbuffer[0] |= GLITCH_EN;
    else
        readbuffer[0] &= ~GLITCH_EN;

    fan_i2c_hal_write( EMC2301_FAN_CONFIG2, 1, readbuffer );
}


void fan_click_config_derivative( fan_derivative_t derivative )
{
    if( derivative > DERIVATIVE_BOTH ) return;

    fan_i2c_hal_read( EMC2301_FAN_CONFIG2, 1, readbuffer );

    readbuffer[0] &= ~DER_OPT;
    readbuffer[0] |= ( uint8_t )( derivative << DER_OPT_BIT );

    fan_i2c_hal_write( EMC2301_FAN_CONFIG2, 1, readbuffer );
}

void fan_click_config_errorRange( fan_error_t error )
{
    if( error > RPM_200 ) return;

    fan_i2c_hal_read( EMC2301_FAN_CONFIG2, 1, readbuffer );

    readbuffer[0] &= ~ERR_RNG;
    readbuffer[0] |= ( uint8_t )( error << ERR_RNG_BIT );

    fan_i2c_hal_write( EMC2301_FAN_CONFIG2, 1, readbuffer );
}

void fan_click_config_gaind( fan_gain_t gain )
{
    if( gain > FAN_GAIN8X ) return;

    fan_i2c_hal_read( EMC2301_GAIN, 1, readbuffer );

    readbuffer[0] &= ~GAIND;
    readbuffer[0] |= ( uint8_t )( gain << GAIND_BIT );

    fan_i2c_hal_write( EMC2301_GAIN, 1, readbuffer );
}

void fan_click_config_gaini( fan_gain_t gain )
{
    if( gain > FAN_GAIN8X ) return;

    fan_i2c_hal_read( EMC2301_GAIN, 1, readbuffer );

    readbuffer[0] &= ~GAINI;
    readbuffer[0] |= ( uint8_t )( gain << GAINI_BIT );

    fan_i2c_hal_write( EMC2301_GAIN, 1, readbuffer );
}

void fan_click_config_gainp( fan_gain_t gain )
{
    if( gain > FAN_GAIN8X ) return;

    fan_i2c_hal_read( EMC2301_GAIN, 1, readbuffer );

    readbuffer[0] &= ~GAINP;
    readbuffer[0] |= ( uint8_t )( gain << GAINP_BIT );

    fan_i2c_hal_write( EMC2301_GAIN, 1, readbuffer );
}

void fan_click_config_drivefail( fan_drive_fail_count_t count )
{
    if( count > DRIVE_CNT_64 ) return;

    if( software_lock ) return;

    fan_i2c_hal_read( EMC2301_FAN_SPINUP, 1, readbuffer );

    readbuffer[0] &= ~DRIVE_FAIL_CNT;
    readbuffer[0] |= ( uint8_t )( count << DRIVE_FAIL_CNT_BIT );

    fan_i2c_hal_write( EMC2301_FAN_SPINUP, 1, readbuffer );
}

void fan_click_config_enableNoKick( bool noKick )
{
    if( software_lock ) return;

    fan_i2c_hal_read( EMC2301_FAN_SPINUP, 1, readbuffer );

    if( noKick )
        readbuffer[0] |= NOKICK;
    else
        readbuffer[0] &= ~NOKICK;

    fan_i2c_hal_write( EMC2301_FAN_SPINUP, 1, readbuffer );
}

void fan_click_config_spinLevel( fan_spinup_t spin )
{
    if( spin > SPINUP_65PERCENT ) return;

    if( software_lock ) return;

    fan_i2c_hal_read( EMC2301_FAN_SPINUP, 1, readbuffer );

    readbuffer[0] &= ~SPIN_LVL;
    readbuffer[0] |= ( uint8_t )( spin << SPIN_LVL_BIT );

    fan_i2c_hal_write( EMC2301_FAN_SPINUP, 1, readbuffer );
}

void fan_click_config_spinTime( fan_spintime_t time )
{
    if( time > SPINUP_2S ) return;

    if( software_lock ) return;

    fan_i2c_hal_read( EMC2301_FAN_SPINUP, 1, readbuffer );

    readbuffer[0] &= ~SPINUP_TIME;
    readbuffer[0] |= ( uint8_t )( time << SPINUP_TIME_BIT );

    fan_i2c_hal_write( EMC2301_FAN_SPINUP, 1, readbuffer );
}

void fan_click_set_max_step( uint8_t step )
{
    if( software_lock ) return;
    if( step > 0x3F ) return;
    fan_i2c_hal_write( EMC2301_FAN_MAX_STEP, 1, &step );
}

void fan_click_set_min_drive( double min_drive )
{
    readbuffer[0] = ( min_drive / 100.00 ) * 255;

    fan_i2c_hal_write( EMC2301_FAN_MIN_DRIVE, 1, readbuffer );
}




/***************************************
 ********** Tach Functions *************
 **************************************/
void fan_click_set_valid_tach( uint16_t tach )
{
    double tmp;
    if( software_lock ) return;
    if( tach > 16000 || tach < 480 ) return;

    tmp = ( ( 1.0f / _numberOfPoles ) * ( ( _numberOfEdges - 1 ) ) / ( tach *
            ( 1.0f / mul ) ) );
    tach = tmp * ( _frequency * SEC_MIN );

    readbuffer[0] = ( tach >> 5 );
    fan_i2c_hal_write( EMC2301_FAN_VALID_TACH, 1, readbuffer );
}

uint16_t fan_click_get_valid_tach()
{
    uint16_t tach = 0;

    fan_i2c_hal_read( EMC2301_FAN_VALID_TACH, 1, readbuffer );

    tach = readbuffer[0] << 8;

    return tach;
}

uint16_t fan_click_get_driveband_fail()
{
    uint16_t fail;
    fan_i2c_hal_read( EMC2301_FAN_FAIL_LOW, 1, readbuffer );
    fan_i2c_hal_read( EMC2301_FAN_FAIL_HIGH, 1, &readbuffer[1] );

    fail = readbuffer[1] << 8;
    fail |= readbuffer[0];
    fail >>= 3;

    return fail;
}

void fan_click_set_target_tach( uint16_t tach )
{
    double tmp;
    if( tach > 16000 || tach < 480 ) return;

    tmp = ( ( 1.0f / _numberOfPoles ) * ( ( _numberOfEdges - 1 ) ) / ( tach *
            ( 1.0f / mul ) ) );
    tach = tmp * ( _frequency * SEC_MIN );

    readbuffer[0] = ( uint8_t )( tach & 0x00FF ) << 3;
    readbuffer[1] = ( uint8_t )( tach >> 5 );

    fan_i2c_hal_write( EMC2301_TACH_TARGET_LOW, 1, readbuffer );
    fan_i2c_hal_write( EMC2301_TACH_TARGET_HIGH, 1, &readbuffer[1] );
}

uint16_t fan_click_get_tach()
{
    uint16_t rpm = 0;
    double tmp;

    fan_i2c_hal_read( EMC2301_TACH_READING_HIGH, 1, readbuffer );
    fan_i2c_hal_read( EMC2301_TACH_READING_LOW, 1, &readbuffer[1] );

    rpm = readbuffer[0] << 8;
    rpm |= readbuffer[1];
    rpm >>= 3;

    tmp = ( ( 1.0f / _numberOfPoles ) * ( ( _numberOfEdges - 1 ) ) / ( rpm *
            ( 1.0f / mul ) ) );
    rpm = tmp * ( _frequency * SEC_MIN );

    return rpm;
}


/*******************************************
 ******** Informational Functions **********
 ******************************************/
void fan_click_lock_registers( bool lock )
{
    readbuffer[0] = ( lock == true ) ? 0x01 : 0x00;
    software_lock = lock;
    fan_i2c_hal_write( EMC2301_SOFTWARE_LOCK, 1, readbuffer );
}

uint8_t fan_click_productID()
{
    fan_i2c_hal_read( EMC2301_PRODUCT_ID, 1, readbuffer );
    return readbuffer[0];
}

uint8_t fan_click_manufactuerID()
{
    fan_i2c_hal_read( EMC2301_MANUFACTUERE_ID, 1, readbuffer );
    return readbuffer[0];
}

uint8_t fan_click_revision()
{
    fan_i2c_hal_read( EMC2301_REVISION, 1, readbuffer );
    return readbuffer[0];
}

/*************** END OF FUNCTIONS ***************************************************************************/