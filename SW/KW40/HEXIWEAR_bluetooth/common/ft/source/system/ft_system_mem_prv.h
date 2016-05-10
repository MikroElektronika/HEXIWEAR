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

#ifndef FT_MEM_PRV_H
#define FT_MEM_PRV_H

 #include "ft_types.h"

/**
 * \defgroup memory_private Memory Management
 * \ingroup ftapi_private
 *
 * \{
 */

/**
 *
 * This structure contains the memory pool for all RAM data of the Freescale touch
 * volatile data structures.
 * This structure can be allocated in RAM.
 */
struct ft_mem {
    uint8_t     *pool;          /**< Pointer to the allocated memory pool for the Freescale touch. */
    uint32_t    pool_size;      /**< Size of the allocated memory pool for the Freescale touch. */
    uint8_t     *free_pointer;  /**< Pointer to the last free position in the memory pool. */
};

/**
 * \defgroup memory_api_private API functions
 * \ingroup memory_private
 * General Private Function definition of the memory support.
 *
 * \{
 */ 

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Initialized the Freescale touch memory managment system.
 * \param pool - pointer to the allocated memory place to be used by the system (the size must be aligned by 4).
 * \param size - size of the memory pool handled by the pool parameter.
 * \return The result of the operation.
 */
int32_t _ft_mem_init(uint8_t *pool, const uint32_t size);

/**
 * \brief Allocation of memory from the memory pool.
 * \param size - size of the memory block to allocate.
 * \return The pointer to the new allocated block, NULL in case there is not enough space in the pool.
 */
void* _ft_mem_alloc(const uint32_t size);

/**
 * \brief Deinitialized the Freescale touch memory management system.
 * \return The result of the operation.
 */
int32_t _ft_mem_deinit(void);


#ifdef __cplusplus
}
#endif

/** \} */ // end of memory_api_private group
/** \} */ // end of memory_private group

#endif /* FT_MEM_PRV_H */
