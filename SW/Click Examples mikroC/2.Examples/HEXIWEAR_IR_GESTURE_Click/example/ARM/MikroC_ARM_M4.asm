MikroC_ARM_M4_handle_gesture:
;MikroC_ARM_M4.c,86 :: 		static void handle_gesture()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;MikroC_ARM_M4.c,88 :: 		if ( ir_gesture_available() )
BL	_ir_gesture_available+0
CMP	R0, #0
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture0
;MikroC_ARM_M4.c,90 :: 		switch ( ir_gesture_read_gesture() )
BL	_ir_gesture_read_gesture+0
STRB	R0, [SP, #4]
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture1
;MikroC_ARM_M4.c,92 :: 		case DIR_UP:
L_MikroC_ARM_M4_handle_gesture3:
;MikroC_ARM_M4.c,93 :: 		OLED_WriteText( "UP", 35, 75 );
MOVW	R0, #lo_addr(?lstr1_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr1_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,94 :: 		break;
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
;MikroC_ARM_M4.c,95 :: 		case DIR_DOWN:
L_MikroC_ARM_M4_handle_gesture4:
;MikroC_ARM_M4.c,96 :: 		OLED_WriteText( "DOWN", 35, 75 );
MOVW	R0, #lo_addr(?lstr2_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr2_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,97 :: 		break;
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
;MikroC_ARM_M4.c,98 :: 		case DIR_LEFT:
L_MikroC_ARM_M4_handle_gesture5:
;MikroC_ARM_M4.c,99 :: 		OLED_WriteText( "LEFT", 35, 75 );
MOVW	R0, #lo_addr(?lstr3_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr3_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,100 :: 		break;
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
;MikroC_ARM_M4.c,101 :: 		case DIR_RIGHT:
L_MikroC_ARM_M4_handle_gesture6:
;MikroC_ARM_M4.c,102 :: 		OLED_WriteText( "RIGHT", 35, 75 );
MOVW	R0, #lo_addr(?lstr4_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr4_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,103 :: 		break;
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
;MikroC_ARM_M4.c,104 :: 		case DIR_NEAR:
L_MikroC_ARM_M4_handle_gesture7:
;MikroC_ARM_M4.c,105 :: 		OLED_WriteText( "NEAR", 35, 75 );
MOVW	R0, #lo_addr(?lstr5_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr5_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,106 :: 		break;
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
;MikroC_ARM_M4.c,107 :: 		case DIR_FAR:
L_MikroC_ARM_M4_handle_gesture8:
;MikroC_ARM_M4.c,108 :: 		OLED_WriteText( "FAR", 35, 75 );
MOVW	R0, #lo_addr(?lstr6_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr6_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,109 :: 		break;
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
;MikroC_ARM_M4.c,110 :: 		default:
L_MikroC_ARM_M4_handle_gesture9:
;MikroC_ARM_M4.c,111 :: 		OLED_WriteText( "NONE", 35, 75 );
MOVW	R0, #lo_addr(?lstr7_MikroC_ARM_M4+0)
MOVT	R0, #hi_addr(?lstr7_MikroC_ARM_M4+0)
MOVS	R2, #75
MOVS	R1, #35
BL	_OLED_WriteText+0
;MikroC_ARM_M4.c,112 :: 		}
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture2
L_MikroC_ARM_M4_handle_gesture1:
LDRB	R0, [SP, #4]
CMP	R0, #3
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture3
CMP	R0, #4
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture4
CMP	R0, #1
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture5
CMP	R0, #2
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture6
CMP	R0, #5
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture7
CMP	R0, #6
IT	EQ
BEQ	L_MikroC_ARM_M4_handle_gesture8
IT	AL
BAL	L_MikroC_ARM_M4_handle_gesture9
L_MikroC_ARM_M4_handle_gesture2:
;MikroC_ARM_M4.c,113 :: 		}
L_MikroC_ARM_M4_handle_gesture0:
;MikroC_ARM_M4.c,114 :: 		}
L_end_handle_gesture:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of MikroC_ARM_M4_handle_gesture
MikroC_ARM_M4_system_init:
;MikroC_ARM_M4.c,119 :: 		static int system_init()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;MikroC_ARM_M4.c,121 :: 		DisableInterrupts();
BL	_DisableInterrupts+0
;MikroC_ARM_M4.c,122 :: 		GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_13 );
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;MikroC_ARM_M4.c,124 :: 		I2C0_Init_Advanced(400000, &_GPIO_Module_I2C0_PD8_9);
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #6784
MOVT	R0, #6
BL	_I2C0_Init_Advanced+0
;MikroC_ARM_M4.c,125 :: 		Delay_ms( 100 );
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_MikroC_ARM_M4_system_init10:
SUBS	R7, R7, #1
BNE	L_MikroC_ARM_M4_system_init10
NOP
NOP
NOP
;MikroC_ARM_M4.c,128 :: 		ir_gesture_init( APDS9960_I2C_ADDR );
MOVS	R0, #57
BL	_ir_gesture_init+0
;MikroC_ARM_M4.c,129 :: 		ir_gesture_enable_gesture_sensor( true );
MOVS	R0, #1
BL	_ir_gesture_enable_gesture_sensor+0
;MikroC_ARM_M4.c,132 :: 		OLED_Init();
BL	_OLED_Init+0
;MikroC_ARM_M4.c,133 :: 		OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );
MOVW	R0, #lo_addr(_common_hexiwearLogo_bmp+0)
MOVT	R0, #hi_addr(_common_hexiwearLogo_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;MikroC_ARM_M4.c,134 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;MikroC_ARM_M4.c,136 :: 		PORTB_PCR13bits.IRQC = 0xB;
MOVS	R2, #11
MOVW	R1, #lo_addr(PORTB_PCR13bits+0)
MOVT	R1, #hi_addr(PORTB_PCR13bits+0)
LDR	R0, [R1, #0]
BFI	R0, R2, #16, #4
STR	R0, [R1, #0]
;MikroC_ARM_M4.c,137 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;MikroC_ARM_M4.c,138 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;MikroC_ARM_M4.c,140 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;MikroC_ARM_M4.c,141 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of MikroC_ARM_M4_system_init
_main:
;MikroC_ARM_M4.c,147 :: 		void main()
SUB	SP, SP, #4
;MikroC_ARM_M4.c,149 :: 		if( system_init() )
BL	MikroC_ARM_M4_system_init+0
CMP	R0, #0
IT	EQ
BEQ	L_main12
;MikroC_ARM_M4.c,150 :: 		return;
IT	AL
BAL	L_end_main
L_main12:
;MikroC_ARM_M4.c,154 :: 		while(1)
L_main13:
;MikroC_ARM_M4.c,156 :: 		if( gesture_flag )
MOVW	R0, #lo_addr(MikroC_ARM_M4_gesture_flag+0)
MOVT	R0, #hi_addr(MikroC_ARM_M4_gesture_flag+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main15
;MikroC_ARM_M4.c,158 :: 		DisableInterrupts();
BL	_DisableInterrupts+0
;MikroC_ARM_M4.c,159 :: 		handle_gesture();
BL	MikroC_ARM_M4_handle_gesture+0
;MikroC_ARM_M4.c,160 :: 		delay_ms(20);
MOVW	R7, #13566
MOVT	R7, #12
NOP
NOP
L_main16:
SUBS	R7, R7, #1
BNE	L_main16
NOP
NOP
NOP
;MikroC_ARM_M4.c,161 :: 		OLED_DrawBox(0,67, 96, 29, OLED_COLOR_BLACK);
MOVW	R0, #0
PUSH	(R0)
MOVS	R3, #29
MOVS	R2, #96
MOVS	R1, #67
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;MikroC_ARM_M4.c,162 :: 		gesture_flag = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(MikroC_ARM_M4_gesture_flag+0)
MOVT	R0, #hi_addr(MikroC_ARM_M4_gesture_flag+0)
STRB	R1, [R0, #0]
;MikroC_ARM_M4.c,163 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;MikroC_ARM_M4.c,164 :: 		}
L_main15:
;MikroC_ARM_M4.c,165 :: 		}
IT	AL
BAL	L_main13
;MikroC_ARM_M4.c,166 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_MotionDetect:
;MikroC_ARM_M4.c,170 :: 		void MotionDetect() iv IVT_INT_PORTB ics ICS_AUTO
SUB	SP, SP, #4
STR	LR, [SP, #0]
;MikroC_ARM_M4.c,172 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;MikroC_ARM_M4.c,174 :: 		if( ir_gesture_is_interrupted( INT_GESTURE ) )
MOVS	R0, #2
BL	_ir_gesture_is_interrupted+0
CMP	R0, #0
IT	EQ
BEQ	L_MotionDetect18
;MikroC_ARM_M4.c,176 :: 		ir_gesture_clear_gesture_int();
BL	_ir_gesture_clear_gesture_int+0
;MikroC_ARM_M4.c,177 :: 		gesture_flag = true;
MOVS	R1, #1
MOVW	R0, #lo_addr(MikroC_ARM_M4_gesture_flag+0)
MOVT	R0, #hi_addr(MikroC_ARM_M4_gesture_flag+0)
STRB	R1, [R0, #0]
;MikroC_ARM_M4.c,179 :: 		}
L_MotionDetect18:
;MikroC_ARM_M4.c,180 :: 		}
L_end_MotionDetect:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MotionDetect
