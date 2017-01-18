_Init_MCU:
;HEXIWEAR_Camera_Click.c,108 :: 		void Init_MCU()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_Camera_Click.c,110 :: 		Delay_ms(200);
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_Init_MCU0:
SUBS	R7, R7, #1
BNE	L_Init_MCU0
NOP
NOP
NOP
;HEXIWEAR_Camera_Click.c,111 :: 		GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);  // Set Ready pin as input
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_Camera_Click.c,113 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4); // Set Chip Select pin as output
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_Camera_Click.c,114 :: 		Cam_Chip_Select = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_Camera_Click.c,115 :: 		Delay_ms(200);
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_Init_MCU2:
SUBS	R7, R7, #1
BNE	L_Init_MCU2
NOP
NOP
NOP
;HEXIWEAR_Camera_Click.c,118 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
MOVW	R2, #lo_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVW	R1, #7
MOVT	R1, #33280
;HEXIWEAR_Camera_Click.c,117 :: 		SPI0_Init_Advanced(20000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
MOVW	R0, #11520
MOVT	R0, #305
;HEXIWEAR_Camera_Click.c,118 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
BL	_SPI0_Init_Advanced+0
;HEXIWEAR_Camera_Click.c,120 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_Camera_Click.c,121 :: 		}
L_end_Init_MCU:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Init_MCU
_SendCommand:
;HEXIWEAR_Camera_Click.c,127 :: 		void SendCommand(uint8_t cmd)
; cmd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; cmd end address is: 0 (R0)
;HEXIWEAR_Camera_Click.c,129 :: 		while(Ready_Pin == 0);
L_SendCommand4:
; cmd start address is: 0 (R0)
MOVW	R2, #lo_addr(PTB_PDIR+0)
MOVT	R2, #hi_addr(PTB_PDIR+0)
LDR	R1, [R2, #0]
CMP	R1, #0
IT	NE
BNE	L_SendCommand5
IT	AL
BAL	L_SendCommand4
L_SendCommand5:
;HEXIWEAR_Camera_Click.c,131 :: 		SPI0_Read(cmd);
; cmd end address is: 0 (R0)
BL	_SPI0_Read+0
;HEXIWEAR_Camera_Click.c,132 :: 		}
L_end_SendCommand:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _SendCommand
_ReadBytes:
;HEXIWEAR_Camera_Click.c,139 :: 		void ReadBytes(uint8_t *ptr, unsigned long num)
; num start address is: 4 (R1)
; ptr start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; num end address is: 4 (R1)
; ptr end address is: 0 (R0)
; ptr start address is: 0 (R0)
; num start address is: 4 (R1)
MOV	R8, R0
; ptr end address is: 0 (R0)
; num end address is: 4 (R1)
MOV	R0, R1
;HEXIWEAR_Camera_Click.c,141 :: 		while(num)
L_ReadBytes6:
; num start address is: 0 (R0)
; ptr start address is: 32 (R8)
CMP	R0, #0
IT	EQ
BEQ	L_ReadBytes7
;HEXIWEAR_Camera_Click.c,143 :: 		num--;
SUBS	R7, R0, #1
; num end address is: 0 (R0)
; num start address is: 28 (R7)
; num end address is: 28 (R7)
; ptr end address is: 32 (R8)
;HEXIWEAR_Camera_Click.c,144 :: 		while(Ready_Pin == 0);
L_ReadBytes8:
; num start address is: 28 (R7)
; ptr start address is: 32 (R8)
MOVW	R3, #lo_addr(PTB_PDIR+0)
MOVT	R3, #hi_addr(PTB_PDIR+0)
LDR	R2, [R3, #0]
CMP	R2, #0
IT	NE
BNE	L_ReadBytes9
IT	AL
BAL	L_ReadBytes8
L_ReadBytes9:
;HEXIWEAR_Camera_Click.c,145 :: 		*ptr = SPI0_Read(0);
MOVS	R0, #0
BL	_SPI0_Read+0
STRB	R0, [R8, #0]
;HEXIWEAR_Camera_Click.c,146 :: 		*ptr++;
ADD	R8, R8, #1
;HEXIWEAR_Camera_Click.c,147 :: 		}
; num end address is: 28 (R7)
; ptr end address is: 32 (R8)
MOV	R0, R7
IT	AL
BAL	L_ReadBytes6
L_ReadBytes7:
;HEXIWEAR_Camera_Click.c,148 :: 		}
L_end_ReadBytes:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ReadBytes
_GetCamBuff:
;HEXIWEAR_Camera_Click.c,154 :: 		void GetCamBuff(uint8_t* buff)
; buff start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R7, R0
; buff end address is: 0 (R0)
; buff start address is: 28 (R7)
;HEXIWEAR_Camera_Click.c,156 :: 		Cam_Chip_Select = 0;
MOVS	R2, #0
SXTB	R2, R2
MOVW	R1, #lo_addr(PTC_PDOR+0)
MOVT	R1, #hi_addr(PTC_PDOR+0)
STR	R2, [R1, #0]
;HEXIWEAR_Camera_Click.c,157 :: 		SendCommand(__CMD_GET_FRAME_BUFFERED);
MOVS	R0, #5
BL	_SendCommand+0
;HEXIWEAR_Camera_Click.c,158 :: 		ReadBytes(buff, FRAME_SIZE);
MOVW	R1, #50688
MOV	R0, R7
; buff end address is: 28 (R7)
BL	_ReadBytes+0
;HEXIWEAR_Camera_Click.c,159 :: 		Cam_Chip_Select = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R1, #lo_addr(PTC_PDOR+0)
MOVT	R1, #hi_addr(PTC_PDOR+0)
STR	R2, [R1, #0]
;HEXIWEAR_Camera_Click.c,160 :: 		}
L_end_GetCamBuff:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _GetCamBuff
_main:
;HEXIWEAR_Camera_Click.c,166 :: 		void main()
;HEXIWEAR_Camera_Click.c,168 :: 		Init_MCU();
BL	_Init_MCU+0
;HEXIWEAR_Camera_Click.c,169 :: 		OLED_DrawImage( camera_bmp, 0, 0);
MOVW	R0, #lo_addr(_camera_bmp+0)
MOVT	R0, #hi_addr(_camera_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_Camera_Click.c,170 :: 		Delay_ms(2000);
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main10:
SUBS	R7, R7, #1
BNE	L_main10
NOP
NOP
NOP
;HEXIWEAR_Camera_Click.c,172 :: 		while (1)
L_main12:
;HEXIWEAR_Camera_Click.c,175 :: 		GetCamBuff(&qcifImg);
MOVW	R0, #lo_addr(_qcifImg+0)
MOVT	R0, #hi_addr(_qcifImg+0)
BL	_GetCamBuff+0
;HEXIWEAR_Camera_Click.c,177 :: 		scaledImgPtr = scaledImg_bmp + 6;
MOVW	R1, #lo_addr(_scaledImg_bmp+6)
MOVT	R1, #hi_addr(_scaledImg_bmp+6)
MOVW	R0, #lo_addr(_scaledImgPtr+0)
MOVT	R0, #hi_addr(_scaledImgPtr+0)
STR	R1, [R0, #0]
;HEXIWEAR_Camera_Click.c,179 :: 		for(rowCnt = 0 + 48; rowCnt < 96 + 48; rowCnt++)
MOVS	R1, #48
MOVW	R0, #lo_addr(_rowCnt+0)
MOVT	R0, #hi_addr(_rowCnt+0)
STRH	R1, [R0, #0]
L_main14:
MOVW	R0, #lo_addr(_rowCnt+0)
MOVT	R0, #hi_addr(_rowCnt+0)
LDRH	R0, [R0, #0]
CMP	R0, #144
IT	CS
BCS	L_main15
;HEXIWEAR_Camera_Click.c,181 :: 		rowPtr = qcifImg + (176 * 2 * rowCnt);
MOVW	R0, #lo_addr(_rowCnt+0)
MOVT	R0, #hi_addr(_rowCnt+0)
LDRH	R1, [R0, #0]
MOVW	R0, #352
MULS	R1, R0, R1
UXTH	R1, R1
MOVW	R0, #lo_addr(_qcifImg+0)
MOVT	R0, #hi_addr(_qcifImg+0)
ADDS	R1, R0, R1
MOVW	R0, #lo_addr(_rowPtr+0)
MOVT	R0, #hi_addr(_rowPtr+0)
STR	R1, [R0, #0]
;HEXIWEAR_Camera_Click.c,182 :: 		for(columnCnt = 0 + 60; columnCnt < 96 + 60; columnCnt++)
MOVS	R1, #60
MOVW	R0, #lo_addr(_columnCnt+0)
MOVT	R0, #hi_addr(_columnCnt+0)
STRH	R1, [R0, #0]
L_main17:
MOVW	R0, #lo_addr(_columnCnt+0)
MOVT	R0, #hi_addr(_columnCnt+0)
LDRH	R0, [R0, #0]
CMP	R0, #156
IT	CS
BCS	L_main18
;HEXIWEAR_Camera_Click.c,184 :: 		*(scaledImgPtr++) = (rowPtr[2*columnCnt]);
MOVW	R5, #lo_addr(_columnCnt+0)
MOVT	R5, #hi_addr(_columnCnt+0)
LDRH	R0, [R5, #0]
LSLS	R1, R0, #1
UXTH	R1, R1
MOVW	R4, #lo_addr(_rowPtr+0)
MOVT	R4, #hi_addr(_rowPtr+0)
LDR	R0, [R4, #0]
ADDS	R0, R0, R1
LDRB	R1, [R0, #0]
MOVW	R3, #lo_addr(_scaledImgPtr+0)
MOVT	R3, #hi_addr(_scaledImgPtr+0)
LDR	R0, [R3, #0]
STRB	R1, [R0, #0]
MOV	R0, R3
LDR	R0, [R0, #0]
ADDS	R2, R0, #1
STR	R2, [R3, #0]
;HEXIWEAR_Camera_Click.c,185 :: 		*(scaledImgPtr++) = (rowPtr[2*columnCnt + 1]);
MOV	R0, R5
LDRH	R0, [R0, #0]
LSLS	R0, R0, #1
UXTH	R0, R0
ADDS	R1, R0, #1
UXTH	R1, R1
MOV	R0, R4
LDR	R0, [R0, #0]
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
STRB	R0, [R2, #0]
MOV	R0, R3
LDR	R0, [R0, #0]
ADDS	R0, R0, #1
STR	R0, [R3, #0]
;HEXIWEAR_Camera_Click.c,182 :: 		for(columnCnt = 0 + 60; columnCnt < 96 + 60; columnCnt++)
MOV	R0, R5
LDRH	R0, [R0, #0]
ADDS	R0, R0, #1
STRH	R0, [R5, #0]
;HEXIWEAR_Camera_Click.c,186 :: 		}
IT	AL
BAL	L_main17
L_main18:
;HEXIWEAR_Camera_Click.c,179 :: 		for(rowCnt = 0 + 48; rowCnt < 96 + 48; rowCnt++)
MOVW	R1, #lo_addr(_rowCnt+0)
MOVT	R1, #hi_addr(_rowCnt+0)
LDRH	R0, [R1, #0]
ADDS	R0, R0, #1
STRH	R0, [R1, #0]
;HEXIWEAR_Camera_Click.c,187 :: 		}
IT	AL
BAL	L_main14
L_main15:
;HEXIWEAR_Camera_Click.c,188 :: 		OLED_DrawImage(scaledImg_bmp, 0, 0);
MOVS	R2, #0
MOVS	R1, #0
MOVW	R0, #lo_addr(_scaledImg_bmp+0)
MOVT	R0, #hi_addr(_scaledImg_bmp+0)
BL	_OLED_DrawImage+0
;HEXIWEAR_Camera_Click.c,189 :: 		}
IT	AL
BAL	L_main12
;HEXIWEAR_Camera_Click.c,190 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
