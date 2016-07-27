_rw_ndef_t4t_reset:
;RW_NDEF_T4T.c,95 :: 		void rw_ndef_t4t_reset( void )
SUB	SP, SP, #4
;RW_NDEF_T4T.c,97 :: 		e_rw_ndef_t4t_state = INITIAL;
MOVS	R1, #0
MOVW	R0, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R0, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R1, [R0, #0]
;RW_NDEF_T4T.c,98 :: 		rw_ndef_t4t_ndef.p_record = ndef_buffer;
MOVW	R1, #lo_addr(_ndef_buffer+0)
MOVT	R1, #hi_addr(_ndef_buffer+0)
MOVW	R0, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+16)
MOVT	R0, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+16)
STR	R1, [R0, #0]
;RW_NDEF_T4T.c,99 :: 		}
L_end_rw_ndef_t4t_reset:
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t4t_reset
_rw_ndef_t4t_read_next:
;RW_NDEF_T4T.c,102 :: 		uint8_t *rsp, uint16_t *p_rsp_size )
; p_rsp_size start address is: 12 (R3)
; rsp start address is: 8 (R2)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R9, R0
UXTH	R10, R1
MOV	R8, R2
MOV	R7, R3
; p_rsp_size end address is: 12 (R3)
; rsp end address is: 8 (R2)
; cmd_size end address is: 4 (R1)
; p_cmd end address is: 0 (R0)
; p_cmd start address is: 36 (R9)
; cmd_size start address is: 40 (R10)
; rsp start address is: 32 (R8)
; p_rsp_size start address is: 28 (R7)
;RW_NDEF_T4T.c,105 :: 		*p_rsp_size = 0;
MOVS	R4, #0
STRH	R4, [R7, #0]
;RW_NDEF_T4T.c,107 :: 		switch( e_rw_ndef_t4t_state )
IT	AL
BAL	L_rw_ndef_t4t_read_next0
; p_cmd end address is: 36 (R9)
; cmd_size end address is: 40 (R10)
;RW_NDEF_T4T.c,109 :: 		case INITIAL:
L_rw_ndef_t4t_read_next2:
;RW_NDEF_T4T.c,111 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_APP_SELECT, sizeof( RW_NDEF_T4T_APP_SELECT ) );
MOVS	R2, #12
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_APP_SELECT+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_APP_SELECT+0)
MOV	R0, R8
; rsp end address is: 32 (R8)
BL	_memcpy+0
;RW_NDEF_T4T.c,112 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_APP_SELECT );
MOVS	R4, #12
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,113 :: 		e_rw_ndef_t4t_state = SELECTING_NDEF_APPLICATION20;
MOVS	R5, #1
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,114 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,116 :: 		case SELECTING_NDEF_APPLICATION20:
L_rw_ndef_t4t_read_next3:
;RW_NDEF_T4T.c,118 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
; cmd_size end address is: 40 (R10)
ADD	R4, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
;RW_NDEF_T4T.c,119 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,118 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,119 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_rw_ndef_t4t_read_next4
;RW_NDEF_T4T.c,122 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_CC_SELECT, sizeof( RW_NDEF_T4T_CC_SELECT ) );
MOVS	R2, #7
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_CC_SELECT+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_CC_SELECT+0)
MOV	R0, R8
; rsp end address is: 32 (R8)
BL	_memcpy+0
;RW_NDEF_T4T.c,123 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_CC_SELECT );
MOVS	R4, #7
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,124 :: 		e_rw_ndef_t4t_state = SELECTING_CC;
MOVS	R5, #3
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,125 :: 		}
IT	AL
BAL	L_rw_ndef_t4t_read_next5
L_rw_ndef_t4t_read_next4:
;RW_NDEF_T4T.c,129 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_APP_SELECT, sizeof( RW_NDEF_T4T_APP_SELECT ) );
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
MOVS	R2, #12
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_APP_SELECT+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_APP_SELECT+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T4T.c,130 :: 		rsp[11] = 0x0;
ADD	R5, R8, #11
; rsp end address is: 32 (R8)
MOVS	R4, #0
STRB	R4, [R5, #0]
;RW_NDEF_T4T.c,131 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_APP_SELECT );
MOVS	R4, #12
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,132 :: 		e_rw_ndef_t4t_state = SELECTING_NDEF_APPLICATION10;
MOVS	R5, #2
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,133 :: 		}
L_rw_ndef_t4t_read_next5:
;RW_NDEF_T4T.c,134 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,136 :: 		case SELECTING_NDEF_APPLICATION10:
L_rw_ndef_t4t_read_next6:
;RW_NDEF_T4T.c,138 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
; cmd_size end address is: 40 (R10)
ADD	R4, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
;RW_NDEF_T4T.c,139 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,138 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,139 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_rw_ndef_t4t_read_next7
;RW_NDEF_T4T.c,142 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_CC_SELECT, sizeof( RW_NDEF_T4T_CC_SELECT ) );
MOVS	R2, #7
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_CC_SELECT+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_CC_SELECT+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T4T.c,143 :: 		rsp[3] = 0x00;
ADD	R5, R8, #3
; rsp end address is: 32 (R8)
MOVS	R4, #0
STRB	R4, [R5, #0]
;RW_NDEF_T4T.c,144 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_CC_SELECT );
MOVS	R4, #7
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,145 :: 		e_rw_ndef_t4t_state = SELECTING_CC;
MOVS	R5, #3
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,146 :: 		}
L_rw_ndef_t4t_read_next7:
;RW_NDEF_T4T.c,147 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,149 :: 		case SELECTING_CC:
L_rw_ndef_t4t_read_next8:
;RW_NDEF_T4T.c,151 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
; cmd_size end address is: 40 (R10)
ADD	R4, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
;RW_NDEF_T4T.c,152 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,151 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,152 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_rw_ndef_t4t_read_next9
;RW_NDEF_T4T.c,155 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
MOVS	R2, #5
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOV	R0, R8
; rsp end address is: 32 (R8)
BL	_memcpy+0
;RW_NDEF_T4T.c,156 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_READ );
MOVS	R4, #5
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,157 :: 		e_rw_ndef_t4t_state = READING_CC;
MOVS	R5, #4
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,158 :: 		}
L_rw_ndef_t4t_read_next9:
;RW_NDEF_T4T.c,159 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,161 :: 		case READING_CC:
L_rw_ndef_t4t_read_next10:
;RW_NDEF_T4T.c,163 :: 		if ( ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
ADD	R4, R9, R4, LSL #0
;RW_NDEF_T4T.c,164 :: 		sizeof( RW_NDEF_T4T_OK ) ) ) && ( cmd_size == 15 + 2 ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,163 :: 		if ( ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,164 :: 		sizeof( RW_NDEF_T4T_OK ) ) ) && ( cmd_size == 15 + 2 ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L__rw_ndef_t4t_read_next33
CMP	R10, #17
IT	NE
BNE	L__rw_ndef_t4t_read_next32
; cmd_size end address is: 40 (R10)
L__rw_ndef_t4t_read_next31:
;RW_NDEF_T4T.c,167 :: 		rw_ndef_t4t_ndef.mapping_version = p_cmd[2];
ADD	R4, R9, #2
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,168 :: 		rw_ndef_t4t_ndef.mle = ( p_cmd[3] << 8 ) + p_cmd[4];
ADD	R4, R9, #3
LDRB	R4, [R4, #0]
LSLS	R5, R4, #8
UXTH	R5, R5
ADD	R4, R9, #4
LDRB	R4, [R4, #0]
ADDS	R5, R5, R4
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
STRH	R5, [R4, #0]
;RW_NDEF_T4T.c,169 :: 		rw_ndef_t4t_ndef.mlc = ( p_cmd[5] << 8 ) + p_cmd[6];
ADD	R4, R9, #5
LDRB	R4, [R4, #0]
LSLS	R5, R4, #8
UXTH	R5, R5
ADD	R4, R9, #6
LDRB	R4, [R4, #0]
ADDS	R5, R5, R4
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+4)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+4)
STRH	R5, [R4, #0]
;RW_NDEF_T4T.c,170 :: 		rw_ndef_t4t_ndef.file_id[0] = p_cmd[9];
ADD	R4, R9, #9
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+6)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+6)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,171 :: 		rw_ndef_t4t_ndef.file_id[1] = p_cmd[10];
ADD	R4, R9, #10
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+7)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+7)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,172 :: 		rw_ndef_t4t_ndef.max_ndef_file_size = ( p_cmd[11] << 8 ) + p_cmd[12];
ADD	R4, R9, #11
LDRB	R4, [R4, #0]
LSLS	R5, R4, #8
UXTH	R5, R5
ADD	R4, R9, #12
LDRB	R4, [R4, #0]
ADDS	R5, R5, R4
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+8)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+8)
STRH	R5, [R4, #0]
;RW_NDEF_T4T.c,173 :: 		rw_ndef_t4t_ndef.rd_access = p_cmd[13];
ADD	R4, R9, #13
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+10)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+10)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,174 :: 		rw_ndef_t4t_ndef.wr_access = p_cmd[14];
ADD	R4, R9, #14
; p_cmd end address is: 36 (R9)
LDRB	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+11)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+11)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,177 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_NDEF_SELECT, sizeof( RW_NDEF_T4T_NDEF_SELECT ) );
MOVS	R2, #7
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_NDEF_SELECT+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_NDEF_SELECT+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T4T.c,178 :: 		if ( rw_ndef_t4t_ndef.mapping_version == 0x10 ) rsp[3] = 0x00;
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+0)
LDRB	R4, [R4, #0]
CMP	R4, #16
IT	NE
BNE	L_rw_ndef_t4t_read_next14
ADD	R5, R8, #3
MOVS	R4, #0
STRB	R4, [R5, #0]
L_rw_ndef_t4t_read_next14:
;RW_NDEF_T4T.c,179 :: 		rsp[5] = rw_ndef_t4t_ndef.file_id[0];
ADD	R5, R8, #5
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+6)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+6)
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T4T.c,180 :: 		rsp[6] = rw_ndef_t4t_ndef.file_id[1];
ADD	R5, R8, #6
; rsp end address is: 32 (R8)
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+7)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+7)
LDRB	R4, [R4, #0]
STRB	R4, [R5, #0]
;RW_NDEF_T4T.c,181 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_NDEF_SELECT );
MOVS	R4, #7
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,182 :: 		e_rw_ndef_t4t_state = SELECTING_NDEF;
MOVS	R5, #5
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,164 :: 		sizeof( RW_NDEF_T4T_OK ) ) ) && ( cmd_size == 15 + 2 ) )
L__rw_ndef_t4t_read_next33:
L__rw_ndef_t4t_read_next32:
;RW_NDEF_T4T.c,184 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,186 :: 		case SELECTING_NDEF:
L_rw_ndef_t4t_read_next15:
;RW_NDEF_T4T.c,188 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
; cmd_size end address is: 40 (R10)
ADD	R4, R9, R4, LSL #0
; p_cmd end address is: 36 (R9)
;RW_NDEF_T4T.c,189 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,188 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,189 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_rw_ndef_t4t_read_next16
;RW_NDEF_T4T.c,192 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
MOVS	R2, #5
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T4T.c,193 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_READ );
MOVS	R4, #5
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,194 :: 		rsp[4] = 2;
ADD	R5, R8, #4
; rsp end address is: 32 (R8)
MOVS	R4, #2
STRB	R4, [R5, #0]
;RW_NDEF_T4T.c,195 :: 		e_rw_ndef_t4t_state = READING_NDEF_SIZE;
MOVS	R5, #6
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,196 :: 		}
L_rw_ndef_t4t_read_next16:
;RW_NDEF_T4T.c,197 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,199 :: 		case READING_NDEF_SIZE:
L_rw_ndef_t4t_read_next17:
;RW_NDEF_T4T.c,201 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
; cmd_size end address is: 40 (R10)
ADD	R4, R9, R4, LSL #0
;RW_NDEF_T4T.c,202 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,201 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,202 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_rw_ndef_t4t_read_next18
;RW_NDEF_T4T.c,204 :: 		rw_ndef_t4t_ndef.record_size = ( p_cmd[0] << 8 ) + p_cmd[1];
LDRB	R4, [R9, #0]
LSLS	R5, R4, #8
UXTH	R5, R5
ADD	R4, R9, #1
; p_cmd end address is: 36 (R9)
LDRB	R4, [R4, #0]
ADDS	R5, R5, R4
UXTH	R5, R5
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
STRH	R5, [R4, #0]
;RW_NDEF_T4T.c,205 :: 		if( rw_ndef_t4t_ndef.record_size > RW_MAX_NDEF_FILE_SIZE )
CMP	R5, #240
IT	LS
BLS	L_rw_ndef_t4t_read_next19
; rsp end address is: 32 (R8)
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,208 :: 		}
IT	AL
BAL	L_rw_ndef_t4t_read_next20
L_rw_ndef_t4t_read_next19:
;RW_NDEF_T4T.c,211 :: 		rw_ndef_t4t_ndef.record_ptr = 0;
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
MOVS	R5, #0
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
STRH	R5, [R4, #0]
;RW_NDEF_T4T.c,214 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
MOVS	R2, #5
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T4T.c,215 :: 		rsp[3] =  2;
ADD	R5, R8, #3
MOVS	R4, #2
STRB	R4, [R5, #0]
;RW_NDEF_T4T.c,216 :: 		rsp[4] = ( rw_ndef_t4t_ndef.record_size > rw_ndef_t4t_ndef.mle - 1 ) ?
ADD	R6, R8, #4
; rsp end address is: 32 (R8)
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
LDRH	R4, [R4, #0]
SUBS	R5, R4, #1
UXTH	R5, R5
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
LDRH	R4, [R4, #0]
CMP	R4, R5
IT	LS
BLS	L_rw_ndef_t4t_read_next21
;RW_NDEF_T4T.c,217 :: 		rw_ndef_t4t_ndef.mle - 1 : ( uint8_t ) rw_ndef_t4t_ndef.record_size;
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
LDRH	R4, [R4, #0]
SUBS	R0, R4, #1
UXTH	R0, R0
; ?FLOC___rw_ndef_t4t_read_next?T133 start address is: 0 (R0)
; ?FLOC___rw_ndef_t4t_read_next?T133 end address is: 0 (R0)
IT	AL
BAL	L_rw_ndef_t4t_read_next22
L_rw_ndef_t4t_read_next21:
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
; ?FLOC___rw_ndef_t4t_read_next?T133 start address is: 0 (R0)
LDRB	R0, [R4, #0]
; ?FLOC___rw_ndef_t4t_read_next?T133 end address is: 0 (R0)
L_rw_ndef_t4t_read_next22:
; ?FLOC___rw_ndef_t4t_read_next?T133 start address is: 0 (R0)
STRB	R0, [R6, #0]
; ?FLOC___rw_ndef_t4t_read_next?T133 end address is: 0 (R0)
;RW_NDEF_T4T.c,218 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_READ );
MOVS	R4, #5
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,219 :: 		e_rw_ndef_t4t_state = READING_NDEF;
MOVS	R5, #7
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
STRB	R5, [R4, #0]
;RW_NDEF_T4T.c,220 :: 		}
L_rw_ndef_t4t_read_next20:
;RW_NDEF_T4T.c,221 :: 		}
L_rw_ndef_t4t_read_next18:
;RW_NDEF_T4T.c,222 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,224 :: 		case READING_NDEF:
L_rw_ndef_t4t_read_next23:
;RW_NDEF_T4T.c,226 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
SUB	R4, R10, #2
UXTH	R4, R4
ADD	R4, R9, R4, LSL #0
;RW_NDEF_T4T.c,227 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
MOVS	R2, #2
SXTH	R2, R2
;RW_NDEF_T4T.c,226 :: 		if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_OK+0)
MOV	R0, R4
;RW_NDEF_T4T.c,227 :: 		sizeof( RW_NDEF_T4T_OK ) ) )
BL	_memcmp+0
CMP	R0, #0
IT	NE
BNE	L_rw_ndef_t4t_read_next24
;RW_NDEF_T4T.c,230 :: 		cmd_size - 2 );
SUB	R6, R10, #2
;RW_NDEF_T4T.c,229 :: 		memcpy( &rw_ndef_t4t_ndef.p_record[rw_ndef_t4t_ndef.record_ptr], p_cmd,
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+16)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+16)
LDR	R4, [R4, #0]
ADDS	R4, R4, R5
;RW_NDEF_T4T.c,230 :: 		cmd_size - 2 );
SXTH	R2, R6
;RW_NDEF_T4T.c,229 :: 		memcpy( &rw_ndef_t4t_ndef.p_record[rw_ndef_t4t_ndef.record_ptr], p_cmd,
MOV	R1, R9
; p_cmd end address is: 36 (R9)
MOV	R0, R4
;RW_NDEF_T4T.c,230 :: 		cmd_size - 2 );
BL	_memcpy+0
;RW_NDEF_T4T.c,231 :: 		rw_ndef_t4t_ndef.record_ptr += cmd_size - 2;
SUB	R5, R10, #2
UXTH	R5, R5
; cmd_size end address is: 40 (R10)
MOVW	R6, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
MOVT	R6, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
LDRH	R4, [R6, #0]
ADDS	R5, R4, R5
UXTH	R5, R5
STRH	R5, [R6, #0]
;RW_NDEF_T4T.c,234 :: 		if ( rw_ndef_t4t_ndef.record_ptr == rw_ndef_t4t_ndef.record_size )
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
LDRH	R4, [R4, #0]
CMP	R5, R4
IT	NE
BNE	L_rw_ndef_t4t_read_next25
; rsp end address is: 32 (R8)
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,237 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t4t_ndef.p_record,
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t4t_read_next26
;RW_NDEF_T4T.c,238 :: 		rw_ndef_t4t_ndef.record_size );
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
LDRH	R5, [R4, #0]
;RW_NDEF_T4T.c,237 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t4t_ndef.p_record,
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+16)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+16)
LDR	R4, [R4, #0]
;RW_NDEF_T4T.c,238 :: 		rw_ndef_t4t_ndef.record_size );
UXTH	R1, R5
;RW_NDEF_T4T.c,237 :: 		if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t4t_ndef.p_record,
MOV	R0, R4
;RW_NDEF_T4T.c,238 :: 		rw_ndef_t4t_ndef.record_size );
MOVW	R4, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R4, #hi_addr(_p_rw_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_t4t_read_next26:
;RW_NDEF_T4T.c,239 :: 		}
IT	AL
BAL	L_rw_ndef_t4t_read_next27
L_rw_ndef_t4t_read_next25:
;RW_NDEF_T4T.c,243 :: 		memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
MOVS	R2, #5
SXTH	R2, R2
MOVW	R1, #lo_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOVT	R1, #hi_addr(RW_NDEF_T4T_RW_NDEF_T4T_READ+0)
MOV	R0, R8
BL	_memcpy+0
;RW_NDEF_T4T.c,244 :: 		rsp[3] =  rw_ndef_t4t_ndef.record_ptr + 2;
ADD	R6, R8, #3
MOVW	R5, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
MOVT	R5, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
LDRH	R4, [R5, #0]
ADDS	R4, R4, #2
STRB	R4, [R6, #0]
;RW_NDEF_T4T.c,245 :: 		rsp[4] = ( ( rw_ndef_t4t_ndef.record_size - rw_ndef_t4t_ndef.record_ptr ) >
ADD	R6, R8, #4
; rsp end address is: 32 (R8)
MOV	R4, R5
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
LDRH	R4, [R4, #0]
SUB	R5, R4, R5
UXTH	R5, R5
;RW_NDEF_T4T.c,246 :: 		rw_ndef_t4t_ndef.mle - 1 ) ? rw_ndef_t4t_ndef.mle - 1 : ( uint8_t ) (
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
LDRH	R4, [R4, #0]
SUBS	R4, R4, #1
UXTH	R4, R4
CMP	R5, R4
IT	LS
BLS	L_rw_ndef_t4t_read_next28
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+2)
LDRH	R4, [R4, #0]
SUBS	R0, R4, #1
UXTH	R0, R0
; ?FLOC___rw_ndef_t4t_read_next?T164 start address is: 0 (R0)
; ?FLOC___rw_ndef_t4t_read_next?T164 end address is: 0 (R0)
IT	AL
BAL	L_rw_ndef_t4t_read_next29
L_rw_ndef_t4t_read_next28:
;RW_NDEF_T4T.c,247 :: 		rw_ndef_t4t_ndef.record_size - rw_ndef_t4t_ndef.record_ptr );
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+12)
LDRH	R5, [R4, #0]
MOVW	R4, #lo_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
MOVT	R4, #hi_addr(RW_NDEF_T4T_rw_ndef_t4t_ndef+14)
LDRH	R4, [R4, #0]
SUB	R0, R4, R5
UXTH	R0, R0
; ?FLOC___rw_ndef_t4t_read_next?T164 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___rw_ndef_t4t_read_next?T164 end address is: 0 (R0)
L_rw_ndef_t4t_read_next29:
; ?FLOC___rw_ndef_t4t_read_next?T164 start address is: 0 (R0)
STRB	R0, [R6, #0]
; ?FLOC___rw_ndef_t4t_read_next?T164 end address is: 0 (R0)
;RW_NDEF_T4T.c,248 :: 		*p_rsp_size = sizeof( RW_NDEF_T4T_READ );
MOVS	R4, #5
STRH	R4, [R7, #0]
; p_rsp_size end address is: 28 (R7)
;RW_NDEF_T4T.c,249 :: 		}
L_rw_ndef_t4t_read_next27:
;RW_NDEF_T4T.c,250 :: 		}
L_rw_ndef_t4t_read_next24:
;RW_NDEF_T4T.c,251 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,253 :: 		default:
L_rw_ndef_t4t_read_next30:
;RW_NDEF_T4T.c,254 :: 		break;
IT	AL
BAL	L_rw_ndef_t4t_read_next1
;RW_NDEF_T4T.c,255 :: 		}
L_rw_ndef_t4t_read_next0:
; p_rsp_size start address is: 28 (R7)
; rsp start address is: 32 (R8)
; cmd_size start address is: 40 (R10)
; p_cmd start address is: 36 (R9)
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_t4t_read_next2
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #1
IT	EQ
BEQ	L_rw_ndef_t4t_read_next3
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #2
IT	EQ
BEQ	L_rw_ndef_t4t_read_next6
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #3
IT	EQ
BEQ	L_rw_ndef_t4t_read_next8
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #4
IT	EQ
BEQ	L_rw_ndef_t4t_read_next10
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #5
IT	EQ
BEQ	L_rw_ndef_t4t_read_next15
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #6
IT	EQ
BEQ	L_rw_ndef_t4t_read_next17
MOVW	R4, #lo_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
MOVT	R4, #hi_addr(RW_NDEF_T4T_e_rw_ndef_t4t_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #7
IT	EQ
BEQ	L_rw_ndef_t4t_read_next23
; p_cmd end address is: 36 (R9)
; cmd_size end address is: 40 (R10)
; rsp end address is: 32 (R8)
; p_rsp_size end address is: 28 (R7)
IT	AL
BAL	L_rw_ndef_t4t_read_next30
L_rw_ndef_t4t_read_next1:
;RW_NDEF_T4T.c,256 :: 		}
L_end_rw_ndef_t4t_read_next:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_t4t_read_next
