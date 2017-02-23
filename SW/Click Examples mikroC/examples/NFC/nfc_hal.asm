_nfc_hal_init:
;nfc_hal.c,156 :: 		void nfc_hal_init( uint8_t address_id )
; address_id start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; address_id end address is: 0 (R0)
; address_id start address is: 0 (R0)
;nfc_hal.c,171 :: 		start_i2c_p = I2C_Start_Ptr;
MOVW	R1, #lo_addr(_I2C_Start_Ptr+0)
MOVT	R1, #hi_addr(_I2C_Start_Ptr+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(nfc_hal_start_i2c_p+0)
MOVT	R1, #hi_addr(nfc_hal_start_i2c_p+0)
STR	R2, [R1, #0]
;nfc_hal.c,172 :: 		write_i2c_p = I2C_Write_Ptr;
MOVW	R1, #lo_addr(_I2C_Write_Ptr+0)
MOVT	R1, #hi_addr(_I2C_Write_Ptr+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(nfc_hal_write_i2c_p+0)
MOVT	R1, #hi_addr(nfc_hal_write_i2c_p+0)
STR	R2, [R1, #0]
;nfc_hal.c,173 :: 		read_i2c_p  = I2C_Read_Ptr;
MOVW	R1, #lo_addr(_I2C_Read_Ptr+0)
MOVT	R1, #hi_addr(_I2C_Read_Ptr+0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(nfc_hal_read_i2c_p+0)
MOVT	R1, #hi_addr(nfc_hal_read_i2c_p+0)
STR	R2, [R1, #0]
;nfc_hal.c,240 :: 		_i2c_hw_address = address_id;
MOVW	R1, #lo_addr(nfc_hal__i2c_hw_address+0)
MOVT	R1, #hi_addr(nfc_hal__i2c_hw_address+0)
STRB	R0, [R1, #0]
; address_id end address is: 0 (R0)
;nfc_hal.c,244 :: 		nfc_hal_reset();
BL	_nfc_hal_reset+0
;nfc_hal.c,245 :: 		}
L_end_nfc_hal_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _nfc_hal_init
_nfc_hal_reset:
;nfc_hal.c,248 :: 		void nfc_hal_reset()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;nfc_hal.c,257 :: 		NFC_RST_PIN = HIGH;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(NFC_RST_PIN+0)
MOVT	R0, #hi_addr(NFC_RST_PIN+0)
STR	R1, [R0, #0]
;nfc_hal.c,258 :: 		Delay_10ms();
BL	_Delay_10ms+0
;nfc_hal.c,259 :: 		NFC_RST_PIN = LOW;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(NFC_RST_PIN+0)
MOVT	R0, #hi_addr(NFC_RST_PIN+0)
STR	R1, [R0, #0]
;nfc_hal.c,260 :: 		Delay_10ms();
BL	_Delay_10ms+0
;nfc_hal.c,261 :: 		NFC_RST_PIN = HIGH;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(NFC_RST_PIN+0)
MOVT	R0, #hi_addr(NFC_RST_PIN+0)
STR	R1, [R0, #0]
;nfc_hal.c,262 :: 		Delay_10ms();
BL	_Delay_10ms+0
;nfc_hal.c,265 :: 		}
L_end_nfc_hal_reset:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _nfc_hal_reset
_nfc_hal_delay:
;nfc_hal.c,268 :: 		void nfc_hal_delay( uint16_t ms )
; ms start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; ms end address is: 0 (R0)
; ms start address is: 0 (R0)
;nfc_hal.c,277 :: 		while( ms--)
L_nfc_hal_delay0:
; ms start address is: 0 (R0)
UXTH	R2, R0
SUBS	R1, R0, #1
UXTH	R0, R1
; ms end address is: 0 (R0)
CMP	R2, #0
IT	EQ
BEQ	L_nfc_hal_delay1
; ms end address is: 0 (R0)
;nfc_hal.c,278 :: 		Delay_1ms();
; ms start address is: 0 (R0)
BL	_Delay_1ms+0
; ms end address is: 0 (R0)
IT	AL
BAL	L_nfc_hal_delay0
L_nfc_hal_delay1:
;nfc_hal.c,283 :: 		}
L_end_nfc_hal_delay:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _nfc_hal_delay
_nfc_hal_write:
;nfc_hal.c,285 :: 		int nfc_hal_write( uint8_t *data_out, uint16_t count )
; count start address is: 4 (R1)
; data_out start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
MOV	R5, R0
UXTH	R0, R1
; count end address is: 4 (R1)
; data_out end address is: 0 (R0)
; data_out start address is: 20 (R5)
; count start address is: 0 (R0)
;nfc_hal.c,287 :: 		if( data_out == NULL )
CMP	R5, #0
IT	NE
BNE	L_nfc_hal_write2
; data_out end address is: 20 (R5)
; count end address is: 0 (R0)
;nfc_hal.c,288 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_hal_write
L_nfc_hal_write2:
;nfc_hal.c,317 :: 		start_i2c_p();
; count start address is: 0 (R0)
; data_out start address is: 20 (R5)
MOVW	R4, #lo_addr(nfc_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
STRH	R0, [SP, #4]
STR	R5, [SP, #8]
BLX	R4
LDR	R5, [SP, #8]
LDRH	R0, [SP, #4]
;nfc_hal.c,318 :: 		return( write_i2c_p( _i2c_hw_address, data_out, count, END_MODE_STOP ) ) ? -1 : 0;
MOVW	R2, #lo_addr(nfc_hal__i2c_hw_address+0)
MOVT	R2, #hi_addr(nfc_hal__i2c_hw_address+0)
LDRB	R2, [R2, #0]
STRB	R2, [SP, #4]
MOVW	R3, #1
MOV	R1, R5
; count end address is: 0 (R0)
UXTH	R2, R0
; data_out end address is: 20 (R5)
LDRB	R0, [SP, #4]
MOVW	R4, #lo_addr(nfc_hal_write_i2c_p+0)
MOVT	R4, #hi_addr(nfc_hal_write_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_hal_write3
; ?FLOC___nfc_hal_write?T5 start address is: 0 (R0)
MOVS	R0, #-1
SXTB	R0, R0
; ?FLOC___nfc_hal_write?T5 end address is: 0 (R0)
IT	AL
BAL	L_nfc_hal_write4
L_nfc_hal_write3:
; ?FLOC___nfc_hal_write?T5 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___nfc_hal_write?T5 end address is: 0 (R0)
L_nfc_hal_write4:
; ?FLOC___nfc_hal_write?T5 start address is: 0 (R0)
; ?FLOC___nfc_hal_write?T5 end address is: 0 (R0)
;nfc_hal.c,346 :: 		}
L_end_nfc_hal_write:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _nfc_hal_write
_nfc_hal_read:
;nfc_hal.c,354 :: 		uint16_t count )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STR	R0, [SP, #4]
STR	R1, [SP, #8]
;nfc_hal.c,394 :: 		start_i2c_p();
MOVW	R4, #lo_addr(nfc_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;nfc_hal.c,395 :: 		read_i2c_p( _i2c_hw_address, data_in, 3, END_MODE_STOP );
MOVW	R3, #lo_addr(nfc_hal__i2c_hw_address+0)
MOVT	R3, #hi_addr(nfc_hal__i2c_hw_address+0)
LDRB	R3, [R3, #0]
MOVS	R2, #3
LDR	R1, [SP, #4]
UXTB	R0, R3
MOVW	R3, #1
MOVW	R4, #lo_addr(nfc_hal_read_i2c_p+0)
MOVT	R4, #hi_addr(nfc_hal_read_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;nfc_hal.c,397 :: 		if( data_in[2] != 0 )
LDR	R4, [SP, #4]
ADDS	R4, R4, #2
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	EQ
BEQ	L_nfc_hal_read5
;nfc_hal.c,399 :: 		start_i2c_p();
MOVW	R4, #lo_addr(nfc_hal_start_i2c_p+0)
MOVT	R4, #hi_addr(nfc_hal_start_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;nfc_hal.c,400 :: 		read_i2c_p( _i2c_hw_address, &data_in[3], data_in[2], END_MODE_STOP );
LDR	R3, [SP, #4]
ADDS	R3, R3, #2
LDRB	R3, [R3, #0]
UXTB	R5, R3
LDR	R3, [SP, #4]
ADDS	R4, R3, #3
MOVW	R3, #lo_addr(nfc_hal__i2c_hw_address+0)
MOVT	R3, #hi_addr(nfc_hal__i2c_hw_address+0)
LDRB	R3, [R3, #0]
MOV	R2, R5
MOV	R1, R4
UXTB	R0, R3
MOVW	R3, #1
MOVW	R4, #lo_addr(nfc_hal_read_i2c_p+0)
MOVT	R4, #hi_addr(nfc_hal_read_i2c_p+0)
LDR	R4, [R4, #0]
BLX	R4
;nfc_hal.c,401 :: 		*nbytes_read = data_in[2] + 3;
LDR	R3, [SP, #4]
ADDS	R3, R3, #2
LDRB	R3, [R3, #0]
ADDS	R4, R3, #3
LDR	R3, [SP, #8]
STRH	R4, [R3, #0]
;nfc_hal.c,403 :: 		} else {
IT	AL
BAL	L_nfc_hal_read6
L_nfc_hal_read5:
;nfc_hal.c,404 :: 		*nbytes_read = 3;
MOVS	R4, #3
LDR	R3, [SP, #8]
STRH	R4, [R3, #0]
;nfc_hal.c,405 :: 		}
L_nfc_hal_read6:
;nfc_hal.c,460 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;nfc_hal.c,461 :: 		}
L_end_nfc_hal_read:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _nfc_hal_read
