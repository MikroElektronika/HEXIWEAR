_rw_ndef_t2t_reset:
;RW_NDEF_T2T.c,69 :: 		void rw_ndef_t2t_reset( void )
SUB	SP, SP, #4
;RW_NDEF_T2T.c,71 :: 		e_rw_ndef_t2t_state = INITIAL;
MOVS	R1, #0
MOVW	R0, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R0, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
STRB	R1, [R0, #0]
;RW_NDEF_T2T.c,72 :: 		rw_ndef_t2t_ndef.p_record = ndef_buffer;
MOVW	R1, #lo_addr(_ndef_buffer+0)
MOVT	R1, #hi_addr(_ndef_buffer+0)
MOVW	R0, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R0, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
STR	R1, [R0, #0]
;RW_NDEF_T2T.c,73 :: 		}
L_end_rw_ndef_t2t_reset:
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t2t_reset
_rw_ndef_t2t_read_next:
;RW_NDEF_T2T.c,76 :: 		uint8_t *rsp, uint16_t *p_rsp_size )
; p_rsp_size start address is: 12 (R3)
; rsp start address is: 8 (R2)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
MOV	R8, R0
MOV	R7, R2
MOV	R9, R3
; p_rsp_size end address is: 12 (R3)
; rsp end address is: 8 (R2)
; cmd_size end address is: 4 (R1)
; p_cmd end address is: 0 (R0)
; p_cmd start address is: 32 (R8)
; cmd_size start address is: 4 (R1)
; rsp start address is: 28 (R7)
; p_rsp_size start address is: 36 (R9)
;RW_NDEF_T2T.c,79 :: 		*p_rsp_size = 0;
MOVS	R4, #0
STRH	R4, [R9, #0]
;RW_NDEF_T2T.c,81 :: 		switch( e_rw_ndef_t2t_state )
IT	AL
BAL	L_rw_ndef_t2t_read_next0
; p_cmd end address is: 32 (R8)
; cmd_size end address is: 4 (R1)
;RW_NDEF_T2T.c,83 :: 		case INITIAL:
L_rw_ndef_t2t_read_next2:
;RW_NDEF_T2T.c,85 :: 		rsp[0] = 0x30;
MOVS	R4, #48
STRB	R4, [R7, #0]
;RW_NDEF_T2T.c,86 :: 		rsp[1] = 0x03;
ADDS	R5, R7, #1
; rsp end address is: 28 (R7)
MOVS	R4, #3
STRB	R4, [R5, #0]
;RW_NDEF_T2T.c,87 :: 		*p_rsp_size = 2;
MOVS	R4, #2
STRH	R4, [R9, #0]
; p_rsp_size end address is: 36 (R9)
;RW_NDEF_T2T.c,88 :: 		e_rw_ndef_t2t_state = READING_CC;
MOVS	R5, #1
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T2T.c,89 :: 		break;
IT	AL
BAL	L_rw_ndef_t2t_read_next1
;RW_NDEF_T2T.c,91 :: 		case READING_CC:
L_rw_ndef_t2t_read_next3:
;RW_NDEF_T2T.c,93 :: 		if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) &&
; p_rsp_size start address is: 36 (R9)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 32 (R8)
CMP	R1, #17
IT	NE
BNE	L__rw_ndef_t2t_read_next32
SUBS	R4, R1, #1
UXTH	R4, R4
; cmd_size end address is: 4 (R1)
ADD	R4, R8, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t2t_read_next31
;RW_NDEF_T2T.c,94 :: 		( p_cmd[0] == T2T_MAGIC_NUMBER ) )
LDRB	R4, [R8, #0]
; p_cmd end address is: 32 (R8)
CMP	R4, #225
IT	NE
BNE	L__rw_ndef_t2t_read_next30
L__rw_ndef_t2t_read_next29:
;RW_NDEF_T2T.c,97 :: 		rsp[0] = 0x30;
MOVS	R4, #48
STRB	R4, [R7, #0]
;RW_NDEF_T2T.c,98 :: 		rsp[1] = 0x04;
ADDS	R5, R7, #1
; rsp end address is: 28 (R7)
MOVS	R4, #4
STRB	R4, [R5, #0]
;RW_NDEF_T2T.c,99 :: 		*p_rsp_size = 2;
MOVS	R4, #2
STRH	R4, [R9, #0]
; p_rsp_size end address is: 36 (R9)
;RW_NDEF_T2T.c,101 :: 		e_rw_ndef_t2t_state = READING_DATA;
MOVS	R5, #2
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T2T.c,93 :: 		if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) &&
L__rw_ndef_t2t_read_next32:
L__rw_ndef_t2t_read_next31:
;RW_NDEF_T2T.c,94 :: 		( p_cmd[0] == T2T_MAGIC_NUMBER ) )
L__rw_ndef_t2t_read_next30:
;RW_NDEF_T2T.c,103 :: 		break;
IT	AL
BAL	L_rw_ndef_t2t_read_next1
;RW_NDEF_T2T.c,105 :: 		case READING_DATA:
L_rw_ndef_t2t_read_next7:
;RW_NDEF_T2T.c,107 :: 		if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
; p_rsp_size start address is: 36 (R9)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 32 (R8)
CMP	R1, #17
IT	NE
BNE	L__rw_ndef_t2t_read_next34
SUBS	R4, R1, #1
UXTH	R4, R4
ADD	R4, R8, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t2t_read_next33
L__rw_ndef_t2t_read_next28:
;RW_NDEF_T2T.c,109 :: 		uint8_t Tmp = 0;
; Tmp start address is: 0 (R0)
MOVS	R0, #0
; p_cmd end address is: 32 (R8)
; cmd_size end address is: 4 (R1)
; rsp end address is: 28 (R7)
; p_rsp_size end address is: 36 (R9)
; Tmp end address is: 0 (R0)
STR	R7, [SP, #4]
MOV	R7, R9
MOV	R9, R8
UXTH	R6, R1
UXTB	R10, R0
LDR	R8, [SP, #4]
;RW_NDEF_T2T.c,111 :: 		while ( p_cmd[Tmp] != T2T_NDEF_TLV )
L_rw_ndef_t2t_read_next11:
; Tmp start address is: 40 (R10)
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 24 (R6)
; p_cmd start address is: 36 (R9)
ADD	R4, R9, R10, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #3
IT	EQ
BEQ	L_rw_ndef_t2t_read_next12
;RW_NDEF_T2T.c,113 :: 		Tmp += 2 + p_cmd[Tmp + 1];
ADD	R4, R10, #1
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
ADDS	R4, R4, #2
SXTH	R4, R4
ADD	R4, R10, R4, LSL #0
UXTB	R10, R4
;RW_NDEF_T2T.c,114 :: 		if ( Tmp > cmd_size ) return;
UXTB	R4, R4
CMP	R4, R6
IT	LS
BLS	L_rw_ndef_t2t_read_next13
; p_rsp_size end address is: 28 (R7)
; rsp end address is: 32 (R8)
; cmd_size end address is: 24 (R6)
; p_cmd end address is: 36 (R9)
; Tmp end address is: 40 (R10)
IT	AL
BAL	L_end_rw_ndef_t2t_read_next
L_rw_ndef_t2t_read_next13:
;RW_NDEF_T2T.c,115 :: 		}
; Tmp start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
; cmd_size start address is: 24 (R6)
; rsp start address is: 32 (R8)
; p_rsp_size start address is: 28 (R7)
IT	AL
BAL	L_rw_ndef_t2t_read_next11
L_rw_ndef_t2t_read_next12:
;RW_NDEF_T2T.c,117 :: 		if( p_cmd[Tmp + 1] == 0xFF ) rw_ndef_t2t_ndef.record_size =
ADD	R4, R10, #1
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #255
IT	NE
BNE	L_rw_ndef_t2t_read_next14
;RW_NDEF_T2T.c,118 :: 		( p_cmd[Tmp + 2] << 8 ) + p_cmd[Tmp + 3];
ADD	R4, R10, #2
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
LSLS	R5, R4, #8
UXTH	R5, R5
ADD	R4, R10, #3
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R4, [R4, #0]
ADDS	R5, R5, R4
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
STRH	R5, [R4, #0]
IT	AL
BAL	L_rw_ndef_t2t_read_next15
L_rw_ndef_t2t_read_next14:
;RW_NDEF_T2T.c,119 :: 		else rw_ndef_t2t_ndef.record_size = p_cmd[Tmp + 1];
ADD	R4, R10, #1
SXTH	R4, R4
ADD	R4, R9, R4, LSL #0
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
STRH	R5, [R4, #0]
L_rw_ndef_t2t_read_next15:
;RW_NDEF_T2T.c,122 :: 		if ( rw_ndef_t2t_ndef.record_size <= ( ( cmd_size - 1 ) - Tmp - 2 ) )
SUBS	R4, R6, #1
UXTH	R4, R4
SUB	R4, R4, R10, LSL #0
UXTH	R4, R4
SUBS	R5, R4, #2
UXTH	R5, R5
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
LDRH	R4, [R4, #0]
CMP	R4, R5
IT	HI
BHI	L_rw_ndef_t2t_read_next16
; p_rsp_size end address is: 28 (R7)
; rsp end address is: 32 (R8)
; cmd_size end address is: 24 (R6)
;RW_NDEF_T2T.c,125 :: 		rw_ndef_t2t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
LDRH	R6, [R4, #0]
;RW_NDEF_T2T.c,124 :: 		memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
ADD	R4, R10, #2
SXTH	R4, R4
; Tmp end address is: 40 (R10)
ADD	R5, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
LDR	R4, [R4, #0]
;RW_NDEF_T2T.c,125 :: 		rw_ndef_t2t_ndef.record_size );
SXTH	R2, R6
;RW_NDEF_T2T.c,124 :: 		memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
MOV	R1, R5
MOV	R0, R4
;RW_NDEF_T2T.c,125 :: 		rw_ndef_t2t_ndef.record_size );
BL	_memcpy+0
;RW_NDEF_T2T.c,128 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t2t_read_next17
;RW_NDEF_T2T.c,129 :: 		rw_ndef_t2t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
LDRH	R5, [R4, #0]
;RW_NDEF_T2T.c,128 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
LDR	R4, [R4, #0]
;RW_NDEF_T2T.c,129 :: 		rw_ndef_t2t_ndef.record_size );
UXTH	R1, R5
;RW_NDEF_T2T.c,128 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
MOV	R0, R4
;RW_NDEF_T2T.c,129 :: 		rw_ndef_t2t_ndef.record_size );
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_t2t_read_next17:
;RW_NDEF_T2T.c,130 :: 		}
IT	AL
BAL	L_rw_ndef_t2t_read_next18
L_rw_ndef_t2t_read_next16:
;RW_NDEF_T2T.c,133 :: 		rw_ndef_t2t_ndef.record_ptr = ( cmd_size - 1 ) - Tmp - 2;
; Tmp start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
; cmd_size start address is: 24 (R6)
; rsp start address is: 32 (R8)
; p_rsp_size start address is: 28 (R7)
SUBS	R4, R6, #1
UXTH	R4, R4
; cmd_size end address is: 24 (R6)
SUB	R4, R4, R10, LSL #0
UXTH	R4, R4
SUBS	R5, R4, #2
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
STRH	R5, [R4, #0]
;RW_NDEF_T2T.c,135 :: 		rw_ndef_t2t_ndef.record_ptr );
SXTH	R6, R5
;RW_NDEF_T2T.c,134 :: 		memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
ADD	R4, R10, #2
SXTH	R4, R4
; Tmp end address is: 40 (R10)
ADD	R5, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
LDR	R4, [R4, #0]
;RW_NDEF_T2T.c,135 :: 		rw_ndef_t2t_ndef.record_ptr );
SXTH	R2, R6
;RW_NDEF_T2T.c,134 :: 		memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
MOV	R1, R5
MOV	R0, R4
;RW_NDEF_T2T.c,135 :: 		rw_ndef_t2t_ndef.record_ptr );
BL	_memcpy+0
;RW_NDEF_T2T.c,136 :: 		rw_ndef_t2t_ndef.blk_nb = 8;
MOVS	R4, #8
MOVW	R6, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+0)
MOVT	R6, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+0)
STRB	R4, [R6, #0]
;RW_NDEF_T2T.c,139 :: 		rsp[0] = 0x30;
MOVS	R4, #48
STRB	R4, [R8, #0]
;RW_NDEF_T2T.c,140 :: 		rsp[1] = rw_ndef_t2t_ndef.blk_nb;
ADD	R5, R8, #1
; rsp end address is: 32 (R8)
MOV	R4, R6
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T2T.c,141 :: 		*p_rsp_size = 2;
MOVS	R4, #2
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T2T.c,142 :: 		e_rw_ndef_t2t_state = READING_NDEF;
MOVS	R5, #3
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T2T.c,143 :: 		}
L_rw_ndef_t2t_read_next18:
;RW_NDEF_T2T.c,107 :: 		if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
L__rw_ndef_t2t_read_next34:
L__rw_ndef_t2t_read_next33:
;RW_NDEF_T2T.c,145 :: 		break;
IT	AL
BAL	L_rw_ndef_t2t_read_next1
;RW_NDEF_T2T.c,147 :: 		case READING_NDEF:
L_rw_ndef_t2t_read_next19:
;RW_NDEF_T2T.c,149 :: 		if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
; p_rsp_size start address is: 36 (R9)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 32 (R8)
CMP	R1, #17
IT	NE
BNE	L__rw_ndef_t2t_read_next36
SUBS	R4, R1, #1
UXTH	R4, R4
; cmd_size end address is: 4 (R1)
ADD	R4, R8, R4, LSL #0
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__rw_ndef_t2t_read_next35
L__rw_ndef_t2t_read_next27:
;RW_NDEF_T2T.c,152 :: 		if ( ( rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr ) < 16 )
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
LDRH	R4, [R4, #0]
SUB	R4, R4, R5
UXTH	R4, R4
CMP	R4, #16
IT	CS
BCS	L_rw_ndef_t2t_read_next23
; rsp end address is: 28 (R7)
; p_rsp_size end address is: 36 (R9)
;RW_NDEF_T2T.c,155 :: 		rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr );
MOVW	R7, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
MOVT	R7, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
LDRH	R5, [R7, #0]
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
LDRH	R4, [R4, #0]
SUB	R6, R4, R5
;RW_NDEF_T2T.c,154 :: 		memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd,
MOV	R4, R7
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
;RW_NDEF_T2T.c,155 :: 		rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr );
SXTH	R2, R6
;RW_NDEF_T2T.c,154 :: 		memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd,
MOV	R1, R8
; p_cmd end address is: 32 (R8)
MOV	R0, R4
;RW_NDEF_T2T.c,155 :: 		rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr );
BL	_memcpy+0
;RW_NDEF_T2T.c,158 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t2t_read_next24
;RW_NDEF_T2T.c,159 :: 		rw_ndef_t2t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+4)
LDRH	R5, [R4, #0]
;RW_NDEF_T2T.c,158 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
LDR	R4, [R4, #0]
;RW_NDEF_T2T.c,159 :: 		rw_ndef_t2t_ndef.record_size );
UXTH	R1, R5
;RW_NDEF_T2T.c,158 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
MOV	R0, R4
;RW_NDEF_T2T.c,159 :: 		rw_ndef_t2t_ndef.record_size );
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_t2t_read_next24:
;RW_NDEF_T2T.c,160 :: 		}
IT	AL
BAL	L_rw_ndef_t2t_read_next25
L_rw_ndef_t2t_read_next23:
;RW_NDEF_T2T.c,163 :: 		memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd, 16 );
; p_rsp_size start address is: 36 (R9)
; rsp start address is: 28 (R7)
; p_cmd start address is: 32 (R8)
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+8)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
MOVS	R2, #16
SXTH	R2, R2
MOV	R1, R8
; p_cmd end address is: 32 (R8)
MOV	R0, R4
BL	_memcpy+0
;RW_NDEF_T2T.c,164 :: 		rw_ndef_t2t_ndef.record_ptr += 16;
MOVW	R5, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
MOVT	R5, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+2)
LDRH	R4, [R5, #0]
ADDS	R4, #16
STRH	R4, [R5, #0]
;RW_NDEF_T2T.c,165 :: 		rw_ndef_t2t_ndef.blk_nb += 4;
MOVW	R6, #lo_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+0)
MOVT	R6, #hi_addr(RW_NDEF_T2T_rw_ndef_t2t_ndef+0)
LDRB	R4, [R6, #0]
ADDS	R4, R4, #4
STRB	R4, [R6, #0]
;RW_NDEF_T2T.c,168 :: 		rsp[0] = 0x30;
MOVS	R4, #48
STRB	R4, [R7, #0]
;RW_NDEF_T2T.c,169 :: 		rsp[1] = rw_ndef_t2t_ndef.blk_nb;
ADDS	R5, R7, #1
; rsp end address is: 28 (R7)
MOV	R4, R6
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T2T.c,170 :: 		*p_rsp_size = 2;
MOVS	R4, #2
STRH	R4, [R9, #0]
; p_rsp_size end address is: 36 (R9)
;RW_NDEF_T2T.c,171 :: 		}
L_rw_ndef_t2t_read_next25:
;RW_NDEF_T2T.c,149 :: 		if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
L__rw_ndef_t2t_read_next36:
L__rw_ndef_t2t_read_next35:
;RW_NDEF_T2T.c,173 :: 		break;
IT	AL
BAL	L_rw_ndef_t2t_read_next1
;RW_NDEF_T2T.c,175 :: 		default:
L_rw_ndef_t2t_read_next26:
;RW_NDEF_T2T.c,176 :: 		break;
IT	AL
BAL	L_rw_ndef_t2t_read_next1
;RW_NDEF_T2T.c,177 :: 		}
L_rw_ndef_t2t_read_next0:
; p_rsp_size start address is: 36 (R9)
; rsp start address is: 28 (R7)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 32 (R8)
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t2t_read_next2
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #1
IT	EQ
BEQ	L_rw_ndef_t2t_read_next3
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #2
IT	EQ
BEQ	L_rw_ndef_t2t_read_next7
MOVW	R4, #lo_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T2T_e_rw_ndef_t2t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #3
IT	EQ
BEQ	L_rw_ndef_t2t_read_next19
; p_cmd end address is: 32 (R8)
; cmd_size end address is: 4 (R1)
; rsp end address is: 28 (R7)
; p_rsp_size end address is: 36 (R9)
IT	AL
BAL	L_rw_ndef_t2t_read_next26
L_rw_ndef_t2t_read_next1:
;RW_NDEF_T2T.c,178 :: 		}
L_end_rw_ndef_t2t_read_next:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _rw_ndef_t2t_read_next
