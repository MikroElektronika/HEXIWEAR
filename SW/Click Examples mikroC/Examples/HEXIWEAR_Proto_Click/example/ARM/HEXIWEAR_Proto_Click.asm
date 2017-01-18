_main:
;HEXIWEAR_Proto_Click.c,86 :: 		void main() org 0x1000
;HEXIWEAR_Proto_Click.c,91 :: 		GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );
MOV	R1, #1024
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Proto_Click.c,93 :: 		GPIO_Digital_Input( &PTC_PDOR, _GPIO_PINMASK_4 );
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_Proto_Click.c,95 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Proto_Click.c,96 :: 		OLED_DrawImage( &protoOFF_bmp, 0, 0 );
MOVW	R0, #lo_addr(_protoOFF_bmp+0)
MOVT	R0, #hi_addr(_protoOFF_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Proto_Click.c,98 :: 		while (1)
L_main0:
;HEXIWEAR_Proto_Click.c,100 :: 		if ( BUTTON_ReadState() != oldState )
MOVW	R0, #lo_addr(PTC_PDIR+0)
MOVT	R0, #hi_addr(PTC_PDIR+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(_oldState+0)
MOVT	R0, #hi_addr(_oldState+0)
LDRB	R0, [R0, #0]
CMP	R1, R0
IT	EQ
BEQ	L_main2
;HEXIWEAR_Proto_Click.c,102 :: 		oldState = BUTTON_ReadState();
MOVW	R0, #lo_addr(PTC_PDIR+0)
MOVT	R0, #hi_addr(PTC_PDIR+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(_oldState+0)
MOVT	R0, #hi_addr(_oldState+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Proto_Click.c,103 :: 		switch ( oldState )
IT	AL
BAL	L_main3
;HEXIWEAR_Proto_Click.c,105 :: 		case BUTTON_State_ON:
L_main5:
;HEXIWEAR_Proto_Click.c,107 :: 		LED_ON();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTA_PSOR+0)
MOVT	R0, #hi_addr(PTA_PSOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Proto_Click.c,108 :: 		OLED_DrawImage( &protoON_bmp, 0, 0 );
MOVW	R0, #lo_addr(_protoON_bmp+0)
MOVT	R0, #hi_addr(_protoON_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Proto_Click.c,109 :: 		break;
IT	AL
BAL	L_main4
;HEXIWEAR_Proto_Click.c,112 :: 		case BUTTON_State_OFF:
L_main6:
;HEXIWEAR_Proto_Click.c,114 :: 		LED_OFF();
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTA_PCOR+0)
MOVT	R0, #hi_addr(PTA_PCOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Proto_Click.c,115 :: 		OLED_DrawImage( &protoOFF_bmp, 0, 0 );
MOVW	R0, #lo_addr(_protoOFF_bmp+0)
MOVT	R0, #hi_addr(_protoOFF_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Proto_Click.c,116 :: 		break;
IT	AL
BAL	L_main4
;HEXIWEAR_Proto_Click.c,119 :: 		default: {}
L_main7:
;HEXIWEAR_Proto_Click.c,120 :: 		}
IT	AL
BAL	L_main4
L_main3:
MOVW	R0, #lo_addr(_oldState+0)
MOVT	R0, #hi_addr(_oldState+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main5
MOVW	R0, #lo_addr(_oldState+0)
MOVT	R0, #hi_addr(_oldState+0)
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	EQ
BEQ	L_main6
IT	AL
BAL	L_main7
L_main4:
;HEXIWEAR_Proto_Click.c,121 :: 		}
L_main2:
;HEXIWEAR_Proto_Click.c,122 :: 		}
IT	AL
BAL	L_main0
;HEXIWEAR_Proto_Click.c,123 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
