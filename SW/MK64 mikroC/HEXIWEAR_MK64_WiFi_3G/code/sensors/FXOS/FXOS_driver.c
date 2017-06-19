// File: FXOS_driver.h

// Definitions of main functionalities in the FXOS driver module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string.h>

#include "FXOS_info.h"
#include "FXOS_types.h"
#include "FXOS_driver.h"

#include "OSA.h"

#include "HEXIWEAR_types.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
static accRangeFXOS_t selectedRange;

// sensitivity coefficientsL: [g/LSB] and [uT/LSB]
static float accMag_sensCoef[] =   {
    // acceleration
    0.000244, // range: +- 2g
    0.000488, // range: +- 4g
    0.000976, // range: +- 8g
    1e-1      // 0.1
};

// reverese sensitivity for calbiration purposes [LSB/g]
static uint32_t acc_reverseSensitivity[] = {
    4096, // range: +- 2g
    2048, // range: +- 4g
    1024  // range: +- 8g
};

static bool isTapEnabled = false;

// Buffer for I2C data.
static uint8_t buffer[2];

////////////////////////////////////////////////////////////////////////////////
// Static function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
 
// Reads a single byte from the sensor register at the given address.
static uint8_t FXOS_ReadSingle( uint8_t rdAddr )
{
    buffer[0] = rdAddr;
    I2C1_Start();
    I2C1_Write( FXOS_I2C_ADDRESS, buffer, 1, END_MODE_RESTART );
    I2C1_Read( FXOS_I2C_ADDRESS, buffer, 1, END_MODE_STOP );

    return buffer[0];
}

// Writes the given byte to the sensor register at the given address.
static void FXOS_WriteSingle( uint8_t wrAddr, uint8_t wrData )
{
    buffer[1] = wrData;
    buffer[0] = wrAddr;
    I2C1_Start();
    I2C1_Write( FXOS_I2C_ADDRESS, buffer, 2, END_MODE_STOP );
}

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the FXOS sensor.
void FXOS_Init()
{
    uint8_t tmp;

    I2C1_Init_Advanced( 400000, &_GPIO_Module_I2C1_PC10_11 );

    FXOS_GotoStandby();

    // Set up Mag OSR and Hybrid mode.
    FXOS_WriteSingle( FXOS_M_CTRL_REG1, M_RST_MASK );

    tmp = FXOS_ReadSingle( FXOS_M_CTRL_REG1 );
    tmp &= ~M_OSR_MASK;
    tmp |= fxosOSR0;
    FXOS_WriteSingle( FXOS_M_CTRL_REG1, tmp );

    tmp = FXOS_ReadSingle( FXOS_M_CTRL_REG1 );
    tmp &= ~M_HMS_MASK;
    tmp |= fxosBoth;
    FXOS_WriteSingle( FXOS_M_CTRL_REG1, tmp );

    // Enable hybrid mode auto increment.
    tmp = FXOS_ReadSingle( FXOS_M_CTRL_REG2 );
    tmp |= M_HYB_AUTOINC_MASK;
    FXOS_WriteSingle( FXOS_M_CTRL_REG2, tmp );
    
    // Set range.
    selectedRange = fxosRange4g;
    tmp = FXOS_ReadSingle( XYZ_DATA_CFG_REG );
    tmp &= ~FS_MASK;
    tmp |= fxosRange4g;
    FXOS_WriteSingle( XYZ_DATA_CFG_REG, tmp );

    // Setup sample rate.
    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp &= ~DR_MASK;
    tmp |= fxosODR0;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );

    // Apply low noise filter.
    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp |= LNOISE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );
    
    FXOS_ConfigureTapEvent();
    
    // Activate the sensor.
    FXOS_SetActive();
    
    OSA_TimeDelay( 20 );
}

// Reads raw data from the sensor. Requires a 6 element array.
void FXOS_ReadRawData( int16_t* sensorData )
{
    uint8_t tmp;
    uint8_t buf[12];

    tmp = OUT_X_MSB_REG;
    I2C1_Start();
    I2C1_Write( FXOS_I2C_ADDRESS, &tmp, 1, END_MODE_RESTART );
    I2C1_Read( FXOS_I2C_ADDRESS, buf, 12, END_MODE_STOP );

    // Get acceleration data.
    sensorData[0] = ( ( int16_t )buf[0] << 8 | buf[1] ) >> 2;
    sensorData[1] = ( ( int16_t )buf[2] << 8 | buf[3] ) >> 2;
    sensorData[2] = ( ( int16_t )buf[4] << 8 | buf[5] ) >> 2;
    
    // Get magnetometer's data.
    sensorData[3] = ( ( int16_t )buf[6] << 8 | buf[7] );
    sensorData[4] = ( ( int16_t )buf[8] << 8 | buf[9] );
    sensorData[5] = ( ( int16_t )buf[10] << 8 | buf[11] );
}

//  Accelerometer offset calibration.
void FXOS_CalibrateAcc()
{
    int16_t accValX;
    int16_t accValY;
    int16_t accValZ;
    
    uint8_t acc_xOffset;
    uint8_t acc_yOffset;
    uint8_t acc_zOffset;
    
    uint8_t tmp;
    uint8_t buf[7];
    
    // Go to standby.
    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp &= ~ACTIVE_MASK;
    tmp |= ~ACTIVE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );

    // Read only acc data.
    tmp = STATUS_00_REG; // OUT_X_MSB_REG;
    I2C1_Start();
    I2C1_Write( FXOS_I2C_ADDRESS, &tmp, 1, END_MODE_RESTART );
    I2C1_Read( FXOS_I2C_ADDRESS, buf, 7, END_MODE_STOP );

    // Get 14-bit acceleration output values for all 3 axes.
    accValX = ( ( int16_t )buf[1] << 8 | buf[2] ) >> 2;
    accValY = ( ( int16_t )buf[3] << 8 | buf[4] ) >> 2;
    accValZ = ( ( int16_t )buf[5] << 8 | buf[6] ) >> 2;

    // Compute offset correction values.
    acc_xOffset = ( accValX / 8 ) * ( -1 );
    acc_yOffset = ( accValY / 8 ) * ( -1 );
    acc_zOffset =
        ( ( accValZ - acc_reverseSensitivity[ selectedRange ] ) / 8 ) * (-1);

    // Save offset values.
    FXOS_WriteSingle( FXOS_OFF_X_REG, acc_xOffset );
    FXOS_WriteSingle( FXOS_OFF_Y_REG, acc_yOffset );
    FXOS_WriteSingle( FXOS_OFF_Z_REG, acc_zOffset );

    // Activate the module.
    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp &= ~ACTIVE_MASK;
    tmp |= ACTIVE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );
}

//  Magnetometer offset calibration.
void FXOS_CalibrateMag()
{
    int16_t magValX;
    int16_t magValY;
    int16_t magValZ;

    int16_t magValX_avg;
    int16_t magValY_avg;
    int16_t magValZ_avg;

    int16_t magValX_min;
    int16_t magValY_min;
    int16_t magValZ_min;

    int16_t magValX_max;
    int16_t magValY_max;
    int16_t magValZ_max;

    uint16_t i = 0;
    
    uint8_t tmp;
    uint8_t buf[13];
    
    // This will take ~30s.
    while ( i < 1000 )
    {
        // Wait for the sample.
        OSA_TimeDelay( 10 );
        
        tmp = STATUS_00_REG; // OUT_X_MSB_REG;
        I2C1_Start();
        I2C1_Write( FXOS_I2C_ADDRESS, &tmp, 1, END_MODE_RESTART );
        I2C1_Read( FXOS_I2C_ADDRESS, buf, 13, END_MODE_STOP );

        // Compute 16-bit X-axis magnetic output value
        magValX = ( ( int16_t )buf[7] << 8 | buf[8] );
        magValY = ( ( int16_t )buf[9] << 8 | buf[10] );
        magValZ = ( ( int16_t )buf[11] << 8 | buf[12] );

        // First sample?
        if ( i == 0 )
        {
            magValX_max = magValX;
            magValX_min = magValX;

            magValY_max = magValY;
            magValY_min = magValY;

            magValZ_max = magValZ;
            magValZ_min = magValZ;
        }

        // Check to see if current sample is the maximum or minimum X-axis value
        if ( magValX > magValX_max )  { magValX_max = magValX; }
        if ( magValX < magValX_min )  { magValX_min = magValX; }

        // Check to see if current sample is the maximum or minimum Y-axis value
        if ( magValY > magValY_max )  { magValY_max = magValY; }
        if ( magValY < magValY_min )  { magValY_min = magValY; }

        // Check to see if current sample is the maximum or minimum Z-axis value
        if ( magValZ > magValZ_max )  { magValZ_max = magValZ; }
        if ( magValZ < magValZ_min )  { magValZ_min = magValZ; }

        i++;
    }
    
    // Compute the average/
    magValX_avg = ( magValX_max + magValX_min ) / 2; // X-axis hard-iron offset
    magValY_avg = ( magValY_max + magValY_min ) / 2; // Y-axis hard-iron offset
    magValZ_avg = ( magValZ_max + magValZ_min ) / 2; // Z-axis hard-iron offset

    // Left-shift by one as magnetometer offset registers
    // are left justified 15-bit
    magValX_avg <<= 1;
    magValY_avg <<= 1;
    magValZ_avg <<= 1;

    // Go to standby.
    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp &= ~ACTIVE_MASK;
    tmp |= ~ACTIVE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );

    FXOS_WriteSingle( M_OFF_X_LSB_REG, magValX_avg & 0xFF );
    FXOS_WriteSingle( M_OFF_X_MSB_REG, ( magValX_avg >> 8 ) & 0xFF );

    FXOS_WriteSingle( M_OFF_Y_LSB_REG, magValY_avg & 0xFF );
    FXOS_WriteSingle( M_OFF_Y_MSB_REG, ( magValY_avg >> 8 ) & 0xFF );

    FXOS_WriteSingle( M_OFF_Z_LSB_REG, magValZ_avg & 0xFF );
    FXOS_WriteSingle( M_OFF_Z_MSB_REG, ( magValZ_avg >> 8 ) & 0xFF );

    // Activate the module.
    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp &= ~ACTIVE_MASK;
    tmp |= ACTIVE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );
}

// Puts the sensor into standby mode.
void FXOS_GotoStandby()
{
    uint8_t tmp;

    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp &= ~ACTIVE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );
}

// Puts the sensor into active mode.
void FXOS_SetActive()
{
    uint8_t tmp;

    tmp = FXOS_ReadSingle( FXOS_CTRL_REG1 );
    tmp |= ACTIVE_MASK;
    FXOS_WriteSingle( FXOS_CTRL_REG1, tmp );
}

// Resets the module.
void FXOS_SoftReset()
{
    FXOS_WriteSingle( FXOS_CTRL_REG2, RST_MASK );
    OSA_TimeDelay( 10 );
}

// Reads raw temperature value.
void FXOS_ReadRawTemp( uint8_t *tempVal )
{
    *tempVal = FXOS_ReadSingle( TEMP_REG );
}

// Configures the FXOS tap event.
void FXOS_ConfigureTapEvent()
{
    FXOS_WriteSingle( HP_FILTER_CUTOFF_REG, 0x00 );

    FXOS_WriteSingle( PULSE_CFG_REG, 1 << 5 );

    // Set the threshold - minimum required acceleration to cause a tap.
    // Write the value as a current sensitivity multiplier to get
    // the desired value in [g]. Current z-threshold is set at 0.25g.
    FXOS_WriteSingle( PULSE_THSZ_REG, 10 );

    // Set the time limit - the maximum time that a tap can be
    // above the threshold 2.55s time limit at 100Hz odr,
    // this is very dependent on data rate, see the app note.
    FXOS_WriteSingle( PULSE_TMLT_REG, 80 );
    
    // Set the pulse latency - the minimum required time between one pulse
    // and the next 5.1s 100Hz odr between taps min, 
    // this also depends on the data rate.
    FXOS_WriteSingle( PULSE_LTCY_REG, 40 );

    // Route the tap detect event to INT1 pin.
    FXOS_WriteSingle( FXOS_CTRL_REG5, 1 << 3 );
        
    // Enable the tap detect interrupt.
    FXOS_EnableTap();
}

// Enable tap detection.
void FXOS_EnableTap()
{
    if( isTapEnabled == false )
    {
        // Must be in standby to change registers.
        FXOS_GotoStandby();
        FXOS_WriteSingle( FXOS_CTRL_REG4, 1 << 3 );
        FXOS_SetActive();
        
        isTapEnabled = true;
    }
}

// Disable tap detection.
void FXOS_DisableTap()
{
    if( isTapEnabled == true )
    {
        isTapEnabled = false;
        
        // Must be in standby to change registers.
        FXOS_GotoStandby();

        // Clear the flag.
        FXOS_ReadSingle( PULSE_SRC_REG );
        
        // Disable the tap event.
        FXOS_WriteSingle( FXOS_CTRL_REG4, 0 );
        
        // Activate.
        FXOS_SetActive();
    }
}

// Check if tap is enabled.
bool FXOS_IsTapEnabled()
{
    return isTapEnabled;
}

// Callback for the interrupt.
void FXOS_Callback()
{
    uint8_t interrupts;
    
    interrupts = FXOS_ReadSingle( INT_SOURCE_REG );
    
    // handle the tap event, if it occurred
    if( ( interrupts & 0x08 ) != 0 )
        FXOS_TapHandler();
}

// Read the status of the tap source register.
void FXOS_TapHandler()
{
    uint8_t interrupts;
    
    interrupts = FXOS_ReadSingle( PULSE_SRC_REG );
    
    // ...
}

// Read FXOS status register.
void FXOS_ReadStatus( uint8_t* sensorStatus )
{
    *sensorStatus = FXOS_ReadSingle( STATUS_00_REG );
}

// Check if tap is enabled.
bool FXOS_CheckForTap()
{
    uint8_t regVal;

    regVal = FXOS_ReadSingle( PULSE_CFG_REG );

    if ( ( regVal & ( 1 << 5 ) ) != 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Formats raw accelerometer data to float.
float FXOS_AccFormatFloat( int16_t input )
{
    // Convert data.
    return ( float )input * accMag_sensCoef[selectedRange];
}

// Formats raw accelerometer data to int.
int16_t FXOS_AccFormatInt( int16_t input )
{
    // Convert data.
    return ( int16_t )( FXOS_AccFormatFloat( input ) * 100 );
}

// Formats raw magnetometer data to float.
float FXOS_MagFormatFloat( int16_t input )
{
    // Convert data.
    return ( float )input * accMag_sensCoef[3];
}

// Formats raw magnetometer data to int.
int16_t FXOS_MagFormatInt( int16_t input )
{
    // Convert data to [uT].
    return ( int16_t )( FXOS_MagFormatFloat( input ) * 100 );
}

// Formats raw to float.
void acc_fmtDef2Float(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = FXOS_AccFormatFloat( input[idx] );
}

// Formats raw to mE format.
void acc_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data
    output[idx] = ( mE_t )FXOS_AccFormatInt( input[idx] );
}

// Formats raw to byte - currently unimplemented.
void acc_fmtDef2Byte(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{}

void acc_fmtMe2Def(
                    const void* src,
                          void* dst
                  )
{
    // helper pointers
    mE_t* input = ( mE_t* )src;
    int16_t* output = ( int16_t* )dst;

    // convert data
    *output = ( int16_t )
        ( ( float ) * input / ( 100 * accMag_sensCoef[selectedRange] ) );
}

// Formats raw to float.
void mag_fmtDef2Float(
                       const void* src,
                             void* dst,
                          uint32_t idx
                     )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = FXOS_MagFormatFloat( input[idx] );
}

// Formats raw to mE format.
void mag_fmtDef2Me(
                    const void* src,
                          void* dst,
                       uint32_t idx
                  )
{
    // helper pointers
    int16_t* input = ( int16_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data to [uT]
    output[idx] = ( mE_t )FXOS_MagFormatInt( input[idx] );
}

// Formats raw to byte - currently unimplemented.
void mag_fmtDef2Byte(
                      const void* src,
                            void* dst,
                         uint32_t idx
                    )
{}