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

#ifndef FT_FRMSTR_PRV_H
#define FT_FRMSTR_PRV_H

 #include "ft_types.h"

/**
 * \defgroup freemaster_private FreeMASTER support
 * \ingroup ftapi_private
 *
 * \{
 */



/**
 * \defgroup freemaster_api_private API functions
 * \ingroup freemaster_private
 * General Private Function definition of the FreeMASTER support.
 *
 * \{
 */ 

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialized the Freescale touch FreeMASTER support system.
 * \return The result of operation.
 */
int32_t _ft_freemaster_init(void);

/**
 * \brief This function adds a dynamic variable into the FreeMASTER TSA table.
 * \param name - pointer to the string with the name of the variable
 * \param type_name - pointer to the string with the name of the variable type
 * \param address - address of the variable 
 * \param size - size of the variable
 * \return The result of the operation.
 */
int32_t _ft_freemaster_add_variable(const char * name, const char * type_name, void* address, uint32_t size);

#ifdef __cplusplus
}
#endif

/** \} */ // end of freemaster_api_private group
/** \} */ // end of freemaster_private group

#endif /* FT_FRMSTR_PRV_H */
