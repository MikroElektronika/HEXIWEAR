/*******************************************************************************
 * Copyright (c) 2014 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *    Sergio R. Caprile - "commonalization" from prior samples and/or documentation extension
 *    Luca Massarelli (associated with Nergal Consulting S.R.L. - porting the library in mikroC
 *******************************************************************************/

/*these implementation is very simple it can only connect to the broker, subscribe and publish*/

#include "mqtt/include/mqtt.h"
#include <string.h>

char flag = 0;                   //set these flag according to your preferences
#define reserved flag.f0
#define setclean flag.f1
#define willflag flag.f2
#define willQOS_lsb flag.f3
#define willQOS_msb flag.f4
#define willretain flag.f5
#define ISpassword flag.f6
#define ISusername flag.f7

#define keepalive 60
//#define username "0117GD0073E97WXP"
//#define password "qcj2t44yk3m7hy3h"

/**
 * Calculates an integer from two bytes read from the input buffer
 * @param pptr pointer to the input buffer - incremented by the number of bytes used & returned
 * @return the integer value calculated
 */
int readInt(unsigned char** pptr)
{
        unsigned char* ptr = *pptr;
        int len = 256*((unsigned char)(*ptr)) + (unsigned char)(*(ptr+1));
        *pptr += 2;
        return len;
}


/**
 * Reads one character from the input buffer.
 * @param pptr pointer to the input buffer - incremented by the number of bytes used & returned
 * @return the character read
 */
char readChar(unsigned char** pptr)
{
        char c = **pptr;
        (*pptr)++;
        return c;
}


/**
 * Writes one character to an output buffer.
 * @param pptr pointer to the output buffer - incremented by the number of bytes used & returned
 * @param c the character to write
 */
void writeChar(unsigned char** pptr, char c)
{
        **pptr = (unsigned char)c;
        (*pptr)++;
}

/**
 * Writes an integer as 2 bytes to an output buffer.
 * @param pptr pointer to the output buffer - incremented by the number of bytes used & returned
 * @param anInt the integer to write: 0 to 65535
 */
void writeInt(unsigned char** pptr, int anInt)
{
        **pptr = (unsigned char)(anInt / 256);
        (*pptr)++;
        **pptr = (unsigned char)(anInt % 256);
        (*pptr)++;
}


/**
 * Writes a "UTF" string to an output buffer.  Converts C string to length-delimited.
 * @param pptr pointer to the output buffer - incremented by the number of bytes used & returned
 * @param string the C string to write
 */


void writeMQTTSNString(unsigned char** pptr, MQTTSNString s){
     int len;
     /*if (s.lenstring != 0) {
        len = s.lenstring;
     } else {
        len = strlen(s.cstring);
     } */
     memcpy(*pptr, s.cstring, s.lenstring);
     *pptr += s.lenstring;
}

/*Create the packet to send to connect to the broker*/


int MQTTSNSerialize_connect(unsigned char* buf, int buflen, char * clientID, const char *username, const char *password)
{
        unsigned char *ptr = buf;
        int len = 0;
        int rc = -1;
        
        ISpassword = TRUE;  /*here I use username and password*/
        ISusername = TRUE;
        
        len = 14 + strlen(clientID);
        if(ISpassword == TRUE) {
                      len += 2 + strlen(password);
        }
        if(ISusername == TRUE) {
                      len += 2 + strlen(username);
        }
        if (len > buflen) {
                rc = 0;
                return(rc);
        }

        writeChar(&ptr, (MQTTSN_CONNECT + 0x0F));      /* write message type */
        writeChar(&ptr, len);
        writeChar(&ptr, 0x00);
        writeChar(&ptr, 0x06);
        writeChar(&ptr, 'M');
        writeChar(&ptr, 'Q');
        writeChar(&ptr, 'I');
        writeChar(&ptr, 's');
        writeChar(&ptr, 'd');
        writeChar(&ptr, 'p');
        writeChar(&ptr, 0x03);
        writeChar(&ptr, flag);
        writeInt(&ptr, keepalive);
        writeInt(&ptr,strlen(clientID)); //clientID LSB
        memcpy(ptr, clientID, strlen(clientID));
        ptr += strlen(clientID);
        if(ISusername == TRUE) {
                      writeInt(&ptr, strlen(username));
                      memcpy(ptr, username, strlen(username));
                      ptr += strlen(username);
        }
        if(ISpassword == TRUE) {
                      writeInt(&ptr, strlen(password));
                      memcpy(ptr, password, strlen(password));
                      ptr += strlen(password);
        }
        rc = ptr - buf;
        return rc;
}

/*check if the broker accept the connection*/

int isConnack(char * buf) {
        if(*buf == 0x20 && *(buf + 3) == 0) {
                return(0);
        } else {
                return(1);
        }
}

/*create the packet to send to publisch something*/

int MQTTSNSerialize_Publish(char * buf, char * payload, char * topic, int packetID) {

     int publen = 0;
     int len = 0;
     char * ptr = buf;

     writeChar(&ptr, (MQTTSN_PUBLISH + 0x2D));
     publen = 2 + strlen(topic) + strlen(payload);
     writeChar(&ptr, publen);
     len = strlen(topic);
     writeInt(&ptr, len);
     memcpy(ptr, topic, len);
     ptr += len;
     //writeInt(&ptr, packetID);
     len = strlen(payload);
     //writeInt(&ptr, len);
     memcpy(ptr, payload, len);
     ptr += len;
     
     return(ptr - buf);

}

/*create the packet to send to subscribe to some topic*/

int MQTTSNSerialize_Subscribe(char * buf, char * topic, int messageID, int qos) {

     int sublen = 0;
     int len = 0;
     char * ptr = buf;

     writeChar(&ptr, 0x82);
     sublen = 5 + strlen(topic);
     writeChar(&ptr, sublen);
     writeInt(&ptr, messageID);
     len = strlen(topic);
     writeInt(&ptr, len);
     memcpy(ptr, topic, len);
     ptr += len;
     writeChar(&ptr, qos);

     return(ptr - buf);

}

/*check if there is some messages arrived*/

char IsArrived(char * buf) {
     int i;
     if(*buf == 0x30) {
             return(1);
     }
     return(0);
}