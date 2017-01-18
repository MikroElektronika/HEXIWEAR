_MAX44000_WriteRegister:
;MAX44000_Driver.c,5 :: 		void MAX44000_WriteRegister(char wrAddr, char wrData) {
; wrData start address is: 4 (R1)
; wrAddr start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; wrData end address is: 4 (R1)
; wrAddr end address is: 0 (R0)
; wrAddr start address is: 0 (R0)
; wrData start address is: 4 (R1)
;MAX44000_Driver.c,6 :: 		tmp_data[0] = wrAddr;
MOVW	R2, #lo_addr(_tmp_data+0)
MOVT	R2, #hi_addr(_tmp_data+0)
STRB	R0, [R2, #0]
; wrAddr end address is: 0 (R0)
;MAX44000_Driver.c,7 :: 		tmp_data[1] = wrData;
MOVW	R2, #lo_addr(_tmp_data+1)
MOVT	R2, #hi_addr(_tmp_data+1)
STRB	R1, [R2, #0]
; wrData end address is: 4 (R1)
;MAX44000_Driver.c,8 :: 		I2C_Start();
BL	_I2C_Start+0
;MAX44000_Driver.c,9 :: 		I2C_Write(MAX44000_I2C_Adr,tmp_data,2,_I2C_END_MODE_STOP);
MOVW	R3, #1
MOVS	R2, #2
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #74
BL	_I2C_Write+0
;MAX44000_Driver.c,10 :: 		}
L_end_MAX44000_WriteRegister:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MAX44000_WriteRegister
_MAX44000_ReadRegister:
;MAX44000_Driver.c,13 :: 		char MAX44000_ReadRegister(char rAddr) {
; rAddr start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; rAddr end address is: 0 (R0)
; rAddr start address is: 0 (R0)
;MAX44000_Driver.c,14 :: 		tmp_data[0] = rAddr;
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
STRB	R0, [R1, #0]
; rAddr end address is: 0 (R0)
;MAX44000_Driver.c,15 :: 		I2C_Start();              // issue I2C start signal
BL	_I2C_Start+0
;MAX44000_Driver.c,16 :: 		I2C_Write(MAX44000_I2C_Adr,tmp_data,1,_I2C_END_MODE_RESTART);
MOVW	R3, #0
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #74
BL	_I2C_Write+0
;MAX44000_Driver.c,17 :: 		I2C_Read (MAX44000_I2C_Adr,tmp_data,1,_I2C_END_MODE_STOP);
MOVW	R3, #1
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #74
BL	_I2C_Read+0
;MAX44000_Driver.c,18 :: 		return tmp_data[0];
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
LDRB	R0, [R1, #0]
;MAX44000_Driver.c,19 :: 		}
L_end_MAX44000_ReadRegister:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MAX44000_ReadRegister
_MAX44000_Init:
;MAX44000_Driver.c,22 :: 		char MAX44000_Init() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;MAX44000_Driver.c,23 :: 		MAX44000_WriteRegister(RECEIVE_CFG, 0xF1); //Receive Register 1.5625ms
MOVS	R1, #241
MOVS	R0, #2
BL	_MAX44000_WriteRegister+0
;MAX44000_Driver.c,24 :: 		MAX44000_WriteRegister(TRANSMIT_CFG,0x0F); //Transmit Register 110mA
MOVS	R1, #15
MOVS	R0, #3
BL	_MAX44000_WriteRegister+0
;MAX44000_Driver.c,25 :: 		MAX44000_WriteRegister(MAIN_CFG,0x13);     //Main Config ALS/Prox Mode
MOVS	R1, #19
MOVS	R0, #1
BL	_MAX44000_WriteRegister+0
;MAX44000_Driver.c,27 :: 		}
L_end_MAX44000_Init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MAX44000_Init
