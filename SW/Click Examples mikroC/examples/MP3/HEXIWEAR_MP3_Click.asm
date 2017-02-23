_InitMCU:
;HEXIWEAR_MP3_Click.c,102 :: 		void InitMCU(){
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_MP3_Click.c,104 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_MP3_Click.c,105 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
MOV	R1, #2048
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_MP3_Click.c,106 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_13);
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_MP3_Click.c,107 :: 		GPIO_Digital_Input( &PTB_PDOR, _GPIO_PINMASK_2);
MOV	R1, #4
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_MP3_Click.c,109 :: 		}
L_end_InitMCU:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _InitMCU
_MP3_Init:
;HEXIWEAR_MP3_Click.c,120 :: 		void MP3_Init(void)
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_MP3_Click.c,122 :: 		BSYNC = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,123 :: 		MP3_CS = 1;
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,126 :: 		MP3_RST = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,127 :: 		Delay_ms(10);
MOVW	R7, #6782
MOVT	R7, #6
NOP
NOP
L_MP3_Init0:
SUBS	R7, R7, #1
BNE	L_MP3_Init0
NOP
NOP
NOP
;HEXIWEAR_MP3_Click.c,128 :: 		MP3_RST = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,130 :: 		while (DREQ1 == 0);
L_MP3_Init2:
MOVW	R1, #lo_addr(PTB_PDIR+0)
MOVT	R1, #hi_addr(PTB_PDIR+0)
LDR	R0, [R1, #0]
CMP	R0, #0
IT	NE
BNE	L_MP3_Init3
IT	AL
BAL	L_MP3_Init2
L_MP3_Init3:
;HEXIWEAR_MP3_Click.c,132 :: 		MP3_SCI_Write(SCI_MODE_ADDR, 0x0800);
MOVW	R1, #2048
MOVS	R0, _SCI_MODE_ADDR
BL	_MP3_SCI_Write+0
;HEXIWEAR_MP3_Click.c,133 :: 		MP3_SCI_Write(SCI_BASS_ADDR, 0x7A00);
MOVW	R1, #31232
MOVS	R0, _SCI_BASS_ADDR
BL	_MP3_SCI_Write+0
;HEXIWEAR_MP3_Click.c,134 :: 		MP3_SCI_Write(SCI_CLOCKF_ADDR, 0x2000);   // default 12 288 000 Hz
MOVW	R1, #8192
MOVS	R0, _SCI_CLOCKF_ADDR
BL	_MP3_SCI_Write+0
;HEXIWEAR_MP3_Click.c,137 :: 		volume_left  = 0x0D; //0x3F;
MOVS	R1, #13
MOVW	R0, #lo_addr(_volume_left+0)
MOVT	R0, #hi_addr(_volume_left+0)
STRB	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,138 :: 		volume_right = 0x0D; //0x3F;
MOVS	R1, #13
MOVW	R0, #lo_addr(_volume_right+0)
MOVT	R0, #hi_addr(_volume_right+0)
STRB	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,139 :: 		MP3_Set_Volume(volume_left, volume_right);
MOVS	R1, #13
MOVS	R0, #13
BL	_MP3_Set_Volume+0
;HEXIWEAR_MP3_Click.c,140 :: 		}
L_end_MP3_Init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MP3_Init
_MP3_Start:
;HEXIWEAR_MP3_Click.c,149 :: 		void MP3_Start(void)
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_MP3_Click.c,152 :: 		MP3_CS            = 1;               // Deselect MP3_CS
MOVS	R2, #1
SXTB	R2, R2
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R2, [R0, #0]
;HEXIWEAR_MP3_Click.c,153 :: 		MP3_RST           = 1;               // Set MP3_RST pin
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R2, [R0, #0]
;HEXIWEAR_MP3_Click.c,155 :: 		BSYNC             = 0;               // Clear BSYNC
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_MP3_Click.c,156 :: 		BSYNC             = 1;               // Clear BSYNC
STR	R2, [R0, #0]
;HEXIWEAR_MP3_Click.c,158 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_MP3_Click.c,159 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_MP3_Click.c,160 :: 		OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );
MOVW	R0, #lo_addr(_common_hexiwearLogo_bmp+0)
MOVT	R0, #hi_addr(_common_hexiwearLogo_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_MP3_Click.c,163 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
MOVW	R2, #lo_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVW	R1, #7
MOVT	R1, #32768
;HEXIWEAR_MP3_Click.c,162 :: 		SPI0_Init_Advanced(1000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
MOVW	R0, #16960
MOVT	R0, #15
;HEXIWEAR_MP3_Click.c,163 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
BL	_SPI0_Init_Advanced+0
;HEXIWEAR_MP3_Click.c,165 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R1, #lo_addr(_SPI2_Write+0)
MOVT	R1, #hi_addr(_SPI2_Write+0)
MOVW	R0, #lo_addr(_SPI2_Read+0)
MOVT	R0, #hi_addr(_SPI2_Read+0)
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,166 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R0, #0
PUSH	(R0)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,167 :: 		OLED_WriteText("1. Initializing", 22, 68 );
MOVW	R0, #lo_addr(?lstr1_HEXIWEAR_MP3_Click+0)
MOVT	R0, #hi_addr(?lstr1_HEXIWEAR_MP3_Click+0)
MOVS	R2, #68
MOVS	R1, #22
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,168 :: 		OLED_WriteText("VS1053B", 34, 81 );
MOVW	R0, #lo_addr(?lstr2_HEXIWEAR_MP3_Click+0)
MOVT	R0, #hi_addr(?lstr2_HEXIWEAR_MP3_Click+0)
MOVS	R2, #81
MOVS	R1, #34
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,169 :: 		MP3_Init();
BL	_MP3_Init+0
;HEXIWEAR_MP3_Click.c,170 :: 		Delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_MP3_Start4:
SUBS	R7, R7, #1
BNE	L_MP3_Start4
NOP
NOP
NOP
;HEXIWEAR_MP3_Click.c,171 :: 		}
L_end_MP3_Start:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _MP3_Start
_MP3_Test:
;HEXIWEAR_MP3_Click.c,180 :: 		void MP3_Test(char *test)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STR	R0, [SP, #8]
;HEXIWEAR_MP3_Click.c,185 :: 		*test = 0;
MOVS	R2, #0
LDR	R1, [SP, #8]
STRB	R2, [R1, #0]
;HEXIWEAR_MP3_Click.c,186 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R2, #lo_addr(_SPI2_Write+0)
MOVT	R2, #hi_addr(_SPI2_Write+0)
MOVW	R1, #lo_addr(_SPI2_Read+0)
MOVT	R1, #hi_addr(_SPI2_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,187 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R1, #0
PUSH	(R1)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,188 :: 		OLED_WriteText("2. Initializing MMC", 5, 75);
MOVW	R1, #lo_addr(?lstr3_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr3_HEXIWEAR_MP3_Click+0)
MOVS	R2, #75
MOV	R0, R1
MOVS	R1, #5
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,189 :: 		Delay_ms(1500);
MOVW	R7, #34558
MOVT	R7, #915
NOP
NOP
L_MP3_Test6:
SUBS	R7, R7, #1
BNE	L_MP3_Test6
NOP
NOP
NOP
;HEXIWEAR_MP3_Click.c,190 :: 		Mmc_Set_Interface(_MMC_INTERFACE_SDHC);
MOVS	R0, #1
BL	_Mmc_Set_Interface+0
;HEXIWEAR_MP3_Click.c,191 :: 		if (Mmc_Fat_Init() == 0) {
BL	_Mmc_Fat_Init+0
CMP	R0, #0
IT	NE
BNE	L_MP3_Test8
;HEXIWEAR_MP3_Click.c,192 :: 		while(1)
L_MP3_Test9:
;HEXIWEAR_MP3_Click.c,194 :: 		OLED_DrawImage( common_hexiwearLogo_bmp, 0, 0 );
MOVW	R1, #lo_addr(_common_hexiwearLogo_bmp+0)
MOVT	R1, #hi_addr(_common_hexiwearLogo_bmp+0)
MOVS	R2, #0
MOV	R0, R1
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_MP3_Click.c,195 :: 		if (Mmc_Fat_Assign(&mp3_filename, 0) ) {
MOVS	R1, #0
MOVW	R0, #lo_addr(_mp3_filename+0)
MOVT	R0, #hi_addr(_mp3_filename+0)
BL	_Mmc_Fat_Assign+0
CMP	R0, #0
IT	EQ
BEQ	L_MP3_Test11
;HEXIWEAR_MP3_Click.c,196 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R2, #lo_addr(_SPI2_Write+0)
MOVT	R2, #hi_addr(_SPI2_Write+0)
MOVW	R1, #lo_addr(_SPI2_Read+0)
MOVT	R1, #hi_addr(_SPI2_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,197 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R1, #0
PUSH	(R1)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,198 :: 		OLED_WriteText("3. File Assigned", 10, 75);
MOVW	R1, #lo_addr(?lstr4_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr4_HEXIWEAR_MP3_Click+0)
MOVS	R2, #75
MOV	R0, R1
MOVS	R1, #10
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,199 :: 		Delay_ms(1500);
MOVW	R7, #34558
MOVT	R7, #915
NOP
NOP
L_MP3_Test12:
SUBS	R7, R7, #1
BNE	L_MP3_Test12
NOP
NOP
NOP
;HEXIWEAR_MP3_Click.c,200 :: 		Mmc_Fat_Reset(&file_size);          // Call Reset before file reading,
MOVW	R0, #lo_addr(_file_size+0)
MOVT	R0, #hi_addr(_file_size+0)
BL	_Mmc_Fat_Reset+0
;HEXIWEAR_MP3_Click.c,202 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R2, #lo_addr(_SPI2_Write+0)
MOVT	R2, #hi_addr(_SPI2_Write+0)
MOVW	R1, #lo_addr(_SPI2_Read+0)
MOVT	R1, #hi_addr(_SPI2_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,203 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R1, #0
PUSH	(R1)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,204 :: 		OLED_DrawImage( MP3_bmp, 0, 0 );
MOVS	R2, #0
MOVS	R1, #0
MOVW	R0, #lo_addr(_mp3_bmp+0)
MOVT	R0, #hi_addr(_mp3_bmp+0)
BL	_OLED_DrawImage+0
;HEXIWEAR_MP3_Click.c,205 :: 		OLED_WriteText("4. Play audio... :)", 5, 75);
MOVW	R1, #lo_addr(?lstr5_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr5_HEXIWEAR_MP3_Click+0)
MOVS	R2, #75
MOV	R0, R1
MOVS	R1, #5
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,207 :: 		while (file_size > BUFFER_SIZE)
L_MP3_Test14:
MOVW	R1, #lo_addr(_file_size+0)
MOVT	R1, #hi_addr(_file_size+0)
LDR	R1, [R1, #0]
CMP	R1, #512
IT	LS
BLS	L_MP3_Test15
;HEXIWEAR_MP3_Click.c,209 :: 		for (i=0; i<BUFFER_SIZE; i++)
; i start address is: 8 (R2)
MOVS	R2, #0
; i end address is: 8 (R2)
MOV	R0, R2
L_MP3_Test16:
; i start address is: 0 (R0)
CMP	R0, #512
IT	CS
BCS	L_MP3_Test17
;HEXIWEAR_MP3_Click.c,211 :: 		Mmc_Fat_Read(mp3_buffer + i);
MOVW	R1, #lo_addr(_mp3_buffer+0)
MOVT	R1, #hi_addr(_mp3_buffer+0)
ADDS	R1, R1, R0
STR	R0, [SP, #4]
MOV	R0, R1
BL	_Mmc_Fat_Read+0
LDR	R0, [SP, #4]
;HEXIWEAR_MP3_Click.c,209 :: 		for (i=0; i<BUFFER_SIZE; i++)
ADDS	R2, R0, #1
; i end address is: 0 (R0)
; i start address is: 8 (R2)
;HEXIWEAR_MP3_Click.c,212 :: 		}
MOV	R0, R2
; i end address is: 8 (R2)
IT	AL
BAL	L_MP3_Test16
L_MP3_Test17:
;HEXIWEAR_MP3_Click.c,213 :: 		for (i=0; i<BUFFER_SIZE/BYTES_2_WRITE; i++) {
; i start address is: 12 (R3)
MOVS	R3, #0
; i end address is: 12 (R3)
MOV	R0, R3
L_MP3_Test19:
; i start address is: 0 (R0)
CMP	R0, #16
IT	CS
BCS	L_MP3_Test20
;HEXIWEAR_MP3_Click.c,214 :: 		MP3_SDI_Write_32(mp3_buffer + i*BYTES_2_WRITE);
LSLS	R2, R0, #5
MOVW	R1, #lo_addr(_mp3_buffer+0)
MOVT	R1, #hi_addr(_mp3_buffer+0)
ADDS	R1, R1, R2
STR	R0, [SP, #4]
MOV	R0, R1
BL	_MP3_SDI_Write_32+0
LDR	R0, [SP, #4]
;HEXIWEAR_MP3_Click.c,213 :: 		for (i=0; i<BUFFER_SIZE/BYTES_2_WRITE; i++) {
ADDS	R1, R0, #1
; i end address is: 0 (R0)
; i start address is: 12 (R3)
MOV	R3, R1
;HEXIWEAR_MP3_Click.c,215 :: 		}
MOV	R0, R3
; i end address is: 12 (R3)
IT	AL
BAL	L_MP3_Test19
L_MP3_Test20:
;HEXIWEAR_MP3_Click.c,217 :: 		file_size -= BUFFER_SIZE;
MOVW	R2, #lo_addr(_file_size+0)
MOVT	R2, #hi_addr(_file_size+0)
LDR	R1, [R2, #0]
SUB	R1, R1, #512
STR	R1, [R2, #0]
;HEXIWEAR_MP3_Click.c,219 :: 		}
IT	AL
BAL	L_MP3_Test14
L_MP3_Test15:
;HEXIWEAR_MP3_Click.c,222 :: 		for (i=0; i<file_size; i++)
; i start address is: 8 (R2)
MOVS	R2, #0
; i end address is: 8 (R2)
MOV	R0, R2
L_MP3_Test22:
; i start address is: 0 (R0)
MOVW	R1, #lo_addr(_file_size+0)
MOVT	R1, #hi_addr(_file_size+0)
LDR	R1, [R1, #0]
CMP	R0, R1
IT	CS
BCS	L_MP3_Test23
;HEXIWEAR_MP3_Click.c,224 :: 		Mmc_Fat_Read(mp3_buffer + i);
MOVW	R1, #lo_addr(_mp3_buffer+0)
MOVT	R1, #hi_addr(_mp3_buffer+0)
ADDS	R1, R1, R0
STR	R0, [SP, #4]
MOV	R0, R1
BL	_Mmc_Fat_Read+0
LDR	R0, [SP, #4]
;HEXIWEAR_MP3_Click.c,222 :: 		for (i=0; i<file_size; i++)
ADDS	R2, R0, #1
; i end address is: 0 (R0)
; i start address is: 8 (R2)
;HEXIWEAR_MP3_Click.c,225 :: 		}
MOV	R0, R2
; i end address is: 8 (R2)
IT	AL
BAL	L_MP3_Test22
L_MP3_Test23:
;HEXIWEAR_MP3_Click.c,227 :: 		for (i=0; i<file_size; i++)
; i start address is: 8 (R2)
MOVS	R2, #0
; i end address is: 8 (R2)
MOV	R0, R2
L_MP3_Test25:
; i start address is: 0 (R0)
MOVW	R1, #lo_addr(_file_size+0)
MOVT	R1, #hi_addr(_file_size+0)
LDR	R1, [R1, #0]
CMP	R0, R1
IT	CS
BCS	L_MP3_Test26
;HEXIWEAR_MP3_Click.c,229 :: 		MP3_SDI_Write(mp3_buffer[i]);
MOVW	R1, #lo_addr(_mp3_buffer+0)
MOVT	R1, #hi_addr(_mp3_buffer+0)
ADDS	R1, R1, R0
LDRB	R1, [R1, #0]
STR	R0, [SP, #4]
UXTB	R0, R1
BL	_MP3_SDI_Write+0
LDR	R0, [SP, #4]
;HEXIWEAR_MP3_Click.c,227 :: 		for (i=0; i<file_size; i++)
ADDS	R1, R0, #1
; i end address is: 0 (R0)
; i start address is: 8 (R2)
MOV	R2, R1
;HEXIWEAR_MP3_Click.c,230 :: 		}
MOV	R0, R2
; i end address is: 8 (R2)
IT	AL
BAL	L_MP3_Test25
L_MP3_Test26:
;HEXIWEAR_MP3_Click.c,231 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R2, #lo_addr(_SPI2_Write+0)
MOVT	R2, #hi_addr(_SPI2_Write+0)
MOVW	R1, #lo_addr(_SPI2_Read+0)
MOVT	R1, #hi_addr(_SPI2_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,232 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R1, #0
PUSH	(R1)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,233 :: 		OLED_WriteText("5. Finish!", 10, 75);
MOVW	R1, #lo_addr(?lstr6_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr6_HEXIWEAR_MP3_Click+0)
MOVS	R2, #75
MOV	R0, R1
MOVS	R1, #10
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,234 :: 		delay_ms(1500);
MOVW	R7, #34558
MOVT	R7, #915
NOP
NOP
L_MP3_Test28:
SUBS	R7, R7, #1
BNE	L_MP3_Test28
NOP
NOP
NOP
;HEXIWEAR_MP3_Click.c,236 :: 		}
IT	AL
BAL	L_MP3_Test30
L_MP3_Test11:
;HEXIWEAR_MP3_Click.c,238 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R2, #lo_addr(_SPI2_Write+0)
MOVT	R2, #hi_addr(_SPI2_Write+0)
MOVW	R1, #lo_addr(_SPI2_Read+0)
MOVT	R1, #hi_addr(_SPI2_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,239 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R1, #0
PUSH	(R1)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,240 :: 		OLED_WriteText("3. File not assigned", 5, 75);
MOVW	R1, #lo_addr(?lstr7_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr7_HEXIWEAR_MP3_Click+0)
MOVS	R2, #75
MOV	R0, R1
MOVS	R1, #5
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,241 :: 		*test = 2;
MOVS	R2, #2
LDR	R1, [SP, #8]
STRB	R2, [R1, #0]
;HEXIWEAR_MP3_Click.c,242 :: 		}
L_MP3_Test30:
;HEXIWEAR_MP3_Click.c,243 :: 		}
IT	AL
BAL	L_MP3_Test9
;HEXIWEAR_MP3_Click.c,244 :: 		}
L_MP3_Test8:
;HEXIWEAR_MP3_Click.c,246 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R2, #lo_addr(_SPI2_Write+0)
MOVT	R2, #hi_addr(_SPI2_Write+0)
MOVW	R1, #lo_addr(_SPI2_Read+0)
MOVT	R1, #hi_addr(_SPI2_Read+0)
MOV	R0, R1
MOV	R1, R2
BL	_SPI_Set_Active+0
;HEXIWEAR_MP3_Click.c,247 :: 		OLED_DrawBox(5, 67, 91, 30, OLED_COLOR_BLACK);
MOVW	R1, #0
PUSH	(R1)
MOVS	R3, #30
MOVS	R2, #91
MOVS	R1, #67
MOVS	R0, #5
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_MP3_Click.c,248 :: 		OLED_WriteText("3. MMC FAT not", 12, 68);
MOVW	R1, #lo_addr(?lstr8_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr8_HEXIWEAR_MP3_Click+0)
MOVS	R2, #68
MOV	R0, R1
MOVS	R1, #12
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,249 :: 		OLED_WriteText("initialized", 35, 81);
MOVW	R1, #lo_addr(?lstr9_HEXIWEAR_MP3_Click+0)
MOVT	R1, #hi_addr(?lstr9_HEXIWEAR_MP3_Click+0)
MOVS	R2, #81
MOV	R0, R1
MOVS	R1, #35
BL	_OLED_WriteText+0
;HEXIWEAR_MP3_Click.c,250 :: 		*test = 2;
MOVS	R2, #2
LDR	R1, [SP, #8]
STRB	R2, [R1, #0]
;HEXIWEAR_MP3_Click.c,252 :: 		}
L_end_MP3_Test:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _MP3_Test
_main:
;HEXIWEAR_MP3_Click.c,258 :: 		void main(){
SUB	SP, SP, #4
;HEXIWEAR_MP3_Click.c,259 :: 		InitMCU();
BL	_InitMCU+0
;HEXIWEAR_MP3_Click.c,260 :: 		MP3_Start();
BL	_MP3_Start+0
;HEXIWEAR_MP3_Click.c,261 :: 		MP3_Test(&ucMP3_run_test);
MOVW	R0, #lo_addr(_ucMP3_run_test+0)
MOVT	R0, #hi_addr(_ucMP3_run_test+0)
BL	_MP3_Test+0
;HEXIWEAR_MP3_Click.c,262 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
