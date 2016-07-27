_InitModules:
;HEXIWEAR_Alcohol_Click.c,116 :: 		void InitModules(void)
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Alcohol_Click.c,121 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Alcohol_Click.c,122 :: 		OLED_DrawImage(&alcohol_bmp, 0, 0);
MOVW	R0, #lo_addr(_alcohol_bmp+0)
MOVT	R0, #hi_addr(_alcohol_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Alcohol_Click.c,124 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Alcohol_Click.c,125 :: 		OLED_WriteText( ppmText, 25, 75 );
MOVS	R2, #75
MOVS	R1, #25
MOVW	R0, #lo_addr(HEXIWEAR_Alcohol_Click_ppmText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Alcohol_Click_ppmText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Alcohol_Click.c,127 :: 		ADC0_Init();
BL	_ADC0_Init+0
;HEXIWEAR_Alcohol_Click.c,130 :: 		Delay_ms(100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_InitModules0:
SUBS	R7, R7, #1
BNE	L_InitModules0
NOP
NOP
NOP
;HEXIWEAR_Alcohol_Click.c,131 :: 		}
L_end_InitModules:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _InitModules
_ReadSensor:
;HEXIWEAR_Alcohol_Click.c,143 :: 		void ReadSensor()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Alcohol_Click.c,145 :: 		adc_rd = ADC0_Get_Sample( 12 );
MOVS	R0, #12
BL	_ADC0_Get_Sample+0
MOVW	R1, #lo_addr(_adc_rd+0)
MOVT	R1, #hi_addr(_adc_rd+0)
STRH	R0, [R1, #0]
;HEXIWEAR_Alcohol_Click.c,148 :: 		delay_ms(10);
MOVW	R7, #6782
MOVT	R7, #6
NOP
NOP
L_ReadSensor2:
SUBS	R7, R7, #1
BNE	L_ReadSensor2
NOP
NOP
NOP
;HEXIWEAR_Alcohol_Click.c,149 :: 		}
L_end_ReadSensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ReadSensor
_CalculatePPM:
;HEXIWEAR_Alcohol_Click.c,161 :: 		void CalculatePPM()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Alcohol_Click.c,169 :: 		Vrl = (float)adc_rd * Vadc_33;
MOVW	R0, #lo_addr(_adc_rd+0)
MOVT	R0, #hi_addr(_adc_rd+0)
LDRH	R0, [R0, #0]
VMOV	S1, R0
VCVT.F32	#0, S1, S1
MOVW	R0, #13107
MOVT	R0, #14931
VMOV	S0, R0
VMUL.F32	S1, S1, S0
MOVW	R0, #lo_addr(_Vrl+0)
MOVT	R0, #hi_addr(_Vrl+0)
VSTR	#1, S1, [R0, #0]
;HEXIWEAR_Alcohol_Click.c,172 :: 		SensorRes = ( ( 5.0 - Vrl ) / Vrl ) * LoadRes;
VMOV.F32	S0, #5
VSUB.F32	S0, S0, S1
VDIV.F32	S1, S0, S1
MOVW	R0, #38912
MOVT	R0, #17955
VMOV	S0, R0
VMUL.F32	S1, S1, S0
MOVW	R0, #lo_addr(_SensorRes+0)
MOVT	R0, #hi_addr(_SensorRes+0)
VSTR	#1, S1, [R0, #0]
;HEXIWEAR_Alcohol_Click.c,173 :: 		ratio     = SensorRes / LoadRes;
MOVW	R0, #38912
MOVT	R0, #17955
VMOV	S0, R0
VDIV.F32	S0, S1, S0
MOVW	R0, #lo_addr(_ratio+0)
MOVT	R0, #hi_addr(_ratio+0)
VSTR	#1, S0, [R0, #0]
;HEXIWEAR_Alcohol_Click.c,176 :: 		lgPPM = ( log10( ratio ) * -1.5512 ) + 2.5911;
BL	_log10+0
MOVW	R0, #36281
MOVT	R0, #49094
VMOV	S1, R0
VMUL.F32	S1, S0, S1
MOVW	R0, #54421
MOVT	R0, #16421
VMOV	S0, R0
VADD.F32	S0, S1, S0
;HEXIWEAR_Alcohol_Click.c,178 :: 		ppm = pow( 10, lgPPM );
VMOV.F32	S1, S0
VMOV.F32	S0, #10
BL	_pow+0
MOVW	R0, #lo_addr(_ppm+0)
MOVT	R0, #hi_addr(_ppm+0)
VSTR	#1, S0, [R0, #0]
;HEXIWEAR_Alcohol_Click.c,179 :: 		}
L_end_CalculatePPM:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _CalculatePPM
_DisplayAlcoholValue:
;HEXIWEAR_Alcohol_Click.c,191 :: 		void DisplayAlcoholValue( unsigned int value )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRH	R0, [SP, #4]
;HEXIWEAR_Alcohol_Click.c,193 :: 		if ( value_old != value )
LDRH	R1, [SP, #4]
VMOV	S1, R1
VCVT.F32	#0, S1, S1
MOVW	R1, #lo_addr(_value_old+0)
MOVT	R1, #hi_addr(_value_old+0)
VLDR	#1, S0, [R1, #0]
VCMPE.F32	S0, S1
VMRS	#60, FPSCR
IT	EQ
BEQ	L_DisplayAlcoholValue4
;HEXIWEAR_Alcohol_Click.c,196 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Alcohol_Click.c,197 :: 		OLED_WriteText( text, 50, 75 );
MOVS	R2, #75
MOVS	R1, #50
MOVW	R0, #lo_addr(_text+0)
MOVT	R0, #hi_addr(_text+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Alcohol_Click.c,199 :: 		WordToStr(value, text);
MOVW	R1, #lo_addr(_text+0)
MOVT	R1, #hi_addr(_text+0)
LDRH	R0, [SP, #4]
BL	_WordToStr+0
;HEXIWEAR_Alcohol_Click.c,201 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Alcohol_Click.c,202 :: 		OLED_WriteText( text, 50, 75 );
MOVS	R2, #75
MOVS	R1, #50
MOVW	R0, #lo_addr(_text+0)
MOVT	R0, #hi_addr(_text+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Alcohol_Click.c,203 :: 		}
L_DisplayAlcoholValue4:
;HEXIWEAR_Alcohol_Click.c,204 :: 		value_old = value;
LDRH	R1, [SP, #4]
VMOV	S0, R1
VCVT.F32	#0, S0, S0
MOVW	R1, #lo_addr(_value_old+0)
MOVT	R1, #hi_addr(_value_old+0)
VSTR	#1, S0, [R1, #0]
;HEXIWEAR_Alcohol_Click.c,205 :: 		}
L_end_DisplayAlcoholValue:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _DisplayAlcoholValue
_main:
;HEXIWEAR_Alcohol_Click.c,211 :: 		void main()
;HEXIWEAR_Alcohol_Click.c,213 :: 		InitModules();
BL	_InitModules+0
;HEXIWEAR_Alcohol_Click.c,215 :: 		while(1)
L_main5:
;HEXIWEAR_Alcohol_Click.c,217 :: 		ReadSensor();
BL	_ReadSensor+0
;HEXIWEAR_Alcohol_Click.c,218 :: 		CalculatePPM();
BL	_CalculatePPM+0
;HEXIWEAR_Alcohol_Click.c,219 :: 		DisplayAlcoholValue( floor(ppm) );
MOVW	R0, #lo_addr(_ppm+0)
MOVT	R0, #hi_addr(_ppm+0)
VLDR	#1, S0, [R0, #0]
BL	_floor+0
VCVT	#1, .F32, S0, S0
VMOV	R0, S0
UXTH	R0, R0
BL	_DisplayAlcoholValue+0
;HEXIWEAR_Alcohol_Click.c,220 :: 		Delay_ms(500);
MOVW	R7, #11518
MOVT	R7, #305
NOP
NOP
L_main7:
SUBS	R7, R7, #1
BNE	L_main7
NOP
NOP
NOP
;HEXIWEAR_Alcohol_Click.c,221 :: 		}
IT	AL
BAL	L_main5
;HEXIWEAR_Alcohol_Click.c,222 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
