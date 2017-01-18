at_engine__tx:
;at_engine.c,299 :: 		static void _tx( uint8_t *tx_input, uint8_t delimiter )
; tx_input start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R1, [SP, #8]
; tx_input end address is: 0 (R0)
; tx_input start address is: 0 (R0)
; tx_input end address is: 0 (R0)
;at_engine.c,304 :: 		while( *tx_input )
L_at_engine__tx0:
; tx_input start address is: 0 (R0)
LDRB	R2, [R0, #0]
CMP	R2, #0
IT	EQ
BEQ	L_at_engine__tx1
;at_engine.c,313 :: 		write_uart_p( *tx_input++ );
LDRB	R2, [R0, #0]
UXTB	R4, R2
STR	R0, [SP, #4]
UXTH	R0, R4
MOVW	R4, #lo_addr(at_engine_write_uart_p+0)
MOVT	R4, #hi_addr(at_engine_write_uart_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDR	R0, [SP, #4]
ADDS	R2, R0, #1
; tx_input end address is: 0 (R0)
; tx_input start address is: 4 (R1)
MOV	R1, R2
;at_engine.c,314 :: 		}
MOV	R0, R1
; tx_input end address is: 4 (R1)
IT	AL
BAL	L_at_engine__tx0
L_at_engine__tx1:
;at_engine.c,316 :: 		write_uart_p( delimiter );
LDRB	R0, [SP, #8]
MOVW	R4, #lo_addr(at_engine_write_uart_p+0)
MOVT	R4, #hi_addr(at_engine_write_uart_p+0)
LDR	R4, [R4, #0]
BLX	R4
;at_engine.c,317 :: 		write_uart_p( '\n' );
MOVS	R0, #10
MOVW	R4, #lo_addr(at_engine_write_uart_p+0)
MOVT	R4, #hi_addr(at_engine_write_uart_p+0)
LDR	R4, [R4, #0]
BLX	R4
;at_engine.c,322 :: 		}
L_end__tx:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of at_engine__tx
at_engine__parse_hash:
;at_engine.c,324 :: 		static uint32_t _parse_hash( char *cmd )
; cmd start address is: 0 (R0)
MOV	R1, R0
; cmd end address is: 0 (R0)
; cmd start address is: 4 (R1)
;at_engine.c,326 :: 		uint16_t ch     = 0;
;at_engine.c,327 :: 		uint32_t hash   = 4321;
; hash start address is: 0 (R0)
MOVW	R0, #4321
MOVT	R0, #0
; cmd end address is: 4 (R1)
; hash end address is: 0 (R0)
MOV	R3, R1
;at_engine.c,328 :: 		while( ( ch = *( cmd++ ) ) )
L_at_engine__parse_hash2:
; hash start address is: 0 (R0)
; cmd start address is: 12 (R3)
; cmd start address is: 12 (R3)
MOV	R2, R3
ADDS	R1, R3, #1
MOV	R3, R1
; cmd end address is: 12 (R3)
LDRB	R1, [R2, #0]
; ch start address is: 8 (R2)
UXTB	R2, R1
CMP	R2, #0
IT	EQ
BEQ	L_at_engine__parse_hash3
; cmd end address is: 12 (R3)
;at_engine.c,329 :: 		hash = ( ( hash << 5 ) + hash ) + ch;
; cmd start address is: 12 (R3)
LSLS	R1, R0, #5
ADDS	R1, R1, R0
; hash end address is: 0 (R0)
ADDS	R1, R1, R2
; hash start address is: 0 (R0)
MOV	R0, R1
; cmd end address is: 12 (R3)
; ch end address is: 8 (R2)
IT	AL
BAL	L_at_engine__parse_hash2
L_at_engine__parse_hash3:
;at_engine.c,330 :: 		return hash;
; hash end address is: 0 (R0)
;at_engine.c,331 :: 		}
L_end__parse_hash:
BX	LR
; end of at_engine__parse_hash
at_engine__parse_find:
;at_engine.c,333 :: 		static uint16_t _parse_find( char* cmd )
; cmd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
;at_engine.c,335 :: 		uint8_t _cnt = 0;
;at_engine.c,337 :: 		uint32_t tmp_hash = _parse_hash( cmd );
; cmd end address is: 0 (R0)
BL	at_engine__parse_hash+0
; tmp_hash start address is: 0 (R0)
;at_engine.c,338 :: 		for( _cnt = 0; _cnt < at_cmd_storage_used; _cnt++ )
; _cnt start address is: 12 (R3)
MOVS	R3, #0
; _cnt end address is: 12 (R3)
L_at_engine__parse_find4:
; _cnt start address is: 12 (R3)
; tmp_hash start address is: 0 (R0)
; tmp_hash end address is: 0 (R0)
MOVW	R1, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R1, #hi_addr(at_engine_at_cmd_storage_used+0)
LDRB	R1, [R1, #0]
CMP	R3, R1
IT	CS
BCS	L_at_engine__parse_find5
; tmp_hash end address is: 0 (R0)
;at_engine.c,339 :: 		if( at_cmd_storage[ _cnt ].hash == tmp_hash )
; tmp_hash start address is: 0 (R0)
MOVS	R1, #24
MUL	R2, R1, R3
MOVW	R1, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R1, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R1, R1, R2
LDR	R1, [R1, #0]
CMP	R1, R0
IT	NE
BNE	L_at_engine__parse_find7
; tmp_hash end address is: 0 (R0)
;at_engine.c,340 :: 		return _cnt;
UXTB	R0, R3
; _cnt end address is: 12 (R3)
IT	AL
BAL	L_end__parse_find
L_at_engine__parse_find7:
;at_engine.c,338 :: 		for( _cnt = 0; _cnt < at_cmd_storage_used; _cnt++ )
; _cnt start address is: 12 (R3)
; tmp_hash start address is: 0 (R0)
ADDS	R3, R3, #1
UXTB	R3, R3
;at_engine.c,340 :: 		return _cnt;
; tmp_hash end address is: 0 (R0)
; _cnt end address is: 12 (R3)
IT	AL
BAL	L_at_engine__parse_find4
L_at_engine__parse_find5:
;at_engine.c,341 :: 		return 0;
MOVS	R0, #0
;at_engine.c,342 :: 		}
L_end__parse_find:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of at_engine__parse_find
at_engine__parse_save:
;at_engine.c,346 :: 		at_cmd_cb tester, at_cmd_cb executer )
; setter start address is: 12 (R3)
; getter start address is: 8 (R2)
; timeout start address is: 4 (R1)
; command start address is: 0 (R0)
SUB	SP, SP, #28
STR	LR, [SP, #0]
MOV	R5, R0
MOV	R4, R1
MOV	R6, R2
MOV	R7, R3
; setter end address is: 12 (R3)
; getter end address is: 8 (R2)
; timeout end address is: 4 (R1)
; command end address is: 0 (R0)
; command start address is: 20 (R5)
; timeout start address is: 16 (R4)
; getter start address is: 24 (R6)
; setter start address is: 28 (R7)
; tester start address is: 32 (R8)
LDR	R8, [SP, #28]
; executer start address is: 36 (R9)
LDR	R9, [SP, #32]
;at_engine.c,350 :: 		cmd.hash        = _parse_hash( command );
MOV	R0, R5
BL	at_engine__parse_hash+0
STR	R0, [SP, #4]
;at_engine.c,351 :: 		cmd.timeout     = timeout;
STR	R4, [SP, #8]
; timeout end address is: 16 (R4)
;at_engine.c,352 :: 		cmd.getter      = getter;
STR	R6, [SP, #12]
; getter end address is: 24 (R6)
;at_engine.c,353 :: 		cmd.setter      = setter;
STR	R7, [SP, #16]
; setter end address is: 28 (R7)
;at_engine.c,354 :: 		cmd.tester      = tester;
STR	R8, [SP, #20]
; tester end address is: 32 (R8)
;at_engine.c,355 :: 		cmd.executer    = executer;
STR	R9, [SP, #24]
; executer end address is: 36 (R9)
;at_engine.c,357 :: 		if( strlen( command ) >= AT_HEADER_SIZE_MAX + AT_HEAD_SIZE )
MOV	R0, R5
BL	_strlen+0
CMP	R0, #17
IT	LT
BLT	L_at_engine__parse_save8
; command end address is: 20 (R5)
;at_engine.c,358 :: 		return;
IT	AL
BAL	L_end__parse_save
L_at_engine__parse_save8:
;at_engine.c,360 :: 		if( at_cmd_storage_used == AT_STORAGE_SIZE )
; command start address is: 20 (R5)
MOVW	R4, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage_used+0)
LDRB	R4, [R4, #0]
CMP	R4, #50
IT	NE
BNE	L_at_engine__parse_save9
; command end address is: 20 (R5)
;at_engine.c,361 :: 		return;
IT	AL
BAL	L_end__parse_save
L_at_engine__parse_save9:
;at_engine.c,363 :: 		if( _parse_find( command ) )
; command start address is: 20 (R5)
MOV	R0, R5
; command end address is: 20 (R5)
BL	at_engine__parse_find+0
CMP	R0, #0
IT	EQ
BEQ	L_at_engine__parse_save10
;at_engine.c,364 :: 		return;
IT	AL
BAL	L_end__parse_save
L_at_engine__parse_save10:
;at_engine.c,366 :: 		at_cmd_storage[ at_cmd_storage_used ] = cmd;
MOVW	R4, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage_used+0)
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
MOV	R7, #24
MOV	R6, R4
ADD	R5, SP, #4
L_at_engine__parse_save11:
LDRB	R4, [R5, #0]
STRB	R4, [R6, #0]
SUBS	R7, R7, #1
ADDS	R5, R5, #1
ADDS	R6, R6, #1
CMP	R7, #0
IT	NE
BNE	L_at_engine__parse_save11
;at_engine.c,367 :: 		at_cmd_storage_used++;
MOVW	R5, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R5, #hi_addr(at_engine_at_cmd_storage_used+0)
LDRB	R4, [R5, #0]
ADDS	R4, R4, #1
STRB	R4, [R5, #0]
;at_engine.c,368 :: 		}
L_end__parse_save:
LDR	LR, [SP, #0]
ADD	SP, SP, #28
BX	LR
; end of at_engine__parse_save
at_engine__parse_pre:
;at_engine.c,370 :: 		static at_type_t _parse_pre( char *raw_in, char *clean_out )
; clean_out start address is: 4 (R1)
; raw_in start address is: 0 (R0)
SUB	SP, SP, #24
STR	LR, [SP, #0]
MOV	R7, R1
; clean_out end address is: 4 (R1)
; raw_in end address is: 0 (R0)
; raw_in start address is: 0 (R0)
; clean_out start address is: 28 (R7)
;at_engine.c,372 :: 		uint8_t     _cnt                   = 0;
;at_engine.c,373 :: 		uint8_t     end_pos                   = 0;
; end_pos start address is: 32 (R8)
MOVW	R8, #0
;at_engine.c,374 :: 		uint8_t     set_pos                   = 0;
; set_pos start address is: 4 (R1)
MOVS	R1, #0
;at_engine.c,375 :: 		uint8_t     get_pos                   = 0;
; get_pos start address is: 12 (R3)
MOVS	R3, #0
;at_engine.c,376 :: 		uint8_t     start_pos                 = 0;
; start_pos start address is: 16 (R4)
MOVS	R4, #0
;at_engine.c,377 :: 		char*       tmp_ptr                   = raw_in;
; tmp_ptr start address is: 20 (R5)
MOV	R5, R0
; raw_in end address is: 0 (R0)
;at_engine.c,378 :: 		char        tmp_cmd[ AT_HEADER_SIZE_MAX ] = { 0 };
ADD	R11, SP, #8
ADD	R10, R11, #15
MOVW	R12, #lo_addr(?ICSat_engine__parse_pre_tmp_cmd_L0+0)
MOVT	R12, #hi_addr(?ICSat_engine__parse_pre_tmp_cmd_L0+0)
BL	___CC2DW+0
;at_engine.c,380 :: 		if( strlen( tmp_ptr ) <= AT_HEAD_SIZE )
STRB	R3, [SP, #4]
STRB	R1, [SP, #5]
MOV	R0, R5
BL	_strlen+0
LDRB	R1, [SP, #5]
LDRB	R3, [SP, #4]
CMP	R0, #2
IT	GT
BGT	L_at_engine__parse_pre12
; end_pos end address is: 32 (R8)
; set_pos end address is: 4 (R1)
; get_pos end address is: 12 (R3)
; start_pos end address is: 16 (R4)
; tmp_ptr end address is: 20 (R5)
; clean_out end address is: 28 (R7)
;at_engine.c,381 :: 		return AT_CMD_UNKNOWN;
MOVS	R0, #0
IT	AL
BAL	L_end__parse_pre
L_at_engine__parse_pre12:
;at_engine.c,383 :: 		strncpy( tmp_cmd, tmp_ptr, AT_HEADER_SIZE_MAX );
; clean_out start address is: 28 (R7)
; tmp_ptr start address is: 20 (R5)
; start_pos start address is: 16 (R4)
; get_pos start address is: 12 (R3)
; set_pos start address is: 4 (R1)
; end_pos start address is: 32 (R8)
ADD	R2, SP, #8
STRB	R4, [SP, #4]
STRB	R3, [SP, #5]
STRB	R1, [SP, #6]
MOV	R1, R5
MOV	R0, R2
; tmp_ptr end address is: 20 (R5)
MOVS	R2, #15
SXTH	R2, R2
BL	_strncpy+0
LDRB	R1, [SP, #6]
LDRB	R3, [SP, #5]
LDRB	R4, [SP, #4]
;at_engine.c,385 :: 		for( _cnt = 0; _cnt < AT_HEADER_SIZE_MAX; _cnt++ )
; _cnt start address is: 0 (R0)
MOVS	R0, #0
; end_pos end address is: 32 (R8)
; set_pos end address is: 4 (R1)
; get_pos end address is: 12 (R3)
; start_pos end address is: 16 (R4)
; clean_out end address is: 28 (R7)
; _cnt end address is: 0 (R0)
STRB	R3, [SP, #4]
UXTB	R3, R8
UXTB	R9, R1
UXTB	R10, R4
LDRB	R8, [SP, #4]
L_at_engine__parse_pre13:
; _cnt start address is: 0 (R0)
; start_pos start address is: 40 (R10)
; get_pos start address is: 32 (R8)
; set_pos start address is: 36 (R9)
; end_pos start address is: 12 (R3)
; clean_out start address is: 28 (R7)
CMP	R0, #15
IT	CS
BCS	L_at_engine__parse_pre118
;at_engine.c,387 :: 		if( tmp_cmd[ _cnt ] == '\0' )
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
CMP	R2, #0
IT	NE
BNE	L_at_engine__parse_pre16
;at_engine.c,389 :: 		if( !end_pos )
CMP	R3, #0
IT	NE
BNE	L_at_engine__parse_pre109
; end_pos end address is: 12 (R3)
;at_engine.c,390 :: 		end_pos = _cnt;
; end_pos start address is: 4 (R1)
UXTB	R1, R0
; end_pos end address is: 4 (R1)
; _cnt end address is: 0 (R0)
UXTB	R0, R1
IT	AL
BAL	L_at_engine__parse_pre17
L_at_engine__parse_pre109:
;at_engine.c,389 :: 		if( !end_pos )
UXTB	R0, R3
;at_engine.c,390 :: 		end_pos = _cnt;
L_at_engine__parse_pre17:
;at_engine.c,391 :: 		break;
; end_pos start address is: 0 (R0)
; end_pos end address is: 0 (R0)
IT	AL
BAL	L_at_engine__parse_pre14
;at_engine.c,392 :: 		}
L_at_engine__parse_pre16:
;at_engine.c,399 :: 		if( ( tmp_cmd[ _cnt ] == '+') && !start_pos )
; _cnt start address is: 0 (R0)
; end_pos start address is: 12 (R3)
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
CMP	R2, #43
IT	NE
BNE	L_at_engine__parse_pre110
CMP	R10, #0
IT	NE
BNE	L_at_engine__parse_pre111
; start_pos end address is: 40 (R10)
L_at_engine__parse_pre91:
;at_engine.c,400 :: 		start_pos = _cnt;
; start_pos start address is: 4 (R1)
UXTB	R1, R0
; start_pos end address is: 4 (R1)
;at_engine.c,399 :: 		if( ( tmp_cmd[ _cnt ] == '+') && !start_pos )
IT	AL
BAL	L_at_engine__parse_pre93
L_at_engine__parse_pre110:
UXTB	R1, R10
L_at_engine__parse_pre93:
; start_pos start address is: 4 (R1)
; start_pos end address is: 4 (R1)
IT	AL
BAL	L_at_engine__parse_pre92
L_at_engine__parse_pre111:
UXTB	R1, R10
L_at_engine__parse_pre92:
;at_engine.c,402 :: 		if( ( tmp_cmd[ _cnt ] == '=' ) && !set_pos )
; start_pos start address is: 4 (R1)
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
CMP	R2, #61
IT	NE
BNE	L_at_engine__parse_pre112
CMP	R9, #0
IT	NE
BNE	L_at_engine__parse_pre113
; set_pos end address is: 36 (R9)
L_at_engine__parse_pre90:
;at_engine.c,403 :: 		set_pos = _cnt;
; set_pos start address is: 8 (R2)
UXTB	R2, R0
; set_pos end address is: 8 (R2)
UXTB	R9, R2
;at_engine.c,402 :: 		if( ( tmp_cmd[ _cnt ] == '=' ) && !set_pos )
IT	AL
BAL	L_at_engine__parse_pre95
L_at_engine__parse_pre112:
L_at_engine__parse_pre95:
; set_pos start address is: 36 (R9)
; set_pos end address is: 36 (R9)
IT	AL
BAL	L_at_engine__parse_pre94
L_at_engine__parse_pre113:
L_at_engine__parse_pre94:
;at_engine.c,405 :: 		if( ( tmp_cmd[ _cnt ] == '?' ) && !get_pos )
; set_pos start address is: 36 (R9)
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
CMP	R2, #63
IT	NE
BNE	L_at_engine__parse_pre114
CMP	R8, #0
IT	NE
BNE	L_at_engine__parse_pre115
; get_pos end address is: 32 (R8)
L_at_engine__parse_pre89:
;at_engine.c,406 :: 		get_pos = _cnt;
; get_pos start address is: 8 (R2)
UXTB	R2, R0
; get_pos end address is: 8 (R2)
UXTB	R8, R2
;at_engine.c,405 :: 		if( ( tmp_cmd[ _cnt ] == '?' ) && !get_pos )
IT	AL
BAL	L_at_engine__parse_pre97
L_at_engine__parse_pre114:
L_at_engine__parse_pre97:
; get_pos start address is: 32 (R8)
; get_pos end address is: 32 (R8)
IT	AL
BAL	L_at_engine__parse_pre96
L_at_engine__parse_pre115:
L_at_engine__parse_pre96:
;at_engine.c,408 :: 		if( ( ( ( tmp_cmd[ _cnt ] == '\r' )  ||
; get_pos start address is: 32 (R8)
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
;at_engine.c,409 :: 		( tmp_cmd[ _cnt ] == '\n' )  ||
CMP	R2, #13
IT	EQ
BEQ	L_at_engine__parse_pre100
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
CMP	R2, #10
IT	EQ
BEQ	L_at_engine__parse_pre99
;at_engine.c,410 :: 		( tmp_cmd[ _cnt ] == ':' ) ) && !end_pos ) && start_pos )
ADD	R2, SP, #8
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
CMP	R2, #58
IT	EQ
BEQ	L_at_engine__parse_pre98
UXTB	R2, R3
IT	AL
BAL	L_at_engine__parse_pre33
;at_engine.c,409 :: 		( tmp_cmd[ _cnt ] == '\n' )  ||
L_at_engine__parse_pre100:
L_at_engine__parse_pre99:
;at_engine.c,410 :: 		( tmp_cmd[ _cnt ] == ':' ) ) && !end_pos ) && start_pos )
L_at_engine__parse_pre98:
CMP	R3, #0
IT	NE
BNE	L_at_engine__parse_pre116
L_at_engine__parse_pre87:
CMP	R1, #0
IT	EQ
BEQ	L_at_engine__parse_pre117
; end_pos end address is: 12 (R3)
L_at_engine__parse_pre86:
;at_engine.c,411 :: 		end_pos = _cnt;
; end_pos start address is: 8 (R2)
UXTB	R2, R0
; end_pos end address is: 8 (R2)
L_at_engine__parse_pre33:
;at_engine.c,410 :: 		( tmp_cmd[ _cnt ] == ':' ) ) && !end_pos ) && start_pos )
; end_pos start address is: 8 (R2)
UXTB	R3, R2
; end_pos end address is: 8 (R2)
IT	AL
BAL	L_at_engine__parse_pre102
L_at_engine__parse_pre116:
L_at_engine__parse_pre102:
; end_pos start address is: 12 (R3)
; end_pos end address is: 12 (R3)
IT	AL
BAL	L_at_engine__parse_pre101
L_at_engine__parse_pre117:
L_at_engine__parse_pre101:
;at_engine.c,385 :: 		for( _cnt = 0; _cnt < AT_HEADER_SIZE_MAX; _cnt++ )
; end_pos start address is: 12 (R3)
ADDS	R0, R0, #1
UXTB	R0, R0
;at_engine.c,412 :: 		}
; start_pos end address is: 4 (R1)
; end_pos end address is: 12 (R3)
; _cnt end address is: 0 (R0)
UXTB	R10, R1
IT	AL
BAL	L_at_engine__parse_pre13
L_at_engine__parse_pre118:
;at_engine.c,385 :: 		for( _cnt = 0; _cnt < AT_HEADER_SIZE_MAX; _cnt++ )
UXTB	R0, R3
;at_engine.c,412 :: 		}
L_at_engine__parse_pre14:
;at_engine.c,414 :: 		if( !set_pos && !get_pos )
; end_pos start address is: 0 (R0)
; start_pos start address is: 40 (R10)
CMP	R9, #0
IT	NE
BNE	L_at_engine__parse_pre104
CMP	R8, #0
IT	NE
BNE	L_at_engine__parse_pre103
; set_pos end address is: 36 (R9)
; get_pos end address is: 32 (R8)
L_at_engine__parse_pre85:
;at_engine.c,416 :: 		strncpy( clean_out, &tmp_cmd[ start_pos ], end_pos - start_pos );
SUB	R3, R0, R10, LSL #0
; end_pos end address is: 0 (R0)
ADD	R2, SP, #8
ADD	R2, R2, R10, LSL #0
; start_pos end address is: 40 (R10)
MOV	R1, R2
SXTH	R2, R3
MOV	R0, R7
; clean_out end address is: 28 (R7)
BL	_strncpy+0
;at_engine.c,417 :: 		return AT_CMD_EXEC;
MOVS	R0, #4
IT	AL
BAL	L_end__parse_pre
;at_engine.c,414 :: 		if( !set_pos && !get_pos )
L_at_engine__parse_pre104:
; get_pos start address is: 32 (R8)
; set_pos start address is: 36 (R9)
; clean_out start address is: 28 (R7)
; start_pos start address is: 40 (R10)
L_at_engine__parse_pre103:
;at_engine.c,419 :: 		} else if( !set_pos && get_pos ) {
CMP	R9, #0
IT	NE
BNE	L_at_engine__parse_pre106
CMP	R8, #0
IT	EQ
BEQ	L_at_engine__parse_pre105
; set_pos end address is: 36 (R9)
L_at_engine__parse_pre84:
;at_engine.c,421 :: 		strncpy( clean_out, &tmp_cmd[ start_pos ], get_pos - start_pos );
SUB	R3, R8, R10, LSL #0
; get_pos end address is: 32 (R8)
ADD	R2, SP, #8
ADD	R2, R2, R10, LSL #0
; start_pos end address is: 40 (R10)
MOV	R1, R2
SXTH	R2, R3
MOV	R0, R7
; clean_out end address is: 28 (R7)
BL	_strncpy+0
;at_engine.c,422 :: 		return AT_CMD_TEST;
MOVS	R0, #3
IT	AL
BAL	L_end__parse_pre
;at_engine.c,419 :: 		} else if( !set_pos && get_pos ) {
L_at_engine__parse_pre106:
; get_pos start address is: 32 (R8)
; set_pos start address is: 36 (R9)
; clean_out start address is: 28 (R7)
; start_pos start address is: 40 (R10)
L_at_engine__parse_pre105:
;at_engine.c,424 :: 		} else if( set_pos && !get_pos ) {
CMP	R9, #0
IT	EQ
BEQ	L_at_engine__parse_pre108
CMP	R8, #0
IT	NE
BNE	L_at_engine__parse_pre107
; get_pos end address is: 32 (R8)
L_at_engine__parse_pre83:
;at_engine.c,426 :: 		strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
SUB	R3, R9, R10, LSL #0
; set_pos end address is: 36 (R9)
ADD	R2, SP, #8
ADD	R2, R2, R10, LSL #0
; start_pos end address is: 40 (R10)
MOV	R1, R2
SXTH	R2, R3
MOV	R0, R7
; clean_out end address is: 28 (R7)
BL	_strncpy+0
;at_engine.c,427 :: 		return AT_CMD_SET;
MOVS	R0, #2
IT	AL
BAL	L_end__parse_pre
;at_engine.c,424 :: 		} else if( set_pos && !get_pos ) {
L_at_engine__parse_pre108:
; get_pos start address is: 32 (R8)
; set_pos start address is: 36 (R9)
; clean_out start address is: 28 (R7)
; start_pos start address is: 40 (R10)
L_at_engine__parse_pre107:
;at_engine.c,429 :: 		} else if( set_pos == get_pos - 1 ) {
SUB	R2, R8, #1
SXTH	R2, R2
; get_pos end address is: 32 (R8)
CMP	R9, R2
IT	NE
BNE	L_at_engine__parse_pre46
;at_engine.c,431 :: 		strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
SUB	R3, R9, R10, LSL #0
; set_pos end address is: 36 (R9)
ADD	R2, SP, #8
ADD	R2, R2, R10, LSL #0
; start_pos end address is: 40 (R10)
MOV	R1, R2
SXTH	R2, R3
MOV	R0, R7
; clean_out end address is: 28 (R7)
BL	_strncpy+0
;at_engine.c,432 :: 		return AT_CMD_GET;
MOVS	R0, #1
IT	AL
BAL	L_end__parse_pre
;at_engine.c,433 :: 		}
L_at_engine__parse_pre46:
;at_engine.c,435 :: 		return AT_CMD_UNKNOWN;
MOVS	R0, #0
;at_engine.c,436 :: 		}
L_end__parse_pre:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of at_engine__parse_pre
__parse_exe:
;at_engine.c,438 :: 		void _parse_exe( char *input, at_cmd_cb *cb, uint32_t *timeout )
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
; input start address is: 0 (R0)
SUB	SP, SP, #28
STR	LR, [SP, #0]
; timeout end address is: 8 (R2)
; cb end address is: 4 (R1)
; input end address is: 0 (R0)
; input start address is: 0 (R0)
; cb start address is: 4 (R1)
; timeout start address is: 8 (R2)
;at_engine.c,440 :: 		at_type_t   cmd_type                    = 0;
;at_engine.c,441 :: 		uint16_t    cmd_idx                     = 0;
;at_engine.c,442 :: 		char        cmd_temp[ AT_HEADER_SIZE_MAX ]  = { 0 };
ADD	R11, SP, #12
ADD	R10, R11, #15
MOVW	R12, #lo_addr(?ICS_parse_exe_cmd_temp_L0+0)
MOVT	R12, #hi_addr(?ICS_parse_exe_cmd_temp_L0+0)
BL	___CC2DW+0
;at_engine.c,444 :: 		if( !( cmd_type = _parse_pre( input, cmd_temp ) ) )
ADD	R3, SP, #12
STR	R2, [SP, #4]
STR	R1, [SP, #8]
MOV	R1, R3
; input end address is: 0 (R0)
BL	at_engine__parse_pre+0
LDR	R1, [SP, #8]
LDR	R2, [SP, #4]
; cmd_type start address is: 16 (R4)
UXTB	R4, R0
CMP	R0, #0
IT	NE
BNE	L__parse_exe47
; cmd_type end address is: 16 (R4)
;at_engine.c,446 :: 		*cb = at_cmd_storage[ 0 ].tester;
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+16)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+16)
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,447 :: 		*timeout = at_cmd_storage[ 0 ].timeout;
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+4)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+4)
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,448 :: 		return;
IT	AL
BAL	L_end__parse_exe
;at_engine.c,449 :: 		}
L__parse_exe47:
;at_engine.c,451 :: 		if( !( cmd_idx = _parse_find( cmd_temp ) ) )
; cmd_type start address is: 16 (R4)
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
ADD	R3, SP, #12
STR	R2, [SP, #4]
STR	R1, [SP, #8]
MOV	R0, R3
BL	at_engine__parse_find+0
LDR	R1, [SP, #8]
LDR	R2, [SP, #4]
; cmd_idx start address is: 20 (R5)
UXTH	R5, R0
CMP	R0, #0
IT	NE
BNE	L__parse_exe48
; cmd_type end address is: 16 (R4)
; cmd_idx end address is: 20 (R5)
;at_engine.c,453 :: 		*cb = at_cmd_storage[ 0 ].tester;
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+16)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+16)
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,454 :: 		*timeout = at_cmd_storage[ 0 ].timeout;
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+4)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+4)
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,455 :: 		return;
IT	AL
BAL	L_end__parse_exe
;at_engine.c,456 :: 		}
L__parse_exe48:
;at_engine.c,458 :: 		switch ( cmd_type )
; cmd_idx start address is: 20 (R5)
; cmd_type start address is: 16 (R4)
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
IT	AL
BAL	L__parse_exe49
; cmd_type end address is: 16 (R4)
;at_engine.c,460 :: 		case AT_CMD_SET :
L__parse_exe51:
;at_engine.c,461 :: 		*cb = at_cmd_storage[ cmd_idx ].setter;
MOVS	R3, #24
MUL	R4, R3, R5
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, #12
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,462 :: 		*timeout = at_cmd_storage[ cmd_idx ].timeout;
MOVS	R3, #24
MUL	R4, R3, R5
; cmd_idx end address is: 20 (R5)
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, R3, #4
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,463 :: 		break;
IT	AL
BAL	L__parse_exe50
;at_engine.c,464 :: 		case AT_CMD_GET :
L__parse_exe52:
;at_engine.c,465 :: 		*cb = at_cmd_storage[ cmd_idx ].getter;
; cmd_idx start address is: 20 (R5)
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
MOVS	R3, #24
MUL	R4, R3, R5
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, #8
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,466 :: 		*timeout = at_cmd_storage[ cmd_idx ].timeout;
MOVS	R3, #24
MUL	R4, R3, R5
; cmd_idx end address is: 20 (R5)
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, R3, #4
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,467 :: 		break;
IT	AL
BAL	L__parse_exe50
;at_engine.c,468 :: 		case AT_CMD_TEST :
L__parse_exe53:
;at_engine.c,469 :: 		*cb = at_cmd_storage[ cmd_idx ].tester;
; cmd_idx start address is: 20 (R5)
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
MOVS	R3, #24
MUL	R4, R3, R5
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, #16
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,470 :: 		*timeout = at_cmd_storage[ cmd_idx ].timeout;
MOVS	R3, #24
MUL	R4, R3, R5
; cmd_idx end address is: 20 (R5)
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, R3, #4
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,471 :: 		break;
IT	AL
BAL	L__parse_exe50
;at_engine.c,472 :: 		case AT_CMD_EXEC :
L__parse_exe54:
;at_engine.c,473 :: 		*cb = at_cmd_storage[ cmd_idx ].executer;
; cmd_idx start address is: 20 (R5)
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
MOVS	R3, #24
MUL	R4, R3, R5
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, #20
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,474 :: 		*timeout = at_cmd_storage[ cmd_idx ].timeout;
MOVS	R3, #24
MUL	R4, R3, R5
; cmd_idx end address is: 20 (R5)
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R3, R3, R4
ADDS	R3, R3, #4
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,475 :: 		break;
IT	AL
BAL	L__parse_exe50
;at_engine.c,476 :: 		case AT_CMD_UNKNOWN :
L__parse_exe55:
;at_engine.c,477 :: 		*cb = at_cmd_storage[ 0 ].executer;
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+20)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+20)
LDR	R3, [R3, #0]
STR	R3, [R1, #0]
; cb end address is: 4 (R1)
;at_engine.c,478 :: 		*timeout = at_cmd_storage[ 0 ].timeout;
MOVW	R3, #lo_addr(at_engine_at_cmd_storage+4)
MOVT	R3, #hi_addr(at_engine_at_cmd_storage+4)
LDR	R3, [R3, #0]
STR	R3, [R2, #0]
; timeout end address is: 8 (R2)
;at_engine.c,479 :: 		break;
IT	AL
BAL	L__parse_exe50
;at_engine.c,480 :: 		}
L__parse_exe49:
; cmd_idx start address is: 20 (R5)
; cmd_type start address is: 16 (R4)
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
CMP	R4, #2
IT	EQ
BEQ	L__parse_exe51
CMP	R4, #1
IT	EQ
BEQ	L__parse_exe52
CMP	R4, #3
IT	EQ
BEQ	L__parse_exe53
CMP	R4, #4
IT	EQ
BEQ	L__parse_exe54
; cmd_idx end address is: 20 (R5)
CMP	R4, #0
IT	EQ
BEQ	L__parse_exe55
; cb end address is: 4 (R1)
; timeout end address is: 8 (R2)
; cmd_type end address is: 16 (R4)
L__parse_exe50:
;at_engine.c,481 :: 		return;
;at_engine.c,482 :: 		}
L_end__parse_exe:
LDR	LR, [SP, #0]
ADD	SP, SP, #28
BX	LR
; end of __parse_exe
_at_init:
;at_engine.c,493 :: 		)
; buffer_size start address is: 12 (R3)
; buffer_ptr start address is: 8 (R2)
; default_write start address is: 4 (R1)
; default_callback start address is: 0 (R0)
SUB	SP, SP, #32
STR	LR, [SP, #0]
MOV	R6, R0
; buffer_size end address is: 12 (R3)
; buffer_ptr end address is: 8 (R2)
; default_write end address is: 4 (R1)
; default_callback end address is: 0 (R0)
; default_callback start address is: 24 (R6)
; default_write start address is: 4 (R1)
; buffer_ptr start address is: 8 (R2)
; buffer_size start address is: 12 (R3)
;at_engine.c,497 :: 		cb_default          = default_callback;
MOVW	R4, #lo_addr(at_engine_cb_default+0)
MOVT	R4, #hi_addr(at_engine_cb_default+0)
STR	R6, [R4, #0]
;at_engine.c,498 :: 		write_uart_p        = default_write;
MOVW	R4, #lo_addr(at_engine_write_uart_p+0)
MOVT	R4, #hi_addr(at_engine_write_uart_p+0)
STR	R1, [R4, #0]
; default_write end address is: 4 (R1)
;at_engine.c,499 :: 		AT_CORE_INIT();
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_t_response_l+0)
MOVT	R4, #hi_addr(at_engine_t_response_l+0)
STR	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_t_response_c+0)
MOVT	R4, #hi_addr(at_engine_t_response_c+0)
STR	R5, [R4, #0]
MOVS	R5, #50
MOVW	R4, #lo_addr(at_engine_t_char_l+0)
MOVT	R4, #hi_addr(at_engine_t_char_l+0)
STR	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_t_char_c+0)
MOVT	R4, #hi_addr(at_engine_t_char_c+0)
STR	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_tmp_cnt+0)
MOVT	R4, #hi_addr(at_engine_tmp_cnt+0)
STR	R4, [SP, #28]
STRB	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_t_response_f+0)
MOVT	R4, #hi_addr(at_engine_t_response_f+0)
STRB	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_t_char_f+0)
MOVT	R4, #hi_addr(at_engine_t_char_f+0)
STRB	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_response_f+0)
MOVT	R4, #hi_addr(at_engine_response_f+0)
STRB	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_no_response_f+0)
MOVT	R4, #hi_addr(at_engine_no_response_f+0)
STRB	R5, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_cue_f+0)
MOVT	R4, #hi_addr(at_engine_cue_f+0)
STRB	R5, [R4, #0]
;at_engine.c,500 :: 		AT_BUFFER_INIT( buffer_ptr, buffer_size );
MOVW	R4, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R4, #hi_addr(at_engine_p_rx_buf+0)
STR	R2, [R4, #0]
MOVW	R4, #lo_addr(at_engine_rx_max+0)
MOVT	R4, #hi_addr(at_engine_rx_max+0)
STRH	R3, [R4, #0]
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_rx_idx+0)
MOVT	R4, #hi_addr(at_engine_rx_idx+0)
STRH	R5, [R4, #0]
SXTH	R4, R3
; buffer_size end address is: 12 (R3)
MOVS	R1, #0
MOV	R0, R2
SXTH	R2, R4
; buffer_ptr end address is: 8 (R2)
BL	_memset+0
;at_engine.c,501 :: 		AT_STORAGE_INIT();
MOVS	R5, #0
MOVW	R4, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage_used+0)
STRB	R5, [R4, #0]
MOVS	R5, #0
LDR	R4, [SP, #28]
STRB	R5, [R4, #0]
; default_callback end address is: 24 (R6)
MOV	R7, R6
L_at_init56:
; default_callback start address is: 28 (R7)
MOVW	R4, #lo_addr(at_engine_tmp_cnt+0)
MOVT	R4, #hi_addr(at_engine_tmp_cnt+0)
LDRB	R4, [R4, #0]
CMP	R4, #50
IT	CS
BCS	L_at_init57
MOVW	R6, #lo_addr(at_engine_tmp_cnt+0)
MOVT	R6, #hi_addr(at_engine_tmp_cnt+0)
LDRB	R5, [R6, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R5, R4, R5
MOVS	R4, #0
STR	R4, [R5, #0]
MOV	R4, R6
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
ADDS	R5, R4, #4
MOVS	R4, #0
STR	R4, [R5, #0]
MOV	R4, R6
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
ADDW	R5, R4, #8
MOVS	R4, #0
STR	R4, [R5, #0]
MOV	R4, R6
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
ADDW	R5, R4, #12
MOVS	R4, #0
STR	R4, [R5, #0]
MOV	R4, R6
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
ADDW	R5, R4, #16
MOVS	R4, #0
STR	R4, [R5, #0]
MOV	R4, R6
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
ADDW	R5, R4, #20
MOVS	R4, #0
STR	R4, [R5, #0]
MOV	R4, R6
LDRB	R4, [R4, #0]
ADDS	R4, R4, #1
STRB	R4, [R6, #0]
IT	AL
BAL	L_at_init56
L_at_init57:
;at_engine.c,502 :: 		cmd.hash                                = _parse_hash( "" );
MOVW	R4, #lo_addr(?lstr1_at_engine+0)
MOVT	R4, #hi_addr(?lstr1_at_engine+0)
MOV	R0, R4
BL	at_engine__parse_hash+0
STR	R0, [SP, #4]
;at_engine.c,503 :: 		cmd.timeout                             = AT_DEFAULT_TIMEOUT;
MOVW	R4, #500
STR	R4, [SP, #8]
;at_engine.c,504 :: 		cmd.getter                              = default_callback;
STR	R7, [SP, #12]
;at_engine.c,505 :: 		cmd.setter                              = default_callback;
STR	R7, [SP, #16]
;at_engine.c,506 :: 		cmd.tester                              = default_callback;
STR	R7, [SP, #20]
;at_engine.c,507 :: 		cmd.executer                            = default_callback;
STR	R7, [SP, #24]
; default_callback end address is: 28 (R7)
;at_engine.c,508 :: 		at_cmd_storage[ at_cmd_storage_used ]   = cmd;
MOVW	R4, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage_used+0)
LDRB	R5, [R4, #0]
MOVS	R4, #24
MULS	R5, R4, R5
MOVW	R4, #lo_addr(at_engine_at_cmd_storage+0)
MOVT	R4, #hi_addr(at_engine_at_cmd_storage+0)
ADDS	R4, R4, R5
MOV	R7, #24
MOV	R6, R4
ADD	R5, SP, #4
L_at_init59:
LDRB	R4, [R5, #0]
STRB	R4, [R6, #0]
SUBS	R7, R7, #1
ADDS	R5, R5, #1
ADDS	R6, R6, #1
CMP	R7, #0
IT	NE
BNE	L_at_init59
;at_engine.c,509 :: 		at_cmd_storage_used++;
MOVW	R5, #lo_addr(at_engine_at_cmd_storage_used+0)
MOVT	R5, #hi_addr(at_engine_at_cmd_storage_used+0)
LDRB	R4, [R5, #0]
ADDS	R4, R4, #1
STRB	R4, [R5, #0]
;at_engine.c,510 :: 		}
L_end_at_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #32
BX	LR
; end of _at_init
_at_rx:
;at_engine.c,512 :: 		void at_rx( char rx_input )
; rx_input start address is: 0 (R0)
; rx_input end address is: 0 (R0)
; rx_input start address is: 0 (R0)
;at_engine.c,514 :: 		AT_SET_CUE();
MOVS	R2, #0
MOVW	R1, #lo_addr(at_engine_no_response_f+0)
MOVT	R1, #hi_addr(at_engine_no_response_f+0)
STRB	R2, [R1, #0]
MOVS	R2, #0
MOVW	R1, #lo_addr(at_engine_response_f+0)
MOVT	R1, #hi_addr(at_engine_response_f+0)
STRB	R2, [R1, #0]
MOVS	R2, #1
MOVW	R1, #lo_addr(at_engine_cue_f+0)
MOVT	R1, #hi_addr(at_engine_cue_f+0)
STRB	R2, [R1, #0]
;at_engine.c,515 :: 		AT_RESTART_T();
MOVS	R2, #0
MOVW	R1, #lo_addr(at_engine_t_char_c+0)
MOVT	R1, #hi_addr(at_engine_t_char_c+0)
STR	R2, [R1, #0]
MOVS	R2, #1
MOVW	R1, #lo_addr(at_engine_t_char_f+0)
MOVT	R1, #hi_addr(at_engine_t_char_f+0)
STRB	R2, [R1, #0]
;at_engine.c,516 :: 		*( p_rx_buf + rx_idx++ ) = rx_input;
MOVW	R1, #lo_addr(at_engine_rx_idx+0)
MOVT	R1, #hi_addr(at_engine_rx_idx+0)
LDRH	R2, [R1, #0]
MOVW	R1, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R1, #hi_addr(at_engine_p_rx_buf+0)
LDR	R1, [R1, #0]
ADDS	R1, R1, R2
STRB	R0, [R1, #0]
; rx_input end address is: 0 (R0)
MOVW	R1, #lo_addr(at_engine_rx_idx+0)
MOVT	R1, #hi_addr(at_engine_rx_idx+0)
LDRH	R1, [R1, #0]
ADDS	R2, R1, #1
MOVW	R1, #lo_addr(at_engine_rx_idx+0)
MOVT	R1, #hi_addr(at_engine_rx_idx+0)
STRH	R2, [R1, #0]
;at_engine.c,517 :: 		}
L_end_at_rx:
BX	LR
; end of _at_rx
_at_tick:
;at_engine.c,519 :: 		void at_tick( void )
;at_engine.c,521 :: 		if( t_response_f )
MOVW	R0, #lo_addr(at_engine_t_response_f+0)
MOVT	R0, #hi_addr(at_engine_t_response_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_at_tick60
;at_engine.c,522 :: 		if( t_response_c++ > t_response_l )
MOVW	R0, #lo_addr(at_engine_t_response_c+0)
MOVT	R0, #hi_addr(at_engine_t_response_c+0)
LDR	R2, [R0, #0]
MOVW	R0, #lo_addr(at_engine_t_response_c+0)
MOVT	R0, #hi_addr(at_engine_t_response_c+0)
LDR	R0, [R0, #0]
ADDS	R1, R0, #1
MOVW	R0, #lo_addr(at_engine_t_response_c+0)
MOVT	R0, #hi_addr(at_engine_t_response_c+0)
STR	R1, [R0, #0]
MOVW	R0, #lo_addr(at_engine_t_response_l+0)
MOVT	R0, #hi_addr(at_engine_t_response_l+0)
LDR	R0, [R0, #0]
CMP	R2, R0
IT	LS
BLS	L_at_tick61
;at_engine.c,524 :: 		t_response_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_response_f+0)
MOVT	R0, #hi_addr(at_engine_t_response_f+0)
STRB	R1, [R0, #0]
;at_engine.c,525 :: 		t_response_c = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_response_c+0)
MOVT	R0, #hi_addr(at_engine_t_response_c+0)
STR	R1, [R0, #0]
;at_engine.c,526 :: 		*( p_rx_buf + rx_idx ) = 0;
MOVW	R0, #lo_addr(at_engine_rx_idx+0)
MOVT	R0, #hi_addr(at_engine_rx_idx+0)
LDRH	R1, [R0, #0]
MOVW	R0, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R0, #hi_addr(at_engine_p_rx_buf+0)
LDR	R0, [R0, #0]
ADDS	R1, R0, R1
MOVS	R0, #0
STRB	R0, [R1, #0]
;at_engine.c,527 :: 		no_response_f = true;
MOVS	R1, #1
MOVW	R0, #lo_addr(at_engine_no_response_f+0)
MOVT	R0, #hi_addr(at_engine_no_response_f+0)
STRB	R1, [R0, #0]
;at_engine.c,528 :: 		}
L_at_tick61:
L_at_tick60:
;at_engine.c,530 :: 		if( t_char_f )
MOVW	R0, #lo_addr(at_engine_t_char_f+0)
MOVT	R0, #hi_addr(at_engine_t_char_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_at_tick62
;at_engine.c,531 :: 		if( t_char_c++ > t_char_l )
MOVW	R0, #lo_addr(at_engine_t_char_c+0)
MOVT	R0, #hi_addr(at_engine_t_char_c+0)
LDR	R2, [R0, #0]
MOVW	R0, #lo_addr(at_engine_t_char_c+0)
MOVT	R0, #hi_addr(at_engine_t_char_c+0)
LDR	R0, [R0, #0]
ADDS	R1, R0, #1
MOVW	R0, #lo_addr(at_engine_t_char_c+0)
MOVT	R0, #hi_addr(at_engine_t_char_c+0)
STR	R1, [R0, #0]
MOVW	R0, #lo_addr(at_engine_t_char_l+0)
MOVT	R0, #hi_addr(at_engine_t_char_l+0)
LDR	R0, [R0, #0]
CMP	R2, R0
IT	LS
BLS	L_at_tick63
;at_engine.c,533 :: 		t_char_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_char_f+0)
MOVT	R0, #hi_addr(at_engine_t_char_f+0)
STRB	R1, [R0, #0]
;at_engine.c,534 :: 		t_char_c = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_char_c+0)
MOVT	R0, #hi_addr(at_engine_t_char_c+0)
STR	R1, [R0, #0]
;at_engine.c,535 :: 		*( p_rx_buf + rx_idx ) = 0;
MOVW	R0, #lo_addr(at_engine_rx_idx+0)
MOVT	R0, #hi_addr(at_engine_rx_idx+0)
LDRH	R1, [R0, #0]
MOVW	R0, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R0, #hi_addr(at_engine_p_rx_buf+0)
LDR	R0, [R0, #0]
ADDS	R1, R0, R1
MOVS	R0, #0
STRB	R0, [R1, #0]
;at_engine.c,536 :: 		response_f = true;
MOVS	R1, #1
MOVW	R0, #lo_addr(at_engine_response_f+0)
MOVT	R0, #hi_addr(at_engine_response_f+0)
STRB	R1, [R0, #0]
;at_engine.c,537 :: 		}
L_at_tick63:
L_at_tick62:
;at_engine.c,538 :: 		}
L_end_at_tick:
BX	LR
; end of _at_tick
_at_cmd_save:
;at_engine.c,542 :: 		at_cmd_cb tester, at_cmd_cb executer )
; setter start address is: 12 (R3)
; getter start address is: 8 (R2)
; timeout start address is: 4 (R1)
; cmd start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
STR	R3, [SP, #4]
MOV	R3, R2
MOV	R2, R1
LDR	R1, [SP, #4]
; setter end address is: 12 (R3)
; getter end address is: 8 (R2)
; timeout end address is: 4 (R1)
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; timeout start address is: 8 (R2)
; getter start address is: 12 (R3)
; setter start address is: 4 (R1)
; tester start address is: 24 (R6)
LDR	R6, [SP, #8]
; executer start address is: 20 (R5)
LDR	R5, [SP, #12]
;at_engine.c,544 :: 		if( !setter )   setter = cb_default;
CMP	R1, #0
IT	NE
BNE	L__at_cmd_save119
; setter end address is: 4 (R1)
MOVW	R4, #lo_addr(at_engine_cb_default+0)
MOVT	R4, #hi_addr(at_engine_cb_default+0)
; setter start address is: 4 (R1)
LDR	R1, [R4, #0]
; setter end address is: 4 (R1)
IT	AL
BAL	L_at_cmd_save64
L__at_cmd_save119:
L_at_cmd_save64:
;at_engine.c,545 :: 		if( !getter )   getter = cb_default;
; setter start address is: 4 (R1)
CMP	R3, #0
IT	NE
BNE	L__at_cmd_save120
; getter end address is: 12 (R3)
MOVW	R4, #lo_addr(at_engine_cb_default+0)
MOVT	R4, #hi_addr(at_engine_cb_default+0)
; getter start address is: 12 (R3)
LDR	R3, [R4, #0]
; getter end address is: 12 (R3)
IT	AL
BAL	L_at_cmd_save65
L__at_cmd_save120:
L_at_cmd_save65:
;at_engine.c,546 :: 		if( !tester )   tester = cb_default;
; getter start address is: 12 (R3)
CMP	R6, #0
IT	NE
BNE	L__at_cmd_save121
; tester end address is: 24 (R6)
MOVW	R4, #lo_addr(at_engine_cb_default+0)
MOVT	R4, #hi_addr(at_engine_cb_default+0)
; tester start address is: 24 (R6)
LDR	R6, [R4, #0]
; tester end address is: 24 (R6)
IT	AL
BAL	L_at_cmd_save66
L__at_cmd_save121:
L_at_cmd_save66:
;at_engine.c,547 :: 		if( !executer ) executer = cb_default;
; tester start address is: 24 (R6)
CMP	R5, #0
IT	NE
BNE	L__at_cmd_save122
; executer end address is: 20 (R5)
MOVW	R4, #lo_addr(at_engine_cb_default+0)
MOVT	R4, #hi_addr(at_engine_cb_default+0)
; executer start address is: 20 (R5)
LDR	R5, [R4, #0]
; executer end address is: 20 (R5)
MOV	R4, R5
IT	AL
BAL	L_at_cmd_save67
L__at_cmd_save122:
MOV	R4, R5
L_at_cmd_save67:
;at_engine.c,548 :: 		if( !timeout )  timeout = AT_DEFAULT_TIMEOUT;
; executer start address is: 16 (R4)
CMP	R2, #0
IT	NE
BNE	L__at_cmd_save123
MOVW	R2, #500
; timeout end address is: 8 (R2)
IT	AL
BAL	L_at_cmd_save68
L__at_cmd_save123:
L_at_cmd_save68:
;at_engine.c,549 :: 		_parse_save( cmd, timeout, getter, setter, tester, executer );
; timeout start address is: 8 (R2)
MOV	R5, R4
; executer end address is: 16 (R4)
MOV	R4, R6
; tester end address is: 24 (R6)
STR	R2, [SP, #4]
; setter end address is: 4 (R1)
MOV	R2, R3
; getter end address is: 12 (R3)
MOV	R3, R1
; timeout end address is: 8 (R2)
LDR	R1, [SP, #4]
; cmd end address is: 0 (R0)
PUSH	(R5)
PUSH	(R4)
BL	at_engine__parse_save+0
ADD	SP, SP, #8
;at_engine.c,550 :: 		}
L_end_at_cmd_save:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _at_cmd_save
_at_cmd_single:
;at_engine.c,552 :: 		void at_cmd_single( char *cmd )
; cmd start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
;at_engine.c,554 :: 		char* tmp = cmd;
STR	R0, [SP, #4]
; cmd end address is: 0 (R0)
;at_engine.c,556 :: 		AT_WAIT_RESPONSE();
L_at_cmd_single69:
MOVW	R1, #lo_addr(at_engine_cue_f+0)
MOVT	R1, #hi_addr(at_engine_cue_f+0)
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	EQ
BEQ	L_at_cmd_single70
BL	_at_process+0
IT	AL
BAL	L_at_cmd_single69
L_at_cmd_single70:
;at_engine.c,557 :: 		_parse_exe( tmp, &tmp_cb, &tmp_timer );
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
MOVW	R1, #lo_addr(at_engine_tmp_cb+0)
MOVT	R1, #hi_addr(at_engine_tmp_cb+0)
LDR	R0, [SP, #4]
BL	__parse_exe+0
;at_engine.c,558 :: 		_tx( tmp, AT_TERMINATE );
MOVS	R1, #13
LDR	R0, [SP, #4]
BL	at_engine__tx+0
;at_engine.c,559 :: 		AT_SET_CUE();
MOVS	R2, #0
MOVW	R1, #lo_addr(at_engine_no_response_f+0)
MOVT	R1, #hi_addr(at_engine_no_response_f+0)
STRB	R2, [R1, #0]
MOVS	R2, #0
MOVW	R1, #lo_addr(at_engine_response_f+0)
MOVT	R1, #hi_addr(at_engine_response_f+0)
STRB	R2, [R1, #0]
MOVS	R2, #1
MOVW	R1, #lo_addr(at_engine_cue_f+0)
MOVT	R1, #hi_addr(at_engine_cue_f+0)
STRB	R2, [R1, #0]
;at_engine.c,560 :: 		AT_LOAD_TIMER( tmp_timer );
MOVW	R1, #lo_addr(at_engine_tmp_timer+0)
MOVT	R1, #hi_addr(at_engine_tmp_timer+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(at_engine_t_response_l+0)
MOVT	R1, #hi_addr(at_engine_t_response_l+0)
STR	R2, [R1, #0]
MOVS	R2, #0
MOVW	R1, #lo_addr(at_engine_t_response_c+0)
MOVT	R1, #hi_addr(at_engine_t_response_c+0)
STR	R2, [R1, #0]
MOVS	R2, #1
MOVW	R1, #lo_addr(at_engine_t_response_f+0)
MOVT	R1, #hi_addr(at_engine_t_response_f+0)
STRB	R2, [R1, #0]
;at_engine.c,561 :: 		}
L_end_at_cmd_single:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _at_cmd_single
_at_cmd_double:
;at_engine.c,563 :: 		void at_cmd_double( char *cmd, char *arg_1 )
; arg_1 start address is: 4 (R1)
; cmd start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; arg_1 end address is: 4 (R1)
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; arg_1 start address is: 4 (R1)
;at_engine.c,565 :: 		char *tmp       = cmd;
STR	R0, [SP, #4]
; cmd end address is: 0 (R0)
;at_engine.c,566 :: 		char *tmp_a1    = arg_1;
STR	R1, [SP, #8]
; arg_1 end address is: 4 (R1)
;at_engine.c,568 :: 		AT_WAIT_RESPONSE();
L_at_cmd_double71:
MOVW	R2, #lo_addr(at_engine_cue_f+0)
MOVT	R2, #hi_addr(at_engine_cue_f+0)
LDRB	R2, [R2, #0]
CMP	R2, #0
IT	EQ
BEQ	L_at_cmd_double72
BL	_at_process+0
IT	AL
BAL	L_at_cmd_double71
L_at_cmd_double72:
;at_engine.c,569 :: 		_parse_exe( tmp, &tmp_cb, &tmp_timer );
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
MOVW	R1, #lo_addr(at_engine_tmp_cb+0)
MOVT	R1, #hi_addr(at_engine_tmp_cb+0)
LDR	R0, [SP, #4]
BL	__parse_exe+0
;at_engine.c,570 :: 		_tx( tmp, AT_TERMINATE );
MOVS	R1, #13
LDR	R0, [SP, #4]
BL	at_engine__tx+0
;at_engine.c,571 :: 		AT_SET_CUE();
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_no_response_f+0)
MOVT	R2, #hi_addr(at_engine_no_response_f+0)
STRB	R3, [R2, #0]
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_response_f+0)
MOVT	R2, #hi_addr(at_engine_response_f+0)
STRB	R3, [R2, #0]
MOVS	R3, #1
MOVW	R2, #lo_addr(at_engine_cue_f+0)
MOVT	R2, #hi_addr(at_engine_cue_f+0)
STRB	R3, [R2, #0]
;at_engine.c,572 :: 		AT_LOAD_TIMER( tmp_timer );
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
LDR	R3, [R2, #0]
MOVW	R2, #lo_addr(at_engine_t_response_l+0)
MOVT	R2, #hi_addr(at_engine_t_response_l+0)
STR	R3, [R2, #0]
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_t_response_c+0)
MOVT	R2, #hi_addr(at_engine_t_response_c+0)
STR	R3, [R2, #0]
MOVS	R3, #1
MOVW	R2, #lo_addr(at_engine_t_response_f+0)
MOVT	R2, #hi_addr(at_engine_t_response_f+0)
STRB	R3, [R2, #0]
;at_engine.c,573 :: 		AT_WAIT_RESPONSE();
L_at_cmd_double73:
MOVW	R2, #lo_addr(at_engine_cue_f+0)
MOVT	R2, #hi_addr(at_engine_cue_f+0)
LDRB	R2, [R2, #0]
CMP	R2, #0
IT	EQ
BEQ	L_at_cmd_double74
BL	_at_process+0
IT	AL
BAL	L_at_cmd_double73
L_at_cmd_double74:
;at_engine.c,574 :: 		AT_STOP_TIMER();
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_t_response_f+0)
MOVT	R2, #hi_addr(at_engine_t_response_f+0)
STRB	R3, [R2, #0]
;at_engine.c,575 :: 		_tx( tmp_a1, AT_TERMINATE_ADD );
MOVS	R1, #26
LDR	R0, [SP, #8]
BL	at_engine__tx+0
;at_engine.c,576 :: 		AT_SET_CUE();
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_no_response_f+0)
MOVT	R2, #hi_addr(at_engine_no_response_f+0)
STRB	R3, [R2, #0]
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_response_f+0)
MOVT	R2, #hi_addr(at_engine_response_f+0)
STRB	R3, [R2, #0]
MOVS	R3, #1
MOVW	R2, #lo_addr(at_engine_cue_f+0)
MOVT	R2, #hi_addr(at_engine_cue_f+0)
STRB	R3, [R2, #0]
;at_engine.c,577 :: 		AT_LOAD_TIMER( tmp_timer );
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
LDR	R3, [R2, #0]
MOVW	R2, #lo_addr(at_engine_t_response_l+0)
MOVT	R2, #hi_addr(at_engine_t_response_l+0)
STR	R3, [R2, #0]
MOVS	R3, #0
MOVW	R2, #lo_addr(at_engine_t_response_c+0)
MOVT	R2, #hi_addr(at_engine_t_response_c+0)
STR	R3, [R2, #0]
MOVS	R3, #1
MOVW	R2, #lo_addr(at_engine_t_response_f+0)
MOVT	R2, #hi_addr(at_engine_t_response_f+0)
STRB	R3, [R2, #0]
;at_engine.c,578 :: 		}
L_end_at_cmd_double:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _at_cmd_double
_at_cmd_triple:
;at_engine.c,580 :: 		void at_cmd_triple( char *cmd, char *arg_1, char *arg_2 )
; arg_2 start address is: 8 (R2)
; arg_1 start address is: 4 (R1)
; cmd start address is: 0 (R0)
SUB	SP, SP, #16
STR	LR, [SP, #0]
; arg_2 end address is: 8 (R2)
; arg_1 end address is: 4 (R1)
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; arg_1 start address is: 4 (R1)
; arg_2 start address is: 8 (R2)
;at_engine.c,582 :: 		char *tmp       = cmd;
STR	R0, [SP, #4]
; cmd end address is: 0 (R0)
;at_engine.c,583 :: 		char *tmp_a1    = arg_1;
STR	R1, [SP, #8]
; arg_1 end address is: 4 (R1)
;at_engine.c,584 :: 		char *tmp_a2    = arg_2;
STR	R2, [SP, #12]
; arg_2 end address is: 8 (R2)
;at_engine.c,586 :: 		AT_WAIT_RESPONSE();
L_at_cmd_triple75:
MOVW	R3, #lo_addr(at_engine_cue_f+0)
MOVT	R3, #hi_addr(at_engine_cue_f+0)
LDRB	R3, [R3, #0]
CMP	R3, #0
IT	EQ
BEQ	L_at_cmd_triple76
BL	_at_process+0
IT	AL
BAL	L_at_cmd_triple75
L_at_cmd_triple76:
;at_engine.c,587 :: 		_parse_exe( tmp, &tmp_cb, &tmp_timer );
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
MOVW	R1, #lo_addr(at_engine_tmp_cb+0)
MOVT	R1, #hi_addr(at_engine_tmp_cb+0)
LDR	R0, [SP, #4]
BL	__parse_exe+0
;at_engine.c,588 :: 		_tx( tmp, AT_TERMINATE );
MOVS	R1, #13
LDR	R0, [SP, #4]
BL	at_engine__tx+0
;at_engine.c,589 :: 		AT_SET_CUE();
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_no_response_f+0)
MOVT	R3, #hi_addr(at_engine_no_response_f+0)
STRB	R4, [R3, #0]
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_response_f+0)
MOVT	R3, #hi_addr(at_engine_response_f+0)
STRB	R4, [R3, #0]
MOVS	R4, #1
MOVW	R3, #lo_addr(at_engine_cue_f+0)
MOVT	R3, #hi_addr(at_engine_cue_f+0)
STRB	R4, [R3, #0]
;at_engine.c,590 :: 		AT_LOAD_TIMER( tmp_timer );
MOVW	R3, #lo_addr(at_engine_tmp_timer+0)
MOVT	R3, #hi_addr(at_engine_tmp_timer+0)
LDR	R4, [R3, #0]
MOVW	R3, #lo_addr(at_engine_t_response_l+0)
MOVT	R3, #hi_addr(at_engine_t_response_l+0)
STR	R4, [R3, #0]
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_t_response_c+0)
MOVT	R3, #hi_addr(at_engine_t_response_c+0)
STR	R4, [R3, #0]
MOVS	R4, #1
MOVW	R3, #lo_addr(at_engine_t_response_f+0)
MOVT	R3, #hi_addr(at_engine_t_response_f+0)
STRB	R4, [R3, #0]
;at_engine.c,591 :: 		AT_WAIT_RESPONSE();
L_at_cmd_triple77:
MOVW	R3, #lo_addr(at_engine_cue_f+0)
MOVT	R3, #hi_addr(at_engine_cue_f+0)
LDRB	R3, [R3, #0]
CMP	R3, #0
IT	EQ
BEQ	L_at_cmd_triple78
BL	_at_process+0
IT	AL
BAL	L_at_cmd_triple77
L_at_cmd_triple78:
;at_engine.c,592 :: 		AT_STOP_TIMER();
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_t_response_f+0)
MOVT	R3, #hi_addr(at_engine_t_response_f+0)
STRB	R4, [R3, #0]
;at_engine.c,593 :: 		_tx( tmp_a1, AT_TERMINATE_ADD );
MOVS	R1, #26
LDR	R0, [SP, #8]
BL	at_engine__tx+0
;at_engine.c,594 :: 		AT_SET_CUE();
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_no_response_f+0)
MOVT	R3, #hi_addr(at_engine_no_response_f+0)
STRB	R4, [R3, #0]
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_response_f+0)
MOVT	R3, #hi_addr(at_engine_response_f+0)
STRB	R4, [R3, #0]
MOVS	R4, #1
MOVW	R3, #lo_addr(at_engine_cue_f+0)
MOVT	R3, #hi_addr(at_engine_cue_f+0)
STRB	R4, [R3, #0]
;at_engine.c,595 :: 		AT_LOAD_TIMER( tmp_timer );
MOVW	R3, #lo_addr(at_engine_tmp_timer+0)
MOVT	R3, #hi_addr(at_engine_tmp_timer+0)
LDR	R4, [R3, #0]
MOVW	R3, #lo_addr(at_engine_t_response_l+0)
MOVT	R3, #hi_addr(at_engine_t_response_l+0)
STR	R4, [R3, #0]
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_t_response_c+0)
MOVT	R3, #hi_addr(at_engine_t_response_c+0)
STR	R4, [R3, #0]
MOVS	R4, #1
MOVW	R3, #lo_addr(at_engine_t_response_f+0)
MOVT	R3, #hi_addr(at_engine_t_response_f+0)
STRB	R4, [R3, #0]
;at_engine.c,596 :: 		AT_WAIT_RESPONSE();
L_at_cmd_triple79:
MOVW	R3, #lo_addr(at_engine_cue_f+0)
MOVT	R3, #hi_addr(at_engine_cue_f+0)
LDRB	R3, [R3, #0]
CMP	R3, #0
IT	EQ
BEQ	L_at_cmd_triple80
BL	_at_process+0
IT	AL
BAL	L_at_cmd_triple79
L_at_cmd_triple80:
;at_engine.c,597 :: 		AT_STOP_TIMER();
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_t_response_f+0)
MOVT	R3, #hi_addr(at_engine_t_response_f+0)
STRB	R4, [R3, #0]
;at_engine.c,598 :: 		_tx( tmp_a2, AT_TERMINATE_ADD );
MOVS	R1, #26
LDR	R0, [SP, #12]
BL	at_engine__tx+0
;at_engine.c,599 :: 		AT_SET_CUE();
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_no_response_f+0)
MOVT	R3, #hi_addr(at_engine_no_response_f+0)
STRB	R4, [R3, #0]
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_response_f+0)
MOVT	R3, #hi_addr(at_engine_response_f+0)
STRB	R4, [R3, #0]
MOVS	R4, #1
MOVW	R3, #lo_addr(at_engine_cue_f+0)
MOVT	R3, #hi_addr(at_engine_cue_f+0)
STRB	R4, [R3, #0]
;at_engine.c,600 :: 		AT_LOAD_TIMER( tmp_timer );
MOVW	R3, #lo_addr(at_engine_tmp_timer+0)
MOVT	R3, #hi_addr(at_engine_tmp_timer+0)
LDR	R4, [R3, #0]
MOVW	R3, #lo_addr(at_engine_t_response_l+0)
MOVT	R3, #hi_addr(at_engine_t_response_l+0)
STR	R4, [R3, #0]
MOVS	R4, #0
MOVW	R3, #lo_addr(at_engine_t_response_c+0)
MOVT	R3, #hi_addr(at_engine_t_response_c+0)
STR	R4, [R3, #0]
MOVS	R4, #1
MOVW	R3, #lo_addr(at_engine_t_response_f+0)
MOVT	R3, #hi_addr(at_engine_t_response_f+0)
STRB	R4, [R3, #0]
;at_engine.c,601 :: 		}
L_end_at_cmd_triple:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _at_cmd_triple
_at_process:
;at_engine.c,603 :: 		void at_process( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;at_engine.c,611 :: 		if( response_f )
MOVW	R0, #lo_addr(at_engine_response_f+0)
MOVT	R0, #hi_addr(at_engine_response_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_at_process81
;at_engine.c,618 :: 		AT_STOP_T();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_char_f+0)
MOVT	R0, #hi_addr(at_engine_t_char_f+0)
STRB	R1, [R0, #0]
;at_engine.c,619 :: 		AT_STOP_TIMER();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_response_f+0)
MOVT	R0, #hi_addr(at_engine_t_response_f+0)
STRB	R1, [R0, #0]
;at_engine.c,620 :: 		_parse_exe( p_rx_buf, &cb, &tmp_timer );
MOVW	R0, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R0, #hi_addr(at_engine_p_rx_buf+0)
STR	R0, [SP, #4]
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
MOVW	R1, #lo_addr(at_engine_cb+0)
MOVT	R1, #hi_addr(at_engine_cb+0)
BL	__parse_exe+0
;at_engine.c,621 :: 		cb( p_rx_buf );
MOVW	R0, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R0, #hi_addr(at_engine_p_rx_buf+0)
LDR	R4, [R0, #0]
MOV	R0, R4
MOVW	R4, #lo_addr(at_engine_cb+0)
MOVT	R4, #hi_addr(at_engine_cb+0)
LDR	R4, [R4, #0]
BLX	R4
;at_engine.c,622 :: 		AT_BUFFER_RESET();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_rx_idx+0)
MOVT	R0, #hi_addr(at_engine_rx_idx+0)
STRH	R1, [R0, #0]
MOVS	R1, #0
LDR	R0, [SP, #4]
LDR	R0, [R0, #0]
STRB	R1, [R0, #0]
;at_engine.c,623 :: 		AT_RESET_CUE();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_no_response_f+0)
MOVT	R0, #hi_addr(at_engine_no_response_f+0)
STRB	R1, [R0, #0]
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_response_f+0)
MOVT	R0, #hi_addr(at_engine_response_f+0)
STRB	R1, [R0, #0]
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_cue_f+0)
MOVT	R0, #hi_addr(at_engine_cue_f+0)
STRB	R1, [R0, #0]
;at_engine.c,624 :: 		}
L_at_process81:
;at_engine.c,626 :: 		if( no_response_f )
MOVW	R0, #lo_addr(at_engine_no_response_f+0)
MOVT	R0, #hi_addr(at_engine_no_response_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_at_process82
;at_engine.c,633 :: 		AT_STOP_T();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_char_f+0)
MOVT	R0, #hi_addr(at_engine_t_char_f+0)
STRB	R1, [R0, #0]
;at_engine.c,634 :: 		AT_STOP_TIMER();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_t_response_f+0)
MOVT	R0, #hi_addr(at_engine_t_response_f+0)
STRB	R1, [R0, #0]
;at_engine.c,635 :: 		_parse_exe( p_rx_buf, &cb, &tmp_timer );
MOVW	R0, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R0, #hi_addr(at_engine_p_rx_buf+0)
STR	R0, [SP, #4]
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(at_engine_tmp_timer+0)
MOVT	R2, #hi_addr(at_engine_tmp_timer+0)
MOVW	R1, #lo_addr(at_engine_cb+0)
MOVT	R1, #hi_addr(at_engine_cb+0)
BL	__parse_exe+0
;at_engine.c,636 :: 		cb( p_rx_buf );
MOVW	R0, #lo_addr(at_engine_p_rx_buf+0)
MOVT	R0, #hi_addr(at_engine_p_rx_buf+0)
LDR	R4, [R0, #0]
MOV	R0, R4
MOVW	R4, #lo_addr(at_engine_cb+0)
MOVT	R4, #hi_addr(at_engine_cb+0)
LDR	R4, [R4, #0]
BLX	R4
;at_engine.c,637 :: 		AT_BUFFER_RESET();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_rx_idx+0)
MOVT	R0, #hi_addr(at_engine_rx_idx+0)
STRH	R1, [R0, #0]
MOVS	R1, #0
LDR	R0, [SP, #4]
LDR	R0, [R0, #0]
STRB	R1, [R0, #0]
;at_engine.c,638 :: 		AT_RESET_CUE();
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_no_response_f+0)
MOVT	R0, #hi_addr(at_engine_no_response_f+0)
STRB	R1, [R0, #0]
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_response_f+0)
MOVT	R0, #hi_addr(at_engine_response_f+0)
STRB	R1, [R0, #0]
MOVS	R1, #0
MOVW	R0, #lo_addr(at_engine_cue_f+0)
MOVT	R0, #hi_addr(at_engine_cue_f+0)
STRB	R1, [R0, #0]
;at_engine.c,639 :: 		}
L_at_process82:
;at_engine.c,640 :: 		}
L_end_at_process:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _at_process
