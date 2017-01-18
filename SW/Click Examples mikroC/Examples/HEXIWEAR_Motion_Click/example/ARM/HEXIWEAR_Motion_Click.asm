_main:
;HEXIWEAR_Motion_Click.c,12 :: 		void main()
;HEXIWEAR_Motion_Click.c,14 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Motion_Click.c,15 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_Motion_Click.c,18 :: 		OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );
MOVW	R0, #lo_addr(_common_hexiwearLogo_bmp+0)
MOVT	R0, #hi_addr(_common_hexiwearLogo_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Motion_Click.c,21 :: 		GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_8 );
MOV	R1, #256
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_Motion_Click.c,24 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 );
MOV	R1, #524288
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Motion_Click.c,27 :: 		GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8  );
MOV	R1, #256
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Motion_Click.c,28 :: 		PTC_PDOR.B8 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,30 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_Motion_Click.c,31 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;HEXIWEAR_Motion_Click.c,34 :: 		PORTB_PCR8bits.IRQC = 0xB;
MOVS	R2, #11
MOVW	R1, #lo_addr(PORTB_PCR8bits+0)
MOVT	R1, #hi_addr(PORTB_PCR8bits+0)
LDR	R0, [R1, #0]
BFI	R0, R2, #16, #4
STR	R0, [R1, #0]
;HEXIWEAR_Motion_Click.c,37 :: 		Motion_Sens_EN = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,39 :: 		while (1)
L_main0:
;HEXIWEAR_Motion_Click.c,41 :: 		if ( 1 == isMotionDetected )
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	NE
BNE	L_main2
;HEXIWEAR_Motion_Click.c,43 :: 		OLED_WriteText( sampleText, 35, 75 );
MOVS	R2, #75
MOVS	R1, #35
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_sampleText+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_sampleText+0)
BL	_OLED_WriteText+0
;HEXIWEAR_Motion_Click.c,44 :: 		PTC_PDOR.B8 = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,45 :: 		isMotionDetected = -1;
MOVS	R1, #-1
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,46 :: 		}
IT	AL
BAL	L_main3
L_main2:
;HEXIWEAR_Motion_Click.c,47 :: 		else if ( 0 == isMotionDetected )
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_main4
;HEXIWEAR_Motion_Click.c,49 :: 		OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );
MOVW	R0, #lo_addr(_common_hexiwearLogo_bmp+0)
MOVT	R0, #hi_addr(_common_hexiwearLogo_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Motion_Click.c,50 :: 		PTC_PDOR.B8 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,51 :: 		isMotionDetected = -1;
MOVS	R1, #-1
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,52 :: 		}
L_main4:
L_main3:
;HEXIWEAR_Motion_Click.c,53 :: 		}
IT	AL
BAL	L_main0
;HEXIWEAR_Motion_Click.c,54 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_MotionDetect:
;HEXIWEAR_Motion_Click.c,56 :: 		void MotionDetect() iv IVT_INT_PORTB ics ICS_AUTO
;HEXIWEAR_Motion_Click.c,58 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,60 :: 		if ( 1 == Motion_Sens_PIN )
MOVW	R1, #lo_addr(PTB_PDIR+0)
MOVT	R1, #hi_addr(PTB_PDIR+0)
LDR	R0, [R1, #0]
CMP	R0, #0
IT	EQ
BEQ	L_MotionDetect5
;HEXIWEAR_Motion_Click.c,62 :: 		isMotionDetected = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,63 :: 		}
IT	AL
BAL	L_MotionDetect6
L_MotionDetect5:
;HEXIWEAR_Motion_Click.c,66 :: 		isMotionDetected = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
MOVT	R0, #hi_addr(HEXIWEAR_Motion_Click_isMotionDetected+0)
STRB	R1, [R0, #0]
;HEXIWEAR_Motion_Click.c,67 :: 		}
L_MotionDetect6:
;HEXIWEAR_Motion_Click.c,68 :: 		}
L_end_MotionDetect:
BX	LR
; end of _MotionDetect
