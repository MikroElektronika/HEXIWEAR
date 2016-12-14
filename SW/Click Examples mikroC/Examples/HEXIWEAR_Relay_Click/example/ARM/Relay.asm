Relay_PacketParser:
;Relay.c,218 :: 		static void PacketParser()
;Relay.c,222 :: 		switch ( hostInterface_rxState )
IT	AL
BAL	L_Relay_PacketParser0
;Relay.c,224 :: 		case hostInterface_rxState_idle:
L_Relay_PacketParser2:
;Relay.c,226 :: 		if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+0)
LDRB	R0, [R0, #0]
CMP	R0, #85
IT	NE
BNE	L_Relay_PacketParser3
;Relay.c,228 :: 		hostInterface_rxState++;
MOVW	R1, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R1, #hi_addr(Relay_hostInterface_rxState+0)
LDRB	R0, [R1, #0]
ADDS	R0, R0, #1
STRB	R0, [R1, #0]
;Relay.c,229 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;Relay.c,230 :: 		}
L_Relay_PacketParser3:
;Relay.c,232 :: 		break;
IT	AL
BAL	L_Relay_PacketParser1
;Relay.c,235 :: 		case hostInterface_rxState_headerReceived:
L_Relay_PacketParser4:
;Relay.c,240 :: 		0xFE ) )
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+0)
LDRB	R0, [R0, #0]
CMP	R0, #85
IT	NE
BNE	L_Relay_PacketParser36
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+1)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+1)
LDRB	R0, [R0, #0]
AND	R0, R0, #254
UXTB	R0, R0
CMP	R0, #170
IT	NE
BNE	L_Relay_PacketParser35
;Relay.c,241 :: 		|| ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+3)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+3)
LDRB	R0, [R0, #0]
CMP	R0, #23
IT	HI
BHI	L_Relay_PacketParser34
IT	AL
BAL	L_Relay_PacketParser7
;Relay.c,240 :: 		0xFE ) )
L_Relay_PacketParser36:
L_Relay_PacketParser35:
;Relay.c,241 :: 		|| ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
L_Relay_PacketParser34:
;Relay.c,245 :: 		hostInterface_rxState = hostInterface_rxState_idle;
MOVS	R1, #0
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;Relay.c,247 :: 		pktBuf = ( uint8_t * )&hostInterface_rxPacket;
MOVW	R1, #lo_addr(Relay_hostInterface_rxPacket+0)
MOVT	R1, #hi_addr(Relay_hostInterface_rxPacket+0)
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
STR	R1, [R0, #0]
;Relay.c,248 :: 		}
IT	AL
BAL	L_Relay_PacketParser8
L_Relay_PacketParser7:
;Relay.c,253 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;Relay.c,255 :: 		if ( 0 == hostInterface_rxPacket.length )
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+3)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+3)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_Relay_PacketParser9
;Relay.c,258 :: 		hostInterface_rxState = hostInterface_rxState_trailerWait;
MOVS	R1, #5
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;Relay.c,259 :: 		}
IT	AL
BAL	L_Relay_PacketParser10
L_Relay_PacketParser9:
;Relay.c,263 :: 		byteCount = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(Relay_PacketParser_byteCount_L0+0)
MOVT	R0, #hi_addr(Relay_PacketParser_byteCount_L0+0)
STRB	R1, [R0, #0]
;Relay.c,265 :: 		hostInterface_rxState = hostInterface_rxState_dataWait;
MOVS	R1, #4
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;Relay.c,266 :: 		}
L_Relay_PacketParser10:
;Relay.c,267 :: 		}
L_Relay_PacketParser8:
;Relay.c,269 :: 		break;
IT	AL
BAL	L_Relay_PacketParser1
;Relay.c,272 :: 		case hostInterface_rxState_dataWait:
L_Relay_PacketParser11:
;Relay.c,274 :: 		byteCount++;
MOVW	R1, #lo_addr(Relay_PacketParser_byteCount_L0+0)
MOVT	R1, #hi_addr(Relay_PacketParser_byteCount_L0+0)
LDRB	R0, [R1, #0]
ADDS	R2, R0, #1
UXTB	R2, R2
STRB	R2, [R1, #0]
;Relay.c,275 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;Relay.c,278 :: 		if  ( hostInterface_rxPacket.length == byteCount )
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+3)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+3)
LDRB	R0, [R0, #0]
CMP	R0, R2
IT	NE
BNE	L_Relay_PacketParser12
;Relay.c,281 :: 		hostInterface_rxState = hostInterface_rxState_trailerWait;
MOVS	R1, #5
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;Relay.c,282 :: 		}
L_Relay_PacketParser12:
;Relay.c,284 :: 		break;
IT	AL
BAL	L_Relay_PacketParser1
;Relay.c,287 :: 		case hostInterface_rxState_trailerWait:
L_Relay_PacketParser13:
;Relay.c,289 :: 		if ( gHostInterface_trailerByte == *pktBuf )
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
LDR	R0, [R0, #0]
LDRB	R0, [R0, #0]
CMP	R0, #69
IT	NE
BNE	L_Relay_PacketParser14
;Relay.c,291 :: 		switch ( hostInterface_rxPacket.type )
IT	AL
BAL	L_Relay_PacketParser15
;Relay.c,293 :: 		case packetType_pressRight:
L_Relay_PacketParser17:
;Relay.c,295 :: 		pressedTouch = touch_right;
MOVS	R1, #1
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
STRB	R1, [R0, #0]
;Relay.c,296 :: 		break;
IT	AL
BAL	L_Relay_PacketParser16
;Relay.c,298 :: 		case packetType_pressLeft:
L_Relay_PacketParser18:
;Relay.c,300 :: 		pressedTouch = touch_left;
MOVS	R1, #0
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
STRB	R1, [R0, #0]
;Relay.c,301 :: 		break;
IT	AL
BAL	L_Relay_PacketParser16
;Relay.c,303 :: 		default:
L_Relay_PacketParser19:
;Relay.c,305 :: 		pressedTouch = touch_invalid;
MOVS	R1, #255
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
STRB	R1, [R0, #0]
;Relay.c,307 :: 		}
IT	AL
BAL	L_Relay_PacketParser16
L_Relay_PacketParser15:
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+2)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+2)
LDRB	R0, [R0, #0]
CMP	R0, #3
IT	EQ
BEQ	L_Relay_PacketParser17
MOVW	R0, #lo_addr(Relay_hostInterface_rxPacket+2)
MOVT	R0, #hi_addr(Relay_hostInterface_rxPacket+2)
LDRB	R0, [R0, #0]
CMP	R0, #2
IT	EQ
BEQ	L_Relay_PacketParser18
IT	AL
BAL	L_Relay_PacketParser19
L_Relay_PacketParser16:
;Relay.c,308 :: 		}
L_Relay_PacketParser14:
;Relay.c,311 :: 		hostInterface_rxState = hostInterface_rxState_idle;
MOVS	R1, #0
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;Relay.c,313 :: 		pktBuf = ( uint8_t * )&hostInterface_rxPacket;
MOVW	R1, #lo_addr(Relay_hostInterface_rxPacket+0)
MOVT	R1, #hi_addr(Relay_hostInterface_rxPacket+0)
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
STR	R1, [R0, #0]
;Relay.c,314 :: 		break;
IT	AL
BAL	L_Relay_PacketParser1
;Relay.c,317 :: 		default:
L_Relay_PacketParser20:
;Relay.c,319 :: 		hostInterface_rxState++;
MOVW	R1, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R1, #hi_addr(Relay_hostInterface_rxState+0)
LDRB	R0, [R1, #0]
ADDS	R0, R0, #1
STRB	R0, [R1, #0]
;Relay.c,320 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;Relay.c,322 :: 		}
IT	AL
BAL	L_Relay_PacketParser1
L_Relay_PacketParser0:
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_Relay_PacketParser2
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #3
IT	EQ
BEQ	L_Relay_PacketParser4
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #4
IT	EQ
BEQ	L_Relay_PacketParser11
MOVW	R0, #lo_addr(Relay_hostInterface_rxState+0)
MOVT	R0, #hi_addr(Relay_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #5
IT	EQ
BEQ	L_Relay_PacketParser13
IT	AL
BAL	L_Relay_PacketParser20
L_Relay_PacketParser1:
;Relay.c,323 :: 		}
L_end_PacketParser:
BX	LR
; end of Relay_PacketParser
_IRQ_Uart4Handler:
;Relay.c,331 :: 		void IRQ_Uart4Handler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Relay.c,334 :: 		volatile uint8_t foo = UART4_S1;
MOVW	R0, #lo_addr(UART4_S1+0)
MOVT	R0, #hi_addr(UART4_S1+0)
; foo start address is: 0 (R0)
LDRB	R0, [R0, #0]
; foo end address is: 0 (R0)
;Relay.c,335 :: 		uint8_t readData = UART4_D;
MOVW	R0, #lo_addr(UART4_D+0)
MOVT	R0, #hi_addr(UART4_D+0)
; readData start address is: 4 (R1)
LDRB	R1, [R0, #0]
;Relay.c,336 :: 		*pktBuf = readData;
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
LDR	R0, [R0, #0]
STRB	R1, [R0, #0]
; readData end address is: 4 (R1)
;Relay.c,338 :: 		PacketParser();
BL	Relay_PacketParser+0
;Relay.c,339 :: 		}
L_end_IRQ_Uart4Handler:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _IRQ_Uart4Handler
_main:
;Relay.c,341 :: 		void main() org 0x1000
;Relay.c,344 :: 		GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );
MOV	R1, #1024
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
BL	_GPIO_Digital_Output+0
;Relay.c,346 :: 		GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;Relay.c,349 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 );
MOV	R1, #8388608
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;Relay.c,351 :: 		OLED_Init();
BL	_OLED_Init+0
;Relay.c,354 :: 		UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_TWO_STOPBITS,  &_GPIO_Module_UART4_PE24_25 );
MOVW	R0, #lo_addr(__GPIO_Module_UART4_PE24_25+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART4_PE24_25+0)
PUSH	(R0)
MOVW	R3, #32
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #230400
BL	_UART4_Init_Advanced+0
ADD	SP, SP, #4
;Relay.c,356 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;Relay.c,357 :: 		NVIC_IntEnable( IVT_INT_UART4_RX_TX );
MOVW	R0, #82
BL	_NVIC_IntEnable+0
;Relay.c,359 :: 		UART4_C2_REG |= 1 << 5;
MOVW	R1, 1074700291
MOVT	R1, 16398
LDRB	R0, [R1, #0]
ORR	R0, R0, #32
STRB	R0, [R1, #0]
;Relay.c,362 :: 		KW40_RST_CLEAR();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PCOR+0)
MOVT	R0, #hi_addr(PTB_PCOR+0)
STR	R1, [R0, #0]
;Relay.c,363 :: 		Delay_ms( 10 );
MOVW	R7, #6782
MOVT	R7, #6
NOP
NOP
L_main21:
SUBS	R7, R7, #1
BNE	L_main21
NOP
NOP
NOP
;Relay.c,364 :: 		KW40_RST_SET();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PSOR+0)
MOVT	R0, #hi_addr(PTB_PSOR+0)
STR	R1, [R0, #0]
;Relay.c,365 :: 		Delay_ms( 200 );
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_main23:
SUBS	R7, R7, #1
BNE	L_main23
NOP
NOP
NOP
;Relay.c,368 :: 		relay1 = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;Relay.c,369 :: 		relay2 = 0;
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
STR	R1, [R0, #0]
;Relay.c,371 :: 		OLED_DrawImage( &relay_bmp, 0, 0 );
MOVW	R0, #lo_addr(_relay_bmp+0)
MOVT	R0, #hi_addr(_relay_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Relay.c,373 :: 		while ( 1 )
L_main25:
;Relay.c,375 :: 		if ( touch_invalid != pressedTouch )
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #255
IT	EQ
BEQ	L_main27
;Relay.c,377 :: 		switch ( pressedTouch )
IT	AL
BAL	L_main28
;Relay.c,379 :: 		case touch_left:
L_main30:
;Relay.c,381 :: 		TOGGLE_RELAY1();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PTOR+0)
MOVT	R0, #hi_addr(PTC_PTOR+0)
STR	R1, [R0, #0]
;Relay.c,382 :: 		break;
IT	AL
BAL	L_main29
;Relay.c,385 :: 		case touch_right:
L_main31:
;Relay.c,387 :: 		TOGGLE_RELAY2();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTA_PTOR+0)
MOVT	R0, #hi_addr(PTA_PTOR+0)
STR	R1, [R0, #0]
;Relay.c,388 :: 		break;
IT	AL
BAL	L_main29
;Relay.c,391 :: 		default:
L_main32:
;Relay.c,393 :: 		}
IT	AL
BAL	L_main29
L_main28:
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main30
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	EQ
BEQ	L_main31
IT	AL
BAL	L_main32
L_main29:
;Relay.c,394 :: 		pressedTouch = touch_invalid;
MOVS	R1, #255
MOVW	R0, #lo_addr(Relay_pressedTouch+0)
MOVT	R0, #hi_addr(Relay_pressedTouch+0)
STRB	R1, [R0, #0]
;Relay.c,395 :: 		}
L_main27:
;Relay.c,396 :: 		}
IT	AL
BAL	L_main25
;Relay.c,397 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
