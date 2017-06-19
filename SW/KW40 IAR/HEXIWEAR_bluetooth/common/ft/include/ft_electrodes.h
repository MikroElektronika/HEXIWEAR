/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
 */
#ifndef FT_ELECTRODES_H
#define FT_ELECTRODES_H


/**
 * \defgroup electrodes Electrodes
 * \ingroup ftapi
 *  
 * Electrodes are data objects that are used by data-acquisition algorithms to store
 * the per-electrode data, as well as the resulting signal and touch / timestamp information.
 *
 * Each Electrode provides at minimum
 * the processed and normalized signal value, the baseline value, and touch / timestamp
 * buffer containing the time of last few touch and release events. All such common
 * information are contained in the ft_electrode structure type. Also, the electrode 
 * contains information about the key detector used to detect touches for this physical 
 * electrode (this is a mandatory field in the electrode definition). This has the advantage 
 * that each electrode has its own setting of key detector, independent on the module used. 
 * It contains information about hardware pin, immediate touch status, and time 
 * stamps of the last few touch or release events.
 *
 * \{
 */
#include "ft_types.h"
#include "ft_filters.h"
#include "ft_keydetectors.h"

   
#ifndef FT_ELECTRODE_STATUS_HISTORY_COUNT
  /** Definition of the electrode history status depth. Default setting is 4.
   */
  #define FT_ELECTRODE_STATUS_HISTORY_COUNT  4
#else
  #if FT_ELECTRODE_STATUS_HISTORY_COUNT < 4
    #error The depth of electrode history buffer (FT_ELECTRODE_STATUS_HISTORY_COUNT) can be set less than 4.
  #endif
#endif

/* forward declarations */
struct ft_filter;
union ft_keydetector_params;

/** Electrode states. */
enum ft_electrode_state {
    FT_ELECTRODE_STATE_INIT    =  0, /**< Initial state; Not enough data for the touch-detection algorithm yet. */
    FT_ELECTRODE_STATE_RELEASE =  1, /**< Release state; A signal is near to the baseline. */
    FT_ELECTRODE_STATE_TOUCH   =  2, /**< Touch state; the selected algorithm has decided that a finger is present. */
};

/**
 *  Electrode status structure holding one entry in the touch-timestamp buffer.
 *  An array of this structure type is a part of each Electrode, and contains last few
 *  touch or release events detected on the electrode.
 */
struct ft_electrode_status {
    uint32_t time_stamp; /**< Time stamp. */
    uint8_t  state;      /**< Electrode's state. */
};

/**
 *  The main structure representing the Electrode instance.
 *  There are all the parameters needed to define the behavior of the Freescale Touch 
 *  electrode, including its key detector, hardware pins, multiplier / divider to normalize
 *  the signal, and the optional shielding electrode.
 *
 *  This structure can be allocated in ROM.
 */
struct ft_electrode {
    const struct ft_electrode                   *shielding_electrode;   /**< Shielding electrode. */
    uint8_t                                     multiplier;             /**< Multiplier. */
    uint8_t                                     divider;                /**< Divider. */
    uint32_t                                    pin_input;              /**< Input pin. */
    const struct ft_keydetector_interface       *keydetector_interface; /**< Pointer to Key Detector interface. */
    const union ft_keydetector_params           keydetector_params;     /**< Pointer to Key Detector params. */
};

/**
 * \defgroup electrodes_api API Functions
 * \ingroup electrodes
 * General Function definition of the electrodes.
 *
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Enable the electrode. The function is used to enable the electrode; it should be
 *              used after the FT initialization, because the default state after the startup
 *              of the FT is electrode disabled.
 * \param electrode Pointer to the electrode params that identify the electrode.
 * \param touch Default parameter if the electrode was touched or not after the enable process.
 * \return result of operation \ref ft_result.
 * This is an example of using this function in the code:
  \code
    //The electrode that is defined in the setup of FT after the initialization must be enabled.
    if (ft_init(&system_0, ft_memory_pool, sizeof(ft_memory_pool)) < FT_SUCCESS)
    {
      while(1); // add code to handle this error 
    }
    // Enable electrode_0 that is defined in the setup of FT 
    if(ft_electrode_enable(&electrode_0, 0) != FT_SUCCESS)
    {
      printf("Enable electrode_0 failed.");
    }
    
   \endcode
 */
int32_t ft_electrode_enable(const struct ft_electrode *electrode, uint32_t touch);

/**
 * \brief Disable the electrode.
 * \param electrode Pointer to the electrode params that identify the electrode.
 * \return result of operation \ref ft_result.
 * This is an example of using this function in code:
 *\code
 *  // Disable electrode_0 that is defined in the setup of FT 
 *  if(ft_electrode_disable(&electrode_0) != FT_SUCCESS)
 *  {
 *    printf("Disable electrode_0 failed.");
 *  }
 *\endcode
*/
int32_t ft_electrode_disable(const struct ft_electrode *electrode);

/**
 * \brief Get the normalized and processed electrode signal.
 * \param electrode Pointer to the electrode data.
 * \return electrode signal calculated from the last raw value measured.
 *
 * The signal value is calculated from the raw electrode capacitance or other
 * physical signal by applying the filtering and normalization algorithms.
 * This signal is used by the "analog" \ref controls that estimate the finger
 * position based on the signal value, rather than on a simple touch / release status.
 * This is an example of using this function in the code:
 *\code
 *  // Get current signal of my_electrode 
 *  printf("The my_electrode has signal: %d.", ft_electrode_get_signal(&my_electrode));
 *\endcode
 */
uint32_t ft_electrode_get_signal(const struct ft_electrode *electrode);

/**
 * \brief Get the last known electrode status.
 * \param electrode Pointer to the electrode data.
 * \return Current electrode status.
 * \code
 *  // Get the latest status of my_electrode 
 *  char * electrode_state_name[3] = 
 * {
 *   "Initialize",
 *   "Released",
 *   "Touched"
 * };
 *  uint32_t state = ft_electrode_get_last_status(&my_electrode);
 *  printf("The my_electrode last status is: %s.", electrode_state_name[state]);
 * \endcode
 */
int32_t ft_electrode_get_last_status(const struct ft_electrode *electrode);

/**
 * \brief Get the time from the last electrode event.
 * \param electrode Pointer to the electrode data.
 * \return Time from the last electrode event.
 * \code
 *  // Get the time offset from the last change of the electrode status
 *  uint32_t offset = ft_electrode_get_time_offset(&my_electrode);
 *  printf("The my_electrode last status change has been before: %d ms .", offset);
 * \endcode
 */
uint32_t ft_electrode_get_time_offset(const struct ft_electrode *electrode);

/**
 * \brief Get the last known electrode time stamp.
 * \param electrode Pointer to the electrode data.
 * \return Current electrode status.
 * \code
 *  // Get the time stamp of the last change of the electrode status
 *  uint32_t time = ft_electrode_get_last_time_stamp(&my_electrode);
 *  printf("The my_electrode last status change was at: %d ms .", time);
 * \endcode
 */
uint32_t ft_electrode_get_last_time_stamp(const struct ft_electrode *electrode);   

/**
 * \brief Get the raw electrode signal.
 * \param electrode Pointer to the electrode data.
 * \return electrode Signal, as it is measured by the physical module.
 *
 * The raw signal is used internally by the filtering and normalization algorithms
 * to calculate the real electrode signal value, which is good to be compared
 * with the signals coming from other electrodes.
 *\code
 *  // Get the current raw signal of my_electrode 
 *  printf("The my_electrode has raw signal: %d.", ft_electrode_get_raw_signal(&my_electrode));
 *\endcode
 */
uint32_t ft_electrode_get_raw_signal(const struct ft_electrode *electrode);

#ifdef __cplusplus
}
#endif

/** \} end of electrodes_api group */
/** \} end of electrodes group */

#endif
