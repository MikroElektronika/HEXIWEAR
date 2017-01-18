/****************************************************************************
* Title                 :   IR GESTURE CLICK
* Filename              :   ir_gesture_hw.c
* Author                :   Nikola Golubovic
* Origin Date           :   15/12/2015
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials    Description
*  15/12/15         1.0            NG
*
*****************************************************************************/
/**
 *  @file ir_gesture_hw.c
 *  @brief IR GESTURE communication driver
 *  This library interfaces the Avago APDS-9960 to Arduino over I2C. The library
 *  relies on the Arduino Wire (I2C) library. to use the library, instantiate an
 *  APDS9960 object, call init(), and call the appropriate functions.
 *  @copyright MikroelEktronika
 *
 *  APDS-9960 current draw tests (default parameters):
 *  Off:                   1mA
 *  Waiting for gesture:   14mA
 *  Gesture in progress:   35mA
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "ir_gesture_hal.h"
#include "ir_gesture_hw.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
/* APDS-9960 register addresses */
#define APDS9960_ENABLE         0x80
#define APDS9960_ATIME          0x81
#define APDS9960_WTIME          0x83
#define APDS9960_AILTL          0x84
#define APDS9960_AILTH          0x85
#define APDS9960_AIHTL          0x86
#define APDS9960_AIHTH          0x87
#define APDS9960_PILT           0x89
#define APDS9960_PIHT           0x8B
#define APDS9960_PERS           0x8C
#define APDS9960_CONFIG1        0x8D
#define APDS9960_PPULSE         0x8E
#define APDS9960_CONTROL        0x8F
#define APDS9960_CONFIG2        0x90
#define APDS9960_ID             0x92
#define APDS9960_STATUS         0x93
#define APDS9960_CDATAL         0x94
#define APDS9960_CDATAH         0x95
#define APDS9960_RDATAL         0x96
#define APDS9960_RDATAH         0x97
#define APDS9960_GDATAL         0x98
#define APDS9960_GDATAH         0x99
#define APDS9960_BDATAL         0x9A
#define APDS9960_BDATAH         0x9B
#define APDS9960_PDATA          0x9C
#define APDS9960_POFFSET_UR     0x9D
#define APDS9960_POFFSET_DL     0x9E
#define APDS9960_CONFIG3        0x9F
#define APDS9960_GPENTH         0xA0
#define APDS9960_GEXTH          0xA1
#define APDS9960_GCONF1         0xA2
#define APDS9960_GCONF2         0xA3
#define APDS9960_GOFFSET_U      0xA4
#define APDS9960_GOFFSET_D      0xA5
#define APDS9960_GOFFSET_L      0xA7
#define APDS9960_GOFFSET_R      0xA9
#define APDS9960_GPULSE         0xA6
#define APDS9960_GCONF3         0xAA
#define APDS9960_GCONF4         0xAB
#define APDS9960_GFLVL          0xAE
#define APDS9960_GSTATUS        0xAF
#define APDS9960_IFORCE         0xE4
#define APDS9960_PICLEAR        0xE5
#define APDS9960_CICLEAR        0xE6
#define APDS9960_AICLEAR        0xE7
#define APDS9960_GFIFO_U        0xFC
#define APDS9960_GFIFO_D        0xFD
#define APDS9960_GFIFO_L        0xFE
#define APDS9960_GFIFO_R        0xFF

/* Bit fields */
#define APDS9960_PON            0b00000001
#define APDS9960_AEN            0b00000010
#define APDS9960_PEN            0b00000100
#define APDS9960_WEN            0b00001000
#define APSD9960_AIEN           0b00010000
#define APDS9960_PIEN           0b00100000
#define APDS9960_GEN            0b01000000
#define APDS9960_GVALID         0b00000001

/* Error code for returned values */
#define ERROR                   0xFF

/*****************************************************************************
* Module Preprocessor Macros
*****************************************************************************/
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/*****************************************************************************
* Module Typedefs
*****************************************************************************/
/* State definitions */
typedef enum
{
    NA_STATE,
    NEAR_STATE,
    FAR_STATE,
    ALL_STATE
} gesture_prox_t;

/* Container for gesture data */
typedef struct
{
    uint8_t u_data[32];
    uint8_t d_data[32];
    uint8_t l_data[32];
    uint8_t r_data[32];
    uint8_t index;
    uint8_t total_gestures;
    uint8_t in_threshold;
    uint8_t out_threshold;
    int ud_delta;
    int lr_delta;
    int ud_count;
    int lr_count;
    int near_count;
    int far_count;
    gesture_prox_t state;
    gesture_dir_t motion;
} gesture_data_t;

typedef enum
{
    /* Acceptable parameters for setMode */
    POWER = 0,
    AMBIENT_LIGHT,
    PROXIMITY,
    WAIT,
    AMBIENT_LIGHT_INT,
    PROXIMITY_INT,
    GESTURE,
    ALL
} ir_mode_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief Reads and returns the contents of the ENABLE register
 *
 * @return Contents of the ENABLE register. 0xFF if error.
 */
static uint8_t get_mode( void );

/**
 * @brief Enables or disables a feature in the APDS-9960
 *
 * @param[in] mode which feature to enable
 * @param[in] enable true or false
 */
static void set_mode( ir_mode_t mode, bool enable );

/* Gesture processing */
/**
 * @brief Processes the raw gesture data to determine swipe direction
 *
 * @return 1 if near or far state seen. 0 otherwise.
 */
static uint8_t process_gesture_data( gesture_data_t *gesture_data );

/**
 * @brief Determines swipe direction or near/far state
 *
 * @return 1 if near/far event. 0 otherwise.
 */
static uint8_t decode_gesture( gesture_data_t *gesture_data );

/******************************************************************************
* Function Definitions
*******************************************************************************/
static uint8_t get_mode()
{
    uint8_t enable_value;

    /* Read current ENABLE register */
    ir_gesture_i2c_hal_read( APDS9960_ENABLE, &enable_value, 1 );

    return enable_value;
}

static void set_mode( ir_mode_t mode, bool enable )
{
    /* Read current ENABLE register */
    uint8_t reg_val = get_mode();

    if( reg_val == ERROR )
        return;

    mode = MIN( mode, ALL );

    if( mode == ALL )
    {
        reg_val = 0x00;

        if( enable )
            reg_val = 0x7F;
    } else {
        reg_val &= ~( 1 << mode );

        if( enable )
            reg_val |= ( 1 << mode );
    }

    /* Write value back to ENABLE register */
    ir_gesture_i2c_hal_write( APDS9960_ENABLE, &reg_val, 1 );
}

static uint8_t process_gesture_data( gesture_data_t *gesture_data )
{
    uint8_t u_first = 0;
    uint8_t d_first = 0;
    uint8_t l_first = 0;
    uint8_t r_first = 0;
    uint8_t u_last = 0;
    uint8_t d_last = 0;
    uint8_t l_last = 0;
    uint8_t r_last = 0;
    int ud_ratio_first;
    int lr_ratio_first;
    int ud_ratio_last;
    int lr_ratio_last;
    int ud_delta;
    int lr_delta;
    int i;

    /* If we have less than 4 total gestures, that's not enough */
    if( gesture_data->total_gestures <= 4 )
        return -1;

    /* Check to make sure our data isn't out of bounds */
    if( ( gesture_data->total_gestures <= 32 ) && ( gesture_data->total_gestures > 0 ) )
    {
        /* Find the first value in U/D/L/R above the threshold */
        for( i = 0; i < gesture_data->total_gestures; i++ )
        {
            if( ( gesture_data->u_data[i] > GESTURE_THRESHOLD_OUT ) &&
                    ( gesture_data->d_data[i] > GESTURE_THRESHOLD_OUT ) &&
                    ( gesture_data->l_data[i] > GESTURE_THRESHOLD_OUT ) &&
                    ( gesture_data->r_data[i] > GESTURE_THRESHOLD_OUT ) )
            {

                u_first = gesture_data->u_data[i];
                d_first = gesture_data->d_data[i];
                l_first = gesture_data->l_data[i];
                r_first = gesture_data->r_data[i];
                break;
            }
        }

        /* If one of the _first values is 0, then there is no good data */
        if( ( u_first == 0 ) || ( d_first == 0 ) ||
                ( l_first == 0 ) || ( r_first == 0 ) )
            return -1;
        /* Find the last value in U/D/L/R above the threshold */
        for( i = gesture_data->total_gestures - 1; i >= 0; i-- )
        {
            if( ( gesture_data->u_data[i] > GESTURE_THRESHOLD_OUT ) &&
                    ( gesture_data->d_data[i] > GESTURE_THRESHOLD_OUT ) &&
                    ( gesture_data->l_data[i] > GESTURE_THRESHOLD_OUT ) &&
                    ( gesture_data->r_data[i] > GESTURE_THRESHOLD_OUT ) )
            {

                u_last = gesture_data->u_data[i];
                d_last = gesture_data->d_data[i];
                l_last = gesture_data->l_data[i];
                r_last = gesture_data->r_data[i];
                break;
            }
        }
    }

    /* Calculate the first vs. last ratio of up/down and left/right */
    ud_ratio_first = ( ( u_first - d_first ) * 100 ) / ( u_first + d_first );
    lr_ratio_first = ( ( l_first - r_first ) * 100 ) / ( l_first + r_first );
    ud_ratio_last = ( ( u_last - d_last ) * 100 ) / ( u_last + d_last );
    lr_ratio_last = ( ( l_last - r_last ) * 100 ) / ( l_last + r_last );

    /* Determine the difference between the first and last ratios */
    ud_delta = ud_ratio_last - ud_ratio_first;
    lr_delta = lr_ratio_last - lr_ratio_first;

    /* Accumulate the UD and LR delta values */
    gesture_data->ud_delta += ud_delta;
    gesture_data->lr_delta += lr_delta;

    /* Determine U/D gesture */
    if( gesture_data->ud_delta >= GESTURE_SENSITIVITY_1 )
        gesture_data->ud_count = 1;
    else if( gesture_data->ud_delta <= -GESTURE_SENSITIVITY_1 )
        gesture_data->ud_count = -1;
    else
        gesture_data->ud_count = 0;

    /* Determine L/R gesture */
    if( gesture_data->lr_delta >= GESTURE_SENSITIVITY_1 )
        gesture_data->lr_count = 1;
    else if( gesture_data->lr_delta <= -GESTURE_SENSITIVITY_1 )
        gesture_data->lr_count = -1;
    else
        gesture_data->lr_count = 0;

    /* Determine Near/Far gesture */
    if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 0 ) )
    {
        if( ( abs( ud_delta ) < GESTURE_SENSITIVITY_2 ) &&
                ( abs( lr_delta ) < GESTURE_SENSITIVITY_2 ) )
        {
            if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                gesture_data->near_count++;
            else if( ( ud_delta != 0 ) || ( lr_delta != 0 ) )
                gesture_data->far_count++;

            if( ( gesture_data->near_count >= 10 ) &&
                    ( gesture_data->far_count >= 2 ) )
            {
                if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                    gesture_data->state = NEAR_STATE;
                else if( ( ud_delta != 0 ) && ( lr_delta != 0 ) )
                    gesture_data->state = FAR_STATE;
                return 0;
            }
        }
    } else {
        if( ( abs( ud_delta ) < GESTURE_SENSITIVITY_2 ) &&
                ( abs( lr_delta ) < GESTURE_SENSITIVITY_2 ) )
        {
            if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
                gesture_data->near_count++;

            if( gesture_data->near_count >= 10 )
            {
                gesture_data->ud_count = 0;
                gesture_data->lr_count = 0;
                gesture_data->ud_delta = 0;
                gesture_data->lr_delta = 0;
            }
        }
    }
    return -1;
}


static uint8_t decode_gesture( gesture_data_t *gesture_data )
{
    /* Return if near or far event is detected */
    if( gesture_data->state == NEAR_STATE )
    {
        gesture_data->motion = DIR_NEAR;
        return 0;
    } else if ( gesture_data->state == FAR_STATE ) {
        gesture_data->motion = DIR_FAR;
        return 0;
    }

    /* Determine swipe direction */
    if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 0 ) )
        gesture_data->motion = DIR_UP;
    else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 0) )
        gesture_data->motion = DIR_DOWN;
    else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 1) )
        gesture_data->motion = DIR_RIGHT;
    else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == -1) )
        gesture_data->motion = DIR_LEFT;
    else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 1) )
    {
        if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
            gesture_data->motion = DIR_UP;
        else
            gesture_data->motion = DIR_RIGHT;
    }
    else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == -1) )
    {
        if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
            gesture_data->motion = DIR_DOWN;
        else
            gesture_data->motion = DIR_LEFT;
    }
    else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == -1) )
    {
        if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
            gesture_data->motion = DIR_UP;
        else
            gesture_data->motion = DIR_LEFT;
    }
    else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 1) )
    {
        if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
            gesture_data->motion = DIR_DOWN;
        else
            gesture_data->motion = DIR_RIGHT;
    }
    else
        return -1;

    return 0;
}


/********** Public **********************************************************/
int ir_gesture_init( uint8_t address )
{
    uint8_t temp;
    char buff[1];
    /* Initialize I2C */
    if( ir_gesture_i2c_init( address ) )
        return -1;

    ir_gesture_i2c_hal_read( APDS9960_ID, &temp, 1 );

    if( !( temp == APDS9960_ID_1 || temp == APDS9960_ID_2 ) )
        return -1;

    /* Set ENABLE register to 0 (disable all features) */
    set_mode( ALL, false );

    /* Set default values for ambient light and proximity registers */
    temp = DEFAULT_ATIME;
    ir_gesture_i2c_hal_write( APDS9960_ATIME, &temp, 1 );
    temp = DEFAULT_WTIME;
    ir_gesture_i2c_hal_write( APDS9960_WTIME, &temp, 1 );
    temp = DEFAULT_PROX_PPULSE;
    ir_gesture_i2c_hal_write( APDS9960_PPULSE, &temp, 1 );
    temp = DEFAULT_POFFSET_UR;
    ir_gesture_i2c_hal_write( APDS9960_POFFSET_UR, &temp, 1 );
    temp = DEFAULT_POFFSET_DL;
    ir_gesture_i2c_hal_write( APDS9960_POFFSET_DL, &temp, 1 );
    temp = DEFAULT_CONFIG1;
    ir_gesture_i2c_hal_write( APDS9960_CONFIG1, &temp, 1 );
    ir_gesture_set_led_drive( DEFAULT_LDRIVE );
    ir_gesture_set_proximity_gain( DEFAULT_PGAIN );
    ir_gesture_set_ambient_light_gain( DEFAULT_AGAIN );
    ir_gesture_set_prox_int_low_thresh( DEFAULT_PILT );
    ir_gesture_set_prox_int_high_thresh( DEFAULT_PIHT );
    ir_gesture_set_light_int_low_threshold( DEFAULT_AILT );
    ir_gesture_set_light_int_high_threshold( DEFAULT_AIHT );
    temp = DEFAULT_PERS;
    ir_gesture_i2c_hal_write( APDS9960_PERS, &temp, 1 );
    temp = DEFAULT_CONFIG2;
    ir_gesture_i2c_hal_write( APDS9960_CONFIG2, &temp, 1 );
    temp = DEFAULT_CONFIG3;
    ir_gesture_i2c_hal_write( APDS9960_CONFIG3, &temp, 1 );

    /* Set default values for gesture sense registers */
    ir_gesture_set_enter_thresh( DEFAULT_GPENTH );
    ir_gesture_set_exit_thresh( DEFAULT_GEXTH );
    temp = DEFAULT_GCONF1;
    ir_gesture_i2c_hal_write( APDS9960_GCONF1, &temp, 1 );
    ir_gesture_set_gesture_gain( DEFAULT_GGAIN );
    ir_gesture_set_gesture_led_drive( DEFAULT_GLDRIVE );
    ir_gesture_set_wait_time( DEFAULT_GWTIME );
    temp = DEFAULT_GOFFSET;
    ir_gesture_i2c_hal_write( APDS9960_GOFFSET_U, &temp, 1 );
    temp = DEFAULT_GOFFSET;
    ir_gesture_i2c_hal_write( APDS9960_GOFFSET_D, &temp, 1 );
    temp = DEFAULT_GOFFSET;
    ir_gesture_i2c_hal_write( APDS9960_GOFFSET_L, &temp, 1 );
    temp = DEFAULT_GOFFSET;
    ir_gesture_i2c_hal_write( APDS9960_GOFFSET_R, &temp, 1 );
    temp = DEFAULT_GPULSE;
    ir_gesture_i2c_hal_write( APDS9960_GPULSE, &temp, 1 );
    temp = DEFAULT_GCONF3;
    ir_gesture_i2c_hal_write( APDS9960_GCONF3, &temp, 1 );
    ir_gesture_set_gesture_int_enable( DEFAULT_GIEN );

    return 0;
}

/* Turn the APDS-9960 on and off */
void ir_gesture_enable_power()
{
    set_mode( POWER, true );
}

void ir_gesture_disable_power()
{
    set_mode( POWER, false );
}

/* Enable or disable specific sensors */
void ir_gesture_enable_light_sensor( bool interrupt )
{
    /* Set default gain, interrupts, enable power, and enable sensor */
    ir_gesture_set_ambient_light_gain( DEFAULT_AGAIN );
    
    ir_gesture_set_ambient_light_int_enable( interrupt );
    ir_gesture_enable_power();
    set_mode( AMBIENT_LIGHT, true );
}

void ir_gesture_disable_light_sensor()
{
    ir_gesture_set_ambient_light_int_enable( false );
    set_mode( AMBIENT_LIGHT, false );
}

void ir_gesture_enable_proximity_sensor( bool interrupt )
{
    /* Set default gain, LED, interrupts, enable power, and enable sensor */
    ir_gesture_set_proximity_gain( DEFAULT_PGAIN );
    ir_gesture_set_led_drive( DEFAULT_LDRIVE );

    ir_gesture_set_proximity_int_enable( interrupt );
    ir_gesture_enable_power();
    set_mode( PROXIMITY, true );
}

void ir_gesture_disable_proximity_sensor()
{
    ir_gesture_set_proximity_int_enable( false );
    set_mode( PROXIMITY, false );
}

void ir_gesture_enable_gesture_sensor( bool interrupt )
{
    uint8_t temp = 0xff;
    /* Enable gesture mode
       Set ENABLE to 0 (power off)
       Set WTIME to 0xFF
       Set AUX to LED_BOOST_300
       Enable PON, WEN, PEN, GEN in ENABLE
    */
    //reset_gesture_parameters();
    ir_gesture_i2c_hal_write( APDS9960_WTIME, &temp, 1 );
    temp = DEFAULT_GESTURE_PPULSE;
    ir_gesture_i2c_hal_write( APDS9960_PPULSE, &temp, 1 );
    ir_gesture_set_led_boost( LED_BOOST_300 );

    ir_gesture_set_gesture_int_enable( interrupt );
    
    ir_gesture_set_gesture_mode( true );
    ir_gesture_enable_power();
    set_mode( WAIT, true );
    set_mode( PROXIMITY, true );
    set_mode( GESTURE, true );
}

void ir_gesture_disable_gesture_sensor()
{
    //reset_gesture_parameters();
    ir_gesture_set_gesture_int_enable( false );
    ir_gesture_set_gesture_mode( false );
    set_mode( GESTURE, false );
}

/* LED drive strength control */
uint8_t ir_gesture_get_led_drive()
{
    uint8_t val=0;

    /* Read value from CONTROL register */
    ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );

    /* Shift and mask out LED drive bits */
    val = ( val >> 6 ) & 0x03;

    return val;
}

void ir_gesture_set_led_drive( uint8_t drive )
{
    uint8_t val;

    drive = MIN( drive, 0x03 );

    /* Read value from CONTROL register */
    ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 6 ) | ( 1 << 7 );
    drive = ( drive << 6 ) | val;

    /* Write register value back into CONTROL register */
    ir_gesture_i2c_hal_write( APDS9960_CONTROL, &drive, 1 );
}

uint8_t ir_gesture_get_gesture_led_drive()
{
    uint8_t val=0;

    /* Read value from GCONF2 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );

    /* Shift and mask out GLDRIVE bits */
    val = ( val >> 3 ) & 0x03;

    return val;
}

void ir_gesture_set_gesture_led_drive( uint8_t drive )
{
    uint8_t val = 0;

    drive = MIN( drive, 0x03 );

    /* Read value from GCONF2 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 3 ) | ( 1 << 4 );
    drive = ( drive << 3 ) | val;

    /* Write register value back into GCONF2 register */
    ir_gesture_i2c_hal_write( APDS9960_GCONF2, &drive, 1 );
}

/* Gain control */
uint8_t ir_gesture_get_ambient_light_gain()
{
    uint8_t val=0;

    /* Read value from CONTROL register */
    ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );

    /* Shift and mask out ADRIVE bits */
    val &= 0x03;

    return val;
}

void ir_gesture_set_ambient_light_gain( uint8_t drive )
{
    uint8_t val=0;

    drive = MIN( drive, 0x03 );

    /* Read value from CONTROL register */
    ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 0 ) | ( 1 << 1 );
    drive |= val;

    /* Write register value back into CONTROL register */
    ir_gesture_i2c_hal_write( APDS9960_CONTROL, &drive, 1 );
}

uint8_t ir_gesture_get_proximity_gain()
{
    uint8_t val;

    /* Read value from CONTROL register */
    ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );

    /* Shift and mask out PDRIVE bits */
    val = ( val >> 2 ) & 0x03;

    return val;
}

void ir_gesture_set_proximity_gain( uint8_t drive )
{
    uint8_t val=0;

    drive = MIN( drive, 0x03 );

    /* Read value from CONTROL register */
    ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 2 ) | ( 1 << 3 );
    drive = ( drive << 2 ) | val;

    /* Write register value back into CONTROL register */
    ir_gesture_i2c_hal_write( APDS9960_CONTROL, &drive, 1 );
}

uint8_t ir_gesture_get_gesture_gain()
{
    uint8_t val=0;

    /* Read value from GCONF2 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );

    /* Shift and mask out GGAIN bits */
    val = ( val >> 5 ) & 0x03;

    return val;
}

void ir_gesture_set_gesture_gain( uint8_t gain )
{
    uint8_t val;

    gain = MIN( gain, 0x03 );

    /* Read value from GCONF2 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 5 ) | ( 1 << 6 );
    gain = ( gain << 5 ) | val;
    /* Write register value back into GCONF2 register */
    ir_gesture_i2c_hal_write( APDS9960_GCONF2, &gain, 1 );
}

/* Get and set light interrupt thresholds */
uint16_t ir_gesture_get_light_int_low_threshold()
{
    uint8_t val_byte;
    uint16_t return_val;

    /* Read value from ambient light low threshold, high byte register */
    ir_gesture_i2c_hal_read( APDS9960_AILTH, &val_byte, 1 );

    return_val = ( uint16_t )( val_byte << 8 );

    /* Read value from ambient light low threshold, low byte register */
    ir_gesture_i2c_hal_read( APDS9960_AILTL, &val_byte, 1 );

    return ( return_val | val_byte );
}

void ir_gesture_set_light_int_low_threshold( uint16_t threshold )
{
    uint8_t val_low;
    uint8_t val_high;

    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = ( threshold & 0xFF00 ) >> 8;

    /* Write low byte */
    ir_gesture_i2c_hal_write( APDS9960_AILTL, &val_low, 1 );

    /* Write high byte */
    ir_gesture_i2c_hal_write( APDS9960_AILTH, &val_high, 1 );
}

uint16_t ir_gesture_get_light_int_high_threshold()
{
    uint8_t val_byte;
    uint16_t return_val;

    /* Read value from ambient light high threshold, high byte register */
    ir_gesture_i2c_hal_read( APDS9960_AIHTH, &val_byte, 1 );

    return_val = ( uint16_t )( val_byte << 8 );

    /* Read value from ambient light high threshold, low byte register */
    ir_gesture_i2c_hal_read( APDS9960_AIHTL, &val_byte, 1 );

    return ( return_val | val_byte );
}

void ir_gesture_set_light_int_high_threshold( uint16_t threshold )
{
    uint8_t val_low;
    uint8_t val_high;

    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = ( threshold & 0xFF00 ) >> 8;

    /* Write high byte */
    ir_gesture_i2c_hal_write( APDS9960_AIHTH, &val_high, 1 );

    /* Write low byte */
    ir_gesture_i2c_hal_write( APDS9960_AIHTL, &val_low, 1 );
}

/* Get and set proximity interrupt thresholds */
uint8_t ir_gesture_get_proximity_int_low_threshold()
{
    uint8_t threshold = 0;

    /* Read value from proximity low threshold register */
    ir_gesture_i2c_hal_read( APDS9960_PILT, &threshold, 1 );

    return threshold;
}

void ir_gesture_set_proximity_int_low_threshold( uint8_t threshold )
{
    /* Write threshold value to register */
    ir_gesture_i2c_hal_write( APDS9960_PILT, &threshold, 1 );
}

uint8_t ir_gesture_get_proximity_int_high_threshold( void )
{
    uint8_t threshold = 0;

    /* Read value from proximity low threshold register */
    ir_gesture_i2c_hal_read( APDS9960_PIHT, &threshold, 1 );

    return threshold;
}

void ir_gesture_set_prox_int_high_threshold( uint8_t threshold )
{
    /* Write threshold value to register */
    ir_gesture_i2c_hal_write( APDS9960_PIHT, &threshold, 1 );
}

/* Get and set interrupt enables */
bool ir_gesture_is_ambient_light_int_enable()
{
    uint8_t val = 0;

    /* Read value from ENABLE register */
    ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );

    /* Shift and mask out AIEN bit */
    val = ( val >> 4 ) & 0x01;

    return ( val == 1 ) ? true : false;
}

void ir_gesture_set_ambient_light_int_enable( bool enable )
{
    uint8_t val = 0;

    /* Read value from ENABLE register */
    ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 0 );

    if( enable )
        val |= ( 1 << 0 );

    /* Write register value back into ENABLE register */
    ir_gesture_i2c_hal_write( APDS9960_ENABLE, &val, 1 );
}

bool ir_gesture_is_proximity_int_enable()
{
    uint8_t val = 0;

    /* Read value from ENABLE register */
    ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );

    /* Shift and mask out PIEN bit */
    val = ( val >> 5 ) & 0x01;

    return ( val == 1 ) ? true : false;
}

void ir_gesture_set_proximity_int_enable( bool enable )
{
    uint8_t val = 0;

    /* Read value from ENABLE register */
    ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 5 );

    if( enable )
        val |= ( 1 << 5 );

    /* Write register value back into ENABLE register */
    ir_gesture_i2c_hal_write( APDS9960_ENABLE, &val, 1 );
}

bool ir_gesture_is_gesture_int_enable()
{
    uint8_t val = 0;

    /* Read value from GCONF4 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );

    /* Shift and mask out GIEN bit */
    val = ( val >> 1 ) & 0x01;

    return ( val == 1 ) ? true : false;
}

void ir_gesture_set_gesture_int_enable( bool enable )
{
    uint8_t val = 0;

    /* Read value from GCONF4 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 1 );

    if( enable )
        val |= ( 1 << 1 );

    /* Write register value back into GCONF4 register */
    ir_gesture_i2c_hal_write( APDS9960_GCONF4, &val, 1 );
}


bool ir_gesture_is_interrupted( gesture_irq_t interrupt )
{
    uint8_t status;
    
    if( interrupt != INT_AMBIENT_LIGHT && interrupt != INT_GESTURE && 
        interrupt != INT_PROXIMITY )
        return false;
    
    ir_gesture_i2c_hal_read( APDS9960_STATUS, &status, 1 );
    
    return ( status & ( 1 << interrupt ) ) ? true : false;
}

/* Clear interrupts */
void ir_gesture_clear_ambient_light_int()
{
    uint8_t throwaway;

    ir_gesture_i2c_hal_read( APDS9960_CICLEAR, &throwaway, 1 );
}

void ir_gesture_clear_proximity_int()
{
    uint8_t throwaway;

    ir_gesture_i2c_hal_read( APDS9960_PICLEAR, &throwaway, 1 );
}

void ir_gesture_clear_gesture_int() // TODO: Not correct, this is a clear all
{
    uint8_t throwaway;

    ir_gesture_i2c_hal_read( APDS9960_AICLEAR, &throwaway, 1 );
}

/* Ambient light methods */
uint16_t ir_gesture_read_ambient_light( )
{
    uint8_t temp;
    uint16_t return_val;

    /* Read value from clear channel, high byte register */
    ir_gesture_i2c_hal_read( APDS9960_CDATAH, &temp, 1 );

    return_val = ( uint16_t )( temp << 8 );

    /* Read value from clear channel, low byte register */
    ir_gesture_i2c_hal_read( APDS9960_CDATAL, &temp, 1 );

    return ( return_val | temp );
}

uint16_t ir_gesture_read_red_light( void )
{
    uint8_t temp;
    uint16_t return_val;

    /* Read value from clear channel, high byte register */
    ir_gesture_i2c_hal_read( APDS9960_RDATAH, &temp, 1 );

    return_val = ( uint16_t )( temp << 8 );

    /* Read value from clear channel, low byte register */
    ir_gesture_i2c_hal_read( APDS9960_RDATAL, &temp, 1 );

    return ( return_val |= temp );
}

uint16_t ir_gesture_read_green_light( void )
{
    uint8_t temp;
    uint16_t return_val;

    /* Read value from clear channel, high byte register */
    ir_gesture_i2c_hal_read( APDS9960_GDATAH, &temp, 1 );

    return_val = ( uint16_t )( temp << 8 );

    /* Read value from clear channel, low byte register */
    ir_gesture_i2c_hal_read( APDS9960_GDATAL, &temp, 1 );

    return ( return_val |= temp );
}

uint16_t ir_gesture_read_blue_light( void )
{
    uint8_t temp;
    uint16_t return_val;

    /* Read value from clear channel, high byte register */
    ir_gesture_i2c_hal_read( APDS9960_BDATAH, &temp, 1 );

    return_val = ( uint16_t )( temp << 8 );

    /* Read value from clear channel, low byte register */
    ir_gesture_i2c_hal_read( APDS9960_BDATAL, &temp, 1 );

    return ( return_val |= temp );
}

uint8_t ir_gesture_get_led_boost()
{
    uint8_t val;

    /* Read value from CONFIG2 register */
    ir_gesture_i2c_hal_read( APDS9960_CONFIG2, &val, 1 );

    /* Shift and mask out LED_BOOST bits */
    val = ( val >> 4 ) & 0x03;

    return val;
}

void ir_gesture_set_led_boost( uint8_t boost )
{
    uint8_t val;

    boost = MIN( boost, 0x03 );

    /* Read value from CONFIG2 register */
    ir_gesture_i2c_hal_read( APDS9960_CONFIG2, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 4 ) | ( 1 << 5 );
    boost = ( boost << 4 ) | val;

    /* Write register value back into CONFIG2 register */
    ir_gesture_i2c_hal_write( APDS9960_CONFIG2, &boost, 1 );
}

/* Proximity methods */
uint8_t ir_gesture_read_proximity( void )
{
    uint8_t val = 0;

    /* Read value from proximity data register */
    ir_gesture_i2c_hal_read( APDS9960_PDATA, &val, 1 );

    return val;
}

uint8_t ir_gesture_get_prox_int_low_thresh()
{
    uint8_t val = 0;

    /* Read value from PILT register */
    ir_gesture_i2c_hal_read( APDS9960_PILT, &val, 1 );

    return val;
}

void ir_gesture_set_prox_int_low_thresh( uint8_t threshold )
{
    ir_gesture_i2c_hal_write( APDS9960_PILT, &threshold, 1 );
}

uint8_t ir_gesture_get_prox_int_high_thresh()
{
    uint8_t val=0;

    /* Read value from PIHT register */
    ir_gesture_i2c_hal_read( APDS9960_PIHT, &val, 1 );

    return val;
}

void ir_gesture_set_prox_int_high_thresh( uint8_t threshold )
{
    ir_gesture_i2c_hal_write( APDS9960_PIHT, &threshold, 1 );
}

bool ir_gesture_is_prox_gain_comp_enable()
{
    uint8_t val=0;

    /* Read value from CONFIG3 register */
    ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );

    /* Shift and mask out PCMP bits */
    val = ( val >> 5 ) & 0x01;

    return ( val == 1 ) ? true : false;
}

void ir_gesture_set_prox_gain_comp_enable( bool enable )
{
    uint8_t val=0;

    /* Read value from CONFIG3 register */
    ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 5 );

    if( enable )
        val |= ( 1 << 5 );

    /* Write register value back into CONFIG3 register */
    ir_gesture_i2c_hal_write( APDS9960_CONFIG3, &val, 1 );
}

uint8_t ir_gesture_get_prox_photo_mask()
{
    uint8_t val = 0;

    /* Read value from CONFIG3 register */
    ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );

    /* Mask out photodiode enable mask bits */
    val &= 0x0f;

    return val;
}

void ir_gesture_set_prox_photo_mask( uint8_t mask )
{
    uint8_t val=0;

    mask = MIN( mask, 0x03 );

    /* Read value from CONFIG3 register */
    ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 0 ) | ( 1 << 1 )| ( 1 << 2 )| ( 1 << 3 );
    mask |= val;

    /* Write register value back into CONFIG3 register */
    ir_gesture_i2c_hal_write( APDS9960_CONFIG3, &mask, 1 );
}


/* Gesture methods */
bool ir_gesture_available()
{
    uint8_t val;

    /* Read value from GSTATUS register */
    ir_gesture_i2c_hal_read( APDS9960_GSTATUS, &val, 1 );
    
    /* Shift and mask out GVALID bit */
    val &= APDS9960_GVALID;

    /* Return 1/0 based on GVALID bit */
    return ( val == 1 ) ? true : false;
}

gesture_dir_t ir_gesture_read_gesture()
{
    uint8_t fifo_count = 0;
    gesture_data_t gesture_data = {0};
    uint8_t fifo_data[132] = {0};
    int i;
    
    /* Make sure that power and gesture is on and data is valid */
    if( !ir_gesture_available() || !( get_mode() & 0b01000001 ) )
        return DIR_NONE;
    
    while( 1 )
    {
        ir_gesture_hal_delay( FIFO_PAUSE_TIME );

        if( ir_gesture_available() )
        {
            /* Read the current FIFO level */
            ir_gesture_i2c_hal_read( APDS9960_GFLVL, &fifo_count, 1 );
    
            if( fifo_count > 0 )
            {
                ir_gesture_i2c_hal_read( APDS9960_GFIFO_U, fifo_data, fifo_count * 4 );
                
                /* If there's stuff in the FIFO, read it into our data block */
                for( i = 0; i < fifo_count; i += 4 )
                {
                    gesture_data.u_data[gesture_data.index] = fifo_data[i];
                    gesture_data.d_data[gesture_data.index] = fifo_data[i + 1];
                    gesture_data.l_data[gesture_data.index] = fifo_data[i + 2];
                    gesture_data.r_data[gesture_data.index] = fifo_data[i + 3];
                    gesture_data.index++;
                    gesture_data.total_gestures++;
                }
            
                if( !process_gesture_data( &gesture_data ) )
                {
                    if( !decode_gesture( &gesture_data ) )
                    {
                    
                    }
                }
            
                gesture_data.index = 0;
                gesture_data.total_gestures = 0;
            }
        } else {
            ir_gesture_hal_delay( FIFO_PAUSE_TIME );
            decode_gesture( &gesture_data );

            return gesture_data.motion;
        }
    }
}

uint8_t ir_gesture_get_gesture_mode()
{
    uint8_t val=0;

    /* Read value from GCONF4 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );

    /* Mask out GMODE bit */
    val &= 0x01;

    return val;
}

void ir_gesture_set_gesture_mode( bool mode )
{
    uint8_t val;

    /* Read value from GCONF4 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 0 );

    if( mode )
        val |= ( 1 << 0 );

    /* Write register value back into GCONF4 register */
    ir_gesture_i2c_hal_write( APDS9960_GCONF4, &val, 1 );
}

uint8_t ir_gesture_enter_thresh()
{
    uint8_t val=0;

    /* Read value from GPENTH register */
    ir_gesture_i2c_hal_read( APDS9960_GPENTH, &val, 1 );

    return val;
}

void ir_gesture_set_enter_thresh( uint8_t threshold )
{
    ir_gesture_i2c_hal_write( APDS9960_GPENTH, &threshold , 1);
}

uint8_t ir_gesture_get_exit_thresh()
{
    uint8_t val = 0;

    /* Read value from GEXTH register */
    ir_gesture_i2c_hal_read( APDS9960_GEXTH, &val, 1 );

    return val;
}

void ir_gesture_set_exit_thresh( uint8_t threshold )
{
    ir_gesture_i2c_hal_write( APDS9960_GEXTH, &threshold, 1 );
}

uint8_t ir_gesture_get_wait_time()
{
    uint8_t val=0;

    /* Read value from GCONF2 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );

    /* Mask out GWTIME bits */
    val &= 0x07;

    return val;
}

void ir_gesture_set_wait_time( uint8_t time )
{
    uint8_t val=0;

    time = MIN( time, 0x07 );

    /* Read value from GCONF2 register */
    ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );

    /* Set bits in register to given value */
    val &= ~( 1 << 0 ) | ( 1 << 1 ) | ( 1 << 2 );
    time |= val;

    /* Write register value back into GCONF2 register */
    ir_gesture_i2c_hal_write( APDS9960_GCONF2, &time, 1 );
}



/*************** END OF FUNCTIONS *******************************************/