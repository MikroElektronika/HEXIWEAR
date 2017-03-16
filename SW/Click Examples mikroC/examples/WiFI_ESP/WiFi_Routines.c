//  Configure WiFI ESP Click module responses to parse
#include "OLED_driver.h"
#include "OLED_resources.h"

extern const OK;
extern const NO_CHANGE;
extern const READY;
extern char Get_Response();

extern unsigned char *SSID;
extern unsigned char *password;
extern unsigned char *port;
extern unsigned char ip_address[40];

void WiFI_Configure()
{
  //Reseting WiFi module
  LOG("Resetting Module",5, 15);
  do {
    UART2_Write_Text("AT+RST");
    UART2_Write(0x0D);
    UART2_Write(0x0A);
    Delay_ms(2000);
  } while(Get_Response() != READY);
  Delay_ms(1000);

  // Setting WiFi Mode - station mode
  LOG("Setting Station mode",5, 25);
  do {
    UART2_Write_Text("AT+CWMODE=1");
    UART2_Write(0x0D);
    UART2_Write(0x0A);
    Delay_ms(2000);
  } while(Get_Response() != OK);
  Delay_ms(2000);

  //Enable multIPle connection
  LOG("Enabling Multiple Con",5, 35);
  do {
    UART2_Write_Text("AT+CIPMUX=1");
    UART2_Write(0x0D);
    UART2_Write(0x0A);
    Delay_ms(2000);
  } while(Get_Response() != OK);
  Delay_ms(2000);

  do {
     // AT+CWJAP="SSID","pasword" <CR><LF>
     LOG("Joining Access Point",5, 45);
     UART2_Write_Text("AT+CWJAP=");
     UART2_Write('"');
     UART2_Write_Text(SSID);
     UART2_Write('"');
     UART2_Write(',');
     UART2_Write('"');
     UART2_Write_Text(password);
     UART2_Write('"');
     UART2_Write(0x0D);
     UART2_Write(0x0A);
     Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  do {
     //AT+CWJAP="SSID","pasword" <CR><LF>
     UART2_Write_Text("AT+CWLAP");
     UART2_Write(0x0D);
     UART2_Write(0x0A);
     Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  // Checking WiFi connection status
  do {
    UART2_Write_Text("AT+CIPSTATUS");
    UART2_Write(0x0D);
    UART2_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  do {
    LOG("Setting Server...",5, 55);
    //AT+CIPSERVER=<mode>,<port><CR><LF>
    UART2_Write_Text("AT+CIPSERVER=1,80");
    UART2_Write(0x0D);
    UART2_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  UART2_Write_Text("AT+CIPSTO?");
  UART2_Write(0x0D);
  UART2_Write(0x0A);
  Delay_ms(1000);

  memset(ip_address, 0, 16);


  LOG("Getting STAIP addr",5, 65);
  UART2_Write_Text("AT+CIFSR");
  UART2_Write(0x0D);
  UART2_Write(0x0A);
  Delay_ms(1000);
  while(Get_Response() != OK);
  Delay_ms(1000);
  OLED_SetFont( guiFont_Tahoma_7_Regular, OLED_COLOR_RED, 0 );
  LOG( ip_address + 13, 5, 75);
}