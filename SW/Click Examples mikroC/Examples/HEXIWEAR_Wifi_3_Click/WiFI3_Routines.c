
//  Configure WiFI3-Click module responses to parse
#include "OLED_driver.h"
extern const OK;
extern const NO_CHANGE;
extern const READY;
extern char Get_Response();

extern unsigned char *SSID;
extern unsigned char *password;
extern unsigned char *port;
extern unsigned char ip_address[16];

void WiFI_Configure() {
  OLED_WriteText("Resetting module", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );

  do {
    UART_Write_Text("AT+RST");
    UART_Write(0x0D);
    UART_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != READY);
  Delay_ms(1000);

  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("Setting STA mode", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );
  do {
    UART_Write_Text("AT+CWMODE=1");
    UART_Write(0x0D);
    UART_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("Set connection", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );
  do {
    UART_Write_Text("AT+CIPMUX=1");
    UART_Write(0x0D);
    UART_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("Set connection2", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );
  do {
    UART_Write_Text("AT+CWMODE=2");
    UART_Write(0x0D);
    UART_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("Making SoftAP", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );
  do {
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
     Delay_ms(1000);
  } while(Get_Response() != OK);

  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("made SAP!", 20, 40 );
  OLED_WriteText("Getting address", 20, 55 );

  
  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("Set server/port", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );
  do {
    //AT+CIPSERVER=<mode>,<port><CR><LF>
    UART_Write_Text("AT+CIPSERVER=1");
    UART_Write(',');
    UART_Write_Text(port);
    UART_Write(0x0D);
    UART_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);
  
  //memset(ip_address, 0, 16);
  do {
    UART_Write_Text("AT+CIFSR");
    UART_Write(0x0D);
    UART_Write(0x0A);
    Delay_ms(1000);
  } while(Get_Response() != OK);
  Delay_ms(1000);

  //Lcd_Cmd(_LCD_CLEAR);
  //Lcd_Out(1,1,"IP address :    ");
  //Lcd_Out(2,1,ip_address);
  Delay_ms(1000);
  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_WriteText("Type:", 20, 40 );
  OLED_WriteText("Please wait...", 20, 55 );
  //Lcd_Out(2,1,ip_address);
  do {
  UART_Write_Text("AT+CIPSTO=30");
  UART_Write(0x0D);
  UART_Write(0x0A);
  Delay_ms(1000);
        // AT+CIPSTO=30
  } while(Get_Response() != OK);
  Delay_ms(1000);

}