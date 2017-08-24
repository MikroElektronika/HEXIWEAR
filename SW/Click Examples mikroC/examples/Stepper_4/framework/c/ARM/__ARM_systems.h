#ifdef __MIKROC_PRO_FOR_ARM__

#ifdef EASYMX_STM32_V7
#define __STM32
#include "ARM/STM32/__STM32_systems.h"
#endif

#ifdef CLICKER_2_STM32
#define __STM32
#include "ARM/STM32/__STM32_systems.h"
#endif

#ifdef  CLICKER_2_CEC1702
#define __CEC
#include "ARM/CEC/__CEC_systems.h"
#endif

#ifdef CLICKER_2_MSP432
#define __MSP
#include "ARM/MSP/__MSP_systems.h"
#endif

#ifdef HEXIWEAR_DOCKING
#define __KINETIS
#include "ARM/KINETIS/__KINETIS_systems.h"
#endif

#ifdef EASY_MX_PRO_V7_TIVA
#define __TIVA
#include "ARM/TIVA/__TIVA_systems.h"
#endif

#endif