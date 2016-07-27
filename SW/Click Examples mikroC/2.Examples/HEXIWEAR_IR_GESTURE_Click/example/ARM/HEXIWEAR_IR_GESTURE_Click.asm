HEXIWEAR_IR_GESTURE_Click_handle_gesture:
;HEXIWEAR_IR_GESTURE_Click.c,97 :: 		static void handle_gesture()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;HEXIWEAR_IR_GESTURE_Click.c,99 :: 		if ( ir_gesture_available() )
BL	_ir_gesture_available+0
CMP	R0, #0
IT	EQ
BEQ	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture0
;HEXIWEAR_IR_GESTURE_Click.c,101 :: 		switch ( ir_gesture_read_gesture() )
BL	_ir_gesture_read_gesture+0
STRB	R0, [SP, #4]
IT	AL
BAL	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture1
;HEXIWEAR_IR_GESTURE_Click.c,103 :: 		case DIR_UP:
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture3:
;HEXIWEAR_IR_GESTURE_Click.c,104 :: 		OLED_DrawImage( irgestureup_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgestureup_bmp+0)
MOVT	R0, #hi_addr(_irgestureup_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,105 :: 		break;
IT	AL
BAL	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture2
;HEXIWEAR_IR_GESTURE_Click.c,106 :: 		case DIR_DOWN:
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture4:
;HEXIWEAR_IR_GESTURE_Click.c,107 :: 		OLED_DrawImage( irgesturedown_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgesturedown_bmp+0)
MOVT	R0, #hi_addr(_irgesturedown_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,108 :: 		break;
IT	AL
BAL	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture2
;HEXIWEAR_IR_GESTURE_Click.c,109 :: 		case DIR_LEFT:
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture5:
;HEXIWEAR_IR_GESTURE_Click.c,110 :: 		OLED_DrawImage( irgestureleft_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgestureleft_bmp+0)
MOVT	R0, #hi_addr(_irgestureleft_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,111 :: 		break;
IT	AL
BAL	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture2
;HEXIWEAR_IR_GESTURE_Click.c,112 :: 		case DIR_RIGHT:
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture6:
;HEXIWEAR_IR_GESTURE_Click.c,113 :: 		OLED_DrawImage( irgestureright_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgestureright_bmp+0)
MOVT	R0, #hi_addr(_irgestureright_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,114 :: 		break;
IT	AL
BAL	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture2
;HEXIWEAR_IR_GESTURE_Click.c,115 :: 		}
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture1:
LDRB	R0, [SP, #4]
CMP	R0, #3
IT	EQ
BEQ	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture3
CMP	R0, #4
IT	EQ
BEQ	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture4
CMP	R0, #1
IT	EQ
BEQ	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture5
CMP	R0, #2
IT	EQ
BEQ	L_HEXIWEAR_IR_GESTURE_Click_handle_gesture6
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture2:
;HEXIWEAR_IR_GESTURE_Click.c,116 :: 		}
L_HEXIWEAR_IR_GESTURE_Click_handle_gesture0:
;HEXIWEAR_IR_GESTURE_Click.c,117 :: 		}
L_end_handle_gesture:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of HEXIWEAR_IR_GESTURE_Click_handle_gesture
HEXIWEAR_IR_GESTURE_Click_system_init:
;HEXIWEAR_IR_GESTURE_Click.c,124 :: 		static int system_init()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_IR_GESTURE_Click.c,126 :: 		DisableInterrupts();
BL	_DisableInterrupts+0
;HEXIWEAR_IR_GESTURE_Click.c,127 :: 		GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_13 );
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_IR_GESTURE_Click.c,129 :: 		I2C0_Init_Advanced(400000, &_GPIO_Module_I2C0_PD8_9);
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #6784
MOVT	R0, #6
BL	_I2C0_Init_Advanced+0
;HEXIWEAR_IR_GESTURE_Click.c,130 :: 		Delay_ms( 100 );
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_HEXIWEAR_IR_GESTURE_Click_system_init7:
SUBS	R7, R7, #1
BNE	L_HEXIWEAR_IR_GESTURE_Click_system_init7
NOP
NOP
NOP
;HEXIWEAR_IR_GESTURE_Click.c,133 :: 		ir_gesture_init( APDS9960_I2C_ADDR );
MOVS	R0, #57
BL	_ir_gesture_init+0
;HEXIWEAR_IR_GESTURE_Click.c,134 :: 		ir_gesture_enable_gesture_sensor( true );
MOVS	R0, #1
BL	_ir_gesture_enable_gesture_sensor+0
;HEXIWEAR_IR_GESTURE_Click.c,137 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_IR_GESTURE_Click.c,138 :: 		OLED_DrawImage( irgesture_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgesture_bmp+0)
MOVT	R0, #hi_addr(_irgesture_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,139 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_IR_GESTURE_Click.c,141 :: 		PORTB_PCR13bits.IRQC = 0xB;
MOVS	R2, #11
MOVW	R1, #lo_addr(PORTB_PCR13bits+0)
MOVT	R1, #hi_addr(PORTB_PCR13bits+0)
LDR	R0, [R1, #0]
BFI	R0, R2, #16, #4
STR	R0, [R1, #0]
;HEXIWEAR_IR_GESTURE_Click.c,142 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;HEXIWEAR_IR_GESTURE_Click.c,143 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_IR_GESTURE_Click.c,145 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;HEXIWEAR_IR_GESTURE_Click.c,146 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of HEXIWEAR_IR_GESTURE_Click_system_init
_main:
;HEXIWEAR_IR_GESTURE_Click.c,152 :: 		void main()
SUB	SP, SP, #4
;HEXIWEAR_IR_GESTURE_Click.c,154 :: 		if( system_init() )
BL	HEXIWEAR_IR_GESTURE_Click_system_init+0
CMP	R0, #0
IT	EQ
BEQ	L_main9
;HEXIWEAR_IR_GESTURE_Click.c,155 :: 		return;
IT	AL
BAL	L_end_main
L_main9:
;HEXIWEAR_IR_GESTURE_Click.c,156 :: 		DisableInterrupts();
BL	_DisableInterrupts+0
;HEXIWEAR_IR_GESTURE_Click.c,157 :: 		OLED_WriteText("Initialization", 20, 75);
MOVW	R0, #lo_addr(?lstr1_HEXIWEAR_IR_GESTURE_Click+0)
MOVT	R0, #hi_addr(?lstr1_HEXIWEAR_IR_GESTURE_Click+0)
MOVS	R2, #75
MOVS	R1, #20
BL	_OLED_WriteText+0
;HEXIWEAR_IR_GESTURE_Click.c,158 :: 		delay_ms(2000);
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main10:
SUBS	R7, R7, #1
BNE	L_main10
NOP
NOP
NOP
;HEXIWEAR_IR_GESTURE_Click.c,159 :: 		OLED_DrawImage( irgesturen_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgesturen_bmp+0)
MOVT	R0, #hi_addr(_irgesturen_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,160 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_IR_GESTURE_Click.c,161 :: 		while(1)
L_main12:
;HEXIWEAR_IR_GESTURE_Click.c,163 :: 		if( gesture_flag )
MOVW	R0, #lo_addr(HEXIWEAR_IR_GESTURE_Click_gesture_flag+0)
MOVT	R0, #hi_addr(HEXIWEAR_IR_GESTURE_Click_gesture_flag+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main14
;HEXIWEAR_IR_GESTURE_Click.c,165 :: 		DisableInterrupts();
BL	_DisableInterrupts+0
;HEXIWEAR_IR_GESTURE_Click.c,166 :: 		handle_gesture();
BL	HEXIWEAR_IR_GESTURE_Click_handle_gesture+0
;HEXIWEAR_IR_GESTURE_Click.c,167 :: 		delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_main15:
SUBS	R7, R7, #1
BNE	L_main15
NOP
NOP
NOP
;HEXIWEAR_IR_GESTURE_Click.c,168 :: 		OLED_DrawImage( irgesturen_bmp, 0, 0 );
MOVW	R0, #lo_addr(_irgesturen_bmp+0)
MOVT	R0, #hi_addr(_irgesturen_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_IR_GESTURE_Click.c,169 :: 		gesture_flag = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(HEXIWEAR_IR_GESTURE_Click_gesture_flag+0)
MOVT	R0, #hi_addr(HEXIWEAR_IR_GESTURE_Click_gesture_flag+0)
STRB	R1, [R0, #0]
;HEXIWEAR_IR_GESTURE_Click.c,170 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_IR_GESTURE_Click.c,171 :: 		}
L_main14:
;HEXIWEAR_IR_GESTURE_Click.c,172 :: 		}
IT	AL
BAL	L_main12
;HEXIWEAR_IR_GESTURE_Click.c,173 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_MotionDetect:
;HEXIWEAR_IR_GESTURE_Click.c,177 :: 		void MotionDetect() iv IVT_INT_PORTB ics ICS_AUTO
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_IR_GESTURE_Click.c,179 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;HEXIWEAR_IR_GESTURE_Click.c,181 :: 		if( ir_gesture_is_interrupted( INT_GESTURE ) )
MOVS	R0, #2
BL	_ir_gesture_is_interrupted+0
CMP	R0, #0
IT	EQ
BEQ	L_MotionDetect17
;HEXIWEAR_IR_GESTURE_Click.c,183 :: 		ir_gesture_clear_gesture_int();
BL	_ir_gesture_clear_gesture_int+0
;HEXIWEAR_IR_GESTURE_Click.c,184 :: 		gesture_flag = true;
MOVS	R1, #1
MOVW	R0, #lo_addr(HEXIWEAR_IR_GESTURE_Click_gesture_flag+0)
MOVT	R0, #hi_addr(HEXIWEAR_IR_GESTURE_Click_gesture_flag+0)
STRB	R1, [R0, #0]
;HEXIWEAR_IR_GESTURE_Click.c,186 :: 		}
L_MotionDetect17:
;HEXIWEAR_IR_GESTURE_Click.c,187 :: 		}
L_end_MotionDetect:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MotionDetect
