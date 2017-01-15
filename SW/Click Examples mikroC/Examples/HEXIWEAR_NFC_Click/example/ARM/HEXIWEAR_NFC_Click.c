/*******************************************************************************
* Title                 :   System Initialization
* Filename              :   sys_init.c
* Author                :   JWB
* Origin Date           :   04/23/2012
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  XX/XX/XX    XXXXXXXXXXX         JWB      Module Created.
*
*******************************************************************************/
/** @file XXX.c
 *  @brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "nfc.h"

#include "OLED_driver.h"
#include "resources.h"

#ifdef CARDEMU_SUPPORT
#include "T4T_NDEF_EMU.h"
#endif
#ifdef P2P_SUPPORT
#include "P2P_NDEF.h"
#endif
#ifdef RW_SUPPORT
#include "RW_NDEF.h"
#endif

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#if defined P2P_SUPPORT || defined RW_SUPPORT
#define NDEF_PRINT_URI_CODE(x) {    switch(x)                                                                \
                                    {                \
                                    case 1: break;   \
                                    case 2: break;   \
                                    case 3: break;   \
                                    case 4: break;   \
                                    case 5: break;   \
                                    case 6: break;   \
                                    default: break;  \
                                    }                \
                               }
#endif

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit NFC_RST_PIN at PTB_PDOR.B11;
sbit NFC_INT_PIN at PTB_PDIR.B13;


#if defined P2P_SUPPORT || defined CARDEMU_SUPPORT
const char NDEF_RECORD[] = { 0xD1,   // MB/ME/CF/1/IL/TNF
                             0x01,   // TYPE LENGTH
                             0x07,   // PAYLOAD LENTGH
                             'T',    // TYPE
                             0x02,   // Status
                             'e', 'n', // Language
                             'T', 'e', 's', 't'
                           };
#endif

uint8_t discovery_technologies[] = {  MODE_POLL | TECH_PASSIVE_NFCA
                                      , MODE_POLL | TECH_PASSIVE_NFCB
                                      , MODE_POLL | TECH_PASSIVE_NFCF
#ifdef P2P_SUPPORT
                                      , MODE_POLL | TECH_ACTIVE_NFCF
#endif
                                      , MODE_LISTEN | TECH_PASSIVE_NFCA
#ifdef P2P_SUPPORT
                                      , MODE_LISTEN | TECH_PASSIVE_NFCF
                                      , MODE_LISTEN | TECH_ACTIVE_NFCA
                                      , MODE_LISTEN | TECH_ACTIVE_NFCF
#endif
                                   };

bool volatile incoming_flag;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#if defined P2P_SUPPORT || defined RW_SUPPORT
char *auth( uint8_t x );
char *encrypt( uint8_t x );
void ndef_pull_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size );
#endif
#if defined P2P_SUPPORT || defined CARDEMU_SUPPORT
void ndef_push_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size );
#endif
void mi_fare_scenario( void );
void init_timer2( void );
int system_init( void );
void process_radio( nfc_interface_t *radio );

/******************************************************************************
* Function Definitions
*******************************************************************************/
#if defined P2P_SUPPORT || defined RW_SUPPORT
char *auth( uint8_t x )
{
    switch( x )
    {
        case 0x01:
            return "Open";
        case 0x02:
            return "WPA-Personal";
        case 0x04:
            return "Shared";
        case 0x08:
            return "WPA-Entreprise";
        case 0x10:
            return "WPA2-Entreprise";
        case 0x20:
            return "WPA2-Personal";
        default:
            return "unknown";
    }
}

char *encrypt( uint8_t x )
{
    switch( x )
    {
        case 0x01:
            return "None";
        case 0x02:
            return "WEP";
        case 0x04:
            return "TKIP";
        case 0x08:
            return "AES";
        case 0x10:
            return "AES/TKIP";
        default:
            return "unknown";
    }
}

volatile uint8_t index;

void ndef_pull_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size )
{
    /* The callback only print out the received message */
    char tmp_txt[80];
    //UART_Write_Text( "--- NDEF Record received:\n" );

    /* Only short, not fragmented and well-known type records are supported here */
    if( p_ndef_record[0] == 0xD1 )
    {
        switch( p_ndef_record[3] )
        {
            case 'T':
                p_ndef_record[7 + p_ndef_record[2]] = '\0';
                sprinti( tmp_txt,
                         "   Text record (language = %c%c): %s\n",
                         p_ndef_record[5],
                         p_ndef_record[6],
                         &p_ndef_record[7] );
                //UART_Write_Text( tmp_txt );

                OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
                OLED_WriteText("Text record:", 4, 55);
                OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
                OLED_WriteText(&p_ndef_record[7], 4, 70);
                
                break;

            case 'U':
                //UART_Write_Text( "   URI record: " );
                NDEF_PRINT_URI_CODE( p_ndef_record[4] )
                p_ndef_record[4 + p_ndef_record[2]] = '\0';
                sprinti( tmp_txt, "%s\n", &p_ndef_record[5] );
                //UART_Write_Text( tmp_txt );
                
                OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
                OLED_WriteText("URI record:", 4, 55);
                OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
                OLED_WriteText(tmp_txt, 4, 70);
                
                break;

            default:
                OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
                OLED_WriteText("Unsupported", 4, 55);
                //UART_Write_Text( "   Unsupported NDEF record, only 'T' and 'U' types are supported\n" );
                break;
        }
    }
    
    /*
    // Only short, not fragmented and WIFI handover type are supported here
    else if( ( p_ndef_record[0] == 0xD2 ) &&
             ( memcmp( &p_ndef_record[3], "application/vnd.wfa.wsc",
                       sizeof( "application/vnd.wfa.wsc" ) ) ) )
    {
        uint8_t i;
        
        index = 26;

        UART_Write_Text( "--- Received WIFI credentials:\n" );

        if( ( p_ndef_record[index] == 0x10 ) &&
                ( p_ndef_record[index + 1] == 0x0e ) )
            index += 4;

        while( index < ndef_record_size )
        {
            if( p_ndef_record[index] == 0x10 )
            {
                if ( p_ndef_record[index + 1] == 0x45 )
                {
                    UART_Write_Text ( "- SSID = " );

                    for( i = 0; i < p_ndef_record[index + 3]; i++ )
                    {
                        sprinti( tmp_txt, "%c", p_ndef_record[index + 4 + i] );
                        UART_Write_Text( tmp_txt );
                    }
                    UART_Write_Text ( "\n" );
                }
                else if ( p_ndef_record[index + 1] == 0x03 )
                {
                    sprinti( tmp_txt, "- Authenticate Type = %s\n",
                             auth( p_ndef_record[index + 5] ) );
                    UART_Write_Text( tmp_txt );
                }
                else if( p_ndef_record[index + 1] == 0x0f )
                {
                    sprinti( tmp_txt, "- Encryption Type = %s\n",
                             encrypt( p_ndef_record[index + 5] ) );
                    UART_Write_Text( tmp_txt );
                }
                else if ( p_ndef_record[index + 1] == 0x27 )
                {
                    UART_Write_Text ( "- Network key = " );

                    for( i = 0; i < p_ndef_record[index + 3]; i++ )
                        UART_Write_Text( "#" );
                    UART_Write_Text ( "\n" );
                }

                index += 4 + p_ndef_record[index + 3];
            }
            else
                continue;
        }
    }
    */
    else
        ;
        //UART_Write_Text( "   Unsupported NDEF record, cannot parse\n" );

    //UART_Write_Text( "\n" );
}
#endif

#if defined P2P_SUPPORT || defined CARDEMU_SUPPORT
void ndef_push_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size )
{
  ;//UART_Write_Text( "--- NDEF Record sent\n\n" );
}
#endif


void mi_fare_scenario()
{
    bool status;
    uint8_t i;
    uint8_t resp[256];
    uint8_t resp_size;
    /* Authenticate sector 1 with generic keys */
    uint8_t auth[] = {0x40, 0x01, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    /* Read block 4 */
    uint8_t read[] = {0x10, 0x30, 0x04};
    /* Write block 4 */
    uint8_t write_part1[] = {0x10, 0xA0, 0x04};
    uint8_t write_part2[] =
    {
        0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99,
        0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
    };
    char tmp_txt[80];

    /* Authenticate */
    status = nfc_reader_tag_cmd( auth, sizeof( auth ), resp, &resp_size );

    if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
    {
        sprinti( tmp_txt, " Authenticate sector %d failed with error 0x%02x\n",
                 auth[1], resp[resp_size - 1] );
        //UART_Write_Text( tmp_txt );
        return;
    }
    sprinti( tmp_txt, " Authenticate sector %d succeed\n", auth[1] );
    //UART_Write_Text( tmp_txt );

    /* Read block */
    status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );

    if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
    {
        sprinti( tmp_txt, " Read block %d failed with error 0x%02x\n",
                 read[2], resp[resp_size - 1] );
        //UART_Write_Text( tmp_txt );
        return;
    }

    sprinti( tmp_txt, " Read block %d: ", read[2] );
    //UART_Write_Text( tmp_txt );

    for( i = 0; i < resp_size - 2; i++ )
    {
        sprinti( tmp_txt, "0x%02X ", resp[i + 1] );
        //UART_Write_Text( tmp_txt );
    }
    //UART_Write_Text( "\n" );

    /* Write block */
    status = nfc_reader_tag_cmd( write_part1, sizeof( write_part1 ), resp,
                                 &resp_size );

    if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
    {
        sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
                 write_part1[2], resp[resp_size - 1] );
        //UART_Write_Text( tmp_txt );
        return;
    }
    status = nfc_reader_tag_cmd( write_part2, sizeof( write_part2 ), resp,
                                 &resp_size );

    if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
    {
        sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
                 write_part1[2],
                 resp[resp_size - 1] );
        //UART_Write_Text( tmp_txt );
        return;
    }

    sprinti( tmp_txt, " Block %d written\n", write_part1[2] );
    //UART_Write_Text( tmp_txt );
    /* Read block */
    status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );

    if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
    {
        sprinti( tmp_txt, " Read failed with error 0x%02x\n", resp[resp_size - 1] );
        //UART_Write_Text( tmp_txt );
        return;
    }

    sprinti( tmp_txt, " Read block %d: ", read[2] );
    //UART_Write_Text( tmp_txt );

    for( i = 0; i < resp_size - 2; i++ )
    {
        sprinti( tmp_txt, "0x%02X ", resp[i + 1] );
        //UART_Write_Text( tmp_txt );
    }
    //UART_Write_Text( "\n" );

    /* Perform presence check */
    while( 1 )
    {
        Delay_ms( 500 );
        status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );

        if( ( status == 1 ) || ( resp[resp_size - 1] == 0xb2 ) )
            break;
    }
}

void init_ExtPinInt()
{
    GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);
    NVIC_IntEnable( IVT_INT_PORTB );
    // enable interrupt at PTB8 on either edge
    PORTB_PCR13 &= 0xFFF0FFFF;
    PORTB_PCR13 |= (((unsigned long)0x9) << 16);
}

//Place/Copy this part in declaration section
void init_timer2()
{
    // enable clock
        LPTMR_bit = 1;

        /* LPTMR prescaler configure */
        LPTMR0_PSR = 0XD;
        
        /* Working Mode configure */
        LPTMR0_CSR = 0X40;

    /* LPTMR interrupt */
        TIE_LPTMR0_CSR_bit = 1;
    NVIC_IntEnable( IVT_INT_LPTimer );
    
    // set the period in [us]
        LPTMR0_CMR = 10;

        // enable the timer
        TEN_LPTMR0_CSR_bit = 1;

}

int system_init()
{
    uint8_t mode = 0;

    OLED_Init();
    OLED_DrawImage(NFC_bmp, 0, 0);

    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
    
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11);

    // UART
    //UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
    
    Delay_ms( 100 );
    
    //UART_Write_Text( "Start Testing Loop\r\n" );
    
    OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
    OLED_DrawBox(0, 80, 96, 15, 0);
    OLED_WriteText("Start Test Loop", 4, 80);

    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );

    Delay_ms( 100 );

//    RCC_APB2ENR.AFIOEN = 1;              // Enable clock for alternate pin functions
//    AFIO_EXTICR3 = 0x0300;
//    EXTI_RTSR |= ( 1 << TR10 );          // Set interrupt on Rising edge
//    EXTI_IMR |= ( 1 << MR10 );           // Set mask
//    NVIC_IntEnable( IVT_INT_EXTI15_10 ); // Enable External interrupt

      init_ExtPinInt();
      init_timer2();
      EnableInterrupts();

#ifdef CARDEMU_SUPPORT
    /* Register NDEF message to be sent to remote reader */
    t4t_ndef_emu_set_record( ( uint8_t * )NDEF_RECORD, sizeof( NDEF_RECORD ),
                             ( void * )ndef_push_cb );
#endif

#ifdef P2P_SUPPORT
    /* Register NDEF message to be sent to remote peer */
    p2p_ndef_set_record( ( uint8_t * )NDEF_RECORD, sizeof( NDEF_RECORD ),
                         ( void * )ndef_push_cb );

    /* Register callback for reception of NDEF message from remote peer */
    p2p_ndef_register_pull_callback( ( void * )ndef_pull_cb );
#endif

#ifdef RW_SUPPORT
    /* Register callback for reception of NDEF message from remote cards */
    rw_ndef_register_pull_callback( ( void * )ndef_pull_cb );
#endif
    /* Set NXPNCI in all modes */
#ifdef CARDEMU_SUPPORT
    mode |= NFC_MODE_CARDEMU;
#endif
#ifdef P2P_SUPPORT
    mode |= NFC_MODE_P2P;
#endif
#ifdef RW_SUPPORT
    mode |= NFC_MODE_RW;
#endif

    /* Open connection to NXPNCI device */
    if( nfc_init( NFC_I2C_SLAVE ) )
    {
        //UART_Write_Text( "Error: cannot connect to NFC click\r\n" );
        OLED_DrawBox(0, 80, 96, 15, 0);
        OLED_WriteText("Error!", 4, 80);
        return -1;
    }
    else if( nfc_configure( mode ) )
    {
        //UART_Write_Text( "Error: cannot configure NFC click\r\n" );
        OLED_DrawBox(0, 80, 96, 15, 0);
        OLED_WriteText("Error!", 4, 80);
        return -1;
    }
    else if( nfc_start_discovery( discovery_technologies, sizeof( discovery_technologies ) ) ) {
        //UART_Write_Text( "Error: cannot start discovery\n" );
        OLED_DrawBox(0, 80, 96, 15, 0);
        OLED_WriteText("Error!", 4, 80);
        return -1;
    }

    //UART_Write_Text( "\r\nNFC Successfully Initialized\r\n" );
    OLED_DrawBox(0, 80, 96, 15, 0);
    OLED_WriteText("Success!", 4, 80);
    incoming_flag = false;
    return 0;
}

void process_radio( nfc_interface_t *radio )
{
    char tmp_txt[80];
#ifdef CARDEMU_SUPPORT
    if( ( radio->interface == INTF_ISODEP ) &&
            ( radio->mode_tech == ( MODE_LISTEN | TECH_PASSIVE_NFCA ) ) )
    {
        //UART_Write_Text( " - LISTEN MODE: Activated from remote Reader\r\n" );
        nfc_process( NFC_MODE_CARDEMU, radio );
        //UART_Write_Text( "READER DISCONNECTED\r\n" );
    }
    else
#endif
#ifdef P2P_SUPPORT
        if( radio->interface == INTF_NFCDEP )
        {
            /* Is target mode ? */
            if( ( radio->mode_tech & MODE_LISTEN ) == MODE_LISTEN )
                ;//UART_Write_Text( " - P2P TARGET MODE: Activated from remote Initiator\r\n" );
            else
                ;//UART_Write_Text( " - P2P INITIATOR MODE: Remote Target activated\r\n" );

            nfc_process( NFC_MODE_P2P, radio );
            //UART_Write_Text( "PEER LOST\r\n" );
        }
        else
#endif
#ifdef RW_SUPPORT
            if( ( radio->mode_tech & MODE_MASK ) == MODE_POLL )
            {
                /* Is card detected MIFARE ?*/
                if( radio->protocol == PROT_MIFARE )
                {
                    //UART_Write_Text( " - POLL MODE: Remote MIFARE card activated\r\n" );
                    
//                    OLED_DrawBox(0, 0, 96, 96, 0);
//                    OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
//                    OLED_DrawBox(0, 80, 96, 15, 0);
//                    OLED_WriteText("Detected:", 4, 10);
//                    OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
//                    OLED_DrawBox(0, 80, 96, 15, 0);
//                    OLED_WriteText("MIFARE card", 4, 25);

                    //mi_fare_scenario();
                    /* Restart discovery loop */
                    
                    OLED_DrawBox(0, 80, 96, 15, 0);
                    OLED_WriteText("MIFARE card", 4, 80);
                    
                    nfc_restart_discovery();
                    Delay_ms(1000);
                }
                /* Is Undetermined target ?*/
                else if( ( radio->protocol != PROT_NFCDEP )
                         && ( radio->interface != INTF_UNDETERMINED ) )
                {
                    sprinti( tmp_txt, " - POLL MODE: Remote T%dT activated\r\n", radio->protocol );
                    //UART_Write_Text( tmp_txt );
                    
                    sprinti( tmp_txt, "Type %d Tag", radio->protocol );

                    OLED_DrawBox(0, 0, 96, 96, 0);
                    OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
                    OLED_DrawBox(0, 80, 96, 15, 0);
                    OLED_WriteText("Detected:", 4, 10);
                    OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
                    OLED_DrawBox(0, 80, 96, 15, 0);
                    OLED_DrawBox(0, 80, 96, 15, 0);
                    OLED_WriteText(tmp_txt, 4, 25);

                    nfc_process( NFC_MODE_RW, radio );
                    //Delay_ms(1000);
                }
                else
                {
                    //UART_Write_Text( " - POLL MODE: Undetermined target\r\n" );

//                    OLED_DrawBox(0, 0, 96, 96, 0);
//                    OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
//                    OLED_DrawBox(0, 80, 96, 15, 0);
//                    OLED_WriteText("Detected:", 4, 10);
//                    OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
//                    OLED_DrawBox(0, 80, 96, 15, 0);
//                    OLED_WriteText("Undetermined", 4, 25);
                    
                    OLED_DrawBox(0, 80, 96, 15, 0);
                    OLED_WriteText("Unknown dev", 4, 80);
                    
                    /* Restart discovery loop */
                    nfc_stop_discovery();
                    nfc_start_discovery( discovery_technologies, sizeof( discovery_technologies ) );
                    Delay_ms(1000);
                }

                //UART_Write_Text( "CARD DISCONNECTED\r\n" );
                OLED_DrawImage(NFC_bmp, 0, 0);
                OLED_DrawBox(0, 80, 96, 15, 0);
                OLED_WriteText("Wait for device", 4, 80);
            }
            else
#endif
            {
                //UART_Write_Text( "WRONG DISCOVERY\r\n" );
            }

}

void main()
{
    nfc_interface_t r_interface;

    if( system_init() )
        while( 1 );

    //UART_Write_Text( "\r\nWAITING FOR DEVICE DISCOVERY\r\n" );
    OLED_DrawBox(0, 80, 96, 15, 0);
    OLED_WriteText("Wait for device", 4, 80);
    
    while( 1 )
    {

        if( incoming_flag )
        {
            //UART_Write_Text( "Device Discovered\r\n" );
            nfc_wait_for_discovery_notification( &r_interface );
            process_radio( &r_interface );
            incoming_flag = false;
        }

    }
}


void card_rx_ISR() iv IVT_INT_PORTB ics ICS_AUTO
{
    PORTB_ISFR = 0xFFFFFFFF;
    nfc_rx_ready();
    incoming_flag = true;
}


void timer2_interrupt() iv IVT_INT_LPTimer
{
    LPTMR0_CSR |= 0x80;
    PTA_PDOR.B11 = ~PTA_PDOR.B11;
    asm nop;
    nfc_timer_tick();
}


/*************** END OF FUNCTIONS ***************************************************************************/