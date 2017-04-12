_hexiwear_uart_messaging_init:
;UART_Messaging.c,17 :: 		void hexiwear_uart_messaging_init( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;UART_Messaging.c,24 :: 		&_GPIO_Module_UART4_PE24_25
MOVW	R0, #lo_addr(__GPIO_Module_UART4_PE24_25+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART4_PE24_25+0)
PUSH	(R0)
;UART_Messaging.c,23 :: 		_UART_TWO_STOPBITS,
MOVW	R3, #32
;UART_Messaging.c,22 :: 		_UART_NOPARITY,
MOVW	R2, #0
;UART_Messaging.c,21 :: 		_UART_8_BIT_DATA,
MOVW	R1, #0
;UART_Messaging.c,20 :: 		230400,
MOV	R0, #230400
;UART_Messaging.c,24 :: 		&_GPIO_Module_UART4_PE24_25
BL	_UART4_Init_Advanced+0
ADD	SP, SP, #4
;UART_Messaging.c,27 :: 		Delay_ms( 100 );
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_hexiwear_uart_messaging_init0:
SUBS	R7, R7, #1
BNE	L_hexiwear_uart_messaging_init0
NOP
NOP
NOP
;UART_Messaging.c,30 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;UART_Messaging.c,31 :: 		NVIC_IntEnable( IVT_INT_UART4_RX_TX );
MOVW	R0, #82
BL	_NVIC_IntEnable+0
;UART_Messaging.c,32 :: 		UART4_C2 |= 1 << 5;
MOVW	R0, #lo_addr(UART4_C2+0)
MOVT	R0, #hi_addr(UART4_C2+0)
LDRB	R0, [R0, #0]
ORR	R1, R0, #32
MOVW	R0, #lo_addr(UART4_C2+0)
MOVT	R0, #hi_addr(UART4_C2+0)
STRB	R1, [R0, #0]
;UART_Messaging.c,33 :: 		}
L_end_hexiwear_uart_messaging_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _hexiwear_uart_messaging_init
_hexiwear_uart_messaging_process:
;UART_Messaging.c,35 :: 		void hexiwear_uart_messaging_process( void )
SUB	SP, SP, #4
STR	LR, [SP, #0]
;UART_Messaging.c,37 :: 		uint8_t tmp = 0;
;UART_Messaging.c,39 :: 		while(rx_tail_ind != rx_head_ind)
L_hexiwear_uart_messaging_process2:
MOVW	R0, #lo_addr(UART_Messaging_rx_head_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_head_ind+0)
LDRB	R1, [R0, #0]
MOVW	R0, #lo_addr(UART_Messaging_rx_tail_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_tail_ind+0)
LDRB	R0, [R0, #0]
CMP	R0, R1
IT	EQ
BEQ	L_hexiwear_uart_messaging_process3
;UART_Messaging.c,41 :: 		tmp = ble_rx_buffer[rx_tail_ind++];
MOVW	R0, #lo_addr(UART_Messaging_rx_tail_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_tail_ind+0)
LDRB	R1, [R0, #0]
MOVW	R0, #lo_addr(UART_Messaging_ble_rx_buffer+0)
MOVT	R0, #hi_addr(UART_Messaging_ble_rx_buffer+0)
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
; tmp start address is: 12 (R3)
UXTB	R3, R0
MOVW	R0, #lo_addr(UART_Messaging_rx_tail_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_tail_ind+0)
LDRB	R0, [R0, #0]
ADDS	R1, R0, #1
MOVW	R0, #lo_addr(UART_Messaging_rx_tail_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_tail_ind+0)
STRB	R1, [R0, #0]
;UART_Messaging.c,42 :: 		msg_buffer[msg_index++] = tmp;
MOVW	R2, #lo_addr(UART_Messaging_msg_index+0)
MOVT	R2, #hi_addr(UART_Messaging_msg_index+0)
LDRB	R1, [R2, #0]
MOVW	R0, #lo_addr(UART_Messaging_msg_buffer+0)
MOVT	R0, #hi_addr(UART_Messaging_msg_buffer+0)
ADDS	R0, R0, R1
STRB	R3, [R0, #0]
MOV	R0, R2
LDRB	R0, [R0, #0]
ADDS	R0, R0, #1
STRB	R0, [R2, #0]
;UART_Messaging.c,44 :: 		if(tmp == 0x45)
CMP	R3, #69
IT	NE
BNE	L_hexiwear_uart_messaging_process4
; tmp end address is: 12 (R3)
;UART_Messaging.c,46 :: 		trailer_flag = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(UART_Messaging_trailer_flag+0)
MOVT	R0, #hi_addr(UART_Messaging_trailer_flag+0)
STRB	R1, [R0, #0]
;UART_Messaging.c,47 :: 		}
L_hexiwear_uart_messaging_process4:
;UART_Messaging.c,48 :: 		}
IT	AL
BAL	L_hexiwear_uart_messaging_process2
L_hexiwear_uart_messaging_process3:
;UART_Messaging.c,50 :: 		if (trailer_flag)
MOVW	R0, #lo_addr(UART_Messaging_trailer_flag+0)
MOVT	R0, #hi_addr(UART_Messaging_trailer_flag+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_hexiwear_uart_messaging_process5
;UART_Messaging.c,52 :: 		if(msg_buffer[0] == 0x55)
MOVW	R0, #lo_addr(UART_Messaging_msg_buffer+0)
MOVT	R0, #hi_addr(UART_Messaging_msg_buffer+0)
LDRB	R0, [R0, #0]
CMP	R0, #85
IT	NE
BNE	L_hexiwear_uart_messaging_process6
;UART_Messaging.c,54 :: 		tmp = msg_buffer[2];
MOVW	R0, #lo_addr(UART_Messaging_msg_buffer+2)
MOVT	R0, #hi_addr(UART_Messaging_msg_buffer+2)
; tmp start address is: 24 (R6)
LDRB	R6, [R0, #0]
;UART_Messaging.c,56 :: 		if(tmp < 4 && tmp >= 0 && callbacks[tmp] != 0)
LDRB	R0, [R0, #0]
CMP	R0, #4
IT	CS
BCS	L__hexiwear_uart_messaging_process14
CMP	R6, #0
IT	CC
BCC	L__hexiwear_uart_messaging_process13
LSLS	R5, R6, #2
MOVW	R4, #lo_addr(UART_Messaging_callbacks+0)
MOVT	R4, #hi_addr(UART_Messaging_callbacks+0)
ADDS	R4, R4, R5
LDR	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L__hexiwear_uart_messaging_process12
L__hexiwear_uart_messaging_process11:
;UART_Messaging.c,57 :: 		callbacks[tmp]();
LSLS	R5, R6, #2
; tmp end address is: 24 (R6)
MOVW	R4, #lo_addr(UART_Messaging_callbacks+0)
MOVT	R4, #hi_addr(UART_Messaging_callbacks+0)
ADDS	R4, R4, R5
LDR	R0, [R4, #0]
BLX	R0
;UART_Messaging.c,56 :: 		if(tmp < 4 && tmp >= 0 && callbacks[tmp] != 0)
L__hexiwear_uart_messaging_process14:
L__hexiwear_uart_messaging_process13:
L__hexiwear_uart_messaging_process12:
;UART_Messaging.c,58 :: 		}
L_hexiwear_uart_messaging_process6:
;UART_Messaging.c,60 :: 		msg_index = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(UART_Messaging_msg_index+0)
MOVT	R0, #hi_addr(UART_Messaging_msg_index+0)
STRB	R1, [R0, #0]
;UART_Messaging.c,61 :: 		trailer_flag = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(UART_Messaging_trailer_flag+0)
MOVT	R0, #hi_addr(UART_Messaging_trailer_flag+0)
STRB	R1, [R0, #0]
;UART_Messaging.c,62 :: 		}
L_hexiwear_uart_messaging_process5:
;UART_Messaging.c,63 :: 		}
L_end_hexiwear_uart_messaging_process:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _hexiwear_uart_messaging_process
_hexiwear_uart_messaging_callback:
;UART_Messaging.c,71 :: 		)
; callback start address is: 4 (R1)
; type start address is: 0 (R0)
; callback end address is: 4 (R1)
; type end address is: 0 (R0)
; type start address is: 0 (R0)
; callback start address is: 4 (R1)
;UART_Messaging.c,73 :: 		callbacks[type] = callback;
LSLS	R3, R0, #2
; type end address is: 0 (R0)
MOVW	R2, #lo_addr(UART_Messaging_callbacks+0)
MOVT	R2, #hi_addr(UART_Messaging_callbacks+0)
ADDS	R2, R2, R3
STR	R1, [R2, #0]
; callback end address is: 4 (R1)
;UART_Messaging.c,74 :: 		}
L_end_hexiwear_uart_messaging_callback:
BX	LR
; end of _hexiwear_uart_messaging_callback
_BLE_RX_ISR:
;UART_Messaging.c,79 :: 		void BLE_RX_ISR() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
;UART_Messaging.c,81 :: 		if(  UART4_S1 & ( 1 << 5 )  )
MOVW	R0, #lo_addr(UART4_S1+0)
MOVT	R0, #hi_addr(UART4_S1+0)
LDRB	R0, [R0, #0]
AND	R0, R0, #32
UXTB	R0, R0
CMP	R0, #0
IT	EQ
BEQ	L_BLE_RX_ISR10
;UART_Messaging.c,83 :: 		uint8_t tmp = UART4_D;
MOVW	R0, #lo_addr(UART4_D+0)
MOVT	R0, #hi_addr(UART4_D+0)
; tmp start address is: 8 (R2)
LDRB	R2, [R0, #0]
;UART_Messaging.c,85 :: 		ble_rx_buffer[rx_head_ind++] = tmp;
MOVW	R0, #lo_addr(UART_Messaging_rx_head_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_head_ind+0)
LDRB	R1, [R0, #0]
MOVW	R0, #lo_addr(UART_Messaging_ble_rx_buffer+0)
MOVT	R0, #hi_addr(UART_Messaging_ble_rx_buffer+0)
ADDS	R0, R0, R1
STRB	R2, [R0, #0]
; tmp end address is: 8 (R2)
MOVW	R0, #lo_addr(UART_Messaging_rx_head_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_head_ind+0)
LDRB	R0, [R0, #0]
ADDS	R1, R0, #1
MOVW	R0, #lo_addr(UART_Messaging_rx_head_ind+0)
MOVT	R0, #hi_addr(UART_Messaging_rx_head_ind+0)
STRB	R1, [R0, #0]
;UART_Messaging.c,87 :: 		}
L_BLE_RX_ISR10:
;UART_Messaging.c,88 :: 		}
L_end_BLE_RX_ISR:
BX	LR
; end of _BLE_RX_ISR
