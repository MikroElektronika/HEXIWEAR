/**
 * pedometer screen objects
 * Project HEXIWEAR, 2015
 */

#include "gui_driver.h"
#include "screens_common.h"
#include "pedometer_private.h"

/**
 * pedometer icons
 */

guiImage_t pedometer_redIcon =
{
       .dynamicArea =
       {
               .xCrd = 64,
               .yCrd = 5,
       },

       .img = pedometer_red_bmp
};

guiImage_t pedometer_greenIcon =
{
        .dynamicArea =
        {
                .xCrd = 64,
                .yCrd = 5,
        },

        .img = pedometer_green_bmp
};
