Skywire_HEXIWEAR_system_init:
;Skywire_HEXIWEAR.c,57 :: 		static void system_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Skywire_HEXIWEAR.c,59 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 | _GPIO_PINMASK_2 );
MOVW	R1, #2052
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;Skywire_HEXIWEAR.c,61 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
MOVW	R0, #lo_addr(__GPIO_Module_UART2_PD3_2+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART2_PD3_2+0)
PUSH	(R0)
MOVW	R3, #0
;Skywire_HEXIWEAR.c,60 :: 		UART2_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #115200
;Skywire_HEXIWEAR.c,61 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
BL	_UART2_Init_Advanced+0
ADD	SP, SP, #4
;Skywire_HEXIWEAR.c,63 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
MOVW	R0, #lo_addr(__GPIO_Module_UART3_PC16_17+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART3_PC16_17+0)
PUSH	(R0)
MOVW	R3, #0
;Skywire_HEXIWEAR.c,62 :: 		UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #115200
;Skywire_HEXIWEAR.c,63 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
BL	_UART3_Init_Advanced+0
ADD	SP, SP, #4
;Skywire_HEXIWEAR.c,64 :: 		I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #6784
MOVT	R0, #6
BL	_I2C0_Init_Advanced+0
;Skywire_HEXIWEAR.c,66 :: 		SIM_SCGC6 |= ( 1 << PIT );
MOVW	R0, #lo_addr(SIM_SCGC6+0)
MOVT	R0, #hi_addr(SIM_SCGC6+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #8388608
MOVW	R0, #lo_addr(SIM_SCGC6+0)
MOVT	R0, #hi_addr(SIM_SCGC6+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,67 :: 		PIT_MCR = 0x00;
MOVS	R1, #0
MOVW	R0, #lo_addr(PIT_MCR+0)
MOVT	R0, #hi_addr(PIT_MCR+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,68 :: 		PIT_LDVAL0 = 59999;
MOVW	R1, #59999
MOVW	R0, #lo_addr(PIT_LDVAL0+0)
MOVT	R0, #hi_addr(PIT_LDVAL0+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,69 :: 		PIT_TCTRL0 |= 2;
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #2
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,70 :: 		PIT_TCTRL0 |= 1;
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #1
MOVW	R0, #lo_addr(PIT_TCTRL0+0)
MOVT	R0, #hi_addr(PIT_TCTRL0+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,71 :: 		UART2_C2 |= 1 << 5;
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
LDRB	R0, [R0, #0]
ORR	R1, R0, #32
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
STRB	R1, [R0, #0]
;Skywire_HEXIWEAR.c,72 :: 		NVIC_IntEnable(IVT_INT_PIT0);
MOVW	R0, #64
BL	_NVIC_IntEnable+0
;Skywire_HEXIWEAR.c,73 :: 		NVIC_IntEnable( IVT_INT_UART2_RX_TX );
MOVW	R0, #51
BL	_NVIC_IntEnable+0
;Skywire_HEXIWEAR.c,74 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;Skywire_HEXIWEAR.c,75 :: 		LOG( "\r\n_______________________________\r\n System Initialized\r\n" );
MOVW	R0, #lo_addr(?lstr1_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr1_Skywire_HEXIWEAR+0)
BL	_UART3_Write_Text+0
;Skywire_HEXIWEAR.c,76 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of Skywire_HEXIWEAR_system_init
Skywire_HEXIWEAR_skywire_power_on:
;Skywire_HEXIWEAR.c,81 :: 		static void skywire_power_on( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Skywire_HEXIWEAR.c,83 :: 		SKYWIRE_EN = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,84 :: 		Delay_ms( 5000 );
MOVW	R7, #49662
MOVT	R7, #3051
NOP
NOP
L_Skywire_HEXIWEAR_skywire_power_on0:
SUBS	R7, R7, #1
BNE	L_Skywire_HEXIWEAR_skywire_power_on0
NOP
NOP
NOP
;Skywire_HEXIWEAR.c,85 :: 		SKYWIRE_EN = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,86 :: 		Delay_ms( 3000 );
MOVW	R7, #3582
MOVT	R7, #1831
NOP
NOP
L_Skywire_HEXIWEAR_skywire_power_on2:
SUBS	R7, R7, #1
BNE	L_Skywire_HEXIWEAR_skywire_power_on2
NOP
NOP
NOP
;Skywire_HEXIWEAR.c,87 :: 		LOG( "\r\nSkywire Initialized\r\n" );
MOVW	R0, #lo_addr(?lstr2_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr2_Skywire_HEXIWEAR+0)
BL	_UART3_Write_Text+0
;Skywire_HEXIWEAR.c,88 :: 		}
L_end_skywire_power_on:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of Skywire_HEXIWEAR_skywire_power_on
_rsp_handler:
;Skywire_HEXIWEAR.c,94 :: 		void rsp_handler( char *rsp )
; rsp start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R7, R0
; rsp end address is: 0 (R0)
; rsp start address is: 28 (R7)
;Skywire_HEXIWEAR.c,96 :: 		char tmp[ 25 ] = { 0 };
;Skywire_HEXIWEAR.c,98 :: 		LOG( "Response : \r\n" );
MOVW	R1, #lo_addr(?lstr3_Skywire_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr3_Skywire_HEXIWEAR+0)
MOV	R0, R1
BL	_UART3_Write_Text+0
;Skywire_HEXIWEAR.c,99 :: 		LOG( rsp );
MOV	R0, R7
BL	_UART3_Write_Text+0
;Skywire_HEXIWEAR.c,100 :: 		LOG( "\r\n" );
MOVW	R1, #lo_addr(?lstr4_Skywire_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr4_Skywire_HEXIWEAR+0)
MOV	R0, R1
BL	_UART3_Write_Text+0
;Skywire_HEXIWEAR.c,101 :: 		if( !strncmp( "\r\nRING", rsp, 6 ) )
MOVW	R1, #lo_addr(?lstr5_Skywire_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr5_Skywire_HEXIWEAR+0)
MOVS	R2, #6
MOV	R0, R1
; rsp end address is: 28 (R7)
MOV	R1, R7
BL	_strncmp+0
CMP	R0, #0
IT	NE
BNE	L_rsp_handler4
;Skywire_HEXIWEAR.c,102 :: 		measure_f = true;
MOVS	R2, #1
MOVW	R1, #lo_addr(_measure_f+0)
MOVT	R1, #hi_addr(_measure_f+0)
STRB	R2, [R1, #0]
L_rsp_handler4:
;Skywire_HEXIWEAR.c,103 :: 		}
L_end_rsp_handler:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rsp_handler
_callerid_handler:
;Skywire_HEXIWEAR.c,108 :: 		void callerid_handler( char *rsp )
; rsp start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; rsp end address is: 0 (R0)
; rsp start address is: 0 (R0)
;Skywire_HEXIWEAR.c,113 :: 		tmp_s = strchr( rsp, '\"' );
MOVS	R1, #34
; rsp end address is: 0 (R0)
BL	_strchr+0
; tmp_s start address is: 16 (R4)
MOV	R4, R0
;Skywire_HEXIWEAR.c,114 :: 		tmp_e = strchr( tmp_s + 1, '\"' );
ADDS	R1, R0, #1
MOV	R0, R1
MOVS	R1, #34
BL	_strchr+0
;Skywire_HEXIWEAR.c,115 :: 		strncpy( caller_id, tmp_s, tmp_e - tmp_s + 1 );
SUB	R1, R0, R4
ADDS	R1, R1, #1
SXTH	R2, R1
MOV	R1, R4
; tmp_s end address is: 16 (R4)
MOVW	R0, #lo_addr(_caller_id+0)
MOVT	R0, #hi_addr(_caller_id+0)
BL	_strncpy+0
;Skywire_HEXIWEAR.c,116 :: 		}
L_end_callerid_handler:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _callerid_handler
_measure_temp:
;Skywire_HEXIWEAR.c,121 :: 		void measure_temp( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;Skywire_HEXIWEAR.c,124 :: 		uint8_t tmp_data[ 2 ] = { 0x00 };
MOVS	R0, #0
STRB	R0, [SP, #4]
MOVS	R0, #0
STRB	R0, [SP, #5]
;Skywire_HEXIWEAR.c,126 :: 		I2C_Start();
BL	_I2C_Start+0
;Skywire_HEXIWEAR.c,127 :: 		I2C_Write( 0x48, tmp_data, 1, END_MODE_RESTART );
ADD	R0, SP, #4
MOVW	R3, #0
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #72
BL	_I2C_Write+0
;Skywire_HEXIWEAR.c,128 :: 		I2C_Read( 0x48, tmp_data, 2, END_MODE_STOP );
ADD	R0, SP, #4
MOVW	R3, #1
MOVS	R2, #2
MOV	R1, R0
MOVS	R0, #72
BL	_I2C_Read+0
;Skywire_HEXIWEAR.c,129 :: 		raw_temp = ( ( tmp_data[ 0 ] << 8 ) | tmp_data[ 1 ] ) >> 4;
ADD	R2, SP, #4
LDRB	R0, [R2, #0]
LSLS	R1, R0, #8
UXTH	R1, R1
ADDS	R0, R2, #1
LDRB	R0, [R0, #0]
ORR	R0, R1, R0, LSL #0
UXTH	R0, R0
LSRS	R0, R0, #4
; raw_temp start address is: 4 (R1)
SXTH	R1, R0
;Skywire_HEXIWEAR.c,131 :: 		if( raw_temp & ( 1 << 11 ) )
SXTH	R0, R0
AND	R0, R0, #2048
SXTH	R0, R0
CMP	R0, #0
IT	EQ
BEQ	L__measure_temp12
;Skywire_HEXIWEAR.c,132 :: 		raw_temp |= 0xF800;
ORR	R0, R1, #63488
SXTH	R1, R0
; raw_temp end address is: 4 (R1)
SXTH	R0, R1
IT	AL
BAL	L_measure_temp5
L__measure_temp12:
;Skywire_HEXIWEAR.c,131 :: 		if( raw_temp & ( 1 << 11 ) )
SXTH	R0, R1
;Skywire_HEXIWEAR.c,132 :: 		raw_temp |= 0xF800;
L_measure_temp5:
;Skywire_HEXIWEAR.c,134 :: 		temperature = ( float )( raw_temp * 0.0625 );
; raw_temp start address is: 0 (R0)
VMOV	S1, R0
VCVT.F32	#1, S1, S1
; raw_temp end address is: 0 (R0)
MOV	R0, #1031798784
VMOV	S0, R0
VMUL.F32	S0, S1, S0
MOVW	R0, #lo_addr(_temperature+0)
MOVT	R0, #hi_addr(_temperature+0)
VSTR	#1, S0, [R0, #0]
;Skywire_HEXIWEAR.c,135 :: 		}
L_end_measure_temp:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _measure_temp
_reply_to_caller:
;Skywire_HEXIWEAR.c,140 :: 		void reply_to_caller( void )
SUB	SP, SP, #324
STR	LR, [SP, #0]
;Skywire_HEXIWEAR.c,142 :: 		char tmp[ 30 ] = { 0 };
ADD	R11, SP, #8
ADD	R10, R11, #316
MOVW	R12, #lo_addr(?ICSreply_to_caller_tmp_L0+0)
MOVT	R12, #hi_addr(?ICSreply_to_caller_tmp_L0+0)
BL	___CC2DW+0
;Skywire_HEXIWEAR.c,143 :: 		char cmd_content[ 30 ] = { 0 };                                             // Send SMS command
;Skywire_HEXIWEAR.c,144 :: 		char reply_content[ 256 ] = { 0 };                                          // SMS content
;Skywire_HEXIWEAR.c,146 :: 		strcat( cmd_content, "AT+CMGS=" );
MOVW	R1, #lo_addr(?lstr6_Skywire_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr6_Skywire_HEXIWEAR+0)
ADD	R0, SP, #38
BL	_strcat+0
;Skywire_HEXIWEAR.c,147 :: 		strcat( cmd_content, caller_id );
ADD	R0, SP, #38
MOVW	R1, #lo_addr(_caller_id+0)
MOVT	R1, #hi_addr(_caller_id+0)
BL	_strcat+0
;Skywire_HEXIWEAR.c,148 :: 		strcat( reply_content, "Temperature : " );
MOVW	R1, #lo_addr(?lstr7_Skywire_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr7_Skywire_HEXIWEAR+0)
ADD	R0, SP, #68
BL	_strcat+0
;Skywire_HEXIWEAR.c,149 :: 		FloatToStr( temperature, tmp );
ADD	R1, SP, #8
MOVW	R0, #lo_addr(_temperature+0)
MOVT	R0, #hi_addr(_temperature+0)
VLDR	#1, S0, [R0, #0]
MOV	R0, R1
BL	_FloatToStr+0
;Skywire_HEXIWEAR.c,150 :: 		strcat( reply_content, Ltrim( tmp ) );
ADD	R0, SP, #8
BL	_Ltrim+0
ADD	R1, SP, #68
STR	R1, [SP, #4]
MOV	R1, R0
LDR	R0, [SP, #4]
BL	_strcat+0
;Skywire_HEXIWEAR.c,151 :: 		strcat( reply_content, " C" );
MOVW	R1, #lo_addr(?lstr8_Skywire_HEXIWEAR+0)
MOVT	R1, #hi_addr(?lstr8_Skywire_HEXIWEAR+0)
ADD	R0, SP, #68
BL	_strcat+0
;Skywire_HEXIWEAR.c,152 :: 		at_cmd_double( cmd_content, reply_content );
ADD	R1, SP, #68
ADD	R0, SP, #38
BL	_at_cmd_double+0
;Skywire_HEXIWEAR.c,153 :: 		}
L_end_reply_to_caller:
LDR	LR, [SP, #0]
ADD	SP, SP, #324
BX	LR
; end of _reply_to_caller
_main:
;Skywire_HEXIWEAR.c,156 :: 		void main()
;Skywire_HEXIWEAR.c,158 :: 		measure_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_measure_f+0)
MOVT	R0, #hi_addr(_measure_f+0)
STRB	R1, [R0, #0]
;Skywire_HEXIWEAR.c,159 :: 		system_init();
BL	Skywire_HEXIWEAR_system_init+0
;Skywire_HEXIWEAR.c,160 :: 		skywire_power_on();
BL	Skywire_HEXIWEAR_skywire_power_on+0
;Skywire_HEXIWEAR.c,161 :: 		at_init( rsp_handler, UART2_Write, buffer, sizeof( buffer ) );
MOVW	R1, #lo_addr(_UART2_Write+0)
MOVT	R1, #hi_addr(_UART2_Write+0)
MOVW	R0, #lo_addr(_rsp_handler+0)
MOVT	R0, #hi_addr(_rsp_handler+0)
MOVW	R3, #1024
MOVW	R2, #lo_addr(_buffer+0)
MOVT	R2, #hi_addr(_buffer+0)
BL	_at_init+0
;Skywire_HEXIWEAR.c,162 :: 		at_cmd_save( "+CLCC", 1000, NULL, NULL, NULL, callerid_handler );           // Assign caller ID handler
MOVW	R2, #lo_addr(_callerid_handler+0)
MOVT	R2, #hi_addr(_callerid_handler+0)
MOVS	R1, #0
MOVW	R0, #lo_addr(?lstr9_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr9_Skywire_HEXIWEAR+0)
PUSH	(R2)
PUSH	(R1)
MOVS	R3, #0
MOVS	R2, #0
MOVW	R1, #1000
BL	_at_cmd_save+0
ADD	SP, SP, #8
;Skywire_HEXIWEAR.c,163 :: 		at_cmd_single( "AT" );
MOVW	R0, #lo_addr(?lstr10_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr10_Skywire_HEXIWEAR+0)
BL	_at_cmd_single+0
;Skywire_HEXIWEAR.c,164 :: 		at_cmd_single( "AT+CSCS=\"GSM\"" );
MOVW	R0, #lo_addr(?lstr11_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr11_Skywire_HEXIWEAR+0)
BL	_at_cmd_single+0
;Skywire_HEXIWEAR.c,165 :: 		at_cmd_single( "AT+CMGF=1" );
MOVW	R0, #lo_addr(?lstr12_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr12_Skywire_HEXIWEAR+0)
BL	_at_cmd_single+0
;Skywire_HEXIWEAR.c,167 :: 		while( 1 )
L_main6:
;Skywire_HEXIWEAR.c,169 :: 		at_process();
BL	_at_process+0
;Skywire_HEXIWEAR.c,171 :: 		if( measure_f )
MOVW	R0, #lo_addr(_measure_f+0)
MOVT	R0, #hi_addr(_measure_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main8
;Skywire_HEXIWEAR.c,173 :: 		measure_temp();
BL	_measure_temp+0
;Skywire_HEXIWEAR.c,174 :: 		at_cmd_single( "AT+CLCC" );
MOVW	R0, #lo_addr(?lstr13_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr13_Skywire_HEXIWEAR+0)
BL	_at_cmd_single+0
;Skywire_HEXIWEAR.c,175 :: 		at_cmd_single( "ATH" );
MOVW	R0, #lo_addr(?lstr14_Skywire_HEXIWEAR+0)
MOVT	R0, #hi_addr(?lstr14_Skywire_HEXIWEAR+0)
BL	_at_cmd_single+0
;Skywire_HEXIWEAR.c,176 :: 		Delay_ms( 2000 );                                                   // Delay needed after ATH
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main9:
SUBS	R7, R7, #1
BNE	L_main9
NOP
NOP
NOP
;Skywire_HEXIWEAR.c,177 :: 		reply_to_caller();
BL	_reply_to_caller+0
;Skywire_HEXIWEAR.c,178 :: 		measure_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_measure_f+0)
MOVT	R0, #hi_addr(_measure_f+0)
STRB	R1, [R0, #0]
;Skywire_HEXIWEAR.c,179 :: 		}
L_main8:
;Skywire_HEXIWEAR.c,180 :: 		}
IT	AL
BAL	L_main6
;Skywire_HEXIWEAR.c,181 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_Timer0_interrupt:
;Skywire_HEXIWEAR.c,186 :: 		void Timer0_interrupt() iv IVT_INT_PIT0
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Skywire_HEXIWEAR.c,188 :: 		PIT_TFLG0.TIF = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PIT_TFLG0+0)
MOVT	R0, #hi_addr(PIT_TFLG0+0)
STR	R1, [R0, #0]
;Skywire_HEXIWEAR.c,189 :: 		at_tick();
BL	_at_tick+0
;Skywire_HEXIWEAR.c,190 :: 		}
L_end_Timer0_interrupt:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Timer0_interrupt
_UART2_RX_ISR:
;Skywire_HEXIWEAR.c,195 :: 		void UART2_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_OFF
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Skywire_HEXIWEAR.c,197 :: 		char foo = UART2_S1;
MOVW	R0, #lo_addr(UART2_S1+0)
MOVT	R0, #hi_addr(UART2_S1+0)
; foo start address is: 4 (R1)
LDRB	R1, [R0, #0]
;Skywire_HEXIWEAR.c,198 :: 		char tmp = UART2_D;
MOVW	R0, #lo_addr(UART2_D+0)
MOVT	R0, #hi_addr(UART2_D+0)
; tmp start address is: 8 (R2)
LDRB	R2, [R0, #0]
;Skywire_HEXIWEAR.c,200 :: 		if( foo & ( 1 << 5 ) )
AND	R0, R1, #32
UXTB	R0, R0
; foo end address is: 4 (R1)
CMP	R0, #0
IT	EQ
BEQ	L_UART2_RX_ISR11
;Skywire_HEXIWEAR.c,201 :: 		at_rx( tmp );
UXTB	R0, R2
; tmp end address is: 8 (R2)
BL	_at_rx+0
L_UART2_RX_ISR11:
;Skywire_HEXIWEAR.c,202 :: 		}
L_end_UART2_RX_ISR:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _UART2_RX_ISR
