// File: heartRate_driver.c

// Definitions of main functionalities in the heart rate module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "heartRate_driver.h"

#include "error.h"
#include "sensor_driver.h"
#include "sensorTag/gui_sensorTag.h"

#include "watch/watch.h"
#include "apps/fitness/fitness.h"

#include "apps/fitness/gui_heartRate/gui_heartRate.h"

#include <math.h>
#include "arm_rfft.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define heartRate_IsPeak( array, idx )                                         \
    ( ( array[ ( idx ) ] > array[ ( ( idx ) + 1 ) ] ) &&                       \
      ( array[ ( idx ) ] > array[ ( ( idx ) - 1 ) ] ) )
    
#define heartRate_UpdateFFT( size )                                            \
    ( arm_rfft_fast_init_f32( &rfftInstance, size ) )
    
#define heartRate_InitFFT()                                                    \
    ( heartRate_UpdateFFT( MAXIM_INIT_SAMPLE_SIZE ) )

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
    
static uint16_t heartRate_currIdx = 0;

static uint16_t fft_currSize = MAXIM_INIT_SAMPLE_SIZE;
static uint16_t fft_nextSize = MAXIM_INIT_SAMPLE_SIZE * 2;

static double heartRate_datBuf[ MAXIM_FINAL_SAMPLE_SIZE ] = { 0 };

static arm_rfft_fast_instance_f32 rfftInstance;

static bool isSensorTagTurnedOff = false;

static double *fft_input  = NULL;
static double *fft_output = NULL;

static uint8_t oldHRVal     = 0;
static uint8_t heartRateVal = 0;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Calculates floating point complex magnitude.
void complex_mag( double *src, double *dst, uint32_t num_samples )
{
    double real, imag;
    uint32_t block_count;

    // Use loop unrolling in chunks of 4.
    block_count = num_samples >> 2;

    // Do loop unrolling.
    while( block_count > 0 )
    {
        // Calculate magnitude of a single point of data.
        real = *src++;
        imag = *src++;
        *dst++ = sqrt( real * real + imag * imag );

        real = *src++;
        imag = *src++;
        *dst++ = sqrt( real * real + imag * imag );

        real = *src++;
        imag = *src++;
        *dst++ = sqrt( real * real + imag * imag );

        real = *src++;
        imag = *src++;
        *dst++ = sqrt( real * real + imag * imag );

        block_count--;
    }

    block_count = num_samples % 4;

    // Calculate remaining points.
    while( block_count > 0 )
    {
        real = *src++;
        imag = *src++;
        *dst++ = sqrt( real * real + imag * imag );

        block_count--;
    }
}

// Sends given data to KW40.
static heartRate_status_t heartRate_SendToKW40( uint32_t valToSend )
{
    hostInterface_packet_t packetToSend;

    linkState_t currentState = watch_CurrentLinkStateGet();

    if( currentState == linkState_connected )
    {
        osa_status_t txStatus = kStatus_OSA_Success;

        packetToSend.type   = packetType_heartRate,
        packetToSend.length = sizeof( valToSend );
        memcpy( ( void* )&( packetToSend._data[0] ),
            ( void* )&valToSend, sizeof( valToSend ) );
        packetToSend._data[ packetToSend.length ] = gHostInterface_trailerByte;

        txStatus = HostInterface_TxQueueMsgPut( &packetToSend, true );
        if( txStatus != kStatus_OSA_Success )
        {
            error_catch( CATCH_QUEUE );
            return HEART_RATE_STATUS_ERROR;
        }

        return HEART_RATE_STATUS_SUCCESS;
    }

    else
    {
        return HEART_RATE_STATUS_ERROR;
    }

    return HEART_RATE_STATUS_SUCCESS;
}

uint16_t minIdx_temp;
uint16_t maxIdx_temp;
// Calculates heart-rate by finding the biggest peak in the spectrum.
static void heartRate_FindHR( double* sigFFT, double minFreq,
    double maxFreq, uint8_t* heartRateVal )
{
    uint16_t i;
    uint16_t minIdx;
    uint16_t maxIdx;
    uint16_t currPeak;
    uint32_t peakIdx;
    uint32_t peaks[ MAXIM_FIFO_DEPTH * 2 ] = { 0 };

    minIdx = ( uint16_t )floor( minFreq * fft_currSize / HR_SAMPLE_RATE );
    maxIdx = ( uint16_t )ceil ( maxFreq * fft_currSize / HR_SAMPLE_RATE );
    minIdx_temp = minIdx;
    maxIdx_temp = maxIdx;

    // Find all the peaks in the [ 45 - 180 ] bpm range,
    // then find the biggest one among them.

    peakIdx = 0;

    for( i = minIdx; i <= maxIdx; i++ )
    {
        if( heartRate_IsPeak( sigFFT, i ) != 0 )
        {
            peaks[ peakIdx ] = i;
            peakIdx += 1;
        }
    }

    // Find the biggest among all the found peaks.
    if( peakIdx > 0 )
    {
        currPeak = peaks[0];
        for( i = 0; i < peakIdx; i++ )
        {
            if( sigFFT[ currPeak ] < sigFFT[ peaks[i] ] )
            {
                currPeak = peaks[i];
            }
        }

        // Convert to BPM.
        *heartRateVal = ( uint8_t )
            ( 60 * ( ( ( double )currPeak * HR_SAMPLE_RATE ) / fft_currSize ) );
    }
    else
    {
        *heartRateVal = 0xFF;
    }
}

// Calculates and updates current heart rate.
static void heartRate_UpdateHR()
{
    // update FFT size if applicable
    if( ( fft_nextSize <= MAXIM_FINAL_SAMPLE_SIZE ) &&
        ( heartRate_currIdx >= fft_nextSize ) )
    {
        fft_currSize = fft_nextSize;
        fft_nextSize *= 2;
        heartRate_UpdateFFT( fft_currSize );
    }

    // copy temporal data into a temporary buffer,
    // as FFT will change the input array 
    memcpy( ( void* )fft_input,
            ( const void* )&( heartRate_datBuf[ 
                heartRate_currIdx - fft_currSize ] ),
            fft_currSize * sizeof( *fft_input ) );

    // calculate FFT
    arm_rfft_fast_f32( &rfftInstance, fft_input, fft_output, 0 );

    // calculate spectral magnitude values
    complex_mag( fft_output, fft_input, fft_currSize );

    oldHRVal = heartRateVal;

    // use these magnitude values to find the dominant frequency peak
    heartRate_FindHR( fft_input,
        MAXIM_HR_FREQ_MIN, MAXIM_HR_FREQ_MAX, &heartRateVal );

    if( ( 0xFF != heartRateVal ) && ( oldHRVal != heartRateVal ) )
    {
        // send to GUI app
        uint32_t tmp = heartRateVal;
        gui_heartRate_QueueMsgPut( &tmp );
        // send to KW40
        heartRate_SendToKW40( heartRateVal );
    }
}

// Reset relevant variables.
static void heartRate_ResetVars()
{
    uint32_t tmp;

    heartRate_currIdx = 0;
    fft_currSize      = MAXIM_INIT_SAMPLE_SIZE;
    fft_nextSize      = MAXIM_INIT_SAMPLE_SIZE * 2;
    heartRate_InitFFT();

    // alert GUI
    tmp = 0xFF;
    gui_heartRate_QueueMsgPut( &tmp );
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Registers heart-rate sensor and FFT.
void heartRate_Init()
{
    // turn sensor tag off, if turned on
    if( gui_sensorTag_IsActive() == true )
    {
        isSensorTagTurnedOff = true;
        gui_sensorTag_TurnOFF();
    }

    GuiDriver_RegisterMinPollDelay( 20 );
    sensor_RegisterPacketDelay( PACKET_HR, 20 );

    heartRate_Pause();
}

// Unregisters from HR sensor and frees used memory.
void heartRate_Deinit()
{
    // turn sensor tag back on upon heart rate app exit
    if( isSensorTagTurnedOff == true )
    {
        isSensorTagTurnedOff = false;
        gui_sensorTag_TurnON();
    }

    OLED_DestroyDynamicArea();

    heartRate_Pause();

    heartRate_SendToKW40( 0 );
}

// Reallocates the buffers and resets the relevant variables.
void heartRate_Resume()
{
    // allocate input and output data buffers

    fft_input = ( double* )
        malloc( MAXIM_FINAL_SAMPLE_SIZE * sizeof( double ) );
    if( fft_input == NULL )
    {
        error_catch( CATCH_HEALTH );
    }

    fft_output = ( double* )
        malloc( ( 2 * MAXIM_FINAL_SAMPLE_SIZE ) * sizeof( double ) );
    if ( fft_output == NULL )
    {
        error_catch( CATCH_HEALTH );
    }

    heartRate_ResetVars();

    sensor_SetPacketTargets( PACKET_HR,
        sensor_GetPacketTargets( PACKET_HR ) | PACKET_PUSH_APP_HEART_RATE,
        true );
}

/// Frees used memory and unregisters from HR sensor.
void heartRate_Pause()
{
    // deallocate data buffers

    if( fft_input != NULL )
    {
        free( fft_input );
        fft_input = NULL;
    }

    if( fft_output != NULL )
    {
        free( fft_output );
        fft_output = NULL;
    }

    sensor_SetPacketTargets( PACKET_HR,
        sensor_GetPacketTargets( PACKET_HR ) & ~PACKET_PUSH_APP_HEART_RATE,
        true );
}

// Processes available HR data.
void heartRate_Process(
    void* sampleBuf, uint8_t numAvailSam, void* param )
{
    uint8_t i;
    uint32_t tmp;
    uint8_t* datBuf = ( uint8_t* )sampleBuf;

    switch( numAvailSam )
    {
        // no new samples, do nothing
        case 0:
        {
            break;
        }

        // overflow
        case 0xFF:
        {
            heartRate_ResetVars();
            break;
        }

        // analyze data
        default:
        {
            // place the available samples into buffer
            for( i = 0; i < numAvailSam; i++ )
            {
                // if it's time, update HR
                if( ( heartRate_currIdx != 0 ) &&
                    ( ( heartRate_currIdx % MAXIM_NEW_SAMPLE_CHUNK ) == 0 ) )
                {
                    heartRate_UpdateHR();
                }

                // if we reached the end of the buffer,
                // shift data back to make room for new samples

                if( heartRate_currIdx == MAXIM_FINAL_SAMPLE_SIZE )
                {
                    memcpy(
                        // to
                        ( void* )&( heartRate_datBuf[0] ),
                        // from
                        ( const void* )
                            &( heartRate_datBuf[ MAXIM_NEW_SAMPLE_CHUNK ] ),
                        // how many
                        ( MAXIM_FINAL_SAMPLE_SIZE - MAXIM_NEW_SAMPLE_CHUNK ) *
                            sizeof( *heartRate_datBuf )
                    );
                    heartRate_currIdx =
                        MAXIM_FINAL_SAMPLE_SIZE - MAXIM_NEW_SAMPLE_CHUNK;
                }

                // process the new sample
                tmp =
                    ( ( ( uint32_t )
                        datBuf[ i * MAXIM_BYTES_PER_ADC_VALUE + 0 ] << 16 ) |
                      ( ( uint32_t )
                        datBuf[ i * MAXIM_BYTES_PER_ADC_VALUE + 1 ] << 8 )  |
                        ( uint32_t )
                        datBuf[ i * MAXIM_BYTES_PER_ADC_VALUE + 2 ]
                      ) & 0x0003FFFF; // 18-bit data

                if( tmp != 0 )
                {
                    // if the value is too small,
                    // reset the variables and activate
                    // sensor proximity mode again

                    if( tmp <= MAXIM_PROXY_THR )
                    {
                        MAXIM_Disable();

                        // discard the samples
                        heartRate_ResetVars();
                        heartRate_SendToKW40( 0 );
                        MAXIM_Enable();
                    }
                    else
                    {
                        heartRate_datBuf[ heartRate_currIdx ] =
                            ( double )tmp;
                        heartRate_currIdx += 1;
                    }
                }
            }
        }
    }
}