
_MIKROBUS_gpioDirection:

	CP.B	W10, #0
	BRA Z	L__MIKROBUS_gpioDirection33
	GOTO	L_MIKROBUS_gpioDirection0
L__MIKROBUS_gpioDirection33:
	GOTO	L_MIKROBUS_gpioDirection1
L_MIKROBUS_gpioDirection3:
	BTSS	W12, #0
	BCLR	TRISB8_bit, BitPos(TRISB8_bit+0)
	BTSC	W12, #0
	BSET	TRISB8_bit, BitPos(TRISB8_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection4:
	BTSS	W12, #0
	BCLR	TRISC1_bit, BitPos(TRISC1_bit+0)
	BTSC	W12, #0
	BSET	TRISC1_bit, BitPos(TRISC1_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection5:
	BTSS	W12, #0
	BCLR	TRISC2_bit, BitPos(TRISC2_bit+0)
	BTSC	W12, #0
	BSET	TRISC2_bit, BitPos(TRISC2_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection6:
	BTSS	W12, #0
	BCLR	TRISF6_bit, BitPos(TRISF6_bit+0)
	BTSC	W12, #0
	BSET	TRISF6_bit, BitPos(TRISF6_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection7:
	BTSS	W12, #0
	BCLR	TRISF7_bit, BitPos(TRISF7_bit+0)
	BTSC	W12, #0
	BSET	TRISF7_bit, BitPos(TRISF7_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection8:
	BTSS	W12, #0
	BCLR	TRISF8_bit, BitPos(TRISF8_bit+0)
	BTSC	W12, #0
	BSET	TRISF8_bit, BitPos(TRISF8_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection9:
	BTSS	W12, #0
	BCLR	TRISD0_bit, BitPos(TRISD0_bit+0)
	BTSC	W12, #0
	BSET	TRISD0_bit, BitPos(TRISD0_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection10:
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection11:
	BTSS	W12, #0
	BCLR	TRISF4_bit, BitPos(TRISF4_bit+0)
	BTSC	W12, #0
	BSET	TRISF4_bit, BitPos(TRISF4_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection12:
	BTSS	W12, #0
	BCLR	TRISF5_bit, BitPos(TRISF5_bit+0)
	BTSC	W12, #0
	BSET	TRISF5_bit, BitPos(TRISF5_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection13:
	BTSS	W12, #0
	BCLR	TRISA2_bit, BitPos(TRISA2_bit+0)
	BTSC	W12, #0
	BSET	TRISA2_bit, BitPos(TRISA2_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection14:
	BTSS	W12, #0
	BCLR	TRISA3_bit, BitPos(TRISA3_bit+0)
	BTSC	W12, #0
	BSET	TRISA3_bit, BitPos(TRISA3_bit+0)
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection15:
	GOTO	L_MIKROBUS_gpioDirection2
L_MIKROBUS_gpioDirection1:
	CP.B	W11, #0
	BRA NZ	L__MIKROBUS_gpioDirection34
	GOTO	L_MIKROBUS_gpioDirection3
L__MIKROBUS_gpioDirection34:
	CP.B	W11, #1
	BRA NZ	L__MIKROBUS_gpioDirection35
	GOTO	L_MIKROBUS_gpioDirection4
L__MIKROBUS_gpioDirection35:
	CP.B	W11, #2
	BRA NZ	L__MIKROBUS_gpioDirection36
	GOTO	L_MIKROBUS_gpioDirection5
L__MIKROBUS_gpioDirection36:
	CP.B	W11, #3
	BRA NZ	L__MIKROBUS_gpioDirection37
	GOTO	L_MIKROBUS_gpioDirection6
L__MIKROBUS_gpioDirection37:
	CP.B	W11, #4
	BRA NZ	L__MIKROBUS_gpioDirection38
	GOTO	L_MIKROBUS_gpioDirection7
L__MIKROBUS_gpioDirection38:
	CP.B	W11, #5
	BRA NZ	L__MIKROBUS_gpioDirection39
	GOTO	L_MIKROBUS_gpioDirection8
L__MIKROBUS_gpioDirection39:
	CP.B	W11, #6
	BRA NZ	L__MIKROBUS_gpioDirection40
	GOTO	L_MIKROBUS_gpioDirection9
L__MIKROBUS_gpioDirection40:
	CP.B	W11, #7
	BRA NZ	L__MIKROBUS_gpioDirection41
	GOTO	L_MIKROBUS_gpioDirection10
L__MIKROBUS_gpioDirection41:
	CP.B	W11, #8
	BRA NZ	L__MIKROBUS_gpioDirection42
	GOTO	L_MIKROBUS_gpioDirection11
L__MIKROBUS_gpioDirection42:
	CP.B	W11, #9
	BRA NZ	L__MIKROBUS_gpioDirection43
	GOTO	L_MIKROBUS_gpioDirection12
L__MIKROBUS_gpioDirection43:
	CP.B	W11, #10
	BRA NZ	L__MIKROBUS_gpioDirection44
	GOTO	L_MIKROBUS_gpioDirection13
L__MIKROBUS_gpioDirection44:
	CP.B	W11, #11
	BRA NZ	L__MIKROBUS_gpioDirection45
	GOTO	L_MIKROBUS_gpioDirection14
L__MIKROBUS_gpioDirection45:
	GOTO	L_MIKROBUS_gpioDirection15
L_MIKROBUS_gpioDirection2:
L_MIKROBUS_gpioDirection0:
	CP.B	W10, #1
	BRA Z	L__MIKROBUS_gpioDirection46
	GOTO	L_MIKROBUS_gpioDirection16
L__MIKROBUS_gpioDirection46:
	GOTO	L_MIKROBUS_gpioDirection17
L_MIKROBUS_gpioDirection19:
	BTSS	W12, #0
	BCLR	TRISB9_bit, BitPos(TRISB9_bit+0)
	BTSC	W12, #0
	BSET	TRISB9_bit, BitPos(TRISB9_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection20:
	BTSS	W12, #0
	BCLR	TRISC3_bit, BitPos(TRISC3_bit+0)
	BTSC	W12, #0
	BSET	TRISC3_bit, BitPos(TRISC3_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection21:
	BTSS	W12, #0
	BCLR	TRISC4_bit, BitPos(TRISC4_bit+0)
	BTSC	W12, #0
	BSET	TRISC4_bit, BitPos(TRISC4_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection22:
	BTSS	W12, #0
	BCLR	TRISF6_bit, BitPos(TRISF6_bit+0)
	BTSC	W12, #0
	BSET	TRISF6_bit, BitPos(TRISF6_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection23:
	BTSS	W12, #0
	BCLR	TRISF7_bit, BitPos(TRISF7_bit+0)
	BTSC	W12, #0
	BSET	TRISF7_bit, BitPos(TRISF7_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection24:
	BTSS	W12, #0
	BCLR	TRISF8_bit, BitPos(TRISF8_bit+0)
	BTSC	W12, #0
	BSET	TRISF8_bit, BitPos(TRISF8_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection25:
	BTSS	W12, #0
	BCLR	TRISD1_bit, BitPos(TRISD1_bit+0)
	BTSC	W12, #0
	BSET	TRISD1_bit, BitPos(TRISD1_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection26:
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection27:
	BTSS	W12, #0
	BCLR	TRISF12_bit, BitPos(TRISF12_bit+0)
	BTSC	W12, #0
	BSET	TRISF12_bit, BitPos(TRISF12_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection28:
	BTSS	W12, #0
	BCLR	TRISF13_bit, BitPos(TRISF13_bit+0)
	BTSC	W12, #0
	BSET	TRISF13_bit, BitPos(TRISF13_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection29:
	BTSS	W12, #0
	BCLR	TRISA2_bit, BitPos(TRISA2_bit+0)
	BTSC	W12, #0
	BSET	TRISA2_bit, BitPos(TRISA2_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection30:
	BTSS	W12, #0
	BCLR	TRISA3_bit, BitPos(TRISA3_bit+0)
	BTSC	W12, #0
	BSET	TRISA3_bit, BitPos(TRISA3_bit+0)
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection31:
	GOTO	L_MIKROBUS_gpioDirection18
L_MIKROBUS_gpioDirection17:
	CP.B	W11, #0
	BRA NZ	L__MIKROBUS_gpioDirection47
	GOTO	L_MIKROBUS_gpioDirection19
L__MIKROBUS_gpioDirection47:
	CP.B	W11, #1
	BRA NZ	L__MIKROBUS_gpioDirection48
	GOTO	L_MIKROBUS_gpioDirection20
L__MIKROBUS_gpioDirection48:
	CP.B	W11, #2
	BRA NZ	L__MIKROBUS_gpioDirection49
	GOTO	L_MIKROBUS_gpioDirection21
L__MIKROBUS_gpioDirection49:
	CP.B	W11, #3
	BRA NZ	L__MIKROBUS_gpioDirection50
	GOTO	L_MIKROBUS_gpioDirection22
L__MIKROBUS_gpioDirection50:
	CP.B	W11, #4
	BRA NZ	L__MIKROBUS_gpioDirection51
	GOTO	L_MIKROBUS_gpioDirection23
L__MIKROBUS_gpioDirection51:
	CP.B	W11, #5
	BRA NZ	L__MIKROBUS_gpioDirection52
	GOTO	L_MIKROBUS_gpioDirection24
L__MIKROBUS_gpioDirection52:
	CP.B	W11, #6
	BRA NZ	L__MIKROBUS_gpioDirection53
	GOTO	L_MIKROBUS_gpioDirection25
L__MIKROBUS_gpioDirection53:
	CP.B	W11, #7
	BRA NZ	L__MIKROBUS_gpioDirection54
	GOTO	L_MIKROBUS_gpioDirection26
L__MIKROBUS_gpioDirection54:
	CP.B	W11, #8
	BRA NZ	L__MIKROBUS_gpioDirection55
	GOTO	L_MIKROBUS_gpioDirection27
L__MIKROBUS_gpioDirection55:
	CP.B	W11, #9
	BRA NZ	L__MIKROBUS_gpioDirection56
	GOTO	L_MIKROBUS_gpioDirection28
L__MIKROBUS_gpioDirection56:
	CP.B	W11, #10
	BRA NZ	L__MIKROBUS_gpioDirection57
	GOTO	L_MIKROBUS_gpioDirection29
L__MIKROBUS_gpioDirection57:
	CP.B	W11, #11
	BRA NZ	L__MIKROBUS_gpioDirection58
	GOTO	L_MIKROBUS_gpioDirection30
L__MIKROBUS_gpioDirection58:
	GOTO	L_MIKROBUS_gpioDirection31
L_MIKROBUS_gpioDirection18:
L_MIKROBUS_gpioDirection16:
L_end_MIKROBUS_gpioDirection:
	RETURN
; end of _MIKROBUS_gpioDirection

_MIKROBUS1_spiDriverMap:

	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
; fCall start address is: 16 (W8)
	MOV	W10, W8
	ADD	W11, #28, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W7
	ADD	W11, #24, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W6
	ADD	W11, #20, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W5
	ADD	W11, #16, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W4
	ADD	W11, #12, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W3
	ADD	W11, #8, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W2
	ADD	W11, #4, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W11], W0
	MOV	W3, W13
	MOV	W2, W12
	MOV	W1, W11
	MOV	W0, W10
	PUSH	W7
	PUSH	W6
	PUSH	W5
	PUSH	W4
	CALL	_SPI1_Init_Advanced
	SUB	#8, W15
	PUSH	W8
	MOV	#lo_addr(_SPI1_Read), W11
	MOV	#lo_addr(_SPI1_Write), W10
	CALL	W8
; fCall end address is: 16 (W8)
	POP	W8
L_end_MIKROBUS1_spiDriverMap:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	RETURN
; end of _MIKROBUS1_spiDriverMap

_MIKROBUS2_spiDriverMap:

	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
; fCall start address is: 16 (W8)
	MOV	W10, W8
	ADD	W11, #28, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W7
	ADD	W11, #24, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W6
	ADD	W11, #20, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W5
	ADD	W11, #16, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W4
	ADD	W11, #12, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W3
	ADD	W11, #8, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W2
	ADD	W11, #4, W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W1], W1
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV	[W11], W0
	MOV	W3, W13
	MOV	W2, W12
	MOV	W1, W11
	MOV	W0, W10
	PUSH	W7
	PUSH	W6
	PUSH	W5
	PUSH	W4
	CALL	_SPI1_Init_Advanced
	SUB	#8, W15
	PUSH	W8
	MOV	#lo_addr(_SPI1_Read), W11
	MOV	#lo_addr(_SPI1_Write), W10
	CALL	W8
; fCall end address is: 16 (W8)
	POP	W8
L_end_MIKROBUS2_spiDriverMap:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	RETURN
; end of _MIKROBUS2_spiDriverMap

_MIKROBUS1_i2cDriverMap:
	LNK	#2

	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	MOV	W10, [W14+0]
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV.D	[W11], W10
	CALL	_I2C2_Init
	MOV	#lo_addr(_I2C2_Write), W13
	MOV	#lo_addr(_I2C2_Restart), W12
	MOV	#lo_addr(_I2C2_Stop), W11
	MOV	#lo_addr(_I2C2_Start), W10
	MOV	#lo_addr(_I2C2_Read), W0
	PUSH	W0
	MOV	[W14+0], W0
	CALL	W0
	SUB	#2, W15
L_end_MIKROBUS1_i2cDriverMap:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	ULNK
	RETURN
; end of _MIKROBUS1_i2cDriverMap

_MIKROBUS2_i2cDriverMap:
	LNK	#2

	PUSH	W10
	PUSH	W11
	PUSH	W12
	PUSH	W13
	MOV	W10, [W14+0]
	MOV	#___Lib_System_DefaultPage, W0
	MOV	WREG, 52
	MOV.D	[W11], W10
	CALL	_I2C2_Init
	MOV	#lo_addr(_I2C2_Write), W13
	MOV	#lo_addr(_I2C2_Restart), W12
	MOV	#lo_addr(_I2C2_Stop), W11
	MOV	#lo_addr(_I2C2_Start), W10
	MOV	#lo_addr(_I2C2_Read), W0
	PUSH	W0
	MOV	[W14+0], W0
	CALL	W0
	SUB	#2, W15
L_end_MIKROBUS2_i2cDriverMap:
	POP	W13
	POP	W12
	POP	W11
	POP	W10
	ULNK
	RETURN
; end of _MIKROBUS2_i2cDriverMap

_MIKROBUS1_getAN:

	CLR.B	W0
	BTSC	RB8_bit, BitPos(RB8_bit+0)
	INC.B	W0
L_end_MIKROBUS1_getAN:
	RETURN
; end of _MIKROBUS1_getAN

_MIKROBUS1_setAN:

	BTSS	W10, #0
	BCLR	LATB8_bit, BitPos(LATB8_bit+0)
	BTSC	W10, #0
	BSET	LATB8_bit, BitPos(LATB8_bit+0)
L_end_MIKROBUS1_setAN:
	RETURN
; end of _MIKROBUS1_setAN

_MIKROBUS2_getAN:

	CLR.B	W0
	BTSC	RB9_bit, BitPos(RB9_bit+0)
	INC.B	W0
L_end_MIKROBUS2_getAN:
	RETURN
; end of _MIKROBUS2_getAN

_MIKROBUS2_setAN:

	BTSS	W10, #0
	BCLR	LATB9_bit, BitPos(LATB9_bit+0)
	BTSC	W10, #0
	BSET	LATB9_bit, BitPos(LATB9_bit+0)
L_end_MIKROBUS2_setAN:
	RETURN
; end of _MIKROBUS2_setAN

_MIKROBUS1_getRST:

	CLR.B	W0
	BTSC	RC1_bit, BitPos(RC1_bit+0)
	INC.B	W0
L_end_MIKROBUS1_getRST:
	RETURN
; end of _MIKROBUS1_getRST

_MIKROBUS1_setRST:

	BTSS	W10, #0
	BCLR	LATC1_bit, BitPos(LATC1_bit+0)
	BTSC	W10, #0
	BSET	LATC1_bit, BitPos(LATC1_bit+0)
L_end_MIKROBUS1_setRST:
	RETURN
; end of _MIKROBUS1_setRST

_MIKROBUS2_getRST:

	CLR.B	W0
	BTSC	RC3_bit, BitPos(RC3_bit+0)
	INC.B	W0
L_end_MIKROBUS2_getRST:
	RETURN
; end of _MIKROBUS2_getRST

_MIKROBUS2_setRST:

	BTSS	W10, #0
	BCLR	LATC3_bit, BitPos(LATC3_bit+0)
	BTSC	W10, #0
	BSET	LATC3_bit, BitPos(LATC3_bit+0)
L_end_MIKROBUS2_setRST:
	RETURN
; end of _MIKROBUS2_setRST

_MIKROBUS1_getCS:

	CLR.B	W0
	BTSC	RC2_bit, BitPos(RC2_bit+0)
	INC.B	W0
L_end_MIKROBUS1_getCS:
	RETURN
; end of _MIKROBUS1_getCS

_MIKROBUS1_setCS:

	BTSS	W10, #0
	BCLR	LATC2_bit, BitPos(LATC2_bit+0)
	BTSC	W10, #0
	BSET	LATC2_bit, BitPos(LATC2_bit+0)
L_end_MIKROBUS1_setCS:
	RETURN
; end of _MIKROBUS1_setCS

_MIKROBUS2_getCS:

	CLR.B	W0
	BTSC	RC4_bit, BitPos(RC4_bit+0)
	INC.B	W0
L_end_MIKROBUS2_getCS:
	RETURN
; end of _MIKROBUS2_getCS

_MIKROBUS2_setCS:

	BTSS	W10, #0
	BCLR	LATC4_bit, BitPos(LATC4_bit+0)
	BTSC	W10, #0
	BSET	LATC4_bit, BitPos(LATC4_bit+0)
L_end_MIKROBUS2_setCS:
	RETURN
; end of _MIKROBUS2_setCS

_MIKROBUS1_getPWM:

	CLR.B	W0
	BTSC	RD0_bit, BitPos(RD0_bit+0)
	INC.B	W0
L_end_MIKROBUS1_getPWM:
	RETURN
; end of _MIKROBUS1_getPWM

_MIKROBUS1_setPWM:

	BTSS	W10, #0
	BCLR	LATD0_bit, BitPos(LATD0_bit+0)
	BTSC	W10, #0
	BSET	LATD0_bit, BitPos(LATD0_bit+0)
L_end_MIKROBUS1_setPWM:
	RETURN
; end of _MIKROBUS1_setPWM

_MIKROBUS2_getPWM:

	CLR.B	W0
	BTSC	RD1_bit, BitPos(RD1_bit+0)
	INC.B	W0
L_end_MIKROBUS2_getPWM:
	RETURN
; end of _MIKROBUS2_getPWM

_MIKROBUS2_setPWM:

	BTSS	W10, #0
	BCLR	LATD1_bit, BitPos(LATD1_bit+0)
	BTSC	W10, #0
	BSET	LATD1_bit, BitPos(LATD1_bit+0)
L_end_MIKROBUS2_setPWM:
	RETURN
; end of _MIKROBUS2_setPWM

_MIKROBUS1_getINT:

L_end_MIKROBUS1_getINT:
	RETURN
; end of _MIKROBUS1_getINT

_MIKROBUS1_setINT:

L_end_MIKROBUS1_setINT:
	RETURN
; end of _MIKROBUS1_setINT

_MIKROBUS2_getINT:

L_end_MIKROBUS2_getINT:
	RETURN
; end of _MIKROBUS2_getINT

_MIKROBUS2_setINT:

L_end_MIKROBUS2_setINT:
	RETURN
; end of _MIKROBUS2_setINT
