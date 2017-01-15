/**
 * @file                                                  gsm4_dev_adapter.h
 *
 * @defgroup DEV_ADAPT Device Adapter
 * @{
 *
 * @brief                       Device Adapter
 *
 * @par
 * Used for adaptation needed for the particular device.
 *
 ******************************************************************************/

#ifndef AT_ADAPTER_H
#define AT_ADAPTER_H

#include "at_config.h"
#include "dev_hal.h"

/******************************************************************************
* Variables
*******************************************************************************/

extern volatile bool            exception_f;
extern volatile bool            response_f;
extern volatile bool            cue_f;

extern volatile char            tx_buffer[ AT_TRANSFER_SIZE ];
extern volatile char            rx_buffer[ AT_TRANSFER_SIZE ];

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Adapter Initialization
 */
void dev_adapter_init
(
                void
);

/**
 * @brief Adapter Flags Reset
 */
void dev_adapter_reset
(
                void
);

/**
 * @brief Transmission
 *
 * @param tx_input - character for transmission through UART bus
 */
int dev_tx
(
                char tx_input
);

/**
 * @brief Reception
 *
 * This function should be placed inside the RX interrupt routine.
 *
 * @param[in] rx_input - character received through UART bus
 */
void dev_rx
(
                char rx_input
);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

/**
 * @}
 */
/*** End of File **************************************************************/
