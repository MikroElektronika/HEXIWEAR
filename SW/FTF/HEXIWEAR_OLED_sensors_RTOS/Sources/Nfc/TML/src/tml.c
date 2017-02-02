#include <stdint.h>
#include "board.h"
#include "fsl_interrupt_manager.h"
#include "generic_i2c_driver.h"
#include <tool.h>

#define I2C_WRITE(x,y) I2C_Send(&NxpNci_I2cHandle, NULL, 0, x, y)
#define I2C_READ(x,y) I2C_Receive(&NxpNci_I2cHandle, x, y)

genericI2cHandle_t NxpNci_I2cHandle = {
		.instance = NXPNCI_I2C_INSTANCE,
		.timeout = 100,
		.alternate = true
};

semaphore_t IrqSem;

typedef enum {ERROR = 0, SUCCESS = !ERROR} Status;

void NXPNCI_IRQHandler(void)
{
	if (GPIO_DRV_ReadPinInput(kGpioNfcIrq) == 1)
	{
		GPIO_DRV_ClearPinIntFlag (kGpioNfcIrq);
		OSA_SemaPost(&IrqSem);
	}
}

static Status tml_Init(void) {
    GPIO_DRV_Init(nfcInPins, nfcOutPins);
    I2C_Init(&NxpNci_I2cHandle, NXPNCI_I2C_ADDR_7BIT, NXPNCI_I2C_BAUDRATE);
    if(OSA_SemaCreate(&IrqSem, 0) != kStatus_OSA_Success) return ERROR;
    return SUCCESS;
}

static Status tml_DeInit(void) {
    OSA_SemaDestroy(&IrqSem);
    I2C_Deinit(&NxpNci_I2cHandle);
    GPIO_DRV_ClearPinOutput(kGpioNfcVen);
    return SUCCESS;
}

static Status tml_Reset(void) {
	GPIO_DRV_ClearPinOutput(kGpioNfcVen);
	Sleep(10);
	GPIO_DRV_SetPinOutput(kGpioNfcVen);
	Sleep(10);
	return SUCCESS;
}

static Status tml_Tx(uint8_t *pBuff, uint16_t buffLen) {
    if (I2C_WRITE(pBuff, buffLen) != STATUS_I2C_SUCCESS)
    {
    	Sleep(10);
    	if(I2C_WRITE(pBuff, buffLen) != STATUS_I2C_SUCCESS)
    	{
    		return ERROR;
    	}
    }

	return SUCCESS;
}

static Status tml_Rx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead) {
    if(I2C_READ(pBuff, 3) == STATUS_I2C_SUCCESS)
    {
    	if ((pBuff[2] + 3) <= buffLen)
    	{
			if (pBuff[2] > 0)
			{
				if(I2C_READ(&pBuff[3], pBuff[2]) == STATUS_I2C_SUCCESS)
				{
					*pBytesRead = pBuff[2] + 3;
				}
				else return ERROR;
			} else
			{
				*pBytesRead = 3;
			}
    	}
		else return ERROR;
   }
    else return ERROR;

	return SUCCESS;
}

static Status tml_WaitForRx(uint32_t timeout) {
	osa_status_t status;

	do status = OSA_SemaWait(&IrqSem, timeout?timeout:OSA_WAIT_FOREVER);
	while((status == kStatus_OSA_Idle) && (timeout != 0));

	if (status == kStatus_OSA_Success) return SUCCESS;

	return ERROR;
}

void tml_Connect(void) {
	tml_Init();
	tml_Reset();
}

void tml_Disconnect(void) {
	tml_DeInit();
}

void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent) {
	if(tml_Tx(pBuffer, BufferLen) == ERROR) *pBytesSent = 0;
	else *pBytesSent = BufferLen;
}

void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint16_t timeout) {
	if (tml_WaitForRx(timeout) == ERROR) *pBytes = 0;
	else tml_Rx(pBuffer, BufferLen, pBytes);
}


