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
#include "WiFi_esp8266.h"
#include "OLED_resources.h"
#include "OLED_driver.h"

#define NULL 0
#define CR           0x0D
#define LF           0x0A
#define RX_BUFF_LEN 1000
#define ONE_SEC 1000
#define TWO_SEC 2000
#define CONNECTION_TYPE "TCP"

// module connections
sbit CH_PD  at PTB_PDOR.B3;
sbit GPIO15 at PTB_PDIR.B11;

char data_ready = 0;
char rx_buff[RX_BUFF_LEN];
unsigned int data_len = 0;

// Uart Rx interrupt handler
void IRQ_UartHandler() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    unsigned short tmp=0;
    volatile uint8_t foo = UART2_S1;
    uint8_t readData = UART2_D;

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
    while(!data_ready );
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

void Get_IP() 
{
    char response_cnt, conn_flg;
    UART_Write_AT(AT_CIFSR);
    while(!data_ready);
    reset_buff();
    while(!data_ready);
    reset_buff();
}


void WiFi3_Init() 
{
    UART2_init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT,  &_GPIO_Module_UART2_PD3_2);             // Initialize UART3 module
    UART_Write_AT(AT_START);

    EnableInterrupts();
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    UART2_C2 |= 1 << 5;

    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_3);
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19);

    CH_PD = 1;                    // Power down line at high level
    GPIO15 = 0;                   // GPIO15 pin at low level on module power-up
    OSA_TimeDelay(5 * ONE_SEC);          // wait five seconds on power-on
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

void WiFI_Configure(const char *ssid, const char *password) 
{
    UART_Write_AT_RespOk(AT_RST);
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
            OSA_TimeDelay(TWO_SEC);
        }
    }

    UART_Write_AT_RespOk("AT+CWJAP=?");
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

int connect_server(const char *addr, const char *port)
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

int send_wifi_message (unsigned char message[], int length)
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

int disconnect_server()
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