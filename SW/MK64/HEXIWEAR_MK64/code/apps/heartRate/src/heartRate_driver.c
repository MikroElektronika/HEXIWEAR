/**
 * \file heartRate_driver.c
 * \version 1.00
 * \brief this file contains heart-rate functionality
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#include "heartRate_driver.h"

#include "error.h"
#include "sensor_driver.h"
#include "gui_sensorTag.h"

#include "watch.h"
#include "fitness.h"

#include "gui_heartRate.h"

#include <math.h>
#include "arm_math.h"

#if defined( HEXIWEAR_DEBUG )
#include "GPIO.h"
#endif

/** private defines */
#define heartRate_IsPeak( array, idx ) ( ( array[ (idx) ] > array[ ( (idx)+1 ) ] ) && ( array[ ( (idx) ) ] > array[ ( (idx)-1 ) ] ) )
#define heartRate_UpdateFFT( size )    ( arm_rfft_fast_init_f32( &rfftInstance, size ) )
#define heartRate_InitFFT()            ( heartRate_UpdateFFT( MAXIM_INIT_SAMPLE_SIZE ) )

/** private variable definitions */

static uint16_t
    heartRate_currIdx = 0;

static uint16_t
    fft_currSize = MAXIM_INIT_SAMPLE_SIZE,
    fft_nextSize = MAXIM_INIT_SAMPLE_SIZE*2;

static float32_t
  heartRate_datBuf[ MAXIM_FINAL_SAMPLE_SIZE ] = { 0 };

static arm_rfft_fast_instance_f32
  rfftInstance;

static bool
	isSensorTagTurnedOff = false;

static float32_t
    *fft_input  = NULL,
    *fft_output = NULL;

static uint8_t
    oldHRVal     = 0,
    heartRateVal = 0;

/** private functions' declarations */
static heartRate_status_t heartRate_SendToKW40( uint32_t valToSend );
static void heartRate_FindHR( float32_t* sigFFT, float32_t minFreq, float32_t maxFreq, uint8_t* heartRateVal );
static void heartRate_UpdateHR();
static void heartRate_ResetVars();

/** Public API */

/**
 * register heart-rate sensor and FFT
 */
void heartRate_Init()
{
	// turn sensor tag off, if turned on
	if ( true == gui_sensorTag_IsActive() )
	{
		isSensorTagTurnedOff = true;
		gui_sensorTag_TurnOFF();
	}

	GuiDriver_RegisterMinPollDelay( 20 );
	sensor_RegisterPacketDelay( PACKET_HR, 20 );

    heartRate_Pause();
}

/**
 * unregister from HR sensor and free used memory
 */
void heartRate_Deinit()
{
  // turn sensor tag back on upon heart rate app exit
  if ( true == isSensorTagTurnedOff )
  {
    isSensorTagTurnedOff = false;
    gui_sensorTag_TurnON();
  }

  OLED_DestroyDynamicArea();

  heartRate_Pause();

  heartRate_SendToKW40( 0 );
}

/**
 * reallocate the buffers and reset the relevant variables
 */
void heartRate_Resume()
{
    /** allocate input and output data buffers */

    fft_input = (float32_t*)malloc( MAXIM_FINAL_SAMPLE_SIZE * sizeof( *fft_input ) );
    if ( NULL == fft_input )
    {
        catch( CATCH_HEALTH );
    }

    fft_output = (float32_t*)malloc( (2*MAXIM_FINAL_SAMPLE_SIZE) * sizeof( *fft_output ) );
    if ( NULL == fft_output )
    {
        catch( CATCH_HEALTH );
    }

    heartRate_ResetVars();

	sensor_SetPacketTargets( PACKET_HR, sensor_GetPacketTargets( PACKET_HR ) | PACKET_PUSH_APP_HEART_RATE, true );
}

/**
 * free used memory and unregister from HR sensor
 */
void heartRate_Pause()
{
	/** deallocate data buffers */

	if ( NULL != fft_input )
	{
		free( fft_input );
		fft_input = NULL;
	}

	if ( NULL != fft_output )
	{
		free( fft_output );
		fft_output = NULL;
	}

	sensor_SetPacketTargets( PACKET_HR, sensor_GetPacketTargets( PACKET_HR ) & ~PACKET_PUSH_APP_HEART_RATE, true );
}

/**
 * process available HR data
 * @param sampleBuf   new data buffer
 * @param numAvailSam number of available data values
 * @param param       optional parameter
 */
void heartRate_Process  (
                              void* sampleBuf,
                            uint8_t numAvailSam,
                              void* param
                        )
{
    uint8_t*
        datBuf = (uint8_t*)sampleBuf;

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
           /** place the available samples into buffer */
            for ( uint8_t i = 0; i < numAvailSam; i++ )
            {
                /** if it's time, update HR */
                if  (
                            ( 0 != heartRate_currIdx )
                        &&  ( 0 == ( heartRate_currIdx % MAXIM_NEW_SAMPLE_CHUNK ) )
                    )
                {
                    heartRate_UpdateHR();
                }

                /**
                 * if we reached the end of the buffer,
                 * shift data back to make room for new samples
                 */

                if ( MAXIM_FINAL_SAMPLE_SIZE == heartRate_currIdx )
                {
                    memcpy  (
                                      (void*)&( heartRate_datBuf[0] ),                                             // to
                                (const void*)&( heartRate_datBuf[ MAXIM_NEW_SAMPLE_CHUNK ] ),                      // from
                                ( MAXIM_FINAL_SAMPLE_SIZE - MAXIM_NEW_SAMPLE_CHUNK ) * sizeof( *heartRate_datBuf ) // how many
                            );
                    heartRate_currIdx = MAXIM_FINAL_SAMPLE_SIZE - MAXIM_NEW_SAMPLE_CHUNK;
                }

                // process the new sample
                uint32_t
                    foo =   (uint32_t)
                            (
                                (
                                    ( datBuf[ i*MAXIM_BYTES_PER_ADC_VALUE + 0 ] << 16 ) |
                                    ( datBuf[ i*MAXIM_BYTES_PER_ADC_VALUE + 1 ] << 8 )  |
                                      datBuf[ i*MAXIM_BYTES_PER_ADC_VALUE + 2 ]
                                ) & 0x0003FFFF // 18-bit data
                            );

                if ( 0 != foo )
                {
                    /**
                     * if the value is too small,
                     * reset the variables and activate
                     * sensor proximity mode again
                     */

                    if ( foo <= MAXIM_PROXY_THR )
                    {
                        MAXIM_Disable();

                        // discard the samples
                        heartRate_ResetVars();
                        heartRate_SendToKW40( 0 );
                        MAXIM_Enable();
                    }
                    else
                    {
                        heartRate_datBuf[ heartRate_currIdx ] = (float32_t)foo;
                        heartRate_currIdx += 1;
                    }
                }
            }
        }
    }
}

/** private functions */

/**
 * reset relevant variables
 */
static void heartRate_ResetVars()
{
    heartRate_currIdx = 0;
    fft_currSize      = MAXIM_INIT_SAMPLE_SIZE;
    fft_nextSize      = MAXIM_INIT_SAMPLE_SIZE*2;
    heartRate_InitFFT();

    /** alert GUI */
    uint32_t
        foo = 0xFF;
    gui_heartRate_QueueMsgPut( &foo );
}

/**
 * calculate and update current heart rate
 */
static void heartRate_UpdateHR()
{
    /** update FFT size if applicable */
    if  (
                      ( fft_nextSize <= MAXIM_FINAL_SAMPLE_SIZE )
            &&  ( heartRate_currIdx  >= fft_nextSize )
        )
    {
        fft_currSize = fft_nextSize;
        fft_nextSize *= 2;
        heartRate_UpdateFFT( fft_currSize );
    }

    /** copy temporal data into a temporary buffer, as FFT will change the input array */
    memcpy  (
                (void*)fft_input,
                (const void*)&( heartRate_datBuf[ heartRate_currIdx - fft_currSize ] ),
                fft_currSize * sizeof( *fft_input )
            );

    /** calculate FFT */
    arm_rfft_fast_f32   (
                            &rfftInstance,
                            fft_input,
                            fft_output,
                            0
                        );

    /** calculate spectral magnitude values */
    arm_cmplx_mag_f32( fft_output, fft_input, fft_currSize );

    oldHRVal = heartRateVal;

    /** use these magnitude values to find the dominant frequency peak */
    heartRate_FindHR(
                        fft_input,
                        MAXIM_HR_FREQ_MIN,
                        MAXIM_HR_FREQ_MAX,
                        &heartRateVal
                    );

    if  (
                   ( 0xFF != heartRateVal )
            && ( oldHRVal != heartRateVal )
        )
    {
        // send to GUI app
        uint32_t
            foo = heartRateVal;
        gui_heartRate_QueueMsgPut( &foo );
        // send to KW40
        heartRate_SendToKW40( heartRateVal );
    }
}

/**
 * calculate heart-rate by finding the biggest peak
 * in the spectrum
 *
 * @param sigFFT       data FFT
 * @param minFreq      min frequency border
 * @param maxFreq      max frequency border
 * @param heartRateVal calculated value returned
 */
static void heartRate_FindHR(
                                float32_t* sigFFT,
                                 float32_t minFreq,
                                 float32_t maxFreq,
                                  uint8_t* heartRateVal
                            )
{
    uint16_t
        minIdx = (uint16_t)floor( minFreq * fft_currSize / HR_SAMPLE_RATE ),
        maxIdx = (uint16_t)ceil ( maxFreq * fft_currSize / HR_SAMPLE_RATE );

    uint16_t
        currPeak;

    uint32_t
      peaks[ MAXIM_FIFO_DEPTH/2 ] = { 0 };

    /**
     * find all the peaks in the [ 45 - 180 ] bpm range,
     * then find the biggest one among them
     */

    uint32_t
      peakIdx = 0;

    for ( uint16_t i = minIdx; i <= maxIdx; i++ )
    {
        if ( 0 != heartRate_IsPeak( sigFFT, i ) )
        {
            peaks[ peakIdx ] = i;
            peakIdx += 1;
        }
    }

    // find the biggest among all the found peaks
    if ( peakIdx > 0 )
    {
        currPeak = peaks[0];
        for ( uint16_t i = 0; i < peakIdx; i++ )
        {
            if ( sigFFT [ currPeak ] < sigFFT[ peaks[i] ] )
            {
                currPeak = peaks[i];
            }
        }

        // convert to BPM
        *heartRateVal = (uint8_t)( 60 * ( ( (float32_t)currPeak * HR_SAMPLE_RATE ) / fft_currSize ) );
    }
    else
    {
        *heartRateVal = 0xFF;
    }
}

/**
 * send given data to KW40
 * @param  valToSend value to be sent
 * @return           status flag
 */
static heartRate_status_t heartRate_SendToKW40( uint32_t valToSend )
{
    hostInterface_packet_t
        packetToSend;

    linkState_t
  	  currentState = watch_CurrentLinkStateGet();

    if ( linkState_connected == currentState )
    {
		osa_status_t
			txStatus = kStatus_OSA_Success;

		packetToSend.type   = packetType_heartRate,
		packetToSend.length = sizeof(valToSend);
		memcpy( (void*)&(packetToSend.data[0]), (void*)&valToSend, sizeof(valToSend) );
		packetToSend.data[ packetToSend.length ] = gHostInterface_trailerByte;

		txStatus = HostInterface_TxQueueMsgPut( &packetToSend, true );
		if ( kStatus_OSA_Success != txStatus )
		{
			catch( CATCH_QUEUE );
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
