/**
 * @file log.h
 * @brief <h2> GSM/GNSS click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * GSM/GNSS click board. 
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        29 Nov 2016
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 *
 * ### Test configuration STM : ###
 * @par
 * -<b> MCU           </b> :    STM32F207VG
 * -<b> Dev. Board    </b> :    EasyMx v7 for STM32
 * -<b> Ext. Modules  </b> :    GSM/GNSS click
 * -<b> SW            </b> :    mikroC PRO for ARM v4.9.0
 *
 */

#ifndef LOG_H
#define LOG_H

#ifdef _DEBUG_
    #ifdef _LOG_UART_
        #define _LOG_CHAR_DEBUG_ 
    #else
        #define _LOG_DEBUG_
    #endif
#endif

inline void log_init(unsigned long baud_rate)
{
#ifdef _DEBUG_
    UART3_Init_Advanced( 
        baud_rate, 
        _UART_8_BIT_DATA,
        _UART_NOPARITY,
        _UART_ONE_STOPBIT,
        &_GPIO_Module_UART3_PC16_17
    );

    Delay_ms( 10 );
#endif    
}

inline void log_info(const char* x)
{
#ifdef _LOG_DEBUG_
    UART3_Write_Text("INFO: ");
    UART3_Write_Text(x);

    UART3_Write_Text("\r\n");
#endif
}

inline void log_error(const char* x)
{
#ifdef _LOG_DEBUG_
    UART3_Write_Text("ERROR: ");
    UART3_Write_Text(x);

    UART3_Write_Text("\r\n");
#endif
}

inline void log_char(char x)
{
#ifdef _LOG_CHAR_DEBUG_
    UART3_Write(x);
#endif    
}

#endif // LOG_H