_engine_init:
; default_callback start address is: 0 (R0)
LINK	LR, #4
; default_callback end address is: 0 (R0)
; default_callback start address is: 0 (R0)
STA.L	gsm4_at_engine_cb_default+0, R0
STI.L	SP, #0, R0
CALL	_dev_adapter_init+0
CALL	_dev_timer_init+0
CALL	_at_parser_init+0
LDI.L	R0, SP, #0
LDK.L	R1, #?lstr1_gsm4_at_engine+0
MOVE.L	R5, R0
MOVE.L	R4, R5
MOVE.L	R3, R4
MOVE.L	R2, R3
; default_callback end address is: 0 (R0)
MOVE.L	R0, R1
LDK.L	R1, #500
CALL	_at_cmd_save+0
LDK.L	R1, #0
STA.B	_exception_f+0, R1
STA.B	_response_f+0, R1
STA.B	_cue_f+0, R1
LDK.L	R2, #256
LDK.L	R1, #0
LDK.L	R0, #_tx_buffer+0
CALL	_memset+0
L_end_engine_init:
UNLINK	LR
RETURN	
; end of _engine_init
_at_cmd:
; input start address is: 0 (R0)
LINK	LR, #4
; input end address is: 0 (R0)
; input start address is: 0 (R0)
STI.L	SP, #0, R0
; input end address is: 0 (R0)
LPM.L	R28, #3333331
NOP	
L_at_cmd0:
SUB.L	R28, R28, #1
CMP.L	R28, #0
JMPC	R30, Z, #0, L_at_cmd0
JMP	$+8
	#3333331
NOP	
NOP	
LDK.L	R2, #gsm4_at_engine_temp_timer+0
LDK.L	R1, #gsm4_at_engine_temp_cb+0
LDI.L	R0, SP, #0
CALL	_at_parse+0
LDA.L	R1, gsm4_at_engine_temp_timer+0
MOVE.L	R0, R1
CALL	_dev_timer_load+0
L_at_cmd2:
LDA.B	R1, _cue_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_at_cmd3
CALL	_at_process+0
JMP	L_at_cmd2
L_at_cmd3:
L_at_cmd4:
LDI.L	R2, SP, #0
LDI.L	R1, SP, #0
ADD.L	R1, R1, #1
STI.L	SP, #0, R1
LDI.B	R1, R2, #0
BEXTU.L	R0, R1, #256
CALL	_dev_tx+0
CMP.S	R0, #0
JMPC	R30, Z, #0, L_at_cmd5
JMP	L_at_cmd4
L_at_cmd5:
CALL	_dev_adapter_reset+0
CALL	_dev_timer_start+0
L_end_at_cmd:
UNLINK	LR
RETURN	
; end of _at_cmd
_at_cmd_addition:
; input start address is: 0 (R0)
LINK	LR, #4
; input end address is: 0 (R0)
; input start address is: 0 (R0)
STI.L	SP, #0, R0
; input end address is: 0 (R0)
LPM.L	R28, #3333331
NOP	
L_at_cmd_addition6:
SUB.L	R28, R28, #1
CMP.L	R28, #0
JMPC	R30, Z, #0, L_at_cmd_addition6
JMP	$+8
	#3333331
NOP	
NOP	
L_at_cmd_addition8:
LDA.B	R1, _exception_f+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_at_cmd_addition9
CALL	_at_process+0
JMP	L_at_cmd_addition8
L_at_cmd_addition9:
CALL	_dev_timer_stop+0
L_at_cmd_addition10:
LDI.L	R2, SP, #0
LDI.L	R1, SP, #0
ADD.L	R1, R1, #1
STI.L	SP, #0, R1
LDI.B	R1, R2, #0
BEXTU.L	R0, R1, #256
CALL	_dev_tx+0
CMP.S	R0, #0
JMPC	R30, Z, #0, L_at_cmd_addition11
JMP	L_at_cmd_addition10
L_at_cmd_addition11:
CALL	_dev_adapter_reset+0
CALL	_dev_timer_restart+0
L_end_at_cmd_addition:
UNLINK	LR
RETURN	
; end of _at_cmd_addition
_at_cmd_save:
; executer start address is: 20 (R5)
; tester start address is: 16 (R4)
; setter start address is: 12 (R3)
; getter start address is: 8 (R2)
; timeout start address is: 4 (R1)
; cmd start address is: 0 (R0)
LINK	LR, #4
STI.L	SP, #0, R3
MOVE.L	R3, R2
LDI.L	R2, SP, #0
; executer end address is: 20 (R5)
; tester end address is: 16 (R4)
; setter end address is: 12 (R3)
; getter end address is: 8 (R2)
; timeout end address is: 4 (R1)
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; timeout start address is: 4 (R1)
; getter start address is: 12 (R3)
; setter start address is: 8 (R2)
; tester start address is: 16 (R4)
; executer start address is: 20 (R5)
CMP.L	R2, #0
JMPC	R30, Z, #0, L__at_cmd_save19
LDA.L	R2, gsm4_at_engine_cb_default+0
; setter end address is: 8 (R2)
JMP	L_at_cmd_save12
L__at_cmd_save19:
L_at_cmd_save12:
; setter start address is: 8 (R2)
CMP.L	R3, #0
JMPC	R30, Z, #0, L__at_cmd_save20
LDA.L	R3, gsm4_at_engine_cb_default+0
; getter end address is: 12 (R3)
JMP	L_at_cmd_save13
L__at_cmd_save20:
L_at_cmd_save13:
; getter start address is: 12 (R3)
CMP.L	R4, #0
JMPC	R30, Z, #0, L__at_cmd_save21
LDA.L	R4, gsm4_at_engine_cb_default+0
; tester end address is: 16 (R4)
MOVE.L	R6, R4
JMP	L_at_cmd_save14
L__at_cmd_save21:
MOVE.L	R6, R4
L_at_cmd_save14:
; tester start address is: 24 (R6)
CMP.L	R5, #0
JMPC	R30, Z, #0, L__at_cmd_save22
; executer end address is: 20 (R5)
; executer start address is: 16 (R4)
LDA.L	R4, gsm4_at_engine_cb_default+0
; executer end address is: 16 (R4)
JMP	L_at_cmd_save15
L__at_cmd_save22:
MOVE.L	R4, R5
L_at_cmd_save15:
; executer start address is: 16 (R4)
CMP.L	R1, #0
JMPC	R30, Z, #0, L__at_cmd_save23
LDK.L	R1, #500
; timeout end address is: 4 (R1)
JMP	L_at_cmd_save16
L__at_cmd_save23:
L_at_cmd_save16:
; timeout start address is: 4 (R1)
STI.L	SP, #0, R3
; executer end address is: 16 (R4)
MOVE.L	R5, R4
MOVE.L	R4, R6
; tester end address is: 24 (R6)
; setter end address is: 8 (R2)
; getter end address is: 12 (R3)
MOVE.L	R3, R2
; timeout end address is: 4 (R1)
LDI.L	R2, SP, #0
; cmd end address is: 0 (R0)
CALL	_at_parser_store+0
L_end_at_cmd_save:
UNLINK	LR
RETURN	
; end of _at_cmd_save
_at_process:
LDA.B	R0, _response_f+0
CMP.B	R0, #0
JMPC	R30, Z, #1, L_at_process17
LDK.L	R0, #0
CALL	_dev_hal_cts_ctl+0
CALL	_dev_timer_stop+0
LDK.L	R2, #gsm4_at_engine_temp_timer+0
LDK.L	R1, #gsm4_at_engine_cb+0
LDK.L	R0, #_rx_buffer+0
CALL	_at_parse+0
LDK.L	R0, #_rx_buffer+0
LDA.L	R6, gsm4_at_engine_cb+0
CALLI	R6
CALL	_dev_adapter_reset+0
LDK.L	R0, #0
STA.B	_timeout_f+0, R0
STA.B	_exception_f+0, R0
STA.B	_response_f+0, R0
STA.B	_cue_f+0, R0
L_at_process17:
LDA.B	R0, _timeout_f+0
CMP.B	R0, #0
JMPC	R30, Z, #1, L_at_process18
LDK.L	R0, #0
CALL	_dev_hal_cts_ctl+0
CALL	_dev_timer_stop+0
LDK.L	R2, #gsm4_at_engine_temp_timer+0
LDK.L	R1, #gsm4_at_engine_cb+0
LDK.L	R0, #_rx_buffer+0
CALL	_at_parse+0
LDK.L	R0, #_rx_buffer+0
LDA.L	R6, gsm4_at_engine_cb+0
CALLI	R6
CALL	_dev_adapter_reset+0
LDK.L	R1, #0
STA.B	_timeout_f+0, R1
STA.B	_exception_f+0, R1
LDK.L	R0, #1
STA.B	_response_f+0, R0
STA.B	_cue_f+0, R1
L_at_process18:
L_end_at_process:
RETURN	
; end of _at_process
