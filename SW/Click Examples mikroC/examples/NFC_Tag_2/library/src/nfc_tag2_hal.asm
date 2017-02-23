_hal_delay:
;nfc_tag2_hal.c,115 :: 		void hal_delay( uint16_t ms )
; ms start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; ms end address is: 0 (R0)
; ms start address is: 0 (R0)
;nfc_tag2_hal.c,124 :: 		while( ms-- )
L_hal_delay0:
; ms start address is: 0 (R0)
UXTH	R2, R0
SUBS	R1, R0, #1
UXTH	R0, R1
; ms end address is: 0 (R0)
CMP	R2, #0
IT	EQ
BEQ	L_hal_delay1
; ms end address is: 0 (R0)
;nfc_tag2_hal.c,125 :: 		Delay_1ms();
; ms start address is: 0 (R0)
BL	_Delay_1ms+0
; ms end address is: 0 (R0)
IT	AL
BAL	L_hal_delay0
L_hal_delay1:
;nfc_tag2_hal.c,127 :: 		}
L_end_hal_delay:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _hal_delay
_hal_nfctag2_init:
;nfc_tag2_hal.c,129 :: 		int hal_nfctag2_init( void )
;nfc_tag2_hal.c,133 :: 		start_i2c_p                 = I2C_Start_Ptr;
MOVW	R0, #lo_addr(_I2C_Start_Ptr+0)
MOVT	R0, #hi_addr(_I2C_Start_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(nfc_tag2_hal_start_i2c_p+0)
MOVT	R0, #hi_addr(nfc_tag2_hal_start_i2c_p+0)
STR	R1, [R0, #0]
;nfc_tag2_hal.c,134 :: 		write_i2c_p                 = I2C_Write_Ptr;
MOVW	R0, #lo_addr(_I2C_Write_Ptr+0)
MOVT	R0, #hi_addr(_I2C_Write_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(nfc_tag2_hal_write_i2c_p+0)
MOVT	R0, #hi_addr(nfc_tag2_hal_write_i2c_p+0)
STR	R1, [R0, #0]
;nfc_tag2_hal.c,135 :: 		read_i2c_p                  = I2C_Read_Ptr;
MOVW	R0, #lo_addr(_I2C_Read_Ptr+0)
MOVT	R0, #hi_addr(_I2C_Read_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(nfc_tag2_hal_read_i2c_p+0)
MOVT	R0, #hi_addr(nfc_tag2_hal_read_i2c_p+0)
STR	R1, [R0, #0]
;nfc_tag2_hal.c,203 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2_hal.c,204 :: 		}
L_end_hal_nfctag2_init:
BX	LR
; end of _hal_nfctag2_init
_hal_nfctag2_write:
;nfc_tag2_hal.c,211 :: 		)
; buffer start address is: 4 (R1)
SUB	SP, SP, #20
STR	LR, [SP, #0]
STRB	R0, [SP, #12]
MOV	R5, R1
STRH	R2, [SP, #16]
; buffer end address is: 4 (R1)
; buffer start address is: 20 (R5)
;nfc_tag2_hal.c,213 :: 		int res = 0;
MOVW	R4, #0
STRH	R4, [SP, #8]
;nfc_tag2_hal.c,214 :: 		uint8_t *ptr = buffer;
STR	R5, [SP, #4]
; buffer end address is: 20 (R5)
;nfc_tag2_hal.c,218 :: 		res |= start_i2c_p();
MOVW	R4, #lo_addr(nfc_tag2_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R3, [SP, #8]
ORRS	R3, R0
STRH	R3, [SP, #8]
;nfc_tag2_hal.c,219 :: 		res |= write_i2c_p( i2c_address, ptr, count, END_MODE_STOP );
MOVW	R3, #1
LDRH	R2, [SP, #16]
LDR	R1, [SP, #4]
LDRB	R0, [SP, #12]
MOVW	R4, #lo_addr(nfc_tag2_hal_write_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_write_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R3, [SP, #8]
ORRS	R3, R0
;nfc_tag2_hal.c,253 :: 		return res;
SXTH	R0, R3
;nfc_tag2_hal.c,254 :: 		}
L_end_hal_nfctag2_write:
LDR	LR, [SP, #0]
ADD	SP, SP, #20
BX	LR
; end of _hal_nfctag2_write
_hal_nfctag2_read:
;nfc_tag2_hal.c,261 :: 		)
; buffer start address is: 4 (R1)
SUB	SP, SP, #20
STR	LR, [SP, #0]
STRB	R0, [SP, #12]
MOV	R5, R1
STRH	R2, [SP, #16]
; buffer end address is: 4 (R1)
; buffer start address is: 20 (R5)
;nfc_tag2_hal.c,263 :: 		int res = 0;
MOVW	R4, #0
STRH	R4, [SP, #8]
;nfc_tag2_hal.c,264 :: 		uint8_t *ptr = buffer;
STR	R5, [SP, #4]
; buffer end address is: 20 (R5)
;nfc_tag2_hal.c,268 :: 		res |= start_i2c_p();
MOVW	R4, #lo_addr(nfc_tag2_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R3, [SP, #8]
ORRS	R3, R0
STRH	R3, [SP, #8]
;nfc_tag2_hal.c,269 :: 		res |= write_i2c_p( i2c_address, ptr, 1, END_MODE_STOP );
MOVW	R3, #1
MOVS	R2, #1
LDR	R1, [SP, #4]
LDRB	R0, [SP, #12]
MOVW	R4, #lo_addr(nfc_tag2_hal_write_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_write_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R4, [SP, #8]
ORRS	R4, R0
STRH	R4, [SP, #8]
;nfc_tag2_hal.c,270 :: 		res |= start_i2c_p();
MOVW	R4, #lo_addr(nfc_tag2_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R3, [SP, #8]
ORRS	R3, R0
STRH	R3, [SP, #8]
;nfc_tag2_hal.c,271 :: 		read_i2c_p( i2c_address, ptr, count, END_MODE_STOP );
MOVW	R3, #1
LDRH	R2, [SP, #16]
LDR	R1, [SP, #4]
LDRB	R0, [SP, #12]
MOVW	R4, #lo_addr(nfc_tag2_hal_read_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_read_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;nfc_tag2_hal.c,315 :: 		return res;
LDRSH	R0, [SP, #8]
;nfc_tag2_hal.c,316 :: 		}
L_end_hal_nfctag2_read:
LDR	LR, [SP, #0]
ADD	SP, SP, #20
BX	LR
; end of _hal_nfctag2_read
_hal_nfctag2_transfer:
;nfc_tag2_hal.c,325 :: 		)
; output start address is: 12 (R3)
; input start address is: 4 (R1)
SUB	SP, SP, #24
STR	LR, [SP, #0]
STRB	R0, [SP, #16]
MOV	R5, R1
STRH	R2, [SP, #20]
MOV	R6, R3
; output end address is: 12 (R3)
; input end address is: 4 (R1)
; input start address is: 20 (R5)
; output start address is: 24 (R6)
LDRH	R4, [SP, #24]
STRH	R4, [SP, #24]
;nfc_tag2_hal.c,327 :: 		int res = 0;
MOVW	R4, #0
STRH	R4, [SP, #12]
;nfc_tag2_hal.c,328 :: 		uint8_t *in = input;
STR	R5, [SP, #4]
; input end address is: 20 (R5)
;nfc_tag2_hal.c,329 :: 		uint8_t *out = output;
STR	R6, [SP, #8]
; output end address is: 24 (R6)
;nfc_tag2_hal.c,333 :: 		res |= start_i2c_p();
MOVW	R4, #lo_addr(nfc_tag2_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R4, [SP, #12]
ORRS	R4, R0
STRH	R4, [SP, #12]
;nfc_tag2_hal.c,334 :: 		res |= write_i2c_p( i2c_address, in, in_count, END_MODE_STOP );
MOVW	R3, #1
LDRH	R2, [SP, #20]
LDR	R1, [SP, #4]
LDRB	R0, [SP, #16]
MOVW	R4, #lo_addr(nfc_tag2_hal_write_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_write_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R4, [SP, #12]
ORRS	R4, R0
STRH	R4, [SP, #12]
;nfc_tag2_hal.c,335 :: 		res |= start_i2c_p();
MOVW	R4, #lo_addr(nfc_tag2_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDRSH	R4, [SP, #12]
ORRS	R4, R0
STRH	R4, [SP, #12]
;nfc_tag2_hal.c,336 :: 		read_i2c_p( i2c_address, out, out_count, END_MODE_STOP );
MOVW	R3, #1
LDRH	R2, [SP, #24]
LDR	R1, [SP, #8]
LDRB	R0, [SP, #16]
MOVW	R4, #lo_addr(nfc_tag2_hal_read_i2c_p+0)
MOVT	R4, #hi_addr(nfc_tag2_hal_read_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;nfc_tag2_hal.c,395 :: 		return res;
LDRSH	R0, [SP, #12]
;nfc_tag2_hal.c,396 :: 		}
L_end_hal_nfctag2_transfer:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of _hal_nfctag2_transfer
