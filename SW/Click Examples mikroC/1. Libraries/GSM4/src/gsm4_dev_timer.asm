_dev_timer_init:
LDK.L	R0, #0
STA.L	gsm4_dev_timer_timer+0, R0
STA.L	gsm4_dev_timer_timer_c+0, R0
LDK.L	R0, #0
STA.B	_timeout_f+0, R0
STA.B	gsm4_dev_timer_timer_f+0, R0
L_end_dev_timer_init:
RETURN	
; end of _dev_timer_init
_dev_tick_isr:
LDA.B	R0, gsm4_dev_timer_timer_f+0
CMP.B	R0, #0
JMPC	R30, Z, #1, L_dev_tick_isr0
LDA.L	R1, gsm4_dev_timer_timer_c+0
LDA.L	R0, gsm4_dev_timer_timer_c+0
ADD.L	R0, R0, #1
STA.L	gsm4_dev_timer_timer_c+0, R0
LDA.L	R0, gsm4_dev_timer_timer+0
CMP.L	R1, R0
JMPC	R30, A, #0, L_dev_tick_isr1
LDK.L	R0, #1
STA.B	_timeout_f+0, R0
L_dev_tick_isr1:
L_dev_tick_isr0:
L_end_dev_tick_isr:
RETURN	
; end of _dev_tick_isr
_dev_timer_start:
LDK.L	R0, #1
STA.B	gsm4_dev_timer_timer_f+0, R0
LDK.L	R0, #0
STA.L	gsm4_dev_timer_timer_c+0, R0
L_end_dev_timer_start:
RETURN	
; end of _dev_timer_start
_dev_timer_restart:
LDK.L	R0, #0
STA.L	gsm4_dev_timer_timer_c+0, R0
L_end_dev_timer_restart:
RETURN	
; end of _dev_timer_restart
_dev_timer_stop:
LDK.L	R0, #0
STA.B	gsm4_dev_timer_timer_f+0, R0
LDK.L	R0, #0
STA.L	gsm4_dev_timer_timer_c+0, R0
L_end_dev_timer_stop:
RETURN	
; end of _dev_timer_stop
_dev_timer_load:
; timeout start address is: 0 (R0)
; timeout end address is: 0 (R0)
; timeout start address is: 0 (R0)
STA.L	gsm4_dev_timer_timer+0, R0
; timeout end address is: 0 (R0)
L_end_dev_timer_load:
RETURN	
; end of _dev_timer_load
