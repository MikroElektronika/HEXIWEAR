
#ifndef _MENU_DRIVER
#define _MENU_DRIVER

#include <stdint.h>
#include <stddef.h>

#include "menu_defs.h"
#include "menu_screens.h"

menuStatus_t MenuDriver_Init();
menuStatus_t MenuDriver_LoadScreen(menuNavigationDir_t navigationDir, void *param);

/**
 * queues
 */

/**
 * push to menu queue
 * @param  packet [description]
 * @return        [description]
 */
menuStatus_t MenuDriver_QueueMsgPut (
                                      hostInterface_packet_t* packet
                                    );


/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
menuStatus_t MenuDriver_QueueMsgGet(
                                     hostInterface_packet_t* packet,
					            uint32_t timeout
                                   );

// update the main screen buffer
void MenuDriver_UpdateScreen (
                                uint8_t xCrd,
                                uint8_t yCrd,

                                uint8_t width,
                                uint8_t height,

                                const uint8_t* image
                              );

#endif
