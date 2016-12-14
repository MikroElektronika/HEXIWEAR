_screen_init:
;HEXIWEAR_Proximity_2_Click.c,101 :: 		void screen_init(){
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Proximity_2_Click.c,102 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Proximity_2_Click.c,103 :: 		OLED_FillScreen( OLED_COLOR_BLACK );
MOVW	R0, #0
BL	_OLED_FillScreen+0
;HEXIWEAR_Proximity_2_Click.c,104 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Proximity_2_Click.c,105 :: 		OLED_DrawImage(Proximity2_bmp,0,0);
MOVW	R0, #lo_addr(_Proximity2_bmp+0)
MOVT	R0, #hi_addr(_Proximity2_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Proximity_2_Click.c,106 :: 		}
L_end_screen_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _screen_init
_main:
;HEXIWEAR_Proximity_2_Click.c,109 :: 		void main() {
;HEXIWEAR_Proximity_2_Click.c,110 :: 		I2C0_Init_Advanced(400000, &_GPIO_Module_I2C0_PD8_9);
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #6784
MOVT	R0, #6
BL	_I2C0_Init_Advanced+0
;HEXIWEAR_Proximity_2_Click.c,112 :: 		delay_ms(200);
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_main0:
SUBS	R7, R7, #1
BNE	L_main0
NOP
NOP
NOP
;HEXIWEAR_Proximity_2_Click.c,114 :: 		screen_init();
BL	_screen_init+0
;HEXIWEAR_Proximity_2_Click.c,116 :: 		MAX44000_Init();
BL	_MAX44000_Init+0
;HEXIWEAR_Proximity_2_Click.c,118 :: 		while(1){
L_main2:
;HEXIWEAR_Proximity_2_Click.c,119 :: 		ProxiValue = MAX44000_ReadRegister(PROX);
MOVS	R0, #22
BL	_MAX44000_ReadRegister+0
MOVW	R1, #lo_addr(_ProxiValue+0)
MOVT	R1, #hi_addr(_ProxiValue+0)
STRB	R0, [R1, #0]
;HEXIWEAR_Proximity_2_Click.c,120 :: 		ByteToStr(ProxiValue,Distance);
MOVW	R1, #lo_addr(_Distance+0)
MOVT	R1, #hi_addr(_Distance+0)
BL	_ByteToStr+0
;HEXIWEAR_Proximity_2_Click.c,121 :: 		value = (76-( ProxiValue / 3));
MOVW	R0, #lo_addr(_ProxiValue+0)
MOVT	R0, #hi_addr(_ProxiValue+0)
LDRB	R1, [R0, #0]
MOVS	R0, #3
UDIV	R0, R1, R0
UXTB	R0, R0
RSB	R2, R0, #76
MOVW	R0, #lo_addr(_value+0)
MOVT	R0, #hi_addr(_value+0)
STRH	R2, [R0, #0]
;HEXIWEAR_Proximity_2_Click.c,122 :: 		OLED_DrawBox (10, 76, value, 3, OLED_COLOR_RED);
MOVW	R1, #63488
UXTH	R0, R2
PUSH	(R1)
MOVS	R3, #3
UXTH	R2, R0
MOVS	R1, #76
MOVS	R0, #10
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Proximity_2_Click.c,123 :: 		if(ProxiOldValue != ProxiValue){
MOVW	R0, #lo_addr(_ProxiValue+0)
MOVT	R0, #hi_addr(_ProxiValue+0)
LDRB	R1, [R0, #0]
MOVW	R0, #lo_addr(_ProxiOldValue+0)
MOVT	R0, #hi_addr(_ProxiOldValue+0)
LDRB	R0, [R0, #0]
CMP	R0, R1
IT	EQ
BEQ	L_main4
;HEXIWEAR_Proximity_2_Click.c,124 :: 		OLED_DrawBox (10, 76, 76, 3, OLED_COLOR_WHITE);
MOVW	R0, #65535
PUSH	(R0)
MOVS	R3, #3
MOVS	R2, #76
MOVS	R1, #76
MOVS	R0, #10
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Proximity_2_Click.c,125 :: 		OLED_DrawBox (10, 76, value, 3, OLED_COLOR_RED);
MOVW	R1, #63488
MOVW	R0, #lo_addr(_value+0)
MOVT	R0, #hi_addr(_value+0)
LDRSH	R0, [R0, #0]
PUSH	(R1)
MOVS	R3, #3
UXTH	R2, R0
MOVS	R1, #76
MOVS	R0, #10
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_Proximity_2_Click.c,126 :: 		delay_ms(50);
MOVW	R7, #33918
MOVT	R7, #30
NOP
NOP
L_main5:
SUBS	R7, R7, #1
BNE	L_main5
NOP
NOP
NOP
;HEXIWEAR_Proximity_2_Click.c,127 :: 		}
L_main4:
;HEXIWEAR_Proximity_2_Click.c,128 :: 		ProxiOldValue = ProxiValue;
MOVW	R0, #lo_addr(_ProxiValue+0)
MOVT	R0, #hi_addr(_ProxiValue+0)
LDRB	R1, [R0, #0]
MOVW	R0, #lo_addr(_ProxiOldValue+0)
MOVT	R0, #hi_addr(_ProxiOldValue+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Proximity_2_Click.c,129 :: 		}
IT	AL
BAL	L_main2
;HEXIWEAR_Proximity_2_Click.c,130 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
