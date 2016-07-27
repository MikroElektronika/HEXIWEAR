BUZZ_PacketParser:
;BUZZ.c,160 :: 		static void PacketParser()
SUB	SP, SP, #4
;BUZZ.c,164 :: 		switch ( hostInterface_rxState )
IT	AL
BAL	L_BUZZ_PacketParser0
;BUZZ.c,166 :: 		case hostInterface_rxState_idle:
L_BUZZ_PacketParser2:
;BUZZ.c,168 :: 		if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+0)
LDRB	R0, [R0, #0]
CMP	R0, #85
IT	NE
BNE	L_BUZZ_PacketParser3
;BUZZ.c,170 :: 		hostInterface_rxState++;
MOVW	R1, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R1, #hi_addr(BUZZ_hostInterface_rxState+0)
LDRB	R0, [R1, #0]
ADDS	R0, R0, #1
STRB	R0, [R1, #0]
;BUZZ.c,171 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;BUZZ.c,172 :: 		}
L_BUZZ_PacketParser3:
;BUZZ.c,174 :: 		break;
IT	AL
BAL	L_BUZZ_PacketParser1
;BUZZ.c,177 :: 		case hostInterface_rxState_headerReceived:
L_BUZZ_PacketParser4:
;BUZZ.c,182 :: 		0xFE ) )
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+0)
LDRB	R0, [R0, #0]
CMP	R0, #85
IT	NE
BNE	L_BUZZ_PacketParser257
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+1)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+1)
LDRB	R0, [R0, #0]
AND	R0, R0, #254
UXTB	R0, R0
CMP	R0, #170
IT	NE
BNE	L_BUZZ_PacketParser256
;BUZZ.c,183 :: 		|| ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+3)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+3)
LDRB	R0, [R0, #0]
CMP	R0, #23
IT	HI
BHI	L_BUZZ_PacketParser255
IT	AL
BAL	L_BUZZ_PacketParser7
;BUZZ.c,182 :: 		0xFE ) )
L_BUZZ_PacketParser257:
L_BUZZ_PacketParser256:
;BUZZ.c,183 :: 		|| ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
L_BUZZ_PacketParser255:
;BUZZ.c,187 :: 		hostInterface_rxState = hostInterface_rxState_idle;
MOVS	R1, #0
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;BUZZ.c,189 :: 		pktBuf = ( uint8_t * )&hostInterface_rxPacket;
MOVW	R1, #lo_addr(BUZZ_hostInterface_rxPacket+0)
MOVT	R1, #hi_addr(BUZZ_hostInterface_rxPacket+0)
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
STR	R1, [R0, #0]
;BUZZ.c,190 :: 		}
IT	AL
BAL	L_BUZZ_PacketParser8
L_BUZZ_PacketParser7:
;BUZZ.c,195 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;BUZZ.c,197 :: 		if ( 0 == hostInterface_rxPacket.length )
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+3)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+3)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_BUZZ_PacketParser9
;BUZZ.c,200 :: 		hostInterface_rxState = hostInterface_rxState_trailerWait;
MOVS	R1, #5
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;BUZZ.c,201 :: 		}
IT	AL
BAL	L_BUZZ_PacketParser10
L_BUZZ_PacketParser9:
;BUZZ.c,205 :: 		byteCount = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(BUZZ_PacketParser_byteCount_L0+0)
MOVT	R0, #hi_addr(BUZZ_PacketParser_byteCount_L0+0)
STRB	R1, [R0, #0]
;BUZZ.c,207 :: 		hostInterface_rxState = hostInterface_rxState_dataWait;
MOVS	R1, #4
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;BUZZ.c,208 :: 		}
L_BUZZ_PacketParser10:
;BUZZ.c,209 :: 		}
L_BUZZ_PacketParser8:
;BUZZ.c,211 :: 		break;
IT	AL
BAL	L_BUZZ_PacketParser1
;BUZZ.c,214 :: 		case hostInterface_rxState_dataWait:
L_BUZZ_PacketParser11:
;BUZZ.c,216 :: 		byteCount++;
MOVW	R1, #lo_addr(BUZZ_PacketParser_byteCount_L0+0)
MOVT	R1, #hi_addr(BUZZ_PacketParser_byteCount_L0+0)
LDRB	R0, [R1, #0]
ADDS	R2, R0, #1
UXTB	R2, R2
STRB	R2, [R1, #0]
;BUZZ.c,217 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;BUZZ.c,220 :: 		if  ( hostInterface_rxPacket.length == byteCount )
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+3)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+3)
LDRB	R0, [R0, #0]
CMP	R0, R2
IT	NE
BNE	L_BUZZ_PacketParser12
;BUZZ.c,223 :: 		hostInterface_rxState = hostInterface_rxState_trailerWait;
MOVS	R1, #5
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;BUZZ.c,224 :: 		}
L_BUZZ_PacketParser12:
;BUZZ.c,226 :: 		break;
IT	AL
BAL	L_BUZZ_PacketParser1
;BUZZ.c,229 :: 		case hostInterface_rxState_trailerWait:
L_BUZZ_PacketParser13:
;BUZZ.c,231 :: 		if ( gHostInterface_trailerByte == *pktBuf )
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
LDR	R0, [R0, #0]
LDRB	R0, [R0, #0]
CMP	R0, #69
IT	NE
BNE	L_BUZZ_PacketParser14
;BUZZ.c,233 :: 		switch ( hostInterface_rxPacket.type )
IT	AL
BAL	L_BUZZ_PacketParser15
;BUZZ.c,235 :: 		case packetType_pressRight:
L_BUZZ_PacketParser17:
;BUZZ.c,237 :: 		pressedTouch = touch_right;
MOVS	R1, #1
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
STRB	R1, [R0, #0]
;BUZZ.c,238 :: 		break;
IT	AL
BAL	L_BUZZ_PacketParser16
;BUZZ.c,240 :: 		case packetType_pressLeft:
L_BUZZ_PacketParser18:
;BUZZ.c,242 :: 		pressedTouch = touch_left;
MOVS	R1, #0
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
STRB	R1, [R0, #0]
;BUZZ.c,243 :: 		break;
IT	AL
BAL	L_BUZZ_PacketParser16
;BUZZ.c,245 :: 		default:
L_BUZZ_PacketParser19:
;BUZZ.c,247 :: 		pressedTouch = touch_invalid;
MOVS	R1, #255
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
STRB	R1, [R0, #0]
;BUZZ.c,249 :: 		}
IT	AL
BAL	L_BUZZ_PacketParser16
L_BUZZ_PacketParser15:
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+2)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+2)
LDRB	R0, [R0, #0]
CMP	R0, #3
IT	EQ
BEQ	L_BUZZ_PacketParser17
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxPacket+2)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxPacket+2)
LDRB	R0, [R0, #0]
CMP	R0, #2
IT	EQ
BEQ	L_BUZZ_PacketParser18
IT	AL
BAL	L_BUZZ_PacketParser19
L_BUZZ_PacketParser16:
;BUZZ.c,250 :: 		}
L_BUZZ_PacketParser14:
;BUZZ.c,253 :: 		hostInterface_rxState = hostInterface_rxState_idle;
MOVS	R1, #0
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
STRB	R1, [R0, #0]
;BUZZ.c,255 :: 		pktBuf = ( uint8_t * )&hostInterface_rxPacket;
MOVW	R1, #lo_addr(BUZZ_hostInterface_rxPacket+0)
MOVT	R1, #hi_addr(BUZZ_hostInterface_rxPacket+0)
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
STR	R1, [R0, #0]
;BUZZ.c,256 :: 		break;
IT	AL
BAL	L_BUZZ_PacketParser1
;BUZZ.c,259 :: 		default:
L_BUZZ_PacketParser20:
;BUZZ.c,261 :: 		hostInterface_rxState++;
MOVW	R1, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R1, #hi_addr(BUZZ_hostInterface_rxState+0)
LDRB	R0, [R1, #0]
ADDS	R0, R0, #1
STRB	R0, [R1, #0]
;BUZZ.c,262 :: 		pktBuf++;
MOVW	R1, #lo_addr(_pktBuf+0)
MOVT	R1, #hi_addr(_pktBuf+0)
LDR	R0, [R1, #0]
ADDS	R0, R0, #1
STR	R0, [R1, #0]
;BUZZ.c,264 :: 		}
IT	AL
BAL	L_BUZZ_PacketParser1
L_BUZZ_PacketParser0:
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_BUZZ_PacketParser2
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #3
IT	EQ
BEQ	L_BUZZ_PacketParser4
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #4
IT	EQ
BEQ	L_BUZZ_PacketParser11
MOVW	R0, #lo_addr(BUZZ_hostInterface_rxState+0)
MOVT	R0, #hi_addr(BUZZ_hostInterface_rxState+0)
LDRB	R0, [R0, #0]
CMP	R0, #5
IT	EQ
BEQ	L_BUZZ_PacketParser13
IT	AL
BAL	L_BUZZ_PacketParser20
L_BUZZ_PacketParser1:
;BUZZ.c,265 :: 		}
L_end_PacketParser:
ADD	SP, SP, #4
BX	LR
; end of BUZZ_PacketParser
_play:
;BUZZ.c,274 :: 		char play(long int freq, int delay_in_miliseconds){
; freq start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRH	R1, [SP, #8]
; freq end address is: 0 (R0)
; freq start address is: 0 (R0)
;BUZZ.c,275 :: 		int i, r=0;
MOVW	R2, #0
STRH	R2, [SP, #4]
;BUZZ.c,277 :: 		PWM_FTM0_Init(freq,_PWM_EDGE_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
MOVW	R3, #lo_addr(__GPIO_Module_PWM0_PTA4+0)
MOVT	R3, #hi_addr(__GPIO_Module_PWM0_PTA4+0)
MOVS	R2, #1
MOVS	R1, #2
UXTH	R0, R0
; freq end address is: 0 (R0)
BL	_PWM_FTM0_Init+0
;BUZZ.c,278 :: 		PWM_FTM0_Set_Duty(5,_PWM_NON_INVERTED,1);
MOVS	R2, #1
MOVS	R1, #0
MOVS	R0, #5
BL	_PWM_FTM0_Set_Duty+0
;BUZZ.c,279 :: 		for(i=0; i < delay_in_miliseconds; i++){
; i start address is: 0 (R0)
MOVS	R0, #0
SXTH	R0, R0
; i end address is: 0 (R0)
L_play21:
; i start address is: 0 (R0)
LDRSH	R2, [SP, #8]
CMP	R0, R2
IT	GE
BGE	L_play22
;BUZZ.c,280 :: 		if (STOPED) {
MOVW	R3, #lo_addr(_STOPED+0)
MOVT	R3, #hi_addr(_STOPED+0)
LDR	R2, [R3, #0]
CMP	R2, #0
IT	EQ
BEQ	L_play24
; i end address is: 0 (R0)
;BUZZ.c,282 :: 		return r;
MOVS	R0, #1
IT	AL
BAL	L_end_play
;BUZZ.c,284 :: 		}
L_play24:
;BUZZ.c,285 :: 		delay_ms(1);
; i start address is: 0 (R0)
MOVW	R7, #39998
MOVT	R7, #0
NOP
NOP
L_play25:
SUBS	R7, R7, #1
BNE	L_play25
NOP
NOP
NOP
;BUZZ.c,279 :: 		for(i=0; i < delay_in_miliseconds; i++){
ADDS	R2, R0, #1
; i end address is: 0 (R0)
; i start address is: 4 (R1)
SXTH	R1, R2
;BUZZ.c,286 :: 		}
SXTH	R0, R1
; i end address is: 4 (R1)
IT	AL
BAL	L_play21
L_play22:
;BUZZ.c,287 :: 		PWM_FTM0_Stop(1);
MOVS	R0, #1
BL	_PWM_FTM0_Stop+0
;BUZZ.c,288 :: 		return r;
LDRSH	R0, [SP, #4]
;BUZZ.c,289 :: 		}
L_end_play:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _play
_play_melody:
;BUZZ.c,292 :: 		void play_melody(){
SUB	SP, SP, #4
STR	LR, [SP, #0]
;BUZZ.c,293 :: 		while(1){
L_play_melody27:
;BUZZ.c,294 :: 		if (play(220,QUARTER_NOTE) == STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody29
;BUZZ.c,295 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody29:
;BUZZ.c,296 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody30:
SUBS	R7, R7, #1
BNE	L_play_melody30
NOP
NOP
NOP
;BUZZ.c,297 :: 		if (play(220,QUARTER_NOTE) == STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody32
;BUZZ.c,298 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody32:
;BUZZ.c,299 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody33:
SUBS	R7, R7, #1
BNE	L_play_melody33
NOP
NOP
NOP
;BUZZ.c,300 :: 		if (play(220,QUARTER_NOTE) == STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody35
;BUZZ.c,301 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody35:
;BUZZ.c,302 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody36:
SUBS	R7, R7, #1
BNE	L_play_melody36
NOP
NOP
NOP
;BUZZ.c,303 :: 		if (play(F3,E+S) == STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody38
;BUZZ.c,304 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody38:
;BUZZ.c,305 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody39:
SUBS	R7, R7, #1
BNE	L_play_melody39
NOP
NOP
NOP
;BUZZ.c,306 :: 		if (play(C4,S) == STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody41
;BUZZ.c,307 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody41:
;BUZZ.c,308 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody42:
SUBS	R7, R7, #1
BNE	L_play_melody42
NOP
NOP
NOP
;BUZZ.c,310 :: 		if (play(LA3,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody44
;BUZZ.c,311 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody44:
;BUZZ.c,312 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody45:
SUBS	R7, R7, #1
BNE	L_play_melody45
NOP
NOP
NOP
;BUZZ.c,313 :: 		if (play(F3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody47
;BUZZ.c,314 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody47:
;BUZZ.c,315 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody48:
SUBS	R7, R7, #1
BNE	L_play_melody48
NOP
NOP
NOP
;BUZZ.c,316 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody50
;BUZZ.c,317 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody50:
;BUZZ.c,318 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody51:
SUBS	R7, R7, #1
BNE	L_play_melody51
NOP
NOP
NOP
;BUZZ.c,319 :: 		if (play(LA3,H)== STOP_PLAYING)
MOVW	R1, #600
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody53
;BUZZ.c,320 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody53:
;BUZZ.c,321 :: 		Delay_ms(1+H);
MOVW	R7, #53822
MOVT	R7, #366
NOP
NOP
L_play_melody54:
SUBS	R7, R7, #1
BNE	L_play_melody54
NOP
NOP
NOP
;BUZZ.c,323 :: 		if (play(E4,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #329
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody56
;BUZZ.c,324 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody56:
;BUZZ.c,325 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody57:
SUBS	R7, R7, #1
BNE	L_play_melody57
NOP
NOP
NOP
;BUZZ.c,326 :: 		if (play(E4,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #329
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody59
;BUZZ.c,327 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody59:
;BUZZ.c,328 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody60:
SUBS	R7, R7, #1
BNE	L_play_melody60
NOP
NOP
NOP
;BUZZ.c,329 :: 		if (play(E4,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #329
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody62
;BUZZ.c,330 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody62:
;BUZZ.c,331 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody63:
SUBS	R7, R7, #1
BNE	L_play_melody63
NOP
NOP
NOP
;BUZZ.c,332 :: 		if (play(F4,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVW	R0, #349
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody65
;BUZZ.c,333 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody65:
;BUZZ.c,334 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody66:
SUBS	R7, R7, #1
BNE	L_play_melody66
NOP
NOP
NOP
;BUZZ.c,335 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody68
;BUZZ.c,336 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody68:
;BUZZ.c,337 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody69:
SUBS	R7, R7, #1
BNE	L_play_melody69
NOP
NOP
NOP
;BUZZ.c,339 :: 		if (play(Ab3,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #207
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody71
;BUZZ.c,340 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody71:
;BUZZ.c,341 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody72:
SUBS	R7, R7, #1
BNE	L_play_melody72
NOP
NOP
NOP
;BUZZ.c,342 :: 		if (play(F3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody74
;BUZZ.c,343 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody74:
;BUZZ.c,344 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody75:
SUBS	R7, R7, #1
BNE	L_play_melody75
NOP
NOP
NOP
;BUZZ.c,345 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody77
;BUZZ.c,346 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody77:
;BUZZ.c,347 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody78:
SUBS	R7, R7, #1
BNE	L_play_melody78
NOP
NOP
NOP
;BUZZ.c,348 :: 		if (play(LA3,H)== STOP_PLAYING)
MOVW	R1, #600
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody80
;BUZZ.c,349 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody80:
;BUZZ.c,350 :: 		Delay_ms(1+H);
MOVW	R7, #53822
MOVT	R7, #366
NOP
NOP
L_play_melody81:
SUBS	R7, R7, #1
BNE	L_play_melody81
NOP
NOP
NOP
;BUZZ.c,352 :: 		if (play(LA4,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #440
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody83
;BUZZ.c,353 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody83:
;BUZZ.c,354 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody84:
SUBS	R7, R7, #1
BNE	L_play_melody84
NOP
NOP
NOP
;BUZZ.c,355 :: 		if (play(LA3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody86
;BUZZ.c,356 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody86:
;BUZZ.c,357 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody87:
SUBS	R7, R7, #1
BNE	L_play_melody87
NOP
NOP
NOP
;BUZZ.c,358 :: 		if (play(LA3,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody89
;BUZZ.c,359 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody89:
;BUZZ.c,360 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody90:
SUBS	R7, R7, #1
BNE	L_play_melody90
NOP
NOP
NOP
;BUZZ.c,361 :: 		if (play(LA4,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #440
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody92
;BUZZ.c,362 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody92:
;BUZZ.c,363 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody93:
SUBS	R7, R7, #1
BNE	L_play_melody93
NOP
NOP
NOP
;BUZZ.c,364 :: 		if (play(Ab4,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVW	R0, #415
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody95
;BUZZ.c,365 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody95:
;BUZZ.c,366 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody96:
SUBS	R7, R7, #1
BNE	L_play_melody96
NOP
NOP
NOP
;BUZZ.c,367 :: 		if (play(G4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #392
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody98
;BUZZ.c,368 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody98:
;BUZZ.c,369 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody99:
SUBS	R7, R7, #1
BNE	L_play_melody99
NOP
NOP
NOP
;BUZZ.c,371 :: 		if (play(Gb4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #369
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody101
;BUZZ.c,372 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody101:
;BUZZ.c,373 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody102:
SUBS	R7, R7, #1
BNE	L_play_melody102
NOP
NOP
NOP
;BUZZ.c,374 :: 		if (play(E4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #329
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody104
;BUZZ.c,375 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody104:
;BUZZ.c,376 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody105:
SUBS	R7, R7, #1
BNE	L_play_melody105
NOP
NOP
NOP
;BUZZ.c,377 :: 		if (play(F4,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVW	R0, #349
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody107
;BUZZ.c,378 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody107:
;BUZZ.c,379 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody108:
SUBS	R7, R7, #1
BNE	L_play_melody108
NOP
NOP
NOP
;BUZZ.c,380 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody110:
SUBS	R7, R7, #1
BNE	L_play_melody110
NOP
NOP
NOP
;BUZZ.c,381 :: 		if (play(Bb3,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVS	R0, #233
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody112
;BUZZ.c,382 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody112:
;BUZZ.c,383 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody113:
SUBS	R7, R7, #1
BNE	L_play_melody113
NOP
NOP
NOP
;BUZZ.c,384 :: 		if (play(Eb4,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #311
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody115
;BUZZ.c,385 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody115:
;BUZZ.c,386 :: 		Delay_ms(1+QUARTER_NOTE);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody116:
SUBS	R7, R7, #1
BNE	L_play_melody116
NOP
NOP
NOP
;BUZZ.c,387 :: 		if (play(D4,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVW	R0, #293
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody118
;BUZZ.c,388 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody118:
;BUZZ.c,389 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody119:
SUBS	R7, R7, #1
BNE	L_play_melody119
NOP
NOP
NOP
;BUZZ.c,390 :: 		if (play(Db4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #277
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody121
;BUZZ.c,391 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody121:
;BUZZ.c,392 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody122:
SUBS	R7, R7, #1
BNE	L_play_melody122
NOP
NOP
NOP
;BUZZ.c,394 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody124
;BUZZ.c,395 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody124:
;BUZZ.c,396 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody125:
SUBS	R7, R7, #1
BNE	L_play_melody125
NOP
NOP
NOP
;BUZZ.c,397 :: 		if (play(B3,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVS	R0, #246
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody127
;BUZZ.c,398 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody127:
;BUZZ.c,399 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody128:
SUBS	R7, R7, #1
BNE	L_play_melody128
NOP
NOP
NOP
;BUZZ.c,400 :: 		if (play(C4,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody130
;BUZZ.c,401 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody130:
;BUZZ.c,402 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody131:
SUBS	R7, R7, #1
BNE	L_play_melody131
NOP
NOP
NOP
;BUZZ.c,403 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody133:
SUBS	R7, R7, #1
BNE	L_play_melody133
NOP
NOP
NOP
;BUZZ.c,404 :: 		if (play(F3,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody135
;BUZZ.c,405 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody135:
;BUZZ.c,406 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody136:
SUBS	R7, R7, #1
BNE	L_play_melody136
NOP
NOP
NOP
;BUZZ.c,407 :: 		if (play(Ab3,QUARTER_NOTE)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #207
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody138
;BUZZ.c,408 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody138:
;BUZZ.c,409 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody139:
SUBS	R7, R7, #1
BNE	L_play_melody139
NOP
NOP
NOP
;BUZZ.c,410 :: 		if (play(F3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody141
;BUZZ.c,411 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody141:
;BUZZ.c,412 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody142:
SUBS	R7, R7, #1
BNE	L_play_melody142
NOP
NOP
NOP
;BUZZ.c,413 :: 		if (play(LA3,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody144
;BUZZ.c,414 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody144:
;BUZZ.c,415 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody145:
SUBS	R7, R7, #1
BNE	L_play_melody145
NOP
NOP
NOP
;BUZZ.c,417 :: 		if (play(C4,Q)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody147
;BUZZ.c,418 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody147:
;BUZZ.c,419 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody148:
SUBS	R7, R7, #1
BNE	L_play_melody148
NOP
NOP
NOP
;BUZZ.c,420 :: 		if (play(LA3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody150
;BUZZ.c,421 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody150:
;BUZZ.c,422 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody151:
SUBS	R7, R7, #1
BNE	L_play_melody151
NOP
NOP
NOP
;BUZZ.c,423 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody153
;BUZZ.c,424 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody153:
;BUZZ.c,425 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody154:
SUBS	R7, R7, #1
BNE	L_play_melody154
NOP
NOP
NOP
;BUZZ.c,426 :: 		if (play(E4,H)== STOP_PLAYING)
MOVW	R1, #600
SXTH	R1, R1
MOVW	R0, #329
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody156
;BUZZ.c,427 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody156:
;BUZZ.c,428 :: 		Delay_ms(1+H);
MOVW	R7, #53822
MOVT	R7, #366
NOP
NOP
L_play_melody157:
SUBS	R7, R7, #1
BNE	L_play_melody157
NOP
NOP
NOP
;BUZZ.c,430 :: 		if (play(LA4,Q)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #440
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody159
;BUZZ.c,431 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody159:
;BUZZ.c,432 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody160:
SUBS	R7, R7, #1
BNE	L_play_melody160
NOP
NOP
NOP
;BUZZ.c,433 :: 		if (play(LA3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody162
;BUZZ.c,434 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody162:
;BUZZ.c,435 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody163:
SUBS	R7, R7, #1
BNE	L_play_melody163
NOP
NOP
NOP
;BUZZ.c,436 :: 		if (play(LA3,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody165
;BUZZ.c,437 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody165:
;BUZZ.c,438 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody166:
SUBS	R7, R7, #1
BNE	L_play_melody166
NOP
NOP
NOP
;BUZZ.c,439 :: 		if (play(LA4,Q)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #440
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody168
;BUZZ.c,440 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody168:
;BUZZ.c,441 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody169:
SUBS	R7, R7, #1
BNE	L_play_melody169
NOP
NOP
NOP
;BUZZ.c,442 :: 		if (play(Ab4,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVW	R0, #415
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody171
;BUZZ.c,443 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody171:
;BUZZ.c,444 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody172:
SUBS	R7, R7, #1
BNE	L_play_melody172
NOP
NOP
NOP
;BUZZ.c,445 :: 		if (play(G4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #392
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody174
;BUZZ.c,446 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody174:
;BUZZ.c,447 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody175:
SUBS	R7, R7, #1
BNE	L_play_melody175
NOP
NOP
NOP
;BUZZ.c,449 :: 		if (play(Gb4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #369
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody177
;BUZZ.c,450 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody177:
;BUZZ.c,451 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody178:
SUBS	R7, R7, #1
BNE	L_play_melody178
NOP
NOP
NOP
;BUZZ.c,452 :: 		if (play(E4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #329
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody180
;BUZZ.c,453 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody180:
;BUZZ.c,454 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody181:
SUBS	R7, R7, #1
BNE	L_play_melody181
NOP
NOP
NOP
;BUZZ.c,455 :: 		if (play(F4,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVW	R0, #349
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody183
;BUZZ.c,456 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody183:
;BUZZ.c,457 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody184:
SUBS	R7, R7, #1
BNE	L_play_melody184
NOP
NOP
NOP
;BUZZ.c,458 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody186:
SUBS	R7, R7, #1
BNE	L_play_melody186
NOP
NOP
NOP
;BUZZ.c,459 :: 		if (play(Bb3,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVS	R0, #233
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody188
;BUZZ.c,460 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody188:
;BUZZ.c,461 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody189:
SUBS	R7, R7, #1
BNE	L_play_melody189
NOP
NOP
NOP
;BUZZ.c,462 :: 		if (play(Eb4,Q)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVW	R0, #311
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody191
;BUZZ.c,463 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody191:
;BUZZ.c,464 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody192:
SUBS	R7, R7, #1
BNE	L_play_melody192
NOP
NOP
NOP
;BUZZ.c,465 :: 		if (play(D4,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVW	R0, #293
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody194
;BUZZ.c,466 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody194:
;BUZZ.c,467 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody195:
SUBS	R7, R7, #1
BNE	L_play_melody195
NOP
NOP
NOP
;BUZZ.c,468 :: 		if (play(Db4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #277
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody197
;BUZZ.c,469 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody197:
;BUZZ.c,470 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody198:
SUBS	R7, R7, #1
BNE	L_play_melody198
NOP
NOP
NOP
;BUZZ.c,472 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody200
;BUZZ.c,473 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody200:
;BUZZ.c,474 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody201:
SUBS	R7, R7, #1
BNE	L_play_melody201
NOP
NOP
NOP
;BUZZ.c,475 :: 		if (play(B3,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVS	R0, #246
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody203
;BUZZ.c,476 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody203:
;BUZZ.c,477 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody204:
SUBS	R7, R7, #1
BNE	L_play_melody204
NOP
NOP
NOP
;BUZZ.c,478 :: 		if (play(C4,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody206
;BUZZ.c,479 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody206:
;BUZZ.c,480 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody207:
SUBS	R7, R7, #1
BNE	L_play_melody207
NOP
NOP
NOP
;BUZZ.c,481 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody209:
SUBS	R7, R7, #1
BNE	L_play_melody209
NOP
NOP
NOP
;BUZZ.c,482 :: 		if (play(F3,E)== STOP_PLAYING)
MOVS	R1, #150
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody211
;BUZZ.c,483 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody211:
;BUZZ.c,484 :: 		Delay_ms(1+E);
MOVW	R7, #10686
MOVT	R7, #92
NOP
NOP
L_play_melody212:
SUBS	R7, R7, #1
BNE	L_play_melody212
NOP
NOP
NOP
;BUZZ.c,485 :: 		if (play(Ab3,Q)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #207
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody214
;BUZZ.c,486 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody214:
;BUZZ.c,487 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody215:
SUBS	R7, R7, #1
BNE	L_play_melody215
NOP
NOP
NOP
;BUZZ.c,488 :: 		if (play(F3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody217
;BUZZ.c,489 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody217:
;BUZZ.c,490 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody218:
SUBS	R7, R7, #1
BNE	L_play_melody218
NOP
NOP
NOP
;BUZZ.c,491 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody220
;BUZZ.c,492 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody220:
;BUZZ.c,493 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody221:
SUBS	R7, R7, #1
BNE	L_play_melody221
NOP
NOP
NOP
;BUZZ.c,495 :: 		if (play(LA3,Q)== STOP_PLAYING)
MOVW	R1, #300
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody223
;BUZZ.c,496 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody223:
;BUZZ.c,497 :: 		Delay_ms(1+Q);
MOVW	R7, #46910
MOVT	R7, #183
NOP
NOP
L_play_melody224:
SUBS	R7, R7, #1
BNE	L_play_melody224
NOP
NOP
NOP
;BUZZ.c,498 :: 		if (play(F3,E+S)== STOP_PLAYING)
MOVS	R1, #225
SXTH	R1, R1
MOVS	R0, #174
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody226
;BUZZ.c,499 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody226:
;BUZZ.c,500 :: 		Delay_ms(1+E+S);
MOVW	R7, #61566
MOVT	R7, #137
NOP
NOP
L_play_melody227:
SUBS	R7, R7, #1
BNE	L_play_melody227
NOP
NOP
NOP
;BUZZ.c,501 :: 		if (play(C4,S)== STOP_PLAYING)
MOVS	R1, #75
SXTH	R1, R1
MOVW	R0, #261
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody229
;BUZZ.c,502 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody229:
;BUZZ.c,503 :: 		Delay_ms(1+S);
MOVW	R7, #25342
MOVT	R7, #46
NOP
NOP
L_play_melody230:
SUBS	R7, R7, #1
BNE	L_play_melody230
NOP
NOP
NOP
;BUZZ.c,504 :: 		if (play(LA3,H)== STOP_PLAYING)
MOVW	R1, #600
SXTH	R1, R1
MOVS	R0, #220
BL	_play+0
CMP	R0, #1
IT	NE
BNE	L_play_melody232
;BUZZ.c,505 :: 		break;
IT	AL
BAL	L_play_melody28
L_play_melody232:
;BUZZ.c,506 :: 		Delay_ms(1+H);
MOVW	R7, #53822
MOVT	R7, #366
NOP
NOP
L_play_melody233:
SUBS	R7, R7, #1
BNE	L_play_melody233
NOP
NOP
NOP
;BUZZ.c,508 :: 		Delay_ms(2*H);
MOVW	R7, #27646
MOVT	R7, #732
NOP
NOP
L_play_melody235:
SUBS	R7, R7, #1
BNE	L_play_melody235
NOP
NOP
NOP
;BUZZ.c,509 :: 		}
IT	AL
BAL	L_play_melody27
L_play_melody28:
;BUZZ.c,510 :: 		}
L_end_play_melody:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _play_melody
_main:
;BUZZ.c,514 :: 		int main(void)
SUB	SP, SP, #4
;BUZZ.c,516 :: 		cntr = 0;
MOVS	R1, #0
SXTH	R1, R1
MOVW	R0, #lo_addr(_cntr+0)
MOVT	R0, #hi_addr(_cntr+0)
STRH	R1, [R0, #0]
;BUZZ.c,517 :: 		OLED_Init();
BL	_OLED_Init+0
;BUZZ.c,518 :: 		OLED_DrawImage( BUZZ_bmp, 0, 0 );
MOVW	R0, #lo_addr(_BUZZ_bmp+0)
MOVT	R0, #hi_addr(_BUZZ_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;BUZZ.c,521 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 );
MOV	R1, #8388608
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;BUZZ.c,524 :: 		UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_TWO_STOPBITS,  &_GPIO_Module_UART4_PE24_25 );
MOVW	R0, #lo_addr(__GPIO_Module_UART4_PE24_25+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART4_PE24_25+0)
PUSH	(R0)
MOVW	R3, #32
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #230400
BL	_UART4_Init_Advanced+0
ADD	SP, SP, #4
;BUZZ.c,526 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;BUZZ.c,527 :: 		NVIC_IntEnable( IVT_INT_UART4_RX_TX );
MOVW	R0, #82
BL	_NVIC_IntEnable+0
;BUZZ.c,529 :: 		UART4_C2_REG |= 1 << 5;
MOVW	R1, 1074700291
MOVT	R1, 16398
LDRB	R0, [R1, #0]
ORR	R0, R0, #32
STRB	R0, [R1, #0]
;BUZZ.c,532 :: 		KW40_RST_CLEAR();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PCOR+0)
MOVT	R0, #hi_addr(PTB_PCOR+0)
STR	R1, [R0, #0]
;BUZZ.c,533 :: 		Delay_ms( 10 );
MOVW	R7, #6782
MOVT	R7, #6
NOP
NOP
L_main237:
SUBS	R7, R7, #1
BNE	L_main237
NOP
NOP
NOP
;BUZZ.c,534 :: 		KW40_RST_SET();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PSOR+0)
MOVT	R0, #hi_addr(PTB_PSOR+0)
STR	R1, [R0, #0]
;BUZZ.c,535 :: 		Delay_ms( 200 );
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_main239:
SUBS	R7, R7, #1
BNE	L_main239
NOP
NOP
NOP
;BUZZ.c,536 :: 		while ( 1 )
L_main241:
;BUZZ.c,541 :: 		if ( touch_invalid != pressedTouch )
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #255
IT	EQ
BEQ	L_main243
;BUZZ.c,543 :: 		switch ( pressedTouch )
IT	AL
BAL	L_main244
;BUZZ.c,545 :: 		case touch_left:
L_main246:
;BUZZ.c,547 :: 		playing = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(_playing+0)
MOVT	R0, #hi_addr(_playing+0)
STR	R1, [R0, #0]
;BUZZ.c,548 :: 		play_melody();
BL	_play_melody+0
;BUZZ.c,549 :: 		break;
IT	AL
BAL	L_main245
;BUZZ.c,551 :: 		}
L_main244:
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main246
L_main245:
;BUZZ.c,552 :: 		}
L_main243:
;BUZZ.c,553 :: 		}
IT	AL
BAL	L_main241
;BUZZ.c,554 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_IRQ_Uart4Handler:
;BUZZ.c,558 :: 		void IRQ_Uart4Handler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
SUB	SP, SP, #4
STR	LR, [SP, #0]
;BUZZ.c,561 :: 		volatile uint8_t foo = UART4_S1;
MOVW	R0, #lo_addr(UART4_S1+0)
MOVT	R0, #hi_addr(UART4_S1+0)
; foo start address is: 0 (R0)
LDRB	R0, [R0, #0]
; foo end address is: 0 (R0)
;BUZZ.c,562 :: 		uint8_t readData = UART4_D;
MOVW	R0, #lo_addr(UART4_D+0)
MOVT	R0, #hi_addr(UART4_D+0)
; readData start address is: 4 (R1)
LDRB	R1, [R0, #0]
;BUZZ.c,563 :: 		*pktBuf = readData;
MOVW	R0, #lo_addr(_pktBuf+0)
MOVT	R0, #hi_addr(_pktBuf+0)
LDR	R0, [R0, #0]
STRB	R1, [R0, #0]
; readData end address is: 4 (R1)
;BUZZ.c,565 :: 		PacketParser();
BL	BUZZ_PacketParser+0
;BUZZ.c,566 :: 		if(cntr != 0)
MOVW	R0, #lo_addr(_cntr+0)
MOVT	R0, #hi_addr(_cntr+0)
LDRSH	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_IRQ_Uart4Handler247
;BUZZ.c,567 :: 		if ( touch_invalid != pressedTouch )
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #255
IT	EQ
BEQ	L_IRQ_Uart4Handler248
;BUZZ.c,569 :: 		switch ( pressedTouch )
IT	AL
BAL	L_IRQ_Uart4Handler249
;BUZZ.c,571 :: 		case touch_left:
L_IRQ_Uart4Handler251:
;BUZZ.c,573 :: 		if(playing)
MOVW	R1, #lo_addr(_playing+0)
MOVT	R1, #hi_addr(_playing+0)
LDR	R0, [R1, #0]
CMP	R0, #0
IT	EQ
BEQ	L_IRQ_Uart4Handler252
;BUZZ.c,575 :: 		STOPED = ~STOPED;
MOVW	R1, #lo_addr(_STOPED+0)
MOVT	R1, #hi_addr(_STOPED+0)
LDR	R0, [R1, #0]
EOR	R0, R0, #1
STR	R0, [R1, #0]
;BUZZ.c,576 :: 		if(cntr == 50)
MOVW	R0, #lo_addr(_cntr+0)
MOVT	R0, #hi_addr(_cntr+0)
LDRSH	R0, [R0, #0]
CMP	R0, #50
IT	NE
BNE	L_IRQ_Uart4Handler253
;BUZZ.c,577 :: 		cntr = 1;
MOVS	R1, #1
SXTH	R1, R1
MOVW	R0, #lo_addr(_cntr+0)
MOVT	R0, #hi_addr(_cntr+0)
STRH	R1, [R0, #0]
L_IRQ_Uart4Handler253:
;BUZZ.c,578 :: 		}
L_IRQ_Uart4Handler252:
;BUZZ.c,581 :: 		}
IT	AL
BAL	L_IRQ_Uart4Handler250
L_IRQ_Uart4Handler249:
MOVW	R0, #lo_addr(BUZZ_pressedTouch+0)
MOVT	R0, #hi_addr(BUZZ_pressedTouch+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_IRQ_Uart4Handler251
L_IRQ_Uart4Handler250:
;BUZZ.c,582 :: 		}
L_IRQ_Uart4Handler248:
L_IRQ_Uart4Handler247:
;BUZZ.c,583 :: 		cntr++;
MOVW	R1, #lo_addr(_cntr+0)
MOVT	R1, #hi_addr(_cntr+0)
LDRSH	R0, [R1, #0]
ADDS	R0, R0, #1
STRH	R0, [R1, #0]
;BUZZ.c,584 :: 		}
L_end_IRQ_Uart4Handler:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _IRQ_Uart4Handler
