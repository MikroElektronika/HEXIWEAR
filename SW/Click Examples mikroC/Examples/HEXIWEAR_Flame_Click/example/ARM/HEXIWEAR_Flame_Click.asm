_InitModules:
;HEXIWEAR_Flame_Click.c,95 :: 		void InitModules(void)
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Flame_Click.c,97 :: 		GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_13 );
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_Flame_Click.c,99 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Flame_Click.c,100 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Flame_Click.c,102 :: 		OLED_DrawImage( &fire_off_bmp, 0, 0 );
MOVW	R0, #lo_addr(_fire_off_bmp+0)
MOVT	R0, #hi_addr(_fire_off_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Flame_Click.c,104 :: 		ADC0_Init();
BL	_ADC0_Init+0
;HEXIWEAR_Flame_Click.c,105 :: 		}
L_end_InitModules:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _InitModules
_main:
;HEXIWEAR_Flame_Click.c,107 :: 		void main() org 0x1000
;HEXIWEAR_Flame_Click.c,109 :: 		InitModules();
BL	_InitModules+0
;HEXIWEAR_Flame_Click.c,111 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_Flame_Click.c,112 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;HEXIWEAR_Flame_Click.c,115 :: 		PORTB_PCR13bits.IRQC = 0xB;
MOVS	R2, #11
MOVW	R1, #lo_addr(PORTB_PCR13bits+0)
MOVT	R1, #hi_addr(PORTB_PCR13bits+0)
LDR	R0, [R1, #0]
BFI	R0, R2, #16, #4
STR	R0, [R1, #0]
;HEXIWEAR_Flame_Click.c,117 :: 		OLED_WriteText( sampleText, 5, 77 );
MOVS	R2, #77
MOVS	R1, #5
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_sampleText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_sampleText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Flame_Click.c,119 :: 		while(1)
L_main0:
;HEXIWEAR_Flame_Click.c,121 :: 		switch ( isFlameDetected )
IT	AL
BAL	L_main2
;HEXIWEAR_Flame_Click.c,123 :: 		case 0:
L_main4:
;HEXIWEAR_Flame_Click.c,125 :: 		OLED_DrawImage( &fire_off_bmp, 0, 0 );
MOVW	R0, #lo_addr(_fire_off_bmp+0)
MOVT	R0, #hi_addr(_fire_off_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Flame_Click.c,126 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Flame_Click.c,127 :: 		OLED_WriteText( sampleText, 5, 77 );
MOVS	R2, #77
MOVS	R1, #5
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_sampleText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_sampleText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Flame_Click.c,128 :: 		isFlameDetected = -1;
MOVS	R1, #-1
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Flame_Click.c,129 :: 		break;
IT	AL
BAL	L_main3
;HEXIWEAR_Flame_Click.c,132 :: 		case 1:
L_main5:
;HEXIWEAR_Flame_Click.c,134 :: 		OLED_DrawImage( &fire_on_bmp, 0, 0 );
MOVW	R0, #lo_addr(_fire_on_bmp+0)
MOVT	R0, #hi_addr(_fire_on_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Flame_Click.c,135 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Flame_Click.c,136 :: 		OLED_WriteText( sampleText, 5, 77 );
MOVS	R2, #77
MOVS	R1, #5
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_sampleText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_sampleText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Flame_Click.c,137 :: 		isFlameDetected = -1;
MOVS	R1, #-1
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Flame_Click.c,138 :: 		break;
IT	AL
BAL	L_main3
;HEXIWEAR_Flame_Click.c,141 :: 		default: {}
L_main6:
;HEXIWEAR_Flame_Click.c,142 :: 		}
IT	AL
BAL	L_main3
L_main2:
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main4
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	EQ
BEQ	L_main5
IT	AL
BAL	L_main6
L_main3:
;HEXIWEAR_Flame_Click.c,144 :: 		adc_result = ADC0_Get_Sample( 12 );
MOVS	R0, #12
BL	_ADC0_Get_Sample+0
MOVW	R1, #lo_addr(_adc_result+0)
MOVT	R1, #hi_addr(_adc_result+0)
STR	R0, [R1, #0]
;HEXIWEAR_Flame_Click.c,145 :: 		LongWordToStr( adc_result, flameLevel );
MOVW	R1, #lo_addr(HEXIWEAR_Flame_Click_flameLevel+0)
MOVT	R1, #hi_addr(HEXIWEAR_Flame_Click_flameLevel+0)
BL	_LongWordToStr+0
;HEXIWEAR_Flame_Click.c,147 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Flame_Click.c,148 :: 		OLED_WriteText( flameLevel, 40, 77 );
MOVS	R2, #77
MOVS	R1, #40
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_flameLevel+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_flameLevel+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Flame_Click.c,150 :: 		Delay_ms(500);
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
;HEXIWEAR_Flame_Click.c,152 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #0
BL	_OLED_SetFont+0
;HEXIWEAR_Flame_Click.c,153 :: 		OLED_WriteText( flameLevel, 40, 77 );
MOVS	R2, #77
MOVS	R1, #40
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_flameLevel+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_flameLevel+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Flame_Click.c,154 :: 		}
IT	AL
BAL	L_main0
;HEXIWEAR_Flame_Click.c,155 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_FlameDetect:
;HEXIWEAR_Flame_Click.c,161 :: 		void FlameDetect() iv IVT_INT_PORTB ics ICS_AUTO
;HEXIWEAR_Flame_Click.c,163 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Flame_Click.c,165 :: 		if ( 1 == FLAME_In )
MOVW	R1, #lo_addr(PTB_PDIR+0)
MOVT	R1, #hi_addr(PTB_PDIR+0)
LDR	R0, [R1, #0]
CMP	R0, #0
IT	EQ
BEQ	L_FlameDetect9
;HEXIWEAR_Flame_Click.c,167 :: 		isFlameDetected = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Flame_Click.c,168 :: 		}
IT	AL
BAL	L_FlameDetect10
L_FlameDetect9:
;HEXIWEAR_Flame_Click.c,171 :: 		isFlameDetected = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Flame_Click_isFlameDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Flame_Click.c,172 :: 		}
L_FlameDetect10:
;HEXIWEAR_Flame_Click.c,173 :: 		}
L_end_FlameDetect:
BX	LR
; end of _FlameDetect
