mic_24045_ARM_system_init:
;mic_24045_ARM.c,42 :: 		static void system_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;mic_24045_ARM.c,45 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_mic_24045_ARM_system_init0:
SUBS	R7, R7, #1
BNE	L_mic_24045_ARM_system_init0
NOP
NOP
NOP
;mic_24045_ARM.c,52 :: 		&_GPIO_Module_SPI0_PC5_7_6);
MOVW	R2, #lo_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI0_PC5_7_6+0)
;mic_24045_ARM.c,51 :: 		_SPI_CFG_MSB_FIRST,
MOVW	R1, #7
MOVT	R1, #33280
;mic_24045_ARM.c,47 :: 		SPI0_Init_Advanced( 16000000, _SPI_CFG_MASTER       |
MOVW	R0, #9216
MOVT	R0, #244
;mic_24045_ARM.c,52 :: 		&_GPIO_Module_SPI0_PC5_7_6);
BL	_SPI0_Init_Advanced+0
;mic_24045_ARM.c,55 :: 		I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9  );
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #6784
MOVT	R0, #6
BL	_I2C0_Init_Advanced+0
;mic_24045_ARM.c,56 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_mic_24045_ARM_system_init2:
SUBS	R7, R7, #1
BNE	L_mic_24045_ARM_system_init2
NOP
NOP
NOP
;mic_24045_ARM.c,57 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
MOV	R1, #2048
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;mic_24045_ARM.c,58 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of mic_24045_ARM_system_init
_main:
;mic_24045_ARM.c,60 :: 		void main()
;mic_24045_ARM.c,62 :: 		memset (write_text, 0, 15);
MOVS	R2, #15
SXTH	R2, R2
MOVS	R1, #0
MOVW	R0, #lo_addr(_write_text+0)
MOVT	R0, #hi_addr(_write_text+0)
BL	_memset+0
;mic_24045_ARM.c,63 :: 		system_init();
BL	mic_24045_ARM_system_init+0
;mic_24045_ARM.c,64 :: 		mic_24045_init(0x50);
MOVS	R0, #80
BL	_mic_24045_init+0
;mic_24045_ARM.c,65 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_main4:
SUBS	R7, R7, #1
BNE	L_main4
NOP
NOP
NOP
;mic_24045_ARM.c,68 :: 		OLED_init();
BL	_OLED_Init+0
;mic_24045_ARM.c,69 :: 		OLED_SetFont( guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Exo_2_Condensed10x16_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Exo_2_Condensed10x16_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;mic_24045_ARM.c,70 :: 		OLED_FillScreen( OLED_COLOR_BLACK );
MOVW	R0, #0
BL	_OLED_FillScreen+0
;mic_24045_ARM.c,71 :: 		OLED_WriteText("Initialized", 20, 8 );
MOVW	R0, #lo_addr(?lstr1_mic_24045_ARM+0)
MOVT	R0, #hi_addr(?lstr1_mic_24045_ARM+0)
MOVS	R2, #8
MOVS	R1, #20
BL	_OLED_WriteText+0
;mic_24045_ARM.c,72 :: 		Delay_ms (2000);
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main6:
SUBS	R7, R7, #1
BNE	L_main6
NOP
NOP
NOP
;mic_24045_ARM.c,73 :: 		i = 21;
MOVS	R1, #21
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
STRB	R1, [R0, #0]
;mic_24045_ARM.c,75 :: 		while (i)
L_main8:
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main9
;mic_24045_ARM.c,77 :: 		write_1 = i*0.25;
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
LDRB	R0, [R0, #0]
VMOV	S1, R0
VCVT.F32	#0, S1, S1
VMOV.F32	S0, #0.25
VMUL.F32	S0, S1, S0
MOVW	R0, #lo_addr(_write_1+0)
MOVT	R0, #hi_addr(_write_1+0)
VSTR	#1, S0, [R0, #0]
;mic_24045_ARM.c,78 :: 		mic_24045_write_vout (write_1);
VMOV.F32	S0, S0
VMOV	R0, S0
BL	_mic_24045_write_vout+0
;mic_24045_ARM.c,79 :: 		MIC24045_EN_PIN = 1;     /* Sets EN pin to 1 */
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;mic_24045_ARM.c,80 :: 		Delay_ms (1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_main10:
SUBS	R7, R7, #1
BNE	L_main10
NOP
NOP
NOP
;mic_24045_ARM.c,82 :: 		read_2 = mic_24045_read_vout ();
BL	_mic_24045_read_vout+0
MOVW	R0, #lo_addr(_read_2+0)
MOVT	R0, #hi_addr(_read_2+0)
VSTR	#1, S0, [R0, #0]
;mic_24045_ARM.c,83 :: 		FloatToStr (read_2, &write_text);
MOVW	R0, #lo_addr(_write_text+0)
MOVT	R0, #hi_addr(_write_text+0)
BL	_FloatToStr+0
;mic_24045_ARM.c,85 :: 		if (read_2 > 1)
MOVW	R0, #lo_addr(_read_2+0)
MOVT	R0, #hi_addr(_read_2+0)
VLDR	#1, S1, [R0, #0]
VMOV.F32	S0, #1
VCMPE.F32	S1, S0
VMRS	#60, FPSCR
IT	LE
BLE	L_main12
;mic_24045_ARM.c,86 :: 		write_text [5] = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_write_text+5)
MOVT	R0, #hi_addr(_write_text+5)
STRB	R1, [R0, #0]
L_main12:
;mic_24045_ARM.c,89 :: 		if (i == 18)
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
LDRB	R0, [R0, #0]
CMP	R0, #18
IT	NE
BNE	L_main13
;mic_24045_ARM.c,92 :: 		i-=3;
MOVW	R1, #lo_addr(_i+0)
MOVT	R1, #hi_addr(_i+0)
LDRB	R0, [R1, #0]
SUBS	R0, R0, #3
STRB	R0, [R1, #0]
;mic_24045_ARM.c,93 :: 		}
L_main13:
;mic_24045_ARM.c,94 :: 		OLED_FillScreen( OLED_COLOR_BLACK );
MOVW	R0, #0
BL	_OLED_FillScreen+0
;mic_24045_ARM.c,95 :: 		OLED_WriteText("Current voltage:", 1, 8 );
MOVW	R0, #lo_addr(?lstr2_mic_24045_ARM+0)
MOVT	R0, #hi_addr(?lstr2_mic_24045_ARM+0)
MOVS	R2, #8
MOVS	R1, #1
BL	_OLED_WriteText+0
;mic_24045_ARM.c,96 :: 		strcat (write_text, " V");
MOVW	R0, #lo_addr(?lstr3_mic_24045_ARM+0)
MOVT	R0, #hi_addr(?lstr3_mic_24045_ARM+0)
MOV	R1, R0
MOVW	R0, #lo_addr(_write_text+0)
MOVT	R0, #hi_addr(_write_text+0)
BL	_strcat+0
;mic_24045_ARM.c,97 :: 		OLED_WriteText(write_text, 20, 28 );
MOVS	R2, #28
MOVS	R1, #20
MOVW	R0, #lo_addr(_write_text+0)
MOVT	R0, #hi_addr(_write_text+0)
BL	_OLED_WriteText+0
;mic_24045_ARM.c,98 :: 		Delay_ms (1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_main14:
SUBS	R7, R7, #1
BNE	L_main14
NOP
NOP
NOP
;mic_24045_ARM.c,106 :: 		MIC24045_EN_PIN = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;mic_24045_ARM.c,107 :: 		Delay_ms (1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_main16:
SUBS	R7, R7, #1
BNE	L_main16
NOP
NOP
NOP
;mic_24045_ARM.c,108 :: 		i--;
MOVW	R1, #lo_addr(_i+0)
MOVT	R1, #hi_addr(_i+0)
LDRB	R0, [R1, #0]
SUBS	R0, R0, #1
STRB	R0, [R1, #0]
;mic_24045_ARM.c,109 :: 		}
IT	AL
BAL	L_main8
L_main9:
;mic_24045_ARM.c,111 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
