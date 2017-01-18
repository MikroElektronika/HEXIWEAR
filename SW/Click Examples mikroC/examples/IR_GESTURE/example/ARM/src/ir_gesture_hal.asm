_ir_gesture_i2c_init:
;ir_gesture_hal.c,64 :: 		int ir_gesture_i2c_init( uint8_t address_id )
; address_id start address is: 0 (R0)
SUB	SP, SP, #4
; address_id end address is: 0 (R0)
; address_id start address is: 0 (R0)
;ir_gesture_hal.c,67 :: 		start_i2c_p = I2C_Start_Ptr;
MOVW	R1, #lo_addr(_I2C_Start_Ptr+0)
MOVT	R1, #hi_addr(_I2C_Start_Ptr+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(ir_gesture_hal_start_i2c_p+0)
MOVT	R1, #hi_addr(ir_gesture_hal_start_i2c_p+0)
STR	R2, [R1, #0]
;ir_gesture_hal.c,68 :: 		write_i2c_p = I2C_Write_Ptr;
MOVW	R1, #lo_addr(_I2C_Write_Ptr+0)
MOVT	R1, #hi_addr(_I2C_Write_Ptr+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(ir_gesture_hal_write_i2c_p+0)
MOVT	R1, #hi_addr(ir_gesture_hal_write_i2c_p+0)
STR	R2, [R1, #0]
;ir_gesture_hal.c,69 :: 		read_i2c_p = I2C_Read_Ptr;
MOVW	R1, #lo_addr(_I2C_Read_Ptr+0)
MOVT	R1, #hi_addr(_I2C_Read_Ptr+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(ir_gesture_hal_read_i2c_p+0)
MOVT	R1, #hi_addr(ir_gesture_hal_read_i2c_p+0)
STR	R2, [R1, #0]
;ir_gesture_hal.c,71 :: 		_i2c_hw_address = address_id;
MOVW	R1, #lo_addr(ir_gesture_hal__i2c_hw_address+0)
MOVT	R1, #hi_addr(ir_gesture_hal__i2c_hw_address+0)
STRB	R0, [R1, #0]
;ir_gesture_hal.c,72 :: 		return ( _i2c_hw_address == 0 ) ? -1 : 0;
CMP	R0, #0
IT	NE
BNE	L_ir_gesture_i2c_init0
; address_id end address is: 0 (R0)
; ?FLOC___ir_gesture_i2c_init?T1 start address is: 0 (R0)
MOVS	R0, #-1
SXTB	R0, R0
; ?FLOC___ir_gesture_i2c_init?T1 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_i2c_init1
L_ir_gesture_i2c_init0:
; ?FLOC___ir_gesture_i2c_init?T1 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_i2c_init?T1 end address is: 0 (R0)
L_ir_gesture_i2c_init1:
; ?FLOC___ir_gesture_i2c_init?T1 start address is: 0 (R0)
; ?FLOC___ir_gesture_i2c_init?T1 end address is: 0 (R0)
;ir_gesture_hal.c,73 :: 		}
L_end_ir_gesture_i2c_init:
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_i2c_init
_ir_gesture_hal_delay:
;ir_gesture_hal.c,75 :: 		void ir_gesture_hal_delay( uint8_t ms )
; ms start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; ms end address is: 0 (R0)
; ms start address is: 0 (R0)
;ir_gesture_hal.c,80 :: 		while( ms-- )
L_ir_gesture_hal_delay2:
; ms start address is: 0 (R0)
UXTB	R2, R0
SUBS	R1, R0, #1
UXTB	R0, R1
; ms end address is: 0 (R0)
CMP	R2, #0
IT	EQ
BEQ	L_ir_gesture_hal_delay3
; ms end address is: 0 (R0)
;ir_gesture_hal.c,81 :: 		Delay_1ms();
; ms start address is: 0 (R0)
BL	_Delay_1ms+0
; ms end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_hal_delay2
L_ir_gesture_hal_delay3:
;ir_gesture_hal.c,84 :: 		}
L_end_ir_gesture_hal_delay:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_hal_delay
_ir_gesture_i2c_hal_write:
;ir_gesture_hal.c,86 :: 		void ir_gesture_i2c_hal_write( uint8_t address, uint8_t const *buff , uint16_t count )
; buff start address is: 4 (R1)
; address start address is: 0 (R0)
SUB	SP, SP, #16
STR	LR, [SP, #0]
STRH	R2, [SP, #12]
; buff end address is: 4 (R1)
; address end address is: 0 (R0)
; address start address is: 0 (R0)
; buff start address is: 4 (R1)
;ir_gesture_hal.c,89 :: 		uint8_t *temp_ptr = ( uint8_t *)buff;
MOV	R3, R1
; buff end address is: 4 (R1)
; temp_ptr start address is: 4 (R1)
MOV	R1, R3
;ir_gesture_hal.c,91 :: 		temp_buff[0] = address;
ADD	R3, SP, #4
STRB	R0, [R3, #0]
; address end address is: 0 (R0)
;ir_gesture_hal.c,92 :: 		memcpy( &temp_buff[1], temp_ptr, count );
ADDS	R3, R3, #1
LDRH	R2, [SP, #12]
; temp_ptr end address is: 4 (R1)
MOV	R0, R3
BL	_memcpy+0
;ir_gesture_hal.c,94 :: 		start_i2c_p();
MOVW	R4, #lo_addr(ir_gesture_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(ir_gesture_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;ir_gesture_hal.c,95 :: 		write_i2c_p( _i2c_hw_address, temp_buff, count + 1, _I2C_END_MODE_STOP );
LDRH	R3, [SP, #12]
ADDS	R5, R3, #1
UXTH	R5, R5
ADD	R4, SP, #4
MOVW	R3, #lo_addr(ir_gesture_hal__i2c_hw_address+0)
MOVT	R3, #hi_addr(ir_gesture_hal__i2c_hw_address+0)
LDRB	R3, [R3, #0]
UXTH	R2, R5
MOV	R1, R4
UXTB	R0, R3
MOVW	R3, #1
MOVW	R4, #lo_addr(ir_gesture_hal_write_i2c_p+0)
MOVT	R4, #hi_addr(ir_gesture_hal_write_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;ir_gesture_hal.c,96 :: 		}
L_end_ir_gesture_i2c_hal_write:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _ir_gesture_i2c_hal_write
_ir_gesture_i2c_hal_read:
;ir_gesture_hal.c,98 :: 		void ir_gesture_i2c_hal_read( uint8_t address, uint8_t const *buffer, uint16_t count )
; buffer start address is: 4 (R1)
SUB	SP, SP, #16
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
MOV	R5, R1
STRH	R2, [SP, #12]
; buffer end address is: 4 (R1)
; buffer start address is: 20 (R5)
;ir_gesture_hal.c,100 :: 		uint8_t *ptr = ( uint8_t *)buffer;
MOV	R4, R5
; buffer end address is: 20 (R5)
STR	R4, [SP, #4]
;ir_gesture_hal.c,102 :: 		start_i2c_p();
MOVW	R4, #lo_addr(ir_gesture_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(ir_gesture_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;ir_gesture_hal.c,103 :: 		write_i2c_p( _i2c_hw_address, &address, 1, _I2C_END_MODE_RESTART );
ADD	R4, SP, #8
MOVW	R3, #lo_addr(ir_gesture_hal__i2c_hw_address+0)
MOVT	R3, #hi_addr(ir_gesture_hal__i2c_hw_address+0)
LDRB	R3, [R3, #0]
MOVS	R2, #1
MOV	R1, R4
UXTB	R0, R3
MOVW	R3, #0
MOVW	R4, #lo_addr(ir_gesture_hal_write_i2c_p+0)
MOVT	R4, #hi_addr(ir_gesture_hal_write_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;ir_gesture_hal.c,104 :: 		read_i2c_p( _i2c_hw_address, ptr, count, _I2C_END_MODE_STOP );
MOVW	R3, #lo_addr(ir_gesture_hal__i2c_hw_address+0)
MOVT	R3, #hi_addr(ir_gesture_hal__i2c_hw_address+0)
LDRB	R3, [R3, #0]
LDRH	R2, [SP, #12]
LDR	R1, [SP, #4]
UXTB	R0, R3
MOVW	R3, #1
MOVW	R4, #lo_addr(ir_gesture_hal_read_i2c_p+0)
MOVT	R4, #hi_addr(ir_gesture_hal_read_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;ir_gesture_hal.c,105 :: 		}
L_end_ir_gesture_i2c_hal_read:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _ir_gesture_i2c_hal_read
