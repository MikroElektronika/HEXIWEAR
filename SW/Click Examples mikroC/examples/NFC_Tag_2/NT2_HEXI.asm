_system_init:
;NT2_HEXI.c,38 :: 		void system_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;NT2_HEXI.c,41 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
MOVW	R0, #lo_addr(__GPIO_Module_UART3_PC16_17+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART3_PC16_17+0)
PUSH	(R0)
MOVW	R3, #0
;NT2_HEXI.c,40 :: 		UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #115200
;NT2_HEXI.c,41 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
BL	_UART3_Init_Advanced+0
ADD	SP, SP, #4
;NT2_HEXI.c,42 :: 		Delay_ms( 200 );
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_system_init0:
SUBS	R7, R7, #1
BNE	L_system_init0
NOP
NOP
NOP
;NT2_HEXI.c,44 :: 		I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #6784
MOVT	R0, #6
BL	_I2C0_Init_Advanced+0
;NT2_HEXI.c,45 :: 		Delay_ms( 200 );
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_system_init2:
SUBS	R7, R7, #1
BNE	L_system_init2
NOP
NOP
NOP
;NT2_HEXI.c,46 :: 		LOG( "\r\n< < System Initialized > >\r\n" );
MOVW	R0, #lo_addr(?lstr1_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr1_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,47 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _system_init
_print_mem:
;NT2_HEXI.c,49 :: 		void print_mem( uint8_t *ptr, uint16_t len )
; len start address is: 4 (R1)
; ptr start address is: 0 (R0)
SUB	SP, SP, #24
STR	LR, [SP, #0]
MOV	R7, R0
UXTH	R8, R1
; len end address is: 4 (R1)
; ptr end address is: 0 (R0)
; ptr start address is: 28 (R7)
; len start address is: 32 (R8)
;NT2_HEXI.c,53 :: 		LOG( "\t" );
MOVW	R2, #lo_addr(?lstr2_NT2_HEXI+0)
MOVT	R2, #hi_addr(?lstr2_NT2_HEXI+0)
MOV	R0, R2
BL	_UART1_Write_Text+0
;NT2_HEXI.c,54 :: 		for( reg_cnt = 0; reg_cnt < len; reg_cnt++ )
; reg_cnt start address is: 36 (R9)
MOVW	R9, #0
SXTH	R9, R9
; ptr end address is: 28 (R7)
; len end address is: 32 (R8)
; reg_cnt end address is: 36 (R9)
STRH	R8, [SP, #4]
MOV	R8, R7
LDRH	R7, [SP, #4]
L_print_mem4:
; reg_cnt start address is: 36 (R9)
; ptr start address is: 32 (R8)
; len start address is: 28 (R7)
; ptr start address is: 32 (R8)
; ptr end address is: 32 (R8)
CMP	R9, R7
IT	CS
BCS	L_print_mem5
; ptr end address is: 32 (R8)
;NT2_HEXI.c,56 :: 		ByteToHex( *( ptr + reg_cnt ), tmp );
; ptr start address is: 32 (R8)
ADD	R3, SP, #8
ADD	R2, R8, R9, LSL #0
LDRB	R2, [R2, #0]
MOV	R1, R3
UXTB	R0, R2
BL	_ByteToHex+0
;NT2_HEXI.c,57 :: 		LOG( Ltrim( tmp ) );
ADD	R2, SP, #8
MOV	R0, R2
BL	_Ltrim+0
BL	_UART1_Write_Text+0
;NT2_HEXI.c,58 :: 		LOG( " " );
MOVW	R2, #lo_addr(?lstr3_NT2_HEXI+0)
MOVT	R2, #hi_addr(?lstr3_NT2_HEXI+0)
MOV	R0, R2
BL	_UART1_Write_Text+0
;NT2_HEXI.c,59 :: 		if( reg_cnt % 16 ) LOG( "\r\n" );
MOVS	R3, #16
SXTH	R3, R3
SDIV	R2, R9, R3
MLS	R2, R3, R2, R9
SXTH	R2, R2
CMP	R2, #0
IT	EQ
BEQ	L_print_mem7
MOVW	R2, #lo_addr(?lstr4_NT2_HEXI+0)
MOVT	R2, #hi_addr(?lstr4_NT2_HEXI+0)
MOV	R0, R2
BL	_UART1_Write_Text+0
L_print_mem7:
;NT2_HEXI.c,54 :: 		for( reg_cnt = 0; reg_cnt < len; reg_cnt++ )
ADD	R9, R9, #1
SXTH	R9, R9
;NT2_HEXI.c,60 :: 		}
; len end address is: 28 (R7)
; ptr end address is: 32 (R8)
; reg_cnt end address is: 36 (R9)
IT	AL
BAL	L_print_mem4
L_print_mem5:
;NT2_HEXI.c,61 :: 		LOG( "\r\n" );
MOVW	R2, #lo_addr(?lstr5_NT2_HEXI+0)
MOVT	R2, #hi_addr(?lstr5_NT2_HEXI+0)
MOV	R0, R2
BL	_UART1_Write_Text+0
;NT2_HEXI.c,62 :: 		}
L_end_print_mem:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of _print_mem
_test_read_common:
;NT2_HEXI.c,72 :: 		void test_read_common( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;NT2_HEXI.c,74 :: 		LOG( "Read Serial number :" );
MOVW	R0, #lo_addr(?lstr6_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr6_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,75 :: 		if( !nfctag2_get( NT2_SET_SERIAL_NO, NT2_click.serial_num ) )
MOVW	R1, #lo_addr(_NT2_click+1)
MOVT	R1, #hi_addr(_NT2_click+1)
MOVS	R0, #0
BL	_nfctag2_get+0
CMP	R0, #0
IT	NE
BNE	L_test_read_common8
;NT2_HEXI.c,76 :: 		print_mem( NT2_click.serial_num, sizeof( NT2_click.serial_num ) );
MOVS	R1, #7
MOVW	R0, #lo_addr(_NT2_click+1)
MOVT	R0, #hi_addr(_NT2_click+1)
BL	_print_mem+0
L_test_read_common8:
;NT2_HEXI.c,77 :: 		LOG( "Read SRAM :" );
MOVW	R0, #lo_addr(?lstr7_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr7_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,78 :: 		if( !nfctag2_get( NT2_SET_SRAM_MEMORY, NT2_click.sram_memory ) )
MOVW	R1, #lo_addr(_NT2_click+17)
MOVT	R1, #hi_addr(_NT2_click+17)
MOVS	R0, #4
BL	_nfctag2_get+0
CMP	R0, #0
IT	NE
BNE	L_test_read_common9
;NT2_HEXI.c,79 :: 		print_mem( NT2_click.sram_memory, sizeof( NT2_click.sram_memory ) );
MOVS	R1, #64
MOVW	R0, #lo_addr(_NT2_click+17)
MOVT	R0, #hi_addr(_NT2_click+17)
BL	_print_mem+0
L_test_read_common9:
;NT2_HEXI.c,80 :: 		LOG( "Reading SRAM Finished\r\n" );
MOVW	R0, #lo_addr(?lstr8_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr8_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,81 :: 		}
L_end_test_read_common:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _test_read_common
_test_write_common:
;NT2_HEXI.c,83 :: 		void test_write_common( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;NT2_HEXI.c,85 :: 		uint8_t default_CC[ 4 ] = { 0xE1, 0xC0, 0x01, 0x00 };
MOVS	R0, #225
STRB	R0, [SP, #4]
MOVS	R0, #192
STRB	R0, [SP, #5]
MOVS	R0, #1
STRB	R0, [SP, #6]
MOVS	R0, #0
STRB	R0, [SP, #7]
;NT2_HEXI.c,86 :: 		memcpy( NT2_click.cap_containter, default_CC,
ADD	R0, SP, #4
;NT2_HEXI.c,87 :: 		sizeof( NT2_click.cap_containter ) );
MOVS	R2, #4
SXTH	R2, R2
;NT2_HEXI.c,86 :: 		memcpy( NT2_click.cap_containter, default_CC,
MOV	R1, R0
MOVW	R0, #lo_addr(_NT2_click+13)
MOVT	R0, #hi_addr(_NT2_click+13)
;NT2_HEXI.c,87 :: 		sizeof( NT2_click.cap_containter ) );
BL	_memcpy+0
;NT2_HEXI.c,88 :: 		if( !nfctag2_set( NT2_SET_CAP_CONTAINER, NT2_click.cap_containter ) )
MOVW	R1, #lo_addr(_NT2_click+13)
MOVT	R1, #hi_addr(_NT2_click+13)
MOVS	R0, #2
BL	_nfctag2_set+0
CMP	R0, #0
IT	NE
BNE	L_test_write_common10
;NT2_HEXI.c,89 :: 		LOG( "New CC writing finished\r\n" );
MOVW	R0, #lo_addr(?lstr9_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr9_NT2_HEXI+0)
BL	_UART1_Write_Text+0
L_test_write_common10:
;NT2_HEXI.c,90 :: 		}
L_end_test_write_common:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _test_write_common
_test_read_config:
;NT2_HEXI.c,100 :: 		void test_read_config( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;NT2_HEXI.c,102 :: 		LOG( "CLK Stretching " );
MOVW	R0, #lo_addr(?lstr10_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr10_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,103 :: 		if( nfctag2_config_get( NT2_CFG_STR ) | NT2_I2C_CLK_STR_ON )
MOVS	R0, #5
BL	_nfctag2_config_get+0
ORR	R0, R0, #1
UXTB	R0, R0
CMP	R0, #0
IT	EQ
BEQ	L_test_read_config11
;NT2_HEXI.c,104 :: 		LOG( "ON\r\n" );
MOVW	R0, #lo_addr(?lstr11_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr11_NT2_HEXI+0)
BL	_UART1_Write_Text+0
IT	AL
BAL	L_test_read_config12
L_test_read_config11:
;NT2_HEXI.c,106 :: 		LOG( "OFF\r\n");
MOVW	R0, #lo_addr(?lstr12_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr12_NT2_HEXI+0)
BL	_UART1_Write_Text+0
L_test_read_config12:
;NT2_HEXI.c,107 :: 		}
L_end_test_read_config:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _test_read_config
_test_write_config:
;NT2_HEXI.c,109 :: 		void test_write_config( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;NT2_HEXI.c,111 :: 		LOG( "Writing new NC reg content");
MOVW	R0, #lo_addr(?lstr13_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr13_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,115 :: 		NT2_DIRECTION_I2C_TO_RF ) )
MOVS	R1, #0
;NT2_HEXI.c,112 :: 		if( !nfctag2_config_set( NT2_CFG_NC_REG, NT2_I2C_RST_OFF         |
MOVS	R0, #0
;NT2_HEXI.c,115 :: 		NT2_DIRECTION_I2C_TO_RF ) )
BL	_nfctag2_config_set+0
CMP	R0, #0
IT	NE
BNE	L_test_write_config13
;NT2_HEXI.c,116 :: 		LOG( "NC Configuration Written\r\n" );
MOVW	R0, #lo_addr(?lstr14_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr14_NT2_HEXI+0)
BL	_UART1_Write_Text+0
L_test_write_config13:
;NT2_HEXI.c,117 :: 		}
L_end_test_write_config:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _test_write_config
_test_read_session:
;NT2_HEXI.c,127 :: 		void test_read_session( void )
SUB	SP, SP, #16
STR	LR, [SP, #0]
;NT2_HEXI.c,131 :: 		LOG( "< Watchdog Timer >\r\n" );
MOVW	R0, #lo_addr(?lstr15_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr15_NT2_HEXI+0)
BL	_UART1_Write_Text+0
;NT2_HEXI.c,132 :: 		temp[ 0 ] = nfctag2_session_get( NT2_CFG_WDT_MS );
ADD	R0, SP, #4
STR	R0, [SP, #12]
STR	R0, [SP, #8]
MOVS	R0, #4
BL	_nfctag2_session_get+0
LDR	R1, [SP, #8]
STRB	R0, [R1, #0]
;NT2_HEXI.c,133 :: 		temp[ 1 ] = nfctag2_session_get( NT2_CFG_WDT_LS );
LDR	R0, [SP, #12]
ADDS	R0, R0, #1
STR	R0, [SP, #8]
MOVS	R0, #3
BL	_nfctag2_session_get+0
LDR	R1, [SP, #8]
STRB	R0, [R1, #0]
;NT2_HEXI.c,134 :: 		print_mem( temp, 2 );
LDR	R0, [SP, #12]
MOVS	R1, #2
BL	_print_mem+0
;NT2_HEXI.c,135 :: 		}
L_end_test_read_session:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _test_read_session
_test_write_session:
;NT2_HEXI.c,137 :: 		void test_write_session( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;NT2_HEXI.c,140 :: 		NT2_I2C_RST_OFF ) )
MOVS	R2, #0
;NT2_HEXI.c,139 :: 		if( !nfctag2_session_set( NT2_CFG_NC_REG, NT2_MASK_NC_I2C_RST,
MOVS	R1, #128
MOVS	R0, #0
;NT2_HEXI.c,140 :: 		NT2_I2C_RST_OFF ) )
BL	_nfctag2_session_set+0
CMP	R0, #0
IT	NE
BNE	L_test_write_session14
;NT2_HEXI.c,141 :: 		LOG( "Restart the module on I2C Repeated start ON\r\n");
MOVW	R0, #lo_addr(?lstr16_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr16_NT2_HEXI+0)
BL	_UART1_Write_Text+0
L_test_write_session14:
;NT2_HEXI.c,143 :: 		NT2_EEPROM_ERR_CLEAR ) )
MOVS	R2, #0
;NT2_HEXI.c,142 :: 		if( !nfctag2_session_set( NT2_SES_NS_REG, NT2_MASK_NS_EEPROM_MASK,
MOVS	R1, #4
MOVS	R0, #6
;NT2_HEXI.c,143 :: 		NT2_EEPROM_ERR_CLEAR ) )
BL	_nfctag2_session_set+0
CMP	R0, #0
IT	NE
BNE	L_test_write_session15
;NT2_HEXI.c,144 :: 		LOG( "EEPROM Error flag removed\r\n");
MOVW	R0, #lo_addr(?lstr17_NT2_HEXI+0)
MOVT	R0, #hi_addr(?lstr17_NT2_HEXI+0)
BL	_UART1_Write_Text+0
L_test_write_session15:
;NT2_HEXI.c,145 :: 		}
L_end_test_write_session:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _test_write_session
_write_ndef:
;NT2_HEXI.c,153 :: 		void write_ndef( void )
SUB	SP, SP, #24
STR	LR, [SP, #0]
;NT2_HEXI.c,164 :: 		0xFE };      // NDEF Message End Mark
ADD	R11, SP, #4
ADD	R10, R11, #18
MOVW	R12, #lo_addr(?ICSwrite_ndef_ndef_rec_L0+0)
MOVT	R12, #hi_addr(?ICSwrite_ndef_ndef_rec_L0+0)
BL	___CC2DW+0
;NT2_HEXI.c,166 :: 		memset( NT2_click.user_memory, 0, 888 );
MOVW	R2, #888
SXTH	R2, R2
MOVS	R1, #0
MOVW	R0, #lo_addr(_NT2_click+97)
MOVT	R0, #hi_addr(_NT2_click+97)
BL	_memset+0
;NT2_HEXI.c,167 :: 		nfctag2_memory_write( 0, NT2_click.user_memory, 888 );
MOVW	R2, #888
MOVW	R1, #lo_addr(_NT2_click+97)
MOVT	R1, #hi_addr(_NT2_click+97)
MOVS	R0, #0
BL	_nfctag2_memory_write+0
;NT2_HEXI.c,168 :: 		nfctag2_memory_write( 0, ndef_rec, sizeof( ndef_rec ) );
ADD	R0, SP, #4
MOVS	R2, #18
MOV	R1, R0
MOVS	R0, #0
BL	_nfctag2_memory_write+0
;NT2_HEXI.c,169 :: 		}
L_end_write_ndef:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of _write_ndef
_main:
;NT2_HEXI.c,172 :: 		void main()
;NT2_HEXI.c,174 :: 		system_init();
BL	_system_init+0
;NT2_HEXI.c,175 :: 		nfctag2_init( 0x04 );
MOVS	R0, #4
BL	_nfctag2_init+0
;NT2_HEXI.c,186 :: 		write_ndef();
BL	_write_ndef+0
;NT2_HEXI.c,188 :: 		while( 1 );
L_main16:
IT	AL
BAL	L_main16
;NT2_HEXI.c,189 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
