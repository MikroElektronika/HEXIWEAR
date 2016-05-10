/**HEADER********************************************************************
 * 
 * Copyright (c) 2004 - 2009, 2013 Freescale Semiconductor;
 * All Rights Reserved
 *
 *
 *************************************************************************** 
 *
 *
 * @file composite_app.h
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief The file contains function headers needed by application
 *
 *****************************************************************************/

#ifndef _COMPOSITE_APP_H
#define _COMPOSITE_APP_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_device_config.h"
#include "usb.h"
#include "usb_device_stack_interface.h"
#include "usb_class_composite.h"
#include "usb_class_cdc.h"
#include "usb_class_msc.h"
#include "disk.h"
#include "composite_app.h"
#include "usb_descriptor.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define USB_STACK_SIZE ( 0xC00 )
#define USB_PRIO ( 13 )

#define COMPOSITE_CFG_MAX            2

#define CDC_VCOM_INTERFACE_INDEX     0
#define MSC_DISK_INTERFACE_INDEX     1

#if HIGH_SPEED
#define CONTROLLER_ID                USB_CONTROLLER_EHCI_0
#define BULK_IN_ENDPOINT             (HS_BULK_IN_ENDPOINT)
#define BULK_OUT_ENDPOINT            (HS_BULK_OUT_ENDPOINT)
#define DIC_ISO_IN_ENDPOINT          (HS_DIC_ISO_IN_ENDPOINT)
#define DIC_ISO_OUT_ENDPOINT         (HS_DIC_ISO_OUT_ENDPOINT)
#define CIC_NOTIF_ENDPOINT           (HS_CIC_NOTIF_ENDPOINT)
#define DIC_BULK_IN_ENDPOINT         (HS_DIC_BULK_IN_ENDPOINT)
#define DIC_BULK_OUT_ENDPOINT        (HS_DIC_BULK_OUT_ENDPOINT)

#else
#define CONTROLLER_ID                USB_CONTROLLER_KHCI_0

#define BULK_IN_ENDPOINT             (FS_BULK_IN_ENDPOINT)
#define BULK_OUT_ENDPOINT            (FS_BULK_OUT_ENDPOINT)
#define DIC_ISO_IN_ENDPOINT          (FS_DIC_ISO_IN_ENDPOINT)
#define DIC_ISO_OUT_ENDPOINT         (FS_DIC_ISO_OUT_ENDPOINT)
#define CIC_NOTIF_ENDPOINT           (FS_CIC_NOTIF_ENDPOINT)
#define DIC_BULK_IN_ENDPOINT         (FS_DIC_BULK_IN_ENDPOINT)
#define DIC_BULK_OUT_ENDPOINT        (FS_DIC_BULK_OUT_ENDPOINT)

#endif
/******************************************************************************
 * Types
 *****************************************************************************/
typedef struct composite_device_struct
{
    composite_handle_t          composite_device;
    cdc_handle_t                cdc_vcom;
    disk_struct_t               msc_disk;
    composite_config_struct_t   composite_device_config_callback;
    class_config_struct_t       composite_device_config_list[COMPOSITE_CFG_MAX];
} composite_device_struct_t;

typedef enum
{
  COMPOSITE_STATUS_SUCCESS,    // success
  COMPOSITE_STATUS_ERROR,      // fail

} composite_status_t;

/*****************************************************************************
 * Global variables
 *****************************************************************************/
#if (OS_ADAPTER_ACTIVE_OS == OS_ADAPTER_MQX)
extern composite_device_struct_t* g_composite_device;
#else
extern composite_device_struct_t g_composite_device;
#endif
/*****************************************************************************
 * Global Functions
 *****************************************************************************/
composite_status_t Run_USB_Task();

#endif
