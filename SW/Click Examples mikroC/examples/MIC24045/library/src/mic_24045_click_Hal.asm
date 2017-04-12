_hal_delay:
;mic_24045_click_Hal.c,122 :: 		void hal_delay( uint16_t ms )
ADDIU	SP, SP, -4
SW	RA, 0(SP)
;mic_24045_click_Hal.c,131 :: 		while( ms-- )
L_hal_delay0:
ANDI	R3, R25, 65535
ADDIU	R2, R25, -1
ANDI	R25, R2, 65535
BNE	R3, R0, L__hal_delay14
NOP	
J	L_hal_delay1
NOP	
L__hal_delay14:
;mic_24045_click_Hal.c,132 :: 		Delay_1ms();
JAL	_Delay_1ms+0
NOP	
J	L_hal_delay0
NOP	
L_hal_delay1:
;mic_24045_click_Hal.c,134 :: 		}
L_end_hal_delay:
LW	RA, 0(SP)
ADDIU	SP, SP, 4
JR	RA
NOP	
; end of _hal_delay
_hal_init:
;mic_24045_click_Hal.c,136 :: 		uint16_t hal_init( uint8_t address_id )
;mic_24045_click_Hal.c,181 :: 		is_idle_i2c_p               = I2C_Is_Idle_Ptr;
LW	R2, Offset(_I2C_Is_Idle_Ptr+0)(GP)
SW	R2, Offset(mic_24045_click_Hal_is_idle_i2c_p+0)(GP)
;mic_24045_click_Hal.c,182 :: 		start_i2c_p                 = I2C_Start_Ptr;
LW	R2, Offset(_I2C_Start_Ptr+0)(GP)
SW	R2, Offset(mic_24045_click_Hal_start_i2c_p+0)(GP)
;mic_24045_click_Hal.c,183 :: 		stop_i2c_p                  = I2C_Stop_Ptr;
LW	R2, Offset(_I2C_Stop_Ptr+0)(GP)
SW	R2, Offset(mic_24045_click_Hal_stop_i2c_p+0)(GP)
;mic_24045_click_Hal.c,184 :: 		restart_i2c_p               = I2C_Restart_Ptr;
LW	R2, Offset(_I2C_Restart_Ptr+0)(GP)
SW	R2, Offset(mic_24045_click_Hal_restart_i2c_p+0)(GP)
;mic_24045_click_Hal.c,185 :: 		write_i2c_p                 = I2C_Write_Ptr;
LW	R2, Offset(_I2C_Write_Ptr+0)(GP)
SW	R2, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
;mic_24045_click_Hal.c,186 :: 		read_i2c_p                  = I2C_Read_Ptr;
LW	R2, Offset(_I2C_Read_Ptr+0)(GP)
SW	R2, Offset(mic_24045_click_Hal_read_i2c_p+0)(GP)
;mic_24045_click_Hal.c,211 :: 		return 0;
MOVZ	R2, R0, R0
;mic_24045_click_Hal.c,212 :: 		}
L_end_hal_init:
JR	RA
NOP	
; end of _hal_init
_hal_write:
;mic_24045_click_Hal.c,219 :: 		)
ADDIU	SP, SP, -28
SW	RA, 0(SP)
;mic_24045_click_Hal.c,221 :: 		uint16_t res = 0;
SW	R25, 4(SP)
MOVZ	R30, R0, R0
SH	R30, 24(SP)
;mic_24045_click_Hal.c,222 :: 		uint8_t *ptr = buffer;
SW	R26, 20(SP)
;mic_24045_click_Hal.c,254 :: 		res |= start_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_start_i2c_p+0)(GP)
SH	R27, 8(SP)
SB	R25, 10(SP)
JALR	RA, R30
NOP	
LBU	R25, 10(SP)
LHU	R3, 24(SP)
OR	R2, R3, R2
SH	R2, 24(SP)
;mic_24045_click_Hal.c,255 :: 		write_i2c_p( ( i2c_address << 1 ) | WRITE_BIT );
ANDI	R2, R25, 255
SLL	R2, R2, 1
ANDI	R25, R2, 255
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LHU	R27, 8(SP)
;mic_24045_click_Hal.c,256 :: 		while( count-- )
L_hal_write2:
ANDI	R3, R27, 65535
ADDIU	R2, R27, -1
ANDI	R27, R2, 65535
BNE	R3, R0, L__hal_write18
NOP	
J	L_hal_write3
NOP	
L__hal_write18:
;mic_24045_click_Hal.c,257 :: 		write_i2c_p( *ptr++ );
LW	R2, 20(SP)
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
LBU	R25, 0(R2)
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
LW	R2, 20(SP)
ADDIU	R2, R2, 1
SW	R2, 20(SP)
J	L_hal_write2
NOP	
L_hal_write3:
;mic_24045_click_Hal.c,258 :: 		stop_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_stop_i2c_p+0)(GP)
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
;mic_24045_click_Hal.c,260 :: 		return res;
LHU	R2, 24(SP)
;mic_24045_click_Hal.c,261 :: 		}
;mic_24045_click_Hal.c,260 :: 		return res;
;mic_24045_click_Hal.c,261 :: 		}
L_end_hal_write:
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 28
JR	RA
NOP	
; end of _hal_write
_hal_read:
;mic_24045_click_Hal.c,268 :: 		)
ADDIU	SP, SP, -28
SW	RA, 0(SP)
;mic_24045_click_Hal.c,270 :: 		uint16_t res = 0;
SW	R25, 4(SP)
MOVZ	R30, R0, R0
SH	R30, 24(SP)
;mic_24045_click_Hal.c,271 :: 		uint8_t *ptr = buffer;
SW	R26, 20(SP)
;mic_24045_click_Hal.c,310 :: 		res |= start_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_start_i2c_p+0)(GP)
SH	R27, 8(SP)
SB	R25, 10(SP)
JALR	RA, R30
NOP	
LBU	R25, 10(SP)
LHU	R3, 24(SP)
OR	R2, R3, R2
SH	R2, 24(SP)
;mic_24045_click_Hal.c,311 :: 		write_i2c_p( ( i2c_address << 1 ) | WRITE_BIT );
ANDI	R2, R25, 255
SLL	R2, R2, 1
SB	R25, 10(SP)
ANDI	R25, R2, 255
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
;mic_24045_click_Hal.c,312 :: 		write_i2c_p( *ptr );
LW	R2, 20(SP)
LBU	R25, 0(R2)
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
;mic_24045_click_Hal.c,313 :: 		stop_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_stop_i2c_p+0)(GP)
JALR	RA, R30
NOP	
;mic_24045_click_Hal.c,314 :: 		Delay_ms( 5 );
LUI	R24, 2
ORI	R24, R24, 2260
L_hal_read4:
ADDIU	R24, R24, -1
BNE	R24, R0, L_hal_read4
NOP	
NOP	
NOP	
;mic_24045_click_Hal.c,315 :: 		res |= start_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_start_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 10(SP)
LHU	R3, 24(SP)
OR	R2, R3, R2
SH	R2, 24(SP)
;mic_24045_click_Hal.c,316 :: 		write_i2c_p( ( i2c_address << 1 ) | READ_BIT );
ANDI	R2, R25, 255
SLL	R2, R2, 1
ORI	R2, R2, 1
ANDI	R25, R2, 255
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LHU	R27, 8(SP)
;mic_24045_click_Hal.c,317 :: 		while( --count )
L_hal_read6:
ADDIU	R2, R27, -1
ANDI	R27, R2, 65535
BNE	R2, R0, L__hal_read21
NOP	
J	L_hal_read7
NOP	
L__hal_read21:
;mic_24045_click_Hal.c,318 :: 		*ptr++ = read_i2c_p( ACK_BIT );
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
LBU	R25, Offset(mic_24045_click_Hal_ACK_BIT+0)(GP)
LW	R30, Offset(mic_24045_click_Hal_read_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
LW	R3, 20(SP)
SB	R2, 0(R3)
LW	R2, 20(SP)
ADDIU	R2, R2, 1
SW	R2, 20(SP)
J	L_hal_read6
NOP	
L_hal_read7:
;mic_24045_click_Hal.c,319 :: 		*ptr = read_i2c_p( NACK_BIT );
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
LBU	R25, Offset(mic_24045_click_Hal_NACK_BIT+0)(GP)
LW	R30, Offset(mic_24045_click_Hal_read_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LW	R3, 20(SP)
SB	R2, 0(R3)
;mic_24045_click_Hal.c,320 :: 		stop_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_stop_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
;mic_24045_click_Hal.c,322 :: 		return res;
LHU	R2, 24(SP)
;mic_24045_click_Hal.c,323 :: 		}
;mic_24045_click_Hal.c,322 :: 		return res;
;mic_24045_click_Hal.c,323 :: 		}
L_end_hal_read:
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 28
JR	RA
NOP	
; end of _hal_read
_hal_transfer:
;mic_24045_click_Hal.c,332 :: 		)
ADDIU	SP, SP, -32
SW	RA, 0(SP)
LHU	R2, 32(SP)
SH	R2, 32(SP)
;mic_24045_click_Hal.c,334 :: 		uint16_t res = 0;
MOVZ	R30, R0, R0
SH	R30, 28(SP)
;mic_24045_click_Hal.c,335 :: 		uint8_t *in = input;
SW	R26, 20(SP)
;mic_24045_click_Hal.c,336 :: 		uint8_t *out = output;
SW	R28, 24(SP)
;mic_24045_click_Hal.c,404 :: 		res |= start_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_start_i2c_p+0)(GP)
SH	R27, 4(SP)
SB	R25, 6(SP)
JALR	RA, R30
NOP	
LBU	R25, 6(SP)
LHU	R3, 28(SP)
OR	R2, R3, R2
SH	R2, 28(SP)
;mic_24045_click_Hal.c,405 :: 		write_i2c_p( ( i2c_address << 1 ) | WRITE_BIT );
ANDI	R2, R25, 255
SLL	R2, R2, 1
SB	R25, 6(SP)
ANDI	R25, R2, 255
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 6(SP)
LHU	R27, 4(SP)
;mic_24045_click_Hal.c,406 :: 		while( in_count-- )
L_hal_transfer8:
ANDI	R3, R27, 65535
ADDIU	R2, R27, -1
ANDI	R27, R2, 65535
BNE	R3, R0, L__hal_transfer24
NOP	
J	L_hal_transfer9
NOP	
L__hal_transfer24:
;mic_24045_click_Hal.c,407 :: 		write_i2c_p( *in++ );
LW	R2, 20(SP)
SW	R28, 4(SP)
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
LBU	R25, 0(R2)
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
LW	R28, 4(SP)
LW	R2, 20(SP)
ADDIU	R2, R2, 1
SW	R2, 20(SP)
J	L_hal_transfer8
NOP	
L_hal_transfer9:
;mic_24045_click_Hal.c,408 :: 		restart_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_restart_i2c_p+0)(GP)
SW	R28, 4(SP)
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
;mic_24045_click_Hal.c,409 :: 		write_i2c_p( ( i2c_address << 1 ) | READ_BIT );
ANDI	R2, R25, 255
SLL	R2, R2, 1
ORI	R2, R2, 1
SB	R25, 16(SP)
ANDI	R25, R2, 255
LW	R30, Offset(mic_24045_click_Hal_write_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
LW	R28, 4(SP)
;mic_24045_click_Hal.c,410 :: 		while( --out_count )
L_hal_transfer10:
LHU	R2, 32(SP)
ADDIU	R2, R2, -1
SH	R2, 32(SP)
BNE	R2, R0, L__hal_transfer26
NOP	
J	L_hal_transfer11
NOP	
L__hal_transfer26:
;mic_24045_click_Hal.c,411 :: 		*out++ = read_i2c_p( ACK_BIT );
SW	R28, 4(SP)
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
LBU	R25, Offset(mic_24045_click_Hal_ACK_BIT+0)(GP)
LW	R30, Offset(mic_24045_click_Hal_read_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
LW	R28, 4(SP)
LW	R3, 24(SP)
SB	R2, 0(R3)
LW	R2, 24(SP)
ADDIU	R2, R2, 1
SW	R2, 24(SP)
J	L_hal_transfer10
NOP	
L_hal_transfer11:
;mic_24045_click_Hal.c,412 :: 		*out = read_i2c_p( NACK_BIT );
SW	R28, 4(SP)
SH	R27, 8(SP)
SW	R26, 12(SP)
SB	R25, 16(SP)
LBU	R25, Offset(mic_24045_click_Hal_NACK_BIT+0)(GP)
LW	R30, Offset(mic_24045_click_Hal_read_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LW	R3, 24(SP)
SB	R2, 0(R3)
;mic_24045_click_Hal.c,413 :: 		stop_i2c_p();
LW	R30, Offset(mic_24045_click_Hal_stop_i2c_p+0)(GP)
JALR	RA, R30
NOP	
LBU	R25, 16(SP)
LW	R26, 12(SP)
LHU	R27, 8(SP)
LW	R28, 4(SP)
;mic_24045_click_Hal.c,416 :: 		return res;
LHU	R2, 28(SP)
;mic_24045_click_Hal.c,417 :: 		}
L_end_hal_transfer:
LW	RA, 0(SP)
ADDIU	SP, SP, 32
JR	RA
NOP	
; end of _hal_transfer
