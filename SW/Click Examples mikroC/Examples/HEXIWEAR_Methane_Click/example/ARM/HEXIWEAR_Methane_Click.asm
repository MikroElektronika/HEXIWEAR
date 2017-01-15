_CalculatePPM:
;HEXIWEAR_Methane_Click.c,100 :: 		void CalculatePPM()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Methane_Click.c,103 :: 		Vrl = (double)adc_rd * Vadc_33;              // For 5V Vcc use Vadc_5  and  for 3V Vcc use Vadc_33
MOVW	R0, #lo_addr(_adc_rd+0)
MOVT	R0, #hi_addr(_adc_rd+0)
LDRH	R0, [R0, #0]
VMOV	S1, R0
VCVT.F32	#0, S1, S1
MOVW	R0, #13107
MOVT	R0, #14931
VMOV	S0, R0
VMUL.F32	S2, S1, S0
MOVW	R0, #lo_addr(_Vrl+0)
MOVT	R0, #hi_addr(_Vrl+0)
VSTR	#1, S2, [R0, #0]
;HEXIWEAR_Methane_Click.c,104 :: 		SensRes = LoadRes * (5 - Vrl)/Vrl;           // Calculate sensor resistance
VMOV.F32	S0, #5
VSUB.F32	S1, S0, S2
MOVW	R0, #38912
MOVT	R0, #17955
VMOV	S0, R0
VMUL.F32	S0, S0, S1
VDIV.F32	S1, S0, S2
MOVW	R0, #lo_addr(_SensRes+0)
MOVT	R0, #hi_addr(_SensRes+0)
VSTR	#1, S1, [R0, #0]
;HEXIWEAR_Methane_Click.c,105 :: 		ratio = SensRes/LoadRes;                     // Calculate ratio
MOVW	R0, #38912
MOVT	R0, #17955
VMOV	S0, R0
VDIV.F32	S0, S1, S0
MOVW	R0, #lo_addr(_ratio+0)
MOVT	R0, #hi_addr(_ratio+0)
VSTR	#1, S0, [R0, #0]
;HEXIWEAR_Methane_Click.c,106 :: 		lgPPM = (log10(ratio) * -0.8 ) + 0.9;        // Calculate ppm
BL	_log10+0
MOVW	R0, #52429
MOVT	R0, #48972
VMOV	S1, R0
VMUL.F32	S1, S0, S1
MOVW	R0, #26214
MOVT	R0, #16230
VMOV	S0, R0
VADD.F32	S0, S1, S0
;HEXIWEAR_Methane_Click.c,107 :: 		ppm = pow(10,lgPPM);                         // Calculate ppm
VMOV.F32	S1, S0
VMOV.F32	S0, #10
BL	_pow+0
MOVW	R0, #lo_addr(_ppm+0)
MOVT	R0, #hi_addr(_ppm+0)
VSTR	#1, S0, [R0, #0]
;HEXIWEAR_Methane_Click.c,108 :: 		}
L_end_CalculatePPM:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _CalculatePPM
_DisplayMethaneValue:
;HEXIWEAR_Methane_Click.c,121 :: 		void DisplayMethaneValue( uint16_t value )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRH	R0, [SP, #4]
;HEXIWEAR_Methane_Click.c,123 :: 		if (value_old != value)                              // If old value and current value are not equal
LDRH	R1, [SP, #4]
VMOV	S1, R1
VCVT.F32	#0, S1, S1
MOVW	R1, #lo_addr(_value_old+0)
MOVT	R1, #hi_addr(_value_old+0)
VLDR	#1, S0, [R1, #0]
VCMPE.F32	S0, S1
VMRS	#60, FPSCR
IT	EQ
BEQ	L_DisplayMethaneValue0
;HEXIWEAR_Methane_Click.c,126 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Methane_Click.c,127 :: 		OLED_WriteText( text, 50, 75 );
MOVS	R2, #75
MOVS	R1, #50
MOVW	R0, #lo_addr(_text+0)
MOVT	R0, #hi_addr(_text+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Methane_Click.c,129 :: 		WordToStr(value, text);
MOVW	R1, #lo_addr(_text+0)
MOVT	R1, #hi_addr(_text+0)
LDRH	R0, [SP, #4]
BL	_WordToStr+0
;HEXIWEAR_Methane_Click.c,131 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Methane_Click.c,132 :: 		OLED_WriteText( text, 50, 75 );
MOVS	R2, #75
MOVS	R1, #50
MOVW	R0, #lo_addr(_text+0)
MOVT	R0, #hi_addr(_text+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Methane_Click.c,133 :: 		}
L_DisplayMethaneValue0:
;HEXIWEAR_Methane_Click.c,134 :: 		value_old = value;
LDRH	R1, [SP, #4]
VMOV	S0, R1
VCVT.F32	#0, S0, S0
MOVW	R1, #lo_addr(_value_old+0)
MOVT	R1, #hi_addr(_value_old+0)
VSTR	#1, S0, [R1, #0]
;HEXIWEAR_Methane_Click.c,135 :: 		}
L_end_DisplayMethaneValue:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _DisplayMethaneValue
_ReadSensor:
;HEXIWEAR_Methane_Click.c,148 :: 		void ReadSensor()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Methane_Click.c,150 :: 		adc_rd = ADC1_Get_Sample( 12 );
MOVS	R0, #12
BL	_ADC1_Get_Sample+0
MOVW	R1, #lo_addr(_adc_rd+0)
MOVT	R1, #hi_addr(_adc_rd+0)
STRH	R0, [R1, #0]
;HEXIWEAR_Methane_Click.c,151 :: 		Delay_ms(10);
MOVW	R7, #6782
MOVT	R7, #6
NOP
NOP
L_ReadSensor1:
SUBS	R7, R7, #1
BNE	L_ReadSensor1
NOP
NOP
NOP
;HEXIWEAR_Methane_Click.c,152 :: 		}
L_end_ReadSensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ReadSensor
_InitModules:
;HEXIWEAR_Methane_Click.c,165 :: 		void InitModules()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Methane_Click.c,167 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Methane_Click.c,168 :: 		OLED_DrawImage( &methane_bmp, 0, 0 );
MOVW	R0, #lo_addr(_methane_bmp+0)
MOVT	R0, #hi_addr(_methane_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Methane_Click.c,170 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Methane_Click.c,171 :: 		OLED_WriteText( ppmText, 25, 75 );
MOVS	R2, #75
MOVS	R1, #25
MOVW	R0, #lo_addr(HEXIWEAR_Methane_Click_ppmText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Methane_Click_ppmText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Methane_Click.c,174 :: 		ADC1_Init();
BL	_ADC1_Init+0
;HEXIWEAR_Methane_Click.c,177 :: 		Delay_ms(100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_InitModules3:
SUBS	R7, R7, #1
BNE	L_InitModules3
NOP
NOP
NOP
;HEXIWEAR_Methane_Click.c,178 :: 		}
L_end_InitModules:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _InitModules
_main:
;HEXIWEAR_Methane_Click.c,184 :: 		void main()
;HEXIWEAR_Methane_Click.c,186 :: 		InitModules();
BL	_InitModules+0
;HEXIWEAR_Methane_Click.c,188 :: 		while(1)
L_main5:
;HEXIWEAR_Methane_Click.c,190 :: 		ReadSensor();
BL	_ReadSensor+0
;HEXIWEAR_Methane_Click.c,191 :: 		CalculatePPM();
BL	_CalculatePPM+0
;HEXIWEAR_Methane_Click.c,192 :: 		DisplayMethaneValue( ppm );
MOVW	R0, #lo_addr(_ppm+0)
MOVT	R0, #hi_addr(_ppm+0)
VLDR	#1, S0, [R0, #0]
VCVT	#1, .F32, S0, S0
VMOV	R0, S0
UXTH	R0, R0
BL	_DisplayMethaneValue+0
;HEXIWEAR_Methane_Click.c,193 :: 		Delay_ms(500);
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
;HEXIWEAR_Methane_Click.c,194 :: 		}
IT	AL
BAL	L_main5
;HEXIWEAR_Methane_Click.c,195 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
