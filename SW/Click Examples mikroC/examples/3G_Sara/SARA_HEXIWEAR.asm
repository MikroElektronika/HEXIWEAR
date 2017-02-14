SARA_HEXIWEAR_system_init:
;SARA_HEXIWEAR.c,57 :: 		static void system_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;SARA_HEXIWEAR.c,59 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
MOVW	R1, #2052
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;SARA_HEXIWEAR.c,61 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
MOVW	R0, #lo_addr(__GPIO_Module_UART2_PD3_2+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART2_PD3_2+0)
PUSH	(R0)
MOVW	R3, #0
;SARA_HEXIWEAR.c,60 :: 		UART2_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #115200
;SARA_HEXIWEAR.c,61 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
BL	_UART2_Init_Advanced+0
ADD	SP, SP, #4
;SARA_HEXIWEAR.c,63 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
MOVW	R0, #lo_addr(__GPIO_Module_UART3_PC16_17+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART3_PC16_17+0)
PUSH	(R0)
MOVW	R3, #0
;SARA_HEXIWEAR.c,62 :: 		UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #115200
;SARA_HEXIWEAR.c,63 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
BL	_UART3_Init_Advanced+0
ADD	SP, SP, #4
;SARA_HEXIWEAR.c,65 :: 		SIM_SCGC6 |= ( 1 << PIT );
MOVW	R0, #lo_addr(SIM_SCGC6+0)
MOVT	R0, #hi_addr(SIM_SCGC6+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #8388608
MOVW	R0, #lo_addr(SIM_SCGC6+0)
MOVT	R0, #hi_addr(SIM_SCGC6+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,66 :: 		PIT_MCR = 0x00;
MOVS	R1, #0
MOVW	R0, #lo_addr(PIT_MCR+0)
MOVT	R0, #hi_addr(PIT_MCR+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,67 :: 		PIT_LDVAL0 = 59999;
MOVW	R1, #59999
MOVW	R0, #lo_addr(PIT_LDVAL0+0)
MOVT	R0, #hi_addr(PIT_LDVAL0+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,68 :: 		PIT_TCTRL0 |= 2;
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #2
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,69 :: 		PIT_TCTRL0 |= 1;
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #1
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,70 :: 		UART2_C2 |= 1 << 5;
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
LDRB	R0, [R0, #0]
ORR	R1, R0, #32
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
STRB	R1, [R0, #0]
;SARA_HEXIWEAR.c,71 :: 		NVIC_IntEnable(IVT_INT_PIT0);
MOVW	R0, #64
BL	_NVIC_IntEnable+0
;SARA_HEXIWEAR.c,72 :: 		NVIC_IntEnable( IVT_INT_UART2_RX_TX );
MOVW	R0, #51
BL	_NVIC_IntEnable+0
;SARA_HEXIWEAR.c,73 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;SARA_HEXIWEAR.c,74 :: 		LOG( "\r\n_______________________________\r\n System Initialized\r\n" );
MOVW	R0, #lo_addr(?lstr1_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr1_SARA_HEXIWEAR+0)
BL	_UART3_Write_Text+0
;SARA_HEXIWEAR.c,75 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of SARA_HEXIWEAR_system_init
_sara_power_on:
;SARA_HEXIWEAR.c,80 :: 		void sara_power_on( void )
SUB	SP, SP, #4
;SARA_HEXIWEAR.c,82 :: 		SARA_PWR = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,83 :: 		Delay_ms( 50 );
MOVW	R7, #33918
MOVT	R7, #30
NOP
NOP
L_sara_power_on0:
SUBS	R7, R7, #1
BNE	L_sara_power_on0
NOP
NOP
NOP
;SARA_HEXIWEAR.c,84 :: 		SARA_PWR = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,85 :: 		Delay_ms( 50 );
MOVW	R7, #33918
MOVT	R7, #30
NOP
NOP
L_sara_power_on2:
SUBS	R7, R7, #1
BNE	L_sara_power_on2
NOP
NOP
NOP
;SARA_HEXIWEAR.c,86 :: 		SARA_PWR = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,87 :: 		Delay_ms( 10000 );
MOVW	R7, #33790
MOVT	R7, #6103
NOP
NOP
L_sara_power_on4:
SUBS	R7, R7, #1
BNE	L_sara_power_on4
NOP
NOP
NOP
;SARA_HEXIWEAR.c,88 :: 		}
L_end_sara_power_on:
ADD	SP, SP, #4
BX	LR
; end of _sara_power_on
_rsp_handler:
;SARA_HEXIWEAR.c,93 :: 		void rsp_handler( char *rsp )
; rsp start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R7, R0
; rsp end address is: 0 (R0)
; rsp start address is: 28 (R7)
;SARA_HEXIWEAR.c,95 :: 		char tmp[ 25 ] = { 0 };
;SARA_HEXIWEAR.c,97 :: 		LOG( "Response : \r\n" );
MOVW	R1, #lo_addr(?lstr2_SARA_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr2_SARA_HEXIWEAR+0)
MOV	R0, R1
BL	_UART3_Write_Text+0
;SARA_HEXIWEAR.c,98 :: 		LOG( rsp );
MOV	R0, R7
BL	_UART3_Write_Text+0
;SARA_HEXIWEAR.c,99 :: 		LOG( "\r\n" );
MOVW	R1, #lo_addr(?lstr3_SARA_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr3_SARA_HEXIWEAR+0)
MOV	R0, R1
BL	_UART3_Write_Text+0
;SARA_HEXIWEAR.c,100 :: 		if( !strncmp( "\r\nRING", rsp, 6 ) )
MOVW	R1, #lo_addr(?lstr4_SARA_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr4_SARA_HEXIWEAR+0)
MOVS	R2, #6
MOV	R0, R1
; rsp end address is: 28 (R7)
MOV	R1, R7
BL	_strncmp+0
CMP	R0, #0
IT	NE
BNE	L_rsp_handler6
;SARA_HEXIWEAR.c,101 :: 		measure_f = true;
MOVS	R2, #1
MOVW	R1, #lo_addr(_measure_f+0)
MOVT	R1, #hi_addr(_measure_f+0)
STRB	R2, [R1, #0]
L_rsp_handler6:
;SARA_HEXIWEAR.c,102 :: 		}
L_end_rsp_handler:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rsp_handler
_callerid_handler:
;SARA_HEXIWEAR.c,107 :: 		void callerid_handler( char *rsp )
; rsp start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; rsp end address is: 0 (R0)
; rsp start address is: 0 (R0)
;SARA_HEXIWEAR.c,112 :: 		tmp_s = strchr( rsp, '\"' );
MOVS	R1, #34
; rsp end address is: 0 (R0)
BL	_strchr+0
; tmp_s start address is: 16 (R4)
MOV	R4, R0
;SARA_HEXIWEAR.c,113 :: 		tmp_e = strchr( tmp_s + 1, '\"' );
ADDS	R1, R0, #1
MOV	R0, R1
MOVS	R1, #34
BL	_strchr+0
;SARA_HEXIWEAR.c,114 :: 		strncpy( caller_id, tmp_s, tmp_e - tmp_s + 1 );
SUB	R1, R0, R4
ADDS	R1, R1, #1
SXTH	R2, R1
MOV	R1, R4
; tmp_s end address is: 16 (R4)
MOVW	R0, #lo_addr(_caller_id+0)
MOVT	R0, #hi_addr(_caller_id+0)
BL	_strncpy+0
;SARA_HEXIWEAR.c,115 :: 		}
L_end_callerid_handler:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _callerid_handler
_reply_to_caller:
;SARA_HEXIWEAR.c,120 :: 		void reply_to_caller( void )
SUB	SP, SP, #292
STR	LR, [SP, #0]
;SARA_HEXIWEAR.c,122 :: 		char tmp[ 30 ] = { 0 };
;SARA_HEXIWEAR.c,123 :: 		char cmd_content[ 30 ] = { 0 };                                             // Send SMS command
ADD	R11, SP, #4
ADD	R10, R11, #286
MOVW	R12, #lo_addr(?ICSreply_to_caller_cmd_content_L0+0)
MOVT	R12, #hi_addr(?ICSreply_to_caller_cmd_content_L0+0)
BL	___CC2DW+0
;SARA_HEXIWEAR.c,124 :: 		char reply_content[ 256 ] = { 0 };                                          // SMS content
;SARA_HEXIWEAR.c,126 :: 		strcat( cmd_content, "AT+CMGS=" );
MOVW	R1, #lo_addr(?lstr5_SARA_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr5_SARA_HEXIWEAR+0)
ADD	R0, SP, #4
BL	_strcat+0
;SARA_HEXIWEAR.c,127 :: 		strcat( cmd_content, caller_id );
ADD	R0, SP, #4
MOVW	R1, #lo_addr(_caller_id+0)
MOVT	R1, #hi_addr(_caller_id+0)
BL	_strcat+0
;SARA_HEXIWEAR.c,128 :: 		strcat( reply_content, "Hello it's me HEXIWEAR :)" );
MOVW	R1, #lo_addr(?lstr6_SARA_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr6_SARA_HEXIWEAR+0)
ADD	R0, SP, #34
BL	_strcat+0
;SARA_HEXIWEAR.c,129 :: 		at_cmd_double( cmd_content, reply_content );
ADD	R1, SP, #34
ADD	R0, SP, #4
BL	_at_cmd_double+0
;SARA_HEXIWEAR.c,130 :: 		}
L_end_reply_to_caller:
LDR	LR, [SP, #0]
ADD	SP, SP, #292
BX	LR
; end of _reply_to_caller
_main:
;SARA_HEXIWEAR.c,133 :: 		void main()
SUB	SP, SP, #4
;SARA_HEXIWEAR.c,135 :: 		measure_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_measure_f+0)
MOVT	R0, #hi_addr(_measure_f+0)
STRB	R1, [R0, #0]
;SARA_HEXIWEAR.c,136 :: 		system_init();
BL	SARA_HEXIWEAR_system_init+0
;SARA_HEXIWEAR.c,137 :: 		sara_power_on();
BL	_sara_power_on+0
;SARA_HEXIWEAR.c,138 :: 		at_init( rsp_handler, UART2_Write, buffer, sizeof( buffer ) );
MOVW	R1, #lo_addr(_UART2_Write+0)
MOVT	R1, #hi_addr(_UART2_Write+0)
MOVW	R0, #lo_addr(_rsp_handler+0)
MOVT	R0, #hi_addr(_rsp_handler+0)
MOVW	R3, #1024
MOVW	R2, #lo_addr(_buffer+0)
MOVT	R2, #hi_addr(_buffer+0)
BL	_at_init+0
;SARA_HEXIWEAR.c,139 :: 		at_cmd_save( "+CLCC", 1000, NULL, NULL, NULL, callerid_handler );           // Assign caller ID handler
MOVW	R2, #lo_addr(_callerid_handler+0)
MOVT	R2, #hi_addr(_callerid_handler+0)
MOVS	R1, #0
MOVW	R0, #lo_addr(?lstr7_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr7_SARA_HEXIWEAR+0)
PUSH	(R2)
PUSH	(R1)
MOVS	R3, #0
MOVS	R2, #0
MOVW	R1, #1000
BL	_at_cmd_save+0
ADD	SP, SP, #8
;SARA_HEXIWEAR.c,140 :: 		at_cmd_single( "AT" );
MOVW	R0, #lo_addr(?lstr8_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr8_SARA_HEXIWEAR+0)
BL	_at_cmd_single+0
;SARA_HEXIWEAR.c,141 :: 		at_cmd_single( "AT+CSCS=\"GSM\"" );
MOVW	R0, #lo_addr(?lstr9_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr9_SARA_HEXIWEAR+0)
BL	_at_cmd_single+0
;SARA_HEXIWEAR.c,142 :: 		at_cmd_single( "AT+CMGF=1" );
MOVW	R0, #lo_addr(?lstr10_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr10_SARA_HEXIWEAR+0)
BL	_at_cmd_single+0
;SARA_HEXIWEAR.c,144 :: 		while( 1 )
L_main7:
;SARA_HEXIWEAR.c,146 :: 		at_process();
BL	_at_process+0
;SARA_HEXIWEAR.c,148 :: 		if( measure_f )
MOVW	R0, #lo_addr(_measure_f+0)
MOVT	R0, #hi_addr(_measure_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main9
;SARA_HEXIWEAR.c,150 :: 		at_cmd_single( "AT+CLCC" );
MOVW	R0, #lo_addr(?lstr11_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr11_SARA_HEXIWEAR+0)
BL	_at_cmd_single+0
;SARA_HEXIWEAR.c,151 :: 		at_cmd_single( "ATH" );
MOVW	R0, #lo_addr(?lstr12_SARA_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr12_SARA_HEXIWEAR+0)
BL	_at_cmd_single+0
;SARA_HEXIWEAR.c,152 :: 		Delay_ms( 3000 );                                                   // Delay needed after ATH
MOVW	R7, #3582
MOVT	R7, #1831
NOP
NOP
L_main10:
SUBS	R7, R7, #1
BNE	L_main10
NOP
NOP
NOP
;SARA_HEXIWEAR.c,153 :: 		reply_to_caller();
BL	_reply_to_caller+0
;SARA_HEXIWEAR.c,154 :: 		measure_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_measure_f+0)
MOVT	R0, #hi_addr(_measure_f+0)
STRB	R1, [R0, #0]
;SARA_HEXIWEAR.c,155 :: 		}
L_main9:
;SARA_HEXIWEAR.c,156 :: 		}
IT	AL
BAL	L_main7
;SARA_HEXIWEAR.c,157 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_Timer0_interrupt:
;SARA_HEXIWEAR.c,162 :: 		void Timer0_interrupt() iv IVT_INT_PIT0
SUB	SP, SP, #4
STR	LR, [SP, #0]
;SARA_HEXIWEAR.c,164 :: 		PIT_TFLG0.TIF = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PIT_TFLG0+0)
MOVT	R0, #hi_addr(PIT_TFLG0+0)
STR	R1, [R0, #0]
;SARA_HEXIWEAR.c,165 :: 		at_tick();
BL	_at_tick+0
;SARA_HEXIWEAR.c,166 :: 		}
L_end_Timer0_interrupt:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Timer0_interrupt
_UART2_RX_ISR:
;SARA_HEXIWEAR.c,171 :: 		void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_OFF
SUB	SP, SP, #4
STR	LR, [SP, #0]
;SARA_HEXIWEAR.c,173 :: 		char foo = UART2_S1;
MOVW	R0, #lo_addr(UART2_S1+0)
MOVT	R0, #hi_addr(UART2_S1+0)
; foo start address is: 4 (R1)
LDRB	R1, [R0, #0]
;SARA_HEXIWEAR.c,174 :: 		char tmp = UART2_D;
MOVW	R0, #lo_addr(UART2_D+0)
MOVT	R0, #hi_addr(UART2_D+0)
; tmp start address is: 8 (R2)
LDRB	R2, [R0, #0]
;SARA_HEXIWEAR.c,176 :: 		if( foo & ( 1 << 5 ) )
AND	R0, R1, #32
UXTB	R0, R0
; foo end address is: 4 (R1)
CMP	R0, #0
IT	EQ
BEQ	L_UART2_RX_ISR12
;SARA_HEXIWEAR.c,177 :: 		at_rx( tmp );
UXTB	R0, R2
; tmp end address is: 8 (R2)
BL	_at_rx+0
L_UART2_RX_ISR12:
;SARA_HEXIWEAR.c,178 :: 		}
L_end_UART2_RX_ISR:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _UART2_RX_ISR
