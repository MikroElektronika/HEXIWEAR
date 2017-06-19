/**
 * \file pedometer_info.h
 * \version 1.00
 * \brief this file contains pedometer app related info and constants
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

#pragma once

#define KEYNETIK_APPID  ( 20 )
#define PEDOMETER_APPID ( 21 )

#define PEDOMETER_STATUS_ACTIVITY_BITNUM ( 0 )
#define PEDOMETER_STATUS_SUSPEND_BITNUM  ( 3 )
#define PEDOMETER_STATUS_ACTCHG_BITNUM   ( 4 )
#define PEDOMETER_STATUS_STEPCHG_BITNUM  ( 5 )
#define PEDOMETER_STATUS_SUSPCHG_BITNUM  ( 6 )
#define PEDOMETER_STATUS_MRGFLG_BITNUM   ( 7 )

#define PEDOMETER_STATUS_CHG_MASK         (\
                                              PEDOMETER_STATUS_ACTCHG_MASK\
                                            | PEDOMETER_STATUS_STEPCHG_MASK\
                                            | PEDOMETER_STATUS_SUSPCHG_MASK\
                                          )

#define PEDOMETER_STATUS_ACTIVITY_MASK   ( 7 << PEDOMETER_STATUS_ACTIVITY_BITNUM )
#define PEDOMETER_STATUS_SUSPEND_MASK    ( 1 << PEDOMETER_STATUS_SUSPEND_BITNUM )
#define PEDOMETER_STATUS_ACTCHG_MASK     ( 1 << PEDOMETER_STATUS_ACTCHG_BITNUM )
#define PEDOMETER_STATUS_STEPCHG_MASK    ( 1 << PEDOMETER_STATUS_STEPCHG_BITNUM )
#define PEDOMETER_STATUS_SUSPCHG_MASK    ( 1 << PEDOMETER_STATUS_SUSPCHG_BITNUM )
#define PEDOMETER_STATUS_MRGFLG_MASK     ( 1 << PEDOMETER_STATUS_MRGFLG_BITNUM )


// tasks' info
#define PEDOMETER_STACK_SIZE ( 0x400 ) // todo: change to meaningful value
#define PEDOMETER_PRIO ( HEXIWEAR_APP_PRIO ) // todo: change to meaningful value

// queues' info
#define PEDOMETER_QUEUE_SIZE ( 3 )
