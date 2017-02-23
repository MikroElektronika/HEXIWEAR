_MP3_SCI_Write:
;MP3_driver.c,45 :: 		void MP3_SCI_Write(char address, unsigned int data_in) {
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
STRH	R1, [SP, #8]
;MP3_driver.c,46 :: 		BSYNC = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(BSYNC+0)
MOVT	R2, #hi_addr(BSYNC+0)
STR	R3, [R2, #0]
;MP3_driver.c,47 :: 		SPI_Set_Active(SPI0_Read, SPI0_Write);
MOVW	R3, #lo_addr(_SPI0_Write+0)
MOVT	R3, #hi_addr(_SPI0_Write+0)
MOVW	R2, #lo_addr(_SPI0_Read+0)
MOVT	R2, #hi_addr(_SPI0_Read+0)
MOV	R1, R3
MOV	R0, R2
BL	_SPI_Set_Active+0
;MP3_driver.c,48 :: 		MP3_CS = 0;                    // select MP3 SCI
MOVS	R3, #0
SXTB	R3, R3
MOVW	R2, #lo_addr(MP3_CS+0)
MOVT	R2, #hi_addr(MP3_CS+0)
STR	R3, [R2, #0]
;MP3_driver.c,49 :: 		SPI_Wr_Ptr(WRITE_CODE);
MOVS	R0, #2
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,50 :: 		SPI_Wr_Ptr(address);
LDRB	R0, [SP, #4]
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,51 :: 		SPI_Wr_Ptr(Hi(data_in));       // high byte
ADD	R2, SP, #8
ADDS	R2, R2, #1
LDRB	R2, [R2, #0]
UXTB	R4, R2
UXTH	R0, R4
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,52 :: 		SPI_Wr_Ptr(Lo(data_in));       // low byte
ADD	R2, SP, #8
LDRB	R2, [R2, #0]
UXTB	R4, R2
UXTH	R0, R4
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,53 :: 		MP3_CS = 1;                    // deselect MP3 SCI
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(MP3_CS+0)
MOVT	R2, #hi_addr(MP3_CS+0)
STR	R3, [R2, #0]
;MP3_driver.c,54 :: 		while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
L_MP3_SCI_Write0:
MOVW	R3, #lo_addr(DREQ1+0)
MOVT	R3, #hi_addr(DREQ1+0)
LDR	R2, [R3, #0]
CMP	R2, #0
IT	NE
BNE	L_MP3_SCI_Write1
IT	AL
BAL	L_MP3_SCI_Write0
L_MP3_SCI_Write1:
;MP3_driver.c,55 :: 		}
L_end_MP3_SCI_Write:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _MP3_SCI_Write
_MP3_SCI_Read:
;MP3_driver.c,64 :: 		void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer) {
SUB	SP, SP, #20
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
STRB	R1, [SP, #12]
STR	R2, [SP, #16]
;MP3_driver.c,67 :: 		SPI_Set_Active(SPI0_Read, SPI0_Write);
MOVW	R4, #lo_addr(_SPI0_Write+0)
MOVT	R4, #hi_addr(_SPI0_Write+0)
MOVW	R3, #lo_addr(_SPI0_Read+0)
MOVT	R3, #hi_addr(_SPI0_Read+0)
MOV	R1, R4
MOV	R0, R3
BL	_SPI_Set_Active+0
;MP3_driver.c,68 :: 		MP3_CS = 0;                    // select MP3 SCI
MOVS	R4, #0
SXTB	R4, R4
MOVW	R3, #lo_addr(MP3_CS+0)
MOVT	R3, #hi_addr(MP3_CS+0)
STR	R4, [R3, #0]
;MP3_driver.c,69 :: 		SPI_Wr_Ptr(READ_CODE);
MOVS	R0, #3
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,70 :: 		SPI_Wr_Ptr(start_address);
LDRB	R0, [SP, #8]
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,72 :: 		while (words_count--) {        // read words_count words byte per byte
L_MP3_SCI_Read2:
LDRB	R4, [SP, #12]
LDRB	R3, [SP, #12]
SUBS	R3, R3, #1
STRB	R3, [SP, #12]
CMP	R4, #0
IT	EQ
BEQ	L_MP3_SCI_Read3
;MP3_driver.c,73 :: 		temp = SPI_Rd_Ptr(0);
MOVS	R0, #0
MOVW	R4, #lo_addr(_SPI_Rd_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Rd_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,74 :: 		temp <<= 8;
LSLS	R3, R0, #8
STRH	R3, [SP, #4]
;MP3_driver.c,75 :: 		temp += SPI_Rd_Ptr(0);
MOVS	R0, #0
MOVW	R4, #lo_addr(_SPI_Rd_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Rd_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
LDRH	R3, [SP, #4]
ADDS	R4, R3, R0
;MP3_driver.c,76 :: 		*(data_buffer++) = temp;
LDR	R3, [SP, #16]
STRH	R4, [R3, #0]
LDR	R3, [SP, #16]
ADDS	R3, R3, #2
STR	R3, [SP, #16]
;MP3_driver.c,77 :: 		}
IT	AL
BAL	L_MP3_SCI_Read2
L_MP3_SCI_Read3:
;MP3_driver.c,78 :: 		MP3_CS = 1;                    // deselect MP3 SCI
MOVS	R4, #1
SXTB	R4, R4
MOVW	R3, #lo_addr(MP3_CS+0)
MOVT	R3, #hi_addr(MP3_CS+0)
STR	R4, [R3, #0]
;MP3_driver.c,79 :: 		while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
L_MP3_SCI_Read4:
MOVW	R4, #lo_addr(DREQ1+0)
MOVT	R4, #hi_addr(DREQ1+0)
LDR	R3, [R4, #0]
CMP	R3, #0
IT	NE
BNE	L_MP3_SCI_Read5
IT	AL
BAL	L_MP3_SCI_Read4
L_MP3_SCI_Read5:
;MP3_driver.c,80 :: 		}
L_end_MP3_SCI_Read:
LDR	LR, [SP, #0]
ADD	SP, SP, #20
BX	LR
; end of _MP3_SCI_Read
_MP3_SDI_Write:
;MP3_driver.c,89 :: 		void MP3_SDI_Write(char data_) {
; data_ start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
UXTB	R3, R0
; data_ end address is: 0 (R0)
; data_ start address is: 12 (R3)
;MP3_driver.c,90 :: 		SPI_Set_Active(SPI0_Read, SPI0_Write);
MOVW	R2, #lo_addr(_SPI0_Write+0)
MOVT	R2, #hi_addr(_SPI0_Write+0)
MOVW	R1, #lo_addr(_SPI0_Read+0)
MOVT	R1, #hi_addr(_SPI0_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;MP3_driver.c,91 :: 		MP3_CS = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R1, #lo_addr(MP3_CS+0)
MOVT	R1, #hi_addr(MP3_CS+0)
STR	R2, [R1, #0]
;MP3_driver.c,92 :: 		BSYNC = 0;
MOVS	R2, #0
SXTB	R2, R2
MOVW	R1, #lo_addr(BSYNC+0)
MOVT	R1, #hi_addr(BSYNC+0)
STR	R2, [R1, #0]
; data_ end address is: 12 (R3)
UXTB	R0, R3
;MP3_driver.c,94 :: 		while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
L_MP3_SDI_Write6:
; data_ start address is: 0 (R0)
MOVW	R2, #lo_addr(DREQ1+0)
MOVT	R2, #hi_addr(DREQ1+0)
LDR	R1, [R2, #0]
CMP	R1, #0
IT	NE
BNE	L_MP3_SDI_Write7
IT	AL
BAL	L_MP3_SDI_Write6
L_MP3_SDI_Write7:
;MP3_driver.c,96 :: 		SPI_Wr_Ptr(data_);
; data_ end address is: 0 (R0)
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;MP3_driver.c,97 :: 		BSYNC = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R1, #lo_addr(BSYNC+0)
MOVT	R1, #hi_addr(BSYNC+0)
STR	R2, [R1, #0]
;MP3_driver.c,98 :: 		}
L_end_MP3_SDI_Write:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MP3_SDI_Write
_MP3_SDI_Write_32:
;MP3_driver.c,107 :: 		void MP3_SDI_Write_32(char *data_) {
SUB	SP, SP, #12
STR	LR, [SP, #0]
STR	R0, [SP, #8]
;MP3_driver.c,109 :: 		SPI_Set_Active(SPI0_Read, SPI0_Write);
MOVW	R2, #lo_addr(_SPI0_Write+0)
MOVT	R2, #hi_addr(_SPI0_Write+0)
MOVW	R1, #lo_addr(_SPI0_Read+0)
MOVT	R1, #hi_addr(_SPI0_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;MP3_driver.c,110 :: 		MP3_CS = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R1, #lo_addr(MP3_CS+0)
MOVT	R1, #hi_addr(MP3_CS+0)
STR	R2, [R1, #0]
;MP3_driver.c,111 :: 		BSYNC = 0;
MOVS	R2, #0
SXTB	R2, R2
MOVW	R1, #lo_addr(BSYNC+0)
MOVT	R1, #hi_addr(BSYNC+0)
STR	R2, [R1, #0]
;MP3_driver.c,113 :: 		while (DREQ1 == 0);             // wait until DREQ1 becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
L_MP3_SDI_Write_328:
MOVW	R2, #lo_addr(DREQ1+0)
MOVT	R2, #hi_addr(DREQ1+0)
LDR	R1, [R2, #0]
CMP	R1, #0
IT	NE
BNE	L_MP3_SDI_Write_329
IT	AL
BAL	L_MP3_SDI_Write_328
L_MP3_SDI_Write_329:
;MP3_driver.c,115 :: 		for (i=0; i<32; i++)
; i start address is: 8 (R2)
MOVS	R2, #0
; i end address is: 8 (R2)
UXTB	R0, R2
L_MP3_SDI_Write_3210:
; i start address is: 0 (R0)
CMP	R0, #32
IT	CS
BCS	L_MP3_SDI_Write_3211
;MP3_driver.c,116 :: 		SPI_Wr_Ptr(data_[i]);
LDR	R1, [SP, #8]
ADDS	R1, R1, R0
LDRB	R1, [R1, #0]
UXTB	R4, R1
STRB	R0, [SP, #4]
UXTH	R0, R4
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
LDRB	R0, [SP, #4]
;MP3_driver.c,115 :: 		for (i=0; i<32; i++)
ADDS	R1, R0, #1
; i end address is: 0 (R0)
; i start address is: 8 (R2)
UXTB	R2, R1
;MP3_driver.c,116 :: 		SPI_Wr_Ptr(data_[i]);
UXTB	R0, R2
; i end address is: 8 (R2)
IT	AL
BAL	L_MP3_SDI_Write_3210
L_MP3_SDI_Write_3211:
;MP3_driver.c,117 :: 		BSYNC = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R1, #lo_addr(BSYNC+0)
MOVT	R1, #hi_addr(BSYNC+0)
STR	R2, [R1, #0]
;MP3_driver.c,118 :: 		}
L_end_MP3_SDI_Write_32:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _MP3_SDI_Write_32
_MP3_Set_Volume:
;MP3_driver.c,127 :: 		void MP3_Set_Volume(char left, char right) {
; right start address is: 4 (R1)
; left start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; right end address is: 4 (R1)
; left end address is: 0 (R0)
; left start address is: 0 (R0)
; right start address is: 4 (R1)
;MP3_driver.c,130 :: 		volume = (left<<8) + right;             // calculate value
LSLS	R2, R0, #8
UXTH	R2, R2
; left end address is: 0 (R0)
ADDS	R2, R2, R1
; right end address is: 4 (R1)
;MP3_driver.c,131 :: 		MP3_SCI_Write(SCI_VOL_ADDR, volume);    // Write value to VOL register
UXTH	R1, R2
MOVS	R0, #11
BL	_MP3_SCI_Write+0
;MP3_driver.c,132 :: 		}
L_end_MP3_Set_Volume:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MP3_Set_Volume
