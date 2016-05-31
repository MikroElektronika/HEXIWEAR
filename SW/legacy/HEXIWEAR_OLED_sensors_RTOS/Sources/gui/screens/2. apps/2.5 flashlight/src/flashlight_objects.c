#include "gui_driver.h"
#include "screens_common.h"
#include "flashlight_private.h"

/************************************************************************************
*************************************************************************************
* Definition of flashlight screen
*************************************************************************************
************************************************************************************/

 guiScreen_t flashlightScreen =
 {
   .navigation =
   {
           .up     = &gui_motionControl_coverScreen,
           .down   = &fitnessScreen,
           .left   = &appsScreen,
           .right  = NULL
   },

   .image = flashlight_screen_bmp,

   .initFunction        = flashlight_Init,
   .createTaskFunction  = flashlight_CreateTasks,
   .destroyTaskFunction = flashlight_DestroyTasks
 };

 guiImage_t
     flashlight_icon =
     {
         .dynamicArea =
         {
             .xCrd   = 24,
             .yCrd   = 23
         },

         .img = flashlight_off_bmp
     };
