_main:
;Motion.c,91 :: 		void main() org 0x1000
;Motion.c,94 :: 		OLED_Init();
BL	_OLED_Init+0
;Motion.c,97 :: 		OLED_DrawImage( motion_none_bmp, 0, 0 );
MOVW	R0, #lo_addr(_motion_none_bmp+0)
MOVT	R0, #hi_addr(_motion_none_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Motion.c,100 :: 		GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_8 );
MOV	R1, #256
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;Motion.c,103 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_19 );
MOV	R1, #524288
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;Motion.c,105 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;Motion.c,106 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;Motion.c,109 :: 		PORTB_PCR8bits.IRQC = 0xB;
MOVS	R2, #11
MOVW	R1, #lo_addr(PORTB_PCR8bits+0)
MOVT	R1, #hi_addr(PORTB_PCR8bits+0)
LDR	R0, [R1, #0]
BFI	R0, R2, #16, #4
STR	R0, [R1, #0]
;Motion.c,112 :: 		Motion_Sens_EN = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;Motion.c,114 :: 		while (1)
L_main0:
;Motion.c,116 :: 		if ( 1 == isMotionDetected )
MOVW	R0, #lo_addr(Motion_isMotionDetected+0)
MOVT	R0, #hi_addr(Motion_isMotionDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	NE
BNE	L_main2
;Motion.c,118 :: 		OLED_DrawImage( motion_detected_bmp, 0, 0 );
MOVW	R0, #lo_addr(_motion_detected_bmp+0)
MOVT	R0, #hi_addr(_motion_detected_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Motion.c,119 :: 		isMotionDetected = -1;
MOVS	R1, #-1
MOVW	R0, #lo_addr(Motion_isMotionDetected+0)
MOVT	R0, #hi_addr(Motion_isMotionDetected+0)
STRB	R1, [R0, #0]
;Motion.c,120 :: 		}
IT	AL
BAL	L_main3
L_main2:
;Motion.c,121 :: 		else if ( 0 == isMotionDetected )
MOVW	R0, #lo_addr(Motion_isMotionDetected+0)
MOVT	R0, #hi_addr(Motion_isMotionDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_main4
;Motion.c,123 :: 		OLED_DrawImage( motion_none_bmp, 0, 0 );
MOVW	R0, #lo_addr(_motion_none_bmp+0)
MOVT	R0, #hi_addr(_motion_none_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Motion.c,124 :: 		isMotionDetected = -1;
MOVS	R1, #-1
MOVW	R0, #lo_addr(Motion_isMotionDetected+0)
MOVT	R0, #hi_addr(Motion_isMotionDetected+0)
STRB	R1, [R0, #0]
;Motion.c,125 :: 		}
L_main4:
L_main3:
;Motion.c,126 :: 		}
IT	AL
BAL	L_main0
;Motion.c,127 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_MotionDetect:
;Motion.c,133 :: 		void MotionDetect() iv IVT_INT_PORTB ics ICS_AUTO
;Motion.c,135 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;Motion.c,137 :: 		if ( 1 == Motion_Sens_PIN )
MOVW	R1, #lo_addr(PTB_PDIR+0)
MOVT	R1, #hi_addr(PTB_PDIR+0)
LDR	R0, [R1, #0]
CMP	R0, #0
IT	EQ
BEQ	L_MotionDetect5
;Motion.c,139 :: 		isMotionDetected = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(Motion_isMotionDetected+0)
MOVT	R0, #hi_addr(Motion_isMotionDetected+0)
STRB	R1, [R0, #0]
;Motion.c,140 :: 		}
IT	AL
BAL	L_MotionDetect6
L_MotionDetect5:
;Motion.c,143 :: 		isMotionDetected = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(Motion_isMotionDetected+0)
MOVT	R0, #hi_addr(Motion_isMotionDetected+0)
STRB	R1, [R0, #0]
;Motion.c,144 :: 		}
L_MotionDetect6:
;Motion.c,145 :: 		}
L_end_MotionDetect:
BX	LR
; end of _MotionDetect
