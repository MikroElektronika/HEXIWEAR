P2P_NDEF_parse_llcp:
;P2P_NDEF.c,117 :: 		p2p_ndef_llcp_header_t *p_llcp_header )
; p_llcp_header start address is: 4 (R1)
; p_buf start address is: 0 (R0)
SUB	SP, SP, #4
; p_llcp_header end address is: 4 (R1)
; p_buf end address is: 0 (R0)
; p_buf start address is: 0 (R0)
; p_llcp_header start address is: 4 (R1)
;P2P_NDEF.c,119 :: 		p_llcp_header->dsap = p_buf[0] >> 2;
LDRB	R2, [R0, #0]
LSRS	R2, R2, #2
STRB	R2, [R1, #0]
;P2P_NDEF.c,120 :: 		p_llcp_header->pdu = ( ( p_buf[0] & 3 ) << 2 ) + ( p_buf[1] >> 6 );
ADDS	R4, R1, #1
LDRB	R2, [R0, #0]
AND	R2, R2, #3
UXTB	R2, R2
LSLS	R3, R2, #2
UXTH	R3, R3
ADDS	R2, R0, #1
LDRB	R2, [R2, #0]
LSRS	R2, R2, #6
UXTB	R2, R2
ADDS	R2, R3, R2
STRB	R2, [R4, #0]
;P2P_NDEF.c,121 :: 		p_llcp_header->ssap = p_buf[1] & 0x3F;
ADDS	R3, R1, #2
; p_llcp_header end address is: 4 (R1)
ADDS	R2, R0, #1
; p_buf end address is: 0 (R0)
LDRB	R2, [R2, #0]
AND	R2, R2, #63
STRB	R2, [R3, #0]
;P2P_NDEF.c,122 :: 		}
L_end_parse_llcp:
ADD	SP, SP, #4
BX	LR
; end of P2P_NDEF_parse_llcp
P2P_NDEF_fill_llcp:
;P2P_NDEF.c,124 :: 		static void fill_llcp( p2p_ndef_llcp_header_t llcp_header, uint8_t *p_buf )
; p_buf start address is: 0 (R0)
SUB	SP, SP, #4
; p_buf end address is: 0 (R0)
; p_buf start address is: 0 (R0)
;P2P_NDEF.c,126 :: 		p_buf[0] = ( llcp_header.ssap << 2 ) + ( ( llcp_header.pdu >> 2 ) & 3 );
LDRB	R1, [SP, #6]
LSLS	R2, R1, #2
UXTH	R2, R2
LDRB	R1, [SP, #5]
LSRS	R1, R1, #2
UXTB	R1, R1
AND	R1, R1, #3
UXTB	R1, R1
ADDS	R1, R2, R1
STRB	R1, [R0, #0]
;P2P_NDEF.c,127 :: 		p_buf[1] = ( llcp_header.pdu << 6 ) + llcp_header.dsap;
ADDS	R3, R0, #1
; p_buf end address is: 0 (R0)
LDRB	R1, [SP, #5]
LSLS	R2, R1, #6
UXTH	R2, R2
LDRB	R1, [SP, #4]
ADDS	R1, R2, R1
STRB	R1, [R3, #0]
;P2P_NDEF.c,128 :: 		}
L_end_fill_llcp:
ADD	SP, SP, #4
BX	LR
; end of P2P_NDEF_fill_llcp
_p2p_ndef_set_record:
;P2P_NDEF.c,131 :: 		uint16_t record_size, void *cb )
; cb start address is: 8 (R2)
; record_size start address is: 4 (R1)
; p_record start address is: 0 (R0)
SUB	SP, SP, #4
; cb end address is: 8 (R2)
; record_size end address is: 4 (R1)
; p_record end address is: 0 (R0)
; p_record start address is: 0 (R0)
; record_size start address is: 4 (R1)
; cb start address is: 8 (R2)
;P2P_NDEF.c,133 :: 		if ( record_size <= P2P_NDEF_MAX_NDEF_RECORD_SIZE )
CMP	R1, #240
IT	HI
BHI	L_p2p_ndef_set_record0
;P2P_NDEF.c,135 :: 		p_ndef_record = p_record;
MOVW	R3, #lo_addr(P2P_NDEF_p_ndef_record+0)
MOVT	R3, #hi_addr(P2P_NDEF_p_ndef_record+0)
STR	R0, [R3, #0]
; p_record end address is: 0 (R0)
;P2P_NDEF.c,136 :: 		ndef_record_size = record_size;
MOVW	R3, #lo_addr(P2P_NDEF_ndef_record_size+0)
MOVT	R3, #hi_addr(P2P_NDEF_ndef_record_size+0)
STRH	R1, [R3, #0]
; record_size end address is: 4 (R1)
;P2P_NDEF.c,137 :: 		p_p2p_ndef_push_cb = ( p2p_ndef_callback_t * ) cb;
MOVW	R3, #lo_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
MOVT	R3, #hi_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
STR	R2, [R3, #0]
; cb end address is: 8 (R2)
;P2P_NDEF.c,138 :: 		return true;
MOVS	R0, #1
IT	AL
BAL	L_end_p2p_ndef_set_record
;P2P_NDEF.c,139 :: 		}
L_p2p_ndef_set_record0:
;P2P_NDEF.c,142 :: 		ndef_record_size = 0;
MOVS	R4, #0
MOVW	R3, #lo_addr(P2P_NDEF_ndef_record_size+0)
MOVT	R3, #hi_addr(P2P_NDEF_ndef_record_size+0)
STRH	R4, [R3, #0]
;P2P_NDEF.c,143 :: 		p_p2p_ndef_push_cb = NULL;
MOVS	R4, #0
MOVW	R3, #lo_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
MOVT	R3, #hi_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
STR	R4, [R3, #0]
;P2P_NDEF.c,144 :: 		return false;
MOVS	R0, #0
;P2P_NDEF.c,146 :: 		}
L_end_p2p_ndef_set_record:
ADD	SP, SP, #4
BX	LR
; end of _p2p_ndef_set_record
_p2p_ndef_register_pull_callback:
;P2P_NDEF.c,148 :: 		void p2p_ndef_register_pull_callback( void *p_cb )
; p_cb start address is: 0 (R0)
SUB	SP, SP, #4
; p_cb end address is: 0 (R0)
; p_cb start address is: 0 (R0)
;P2P_NDEF.c,150 :: 		p_p2p_ndef_pull_cb = ( p2p_ndef_callback_t * ) p_cb;
MOVW	R1, #lo_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
MOVT	R1, #hi_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
STR	R0, [R1, #0]
; p_cb end address is: 0 (R0)
;P2P_NDEF.c,151 :: 		}
L_end_p2p_ndef_register_pull_callback:
ADD	SP, SP, #4
BX	LR
; end of _p2p_ndef_register_pull_callback
_p2p_ndef_reset:
;P2P_NDEF.c,153 :: 		void p2p_ndef_reset( void )
SUB	SP, SP, #4
;P2P_NDEF.c,155 :: 		if ( ndef_record_size != 0 )
MOVW	R0, #lo_addr(P2P_NDEF_ndef_record_size+0)
MOVT	R0, #hi_addr(P2P_NDEF_ndef_record_size+0)
LDRH	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_p2p_ndef_reset2
;P2P_NDEF.c,156 :: 		e_p2p_snep_client_state = INITIAL;
MOVS	R1, #1
MOVW	R0, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R0, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R1, [R0, #0]
IT	AL
BAL	L_p2p_ndef_reset3
L_p2p_ndef_reset2:
;P2P_NDEF.c,158 :: 		e_p2p_snep_client_state = IDLE_STATE;
MOVS	R1, #0
MOVW	R0, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R0, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R1, [R0, #0]
L_p2p_ndef_reset3:
;P2P_NDEF.c,159 :: 		}
L_end_p2p_ndef_reset:
ADD	SP, SP, #4
BX	LR
; end of _p2p_ndef_reset
_p2p_ndef_next:
;P2P_NDEF.c,162 :: 		uint8_t *p_rsp, uint16_t *p_rsp_size )
; p_cmd start address is: 0 (R0)
SUB	SP, SP, #20
STR	LR, [SP, #0]
MOV	R6, R0
STR	R2, [SP, #12]
STR	R3, [SP, #16]
; p_cmd end address is: 0 (R0)
; p_cmd start address is: 24 (R6)
;P2P_NDEF.c,167 :: 		*p_rsp_size = 0;
MOVS	R5, #0
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,169 :: 		parse_llcp( p_cmd, &llcp_header );
ADD	R4, SP, #8
MOV	R1, R4
MOV	R0, R6
BL	P2P_NDEF_parse_llcp+0
;P2P_NDEF.c,171 :: 		switch ( llcp_header.pdu )
IT	AL
BAL	L_p2p_ndef_next4
; p_cmd end address is: 24 (R6)
;P2P_NDEF.c,173 :: 		case CONNECT:
L_p2p_ndef_next6:
;P2P_NDEF.c,175 :: 		if ( llcp_header.dsap == SAP_SNEP )
LDRB	R4, [SP, #8]
CMP	R4, #4
IT	NE
BNE	L_p2p_ndef_next7
;P2P_NDEF.c,178 :: 		if( p_p2p_ndef_pull_cb != NULL )
MOVW	R4, #lo_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_p2p_ndef_next8
;P2P_NDEF.c,180 :: 		llcp_header.pdu = CC;
MOVS	R4, #6
STRB	R4, [SP, #9]
;P2P_NDEF.c,181 :: 		fill_llcp( llcp_header, p_rsp );
LDR	R0, [SP, #12]
SUB	SP, SP, #4
ADD	R12, SP, #12
ADD	R11, SP, #0
ADD	R10, R11, #3
BL	___CC2DW+0
BL	P2P_NDEF_fill_llcp+0
ADD	SP, SP, #4
;P2P_NDEF.c,182 :: 		*p_rsp_size = 2;
MOVS	R5, #2
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,183 :: 		}
L_p2p_ndef_next8:
;P2P_NDEF.c,184 :: 		} else {
IT	AL
BAL	L_p2p_ndef_next9
L_p2p_ndef_next7:
;P2P_NDEF.c,186 :: 		llcp_header.pdu = DM;
MOVS	R4, #7
STRB	R4, [SP, #9]
;P2P_NDEF.c,187 :: 		fill_llcp( llcp_header, p_rsp );
LDR	R0, [SP, #12]
SUB	SP, SP, #4
ADD	R12, SP, #12
ADD	R11, SP, #0
ADD	R10, R11, #3
BL	___CC2DW+0
BL	P2P_NDEF_fill_llcp+0
ADD	SP, SP, #4
;P2P_NDEF.c,188 :: 		*p_rsp_size = 2;
MOVS	R5, #2
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,189 :: 		}
L_p2p_ndef_next9:
;P2P_NDEF.c,190 :: 		break;
IT	AL
BAL	L_p2p_ndef_next5
;P2P_NDEF.c,191 :: 		case I:
L_p2p_ndef_next10:
;P2P_NDEF.c,193 :: 		if ( ( p_cmd[3] == SNEP_VER10 ) && ( p_cmd[4] == SNEP_PUT ) )
; p_cmd start address is: 24 (R6)
ADDS	R4, R6, #3
LDRB	R4, [R4, #0]
CMP	R4, #16
IT	NE
BNE	L__p2p_ndef_next29
ADDS	R4, R6, #4
LDRB	R4, [R4, #0]
CMP	R4, #2
IT	NE
BNE	L__p2p_ndef_next28
L__p2p_ndef_next27:
;P2P_NDEF.c,196 :: 		if( p_p2p_ndef_pull_cb != NULL ) p_p2p_ndef_pull_cb( &p_cmd[9], p_cmd[8] );
MOVW	R4, #lo_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_p2p_ndef_next14
ADDW	R4, R6, #8
LDRB	R4, [R4, #0]
UXTB	R5, R4
ADDW	R4, R6, #9
STR	R6, [SP, #4]
UXTH	R1, R5
MOV	R0, R4
MOVW	R4, #lo_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_p2p_ndef_pull_cb+0)
LDR	R4, [R4, #0]
BLX	R4
LDR	R6, [SP, #4]
L_p2p_ndef_next14:
;P2P_NDEF.c,199 :: 		llcp_header.pdu = I;
MOVS	R4, #12
STRB	R4, [SP, #9]
;P2P_NDEF.c,200 :: 		fill_llcp( llcp_header, p_rsp );
LDR	R0, [SP, #12]
SUB	SP, SP, #4
ADD	R12, SP, #12
ADD	R11, SP, #0
ADD	R10, R11, #3
BL	___CC2DW+0
BL	P2P_NDEF_fill_llcp+0
ADD	SP, SP, #4
;P2P_NDEF.c,201 :: 		p_rsp[2] = ( p_cmd[2] >> 4 ) + 1; // N(R)
LDR	R4, [SP, #12]
ADDS	R5, R4, #2
ADDS	R4, R6, #2
; p_cmd end address is: 24 (R6)
LDRB	R4, [R4, #0]
LSRS	R4, R4, #4
UXTB	R4, R4
ADDS	R4, R4, #1
STRB	R4, [R5, #0]
;P2P_NDEF.c,202 :: 		memcpy( &p_rsp[3], ( uint8_t * )SNEP_PUT_SUCCESS, sizeof( SNEP_PUT_SUCCESS ) );
LDR	R4, [SP, #12]
ADDS	R4, R4, #3
MOVS	R2, #6
SXTH	R2, R2
MOVW	R1, #lo_addr(P2P_NDEF_SNEP_PUT_SUCCESS+0)
MOVT	R1, #hi_addr(P2P_NDEF_SNEP_PUT_SUCCESS+0)
MOV	R0, R4
BL	_memcpy+0
;P2P_NDEF.c,203 :: 		*p_rsp_size = 9;
MOVS	R5, #9
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,193 :: 		if ( ( p_cmd[3] == SNEP_VER10 ) && ( p_cmd[4] == SNEP_PUT ) )
L__p2p_ndef_next29:
L__p2p_ndef_next28:
;P2P_NDEF.c,205 :: 		break;
IT	AL
BAL	L_p2p_ndef_next5
;P2P_NDEF.c,206 :: 		case CC:
L_p2p_ndef_next15:
;P2P_NDEF.c,208 :: 		e_p2p_snep_client_state = SNEP_CLIENT_CONNECTED;
MOVS	R5, #5
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R5, [R4, #0]
;P2P_NDEF.c,209 :: 		break;
IT	AL
BAL	L_p2p_ndef_next5
;P2P_NDEF.c,210 :: 		default:
L_p2p_ndef_next16:
;P2P_NDEF.c,211 :: 		break;
IT	AL
BAL	L_p2p_ndef_next5
;P2P_NDEF.c,213 :: 		}
L_p2p_ndef_next4:
; p_cmd start address is: 24 (R6)
LDRB	R4, [SP, #9]
CMP	R4, #4
IT	EQ
BEQ	L_p2p_ndef_next6
LDRB	R4, [SP, #9]
CMP	R4, #12
IT	EQ
BEQ	L_p2p_ndef_next10
; p_cmd end address is: 24 (R6)
LDRB	R4, [SP, #9]
CMP	R4, #6
IT	EQ
BEQ	L_p2p_ndef_next15
IT	AL
BAL	L_p2p_ndef_next16
L_p2p_ndef_next5:
;P2P_NDEF.c,216 :: 		if( *p_rsp_size == 0 )
LDR	R4, [SP, #16]
LDRH	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L_p2p_ndef_next17
;P2P_NDEF.c,218 :: 		switch( e_p2p_snep_client_state )
IT	AL
BAL	L_p2p_ndef_next18
;P2P_NDEF.c,220 :: 		case INITIATE_PUSH:
L_p2p_ndef_next20:
;P2P_NDEF.c,221 :: 		memcpy( p_rsp, ( uint8_t * )LLCP_CONNECT_SNEP, sizeof( LLCP_CONNECT_SNEP ) );
MOVS	R2, #2
SXTH	R2, R2
MOVW	R1, #lo_addr(P2P_NDEF_LLCP_CONNECT_SNEP+0)
MOVT	R1, #hi_addr(P2P_NDEF_LLCP_CONNECT_SNEP+0)
LDR	R0, [SP, #12]
BL	_memcpy+0
;P2P_NDEF.c,222 :: 		*p_rsp_size = sizeof( LLCP_CONNECT_SNEP );
MOVS	R5, #2
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,223 :: 		e_p2p_snep_client_state = SNEP_CLIENT_CONNECTING;
MOVS	R5, #4
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R5, [R4, #0]
;P2P_NDEF.c,224 :: 		break;
IT	AL
BAL	L_p2p_ndef_next19
;P2P_NDEF.c,226 :: 		case SNEP_CLIENT_CONNECTED:
L_p2p_ndef_next21:
;P2P_NDEF.c,227 :: 		llcp_header.pdu = I;
MOVS	R4, #12
STRB	R4, [SP, #9]
;P2P_NDEF.c,228 :: 		fill_llcp( llcp_header, p_rsp );
LDR	R0, [SP, #12]
SUB	SP, SP, #4
ADD	R12, SP, #12
ADD	R11, SP, #0
ADD	R10, R11, #3
BL	___CC2DW+0
BL	P2P_NDEF_fill_llcp+0
ADD	SP, SP, #4
;P2P_NDEF.c,229 :: 		p_rsp[2] = 0; // N(R)
LDR	R4, [SP, #12]
ADDS	R5, R4, #2
MOVS	R4, #0
STRB	R4, [R5, #0]
;P2P_NDEF.c,230 :: 		p_rsp[3] = SNEP_VER10;
LDR	R4, [SP, #12]
ADDS	R5, R4, #3
MOVS	R4, #16
STRB	R4, [R5, #0]
;P2P_NDEF.c,231 :: 		p_rsp[4] = SNEP_PUT;
LDR	R4, [SP, #12]
ADDS	R5, R4, #4
MOVS	R4, #2
STRB	R4, [R5, #0]
;P2P_NDEF.c,232 :: 		p_rsp[5] = 0;
LDR	R4, [SP, #12]
ADDS	R5, R4, #5
MOVS	R4, #0
STRB	R4, [R5, #0]
;P2P_NDEF.c,233 :: 		p_rsp[6] = 0;
LDR	R4, [SP, #12]
ADDS	R5, R4, #6
MOVS	R4, #0
STRB	R4, [R5, #0]
;P2P_NDEF.c,234 :: 		p_rsp[7] = 0;
LDR	R4, [SP, #12]
ADDS	R5, R4, #7
MOVS	R4, #0
STRB	R4, [R5, #0]
;P2P_NDEF.c,235 :: 		p_rsp[8] = ndef_record_size;
LDR	R4, [SP, #12]
ADDW	R6, R4, #8
MOVW	R5, #lo_addr(P2P_NDEF_ndef_record_size+0)
MOVT	R5, #hi_addr(P2P_NDEF_ndef_record_size+0)
LDRH	R4, [R5, #0]
STRB	R4, [R6, #0]
;P2P_NDEF.c,236 :: 		memcpy( &p_rsp[9], p_ndef_record, ndef_record_size );
MOV	R4, R5
LDRH	R6, [R4, #0]
MOVW	R4, #lo_addr(P2P_NDEF_p_ndef_record+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_ndef_record+0)
LDR	R5, [R4, #0]
LDR	R4, [SP, #12]
ADDS	R4, #9
SXTH	R2, R6
MOV	R1, R5
MOV	R0, R4
BL	_memcpy+0
;P2P_NDEF.c,237 :: 		*p_rsp_size = 9 + ndef_record_size;
MOVW	R4, #lo_addr(P2P_NDEF_ndef_record_size+0)
MOVT	R4, #hi_addr(P2P_NDEF_ndef_record_size+0)
LDRH	R4, [R4, #0]
ADDW	R5, R4, #9
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,238 :: 		e_p2p_snep_client_state = NDEF_MSG_SENT;
MOVS	R5, #6
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R5, [R4, #0]
;P2P_NDEF.c,240 :: 		if( p_p2p_ndef_push_cb != NULL )
MOVW	R4, #lo_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_p2p_ndef_next22
;P2P_NDEF.c,242 :: 		ndef_record_size );
MOVW	R4, #lo_addr(P2P_NDEF_ndef_record_size+0)
MOVT	R4, #hi_addr(P2P_NDEF_ndef_record_size+0)
LDRH	R5, [R4, #0]
;P2P_NDEF.c,241 :: 		p_p2p_ndef_push_cb( p_ndef_record,
MOVW	R4, #lo_addr(P2P_NDEF_p_ndef_record+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_ndef_record+0)
LDR	R4, [R4, #0]
;P2P_NDEF.c,242 :: 		ndef_record_size );
UXTH	R1, R5
;P2P_NDEF.c,241 :: 		p_p2p_ndef_push_cb( p_ndef_record,
MOV	R0, R4
;P2P_NDEF.c,242 :: 		ndef_record_size );
MOVW	R4, #lo_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
MOVT	R4, #hi_addr(P2P_NDEF_p_p2p_ndef_push_cb+0)
LDR	R4, [R4, #0]
BLX	R4
L_p2p_ndef_next22:
;P2P_NDEF.c,243 :: 		break;
IT	AL
BAL	L_p2p_ndef_next19
;P2P_NDEF.c,244 :: 		case DELAYING_PUSH:
L_p2p_ndef_next23:
;P2P_NDEF.c,245 :: 		p2p_snep_client_delay_count++;
MOVW	R5, #lo_addr(P2P_NDEF_p2p_snep_client_delay_count+0)
MOVT	R5, #hi_addr(P2P_NDEF_p2p_snep_client_delay_count+0)
LDRH	R4, [R5, #0]
ADDS	R4, R4, #1
UXTH	R4, R4
STRH	R4, [R5, #0]
;P2P_NDEF.c,246 :: 		if( p2p_snep_client_delay_count == NDEF_PUSH_DELAY_COUNT )
CMP	R4, #1
IT	NE
BNE	L_p2p_ndef_next24
;P2P_NDEF.c,247 :: 		e_p2p_snep_client_state = INITIATE_PUSH;
MOVS	R5, #3
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R5, [R4, #0]
L_p2p_ndef_next24:
;P2P_NDEF.c,249 :: 		nfc_hal_delay( 1000 );
MOVW	R0, #1000
BL	_nfc_hal_delay+0
;P2P_NDEF.c,250 :: 		memcpy( p_rsp, ( uint8_t * )LLCP_SYMM, sizeof( LLCP_SYMM ) );
MOVS	R2, #2
SXTH	R2, R2
MOVW	R1, #lo_addr(P2P_NDEF_LLCP_SYMM+0)
MOVT	R1, #hi_addr(P2P_NDEF_LLCP_SYMM+0)
LDR	R0, [SP, #12]
BL	_memcpy+0
;P2P_NDEF.c,251 :: 		*p_rsp_size = sizeof( LLCP_SYMM );
MOVS	R5, #2
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,252 :: 		break;
IT	AL
BAL	L_p2p_ndef_next19
;P2P_NDEF.c,254 :: 		case INITIAL:
L_p2p_ndef_next25:
;P2P_NDEF.c,255 :: 		p2p_snep_client_delay_count = 0;
MOVS	R5, #0
MOVW	R4, #lo_addr(P2P_NDEF_p2p_snep_client_delay_count+0)
MOVT	R4, #hi_addr(P2P_NDEF_p2p_snep_client_delay_count+0)
STRH	R5, [R4, #0]
;P2P_NDEF.c,256 :: 		e_p2p_snep_client_state = DELAYING_PUSH;
MOVS	R5, #2
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
STRB	R5, [R4, #0]
;P2P_NDEF.c,257 :: 		default:
L_p2p_ndef_next26:
;P2P_NDEF.c,259 :: 		nfc_hal_delay ( SYMM_FREQ );
MOVW	R0, #500
BL	_nfc_hal_delay+0
;P2P_NDEF.c,260 :: 		memcpy( p_rsp, ( uint8_t * )LLCP_SYMM, sizeof( LLCP_SYMM ) );
MOVS	R2, #2
SXTH	R2, R2
MOVW	R1, #lo_addr(P2P_NDEF_LLCP_SYMM+0)
MOVT	R1, #hi_addr(P2P_NDEF_LLCP_SYMM+0)
LDR	R0, [SP, #12]
BL	_memcpy+0
;P2P_NDEF.c,261 :: 		*p_rsp_size = sizeof( LLCP_SYMM );
MOVS	R5, #2
LDR	R4, [SP, #16]
STRH	R5, [R4, #0]
;P2P_NDEF.c,262 :: 		break;
IT	AL
BAL	L_p2p_ndef_next19
;P2P_NDEF.c,263 :: 		}
L_p2p_ndef_next18:
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #3
IT	EQ
BEQ	L_p2p_ndef_next20
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #5
IT	EQ
BEQ	L_p2p_ndef_next21
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #2
IT	EQ
BEQ	L_p2p_ndef_next23
MOVW	R4, #lo_addr(P2P_NDEF_e_p2p_snep_client_state+0)
MOVT	R4, #hi_addr(P2P_NDEF_e_p2p_snep_client_state+0)
LDRB	R4, [R4, #0]
CMP	R4, #1
IT	EQ
BEQ	L_p2p_ndef_next25
IT	AL
BAL	L_p2p_ndef_next26
L_p2p_ndef_next19:
;P2P_NDEF.c,264 :: 		}
L_p2p_ndef_next17:
;P2P_NDEF.c,265 :: 		}
L_end_p2p_ndef_next:
LDR	LR, [SP, #0]
ADD	SP, SP, #20
BX	LR
; end of _p2p_ndef_next
