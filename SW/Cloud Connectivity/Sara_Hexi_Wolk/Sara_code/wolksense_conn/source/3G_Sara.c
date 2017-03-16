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
#include "Defines.h"
#include "3G_Sara.h"
#include "OLED_resources.h"
#include "OLED_driver.h"

#define NULL 0
#define CR           0x0D
#define LF           0x0A
#define RX_BUFF_LEN 1000
#define ONE_SEC 1000
#define TWO_SEC 2000
#define CONNECTION_TYPE "TCP"


sbit SARA_PWR at PTB_PDOR.B11;

char data_ready = 0;
char rx_buff[RX_BUFF_LEN];
unsigned int data_len = 0;

char socket_num[32];

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
            rx_buff[data_len] = 0;
            break;
        }
    default:
        {
            rx_buff[data_len] = tmp;
            data_len++;
            break;
        }
    }
}


void UART_Write_AT(char *CMD) 
{
    UART_Write_Text(CMD);
    UART_Write(CR);
    UART_Write(LF);
}

void reset_buff() 
{
    memset(rx_buff,0,data_len);
    data_ready = 0;
    data_len=0;
}


int response_success(const char *tag)
{
    int result = RESP_FALSE;
    while(!data_ready || !strstr(rx_buff,tag));
    if(strstr(rx_buff,tag))
    {
        result = RESP_TRUE;
    }
    reset_buff();

    return result;
}

int response_init(const char *network)
{
    int result = RESP_FALSE;
    while(!data_ready );
    if(strstr(rx_buff,network))
    {
        result = RESP_TRUE;
    }
    reset_buff();
    
    return result;
}

int response_socket(char *socket_num, char *tag)
{
    char result = RESP_FALSE;
    char *mark_start;
    char *mark_end;
    int size=0;

    while(!data_ready );
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


char* itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char* p = b;
    int shifter;
    if(i < 0)
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

void G3_init ()
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
    UART2_init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT,  &_GPIO_Module_UART2_PD3_2);             // Initialize UART3 module

    EnableInterrupts();
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    UART2_C2 |= 1 << 5;

    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_3);
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19);

    SARA_PWR = 0;
    OSA_TimeDelay( 50 );
    SARA_PWR = 1;
    OSA_TimeDelay( 50 );
    SARA_PWR = 0;

    OSA_TimeDelay(15000);               // wait on power-on
}



int G3_Configure(const char* carrier, const char* username, const char* password)
{
    char user[40] = "AT+UPSD=1,2,\"";
    char pass[40] = "AT+UPSD=1,3,\"";

    strcat(user, username);
    strcat(user, "\"");
    strcat(pass, password);
    strcat(pass, "\"");

    UART_Write_AT("AT+COPS?");
    if(response_init(carrier) == RESP_FALSE)
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

int connect_server(const char server_addr[], const char port[])
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

int send_wifi_message (unsigned char message[], int length)
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

    if(response_success("@") == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    for (i=0;i<length;i++)
    {
        UART_Write(message[i]);
    }

    UART_Write(CR);
    UART_Write(LF);

    if(response_success("OK") == RESP_FALSE)
    {
        OSA_TimeDelay(TWO_SEC);
        return RESP_FALSE;
    }

    return RESP_TRUE;
}


int disconnect_server()
{
    UART_Write_Text("AT+USOCL=");
    
    if(UART_WriteAtRespOk(socket_num) == RESP_FALSE)
    {
        return RESP_FALSE;
    }

    return RESP_TRUE;
}