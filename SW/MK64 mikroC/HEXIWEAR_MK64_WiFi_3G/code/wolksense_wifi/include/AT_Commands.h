#ifndef AT_COMMANDS
#define AT_COMMANDS

const char AT_START[] = "Start";
const char AT_RST[] = "AT+RST";
const char AT_CWMODE[] = "AT+CWMODE=";
const char AT_CWJAP[] = "AT+CWJAP=";
const char AT_CWLAP[] = "AT+CWLAP";
const char AT_CWQAP[] = "AT+CWQAP";
const char AT_CWSAP[] = "AT+CWSAP=";
const char AT_CIPSTATUS[] = "AT+CIPSTATUS";
const char AT_CIPSTART[] = "AT+CIPSTART=";
const char AT_CIPSEND[] = "AT+CIPSEND=";
const char AT_CIPCLOSE[] = "AT+CIPCLOSE";
const char AT_CIFSR[] = "AT+CIFSR";
const char AT_CIPMUX[] = "AT+CIPMUX=";
const char AT_CIPSERVER[] = "AT+CIPSERVER=";
const char RECEIVED_DATA[] = "+IPD";

#define RESP_FALSE -1
#define RESP_TRUE 0

#endif