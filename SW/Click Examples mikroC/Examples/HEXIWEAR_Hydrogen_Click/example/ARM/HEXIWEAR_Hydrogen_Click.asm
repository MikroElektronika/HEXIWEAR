_CalculatePPM:
;HEXIWEAR_Hydrogen_Click.c,100 :: 		void CalculatePPM()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Hydrogen_Click.c,103 :: 		Vrl = (double)adc_rd * Vadc_33;          // For 5V Vcc use Vadc_5 and for 3V Vcc use Vadc_33
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
;HEXIWEAR_Hydrogen_Click.c,104 :: 		SensRes = LoadRes * ( 5.0 - Vrl ) / Vrl; // Calculate sensor resistance
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
;HEXIWEAR_Hydrogen_Click.c,105 :: 		ratio = SensRes/LoadRes;                 // Calculate ratio
MOVW	R0, #38912
MOVT	R0, #17955
VMOV	S0, R0
VDIV.F32	S0, S1, S0
MOVW	R0, #lo_addr(_ratio+0)
MOVT	R0, #hi_addr(_ratio+0)
VSTR	#1, S0, [R0, #0]
;HEXIWEAR_Hydrogen_Click.c,106 :: 		lgPPM = ( log10(ratio) * -0.8 ) + 0.9;   // Calculate PPM
BL	_log10+0
MOVW	R0, #52429
MOVT	R0, #48972
VMOV	S1, R0
VMUL.F32	S1, S0, S1
MOVW	R0, #26214
MOVT	R0, #16230
VMOV	S0, R0
VADD.F32	S0, S1, S0
;HEXIWEAR_Hydrogen_Click.c,107 :: 		ppm = pow( 10, lgPPM );                  // Calculate PPM
VMOV.F32	S1, S0
VMOV.F32	S0, #10
BL	_pow+0
MOVW	R0, #lo_addr(_ppm+0)
MOVT	R0, #hi_addr(_ppm+0)
VSTR	#1, S0, [R0, #0]
;HEXIWEAR_Hydrogen_Click.c,108 :: 		}
L_end_CalculatePPM:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _CalculatePPM
_ReadSensor:
;HEXIWEAR_Hydrogen_Click.c,121 :: 		void ReadSensor()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Hydrogen_Click.c,123 :: 		adc_rd = ADC0_Get_Sample( 13 );
MOVS	R0, #13
BL	_ADC0_Get_Sample+0
MOVW	R1, #lo_addr(_adc_rd+0)
MOVT	R1, #hi_addr(_adc_rd+0)
STRH	R0, [R1, #0]
;HEXIWEAR_Hydrogen_Click.c,124 :: 		delay_ms(10);
MOVW	R7, #6782
MOVT	R7, #6
NOP
NOP
L_ReadSensor0:
SUBS	R7, R7, #1
BNE	L_ReadSensor0
NOP
NOP
NOP
;HEXIWEAR_Hydrogen_Click.c,125 :: 		}
L_end_ReadSensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ReadSensor
_DisplayHydrogenValue:
;HEXIWEAR_Hydrogen_Click.c,138 :: 		void DisplayHydrogenValue( uint16_t value )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRH	R0, [SP, #4]
;HEXIWEAR_Hydrogen_Click.c,140 :: 		if ( value_old != value )
LDRH	R1, [SP, #4]
VMOV	S1, R1
VCVT.F32	#0, S1, S1
MOVW	R1, #lo_addr(_value_old+0)
MOVT	R1, #hi_addr(_value_old+0)
VLDR	#1, S0, [R1, #0]
VCMPE.F32	S0, S1
VMRS	#60, FPSCR
IT	EQ
BEQ	L_DisplayHydrogenValue2
;HEXIWEAR_Hydrogen_Click.c,143 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Hydrogen_Click.c,144 :: 		OLED_WriteText( text, 50, 75 );
MOVS	R2, #75
MOVS	R1, #50
MOVW	R0, #lo_addr(_text+0)
MOVT	R0, #hi_addr(_text+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Hydrogen_Click.c,146 :: 		WordToStr(value, text);
MOVW	R1, #lo_addr(_text+0)
MOVT	R1, #hi_addr(_text+0)
LDRH	R0, [SP, #4]
BL	_WordToStr+0
;HEXIWEAR_Hydrogen_Click.c,148 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Hydrogen_Click.c,149 :: 		OLED_WriteText( text, 50, 75 );
MOVS	R2, #75
MOVS	R1, #50
MOVW	R0, #lo_addr(_text+0)
MOVT	R0, #hi_addr(_text+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Hydrogen_Click.c,150 :: 		}
L_DisplayHydrogenValue2:
;HEXIWEAR_Hydrogen_Click.c,151 :: 		value_old = value;
LDRH	R1, [SP, #4]
VMOV	S0, R1
VCVT.F32	#0, S0, S0
MOVW	R1, #lo_addr(_value_old+0)
MOVT	R1, #hi_addr(_value_old+0)
VSTR	#1, S0, [R1, #0]
;HEXIWEAR_Hydrogen_Click.c,152 :: 		}
L_end_DisplayHydrogenValue:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _DisplayHydrogenValue
_InitModules:
;HEXIWEAR_Hydrogen_Click.c,165 :: 		void InitModules()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Hydrogen_Click.c,170 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Hydrogen_Click.c,171 :: 		OLED_DrawImage(&hydrogen_bmp, 0, 0);
MOVW	R0, #lo_addr(_hydrogen_bmp+0)
MOVT	R0, #hi_addr(_hydrogen_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Hydrogen_Click.c,173 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Hydrogen_Click.c,174 :: 		OLED_WriteText( ppmText, 25, 75 );
MOVS	R2, #75
MOVS	R1, #25
MOVW	R0, #lo_addr(HEXIWEAR_Hydrogen_Click_ppmText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Hydrogen_Click_ppmText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Hydrogen_Click.c,176 :: 		ADC0_Init();
BL	_ADC0_Init+0
;HEXIWEAR_Hydrogen_Click.c,179 :: 		Delay_ms(100);
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
;HEXIWEAR_Hydrogen_Click.c,180 :: 		}
L_end_InitModules:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _InitModules
_main:
;HEXIWEAR_Hydrogen_Click.c,186 :: 		void main()
;HEXIWEAR_Hydrogen_Click.c,188 :: 		InitModules();
BL	_InitModules+0
;HEXIWEAR_Hydrogen_Click.c,190 :: 		while(1)
L_main5:
;HEXIWEAR_Hydrogen_Click.c,192 :: 		ReadSensor();
BL	_ReadSensor+0
;HEXIWEAR_Hydrogen_Click.c,193 :: 		CalculatePPM();
BL	_CalculatePPM+0
;HEXIWEAR_Hydrogen_Click.c,194 :: 		DisplayHydrogenValue(ppm);
MOVW	R0, #lo_addr(_ppm+0)
MOVT	R0, #hi_addr(_ppm+0)
VLDR	#1, S0, [R0, #0]
VCVT	#1, .F32, S0, S0
VMOV	R0, S0
UXTH	R0, R0
BL	_DisplayHydrogenValue+0
;HEXIWEAR_Hydrogen_Click.c,195 :: 		Delay_ms(500);
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
;HEXIWEAR_Hydrogen_Click.c,196 :: 		}
IT	AL
BAL	L_main5
;HEXIWEAR_Hydrogen_Click.c,197 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
