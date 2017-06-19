#ifndef MQTT_CLIENT
#define MQTT_CLIENT

enum MQTTSN_msgTypes
{
        MQTTSN_RES_1, MQTTSN_CONNECT,MQTTSN_CONNACK,MQTTSN_PUBLISH, MQTTSN_PUBACK, 
        MQTTSN_PUBREC, MQTTSN_PUBREL,MQTTSN_PUBCOMP, MQTTSN_SUBSCRIBE, 
        MQTTSN_SUBACK,MQTTSN_UNSUSCRIBE,MQTTSN_UNSUBACK, MQTTSN_PINGREQ,
        MQTTSN_PINGRESQ,MQTTSN_DISCONNECT, MQTTSN_RES_2
};

#define TRUE 1
#define FALSE 0


typedef struct MQTTSNString{
        char cstring[20];
        int lenstring;
} MQTTSNString;

int readInt(unsigned char** pptr);
char readChar(unsigned char** pptr);
void writeChar(unsigned char** pptr, char c);
void writeInt(unsigned char** pptr, int anInt);
int readMQTTSNString(MQTTSNString* mqttstring, unsigned char** pptr, unsigned char* enddata);
void writeCString(unsigned char** pptr, char* string);
void writeMQTTSNString(unsigned char** pptr, MQTTSNString mqttstring);
int MQTTSNSerialize_Publish(char * ptr, char * payload, char * topic, int packetID);
int MQTTSNSerialize_connect(unsigned char* buf, int buflen, char * clientID, const char *username2, const char *password2);
int isConnack(char * buf);
MQTTSNSerialize_Subscribe(char * buf, char * topic, int messageID, int qos);
int isSuback(char * buf, int messageID);
char IsArrived(char * buf);

#endif