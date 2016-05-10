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
#ifndef FT_FILTERS_PRV_H
#define FT_FILTERS_PRV_H

#include "ft_filters.h"

/**
 * \defgroup filter_private Filters
 * \ingroup ftapi_private
 * The filters data structure that is used in the Freescale Touch library.
 *
 * \{
 */

/**
 * The filter state definition.
 *
 */
enum ft_filter_state {
    FT_FILTER_STATE_INIT = 0,   /**< The filter is initialized. */
    FT_FILTER_STATE_RUN  = 1    /**< The filter is running correctly. */
};

/**
 * The butterworth filter context data.
 *
 */
struct ft_filter_fbutt_data {
    int32_t y;                  /**< The last result of the filter. */
    int16_t x;                  /**< The previous input value. */
    int32_t coeficient;         /** Coefficient computed by the input parameters. */
};


/**
 * The moving average filter context data.
 *
 */
struct ft_filter_moving_average_data {
  int32_t       sum;       /**< The sum of the filter data */ 
};

/**
 * \defgroup filter_api_private API Functions
 * \ingroup filter_private
 * General Private Function definition of filters.
 *
 * \{
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief        Gets the absolute value.
 * \param lsrc   Input signed 32-bit number.
 * \return       Unsigned 32-bit absolute value of the input number.
 */
uint32_t _ft_abs_int32(int32_t lsrc);
  
/**
 * \brief        Initialize the ButterWorth filter for the first use.
 * \param rom    Pointer to the ft_filter_fbutt structure.
 * \param ram    Pointer to the ft_filter_fbutt_data.
 * \param signal Input signal.
 * \return none
 */
void _ft_filter_fbutt_init(const struct ft_filter_fbutt *rom, 
                           struct ft_filter_fbutt_data *ram, uint32_t signal);

/**
 * \brief Process signal fbutt filter.
 * \param ram    Pointer to the ft_filter_fbutt_data structure.
 * \param signal Input signal.
 * \return Filtered signal.
 *
 * Returns signal equal
 *
 */
uint16_t _ft_filter_fbutt_process(struct ft_filter_fbutt_data *ram,
                                 uint16_t signal);
/**
 * \brief Process signal IIR filter
 * \param rom             Pointer to ft_filter_iir
 * \param signal          Current signal.
 * \param previous_signal Previous signal
 * \return signal
 *
 * Process the signal, using the following equation:
 * y(n)=(1 / (coef + 1) * current signal + (coef / (coef + 1) * previous_signal)
 */
uint32_t _ft_filter_iir_process(const struct ft_filter_iir *rom,
                               uint32_t signal, uint32_t previous_signal);

/**
 * \brief This function initialize moving average filter.
 * \param rom Pointer to ft_filter_moving_average structure.
 * \param ram Pointer to ft_filter_moving_average_data structure.
 * \param value Input initial value.
 * \return result of operation (0 - OK, otherwise - FALSE).
 */
int32_t _ft_filter_moving_average_init(const struct ft_filter_moving_average *rom,
                                    struct ft_filter_moving_average_data *ram,
                                    uint16_t value);
/**
 * \brief This function compute moving average filter.
 * \param rom Pointer to ft_filter_moving_average structure.
 * \param ram Pointer to ft_filter_moving_average_data structure.
 * \param value Input new value.
 * \return Current value of the moving average filter.
 */ 
uint32_t _ft_filter_moving_average_process(const struct ft_filter_moving_average *rom,
                                        struct ft_filter_moving_average_data *ram,
                                        uint16_t value);
/**
 * \brief This function compute absolute value (16-bit version).
 * \param value Input signed value.
 * \return Absolute unsigned value of input.
 */ 
uint16_t _ft_filter_abs(int16_t value);

/**
 * \brief This function limit the input value in allowd range (16-bit version).
 * \param value Input value.
 * \param limit_l Limitation low range border.
 * \param limit_H Limitation high range border.
 * \return Result value.
 */ 
uint16_t _ft_filter_limit_u(int32_t value, uint16_t limit_l, uint16_t limit_h);

/**
 * \brief This function make dead range for input value out of the allowed range (16-bit version).
 * \param value Input value.
 * \param base Base value of deadband range.
 * \param range Range of the deadband range (one half).
 * \return Result value out of the deadband range.
 */ 
uint16_t _ft_filter_deadrange_u(uint16_t value, uint16_t base, uint16_t range);

/**
 * \brief This function checks if input value is inside of the deadband range (16-bit version).
 * \param value Input value.
 * \param base Base value of deadband range.
 * \param range Range of the deadband range (one half).
 * \return Result TRUE - value is in deadband range.
                  FALSE - value is out of deadband range.
 */
int32_t _ft_filter_is_deadrange_u(uint16_t value, uint16_t base, uint16_t range);

#ifdef __cplusplus
}
#endif

/** \} */ // end of filter_api_private group
/** \} */ // end of filters_private group

#endif
