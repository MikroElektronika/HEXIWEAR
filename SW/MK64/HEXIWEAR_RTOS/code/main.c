/**
 * @file main.c
 * @brief this file contains the launch of the initialization task which will
 * finish the necessary initialization upon the scheduler is started
 *
 * @version 1.00
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

#include "main.h"
#include "OLED_defs.h"
#include "OLED_driver.h"
#include "OLED_resources.h"

void Task1( task_param_t param )
{
    oled_dynamic_area_t oled_dynamic_area;
    oled_text_properties_t oled_text_properties;

    hostInterface_packet_t command_packet;

	OLED_Init( &oledModule, &oledSettings );
	OLED_FillScreen( GUI_COLOR_BLACK );

	oled_dynamic_area.xCrd = 0;
	oled_dynamic_area.yCrd = 0;
	oled_dynamic_area.width = 96;
	oled_dynamic_area.height = 96;
	OLED_SetDynamicArea( &oled_dynamic_area );

	oled_text_properties.font = guiFont_Tahoma_8_Regular;
	oled_text_properties.fontColor = GUI_COLOR_WHITE;
	oled_text_properties.alignParam = OLED_TEXT_ALIGN_LEFT;
	oled_text_properties.background = NULL;
	OLED_SetTextProperties( &oled_text_properties );

	OLED_DrawText( "Welcome" );

	while(1)
	{
		OSA_TimeDelay( 500 );

		HostInterface_CmdQueueMsgGet( &command_packet );

		switch( command_packet.type )
		{

		    // buttons
		    case packetType_pressUp:
		    {
		    	OLED_DrawText( "Up" );
				// Insert your code here...

				break;
		    }
		    case packetType_pressDown:
		    {
		    	OLED_DrawText( "Down" );
				// Insert your code here...

				break;
		    }
		    case packetType_pressLeft:
		    {
		    	OLED_DrawText( "Left" );
				// Insert your code here...

				break;
		    }
		    case packetType_pressRight:
		    {
		    	OLED_DrawText( "Right" );
				// Insert your code here...

				break;
		    }

		    default: {}
	    }
	}
}

void main()
{
  /** initialize the hardware */
  PE_low_level_init();

  /** disable write buffering end enable ARM exceptions */
  HEXIWEAR_EnableExceptions();

  /** initialize the startup task */
  HEXIWEAR_Init();

  OSA_TaskCreate(
		          Task1,
                  (uint8_t*)"Task1",
                  0x1000,
                  NULL,
                  10,
                  (task_param_t)0,
                  false,
                  NULL
                );

  /** start RTOS scheduler */
  HEXIWEAR_Start();

  while (1) {}
}
