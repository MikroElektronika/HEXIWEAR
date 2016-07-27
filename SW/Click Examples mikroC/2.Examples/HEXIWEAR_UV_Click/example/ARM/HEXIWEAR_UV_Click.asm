_main:
;HEXIWEAR_UV_Click.c,85 :: 		void main() org 0x1000
;HEXIWEAR_UV_Click.c,88 :: 		measurement = 0;
;HEXIWEAR_UV_Click.c,91 :: 		InitModules();
BL	HEXIWEAR_UV_Click_InitModules+0
;HEXIWEAR_UV_Click.c,93 :: 		while(1)
L_main0:
;HEXIWEAR_UV_Click.c,96 :: 		measurement = GetADC();
BL	HEXIWEAR_UV_Click_GetADC+0
;HEXIWEAR_UV_Click.c,99 :: 		ProcessValue( measurement );
BL	HEXIWEAR_UV_Click_ProcessValue+0
;HEXIWEAR_UV_Click.c,102 :: 		Delay_ms(500);
MOVW	R7, #11518
MOVT	R7, #305
NOP
NOP
L_main2:
SUBS	R7, R7, #1
BNE	L_main2
NOP
NOP
NOP
;HEXIWEAR_UV_Click.c,103 :: 		}
IT	AL
BAL	L_main0
;HEXIWEAR_UV_Click.c,104 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
HEXIWEAR_UV_Click_InitModules:
;HEXIWEAR_UV_Click.c,117 :: 		static void InitModules()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_UV_Click.c,119 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 );
MOV	R1, #524288
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_UV_Click.c,121 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_UV_Click.c,122 :: 		OLED_DrawImage( &uv_bmp, 0, 0 );
MOVW	R0, #lo_addr(_uv_bmp+0)
MOVT	R0, #hi_addr(_uv_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_UV_Click.c,124 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_UV_Click.c,125 :: 		OLED_WriteText( uvText, 20, 75 );
MOVS	R2, #75
MOVS	R1, #20
MOVW	R0, #lo_addr(HEXIWEAR_UV_Click_uvText+0)
MOVT	R0, #hi_addr(HEXIWEAR_UV_Click_uvText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_UV_Click.c,126 :: 		OLED_WriteText( uvUnit, 72, 75 );
MOVS	R2, #75
MOVS	R1, #72
MOVW	R0, #lo_addr(HEXIWEAR_UV_Click_uvUnit+0)
MOVT	R0, #hi_addr(HEXIWEAR_UV_Click_uvUnit+0)
BL	_OLED_WriteText+0
;HEXIWEAR_UV_Click.c,129 :: 		ADC0_Init();
BL	_ADC0_Init+0
;HEXIWEAR_UV_Click.c,131 :: 		Delay_ms(100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_HEXIWEAR_UV_Click_InitModules4:
SUBS	R7, R7, #1
BNE	L_HEXIWEAR_UV_Click_InitModules4
NOP
NOP
NOP
;HEXIWEAR_UV_Click.c,134 :: 		UV_Enable  = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_UV_Click.c,135 :: 		}
L_end_InitModules:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of HEXIWEAR_UV_Click_InitModules
HEXIWEAR_UV_Click_GetADC:
;HEXIWEAR_UV_Click.c,144 :: 		static uint16_t GetADC()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_UV_Click.c,148 :: 		adcVal = 0,
;HEXIWEAR_UV_Click.c,149 :: 		avrg   = 0;
; avrg start address is: 32 (R8)
MOV	R8, #0
;HEXIWEAR_UV_Click.c,151 :: 		for ( i = 0; i < 16; i++ )
; i start address is: 28 (R7)
MOVS	R7, #0
; avrg end address is: 32 (R8)
; i end address is: 28 (R7)
L_HEXIWEAR_UV_Click_GetADC6:
; i start address is: 28 (R7)
; avrg start address is: 32 (R8)
CMP	R7, #16
IT	CS
BCS	L_HEXIWEAR_UV_Click_GetADC7
;HEXIWEAR_UV_Click.c,153 :: 		adcVal = ADC0_Get_Sample( 13 );
MOVS	R0, #13
BL	_ADC0_Get_Sample+0
;HEXIWEAR_UV_Click.c,154 :: 		avrg  += adcVal;
ADD	R0, R8, R0, LSL #0
; avrg end address is: 32 (R8)
; avrg start address is: 4 (R1)
MOV	R1, R0
;HEXIWEAR_UV_Click.c,151 :: 		for ( i = 0; i < 16; i++ )
ADDS	R7, R7, #1
;HEXIWEAR_UV_Click.c,155 :: 		}
MOV	R8, R1
; avrg end address is: 4 (R1)
; i end address is: 28 (R7)
IT	AL
BAL	L_HEXIWEAR_UV_Click_GetADC6
L_HEXIWEAR_UV_Click_GetADC7:
;HEXIWEAR_UV_Click.c,157 :: 		return ( avrg >> 4 );
; avrg start address is: 32 (R8)
LSR	R0, R8, #4
; avrg end address is: 32 (R8)
UXTH	R0, R0
;HEXIWEAR_UV_Click.c,158 :: 		}
L_end_GetADC:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of HEXIWEAR_UV_Click_GetADC
HEXIWEAR_UV_Click_ProcessValue:
;HEXIWEAR_UV_Click.c,167 :: 		static void ProcessValue( uint16_t valueTemp )
; valueTemp start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; valueTemp end address is: 0 (R0)
; valueTemp start address is: 0 (R0)
;HEXIWEAR_UV_Click.c,172 :: 		if ((valueTemp > 1100) && (valueTemp < 4095))
MOVW	R1, #1100
CMP	R0, R1
IT	LS
BLS	L_HEXIWEAR_UV_Click_ProcessValue15
MOVW	R1, #4095
CMP	R0, R1
IT	CS
BCS	L_HEXIWEAR_UV_Click_ProcessValue14
L_HEXIWEAR_UV_Click_ProcessValue13:
;HEXIWEAR_UV_Click.c,175 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
STRH	R0, [SP, #4]
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_UV_Click.c,176 :: 		OLED_WriteText( uvLevel, 42, 75 );
MOVS	R2, #75
MOVS	R1, #42
MOVW	R0, #lo_addr(HEXIWEAR_UV_Click_uvLevel+0)
MOVT	R0, #hi_addr(HEXIWEAR_UV_Click_uvLevel+0)
BL	_OLED_WriteText+0
LDRH	R0, [SP, #4]
;HEXIWEAR_UV_Click.c,179 :: 		UV_val = valueTemp * 3300.0 / 4096.0;
VMOV	S1, R0
VCVT.F32	#0, S1, S1
; valueTemp end address is: 0 (R0)
MOVW	R1, #16384
MOVT	R1, #17742
VMOV	S0, R1
VMUL.F32	S1, S1, S0
MOV	R1, #1166016512
VMOV	S0, R1
VDIV.F32	S0, S1, S0
;HEXIWEAR_UV_Click.c,180 :: 		WordToStr( (uint16_t)UV_val, uvLevel );
VCVT	#1, .F32, S0, S0
VMOV	R1, S0
UXTH	R1, R1
UXTH	R0, R1
MOVW	R1, #lo_addr(HEXIWEAR_UV_Click_uvLevel+0)
MOVT	R1, #hi_addr(HEXIWEAR_UV_Click_uvLevel+0)
BL	_WordToStr+0
;HEXIWEAR_UV_Click.c,181 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_UV_Click.c,182 :: 		OLED_WriteText( uvLevel, 42, 75 );
MOVS	R2, #75
MOVS	R1, #42
MOVW	R0, #lo_addr(HEXIWEAR_UV_Click_uvLevel+0)
MOVT	R0, #hi_addr(HEXIWEAR_UV_Click_uvLevel+0)
BL	_OLED_WriteText+0
;HEXIWEAR_UV_Click.c,183 :: 		}
IT	AL
BAL	L_HEXIWEAR_UV_Click_ProcessValue12
;HEXIWEAR_UV_Click.c,172 :: 		if ((valueTemp > 1100) && (valueTemp < 4095))
L_HEXIWEAR_UV_Click_ProcessValue15:
L_HEXIWEAR_UV_Click_ProcessValue14:
;HEXIWEAR_UV_Click.c,187 :: 		}
L_HEXIWEAR_UV_Click_ProcessValue12:
;HEXIWEAR_UV_Click.c,188 :: 		}
L_end_ProcessValue:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of HEXIWEAR_UV_Click_ProcessValue
