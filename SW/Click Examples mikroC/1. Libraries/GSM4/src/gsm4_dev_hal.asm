_dev_hal_pwr_ctl:
; state start address is: 0 (R0)
; state end address is: 0 (R0)
; state start address is: 0 (R0)
CMP.B	R0, #0
JMPC	R30, Z, #1, L_dev_hal_pwr_ctl0
; state end address is: 0 (R0)
LDA.x	R1, #AlignedAddress(GSM_PWR+0)
BINS.L	R1, R1, #BitPos(GSM_PWR+0)=1
STI.x	GSM_PWR+0, #AlignedAddress(R1)
JMP	L_dev_hal_pwr_ctl1
L_dev_hal_pwr_ctl0:
LDA.x	R1, #AlignedAddress(GSM_PWR+0)
BINS.L	R1, R1, #BitPos(GSM_PWR+0)=0
STI.x	GSM_PWR+0, #AlignedAddress(R1)
L_dev_hal_pwr_ctl1:
L_end_dev_hal_pwr_ctl:
RETURN	
; end of _dev_hal_pwr_ctl
_dev_hal_rts_ctl:
LDA.x	R0, #AlignedAddress(GSM_CTS+0)
BEXTU.L	R0, R0, #BitPos(GSM_CTS+0)
CMP.L	R0, #0
JMPC	R30, Z, #1, L_dev_hal_rts_ctl2
LDK.L	R0, #0
JMP	L_end_dev_hal_rts_ctl
L_dev_hal_rts_ctl2:
LDK.L	R0, #1
L_end_dev_hal_rts_ctl:
RETURN	
; end of _dev_hal_rts_ctl
_dev_hal_cts_ctl:
; state start address is: 0 (R0)
; state end address is: 0 (R0)
; state start address is: 0 (R0)
CMP.B	R0, #0
JMPC	R30, Z, #1, L_dev_hal_cts_ctl4
; state end address is: 0 (R0)
LDA.x	R1, #AlignedAddress(GSM_RTS+0)
BINS.L	R1, R1, #BitPos(GSM_RTS+0)=0
STI.x	GSM_RTS+0, #AlignedAddress(R1)
JMP	L_dev_hal_cts_ctl5
L_dev_hal_cts_ctl4:
LDA.x	R1, #AlignedAddress(GSM_RTS+0)
BINS.L	R1, R1, #BitPos(GSM_RTS+0)=1
STI.x	GSM_RTS+0, #AlignedAddress(R1)
L_dev_hal_cts_ctl5:
L_end_dev_hal_cts_ctl:
RETURN	
; end of _dev_hal_cts_ctl
_dev_hal_init:
LDA.L	R0, _UART_Wr_Ptr+0
STA.L	gsm4_dev_hal_write_uart_p+0, R0
L_end_dev_hal_init:
RETURN	
; end of _dev_hal_init
_dev_hal_write:
; ch start address is: 0 (R0)
; ch end address is: 0 (R0)
; ch start address is: 0 (R0)
; ch end address is: 0 (R0)
LDA.L	R6, gsm4_dev_hal_write_uart_p+0
CALLI	R6
L_end_dev_hal_write:
RETURN	
; end of _dev_hal_write
