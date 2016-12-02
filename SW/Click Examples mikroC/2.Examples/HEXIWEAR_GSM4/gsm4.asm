_gsm4_init:
;gsm4.c,8 :: 		void gsm4_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;gsm4.c,10 :: 		engine_init( gsm4_evn_default );
MOVW	R0, #lo_addr(_gsm4_evn_default+0)
MOVT	R0, #hi_addr(_gsm4_evn_default+0)
BL	_engine_init+0
;gsm4.c,16 :: 		at_cmd_save( "RING", 1000, NULL, NULL, NULL, gsm4_ev_ring );
MOVW	R2, #lo_addr(_gsm4_ev_ring+0)
MOVT	R2, #hi_addr(_gsm4_ev_ring+0)
MOVS	R1, #0
MOVW	R0, #lo_addr(?lstr1_gsm4+0)
MOVT	R0, #hi_addr(?lstr1_gsm4+0)
PUSH	(R2)
PUSH	(R1)
MOVS	R3, #0
MOVS	R2, #0
MOVW	R1, #1000
BL	_at_cmd_save+0
ADD	SP, SP, #8
;gsm4.c,18 :: 		at_cmd( "AT" );
MOVW	R0, #lo_addr(?lstr2_gsm4+0)
MOVT	R0, #hi_addr(?lstr2_gsm4+0)
BL	_at_cmd+0
;gsm4.c,19 :: 		at_cmd( "AT+CSCS=\"GSM\"" );
MOVW	R0, #lo_addr(?lstr3_gsm4+0)
MOVT	R0, #hi_addr(?lstr3_gsm4+0)
BL	_at_cmd+0
;gsm4.c,20 :: 		at_cmd( "AT+CMGF=1" );
MOVW	R0, #lo_addr(?lstr4_gsm4+0)
MOVT	R0, #hi_addr(?lstr4_gsm4+0)
BL	_at_cmd+0
;gsm4.c,21 :: 		}
L_end_gsm4_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _gsm4_init
_gsm4_evn_default:
;gsm4.c,23 :: 		void gsm4_evn_default( char *response )
; response start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; response end address is: 0 (R0)
; response start address is: 0 (R0)
;gsm4.c,25 :: 		UART3_Write_Text( response );
; response end address is: 0 (R0)
BL	_UART3_Write_Text+0
;gsm4.c,26 :: 		}
L_end_gsm4_evn_default:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _gsm4_evn_default
_gsm4_ev_ring:
;gsm4.c,28 :: 		void gsm4_ev_ring( char *response )
SUB	SP, SP, #4
;gsm4.c,30 :: 		ring_f = true;
MOVS	R2, #1
MOVW	R1, #lo_addr(_ring_f+0)
MOVT	R1, #hi_addr(_ring_f+0)
STRB	R2, [R1, #0]
;gsm4.c,31 :: 		}
L_end_gsm4_ev_ring:
ADD	SP, SP, #4
BX	LR
; end of _gsm4_ev_ring
