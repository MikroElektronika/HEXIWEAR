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

#include "mqtt_wolksense_wifi.h"
#include "wifi_3g_impl.h"
#include "mqtt.h"

#define BUFFER_SIZE 256
#define CLIENT_ID "mikroe"
#define RESP_FALSE -1
#define RESP_TRUE 0


int connect_broker_wifi (const char *serial_mqtt, const char *password_mqtt)
{
    int len=0;
    int buflen = 0;
    unsigned char buffer[BUFFER_SIZE] = {0};
    buflen = sizeof(buffer);
    len = MQTTSNSerialize_connect(buffer, buflen, CLIENT_ID, serial_mqtt, password_mqtt);

    if (send_message_wifi(buffer, len) == RESP_FALSE)
    {
        return RESP_FALSE;
    }
    return RESP_TRUE;
}

int publish_broker_wifi (unsigned char message[], const char *topic)
{
    short packetID = 0;
    int len=0;
    unsigned char buffer[BUFFER_SIZE] = {0};
    len = MQTTSNSerialize_Publish(buffer, message, topic, packetID);
    if (send_message_wifi(buffer, len) == RESP_FALSE)
    {
        return RESP_FALSE;
    }

    return RESP_TRUE;
}

int subscribe_broker_wifi (unsigned char topic[])
{
    int len=0;
    unsigned char buffer[BUFFER_SIZE] = {0};
    len = MQTTSNSerialize_Subscribe(buffer, topic, 1,1);
    if (send_message_wifi(buffer, len) == RESP_FALSE)
    {
        return RESP_FALSE;
    }

    return RESP_TRUE;
}