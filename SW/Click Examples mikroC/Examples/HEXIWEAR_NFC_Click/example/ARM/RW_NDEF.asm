_rw_ndef_register_pull_callback:
;RW_NDEF.c,60 :: 		void rw_ndef_register_pull_callback( void *p_cb )
; p_cb start address is: 0 (R0)
SUB	SP, SP, #4
; p_cb end address is: 0 (R0)
; p_cb start address is: 0 (R0)
;RW_NDEF.c,62 :: 		p_rw_ndef_pull_cb = ( rw_ndef_callback_t * ) p_cb;
MOVW	R1, #lo_addr(_p_rw_ndef_pull_cb+0)
MOVT	R1, #hi_addr(_p_rw_ndef_pull_cb+0)
STR	R0, [R1, #0]
; p_cb end address is: 0 (R0)
;RW_NDEF.c,63 :: 		}
L_end_rw_ndef_register_pull_callback:
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_register_pull_callback
_rw_ndef_reset:
;RW_NDEF.c,65 :: 		void rw_ndef_reset(uint8_t type )
; type start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; type end address is: 0 (R0)
; type start address is: 0 (R0)
;RW_NDEF.c,67 :: 		switch ( type )
IT	AL
BAL	L_rw_ndef_reset0
; type end address is: 0 (R0)
;RW_NDEF.c,69 :: 		case RW_NDEF_TYPE_T1T:
L_rw_ndef_reset2:
;RW_NDEF.c,70 :: 		rw_ndef_t1t_reset();
BL	_rw_ndef_t1t_reset+0
;RW_NDEF.c,71 :: 		p_read_fct = rw_ndef_t1t_read_next;
MOVW	R2, #lo_addr(_rw_ndef_t1t_read_next+0)
MOVT	R2, #hi_addr(_rw_ndef_t1t_read_next+0)
MOVW	R1, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R1, #hi_addr(RW_NDEF_p_read_fct+0)
STR	R2, [R1, #0]
;RW_NDEF.c,72 :: 		break;
IT	AL
BAL	L_rw_ndef_reset1
;RW_NDEF.c,73 :: 		case RW_NDEF_TYPE_T2T:
L_rw_ndef_reset3:
;RW_NDEF.c,74 :: 		rw_ndef_t2t_reset();
BL	_rw_ndef_t2t_reset+0
;RW_NDEF.c,75 :: 		p_read_fct = rw_ndef_t2t_read_next;
MOVW	R2, #lo_addr(_rw_ndef_t2t_read_next+0)
MOVT	R2, #hi_addr(_rw_ndef_t2t_read_next+0)
MOVW	R1, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R1, #hi_addr(RW_NDEF_p_read_fct+0)
STR	R2, [R1, #0]
;RW_NDEF.c,76 :: 		break;
IT	AL
BAL	L_rw_ndef_reset1
;RW_NDEF.c,77 :: 		case RW_NDEF_TYPE_T3T:
L_rw_ndef_reset4:
;RW_NDEF.c,78 :: 		rw_ndef_t3t_reset();
BL	_rw_ndef_t3t_reset+0
;RW_NDEF.c,79 :: 		p_read_fct = rw_ndef_t3t_read_next;
MOVW	R2, #lo_addr(_rw_ndef_t3t_read_next+0)
MOVT	R2, #hi_addr(_rw_ndef_t3t_read_next+0)
MOVW	R1, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R1, #hi_addr(RW_NDEF_p_read_fct+0)
STR	R2, [R1, #0]
;RW_NDEF.c,80 :: 		break;
IT	AL
BAL	L_rw_ndef_reset1
;RW_NDEF.c,81 :: 		case RW_NDEF_TYPE_T4T:
L_rw_ndef_reset5:
;RW_NDEF.c,82 :: 		rw_ndef_t4t_reset();
BL	_rw_ndef_t4t_reset+0
;RW_NDEF.c,83 :: 		p_read_fct = rw_ndef_t4t_read_next;
MOVW	R2, #lo_addr(_rw_ndef_t4t_read_next+0)
MOVT	R2, #hi_addr(_rw_ndef_t4t_read_next+0)
MOVW	R1, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R1, #hi_addr(RW_NDEF_p_read_fct+0)
STR	R2, [R1, #0]
;RW_NDEF.c,84 :: 		break;
IT	AL
BAL	L_rw_ndef_reset1
;RW_NDEF.c,85 :: 		default:
L_rw_ndef_reset6:
;RW_NDEF.c,86 :: 		p_read_fct = NULL;
MOVS	R2, #0
MOVW	R1, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R1, #hi_addr(RW_NDEF_p_read_fct+0)
STR	R2, [R1, #0]
;RW_NDEF.c,87 :: 		break;
IT	AL
BAL	L_rw_ndef_reset1
;RW_NDEF.c,88 :: 		}
L_rw_ndef_reset0:
; type start address is: 0 (R0)
CMP	R0, #1
IT	EQ
BEQ	L_rw_ndef_reset2
CMP	R0, #2
IT	EQ
BEQ	L_rw_ndef_reset3
CMP	R0, #3
IT	EQ
BEQ	L_rw_ndef_reset4
CMP	R0, #4
IT	EQ
BEQ	L_rw_ndef_reset5
; type end address is: 0 (R0)
IT	AL
BAL	L_rw_ndef_reset6
L_rw_ndef_reset1:
;RW_NDEF.c,89 :: 		}
L_end_rw_ndef_reset:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_reset
_rw_ndef_read_next:
;RW_NDEF.c,92 :: 		uint8_t *rsp, uint16_t *p_rsp_size )
; p_rsp_size start address is: 12 (R3)
; rsp start address is: 8 (R2)
; cmd_size start address is: 4 (R1)
; p_cmd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; p_rsp_size end address is: 12 (R3)
; rsp end address is: 8 (R2)
; cmd_size end address is: 4 (R1)
; p_cmd end address is: 0 (R0)
; p_cmd start address is: 0 (R0)
; cmd_size start address is: 4 (R1)
; rsp start address is: 8 (R2)
; p_rsp_size start address is: 12 (R3)
;RW_NDEF.c,94 :: 		if( p_read_fct != NULL )
MOVW	R4, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R4, #hi_addr(RW_NDEF_p_read_fct+0)
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_rw_ndef_read_next7
;RW_NDEF.c,95 :: 		p_read_fct( p_cmd, cmd_size, rsp, p_rsp_size );
; p_rsp_size end address is: 12 (R3)
; rsp end address is: 8 (R2)
; cmd_size end address is: 4 (R1)
; p_cmd end address is: 0 (R0)
MOVW	R4, #lo_addr(RW_NDEF_p_read_fct+0)
MOVT	R4, #hi_addr(RW_NDEF_p_read_fct+0)
LDR	R4, [R4, #0]
BLX	R4
L_rw_ndef_read_next7:
;RW_NDEF.c,96 :: 		}
L_end_rw_ndef_read_next:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _rw_ndef_read_next
