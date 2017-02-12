/**
 * \file MultipleChoice_driver.c
 * \version 1.00
 */

/** includes */

#include "gui_driver.h"
#include "screens_common.h"
#include "MultipleChoice_private.h"
#include "MultipleChoice.h"
#include "power_driver.h"

#include "gui_defs.h" /* guiDriver_display.image[] is the image buffer */

static uint32_t MultipleChoice_passkey = 1234;
static TaskHandle_t taskHandle = NULL;

/**
 * initialize the Screen
 * @param param optional parameter, in this case,
 * it can be a pointer to the previous screen
 */
void MultipleChoice_Init(void *param) {
	GuiDriver_LabelCreate(&MultipleChoice_label);

	sprintf((char*)MultipleChoice_label.caption, "%lu", MultipleChoice_passkey);
	GuiDriver_LabelAddToScr(&MultipleChoice_label);

#if 1
	{
	  int i;
	  oled_status_t status;

	  for(i=0; i<15; i++) {
	    guiDriver_display.image[i] = 0x55;
	    //status = OLED_DrawPixel(i,i, 0xabcd);
	    //if (status!=OLED_STATUS_SUCCESS) {
	    //  for(;;){}
	    //}
	  }
	}
#endif
	// disable power save
	power_DisablePowerSave();
}

static void MultipleChoice_Task(void *param) {
  for(;;) {
    vTaskDelay(100/configTICK_RATE_HZ);
  }
}

void MultipleChoice_CreateTasks(void* param) {
  if (xTaskCreate(
      MultipleChoice_Task,   /** pointer to the task */
      (char const*)"MultipleChoice",  /** task name for kernel awareness debugging */
      300,  /** task stack size */
      NULL,  /** optional task startup argument */
      tskIDLE_PRIORITY+1,   /** initial priority */
      &taskHandle  /** optional task handle to create */
    ) != pdPASS)
  {
    catch(CATCH_INIT);
  }
}

/**
 * destroy the Screen
 * @param param optional parameter
 */
void MultipleChoice_DestroyTasks(void *param) {
	OLED_DestroyDynamicArea();
	GuiDriver_LabelDestroy(&MultipleChoice_label);

	// enable power save
	power_EnablePowerSave();
	vTaskDelete(taskHandle);
	taskHandle = NULL;
}

/**
 * Save the passkey
 * @param passkey given passkey
 */
void MultipleChoice_SetPasskey(uint32_t passkey) {
  MultipleChoice_passkey = passkey;
}
