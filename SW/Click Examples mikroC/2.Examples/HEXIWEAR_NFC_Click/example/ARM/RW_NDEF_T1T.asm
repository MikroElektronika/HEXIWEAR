_rw_ndef_t1t_reset:
;RW_NDEF_T1T.c,77 :: 		void rw_ndef_t1t_reset( void )
SUB	SP, SP, #4
;RW_NDEF_T1T.c,79 :: 		e_rw_ndef_t1t_state = INITIAL;
MOVS	R1, #0
MOVW	R0, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R0, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
STRB	R1, [R0, #0]
;RW_NDEF_T1T.c,80 :: 		rw_ndef_t1t_ndef.p_record = ndef_buffer;
MOVW	R1, #lo_addr(_ndef_buffer+0)
MOVT	R1, #hi_addr(_ndef_buffer+0)
MOVW	R0, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R0, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
STR	R1, [R0, #0]
;RW_NDEF_T1T.c,81 :: 		}
L_end_rw_ndef_t1t_reset:
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t1t_reset
_rw_ndef_t1t_read_next:
;RW_NDEF_T1T.c,84 :: 		uint8_t *rsp, uint16_t *p_rsp_size )
; p_rsp_size start address is: 12 (R3)
; rsp start address is: 8 (R2)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
MOV	R9, R0
MOV	R7, R2
MOV	R8, R3
; p_rsp_size end address is: 12 (R3)
; rsp end address is: 8 (R2)
; cmd_size end address is: 4 (R1)
; p_cmd end address is: 0 (R0)
; p_cmd start address is: 36 (R9)
; cmd_size start address is: 4 (R1)
; rsp start address is: 28 (R7)
; p_rsp_size start address is: 32 (R8)
;RW_NDEF_T1T.c,87 :: 		*p_rsp_size = 0;
MOVS	R4, #0
STRH	R4, [R8, #0]
;RW_NDEF_T1T.c,89 :: 		switch( e_rw_ndef_t1t_state )
IT	AL
BAL	L_rw_ndef_t1t_read_next0
; cmd_size end address is: 4 (R1)
; p_cmd end address is: 36 (R9)
;RW_NDEF_T1T.c,91 :: 		case INITIAL:
L_rw_ndef_t1t_read_next2:
;RW_NDEF_T1T.c,93 :: 		memcpy( rsp, ( uint8_t * )T1T_RID, sizeof( T1T_RID ) );
MOVS	R2, #7
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_T1T_RID+0)
MOVT	R1, #hi_addr(RW_NDEF_T1T_T1T_RID+0)
MOV	R0, R7
; rsp end address is: 28 (R7)
BL	_memcpy+0
;RW_NDEF_T1T.c,94 :: 		*p_rsp_size = 7;
MOVS	R4, #7
STRH	R4, [R8, #0]
; p_rsp_size end address is: 32 (R8)
;RW_NDEF_T1T.c,95 :: 		e_rw_ndef_t1t_state = GETTING_ID;
MOVS	R5, #1
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T1T.c,96 :: 		break;
IT	AL
BAL	L_rw_ndef_t1t_read_next1
;RW_NDEF_T1T.c,98 :: 		case GETTING_ID:
L_rw_ndef_t1t_read_next3:
;RW_NDEF_T1T.c,100 :: 		if ( ( cmd_size == 7 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
; p_cmd start address is: 36 (R9)
; p_rsp_size start address is: 32 (R8)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
CMP	R1, #7
IT	NE
BNE	L__rw_ndef_t1t_read_next30
SUBS	R4, R1, #1
UXTH	R4, R4
; cmd_size end address is: 4 (R1)
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t1t_read_next29
L__rw_ndef_t1t_read_next28:
;RW_NDEF_T1T.c,103 :: 		rw_ndef_t1t_ndef.hr0 = p_cmd[0];
LDRB	R5, [R9, #0]
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+0)
STRB	R5, [R4, #0]
;RW_NDEF_T1T.c,104 :: 		rw_ndef_t1t_ndef.hr1 = p_cmd[1];
ADD	R4, R9, #1
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+1)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+1)
STRB	R5, [R4, #0]
;RW_NDEF_T1T.c,105 :: 		memcpy( rw_ndef_t1t_ndef.uid, &p_cmd[2], sizeof( rw_ndef_t1t_ndef.uid ) );
ADD	R4, R9, #2
; p_cmd end address is: 36 (R9)
MOVS	R2, #4
SXTH	R2, R2
MOV	R1, R4
MOVW	R0, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOVT	R0, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
BL	_memcpy+0
;RW_NDEF_T1T.c,108 :: 		memcpy( rsp, ( uint8_t * )T1T_RALL, sizeof( T1T_RALL ) );
MOVS	R2, #3
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_T1T_RALL+0)
MOVT	R1, #hi_addr(RW_NDEF_T1T_T1T_RALL+0)
MOV	R0, R7
BL	_memcpy+0
;RW_NDEF_T1T.c,109 :: 		memcpy( &rsp[3], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
ADDS	R4, R7, #3
; rsp end address is: 28 (R7)
MOVS	R2, #4
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOVT	R1, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOV	R0, R4
BL	_memcpy+0
;RW_NDEF_T1T.c,110 :: 		*p_rsp_size = sizeof( T1T_RALL ) + sizeof( rw_ndef_t1t_ndef.uid );
MOVS	R4, #7
STRH	R4, [R8, #0]
; p_rsp_size end address is: 32 (R8)
;RW_NDEF_T1T.c,111 :: 		e_rw_ndef_t1t_state = READING_CARD_CONTENT;
MOVS	R5, #2
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T1T.c,100 :: 		if ( ( cmd_size == 7 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
L__rw_ndef_t1t_read_next30:
L__rw_ndef_t1t_read_next29:
;RW_NDEF_T1T.c,113 :: 		break;
IT	AL
BAL	L_rw_ndef_t1t_read_next1
;RW_NDEF_T1T.c,115 :: 		case READING_CARD_CONTENT:
L_rw_ndef_t1t_read_next7:
;RW_NDEF_T1T.c,117 :: 		if ( ( cmd_size == 123 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
; p_cmd start address is: 36 (R9)
; p_rsp_size start address is: 32 (R8)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
CMP	R1, #123
IT	NE
BNE	L__rw_ndef_t1t_read_next32
SUBS	R4, R1, #1
UXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t1t_read_next31
L__rw_ndef_t1t_read_next27:
;RW_NDEF_T1T.c,120 :: 		if ( p_cmd[10] == T1T_MAGIC_NUMBER )
ADD	R4, R9, #10
LDRB	R4, [R4, #0]
CMP	R4, #225
IT	NE
BNE	L_rw_ndef_t1t_read_next11
;RW_NDEF_T1T.c,122 :: 		uint8_t tmp = 14;
; tmp start address is: 0 (R0)
MOVS	R0, #14
; cmd_size end address is: 4 (R1)
; rsp end address is: 28 (R7)
; p_rsp_size end address is: 32 (R8)
; tmp end address is: 0 (R0)
; p_cmd end address is: 36 (R9)
STR	R8, [SP, #4]
UXTB	R10, R0
UXTH	R0, R1
MOV	R8, R7
LDR	R7, [SP, #4]
;RW_NDEF_T1T.c,126 :: 		while ( p_cmd[tmp] != T1T_NDEF_TLV )
L_rw_ndef_t1t_read_next12:
; tmp start address is: 40 (R10)
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 0 (R0)
; p_cmd start address is: 36 (R9)
ADD	R4, R9, R10, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #3
IT	EQ
BEQ	L_rw_ndef_t1t_read_next13
;RW_NDEF_T1T.c,128 :: 		tmp += 2 + p_cmd[tmp + 1];
ADD	R4, R10, #1
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
ADDS	R4, R4, #2
SXTH	R4, R4
ADD	R4, R10, R4, LSL #0
UXTB	R10, R4
;RW_NDEF_T1T.c,129 :: 		if ( tmp > cmd_size ) return;
UXTB	R4, R4
CMP	R4, R0
IT	LS
BLS	L_rw_ndef_t1t_read_next14
; p_rsp_size end address is: 28 (R7)
; rsp end address is: 32 (R8)
; cmd_size end address is: 0 (R0)
; p_cmd end address is: 36 (R9)
; tmp end address is: 40 (R10)
IT	AL
BAL	L_end_rw_ndef_t1t_read_next
L_rw_ndef_t1t_read_next14:
;RW_NDEF_T1T.c,130 :: 		}
; tmp start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
; cmd_size start address is: 0 (R0)
; rsp start address is: 32 (R8)
; p_rsp_size start address is: 28 (R7)
IT	AL
BAL	L_rw_ndef_t1t_read_next12
L_rw_ndef_t1t_read_next13:
;RW_NDEF_T1T.c,132 :: 		rw_ndef_t1t_ndef.record_size = p_cmd[tmp + 1];
ADD	R4, R10, #1
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
MOVW	R6, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
MOVT	R6, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
STRH	R4, [R6, #0]
;RW_NDEF_T1T.c,133 :: 		data_size = ( cmd_size - 1 ) - 16 - tmp - 2;
SUBS	R4, R0, #1
UXTH	R4, R4
; cmd_size end address is: 0 (R0)
SUBS	R4, #16
UXTH	R4, R4
SUB	R4, R4, R10, LSL #0
UXTH	R4, R4
SUBS	R4, R4, #2
; data_size start address is: 0 (R0)
UXTB	R0, R4
;RW_NDEF_T1T.c,136 :: 		if( rw_ndef_t1t_ndef.record_size <= data_size )
UXTB	R5, R4
MOV	R4, R6
LDRH	R4, [R4, #0]
CMP	R4, R5
IT	HI
BHI	L_rw_ndef_t1t_read_next15
; p_rsp_size end address is: 28 (R7)
; rsp end address is: 32 (R8)
; data_size end address is: 0 (R0)
;RW_NDEF_T1T.c,139 :: 		rw_ndef_t1t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
LDRH	R6, [R4, #0]
;RW_NDEF_T1T.c,138 :: 		memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
ADD	R4, R10, #2
SXTH	R4, R4
; tmp end address is: 40 (R10)
ADD	R5, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
LDR	R4, [R4, #0]
;RW_NDEF_T1T.c,139 :: 		rw_ndef_t1t_ndef.record_size );
SXTH	R2, R6
;RW_NDEF_T1T.c,138 :: 		memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
MOV	R1, R5
MOV	R0, R4
;RW_NDEF_T1T.c,139 :: 		rw_ndef_t1t_ndef.record_size );
BL	_memcpy+0
;RW_NDEF_T1T.c,142 :: 		if( p_rw_ndef_pull_cb != NULL )
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t1t_read_next16
;RW_NDEF_T1T.c,144 :: 		rw_ndef_t1t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
LDRH	R5, [R4, #0]
;RW_NDEF_T1T.c,143 :: 		p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
LDR	R4, [R4, #0]
;RW_NDEF_T1T.c,144 :: 		rw_ndef_t1t_ndef.record_size );
UXTH	R1, R5
;RW_NDEF_T1T.c,143 :: 		p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
MOV	R0, R4
;RW_NDEF_T1T.c,144 :: 		rw_ndef_t1t_ndef.record_size );
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_t1t_read_next16:
;RW_NDEF_T1T.c,145 :: 		} else {
IT	AL
BAL	L_rw_ndef_t1t_read_next17
L_rw_ndef_t1t_read_next15:
;RW_NDEF_T1T.c,146 :: 		rw_ndef_t1t_ndef.record_ptr = data_size;
; data_size start address is: 0 (R0)
; tmp start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
; rsp start address is: 32 (R8)
; p_rsp_size start address is: 28 (R7)
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
STRH	R0, [R4, #0]
; data_size end address is: 0 (R0)
;RW_NDEF_T1T.c,148 :: 		rw_ndef_t1t_ndef.record_ptr );
LDRH	R6, [R4, #0]
;RW_NDEF_T1T.c,147 :: 		memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
ADD	R4, R10, #2
SXTH	R4, R4
; tmp end address is: 40 (R10)
ADD	R5, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
LDR	R4, [R4, #0]
;RW_NDEF_T1T.c,148 :: 		rw_ndef_t1t_ndef.record_ptr );
SXTH	R2, R6
;RW_NDEF_T1T.c,147 :: 		memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
MOV	R1, R5
MOV	R0, R4
;RW_NDEF_T1T.c,148 :: 		rw_ndef_t1t_ndef.record_ptr );
BL	_memcpy+0
;RW_NDEF_T1T.c,149 :: 		rw_ndef_t1t_ndef.blk_nb = 0x10;
MOVS	R5, #16
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
STRB	R5, [R4, #0]
;RW_NDEF_T1T.c,152 :: 		memcpy( rsp, ( uint8_t * )T1T_READ8, sizeof( T1T_READ8 ) );
MOVS	R2, #10
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_T1T_READ8+0)
MOVT	R1, #hi_addr(RW_NDEF_T1T_T1T_READ8+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T1T.c,153 :: 		rsp[1] = rw_ndef_t1t_ndef.blk_nb;
ADD	R5, R8, #1
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T1T.c,154 :: 		memcpy( &rsp[10], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
ADD	R4, R8, #10
; rsp end address is: 32 (R8)
MOVS	R2, #4
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOVT	R1, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOV	R0, R4
BL	_memcpy+0
;RW_NDEF_T1T.c,155 :: 		*p_rsp_size = sizeof( T1T_READ8 ) + sizeof( rw_ndef_t1t_ndef.uid );
MOVS	R4, #14
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T1T.c,157 :: 		e_rw_ndef_t1t_state = READING_NDEF;
MOVS	R5, #3
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T1T.c,158 :: 		}
L_rw_ndef_t1t_read_next17:
;RW_NDEF_T1T.c,159 :: 		}
L_rw_ndef_t1t_read_next11:
;RW_NDEF_T1T.c,117 :: 		if ( ( cmd_size == 123 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
L__rw_ndef_t1t_read_next32:
L__rw_ndef_t1t_read_next31:
;RW_NDEF_T1T.c,161 :: 		break;
IT	AL
BAL	L_rw_ndef_t1t_read_next1
;RW_NDEF_T1T.c,163 :: 		case READING_NDEF:
L_rw_ndef_t1t_read_next18:
;RW_NDEF_T1T.c,165 :: 		if ( ( cmd_size == 10 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
; p_cmd start address is: 36 (R9)
; p_rsp_size start address is: 32 (R8)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
CMP	R1, #10
IT	NE
BNE	L__rw_ndef_t1t_read_next34
SUBS	R4, R1, #1
UXTH	R4, R4
; cmd_size end address is: 4 (R1)
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t1t_read_next33
L__rw_ndef_t1t_read_next26:
;RW_NDEF_T1T.c,168 :: 		if ( ( rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr ) < 8 )
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
LDRH	R4, [R4, #0]
SUB	R4, R4, R5
UXTH	R4, R4
CMP	R4, #8
IT	CS
BCS	L_rw_ndef_t1t_read_next22
; rsp end address is: 28 (R7)
; p_rsp_size end address is: 32 (R8)
;RW_NDEF_T1T.c,171 :: 		rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr );
MOVW	R8, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
MOVT	R8, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
LDRH	R5, [R8, #0]
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
LDRH	R4, [R4, #0]
SUB	R7, R4, R5
;RW_NDEF_T1T.c,170 :: 		memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1],
ADD	R6, R9, #1
; p_cmd end address is: 36 (R9)
MOV	R4, R8
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
;RW_NDEF_T1T.c,171 :: 		rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr );
SXTH	R2, R7
;RW_NDEF_T1T.c,170 :: 		memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1],
MOV	R1, R6
MOV	R0, R4
;RW_NDEF_T1T.c,171 :: 		rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr );
BL	_memcpy+0
;RW_NDEF_T1T.c,174 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t1t_read_next23
;RW_NDEF_T1T.c,175 :: 		rw_ndef_t1t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+10)
LDRH	R5, [R4, #0]
;RW_NDEF_T1T.c,174 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
LDR	R4, [R4, #0]
;RW_NDEF_T1T.c,175 :: 		rw_ndef_t1t_ndef.record_size );
UXTH	R1, R5
;RW_NDEF_T1T.c,174 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
MOV	R0, R4
;RW_NDEF_T1T.c,175 :: 		rw_ndef_t1t_ndef.record_size );
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_t1t_read_next23:
;RW_NDEF_T1T.c,176 :: 		}
IT	AL
BAL	L_rw_ndef_t1t_read_next24
L_rw_ndef_t1t_read_next22:
;RW_NDEF_T1T.c,179 :: 		memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1], 8 );
; p_cmd start address is: 36 (R9)
; p_rsp_size start address is: 32 (R8)
; rsp start address is: 28 (R7)
ADD	R6, R9, #1
; p_cmd end address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+12)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
MOVS	R2, #8
SXTH	R2, R2
MOV	R1, R6
MOV	R0, R4
BL	_memcpy+0
;RW_NDEF_T1T.c,180 :: 		rw_ndef_t1t_ndef.record_ptr += 8;
MOVW	R5, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
MOVT	R5, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+8)
LDRH	R4, [R5, #0]
ADDS	R4, #8
STRH	R4, [R5, #0]
;RW_NDEF_T1T.c,181 :: 		rw_ndef_t1t_ndef.blk_nb++;
MOVW	R5, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
MOVT	R5, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
LDRB	R4, [R5, #0]
ADDS	R4, R4, #1
STRB	R4, [R5, #0]
;RW_NDEF_T1T.c,184 :: 		memcpy ( rsp, ( uint8_t * )T1T_READ8, sizeof( T1T_READ8 ) );
MOVS	R2, #10
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_T1T_READ8+0)
MOVT	R1, #hi_addr(RW_NDEF_T1T_T1T_READ8+0)
MOV	R0, R7
BL	_memcpy+0
;RW_NDEF_T1T.c,185 :: 		rsp[1] = rw_ndef_t1t_ndef.blk_nb;
ADDS	R5, R7, #1
MOVW	R4, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
MOVT	R4, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+6)
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T1T.c,186 :: 		memcpy ( &rsp[10], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
ADDW	R4, R7, #10
; rsp end address is: 28 (R7)
MOVS	R2, #4
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOVT	R1, #hi_addr(RW_NDEF_T1T_rw_ndef_t1t_ndef+2)
MOV	R0, R4
BL	_memcpy+0
;RW_NDEF_T1T.c,187 :: 		*p_rsp_size = sizeof( T1T_READ8 ) + sizeof( rw_ndef_t1t_ndef.uid );
MOVS	R4, #14
STRH	R4, [R8, #0]
; p_rsp_size end address is: 32 (R8)
;RW_NDEF_T1T.c,188 :: 		}
L_rw_ndef_t1t_read_next24:
;RW_NDEF_T1T.c,165 :: 		if ( ( cmd_size == 10 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
L__rw_ndef_t1t_read_next34:
L__rw_ndef_t1t_read_next33:
;RW_NDEF_T1T.c,190 :: 		break;
IT	AL
BAL	L_rw_ndef_t1t_read_next1
;RW_NDEF_T1T.c,192 :: 		default:
L_rw_ndef_t1t_read_next25:
;RW_NDEF_T1T.c,193 :: 		break;
IT	AL
BAL	L_rw_ndef_t1t_read_next1
;RW_NDEF_T1T.c,194 :: 		}
L_rw_ndef_t1t_read_next0:
; p_cmd start address is: 36 (R9)
; p_rsp_size start address is: 32 (R8)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t1t_read_next2
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #1
IT	EQ
BEQ	L_rw_ndef_t1t_read_next3
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #2
IT	EQ
BEQ	L_rw_ndef_t1t_read_next7
MOVW	R4, #lo_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T1T_e_rw_ndef_t1t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #3
IT	EQ
BEQ	L_rw_ndef_t1t_read_next18
; cmd_size end address is: 4 (R1)
; rsp end address is: 28 (R7)
; p_rsp_size end address is: 32 (R8)
; p_cmd end address is: 36 (R9)
IT	AL
BAL	L_rw_ndef_t1t_read_next25
L_rw_ndef_t1t_read_next1:
;RW_NDEF_T1T.c,195 :: 		}
L_end_rw_ndef_t1t_read_next:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _rw_ndef_t1t_read_next
