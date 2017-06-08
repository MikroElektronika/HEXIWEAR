Thermo_4_KINETIS_system_init:
;Thermo_4_KINETIS.c,25 :: 		static void system_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Thermo_4_KINETIS.c,28 :: 		UART0_Init( 115200 );
MOV	R0, #115200
BL	_UART0_Init+0
;Thermo_4_KINETIS.c,29 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_Thermo_4_KINETIS_system_init0:
SUBS	R7, R7, #1
BNE	L_Thermo_4_KINETIS_system_init0
NOP
NOP
NOP
;Thermo_4_KINETIS.c,30 :: 		I2C0_Init_Advanced(100000, &_GPIO_Module_I2C0_PD8_9);
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #34464
MOVT	R0, #1
BL	_I2C0_Init_Advanced+0
;Thermo_4_KINETIS.c,31 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_Thermo_4_KINETIS_system_init2:
SUBS	R7, R7, #1
BNE	L_Thermo_4_KINETIS_system_init2
NOP
NOP
NOP
;Thermo_4_KINETIS.c,32 :: 		UART0_Write_Text( "\r\n INITIALIZED  \r\n" );
MOVW	R0, #lo_addr(?lstr1_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr1_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,34 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of Thermo_4_KINETIS_system_init
_main:
;Thermo_4_KINETIS.c,38 :: 		void main()
;Thermo_4_KINETIS.c,41 :: 		system_init();
BL	Thermo_4_KINETIS_system_init+0
;Thermo_4_KINETIS.c,42 :: 		thermo_init(0x55);
MOVS	R0, #85
BL	_thermo_init+0
;Thermo_4_KINETIS.c,43 :: 		Delay_ms (100);
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
;Thermo_4_KINETIS.c,44 :: 		i=5;
MOVS	R1, #5
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
STRB	R1, [R0, #0]
;Thermo_4_KINETIS.c,48 :: 		thermo_write_temperature (65.5, THERMO_TOS);
MOVW	R0, #0
MOVT	R0, #17027
VMOV	S0, R0
MOVS	R0, #3
BL	_thermo_write_temperature+0
;Thermo_4_KINETIS.c,50 :: 		thermo_read_temperature_text (uart_text, THERMO_TOS);
MOVS	R1, #3
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_thermo_read_temperature_text+0
;Thermo_4_KINETIS.c,51 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_main6:
SUBS	R7, R7, #1
BNE	L_main6
NOP
NOP
NOP
;Thermo_4_KINETIS.c,53 :: 		UART0_Write_Text("\r\n Current temperature limit for output signal: ");
MOVW	R0, #lo_addr(?lstr2_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr2_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,54 :: 		UART0_Write_Text(uart_text);
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,55 :: 		Delay_ms( 1000 );
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_main8:
SUBS	R7, R7, #1
BNE	L_main8
NOP
NOP
NOP
;Thermo_4_KINETIS.c,58 :: 		_fh_value = thermo_read_temperature_fh (THERMO_TEMP);
MOVS	R0, #0
BL	_thermo_read_temperature_fh+0
MOVW	R0, #lo_addr(__fh_value+0)
MOVT	R0, #hi_addr(__fh_value+0)
VSTR	#1, S0, [R0, #0]
;Thermo_4_KINETIS.c,59 :: 		FloatToStr (_fh_value , uart_text);
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_FloatToStr+0
;Thermo_4_KINETIS.c,60 :: 		uart_text [5] = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_uart_text+5)
MOVT	R0, #hi_addr(_uart_text+5)
STRB	R1, [R0, #0]
;Thermo_4_KINETIS.c,61 :: 		Delay_ms (100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_main10:
SUBS	R7, R7, #1
BNE	L_main10
NOP
NOP
NOP
;Thermo_4_KINETIS.c,62 :: 		UART0_Write_Text("\r\n \r\n Current temperature in Fahrenheit: ");
MOVW	R0, #lo_addr(?lstr3_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr3_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,63 :: 		UART0_Write_Text(uart_text);
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,64 :: 		Delay_ms( 1000 );
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_main12:
SUBS	R7, R7, #1
BNE	L_main12
NOP
NOP
NOP
;Thermo_4_KINETIS.c,69 :: 		while( i-- )
L_main14:
MOVW	R2, #lo_addr(_i+0)
MOVT	R2, #hi_addr(_i+0)
LDRB	R1, [R2, #0]
MOV	R0, R2
LDRB	R0, [R0, #0]
SUBS	R0, R0, #1
STRB	R0, [R2, #0]
CMP	R1, #0
IT	EQ
BEQ	L_main15
;Thermo_4_KINETIS.c,71 :: 		UART0_Write_Text( "\r\n Current TEMP value: " );
MOVW	R0, #lo_addr(?lstr4_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr4_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,72 :: 		thermo_read_temperature_text (uart_text, THERMO_TEMP);
MOVS	R1, #0
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_thermo_read_temperature_text+0
;Thermo_4_KINETIS.c,73 :: 		UART0_Write_Text(uart_text);
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,74 :: 		Delay_ms( 2000 );
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main16:
SUBS	R7, R7, #1
BNE	L_main16
NOP
NOP
NOP
;Thermo_4_KINETIS.c,75 :: 		}
IT	AL
BAL	L_main14
L_main15:
;Thermo_4_KINETIS.c,79 :: 		thermo_config (THERMO_SHUTDOWN);
MOVS	R0, #1
BL	_thermo_config+0
;Thermo_4_KINETIS.c,80 :: 		UART0_Write_Text( "\r\n SHUTDOWN MODE" );
MOVW	R0, #lo_addr(?lstr5_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr5_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,81 :: 		Delay_ms( 350 );       /*measure time is up to 300 ms*/
MOVW	R7, #40830
MOVT	R7, #213
NOP
NOP
L_main18:
SUBS	R7, R7, #1
BNE	L_main18
NOP
NOP
NOP
;Thermo_4_KINETIS.c,82 :: 		i=5;
MOVS	R1, #5
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
STRB	R1, [R0, #0]
;Thermo_4_KINETIS.c,83 :: 		while( i-- )
L_main20:
MOVW	R2, #lo_addr(_i+0)
MOVT	R2, #hi_addr(_i+0)
LDRB	R1, [R2, #0]
MOV	R0, R2
LDRB	R0, [R0, #0]
SUBS	R0, R0, #1
STRB	R0, [R2, #0]
CMP	R1, #0
IT	EQ
BEQ	L_main21
;Thermo_4_KINETIS.c,85 :: 		UART0_Write_Text( "\r\n Current TEMP value: " );
MOVW	R0, #lo_addr(?lstr6_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr6_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,86 :: 		thermo_read_temperature_text (uart_text, THERMO_TEMP);
MOVS	R1, #0
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_thermo_read_temperature_text+0
;Thermo_4_KINETIS.c,87 :: 		UART0_Write_Text(uart_text);
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,88 :: 		Delay_ms( 2000 );
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main22:
SUBS	R7, R7, #1
BNE	L_main22
NOP
NOP
NOP
;Thermo_4_KINETIS.c,89 :: 		}
IT	AL
BAL	L_main20
L_main21:
;Thermo_4_KINETIS.c,93 :: 		thermo_config (THERMO_POWERUP);
MOVS	R0, #254
BL	_thermo_config+0
;Thermo_4_KINETIS.c,94 :: 		UART0_Write_Text( "\r\n POWERING UP..." );
MOVW	R0, #lo_addr(?lstr7_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr7_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,95 :: 		Delay_ms( 350 );
MOVW	R7, #40830
MOVT	R7, #213
NOP
NOP
L_main24:
SUBS	R7, R7, #1
BNE	L_main24
NOP
NOP
NOP
;Thermo_4_KINETIS.c,96 :: 		i=5;
MOVS	R1, #5
MOVW	R0, #lo_addr(_i+0)
MOVT	R0, #hi_addr(_i+0)
STRB	R1, [R0, #0]
;Thermo_4_KINETIS.c,97 :: 		while( i-- )
L_main26:
MOVW	R2, #lo_addr(_i+0)
MOVT	R2, #hi_addr(_i+0)
LDRB	R1, [R2, #0]
MOV	R0, R2
LDRB	R0, [R0, #0]
SUBS	R0, R0, #1
STRB	R0, [R2, #0]
CMP	R1, #0
IT	EQ
BEQ	L_main27
;Thermo_4_KINETIS.c,99 :: 		UART0_Write_Text( "\r\n Current TEMP value: " );
MOVW	R0, #lo_addr(?lstr8_Thermo_4_KINETIS+0)
MOVT	R0, #hi_addr(?lstr8_Thermo_4_KINETIS+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,100 :: 		thermo_read_temperature_text (uart_text, THERMO_TEMP);
MOVS	R1, #0
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_thermo_read_temperature_text+0
;Thermo_4_KINETIS.c,101 :: 		UART0_Write_Text(uart_text);
MOVW	R0, #lo_addr(_uart_text+0)
MOVT	R0, #hi_addr(_uart_text+0)
BL	_UART0_Write_Text+0
;Thermo_4_KINETIS.c,102 :: 		Delay_ms( 2000 );
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main28:
SUBS	R7, R7, #1
BNE	L_main28
NOP
NOP
NOP
;Thermo_4_KINETIS.c,103 :: 		}
IT	AL
BAL	L_main26
L_main27:
;Thermo_4_KINETIS.c,105 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
