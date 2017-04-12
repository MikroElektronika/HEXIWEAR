mic_24045_click__mic_24045_read:
;mic_24045_click.c,42 :: 		static uint16_t _mic_24045_read ( uint8_t reg, uint8_t *output )
ADDIU	SP, SP, -16
SW	RA, 0(SP)
;mic_24045_click.c,44 :: 		uint8_t *out = output;
SW	R25, 4(SP)
SW	R26, 8(SP)
SW	R27, 12(SP)
; out start address is: 8 (R2)
MOVZ	R2, R26, R0
;mic_24045_click.c,45 :: 		*out = reg;
SB	R25, 0(R26)
;mic_24045_click.c,46 :: 		hal_read( _i2c_hw_address, out ,1 );
ORI	R27, R0, 1
MOVZ	R26, R2, R0
; out end address is: 8 (R2)
ORI	R25, R0, 80
JAL	_hal_read+0
NOP	
;mic_24045_click.c,47 :: 		return MIC24045_CLICK_OK;
MOVZ	R2, R0, R0
;mic_24045_click.c,48 :: 		}
;mic_24045_click.c,47 :: 		return MIC24045_CLICK_OK;
;mic_24045_click.c,48 :: 		}
L_end__mic_24045_read:
LW	R27, 12(SP)
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 16
JR	RA
NOP	
; end of mic_24045_click__mic_24045_read
mic_24045_click__mic_24045_write:
;mic_24045_click.c,51 :: 		static uint16_t _mic_24045_write ( uint8_t reg, uint8_t wr_data)
ADDIU	SP, SP, -20
SW	RA, 0(SP)
;mic_24045_click.c,54 :: 		input[ 0 ] = reg;
SW	R25, 4(SP)
SW	R26, 8(SP)
SW	R27, 12(SP)
ADDIU	R3, SP, 16
SB	R25, 0(R3)
;mic_24045_click.c,55 :: 		input[ 1 ] = wr_data;
ADDIU	R2, R3, 1
SB	R26, 0(R2)
;mic_24045_click.c,56 :: 		hal_write( _i2c_hw_address, input, 2 );
ORI	R27, R0, 2
MOVZ	R26, R3, R0
ORI	R25, R0, 80
JAL	_hal_write+0
NOP	
;mic_24045_click.c,57 :: 		return MIC24045_CLICK_OK;
MOVZ	R2, R0, R0
;mic_24045_click.c,58 :: 		}
;mic_24045_click.c,57 :: 		return MIC24045_CLICK_OK;
;mic_24045_click.c,58 :: 		}
L_end__mic_24045_write:
LW	R27, 12(SP)
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 20
JR	RA
NOP	
; end of mic_24045_click__mic_24045_write
mic_24045_click__mic_24045_float2bit:
;mic_24045_click.c,60 :: 		static uint8_t _mic_24045_float2bit (float vout)
ADDIU	SP, SP, -4
SW	RA, 0(SP)
;mic_24045_click.c,62 :: 		uint8_t _value = 0;
;mic_24045_click.c,63 :: 		if (vout >= 5.250)
LUI	R4, 16552
ORI	R4, R4, 0
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 1
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit62
NOP	
J	L_mic_24045_click__mic_24045_float2bit0
NOP	
L_mic_24045_click__mic_24045_float2bit62:
;mic_24045_click.c,66 :: 		return _value;
ORI	R2, R0, 255
J	L_end__mic_24045_float2bit
NOP	
;mic_24045_click.c,67 :: 		}
L_mic_24045_click__mic_24045_float2bit0:
;mic_24045_click.c,68 :: 		else if (vout >= 4.750)
LUI	R4, 16536
ORI	R4, R4, 0
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 1
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit65
NOP	
J	L_mic_24045_click__mic_24045_float2bit2
NOP	
L_mic_24045_click__mic_24045_float2bit65:
;mic_24045_click.c,70 :: 		_value = 0xf5;
; _value start address is: 12 (R3)
ORI	R3, R0, 245
; _value end address is: 12 (R3)
;mic_24045_click.c,71 :: 		while (vout > 4.750)
L_mic_24045_click__mic_24045_float2bit3:
; _value start address is: 12 (R3)
LUI	R4, 16536
ORI	R4, R4, 0
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 0
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit68
NOP	
J	L_mic_24045_click__mic_24045_float2bit4
NOP	
L_mic_24045_click__mic_24045_float2bit68:
;mic_24045_click.c,73 :: 		_value++;
ADDIU	R2, R3, 1
ANDI	R3, R2, 255
;mic_24045_click.c,74 :: 		vout -= 0.05;
LUI	R6, 15692
ORI	R6, R6, 52429
MOVZ	R4, R25, R0
JAL	__Sub_FP+0
NOP	
MOVZ	R25, R2, R0
;mic_24045_click.c,75 :: 		}
J	L_mic_24045_click__mic_24045_float2bit3
NOP	
L_mic_24045_click__mic_24045_float2bit4:
;mic_24045_click.c,76 :: 		return _value;
ANDI	R2, R3, 255
; _value end address is: 12 (R3)
J	L_end__mic_24045_float2bit
NOP	
;mic_24045_click.c,77 :: 		}
L_mic_24045_click__mic_24045_float2bit2:
;mic_24045_click.c,78 :: 		else if (vout >= 3.420)
LUI	R4, 16474
ORI	R4, R4, 57672
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 1
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit71
NOP	
J	L_mic_24045_click__mic_24045_float2bit6
NOP	
L_mic_24045_click__mic_24045_float2bit71:
;mic_24045_click.c,81 :: 		return _value;
ORI	R2, R0, 244
J	L_end__mic_24045_float2bit
NOP	
;mic_24045_click.c,82 :: 		}
L_mic_24045_click__mic_24045_float2bit6:
;mic_24045_click.c,83 :: 		else if (vout >= 1.980)
LUI	R4, 16381
ORI	R4, R4, 28836
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 1
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit74
NOP	
J	L_mic_24045_click__mic_24045_float2bit8
NOP	
L_mic_24045_click__mic_24045_float2bit74:
;mic_24045_click.c,85 :: 		_value = 0xc4;
; _value start address is: 12 (R3)
ORI	R3, R0, 196
; _value end address is: 12 (R3)
;mic_24045_click.c,86 :: 		while (vout > 1.980)
L_mic_24045_click__mic_24045_float2bit9:
; _value start address is: 12 (R3)
LUI	R4, 16381
ORI	R4, R4, 28836
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 0
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit77
NOP	
J	L_mic_24045_click__mic_24045_float2bit10
NOP	
L_mic_24045_click__mic_24045_float2bit77:
;mic_24045_click.c,88 :: 		_value++;
ADDIU	R2, R3, 1
ANDI	R3, R2, 255
;mic_24045_click.c,89 :: 		vout -= 0.03;
LUI	R6, 15605
ORI	R6, R6, 49807
MOVZ	R4, R25, R0
JAL	__Sub_FP+0
NOP	
MOVZ	R25, R2, R0
;mic_24045_click.c,90 :: 		}
J	L_mic_24045_click__mic_24045_float2bit9
NOP	
L_mic_24045_click__mic_24045_float2bit10:
;mic_24045_click.c,91 :: 		return _value;
ANDI	R2, R3, 255
; _value end address is: 12 (R3)
J	L_end__mic_24045_float2bit
NOP	
;mic_24045_click.c,92 :: 		}
L_mic_24045_click__mic_24045_float2bit8:
;mic_24045_click.c,93 :: 		else if (vout >= 1.290)
LUI	R4, 16293
ORI	R4, R4, 7864
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 1
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit80
NOP	
J	L_mic_24045_click__mic_24045_float2bit12
NOP	
L_mic_24045_click__mic_24045_float2bit80:
;mic_24045_click.c,95 :: 		_value = 0x81;
; _value start address is: 12 (R3)
ORI	R3, R0, 129
; _value end address is: 12 (R3)
;mic_24045_click.c,96 :: 		while (vout > 1.290)
L_mic_24045_click__mic_24045_float2bit13:
; _value start address is: 12 (R3)
LUI	R4, 16293
ORI	R4, R4, 7864
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 0
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit83
NOP	
J	L_mic_24045_click__mic_24045_float2bit14
NOP	
L_mic_24045_click__mic_24045_float2bit83:
;mic_24045_click.c,98 :: 		_value++;
ADDIU	R2, R3, 1
ANDI	R3, R2, 255
;mic_24045_click.c,99 :: 		vout -= 0.01;
LUI	R6, 15395
ORI	R6, R6, 55050
MOVZ	R4, R25, R0
JAL	__Sub_FP+0
NOP	
MOVZ	R25, R2, R0
;mic_24045_click.c,100 :: 		}
J	L_mic_24045_click__mic_24045_float2bit13
NOP	
L_mic_24045_click__mic_24045_float2bit14:
;mic_24045_click.c,101 :: 		return _value;
ANDI	R2, R3, 255
; _value end address is: 12 (R3)
J	L_end__mic_24045_float2bit
NOP	
;mic_24045_click.c,102 :: 		}
L_mic_24045_click__mic_24045_float2bit12:
;mic_24045_click.c,103 :: 		else if (vout >= 0.640)
LUI	R4, 16163
ORI	R4, R4, 55050
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 1
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit86
NOP	
J	L_mic_24045_click__mic_24045_float2bit16
NOP	
L_mic_24045_click__mic_24045_float2bit86:
;mic_24045_click.c,105 :: 		_value = 0x00;
; _value start address is: 12 (R3)
MOVZ	R3, R0, R0
; _value end address is: 12 (R3)
;mic_24045_click.c,106 :: 		while (vout > 0.640)
L_mic_24045_click__mic_24045_float2bit17:
; _value start address is: 12 (R3)
LUI	R4, 16163
ORI	R4, R4, 55050
MOVZ	R6, R25, R0
JAL	__Compare_FP+0
NOP	
SLTI	R2, R2, 0
BNE	R2, R0, L_mic_24045_click__mic_24045_float2bit89
NOP	
J	L_mic_24045_click__mic_24045_float2bit18
NOP	
L_mic_24045_click__mic_24045_float2bit89:
;mic_24045_click.c,108 :: 		_value++;
ADDIU	R2, R3, 1
ANDI	R3, R2, 255
;mic_24045_click.c,109 :: 		vout -= 0.005;
LUI	R6, 15267
ORI	R6, R6, 55050
MOVZ	R4, R25, R0
JAL	__Sub_FP+0
NOP	
MOVZ	R25, R2, R0
;mic_24045_click.c,110 :: 		}
J	L_mic_24045_click__mic_24045_float2bit17
NOP	
L_mic_24045_click__mic_24045_float2bit18:
;mic_24045_click.c,111 :: 		return _value;
ANDI	R2, R3, 255
; _value end address is: 12 (R3)
J	L_end__mic_24045_float2bit
NOP	
;mic_24045_click.c,112 :: 		}
L_mic_24045_click__mic_24045_float2bit16:
;mic_24045_click.c,114 :: 		return _value;
MOVZ	R2, R0, R0
;mic_24045_click.c,115 :: 		}
L_end__mic_24045_float2bit:
LW	RA, 0(SP)
ADDIU	SP, SP, 4
JR	RA
NOP	
; end of mic_24045_click__mic_24045_float2bit
mic_24045_click__mic_24045_bit2float:
;mic_24045_click.c,117 :: 		static float _mic_24045_bit2float (uint8_t _value)
ADDIU	SP, SP, -4
SW	RA, 0(SP)
;mic_24045_click.c,119 :: 		float _retval = 0;
; _retval start address is: 12 (R3)
MOVZ	R3, R0, R0
;mic_24045_click.c,120 :: 		if (_value >= 0 && _value <= 0x80)
ANDI	R2, R25, 255
SLTIU	R2, R2, 0
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float91
NOP	
J	L_mic_24045_click__mic_24045_bit2float50
NOP	
L_mic_24045_click__mic_24045_bit2float91:
ANDI	R2, R25, 255
SLTIU	R2, R2, 129
BNE	R2, R0, L_mic_24045_click__mic_24045_bit2float92
NOP	
J	L_mic_24045_click__mic_24045_bit2float49
NOP	
L_mic_24045_click__mic_24045_bit2float92:
; _retval end address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float48:
;mic_24045_click.c,122 :: 		_retval = 0.640;
; _retval start address is: 12 (R3)
LUI	R3, 16163
ORI	R3, R3, 55050
; _retval end address is: 12 (R3)
;mic_24045_click.c,123 :: 		while (_value > 0)
L_mic_24045_click__mic_24045_bit2float23:
; _retval start address is: 12 (R3)
ANDI	R2, R25, 255
SLTIU	R2, R2, 1
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float93
NOP	
J	L_mic_24045_click__mic_24045_bit2float24
NOP	
L_mic_24045_click__mic_24045_bit2float93:
;mic_24045_click.c,125 :: 		_retval += 0.005;
LUI	R4, 15267
ORI	R4, R4, 55050
MOVZ	R6, R3, R0
JAL	__Add_FP+0
NOP	
MOVZ	R3, R2, R0
;mic_24045_click.c,126 :: 		_value --;
ADDIU	R2, R25, -1
ANDI	R25, R2, 255
;mic_24045_click.c,127 :: 		}
J	L_mic_24045_click__mic_24045_bit2float23
NOP	
L_mic_24045_click__mic_24045_bit2float24:
;mic_24045_click.c,128 :: 		return _retval;
MOVZ	R2, R3, R0
; _retval end address is: 12 (R3)
J	L_end__mic_24045_bit2float
NOP	
;mic_24045_click.c,120 :: 		if (_value >= 0 && _value <= 0x80)
L_mic_24045_click__mic_24045_bit2float50:
; _retval start address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float49:
;mic_24045_click.c,130 :: 		else if (_value >= 0x81 && _value <= 0xC3)
ANDI	R2, R25, 255
SLTIU	R2, R2, 129
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float94
NOP	
J	L_mic_24045_click__mic_24045_bit2float52
NOP	
L_mic_24045_click__mic_24045_bit2float94:
ANDI	R2, R25, 255
SLTIU	R2, R2, 196
BNE	R2, R0, L_mic_24045_click__mic_24045_bit2float95
NOP	
J	L_mic_24045_click__mic_24045_bit2float51
NOP	
L_mic_24045_click__mic_24045_bit2float95:
; _retval end address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float47:
;mic_24045_click.c,132 :: 		_retval = 1.290;
; _retval start address is: 12 (R3)
LUI	R3, 16293
ORI	R3, R3, 7864
; _retval end address is: 12 (R3)
;mic_24045_click.c,133 :: 		while (_value > 0x81)
L_mic_24045_click__mic_24045_bit2float29:
; _retval start address is: 12 (R3)
ANDI	R2, R25, 255
SLTIU	R2, R2, 130
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float96
NOP	
J	L_mic_24045_click__mic_24045_bit2float30
NOP	
L_mic_24045_click__mic_24045_bit2float96:
;mic_24045_click.c,135 :: 		_retval += 0.010;
LUI	R4, 15395
ORI	R4, R4, 55050
MOVZ	R6, R3, R0
JAL	__Add_FP+0
NOP	
MOVZ	R3, R2, R0
;mic_24045_click.c,136 :: 		_value --;
ADDIU	R2, R25, -1
ANDI	R25, R2, 255
;mic_24045_click.c,137 :: 		}
J	L_mic_24045_click__mic_24045_bit2float29
NOP	
L_mic_24045_click__mic_24045_bit2float30:
;mic_24045_click.c,138 :: 		return _retval;
MOVZ	R2, R3, R0
; _retval end address is: 12 (R3)
J	L_end__mic_24045_bit2float
NOP	
;mic_24045_click.c,130 :: 		else if (_value >= 0x81 && _value <= 0xC3)
L_mic_24045_click__mic_24045_bit2float52:
; _retval start address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float51:
;mic_24045_click.c,140 :: 		else if (_value >= 0xC4 && _value <= 0xF4)
ANDI	R2, R25, 255
SLTIU	R2, R2, 196
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float97
NOP	
J	L_mic_24045_click__mic_24045_bit2float54
NOP	
L_mic_24045_click__mic_24045_bit2float97:
ANDI	R2, R25, 255
SLTIU	R2, R2, 245
BNE	R2, R0, L_mic_24045_click__mic_24045_bit2float98
NOP	
J	L_mic_24045_click__mic_24045_bit2float53
NOP	
L_mic_24045_click__mic_24045_bit2float98:
; _retval end address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float46:
;mic_24045_click.c,142 :: 		_retval = 1.980;
; _retval start address is: 12 (R3)
LUI	R3, 16381
ORI	R3, R3, 28836
; _retval end address is: 12 (R3)
;mic_24045_click.c,143 :: 		while (_value > 0xC4)
L_mic_24045_click__mic_24045_bit2float35:
; _retval start address is: 12 (R3)
ANDI	R2, R25, 255
SLTIU	R2, R2, 197
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float99
NOP	
J	L_mic_24045_click__mic_24045_bit2float36
NOP	
L_mic_24045_click__mic_24045_bit2float99:
;mic_24045_click.c,145 :: 		_retval += 0.030;
LUI	R4, 15605
ORI	R4, R4, 49807
MOVZ	R6, R3, R0
JAL	__Add_FP+0
NOP	
MOVZ	R3, R2, R0
;mic_24045_click.c,146 :: 		_value --;
ADDIU	R2, R25, -1
ANDI	R25, R2, 255
;mic_24045_click.c,147 :: 		}
J	L_mic_24045_click__mic_24045_bit2float35
NOP	
L_mic_24045_click__mic_24045_bit2float36:
;mic_24045_click.c,148 :: 		return _retval;
MOVZ	R2, R3, R0
; _retval end address is: 12 (R3)
J	L_end__mic_24045_bit2float
NOP	
;mic_24045_click.c,140 :: 		else if (_value >= 0xC4 && _value <= 0xF4)
L_mic_24045_click__mic_24045_bit2float54:
; _retval start address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float53:
;mic_24045_click.c,150 :: 		else if (_value >= 0xF5 && _value <= 0xFF)
ANDI	R2, R25, 255
SLTIU	R2, R2, 245
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float100
NOP	
J	L_mic_24045_click__mic_24045_bit2float56
NOP	
L_mic_24045_click__mic_24045_bit2float100:
ANDI	R2, R25, 255
SLTIU	R2, R2, 256
BNE	R2, R0, L_mic_24045_click__mic_24045_bit2float101
NOP	
J	L_mic_24045_click__mic_24045_bit2float55
NOP	
L_mic_24045_click__mic_24045_bit2float101:
; _retval end address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float45:
;mic_24045_click.c,152 :: 		_retval = 4.750;
; _retval start address is: 12 (R3)
LUI	R3, 16536
ORI	R3, R3, 0
; _retval end address is: 12 (R3)
;mic_24045_click.c,153 :: 		while (_value > 0xF5)
L_mic_24045_click__mic_24045_bit2float41:
; _retval start address is: 12 (R3)
ANDI	R2, R25, 255
SLTIU	R2, R2, 246
BEQ	R2, R0, L_mic_24045_click__mic_24045_bit2float102
NOP	
J	L_mic_24045_click__mic_24045_bit2float42
NOP	
L_mic_24045_click__mic_24045_bit2float102:
;mic_24045_click.c,155 :: 		_retval += 0.050;
LUI	R4, 15692
ORI	R4, R4, 52429
MOVZ	R6, R3, R0
JAL	__Add_FP+0
NOP	
MOVZ	R3, R2, R0
;mic_24045_click.c,156 :: 		_value --;
ADDIU	R2, R25, -1
ANDI	R25, R2, 255
;mic_24045_click.c,157 :: 		}
J	L_mic_24045_click__mic_24045_bit2float41
NOP	
L_mic_24045_click__mic_24045_bit2float42:
;mic_24045_click.c,158 :: 		return _retval;
MOVZ	R2, R3, R0
; _retval end address is: 12 (R3)
J	L_end__mic_24045_bit2float
NOP	
;mic_24045_click.c,150 :: 		else if (_value >= 0xF5 && _value <= 0xFF)
L_mic_24045_click__mic_24045_bit2float56:
; _retval start address is: 12 (R3)
L_mic_24045_click__mic_24045_bit2float55:
;mic_24045_click.c,160 :: 		return _retval;
MOVZ	R2, R3, R0
; _retval end address is: 12 (R3)
;mic_24045_click.c,162 :: 		}
L_end__mic_24045_bit2float:
LW	RA, 0(SP)
ADDIU	SP, SP, 4
JR	RA
NOP	
; end of mic_24045_click__mic_24045_bit2float
_mic_24045_init:
;mic_24045_click.c,169 :: 		uint16_t mic_24045_init (uint8_t i2c_address )
ADDIU	SP, SP, -4
SW	RA, 0(SP)
;mic_24045_click.c,171 :: 		return hal_init( i2c_address);
JAL	_hal_init+0
NOP	
;mic_24045_click.c,172 :: 		}
L_end_mic_24045_init:
LW	RA, 0(SP)
ADDIU	SP, SP, 4
JR	RA
NOP	
; end of _mic_24045_init
_mic_24045_status:
;mic_24045_click.c,174 :: 		bool mic_24045_status (uint8_t cmd)
ADDIU	SP, SP, -12
SW	RA, 0(SP)
;mic_24045_click.c,176 :: 		uint8_t _value = 0;
SW	R26, 4(SP)
MOVZ	R30, R0, R0
SB	R30, 9(SP)
;mic_24045_click.c,177 :: 		_mic_24045_read (MIC24045_STATUS, &_value);
ADDIU	R2, SP, 9
SB	R25, 8(SP)
MOVZ	R26, R2, R0
MOVZ	R25, R0, R0
JAL	mic_24045_click__mic_24045_read+0
NOP	
LBU	R25, 8(SP)
;mic_24045_click.c,178 :: 		if (cmd & _value)
LBU	R2, 9(SP)
AND	R2, R25, R2
BNE	R2, R0, L__mic_24045_status106
NOP	
J	L_mic_24045_status43
NOP	
L__mic_24045_status106:
;mic_24045_click.c,179 :: 		return true;
ORI	R2, R0, 1
J	L_end_mic_24045_status
NOP	
L_mic_24045_status43:
;mic_24045_click.c,180 :: 		else return false;
MOVZ	R2, R0, R0
;mic_24045_click.c,181 :: 		}
;mic_24045_click.c,180 :: 		else return false;
;mic_24045_click.c,181 :: 		}
L_end_mic_24045_status:
LW	R26, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 12
JR	RA
NOP	
; end of _mic_24045_status
_mic_24045_clear_flags:
;mic_24045_click.c,183 :: 		void mic_24045_clear_flags ()
ADDIU	SP, SP, -12
SW	RA, 0(SP)
;mic_24045_click.c,185 :: 		_mic_24045_write (MIC24045_COMMAND, MIC24045_CIFF);
SW	R25, 4(SP)
SW	R26, 8(SP)
ORI	R26, R0, 1
ORI	R25, R0, 4
JAL	mic_24045_click__mic_24045_write+0
NOP	
;mic_24045_click.c,186 :: 		}
L_end_mic_24045_clear_flags:
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 12
JR	RA
NOP	
; end of _mic_24045_clear_flags
_mic_24045_read_vout:
;mic_24045_click.c,189 :: 		float mic_24045_read_vout ()
ADDIU	SP, SP, -16
SW	RA, 0(SP)
;mic_24045_click.c,191 :: 		uint8_t _value = 0;
SW	R25, 4(SP)
SW	R26, 8(SP)
MOVZ	R30, R0, R0
SB	R30, 12(SP)
;mic_24045_click.c,192 :: 		_mic_24045_read (MIC24045_VOUT, &_value);
ADDIU	R2, SP, 12
MOVZ	R26, R2, R0
ORI	R25, R0, 3
JAL	mic_24045_click__mic_24045_read+0
NOP	
;mic_24045_click.c,193 :: 		return _mic_24045_bit2float (_value);
LBU	R25, 12(SP)
JAL	mic_24045_click__mic_24045_bit2float+0
NOP	
;mic_24045_click.c,194 :: 		}
;mic_24045_click.c,193 :: 		return _mic_24045_bit2float (_value);
;mic_24045_click.c,194 :: 		}
L_end_mic_24045_read_vout:
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 16
JR	RA
NOP	
; end of _mic_24045_read_vout
_mic_24045_write_vout:
;mic_24045_click.c,195 :: 		void mic_24045_write_vout (float vout)
ADDIU	SP, SP, -12
SW	RA, 0(SP)
;mic_24045_click.c,197 :: 		uint8_t _value = 0;
SW	R25, 4(SP)
SW	R26, 8(SP)
;mic_24045_click.c,198 :: 		_value = _mic_24045_float2bit (vout);
JAL	mic_24045_click__mic_24045_float2bit+0
NOP	
;mic_24045_click.c,199 :: 		_mic_24045_write (MIC24045_VOUT, _value);
ANDI	R26, R2, 255
ORI	R25, R0, 3
JAL	mic_24045_click__mic_24045_write+0
NOP	
;mic_24045_click.c,200 :: 		}
L_end_mic_24045_write_vout:
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 12
JR	RA
NOP	
; end of _mic_24045_write_vout
_mic_24045_read_settings:
;mic_24045_click.c,204 :: 		uint8_t mic_24045_read_settings (uint8_t reg)
ADDIU	SP, SP, -12
SW	RA, 0(SP)
;mic_24045_click.c,206 :: 		uint8_t _value = 0;
SW	R26, 4(SP)
MOVZ	R30, R0, R0
SB	R30, 8(SP)
;mic_24045_click.c,207 :: 		_mic_24045_read (reg, &_value);
ADDIU	R2, SP, 8
MOVZ	R26, R2, R0
JAL	mic_24045_click__mic_24045_read+0
NOP	
;mic_24045_click.c,208 :: 		return _value;
LBU	R2, 8(SP)
;mic_24045_click.c,209 :: 		}
;mic_24045_click.c,208 :: 		return _value;
;mic_24045_click.c,209 :: 		}
L_end_mic_24045_read_settings:
LW	R26, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 12
JR	RA
NOP	
; end of _mic_24045_read_settings
_mic_24045_write_settings:
;mic_24045_click.c,210 :: 		void mic_24045_write_settings (uint8_t reg, uint8_t set)
ADDIU	SP, SP, -4
SW	RA, 0(SP)
;mic_24045_click.c,212 :: 		_mic_24045_write (reg, set);
JAL	mic_24045_click__mic_24045_write+0
NOP	
;mic_24045_click.c,213 :: 		}
L_end_mic_24045_write_settings:
LW	RA, 0(SP)
ADDIU	SP, SP, 4
JR	RA
NOP	
; end of _mic_24045_write_settings
