/**HEADER********************************************************************
* 
* Copyright (c) 2013 - 2014 Freescale Semiconductor;
* All Rights Reserved
*
*
*************************************************************************** 
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* $FileName: osadapter_types.h$
* $Version : 
* $Date    : 
*
* Comments:
*
* @brief The file contains definition for OS adapter layer.
*
*****************************************************************************/

#ifndef _OSADAPTER_TYPES_H
#define _OSADAPTER_TYPES_H 1


typedef void (* task_start_t)( void * param);
typedef void (* osa_int_isr_fptr)(void * param);
typedef void* os_event_handle;
typedef void* os_msgq_handle;
typedef void* os_gpio_handle;
typedef void* os_mutex_handle;
typedef void* os_sem_handle;


#define OS_TASK_OK         (0)
#define OS_TASK_ERROR      (-1)
#define OS_EVENT_OK        (0)
#define OS_EVENT_ERROR     (-1)
#define OS_EVENT_TIMEOUT   (-2)
#define OS_MSGQ_OK         (0)
#define OS_MSGQ_ERROR      (-1)
#define OS_GPIO_OK         (0)
#define OS_GPIO_ERROR      (-1)
#define OS_MUTEX_OK        (0)
#define OS_MUTEX_ERROR     (-1)
#define OS_SEM_OK          (0)
#define OS_SEM_ERROR       (-1)
#define OS_SEM_TIMEOUT     (-2)

/* Block the reading task if msgq is empty */
#define OS_MSGQ_RECEIVE_BLOCK_ON_EMPTY       (0x04)


#endif


