#include <stdint.h>
#include "fsl_os_abstraction.h"

void Sleep(unsigned int ms)
{
	OSA_TimeDelay(ms);
}
