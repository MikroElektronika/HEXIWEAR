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

#ifndef WIFI_3G_IMPL
#define WIFI_3G_IMPL

char* itoa(int i, char b[]);
void Get_IP();
int UART_WriteAtRespOk(char* write);
void UART_Write_AT(char *CMD);

void init_wifi(const int clickPosition);
int configure_wifi(const char *ssid, const char *password);
int connect_server_wifi(const char *addr, const char *port);
int disconnect_server_wifi();
int response_init_wifi(const char *network);
int send_message_wifi (unsigned char message[], int length);

void init_3g(const int clickPosition);
int configure_3g(const char* carrier, const char* username, const char* password);
int connect_server_3g(const char server_addr[], const char port[]);
int disconnect_server_3g();
int response_success_3g(const char *tag);
int send_message_3g(unsigned char message[], int length);

#endif