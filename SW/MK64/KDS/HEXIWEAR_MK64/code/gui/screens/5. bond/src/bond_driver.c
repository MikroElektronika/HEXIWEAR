/**
 * \file bond_driver.c
 * \version 1.00
 * \brief this file contains HEXIWEAR Bond Screen functionality
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

/** includes */

#include "gui_driver.h"
#include "screens_common.h"
#include "bond_private.h"
#include "power_driver.h"

/** private type definitions */

/** private macros */

/*! @brief Converts milliseconds to ticks*/
#define MSEC_TO_TICK(msec)  (((uint32_t)(msec)+500uL/(uint32_t)configTICK_RATE_HZ) \
                             *(uint32_t)configTICK_RATE_HZ/1000uL)


/** private prototypes */

/** public memory declarations */

/** private memory declarations */

static uint32_t bond_passkey;

/**
 * initialize the Bond Screen
 * @param param optional parameter, in this case,
 * it can be a pointer to the previous screen
 */
void bond_Init( void *param )
{
	if(&bondScreen != (guiScreen_t*) param)
	{
	bondScreen.navigation.left = (guiScreen_t*) param;
	}

	GuiDriver_LabelCreate(&bond_label);

	sprintf((char*)bond_label.caption, "%lu", bond_passkey);
	GuiDriver_LabelAddToScr(&bond_label);

	// disable power save
	power_DisablePowerSave();
}

/**
 * destroy the Bond Screen
 * @param param optional parameter
 */
void bond_DestroyTasks( void *param )
{
	OLED_DestroyDynamicArea();
	GuiDriver_LabelDestroy(&bond_label);

	// enable power save
	power_EnablePowerSave();
}

/**
 * Save the passkey
 * @param passkey given passkey
 */
void bond_SetPasskey(uint32_t passkey)
{
	bond_passkey = passkey;
}
