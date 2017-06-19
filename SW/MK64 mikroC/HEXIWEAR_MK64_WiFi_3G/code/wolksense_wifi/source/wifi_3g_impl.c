/*   
   Copyright 2017 WolkAbout Technology s.r.o.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "OSA.h"
#include "AT_Commands.h"
#include "wifi_3g_impl.h"
#include "OLED_driver.h"

#define NULL 0
#define CR           0x0D
#define LF           0x0A
#define RX_BUFF_LEN 1000
#define ONE_SEC 1000
#define TWO_SEC 2000
#define CONNECTION_TYPE "TCP"

#define wait_limit 30

// module connections
sbit PWR_SOCKET_1 at PTB_PDOR.B11;
sbit PWR_SOCKET_2 at PTB_PDOR.B19;
sbit PWR_SOCKET_3 at PTB_PDOR.B10;

char data_ready = 0;
char rx_buff[RX_BUFF_LEN];
unsigned int data_len = 0;

char socket_num[32];

void UartHandler(volatile uint8_t foo, uint8_t readData)
{
    unsigned short tmp=0;
    tmp = readData;
    
    switch(tmp)
    {
        case LF:
        {
            if(data_len > 1)
            {
                data_ready = 1;
            }
            break;
        }
        case CR:
        {
            rx_buff[data_len] = 0; //but not necessary
            break;
        }
        default:
        {
            rx_buff[data_len] = tmp;
            data_len++;
        }
    }
}

// Uart3 Rx interrupt handler
void IRQ_UartHandler3() iv IVT_INT_UART3_RX_TX ics ICS_AUTO
{
    volatile uint8_t foo = UART3_S1;
    uint8_t readData = UART3_D;
    
    UartHandler(foo, readData);
}

// Uart2 Rx interrupt handler
void IRQ_UartHandler2() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    volatile uint8_t foo = UART2_S1;
    uint8_t readData = UART2_D;
    
    UartHandler(foo, readData);
}

void reset_buff() 
{
    memset(rx_buff,0,data_len);
    data_ready = 0;
    data_len=0;
}

void UART_Write_AT(char *CMD) 
{
    UART_Write_Text(CMD);
    UART_Write(CR);
    UART_Write(LF);
}

char response_success(const char *rsp_code)
{
    char result;
    int counter;
    while(!data_ready)
    {
        OSA_TimeDelay(20);
        counter++;
        if(counter > wait_limit)
        {
            return 0;
        }
    }
    if(strstr(rx_buff,rsp_code)) 
    {
        result = 1;
    }
    else 
    {
        result = 0;
    }
    reset_buff();
    return result;
}

int g3_response_success(const char *tag)
{
    int result = RESP_FALSE;
    int counter = 0;
    while(!data_ready || !strstr(rx_buff,tag))
    {
        counter++;
        OSA_TimeDelay(100);
        if(counter > 30)
        {
            reset_buff();
            return result;
        }
    }
    if(strstr(rx_buff,tag))
    {
        result = RESP_TRUE;
    }
    reset_buff();

    return result;
}
 

void Get_IP() 
{
    char response_cnt, conn_flg;
    UART_Write_AT(AT_CIFSR);
    while(!data_ready);
    reset_buff();
    while(!data_ready);
    reset_buff();
}

void setPowerSockets(const int clickPosition)
{
    PWR_SOCKET_1 = clickPosition == 1 ? 1 : 0;
    PWR_SOCKET_2 = clickPosition == 2 ? 1 : 0;
    PWR_SOCKET_3 = clickPosition == 3 ? 1 : 0;
}

void recover_3g(const int clickPosition)
{
   if (clickPosition==1)
   {
       PWR_SOCKET_1 = 0;
   }else if (clickPosition==2)
   {
       PWR_SOCKET_2 = 0;
   }else if (clickPosition==3)
   {
       PWR_SOCKET_3 = 0;
   }
}



void init_wifi(const int clickPosition)
{
    if(clickPosition == 1)
    {
        UART2_Init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2);             // Initialize UART2 module
        EnableInterrupts();
        NVIC_IntEnable( IVT_INT_UART2_RX_TX );
        UART2_C2 |= 1 << 5;
        
        GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
        setPowerSockets(clickPosition);
        UART_Write_AT(AT_START);
    }
    else if(clickPosition == 2 || clickPosition == 3)
    {
        UART3_Init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17);             // Initialize UART3 module
        EnableInterrupts();
        NVIC_IntEnable( IVT_INT_UART3_RX_TX );
        UART3_C2 |= 1 << 5;

        if(clickPosition == 2)
        {
            GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19);
        }
        else
        {
            GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_10);
        }
        setPowerSockets(clickPosition);
        UART_Write_AT(AT_START);
    }
    

}

void init_3g (const int clickPosition)
{
    if(clickPosition == 1)
    {
        GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
        UART2_Init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2);             // Initialize UART2 module
        EnableInterrupts();
        NVIC_IntEnable( IVT_INT_UART2_RX_TX );
        UART2_C2 |= 1 << 5;
        PWR_SOCKET_1 = 0;
        OSA_TimeDelay( 200 );
        PWR_SOCKET_1 = 1;
        OSA_TimeDelay( 200 );
        PWR_SOCKET_1 = 0;
        OSA_TimeDelay( 200 );
    }
    else if(clickPosition == 2 || clickPosition == 3)
    {
        UART3_Init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT,  &_GPIO_Module_UART3_PC16_17);             // Initialize UART3 module
        EnableInterrupts();
        NVIC_IntEnable( IVT_INT_UART3_RX_TX );
        UART3_C2 |= 1 << 5;
        if(clickPosition == 2)
        {
            GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 | _GPIO_PINMASK_2 );
            PWR_SOCKET_2 = 0;
            OSA_TimeDelay( 200 );
            PWR_SOCKET_2 = 1;
            OSA_TimeDelay( 200 );
            PWR_SOCKET_2 = 0;
            OSA_TimeDelay( 200 );
        }
        else
        {
            GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_10 | _GPIO_PINMASK_2 );
            PWR_SOCKET_3 = 0;
            OSA_TimeDelay( 200 );
            PWR_SOCKET_3 = 1;
            OSA_TimeDelay( 200 );
            PWR_SOCKET_3 = 0;
            OSA_TimeDelay( 200 );
        }
    }
    setPowerSockets(clickPosition);
    //OSA_TimeDelay(10000);               // wait on power-on
}

void UART_Write_AT_RespOk(char* text)
{
    while (1)
    {
        UART_Write_AT(text);
        if(response_success("OK"))
        {
            return;
        }
        else
        {
            OSA_TimeDelay(TWO_SEC);
        }
    }
}

int UART_WriteAtRespOk(char* write)
{
    UART_Write_AT(write);

    if(response_success("OK") == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

bool UART_Write_AT_RespLimitedWait(char* text)
{
    int counter = 0;
    while (counter < wait_limit)
    {
        UART_Write_AT(text);
        if(response_success("OK"))
        {
            return true;
        }
        else
        {
            counter += 2;
            OSA_TimeDelay(TWO_SEC);
        }
    }
    return false;
}

int configure_wifi(const char *ssid, const char *password)
{
    int counter = 0;
    if(!UART_Write_AT_RespLimitedWait(AT_RST))
    {
        return 0;
    }
    UART_Write_AT_RespOk("AT+CWMODE=1");
    UART_Write_AT_RespOk("AT+CIPMUX=0");

    OSA_TimeDelay(ONE_SEC);

    while (1)
    {
        UART_Write_Text(AT_CWJAP);
        UART_Write('"');
        UART_Write_Text(ssid);
        UART_Write('"');
        UART_Write(',');
        UART_Write('"');
        UART_Write_Text(password);
        UART_Write('"');
        UART_Write(CR);
        UART_Write(LF);
        
        if(response_success("OK"))
        {
            break;
        }
        else
        {
            if(counter > wait_limit)
            {
                return 0;
            }
            counter += 2;
            OSA_TimeDelay(TWO_SEC);
        }

    }

    UART_Write_AT_RespOk("AT+CWJAP=?");
    return 1;
}

char* itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char* p = b;
    int shifter;
    if(i<0)
    {
        *p++ = '-';
        i *= -1;
    }

    shifter = i;
    do
    { //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);

    *p = '\0';
    do
    { //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);

    return b;
}

int connect_server_wifi(const char *addr, const char *port)
{
    UART_Write_Text(AT_CIPSTART);
    UART_Write('"');
    UART_Write_Text(CONNECTION_TYPE);
    UART_Write_Text("\",\"");
    UART_Write_Text(addr);
    UART_Write_Text("\",");
    UART_Write_Text(port);
    UART_Write(CR);
    UART_Write(LF);
    OSA_TimeDelay(ONE_SEC);

    if(!response_success("OK"))
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int response_socket(char *socket_num, char *tag)
{
    char result = RESP_FALSE;
    char *mark_start;
    char *mark_end;
    int size=0;
    int counter = 0;

    while(!data_ready )
    {
        counter++;
        OSA_TimeDelay(100);
        if(counter > 30)
        {
            reset_buff();
            return result;
        }
    }
    if(((strstr(rx_buff,"OK")) || (strstr(rx_buff,"no change")) || (strstr(rx_buff,"ready")) || (strstr(rx_buff,"@"))) && (strstr(rx_buff,tag)))
    {
        mark_start = strstr(rx_buff,":");
        mark_end = strstr(rx_buff,"OK");
        size = mark_end - mark_start;
        memcpy(socket_num, mark_start+1, size-1);
        result = RESP_TRUE;
    }

    reset_buff();

    return result;
}

int connect_server_3g(const char server_addr[], const char port[])
{
    char addr[50] = ",\"";
    strcat(addr, server_addr);
    strcat(addr, "\",");
    strcat(addr, port);

    memset(socket_num, 0 , 32);
    OSA_TimeDelay(ONE_SEC);
    UART_Write_AT("AT+USOCR=6");
    OSA_TimeDelay(ONE_SEC);

    if(response_socket(socket_num, "USOCR:") == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }
    UART_Write_Text("AT+USOCO=");
    UART_Write_Text(socket_num);

    if(UART_WriteAtRespOk(addr) == RESP_FALSE)
    {
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int send_message_wifi (unsigned char message[], int length)
{
    int i =0;
    unsigned char len_str[16] = {0};
    char *t_ptr =  itoa(length, len_str);

    UART_Write_Text(AT_CIPSEND);
    UART_Write_Text(t_ptr);
    UART_Write(CR);
    UART_Write(LF);
    OSA_TimeDelay(ONE_SEC);

    if(!response_success(">"))
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    OSA_TimeDelay(ONE_SEC);
    for (i-0;i<length;i++)
    {
        UART_Write(message[i]);
    }

    UART_Write(CR);
    UART_Write(LF);
    OSA_TimeDelay(ONE_SEC);
    if(!response_success("OK"))
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int disconnect_server_wifi()
{
    UART_Write_Text(AT_CIPCLOSE);
    UART_Write(CR);
    UART_Write(LF);
    OSA_TimeDelay(ONE_SEC);

    if(!response_success("OK"))
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int disconnect_server_3g()
{
    UART_Write_Text("AT+USOCL=");

    if(UART_WriteAtRespOk(socket_num) == RESP_FALSE)
    {
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int wifi_response_init(const char *network)
{
    int result = RESP_FALSE;
    int counter = 0;
    while(!data_ready )
    {
        counter++;
        OSA_TimeDelay(100);
        if(counter > 30)
        {
            reset_buff();
            return result;
        }
    }
    if(strstr(rx_buff,network))
    {
        result = RESP_TRUE;
    }
    reset_buff();

    return result;
}

int send_message_3g (unsigned char message[], int length)
{
    int i =0;
    unsigned char len_str[16] = {0};
    char *t_ptr =  itoa(length, len_str);

    UART_Write_Text("AT+USOWR=");
    UART_Write_Text(socket_num);
    UART_Write_Text(",");
    UART_Write_Text(t_ptr);
    UART_Write(CR);
    UART_Write(LF);

    if(g3_response_success("@") == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }
    
     OSA_TimeDelay(ONE_SEC);

    for (i=0;i<length;i++)
    {
        UART_Write(message[i]);
    }

    UART_Write(CR);
    UART_Write(LF);

         OSA_TimeDelay(ONE_SEC);
    if(g3_response_success("OK") == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int configure_3g(const char* g3_carrier, const char* g3_username, const char* g3_password)
{
    char user[64] = "AT+UPSD=1,2,\"";
    char pass[64] = "AT+UPSD=1,3,\"";

    strcat(user, g3_username);
    strcat(user, "\"");
    strcat(pass, g3_password);
    strcat(pass, "\"");

//    if(!UART_Write_AT_RespLimitedWait("AT+COPS?"))
//    {
//        return 0;
//    }
    UART_Write_AT("AT+COPS?");
    OSA_TimeDelay(5000);
    if(wifi_response_init(g3_carrier) == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    if(UART_WriteAtRespOk("AT+CGDCONT=1,\"IP\",\"internet\"") == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk("AT+CGEQREQ=1,3,64,64,,,0,320,\"1E4\",\"1E5\",1,,3") == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk("AT+UPSND=1,8") == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk("AT+UPSD=1,1,\"internet\"") == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk(user) == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk(pass) == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk("AT+UPSD=1,7,\"0.0.0.0\"") == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk("AT+UPSDA=1,1") == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    if(UART_WriteAtRespOk("AT+UPSDA=1,3") == RESP_FALSE)
    {
        return RESP_FALSE;
    }

    return RESP_TRUE;
}