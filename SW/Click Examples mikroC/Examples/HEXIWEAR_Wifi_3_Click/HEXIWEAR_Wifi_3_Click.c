/****************************************************************************
* Title                 :   WiFi_3 click
* Filename              :   WiFi_3.c
* Author                :   DJ
* Origin Date           :   14/04/2016
* Notes                 :   HEXIWEAR_WiFi_3 Example
*****************************************************************************/
/**
 * @file WiFi_3.c
 * @brief <h2> HEXIWEAR_WiFi_3 Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * WiFi_3 click board.
 */

/**
 * @page Example Info
 * @date        14 Apr 2016
 * @author      DJ
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page Test Configuration
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12              </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                    </li>
 * <li><b> Oscillator    </b> :      12 MHz external             </li>
 * <li><b> Ext. Modules  </b> :      WiFi_3 Click                 </li>
 * <li><b> Ext. Modules  </b> :      Relay Click                  </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> WiFi_3 click example using HEXIWEAR </h3>
 * @par Place WiFi 3 Click into the mikroBUS socket 1 on docking station.
 * @par Place Relay Click into the mikroBUS socket 2 on docking station.
 * @par Connect to Soft AP (SSID: "HEXIWEAR_WiFi_3").
 * @par Send "R1" or "R2" over TCP, to "192.168.0.1" to toggle corresponding relay.
 *
 * <h3> Relay Features </h3>
 * @par Relay click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/

#include "OLED_driver.h"

// module connections
sbit CH_PD  at PTB_PDOR.B3;
sbit GPIO15 at PTB_PDIR.B19;

sbit REL1  at PTA_PDOR.B11;
sbit REL2  at PTC_PTOR.B3;

extern void WiFI_Configure();

// responses to parse
const OK = 1;
const ERROR = 2;
const NO_CHANGE = 3;
const FAIL = 4;
const READY = 5;
const PRESSED = 6;
const CONNECTED = 7;

char received_data[450], ip_address[16];
unsigned short i, tmp, DataReady;

char state;
char response_rcvd;
char responseID, response = 0;

// Change following information to match your network settings
unsigned char *SSID = "HEXIWEAR_WiFi_3";
unsigned char *password = "123456";
unsigned char *port = "4040";



#define CR           0x0D
#define LF           0x0A
#define NEW_CONFIGURATION

char data_ready = 0;
char rx_buff[1000];
unsigned int data_len = 0;

// Uart Rx interrupt handler
void IRQ_UartHandler() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
   volatile uint8_t foo = UART2_S1;
   uint8_t readData = UART2_D;

   tmp = readData;
   switch(tmp) {
     case LF:
        if(data_len > 1){
          data_ready = 1;
        }
        break;
     case CR:
        rx_buff[data_len] = 0; //but not necessary
        break;
     default:
        rx_buff[data_len] = tmp;
        data_len++;
   }

}


void reset_buff() {
  memset(rx_buff,0,data_len);
  data_ready = 0;
  data_len=0;
}

void UART_Write_AT(char *CMD) {
   UART_Write_Text(CMD);
   UART_Write(0x0D);
   UART_Write(0x0A);
}

char response_success() {
    char result;
    while(!data_ready);
    if((strstr(rx_buff,"OK")) || (strstr(rx_buff,"no change")) || (strstr(rx_buff,"ready"))) {
       result = 1;
    }else result = 0;
    reset_buff();
    return result;
}

void Get_IP() {
   char response_cnt, conn_flg;

     UART_Write_AT("AT+CIFSR");
     while(!data_ready);
     reset_buff();
     while(!data_ready);
     reset_buff();
}


void WiFi3_Init() {
  GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_3);
  GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19);
  
  GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_3);
  GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11);
  
  REL1 = 0;
  REL2 = 0;
  
  CH_PD = 1;                    // Power down line at high level
  GPIO15 = 0;                   // GPIO15 pin at low level on module power-up
  Delay_ms(1000);               // wait five seconds on power-on
}

void WiFI_Configure() {

  OLED_WriteText("Resetting module", 5, 80 );
//  OLED_WriteText("Please wait...", 5, 55 );
  UART_Write_AT("AT+RST");                                                     //Reset module
  while(!response_success());
  delay_ms(1000);

  UART_Write_AT("AT+CWMODE=1");                                                //change the working mode to 1
  while(!response_success());                                                  //wait to respond success
  delay_ms(1000);


  OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
  OLED_WriteText("Set connection", 15, 80 );

  UART_Write_AT("AT+CIPMUX=1");                                                //change the connection mode to 1
  while(!response_success());                                                  //wait to respond succes
  delay_ms(1000);

  UART_Write_AT("AT+CWMODE=2");                                                //change the connection mode to 1
  while(!response_success());                                                  //wait to respond succes
  delay_ms(1000);
  


  OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
  OLED_WriteText("Making SoftAP", 12, 80 );

  //AT+CWJAP="SSID","pasword" <CR><LF>
  UART_Write_Text("AT+CWSAP=");
  UART_Write('"');
  UART_Write_Text(SSID);
  UART_Write('"');
  UART_Write(',');
  UART_Write('"');
  UART_Write_Text(password);
  UART_Write('"');
  UART_Write(',');
  UART_Write('5');
  UART_Write(',');
  UART_Write('0');
  UART_Write(0x0D);
  UART_Write(0x0A);
  while(!response_success());                                                  //wait to respond succes
  delay_ms(1000);

  UART_Write_Text("AT+CIPAP=");                                                // Set IP address
  UART_Write('"');
  UART_Write_Text("192.168.0.1");
  UART_Write('"');
  UART_Write(0x0D);
  UART_Write(0x0A);

  while(!response_success());                                                  //wait to respond succes
  delay_ms(1000);

  OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
  OLED_WriteText("Set server/port", 10, 80 );
  UART_Write_Text("AT+CIPSERVER=1");
  UART_Write(',');
  UART_Write_Text(port);
  UART_Write(0x0D);
  UART_Write(0x0A);
  while(!response_success());                                                  //wait to respond succes
  Delay_ms(1000);

  OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
  OLED_WriteText("Listen...", 30, 80 );

  UART_Write_AT("AT+CIPSTO=30");                                                //change the connection mode to 1
  while(!response_success());                                                  //wait to respond succes
  delay_ms(1000);

}

oled_text_properties_t
    textProperties;

void main() {
  // Initialize variables
  state = 0;
  response_rcvd = 0;
  responseID = 0;
  response = 0;
  tmp = 0;
  i = 0;
  OLED_Init();
  
  OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );

  OLED_DrawImage( WiFi_bmp, 0, 0 );

  UART2_init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT,  &_GPIO_Module_UART2_PD3_2);             // Initialize UART3 module
  UART_Write_Text("Start");
  UART_Write(0x0D);
  UART_Write(0x0A);

  EnableInterrupts();
  NVIC_IntEnable( IVT_INT_UART2_RX_TX );
  UART2_C2 |= 1 << 5;

  // Initialize WiFI module
  WiFi3_Init();
  // Configure WiFI module
  WiFI_Configure();

  while (1)
  {
     while(!data_ready);
     
     if(memcmp("+IPD", &rx_buff[0], 4) == 0)
     {
        if(strcmp("R1", &rx_buff[9]) == 0)
       {
          REL1 = ~REL1;
       }
       else if(strcmp("R2", &rx_buff[9]) == 0)
       {
          REL2 = ~REL2;
       }
     }
     
     reset_buff();
  }
}