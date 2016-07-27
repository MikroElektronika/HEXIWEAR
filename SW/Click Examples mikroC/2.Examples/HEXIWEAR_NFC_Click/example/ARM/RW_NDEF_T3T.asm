_rw_ndef_t3t_reset:
;RW_NDEF_T3T.c,73 :: 		void rw_ndef_t3t_reset( void )
SUB	SP, SP, #4
;RW_NDEF_T3T.c,75 :: 		e_rw_ndef_t3t_state = INITIAL;
MOVS	R1, #0
MOVW	R0, #lo_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
MOVT	R0, #hi_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
STRB	R1, [R0, #0]
;RW_NDEF_T3T.c,76 :: 		rw_ndef_t3t_ndef.p_record = ndef_buffer;
MOVW	R1, #lo_addr(_ndef_buffer+0)
MOVT	R1, #hi_addr(_ndef_buffer+0)
MOVW	R0, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
MOVT	R0, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
STR	R1, [R0, #0]
;RW_NDEF_T3T.c,77 :: 		}
L_end_rw_ndef_t3t_reset:
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t3t_reset
_rw_ndef_t3t_set_id_m:
;RW_NDEF_T3T.c,79 :: 		void rw_ndef_t3t_set_id_m( uint8_t *pIDm )
; pIDm start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R6, R0
; pIDm end address is: 0 (R0)
; pIDm start address is: 24 (R6)
;RW_NDEF_T3T.c,81 :: 		memcpy( rw_ndef_t3t_ndef.id_m, pIDm, sizeof( rw_ndef_t3t_ndef.id_m ) );
MOVS	R2, #8
SXTH	R2, R2
MOV	R1, R6
MOVW	R0, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+0)
MOVT	R0, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+0)
BL	_memcpy+0
;RW_NDEF_T3T.c,82 :: 		memcpy( &T3T_CHECK[2], pIDm, sizeof( rw_ndef_t3t_ndef.id_m ) );
MOVS	R2, #8
SXTH	R2, R2
MOV	R1, R6
; pIDm end address is: 24 (R6)
MOVW	R0, #lo_addr(RW_NDEF_T3T_T3T_CHECK+2)
MOVT	R0, #hi_addr(RW_NDEF_T3T_T3T_CHECK+2)
BL	_memcpy+0
;RW_NDEF_T3T.c,83 :: 		}
L_end_rw_ndef_t3t_set_id_m:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t3t_set_id_m
_rw_ndef_t3t_read_next:
;RW_NDEF_T3T.c,86 :: 		uint8_t *p_cmd, uint16_t *p_cmd_size )
; p_cmd_size start address is: 12 (R3)
; p_cmd start address is: 8 (R2)
; rsp_size start address is: 4 (R1)
; p_rsp start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R9, R0
MOV	R7, R2
MOV	R8, R3
; p_cmd_size end address is: 12 (R3)
; p_cmd end address is: 8 (R2)
; rsp_size end address is: 4 (R1)
; p_rsp end address is: 0 (R0)
; p_rsp start address is: 36 (R9)
; rsp_size start address is: 4 (R1)
; p_cmd start address is: 28 (R7)
; p_cmd_size start address is: 32 (R8)
;RW_NDEF_T3T.c,89 :: 		*p_cmd_size = 0;
MOVS	R4, #0
STRH	R4, [R8, #0]
;RW_NDEF_T3T.c,91 :: 		switch( e_rw_ndef_t3t_state )
IT	AL
BAL	L_rw_ndef_t3t_read_next0
; p_rsp end address is: 36 (R9)
; rsp_size end address is: 4 (R1)
;RW_NDEF_T3T.c,93 :: 		case INITIAL:
L_rw_ndef_t3t_read_next2:
;RW_NDEF_T3T.c,95 :: 		memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
MOVS	R2, #16
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T3T_T3T_CHECK+0)
MOVT	R1, #hi_addr(RW_NDEF_T3T_T3T_CHECK+0)
MOV	R0, R7
; p_cmd end address is: 28 (R7)
BL	_memcpy+0
;RW_NDEF_T3T.c,96 :: 		*p_cmd_size = sizeof( T3T_CHECK );
MOVS	R4, #16
STRH	R4, [R8, #0]
; p_cmd_size end address is: 32 (R8)
;RW_NDEF_T3T.c,97 :: 		e_rw_ndef_t3t_state = GETTING_ATTRIBUTE_INFO;
MOVS	R5, #1
MOVW	R4, #lo_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T3T.c,98 :: 		break;
IT	AL
BAL	L_rw_ndef_t3t_read_next1
;RW_NDEF_T3T.c,100 :: 		case GETTING_ATTRIBUTE_INFO:
L_rw_ndef_t3t_read_next3:
;RW_NDEF_T3T.c,102 :: 		if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
; p_cmd_size start address is: 32 (R8)
; p_cmd start address is: 28 (R7)
; rsp_size start address is: 4 (R1)
; p_rsp start address is: 36 (R9)
SUBS	R4, R1, #1
UXTH	R4, R4
; rsp_size end address is: 4 (R1)
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t3t_read_next22
ADD	R4, R9, #1
LDRB	R4, [R4, #0]
CMP	R4, #7
IT	NE
BNE	L__rw_ndef_t3t_read_next21
;RW_NDEF_T3T.c,103 :: 		( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
ADD	R4, R9, #10
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t3t_read_next20
ADD	R4, R9, #11
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t3t_read_next19
L__rw_ndef_t3t_read_next18:
;RW_NDEF_T3T.c,107 :: 		p_rsp[26];
ADD	R4, R9, #26
; p_rsp end address is: 36 (R9)
LDRB	R4, [R4, #0]
UXTB	R5, R4
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
STRH	R5, [R4, #0]
;RW_NDEF_T3T.c,109 :: 		if( rw_ndef_t3t_ndef.record_size > RW_MAX_NDEF_FILE_SIZE )
CMP	R5, #240
IT	LS
BLS	L_rw_ndef_t3t_read_next7
; p_cmd end address is: 28 (R7)
; p_cmd_size end address is: 32 (R8)
;RW_NDEF_T3T.c,112 :: 		} else {
IT	AL
BAL	L_rw_ndef_t3t_read_next8
L_rw_ndef_t3t_read_next7:
;RW_NDEF_T3T.c,113 :: 		rw_ndef_t3t_ndef.record_ptr = 0;
; p_cmd_size start address is: 32 (R8)
; p_cmd start address is: 28 (R7)
MOVS	R5, #0
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
STRH	R5, [R4, #0]
;RW_NDEF_T3T.c,114 :: 		rw_ndef_t3t_ndef.blk_nb = 1;
MOVS	R5, #1
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+8)
STRB	R5, [R4, #0]
;RW_NDEF_T3T.c,117 :: 		memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
MOVS	R2, #16
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T3T_T3T_CHECK+0)
MOVT	R1, #hi_addr(RW_NDEF_T3T_T3T_CHECK+0)
MOV	R0, R7
BL	_memcpy+0
;RW_NDEF_T3T.c,118 :: 		p_cmd[15] = 0x01;
ADDW	R5, R7, #15
; p_cmd end address is: 28 (R7)
MOVS	R4, #1
STRB	R4, [R5, #0]
;RW_NDEF_T3T.c,119 :: 		*p_cmd_size = sizeof( T3T_CHECK );
MOVS	R4, #16
STRH	R4, [R8, #0]
; p_cmd_size end address is: 32 (R8)
;RW_NDEF_T3T.c,120 :: 		e_rw_ndef_t3t_state = READING_CARD_CONTENT;
MOVS	R5, #2
MOVW	R4, #lo_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T3T.c,121 :: 		}
L_rw_ndef_t3t_read_next8:
;RW_NDEF_T3T.c,102 :: 		if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
L__rw_ndef_t3t_read_next22:
L__rw_ndef_t3t_read_next21:
;RW_NDEF_T3T.c,103 :: 		( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
L__rw_ndef_t3t_read_next20:
L__rw_ndef_t3t_read_next19:
;RW_NDEF_T3T.c,123 :: 		break;
IT	AL
BAL	L_rw_ndef_t3t_read_next1
;RW_NDEF_T3T.c,125 :: 		case READING_CARD_CONTENT:
L_rw_ndef_t3t_read_next9:
;RW_NDEF_T3T.c,127 :: 		if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
; p_cmd_size start address is: 32 (R8)
; p_cmd start address is: 28 (R7)
; rsp_size start address is: 4 (R1)
; p_rsp start address is: 36 (R9)
SUBS	R4, R1, #1
UXTH	R4, R4
; rsp_size end address is: 4 (R1)
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t3t_read_next26
ADD	R4, R9, #1
LDRB	R4, [R4, #0]
CMP	R4, #7
IT	NE
BNE	L__rw_ndef_t3t_read_next25
;RW_NDEF_T3T.c,128 :: 		( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
ADD	R4, R9, #10
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t3t_read_next24
ADD	R4, R9, #11
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t3t_read_next23
L__rw_ndef_t3t_read_next17:
;RW_NDEF_T3T.c,131 :: 		if ( ( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) <= 16 )
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
LDRH	R4, [R4, #0]
SUB	R4, R4, R5
UXTH	R4, R4
CMP	R4, #16
IT	HI
BHI	L_rw_ndef_t3t_read_next13
; p_cmd end address is: 28 (R7)
; p_cmd_size end address is: 32 (R8)
;RW_NDEF_T3T.c,134 :: 		( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) );
MOVW	R8, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
MOVT	R8, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
LDRH	R5, [R8, #0]
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
LDRH	R4, [R4, #0]
SUB	R7, R4, R5
;RW_NDEF_T3T.c,133 :: 		memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
ADD	R6, R9, #13
; p_rsp end address is: 36 (R9)
MOV	R4, R8
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
;RW_NDEF_T3T.c,134 :: 		( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) );
SXTH	R2, R7
;RW_NDEF_T3T.c,133 :: 		memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
MOV	R1, R6
MOV	R0, R4
;RW_NDEF_T3T.c,134 :: 		( rw_ndef_t3t_ndef.record_size - rw_ndef_t3t_ndef.record_ptr ) );
BL	_memcpy+0
;RW_NDEF_T3T.c,136 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t3t_ndef.p_record,
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t3t_read_next14
;RW_NDEF_T3T.c,137 :: 		rw_ndef_t3t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+12)
LDRH	R5, [R4, #0]
;RW_NDEF_T3T.c,136 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t3t_ndef.p_record,
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
LDR	R4, [R4, #0]
;RW_NDEF_T3T.c,137 :: 		rw_ndef_t3t_ndef.record_size );
UXTH	R1, R5
;RW_NDEF_T3T.c,136 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t3t_ndef.p_record,
MOV	R0, R4
;RW_NDEF_T3T.c,137 :: 		rw_ndef_t3t_ndef.record_size );
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_t3t_read_next14:
;RW_NDEF_T3T.c,138 :: 		} else {
IT	AL
BAL	L_rw_ndef_t3t_read_next15
L_rw_ndef_t3t_read_next13:
;RW_NDEF_T3T.c,139 :: 		memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
; p_cmd_size start address is: 32 (R8)
; p_cmd start address is: 28 (R7)
; p_rsp start address is: 36 (R9)
ADD	R6, R9, #13
; p_rsp end address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+16)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
;RW_NDEF_T3T.c,140 :: 		16 );
MOVS	R2, #16
SXTH	R2, R2
;RW_NDEF_T3T.c,139 :: 		memcpy( &rw_ndef_t3t_ndef.p_record[rw_ndef_t3t_ndef.record_ptr], &p_rsp[13],
MOV	R1, R6
MOV	R0, R4
;RW_NDEF_T3T.c,140 :: 		16 );
BL	_memcpy+0
;RW_NDEF_T3T.c,141 :: 		rw_ndef_t3t_ndef.record_ptr += 16;
MOVW	R5, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
MOVT	R5, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+10)
LDRH	R4, [R5, #0]
ADDS	R4, #16
STRH	R4, [R5, #0]
;RW_NDEF_T3T.c,142 :: 		rw_ndef_t3t_ndef.blk_nb++;
MOVW	R5, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+8)
MOVT	R5, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+8)
LDRB	R4, [R5, #0]
ADDS	R4, R4, #1
STRB	R4, [R5, #0]
;RW_NDEF_T3T.c,145 :: 		memcpy ( p_cmd, T3T_CHECK, sizeof( T3T_CHECK ) );
MOVS	R2, #16
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T3T_T3T_CHECK+0)
MOVT	R1, #hi_addr(RW_NDEF_T3T_T3T_CHECK+0)
MOV	R0, R7
BL	_memcpy+0
;RW_NDEF_T3T.c,146 :: 		p_cmd[15] = rw_ndef_t3t_ndef.blk_nb;
ADDW	R5, R7, #15
; p_cmd end address is: 28 (R7)
MOVW	R4, #lo_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T3T_rw_ndef_t3t_ndef+8)
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T3T.c,147 :: 		*p_cmd_size = sizeof( T3T_CHECK );
MOVS	R4, #16
STRH	R4, [R8, #0]
; p_cmd_size end address is: 32 (R8)
;RW_NDEF_T3T.c,148 :: 		}
L_rw_ndef_t3t_read_next15:
;RW_NDEF_T3T.c,127 :: 		if ( ( p_rsp[rsp_size - 1] == 0x00 ) && ( p_rsp[1] == 0x07 ) &&
L__rw_ndef_t3t_read_next26:
L__rw_ndef_t3t_read_next25:
;RW_NDEF_T3T.c,128 :: 		( p_rsp[10] == 0x00 ) && ( p_rsp[11] == 0x00 ) )
L__rw_ndef_t3t_read_next24:
L__rw_ndef_t3t_read_next23:
;RW_NDEF_T3T.c,150 :: 		break;
IT	AL
BAL	L_rw_ndef_t3t_read_next1
;RW_NDEF_T3T.c,152 :: 		default:
L_rw_ndef_t3t_read_next16:
;RW_NDEF_T3T.c,153 :: 		break;
IT	AL
BAL	L_rw_ndef_t3t_read_next1
;RW_NDEF_T3T.c,154 :: 		}
L_rw_ndef_t3t_read_next0:
; p_cmd_size start address is: 32 (R8)
; p_cmd start address is: 28 (R7)
; rsp_size start address is: 4 (R1)
; p_rsp start address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t3t_read_next2
MOVW	R4, #lo_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #1
IT	EQ
BEQ	L_rw_ndef_t3t_read_next3
MOVW	R4, #lo_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T3T_e_rw_ndef_t3t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #2
IT	EQ
BEQ	L_rw_ndef_t3t_read_next9
; p_rsp end address is: 36 (R9)
; rsp_size end address is: 4 (R1)
; p_cmd end address is: 28 (R7)
; p_cmd_size end address is: 32 (R8)
IT	AL
BAL	L_rw_ndef_t3t_read_next16
L_rw_ndef_t3t_read_next1:
;RW_NDEF_T3T.c,155 :: 		}
L_end_rw_ndef_t3t_read_next:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t3t_read_next
