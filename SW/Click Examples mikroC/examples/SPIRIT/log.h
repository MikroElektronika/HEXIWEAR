/**
 * log.h
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
 * @page        Log
 * @date        29 Nov 2016
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */


#ifndef LOG_H
#define LOG_H


#if   defined( _UART1_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )          UART1_Init( x )
    #define UART_WRITE_TEXT( x )    UART1_Write_Text( x )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif defined( _UART2_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )          UART2_Init( x )
    #define UART_WRITE_TEXT( x )    UART2_Write_Text( x )   
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif defined( _UART3_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )          UART3_Init( x )
    #define UART_WRITE_TEXT( x )    UART3_Write_Text( x )  
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif defined( _UART4_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )          UART4_Init( x )
    #define UART_WRITE_TEXT( x )    UART4_Write_Text( x )  
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif defined( _UART5_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )          UART5_Init( x )
    #define UART_WRITE_TEXT( x )    UART5_Write_Text( x )  
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#elif defined( _SOFT_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )
                 
    #define UART_WRITE_TEXT( x )\
            {\
                char* ptr = x;\
                while(*ptr)\
                {\
                    Soft_UART_Write(*ptr++);\
                }\
            }
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#else
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    #define UART_INIT( x )
    #define UART_WRITE_TEXT( x )     
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#endif

#if defined(_UART1_LOG_) || defined(_UART2_LOG_) || defined(_UART3_LOG_)\
    || defined(_UART4_LOG_) || defined(_UART5_LOG_) || defined( _SOFT_LOG_ )
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static char sep[] = 
    "-------------------------------------------------------";

#define LOG_NEW_LINE\
        UART_WRITE_TEXT( "\r\n" );  

#define LOG_TAB\
        UART_WRITE_TEXT( "\x09" );   


#define LOG_INIT( baud_rate )\
        UART_INIT( baud_rate );\
        Delay_ms( 10 );\
        UART_WRITE_TEXT( "\x0C" );\
        UART_WRITE_TEXT(\
            "=#===================================================#="\
        );\
        LOG_NEW_LINE;\
        UART_WRITE_TEXT(\
            "=#           Log initialised                         #="\
        );\
        LOG_NEW_LINE;\
        UART_WRITE_TEXT(\
            "=#===================================================#="\
        );\
        LOG_NEW_LINE;      
        
#define LOG_INFO( x )\
        UART_WRITE_TEXT( "INFO: " ); LOG_TAB;\
        UART_WRITE_TEXT( x );\
        LOG_NEW_LINE;      
        
#define LOG_ERROR( x )\
        UART_WRITE_TEXT( "ERROR: " ); LOG_TAB;\
        UART_WRITE_TEXT( x );\
        LOG_NEW_LINE;      
        
#define LOG_HEX_ARRAY( x , cnt )\
        {\
        unsigned int _log_ind_ = 0;\
        char _log_buffer_[3];\
        _log_ind_ = 0;\
        UART_WRITE_TEXT( "ARRAY: " ); LOG_TAB;\
        while (_log_ind_ < cnt )\
        {\
            ByteToHex( x[_log_ind_++], _log_buffer_ );\
            UART_WRITE_TEXT( "0x" );\
            UART_WRITE_TEXT( _log_buffer_ );\
            UART_WRITE_TEXT( " " );\
            if(_log_ind_ % 8 == 0)\
            {\
                LOG_NEW_LINE; LOG_TAB;\
            }\
        }\
        LOG_NEW_LINE;\
        }      

#define LOG_HEX_U32( label, x )\
        {\
        char _log_buffer_[9];\
        UART_WRITE_TEXT( "VALUE: " ); LOG_TAB;\
        UART_WRITE_TEXT( label );\
        UART_WRITE_TEXT( " : 0x" );\
        LongWordToHex(x, _log_buffer_);\
        UART_WRITE_TEXT( _log_buffer_ );\
        LOG_NEW_LINE;\
        }

#define LOG_HEX_U16( label, x )\
        {\
        char _log_buffer_[5];\
        UART_WRITE_TEXT( "VALUE: " ); LOG_TAB;\
        UART_WRITE_TEXT( label );\
        UART_WRITE_TEXT( " : 0x" );\
        WordToHex(x, _log_buffer_);\
        UART_WRITE_TEXT( _log_buffer_ );\
        LOG_NEW_LINE;\
        }

#define LOG_HEX_U8( label, x )\
        {\
        char _log_buffer_[3];\
        UART_WRITE_TEXT( "VALUE: " ); LOG_TAB;\
        UART_WRITE_TEXT( label );\
        UART_WRITE_TEXT( " : 0x" );\
        ByteToHex(x, _log_buffer_);\
        UART_WRITE_TEXT( _log_buffer_ );\
        LOG_NEW_LINE;\
        }
                
#define LOG_VAL_INT( label, x )\
        {\
        char _log_buffer_[16];\
        UART_WRITE_TEXT( "VALUE: " ); LOG_TAB;\
        UART_WRITE_TEXT( label );\
        UART_WRITE_TEXT( " : " );\
        LongToStr(x, _log_buffer_);\
        UART_WRITE_TEXT( Ltrim(_log_buffer_) );\
        LOG_NEW_LINE;\
        }

#define LOG_VAL_REAL( label, x )\
        {\
        char _log_buffer_[16];\
        UART_WRITE_TEXT( "VALUE: " ); LOG_TAB;\
        UART_WRITE_TEXT( label );\
        UART_WRITE_TEXT( " : " );\
        FloatToStr(x, _log_buffer_);\
        UART_WRITE_TEXT( _log_buffer_ );\
        LOG_NEW_LINE;\
        }

#define LOG_RULE()\
        UART_WRITE_TEXT(sep);\
        LOG_NEW_LINE;  

#define LOG_HEADER( x )\
        LOG_RULE();\
        LOG_TAB;\
        UART_WRITE_TEXT(x);\
        LOG_NEW_LINE;\
        LOG_RULE();


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#else
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define LOG_NEW_LINE   
#define LOG_TAB        
#define LOG_RULE()
#define LOG_INIT( baud_rate )
#define LOG_INFO( x )
#define LOG_ERROR( x )
#define LOG_VAL_REAL( label, x ) 
#define LOG_VAL_INT( label, x )
#define LOG_HEX_U8( label, x ) 
#define LOG_HEX_U16( label, x )
#define LOG_HEX_U32( label, x ) 
#define LOG_HEX_ARRAY( x , cnt ) 
#define LOG_HEADER( x ) 
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#endif
 
#endif // LOG_H