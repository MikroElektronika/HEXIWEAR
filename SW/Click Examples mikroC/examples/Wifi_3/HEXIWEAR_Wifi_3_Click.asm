_IRQ_UartHandler:
;HEXIWEAR_Wifi_3_Click.c,98 :: 		void IRQ_UartHandler() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
;HEXIWEAR_Wifi_3_Click.c,100 :: 		volatile uint8_t foo = UART2_S1;
MOVW	R0, #lo_addr(UART2_S1+0)
MOVT	R0, #hi_addr(UART2_S1+0)
; foo start address is: 0 (R0)
LDRB	R0, [R0, #0]
; foo end address is: 0 (R0)
;HEXIWEAR_Wifi_3_Click.c,101 :: 		uint8_t readData = UART2_D;
MOVW	R0, #lo_addr(UART2_D+0)
MOVT	R0, #hi_addr(UART2_D+0)
; readData start address is: 4 (R1)
LDRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,103 :: 		tmp = readData;
MOVW	R0, #lo_addr(_tmp+0)
MOVT	R0, #hi_addr(_tmp+0)
STRB	R1, [R0, #0]
; readData end address is: 4 (R1)
;HEXIWEAR_Wifi_3_Click.c,104 :: 		switch(tmp) {
IT	AL
BAL	L_IRQ_UartHandler0
;HEXIWEAR_Wifi_3_Click.c,105 :: 		case LF:
L_IRQ_UartHandler2:
;HEXIWEAR_Wifi_3_Click.c,106 :: 		if(data_len > 1){
MOVW	R0, #lo_addr(_data_len+0)
MOVT	R0, #hi_addr(_data_len+0)
LDRH	R0, [R0, #0]
CMP	R0, #1
IT	LS
BLS	L_IRQ_UartHandler3
;HEXIWEAR_Wifi_3_Click.c,107 :: 		data_ready = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(_data_ready+0)
MOVT	R0, #hi_addr(_data_ready+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,108 :: 		}
L_IRQ_UartHandler3:
;HEXIWEAR_Wifi_3_Click.c,109 :: 		break;
IT	AL
BAL	L_IRQ_UartHandler1
;HEXIWEAR_Wifi_3_Click.c,110 :: 		case CR:
L_IRQ_UartHandler4:
;HEXIWEAR_Wifi_3_Click.c,111 :: 		rx_buff[data_len] = 0; //but not necessary
MOVW	R0, #lo_addr(_data_len+0)
MOVT	R0, #hi_addr(_data_len+0)
LDRH	R1, [R0, #0]
MOVW	R0, #lo_addr(_rx_buff+0)
MOVT	R0, #hi_addr(_rx_buff+0)
ADDS	R1, R0, R1
MOVS	R0, #0
STRB	R0, [R1, #0]
;HEXIWEAR_Wifi_3_Click.c,112 :: 		break;
IT	AL
BAL	L_IRQ_UartHandler1
;HEXIWEAR_Wifi_3_Click.c,113 :: 		default:
L_IRQ_UartHandler5:
;HEXIWEAR_Wifi_3_Click.c,114 :: 		rx_buff[data_len] = tmp;
MOVW	R2, #lo_addr(_data_len+0)
MOVT	R2, #hi_addr(_data_len+0)
LDRH	R1, [R2, #0]
MOVW	R0, #lo_addr(_rx_buff+0)
MOVT	R0, #hi_addr(_rx_buff+0)
ADDS	R1, R0, R1
MOVW	R0, #lo_addr(_tmp+0)
MOVT	R0, #hi_addr(_tmp+0)
LDRB	R0, [R0, #0]
STRB	R0, [R1, #0]
;HEXIWEAR_Wifi_3_Click.c,115 :: 		data_len++;
MOV	R0, R2
LDRH	R0, [R0, #0]
ADDS	R0, R0, #1
STRH	R0, [R2, #0]
;HEXIWEAR_Wifi_3_Click.c,116 :: 		}
IT	AL
BAL	L_IRQ_UartHandler1
L_IRQ_UartHandler0:
MOVW	R0, #lo_addr(_tmp+0)
MOVT	R0, #hi_addr(_tmp+0)
LDRB	R0, [R0, #0]
CMP	R0, #10
IT	EQ
BEQ	L_IRQ_UartHandler2
MOVW	R0, #lo_addr(_tmp+0)
MOVT	R0, #hi_addr(_tmp+0)
LDRB	R0, [R0, #0]
CMP	R0, #13
IT	EQ
BEQ	L_IRQ_UartHandler4
IT	AL
BAL	L_IRQ_UartHandler5
L_IRQ_UartHandler1:
;HEXIWEAR_Wifi_3_Click.c,118 :: 		}
L_end_IRQ_UartHandler:
BX	LR
; end of _IRQ_UartHandler
_reset_buff:
;HEXIWEAR_Wifi_3_Click.c,121 :: 		void reset_buff() {
SUB	SP, SP, #8
STR	LR, [SP, #0]
;HEXIWEAR_Wifi_3_Click.c,122 :: 		memset(rx_buff,0,data_len);
MOVW	R0, #lo_addr(_data_len+0)
MOVT	R0, #hi_addr(_data_len+0)
STR	R0, [SP, #4]
LDRH	R0, [R0, #0]
SXTH	R2, R0
MOVS	R1, #0
MOVW	R0, #lo_addr(_rx_buff+0)
MOVT	R0, #hi_addr(_rx_buff+0)
BL	_memset+0
;HEXIWEAR_Wifi_3_Click.c,123 :: 		data_ready = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_data_ready+0)
MOVT	R0, #hi_addr(_data_ready+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,124 :: 		data_len=0;
MOVS	R1, #0
LDR	R0, [SP, #4]
STRH	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,125 :: 		}
L_end_reset_buff:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _reset_buff
_UART_Write_AT:
;HEXIWEAR_Wifi_3_Click.c,127 :: 		void UART_Write_AT(char *CMD) {
; CMD start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; CMD end address is: 0 (R0)
; CMD start address is: 0 (R0)
;HEXIWEAR_Wifi_3_Click.c,128 :: 		UART_Write_Text(CMD);
; CMD end address is: 0 (R0)
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,129 :: 		UART_Write(0x0D);
MOVS	R0, #13
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,130 :: 		UART_Write(0x0A);
MOVS	R0, #10
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,131 :: 		}
L_end_UART_Write_AT:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _UART_Write_AT
_response_success:
;HEXIWEAR_Wifi_3_Click.c,133 :: 		char response_success() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Wifi_3_Click.c,135 :: 		while(!data_ready);
L_response_success6:
MOVW	R0, #lo_addr(_data_ready+0)
MOVT	R0, #hi_addr(_data_ready+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_response_success7
IT	AL
BAL	L_response_success6
L_response_success7:
;HEXIWEAR_Wifi_3_Click.c,136 :: 		if((strstr(rx_buff,"OK")) || (strstr(rx_buff,"no change")) || (strstr(rx_buff,"ready"))) {
MOVW	R0, #lo_addr(?lstr4_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr4_HEXIWEAR_Wifi_3_Click+0)
MOV	R1, R0
MOVW	R0, #lo_addr(_rx_buff+0)
MOVT	R0, #hi_addr(_rx_buff+0)
BL	_strstr+0
CMP	R0, #0
IT	NE
BNE	L__response_success61
MOVW	R0, #lo_addr(?lstr5_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr5_HEXIWEAR_Wifi_3_Click+0)
MOV	R1, R0
MOVW	R0, #lo_addr(_rx_buff+0)
MOVT	R0, #hi_addr(_rx_buff+0)
BL	_strstr+0
CMP	R0, #0
IT	NE
BNE	L__response_success60
MOVW	R0, #lo_addr(?lstr6_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr6_HEXIWEAR_Wifi_3_Click+0)
MOV	R1, R0
MOVW	R0, #lo_addr(_rx_buff+0)
MOVT	R0, #hi_addr(_rx_buff+0)
BL	_strstr+0
CMP	R0, #0
IT	NE
BNE	L__response_success59
IT	AL
BAL	L_response_success10
L__response_success61:
L__response_success60:
L__response_success59:
;HEXIWEAR_Wifi_3_Click.c,137 :: 		result = 1;
; result start address is: 0 (R0)
MOVS	R0, #1
;HEXIWEAR_Wifi_3_Click.c,138 :: 		}else result = 0;
UXTB	R6, R0
; result end address is: 0 (R0)
IT	AL
BAL	L_response_success11
L_response_success10:
; result start address is: 0 (R0)
MOVS	R0, #0
; result end address is: 0 (R0)
UXTB	R6, R0
L_response_success11:
;HEXIWEAR_Wifi_3_Click.c,139 :: 		reset_buff();
; result start address is: 24 (R6)
BL	_reset_buff+0
;HEXIWEAR_Wifi_3_Click.c,140 :: 		return result;
UXTB	R0, R6
; result end address is: 24 (R6)
;HEXIWEAR_Wifi_3_Click.c,141 :: 		}
L_end_response_success:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _response_success
_Get_IP:
;HEXIWEAR_Wifi_3_Click.c,143 :: 		void Get_IP() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Wifi_3_Click.c,146 :: 		UART_Write_AT("AT+CIFSR");
MOVW	R0, #lo_addr(?lstr7_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr7_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_AT+0
;HEXIWEAR_Wifi_3_Click.c,147 :: 		while(!data_ready);
L_Get_IP12:
MOVW	R0, #lo_addr(_data_ready+0)
MOVT	R0, #hi_addr(_data_ready+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_Get_IP13
IT	AL
BAL	L_Get_IP12
L_Get_IP13:
;HEXIWEAR_Wifi_3_Click.c,148 :: 		reset_buff();
BL	_reset_buff+0
;HEXIWEAR_Wifi_3_Click.c,149 :: 		while(!data_ready);
L_Get_IP14:
MOVW	R0, #lo_addr(_data_ready+0)
MOVT	R0, #hi_addr(_data_ready+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_Get_IP15
IT	AL
BAL	L_Get_IP14
L_Get_IP15:
;HEXIWEAR_Wifi_3_Click.c,150 :: 		reset_buff();
BL	_reset_buff+0
;HEXIWEAR_Wifi_3_Click.c,151 :: 		}
L_end_Get_IP:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Get_IP
_WiFi3_Init:
;HEXIWEAR_Wifi_3_Click.c,154 :: 		void WiFi3_Init() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Wifi_3_Click.c,155 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_3);
MOV	R1, #8
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Wifi_3_Click.c,156 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_19);
MOV	R1, #524288
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Wifi_3_Click.c,158 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_3);
MOV	R1, #8
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Wifi_3_Click.c,159 :: 		GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11);
MOV	R1, #2048
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Wifi_3_Click.c,161 :: 		REL1 = 0;
MOVS	R2, #0
SXTB	R2, R2
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
STR	R2, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,162 :: 		REL2 = 0;
MOVW	R0, #lo_addr(PTC_PTOR+0)
MOVT	R0, #hi_addr(PTC_PTOR+0)
STR	R2, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,164 :: 		CH_PD = 1;                    // Power down line at high level
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,165 :: 		GPIO15 = 0;                   // GPIO15 pin at low level on module power-up
MOVW	R0, #lo_addr(PTB_PDIR+0)
MOVT	R0, #hi_addr(PTB_PDIR+0)
STR	R2, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,166 :: 		Delay_ms(1000);               // wait five seconds on power-on
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFi3_Init16:
SUBS	R7, R7, #1
BNE	L_WiFi3_Init16
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,167 :: 		}
L_end_WiFi3_Init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _WiFi3_Init
_WiFI_Configure:
;HEXIWEAR_Wifi_3_Click.c,169 :: 		void WiFI_Configure() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Wifi_3_Click.c,171 :: 		OLED_WriteText("Resetting module", 5, 80 );
MOVW	R0, #lo_addr(?lstr8_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr8_HEXIWEAR_Wifi_3_Click+0)
MOVS	R2, #80
MOVS	R1, #5
BL	_OLED_WriteText+0
;HEXIWEAR_Wifi_3_Click.c,173 :: 		UART_Write_AT("AT+RST");                                                     //Reset module
MOVW	R0, #lo_addr(?lstr9_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr9_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_AT+0
;HEXIWEAR_Wifi_3_Click.c,174 :: 		while(!response_success());
L_WiFI_Configure18:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure19
IT	AL
BAL	L_WiFI_Configure18
L_WiFI_Configure19:
;HEXIWEAR_Wifi_3_Click.c,175 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure20:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure20
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,177 :: 		UART_Write_AT("AT+CWMODE=1");                                                //change the working mode to 1
MOVW	R0, #lo_addr(?lstr10_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr10_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_AT+0
;HEXIWEAR_Wifi_3_Click.c,178 :: 		while(!response_success());                                                  //wait to respond success
L_WiFI_Configure22:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure23
IT	AL
BAL	L_WiFI_Configure22
L_WiFI_Configure23:
;HEXIWEAR_Wifi_3_Click.c,179 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure24:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure24
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,182 :: 		OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
MOVW	R0, #0
PUSH	(R0)
MOVS	R3, #16
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Wifi_3_Click.c,183 :: 		OLED_WriteText("Set connection", 15, 80 );
MOVW	R0, #lo_addr(?lstr11_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr11_HEXIWEAR_Wifi_3_Click+0)
MOVS	R2, #80
MOVS	R1, #15
BL	_OLED_WriteText+0
;HEXIWEAR_Wifi_3_Click.c,185 :: 		UART_Write_AT("AT+CIPMUX=1");                                                //change the connection mode to 1
MOVW	R0, #lo_addr(?lstr12_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr12_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_AT+0
;HEXIWEAR_Wifi_3_Click.c,186 :: 		while(!response_success());                                                  //wait to respond succes
L_WiFI_Configure26:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure27
IT	AL
BAL	L_WiFI_Configure26
L_WiFI_Configure27:
;HEXIWEAR_Wifi_3_Click.c,187 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure28:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure28
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,189 :: 		UART_Write_AT("AT+CWMODE=2");                                                //change the connection mode to 1
MOVW	R0, #lo_addr(?lstr13_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr13_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_AT+0
;HEXIWEAR_Wifi_3_Click.c,190 :: 		while(!response_success());                                                  //wait to respond succes
L_WiFI_Configure30:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure31
IT	AL
BAL	L_WiFI_Configure30
L_WiFI_Configure31:
;HEXIWEAR_Wifi_3_Click.c,191 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure32:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure32
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,195 :: 		OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
MOVW	R0, #0
PUSH	(R0)
MOVS	R3, #16
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Wifi_3_Click.c,196 :: 		OLED_WriteText("Making SoftAP", 12, 80 );
MOVW	R0, #lo_addr(?lstr14_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr14_HEXIWEAR_Wifi_3_Click+0)
MOVS	R2, #80
MOVS	R1, #12
BL	_OLED_WriteText+0
;HEXIWEAR_Wifi_3_Click.c,199 :: 		UART_Write_Text("AT+CWSAP=");
MOVW	R0, #lo_addr(?lstr15_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr15_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,200 :: 		UART_Write('"');
MOVS	R0, #34
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,201 :: 		UART_Write_Text(SSID);
MOVW	R0, #lo_addr(_SSID+0)
MOVT	R0, #hi_addr(_SSID+0)
LDR	R0, [R0, #0]
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,202 :: 		UART_Write('"');
MOVS	R0, #34
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,203 :: 		UART_Write(',');
MOVS	R0, #44
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,204 :: 		UART_Write('"');
MOVS	R0, #34
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,205 :: 		UART_Write_Text(password);
MOVW	R0, #lo_addr(_password+0)
MOVT	R0, #hi_addr(_password+0)
LDR	R0, [R0, #0]
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,206 :: 		UART_Write('"');
MOVS	R0, #34
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,207 :: 		UART_Write(',');
MOVS	R0, #44
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,208 :: 		UART_Write('5');
MOVS	R0, #53
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,209 :: 		UART_Write(',');
MOVS	R0, #44
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,210 :: 		UART_Write('0');
MOVS	R0, #48
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,211 :: 		UART_Write(0x0D);
MOVS	R0, #13
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,212 :: 		UART_Write(0x0A);
MOVS	R0, #10
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,213 :: 		while(!response_success());                                                  //wait to respond succes
L_WiFI_Configure34:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure35
IT	AL
BAL	L_WiFI_Configure34
L_WiFI_Configure35:
;HEXIWEAR_Wifi_3_Click.c,214 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure36:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure36
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,216 :: 		UART_Write_Text("AT+CIPAP=");                                                // Set IP address
MOVW	R0, #lo_addr(?lstr16_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr16_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,217 :: 		UART_Write('"');
MOVS	R0, #34
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,218 :: 		UART_Write_Text("192.168.0.1");
MOVW	R0, #lo_addr(?lstr17_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr17_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,219 :: 		UART_Write('"');
MOVS	R0, #34
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,220 :: 		UART_Write(0x0D);
MOVS	R0, #13
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,221 :: 		UART_Write(0x0A);
MOVS	R0, #10
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,223 :: 		while(!response_success());                                                  //wait to respond succes
L_WiFI_Configure38:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure39
IT	AL
BAL	L_WiFI_Configure38
L_WiFI_Configure39:
;HEXIWEAR_Wifi_3_Click.c,224 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure40:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure40
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,226 :: 		OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
MOVW	R0, #0
PUSH	(R0)
MOVS	R3, #16
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Wifi_3_Click.c,227 :: 		OLED_WriteText("Set server/port", 10, 80 );
MOVW	R0, #lo_addr(?lstr18_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr18_HEXIWEAR_Wifi_3_Click+0)
MOVS	R2, #80
MOVS	R1, #10
BL	_OLED_WriteText+0
;HEXIWEAR_Wifi_3_Click.c,228 :: 		UART_Write_Text("AT+CIPSERVER=1");
MOVW	R0, #lo_addr(?lstr19_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr19_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,229 :: 		UART_Write(',');
MOVS	R0, #44
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,230 :: 		UART_Write_Text(port);
MOVW	R0, #lo_addr(_port+0)
MOVT	R0, #hi_addr(_port+0)
LDR	R0, [R0, #0]
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,231 :: 		UART_Write(0x0D);
MOVS	R0, #13
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,232 :: 		UART_Write(0x0A);
MOVS	R0, #10
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,233 :: 		while(!response_success());                                                  //wait to respond succes
L_WiFI_Configure42:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure43
IT	AL
BAL	L_WiFI_Configure42
L_WiFI_Configure43:
;HEXIWEAR_Wifi_3_Click.c,234 :: 		Delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure44:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure44
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,236 :: 		OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
MOVW	R0, #0
PUSH	(R0)
MOVS	R3, #16
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Wifi_3_Click.c,237 :: 		OLED_WriteText("Listen...", 30, 80 );
MOVW	R0, #lo_addr(?lstr20_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr20_HEXIWEAR_Wifi_3_Click+0)
MOVS	R2, #80
MOVS	R1, #30
BL	_OLED_WriteText+0
;HEXIWEAR_Wifi_3_Click.c,239 :: 		UART_Write_AT("AT+CIPSTO=30");                                                //change the connection mode to 1
MOVW	R0, #lo_addr(?lstr21_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr21_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_AT+0
;HEXIWEAR_Wifi_3_Click.c,240 :: 		while(!response_success());                                                  //wait to respond succes
L_WiFI_Configure46:
BL	_response_success+0
CMP	R0, #0
IT	NE
BNE	L_WiFI_Configure47
IT	AL
BAL	L_WiFI_Configure46
L_WiFI_Configure47:
;HEXIWEAR_Wifi_3_Click.c,241 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_WiFI_Configure48:
SUBS	R7, R7, #1
BNE	L_WiFI_Configure48
NOP
NOP
NOP
;HEXIWEAR_Wifi_3_Click.c,243 :: 		}
L_end_WiFI_Configure:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _WiFI_Configure
_main:
;HEXIWEAR_Wifi_3_Click.c,248 :: 		void main() {
SUB	SP, SP, #4
;HEXIWEAR_Wifi_3_Click.c,250 :: 		state = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_state+0)
MOVT	R0, #hi_addr(_state+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,251 :: 		response_rcvd = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_response_rcvd+0)
MOVT	R0, #hi_addr(_response_rcvd+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,252 :: 		responseID = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_responseID+0)
MOVT	R0, #hi_addr(_responseID+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,253 :: 		response = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_response+0)
MOVT	R0, #hi_addr(_response+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,254 :: 		tmp = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_tmp+0)
MOVT	R0, #hi_addr(_tmp+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,255 :: 		i = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,256 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Wifi_3_Click.c,258 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Wifi_3_Click.c,260 :: 		OLED_DrawImage( WiFi_bmp, 0, 0 );
MOVW	R0, #lo_addr(_WiFi_bmp+0)
MOVT	R0, #hi_addr(_WiFi_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Wifi_3_Click.c,262 :: 		UART2_init_Advanced( 115000, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT,  &_GPIO_Module_UART2_PD3_2);             // Initialize UART3 module
MOVW	R0, #lo_addr(__GPIO_Module_UART2_PD3_2+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART2_PD3_2+0)
PUSH	(R0)
MOVW	R3, #0
MOVW	R2, #0
MOVW	R1, #0
MOVW	R0, #49464
MOVT	R0, #1
BL	_UART2_Init_Advanced+0
ADD	SP, SP, #4
;HEXIWEAR_Wifi_3_Click.c,263 :: 		UART_Write_Text("Start");
MOVW	R0, #lo_addr(?lstr22_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr22_HEXIWEAR_Wifi_3_Click+0)
BL	_UART_Write_Text+0
;HEXIWEAR_Wifi_3_Click.c,264 :: 		UART_Write(0x0D);
MOVS	R0, #13
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,265 :: 		UART_Write(0x0A);
MOVS	R0, #10
BL	_UART_Write+0
;HEXIWEAR_Wifi_3_Click.c,267 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_Wifi_3_Click.c,268 :: 		NVIC_IntEnable( IVT_INT_UART2_RX_TX );
MOVW	R0, #51
BL	_NVIC_IntEnable+0
;HEXIWEAR_Wifi_3_Click.c,269 :: 		UART2_C2 |= 1 << 5;
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
LDRB	R0, [R0, #0]
ORR	R1, R0, #32
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Wifi_3_Click.c,272 :: 		WiFi3_Init();
BL	_WiFi3_Init+0
;HEXIWEAR_Wifi_3_Click.c,274 :: 		WiFI_Configure();
BL	_WiFI_Configure+0
;HEXIWEAR_Wifi_3_Click.c,276 :: 		while (1)
L_main50:
;HEXIWEAR_Wifi_3_Click.c,278 :: 		while(!data_ready);
L_main52:
MOVW	R0, #lo_addr(_data_ready+0)
MOVT	R0, #hi_addr(_data_ready+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_main53
IT	AL
BAL	L_main52
L_main53:
;HEXIWEAR_Wifi_3_Click.c,280 :: 		if(memcmp("+IPD", &rx_buff[0], 4) == 0)
MOVW	R0, #lo_addr(?lstr23_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr23_HEXIWEAR_Wifi_3_Click+0)
MOVS	R2, #4
SXTH	R2, R2
MOVW	R1, #lo_addr(_rx_buff+0)
MOVT	R1, #hi_addr(_rx_buff+0)
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_main54
;HEXIWEAR_Wifi_3_Click.c,282 :: 		if(strcmp("R1", &rx_buff[9]) == 0)
MOVW	R0, #lo_addr(?lstr24_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr24_HEXIWEAR_Wifi_3_Click+0)
MOVW	R1, #lo_addr(_rx_buff+9)
MOVT	R1, #hi_addr(_rx_buff+9)
BL	_strcmp+0
CMP	R0, #0
IT	NE
BNE	L_main55
;HEXIWEAR_Wifi_3_Click.c,284 :: 		REL1 = ~REL1;
MOVW	R1, #lo_addr(PTA_PDOR+0)
MOVT	R1, #hi_addr(PTA_PDOR+0)
LDR	R0, [R1, #0]
EOR	R0, R0, #1
STR	R0, [R1, #0]
;HEXIWEAR_Wifi_3_Click.c,285 :: 		}
IT	AL
BAL	L_main56
L_main55:
;HEXIWEAR_Wifi_3_Click.c,286 :: 		else if(strcmp("R2", &rx_buff[9]) == 0)
MOVW	R0, #lo_addr(?lstr25_HEXIWEAR_Wifi_3_Click+0)
MOVT	R0, #hi_addr(?lstr25_HEXIWEAR_Wifi_3_Click+0)
MOVW	R1, #lo_addr(_rx_buff+9)
MOVT	R1, #hi_addr(_rx_buff+9)
BL	_strcmp+0
CMP	R0, #0
IT	NE
BNE	L_main57
;HEXIWEAR_Wifi_3_Click.c,288 :: 		REL2 = ~REL2;
MOVW	R1, #lo_addr(PTC_PTOR+0)
MOVT	R1, #hi_addr(PTC_PTOR+0)
LDR	R0, [R1, #0]
EOR	R0, R0, #1
STR	R0, [R1, #0]
;HEXIWEAR_Wifi_3_Click.c,289 :: 		}
L_main57:
L_main56:
;HEXIWEAR_Wifi_3_Click.c,290 :: 		}
L_main54:
;HEXIWEAR_Wifi_3_Click.c,292 :: 		reset_buff();
BL	_reset_buff+0
;HEXIWEAR_Wifi_3_Click.c,293 :: 		}
IT	AL
BAL	L_main50
;HEXIWEAR_Wifi_3_Click.c,294 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
