_system_init:
;GSM4_HEXI.c,14 :: 		void system_init()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;GSM4_HEXI.c,16 :: 		GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_14 );
MOV	R1, #16384
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
BL	_GPIO_Digital_Output+0
;GSM4_HEXI.c,17 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
MOV	R1, #2048
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;GSM4_HEXI.c,18 :: 		GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;GSM4_HEXI.c,19 :: 		GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 );
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDIR+0)
MOVT	R0, #hi_addr(PTB_PDIR+0)
BL	_GPIO_Digital_Input+0
;GSM4_HEXI.c,20 :: 		GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_10 );
MOV	R1, #1024
MOVW	R0, #lo_addr(PTA_PDIR+0)
MOVT	R0, #hi_addr(PTA_PDIR+0)
BL	_GPIO_Digital_Input+0
;GSM4_HEXI.c,21 :: 		GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_2 );
MOV	R1, #4
MOVW	R0, #lo_addr(PTB_PDIR+0)
MOVT	R0, #hi_addr(PTB_PDIR+0)
BL	_GPIO_Digital_Input+0
;GSM4_HEXI.c,24 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
MOVW	R0, #lo_addr(__GPIO_Module_UART3_PC16_17+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART3_PC16_17+0)
PUSH	(R0)
MOVW	R3, #0
;GSM4_HEXI.c,23 :: 		UART3_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOV	R0, #115200
;GSM4_HEXI.c,24 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART3_PC16_17 );
BL	_UART3_Init_Advanced+0
ADD	SP, SP, #4
;GSM4_HEXI.c,27 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
MOVW	R0, #lo_addr(__GPIO_Module_UART2_PD3_2+0)
MOVT	R0, #hi_addr(__GPIO_Module_UART2_PD3_2+0)
PUSH	(R0)
MOVW	R3, #0
;GSM4_HEXI.c,26 :: 		UART2_Init_Advanced( 9600, _UART_8_BIT_DATA, _UART_NOPARITY,
MOVW	R2, #0
MOVW	R1, #0
MOVW	R0, #9600
;GSM4_HEXI.c,27 :: 		_UART_ONE_STOPBIT, &_GPIO_Module_UART2_PD3_2 );
BL	_UART2_Init_Advanced+0
ADD	SP, SP, #4
;GSM4_HEXI.c,29 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;GSM4_HEXI.c,30 :: 		NVIC_IntEnable( IVT_INT_UART2_RX_TX );
MOVW	R0, #51
BL	_NVIC_IntEnable+0
;GSM4_HEXI.c,31 :: 		UART2_C2 |= 1 << 5;
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
LDRB	R0, [R0, #0]
ORR	R1, R0, #32
MOVW	R0, #lo_addr(UART2_C2+0)
MOVT	R0, #hi_addr(UART2_C2+0)
STRB	R1, [R0, #0]
;GSM4_HEXI.c,33 :: 		Delay_ms( 500 );
MOVW	R7, #11518
MOVT	R7, #305
NOP
NOP
L_system_init0:
SUBS	R7, R7, #1
BNE	L_system_init0
NOP
NOP
NOP
;GSM4_HEXI.c,34 :: 		UART3_Write_Text( "INITIALIZED\r\n" );
MOVW	R0, #lo_addr(?lstr1_GSM4_HEXI+0)
MOVT	R0, #hi_addr(?lstr1_GSM4_HEXI+0)
BL	_UART3_Write_Text+0
;GSM4_HEXI.c,35 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _system_init
_main:
;GSM4_HEXI.c,37 :: 		void main() {
SUB	SP, SP, #4
;GSM4_HEXI.c,39 :: 		system_init();
BL	_system_init+0
;GSM4_HEXI.c,40 :: 		gsm4_init();
BL	_gsm4_init+0
;GSM4_HEXI.c,42 :: 		LED3 = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
STR	R1, [R0, #0]
;GSM4_HEXI.c,44 :: 		while( 1 ) {
L_main2:
;GSM4_HEXI.c,46 :: 		at_process();
BL	_at_process+0
;GSM4_HEXI.c,48 :: 		if( ring_f ) {
MOVW	R0, #lo_addr(_ring_f+0)
MOVT	R0, #hi_addr(_ring_f+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main4
;GSM4_HEXI.c,50 :: 		LED3 = ~LED3;
MOVW	R1, #lo_addr(PTA_PDOR+0)
MOVT	R1, #hi_addr(PTA_PDOR+0)
LDR	R0, [R1, #0]
EOR	R0, R0, #1
STR	R0, [R1, #0]
;GSM4_HEXI.c,51 :: 		ring_f = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_ring_f+0)
MOVT	R0, #hi_addr(_ring_f+0)
STRB	R1, [R0, #0]
;GSM4_HEXI.c,52 :: 		}
L_main4:
;GSM4_HEXI.c,53 :: 		}
IT	AL
BAL	L_main2
;GSM4_HEXI.c,54 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_UART_RX_ISR:
;GSM4_HEXI.c,56 :: 		void UART_RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
SUB	SP, SP, #4
STR	LR, [SP, #0]
;GSM4_HEXI.c,58 :: 		char foo = UART2_S1;
MOVW	R0, #lo_addr(UART2_S1+0)
MOVT	R0, #hi_addr(UART2_S1+0)
; foo start address is: 4 (R1)
LDRB	R1, [R0, #0]
;GSM4_HEXI.c,59 :: 		char tmp = UART2_D;
MOVW	R0, #lo_addr(UART2_D+0)
MOVT	R0, #hi_addr(UART2_D+0)
; tmp start address is: 8 (R2)
LDRB	R2, [R0, #0]
;GSM4_HEXI.c,61 :: 		if( foo & ( 1 << 5 ) )
AND	R0, R1, #32
UXTB	R0, R0
; foo end address is: 4 (R1)
CMP	R0, #0
IT	EQ
BEQ	L_UART_RX_ISR5
;GSM4_HEXI.c,62 :: 		dev_rx( tmp );
UXTB	R0, R2
; tmp end address is: 8 (R2)
BL	_dev_rx+0
L_UART_RX_ISR5:
;GSM4_HEXI.c,63 :: 		}
L_end_UART_RX_ISR:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _UART_RX_ISR
