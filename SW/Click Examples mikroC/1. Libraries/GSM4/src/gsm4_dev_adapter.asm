_dev_adapter_init:
CALL	_dev_hal_init+0
CALL	_dev_adapter_reset+0
LDK.L	R0, #0
STA.B	gsm4_dev_adapter_err_c+0, R0
STA.B	gsm4_dev_adapter_err_f+0, R0
LDK.L	R1, #?lstr1_gsm4_dev_adapter+0
LDK.L	R0, #gsm4_dev_adapter_error+0
CALL	_strcpy+0
LDK.L	R2, #256
LDK.L	R1, #0
LDK.L	R0, #_tx_buffer+0
CALL	_memset+0
LDK.L	R2, #256
LDK.L	R1, #0
LDK.L	R0, #_rx_buffer+0
CALL	_memset+0
L_end_dev_adapter_init:
RETURN	
; end of _dev_adapter_init
_dev_adapter_reset:
LDK.L	R0, #0
STA.S	gsm4_dev_adapter_rx_idx+0, R0
LDK.L	R0, #0
STA.B	gsm4_dev_adapter_term_f+0, R0
STA.B	gsm4_dev_adapter_frag_f+0, R0
STA.B	gsm4_dev_adapter_head_f+0, R0
STA.B	gsm4_dev_adapter_data_f+0, R0
STA.B	gsm4_dev_adapter_summ_f+0, R0
STA.B	gsm4_dev_adapter_head_t+0, R0
STA.B	gsm4_dev_adapter_data_t+0, R0
STA.B	gsm4_dev_adapter_summ_t+0, R0
LDK.L	R0, #1
CALL	_dev_hal_cts_ctl+0
L_end_dev_adapter_reset:
RETURN	
; end of _dev_adapter_reset
_dev_tx:
; tx_input start address is: 0 (R0)
; tx_input end address is: 0 (R0)
; tx_input start address is: 0 (R0)
CMP.B	R0, #0
JMPC	R30, Z, #1, L_dev_tx0
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R1, R1, R2
STI.B	R1, #0, R0
; tx_input end address is: 0 (R0)
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
JMP	L_dev_tx1
L_dev_tx0:
LDA.B	R1, _exception_f+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_dev_tx2
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #13
STI.B	R2, #0, R1
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #10
STI.B	R2, #0, R1
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
JMP	L_dev_tx3
L_dev_tx2:
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #26
STI.B	R2, #0, R1
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #13
STI.B	R2, #0, R1
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
L_dev_tx3:
LDK.L	R1, #0
STA.S	gsm4_dev_adapter_tx_idx+0, R1
L_dev_tx4:
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R1, R1, R2
LDI.B	R1, R1, #0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_tx5
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R1, R1, R2
LDI.B	R1, R1, #0
; tmp start address is: 0 (R0)
BEXTU.L	R0, R1, #256
; tmp end address is: 0 (R0)
CALL	_dev_hal_write+0
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
JMP	L_dev_tx4
L_dev_tx5:
LDK.L	R1, #0
STA.S	gsm4_dev_adapter_tx_idx+0, R1
LDK.L	R1, #0
STA.B	_exception_f+0, R1
STA.B	_response_f+0, R1
LDK.L	R1, #1
STA.B	_cue_f+0, R1
LDK.L	R0, #1
JMP	L_end_dev_tx
L_dev_tx1:
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
CMP.S	R1, #256
JMPC	R30, Z, #0, L_dev_tx6
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
LDK.L	R1, #0
STA.S	gsm4_dev_adapter_tx_idx+0, R1
L_dev_tx7:
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R1, R1, R2
LDI.B	R1, R1, #0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_tx8
LDA.S	R2, gsm4_dev_adapter_tx_idx+0
LDK.L	R1, #_tx_buffer+0
ADD.L	R1, R1, R2
LDI.B	R1, R1, #0
; tmp start address is: 0 (R0)
BEXTU.L	R0, R1, #256
; tmp end address is: 0 (R0)
CALL	_dev_hal_write+0
LDA.S	R1, gsm4_dev_adapter_tx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_tx_idx+0, R1
JMP	L_dev_tx7
L_dev_tx8:
LDK.L	R1, #0
STA.S	gsm4_dev_adapter_tx_idx+0, R1
LDK.L	R0, #0
JMP	L_end_dev_tx
L_dev_tx6:
LDK.L	R0, #0
L_end_dev_tx:
RETURN	
; end of _dev_tx
_dev_rx:
; rx_input start address is: 0 (R0)
; rx_input end address is: 0 (R0)
; rx_input start address is: 0 (R0)
CMP.B	R0, #13
JMPC	R30, Z, #0, L_dev_rx9
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_term_f+0, R1
L_dev_rx9:
CMP.B	R0, #10
JMPC	R30, Z, #0, L__dev_rx49
LDA.B	R1, gsm4_dev_adapter_term_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L__dev_rx48
L__dev_rx47:
LDK.L	R1, #0
STA.B	gsm4_dev_adapter_term_f+0, R1
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_frag_f+0, R1
L__dev_rx49:
L__dev_rx48:
LDA.B	R1, gsm4_dev_adapter_frag_f+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_dev_rx13
LDA.B	R1, gsm4_dev_adapter_head_f+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L__dev_rx61
LDA.B	R1, gsm4_dev_adapter_data_f+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L__dev_rx60
LDA.B	R1, gsm4_dev_adapter_summ_f+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L__dev_rx59
L__dev_rx46:
CMP.B	R0, #65
JMPC	R30, Z, #0, L_dev_rx17
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_head_f+0, R1
JMP	L_dev_rx18
L_dev_rx17:
CMP.B	R0, #79
JMPC	R30, Z, #1, L__dev_rx56
CMP.B	R0, #69
JMPC	R30, Z, #1, L__dev_rx55
CMP.B	R0, #66
JMPC	R30, Z, #1, L__dev_rx54
CMP.B	R0, #67
JMPC	R30, Z, #1, L__dev_rx53
CMP.B	R0, #82
JMPC	R30, Z, #1, L__dev_rx52
CMP.B	R0, #78
JMPC	R30, Z, #1, L__dev_rx51
CMP.B	R0, #80
JMPC	R30, Z, #1, L__dev_rx50
JMP	L_dev_rx21
L__dev_rx56:
L__dev_rx55:
L__dev_rx54:
L__dev_rx53:
L__dev_rx52:
L__dev_rx51:
L__dev_rx50:
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_summ_f+0, R1
JMP	L_dev_rx22
L_dev_rx21:
CMP.B	R0, #43
JMPC	R30, Z, #1, L__dev_rx58
LDA.B	R1, gsm4_dev_adapter_data_t+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L__dev_rx57
JMP	L_dev_rx25
L__dev_rx58:
L__dev_rx57:
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_data_f+0, R1
L_dev_rx25:
L_dev_rx22:
L_dev_rx18:
L__dev_rx61:
L__dev_rx60:
L__dev_rx59:
CMP.B	R0, #62
JMPC	R30, Z, #0, L_dev_rx26
LDK.L	R1, #1
STA.B	_exception_f+0, R1
L_dev_rx26:
L_dev_rx13:
LDA.B	R1, gsm4_dev_adapter_head_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx27
LDA.B	R1, gsm4_dev_adapter_head_t+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_dev_rx28
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_head_t+0, R1
L_dev_rx28:
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R1, R1, R2
STI.B	R1, #0, R0
LDA.S	R1, gsm4_dev_adapter_rx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_rx_idx+0, R1
L_dev_rx27:
LDA.B	R1, gsm4_dev_adapter_data_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx29
LDA.B	R1, gsm4_dev_adapter_data_t+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_dev_rx30
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_data_t+0, R1
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R1, R1, R2
STA.L	gsm4_dev_adapter_data_ptr+0, R1
L_dev_rx30:
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R1, R1, R2
STI.B	R1, #0, R0
LDA.S	R1, gsm4_dev_adapter_rx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_rx_idx+0, R1
L_dev_rx29:
LDA.B	R1, gsm4_dev_adapter_summ_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx31
LDA.B	R1, gsm4_dev_adapter_summ_t+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_dev_rx32
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_summ_t+0, R1
L_dev_rx32:
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R1, R1, R2
STI.B	R1, #0, R0
; rx_input end address is: 0 (R0)
LDA.S	R1, gsm4_dev_adapter_rx_idx+0
ADD.L	R1, R1, #1
STA.S	gsm4_dev_adapter_rx_idx+0, R1
L_dev_rx31:
LDA.B	R1, gsm4_dev_adapter_frag_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx33
LDA.B	R1, gsm4_dev_adapter_head_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx34
LDK.L	R1, #0
STA.B	gsm4_dev_adapter_head_f+0, R1
L_dev_rx34:
LDA.B	R1, gsm4_dev_adapter_data_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx35
L_dev_rx36:
LDA.B	R1, gsm4_dev_adapter_error+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx37
LDA.B	R2, gsm4_dev_adapter_err_c+0
LDK.L	R1, #gsm4_dev_adapter_error+0
ADD.L	R1, R1, R2
LDI.B	R3, R1, #0
LDA.B	R2, gsm4_dev_adapter_err_c+0
LDA.B	R1, gsm4_dev_adapter_err_c+0
ADD.L	R1, R1, #1
STA.B	gsm4_dev_adapter_err_c+0, R1
LDA.L	R1, gsm4_dev_adapter_data_ptr+0
ADD.L	R1, R1, R2
LDI.B	R1, R1, #0
CMP.B	R3, R1
JMPC	R30, Z, #0, L_dev_rx38
LDK.L	R1, #1
STA.B	gsm4_dev_adapter_err_f+0, R1
JMP	L_dev_rx39
L_dev_rx38:
LDK.L	R1, #0
STA.B	gsm4_dev_adapter_err_f+0, R1
JMP	L_dev_rx37
L_dev_rx39:
JMP	L_dev_rx36
L_dev_rx37:
LDA.B	R1, gsm4_dev_adapter_err_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx40
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
LDK.L	R1, #1
STA.B	_response_f+0, R1
L_dev_rx40:
LDA.B	R1, gsm4_dev_adapter_head_t+0
CMP.B	R1, #0
JMPC	R30, Z, #0, L_dev_rx41
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
LDK.L	R1, #1
STA.B	_response_f+0, R1
L_dev_rx41:
LDK.L	R1, #0
STA.B	gsm4_dev_adapter_err_c+0, R1
STA.B	gsm4_dev_adapter_data_f+0, R1
L_dev_rx35:
LDA.B	R1, gsm4_dev_adapter_summ_f+0
CMP.B	R1, #0
JMPC	R30, Z, #1, L_dev_rx42
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
LDK.L	R1, #1
STA.B	_response_f+0, R1
L_dev_rx42:
LDK.L	R1, #0
STA.B	gsm4_dev_adapter_frag_f+0, R1
L_dev_rx33:
LDA.S	R1, gsm4_dev_adapter_rx_idx+0
CMP.S	R1, #256
JMPC	R30, Z, #0, L_dev_rx43
LDA.S	R2, gsm4_dev_adapter_rx_idx+0
LDK.L	R1, #_rx_buffer+0
ADD.L	R2, R1, R2
LDK.L	R1, #0
STI.B	R2, #0, R1
LDK.L	R1, #1
STA.B	_response_f+0, R1
L_dev_rx43:
L_end_dev_rx:
RETURN	
; end of _dev_rx
