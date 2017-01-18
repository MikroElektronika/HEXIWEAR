/**
 * @file gsm_gnss_click.h
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
 * @date        23 Nov 2016
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

/******************************************************************************
* Includes
*******************************************************************************/
#include <built_in.h>
#include <stdio.h>

#include "gsm_gnss_click.h"


/******************************************************************************
* Preprocessors
*******************************************************************************/
#define CMD_BUFFER_LENGTH 25
#define MAX_PHONE_NUMBER_LENGTH 10
#define CMGS_CMD_LENGTH 9
#define SUB_CHAR 0x1A

#define SMS_FINISHED_INITIALISATION_CODE "3"
#define PARAM_OFFSET 2


/******************************************************************************
* Typedefs
*******************************************************************************/
//typedef struct {
    
//};

/******************************************************************************
* Variable Definitions
*******************************************************************************/
extern sfr sbit GSM_PWR;
extern sfr sbit R_LED;

static bool sim_ready = false;
static bool rdy_flag = false;
static bool network_reg = false;
static bool time_sync = false;

static bool sms_sent = false;
static bool sms_delivered = false;

static bool sms_pending = false;


static send_sms_callback_t sms_sent_callback;
static send_sms_callback_t sms_delivered_callback;
static send_sms_callback_t sms_failed_callback;
static send_sms_callback_t sms_confirmed_callback;

static int message_reference;

char tmp_buffer[16];

char navigation_url_buffer[70];         
static bool navigation_ready = false;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void gsm_gnss_click_reset( void );
static bool gsm_gnss_click_wait_ready( void );

static void gsm_gnss_click_evt_default( char* response );
static void gsm_gnss_click_evt_qinistat_exe( char* response );
static void gsm_gnss_click_evt_cmgs_setter( char* response );
static void gsm_gnss_click_evt_cds_exe( char* response );
static void gsm_gnss_click_evt_cms_error( char* response );
static void gsm_gnss_click_evt_qgnssrd_set( char *response );

static bool gsm_gnss_click_response_ok( char* response);

static void gsm_gnss_click_format_cmgs_cmd( 
    char* cmd_buffer, 
    const char* phone_number
);

static void gsm_gnss_click_get_param(char* params, char* out, uint8_t index);

/******************************************************************************
* Private Functions
*******************************************************************************/

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_reset( void )
{
    GSM_PWR = 1; 
    Delay_ms(10);

    GSM_PWR = 0; 
    Delay_ms(10);

    GSM_PWR = 1;
}

/***************************************************************************//**
 *
 */
static bool gsm_gnss_click_response_ok( char* response)
{
    char* ok_str = strstr(response, "OK");
    if(ok_str != NULL) return true;

    return false;
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_default( char *response )
{ 
    log_info("DEFAULT EVENT");
    log_info(response);

    if(strncmp(response, "RDY", 3) == 0)
     rdy_flag = true;
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_qinistat_exe( char *response )
{
    char* colon_delimiter_ptr; 

    log_info(response);

    if( ! gsm_gnss_click_response_ok( response ) )
        return;

    gsm_gnss_click_get_param(response, tmp_buffer, 0);

    if (strcmp(tmp_buffer, SMS_FINISHED_INITIALISATION_CODE) == 0)
    {
        sim_ready = true;
    }
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_cmgs_setter( char *response )
{
    const char* param_ptr;
    const char* comma_ptr;
    char tmp_buffer[10];

    log_info("CMGS SETTER");
    log_info(response);

    //strncpy(navigation_url_buffer, response, 70);

    if( ! gsm_gnss_click_response_ok( response ) )
    {
        sms_failed_callback();
        sms_pending = false;
        return;
    }

    log_info("pass 2");
    gsm_gnss_click_get_param(response, tmp_buffer, 0);
    log_info("pass 3");
    
    log_info(tmp_buffer);

    message_reference = atoi(tmp_buffer);

    sms_sent_callback();
    sms_pending = false;
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_cds_exe( char *response )
{
    char tmp_buffer[10];
    char* comma_ptr;
    int first_octave;
    
          
    log_info(response);
    
    gsm_gnss_click_get_param(response, tmp_buffer, 0);

    first_octave = atoi(tmp_buffer);

    gsm_gnss_click_get_param(response, tmp_buffer, 1);

    if (message_reference == atoi(tmp_buffer))
    {
        sms_delivered_callback();
    }
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_cms_error( char *response )
{
    log_error(response);

    sms_failed_callback();
    sms_pending = false;
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_cgreg_get( char *response )
{
    uint8_t stat;

    log_info(response);

    gsm_gnss_click_get_param( response, tmp_buffer, 1 );
    stat = atoi(tmp_buffer);

    if(stat == 1)
        network_reg = true;
    
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_qgnssts_get( char *response )
{
    uint8_t stat;

    log_info(response);

    gsm_gnss_click_get_param( response, tmp_buffer, 0 );
    stat = atoi(tmp_buffer);

    if(stat == 1)
        time_sync = true;
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_evt_qgnssrd_set( char *response )
{
    char deg[4] = { 0 };
    char min[3] = { 0 };
    char dec[5] = { 0 };

    float  latitude;
    float  longitude;

    char latitude_buffer[16] = { 0 };
    char longitude_buffer[16] = { 0 };

    log_info(response);

    gsm_gnss_click_get_param( response, tmp_buffer, 1 );

    strncpy(deg, tmp_buffer, 2);
    strncpy(min, tmp_buffer + 2, 2);
    strncpy(dec, tmp_buffer + 5, 4);

    latitude = atoi(deg) + (atoi(min) + (atoi(dec) / 10000.0f)) / 60.0f;
    
    gsm_gnss_click_get_param( response, tmp_buffer, 2 );

    if(tmp_buffer[0] == 'S') latitude *= -1.0f;

    gsm_gnss_click_get_param( response, tmp_buffer, 3 );

    strncpy(deg, tmp_buffer, 3);
    strncpy(min, tmp_buffer + 3, 2);
    strncpy(dec, tmp_buffer + 6, 4);

    longitude = atoi(deg) + (atoi(min) + atoi(dec) / 10000.0f) / 60.0f;

    gsm_gnss_click_get_param( response, tmp_buffer, 4 );

    if(tmp_buffer[0] == 'W') longitude *= -1.0f;

    FloatToStr(latitude, latitude_buffer);
    FloatToStr(longitude, longitude_buffer);

    sprintf(
        navigation_url_buffer,
        "https://www.google.rs/maps/place/%s,%s",
        Ltrim(latitude_buffer), Ltrim(longitude_buffer)
    );

    navigation_ready = true;
}

/***************************************************************************//**
 *  The function blocks until SIM card initialisation is done.
 *  The function returns when initialization of SIM card related functions has
 *  been finished.
 *  \param timeout Timeout.
 *  \return Returns true if initialisation is done, and false if initialisation 
 *          is not finished for given timeout.
 */
static bool gsm_gnss_click_wait_ready( void )
{
    uint8_t index = 0;

    while( ! rdy_flag )
        at_process();

    hexiwear_gsm_gnss_gui_draw_waiting_bar( index++ );
    
    while( ! sim_ready )
    {
        if(! (index % 5) ) at_cmd( "AT+QINISTAT" );
        
        hexiwear_gsm_gnss_gui_draw_waiting_bar( index++ );
        Delay_ms(200);
    }

    return true;
}

/***************************************************************************//**
 *
 */
static void gsm_gnss_click_get_param( char* response, char* out, uint8_t index)
{
    uint8_t i = 0;
    uint8_t j = 0;
    char* comma;
    char* param = strchr(response, ':') + 2;

    while( index && param[i] != '\r' )
    {
        if(param[i++] == ',')
        {
            index--;
        }
    }

    while( param[i] != ',' && param[i] != '\r')
    {
        out[j++] = param[i++];
    }

    out[j] = '\0'; 
}

/***************************************************************************//**
 *  
 */
static void gsm_gnss_click_format_cmgs_cmd( 
     char* cmd_buffer, 
     const char* phone_number
)
{
    memset(cmd_buffer, 0x00, CMD_BUFFER_LENGTH);

    strcpy(cmd_buffer, "AT+CMGS=\"");
    cmd_buffer = cmd_buffer + CMGS_CMD_LENGTH;

    strcpy(cmd_buffer, phone_number);
    cmd_buffer = cmd_buffer + strlen(phone_number);

    strcpy(cmd_buffer, "\"");
}

/***************************************************************************//**
 *  
 */
static void gsm_gnss_click_init_cmds( void )
{
    // Set SMS message format as text mode.
    at_cmd( "AT+CMGF=1" );
    // Set character set as GSM which is used by the TE.
    at_cmd( "AT+CSCS=\"GSM\"" );
    // SMS status report is supported under text mode if <fo> is set to 49.
    at_cmd( "AT+CSMP=49,167,0,0" );
    // SMS-STATUS-REPORTs are routed to the TE by using unsolicited result 
    // code: +CDS.
    at_cmd( "AT+CNMI=2,2,0,1,0" );

    // Enable GNSS.
    at_cmd( "AT+QGNSSC=1" );
    at_cmd( "AT+QIFGCNT=2" );
    at_cmd( "AT+QICSGP=1,\"CMNET\"" );

    at_cmd( "AT+QGNSSTS?" );

    at_cmd( "AT+QGNSSEPO=1" );
    at_cmd( "AT+QGEPOAID" );
}


/*******************************************************************************
* Public Functions
*******************************************************************************/

/***************************************************************************//**
 *
 */
void gsm_gnss_click_init( void )
{
    engine_init( gsm_gnss_click_evt_default );

    at_cmd_save( "+QINISTAT", 
        1000, 
        NULL, 
        NULL, 
        NULL, 
        gsm_gnss_click_evt_qinistat_exe 
    );
    
    at_cmd_save( "+CMGS", 
        1000, 
        NULL,
        gsm_gnss_click_evt_cmgs_setter,
        NULL,
        gsm_gnss_click_evt_cmgs_setter 
    );

    at_cmd_save( "+CDS", 
        1000, 
        NULL,
        NULL,
        NULL,
        gsm_gnss_click_evt_cds_exe 
    );

    at_cmd_save( "+CMS ERROR", 
        1000, 
        gsm_gnss_click_evt_cms_error, 
        gsm_gnss_click_evt_cms_error, 
        gsm_gnss_click_evt_cms_error, 
        gsm_gnss_click_evt_cms_error 
    );
  
    at_cmd_save( "+CGREG", 
        1000, 
        gsm_gnss_click_evt_cgreg_get, 
        gsm_gnss_click_evt_cgreg_get, 
        gsm_gnss_click_evt_cgreg_get, 
        gsm_gnss_click_evt_cgreg_get

    );

    at_cmd_save( "+QGNSSTS", 
        1000, 
        gsm_gnss_click_evt_qgnssts_get, 
        gsm_gnss_click_evt_qgnssts_get, 
        gsm_gnss_click_evt_qgnssts_get, 
        gsm_gnss_click_evt_qgnssts_get
    );

    at_cmd_save( "+QGNSSRD", 
        1000, 
        NULL, 
        gsm_gnss_click_evt_qgnssrd_set, 
        NULL, 
        NULL
    );

    gsm_gnss_click_reset();

    at_cmd( "AT" );

    gsm_gnss_click_wait_ready();
    gsm_gnss_click_init_cmds();
}

/***************************************************************************//**
 *  Configure callbacks.
 */
void gsm_gnss_click_configure_callbacks(
    send_sms_callback_t sms_sent, 
    send_sms_callback_t sms_delivered,
    send_sms_callback_t sms_failed,
    send_sms_callback_t sms_confirmed
)
{
    sms_sent_callback = sms_sent;
    sms_delivered_callback = sms_delivered;
    sms_failed_callback = sms_failed;
    sms_confirmed_callback = sms_confirmed;
}


/***************************************************************************//**
 *  Sends SMS.
 */
void gsm_gnss_click_send_sms(const char* phone_number, const char* msg)
{ 
    char cmd_buffer[CMD_BUFFER_LENGTH];
    log_info("Enter send sms procedure.");
    log_info(phone_number);
    if( strlen(phone_number) > MAX_PHONE_NUMBER_LENGTH )
        return;
    log_info("Phone number is valid");
    if(sms_pending) return;    
    log_info("Formating command...");
    gsm_gnss_click_format_cmgs_cmd(cmd_buffer, phone_number);
    
    log_info("Sending...");
    log_info(msg);

    at_cmd( cmd_buffer );
    at_cmd_addition( msg );
    
    log_info("Sent.");

    sms_pending = true;
    navigation_ready = false;
}

/***************************************************************************//**
 *  AT engine process for receiving URC messages from the ME.
 */
void gsm_gnss_click_process( void )
{
    at_process();
}

/***************************************************************************//**
 *  
 */
void gsm_gnss_click_read_nav( char* url )
{
    // Read GNSS navigation_ready information. Get GLL sentence.
    at_cmd("AT+QGNSSRD=\"NMEA/GLL\"");
    while ( ! navigation_ready )
        at_process();

    strcpy(url, navigation_url_buffer);
}

/*************** END OF FUNCTIONS *********************************************/

/******************************************************************************
* ISRS
*******************************************************************************/
void GSM_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    char s1 = UART2_S1;
    char tmp = UART2_D;

    if(  s1 & ( 1 << 5 )  )
    {
        dev_rx( tmp );
        log_char( tmp );
    }
}
/******************************************************************************/