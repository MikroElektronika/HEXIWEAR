_Thunder_Write:
;Thunder.c,105 :: 		void Thunder_Write(unsigned short address, unsigned short data1)
; data1 start address is: 4 (R1)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
UXTB	R0, R1
; data1 end address is: 4 (R1)
; data1 start address is: 0 (R0)
;Thunder.c,108 :: 		address.B7 = 0;
LDRB	R2, [SP, #8]
BFC	R2, #7, #1
STRB	R2, [SP, #8]
;Thunder.c,109 :: 		address.B6 = 0;
LDRB	R2, [SP, #8]
BFC	R2, #6, #1
STRB	R2, [SP, #8]
;Thunder.c,110 :: 		Thunder_CS = 0;
MOVS	R3, #0
SXTB	R3, R3
MOVW	R2, #lo_addr(PTC_PDOR+0)
MOVT	R2, #hi_addr(PTC_PDOR+0)
STR	R3, [R2, #0]
;Thunder.c,111 :: 		SPI_Wr_Ptr(address);
STRB	R0, [SP, #4]
LDRB	R0, [SP, #8]
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
LDRB	R0, [SP, #4]
;Thunder.c,112 :: 		SPI_Wr_Ptr(data1);
; data1 end address is: 0 (R0)
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;Thunder.c,113 :: 		Thunder_CS = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTC_PDOR+0)
MOVT	R2, #hi_addr(PTC_PDOR+0)
STR	R3, [R2, #0]
;Thunder.c,114 :: 		}
L_end_Thunder_Write:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _Thunder_Write
_Thunder_Read:
;Thunder.c,116 :: 		unsigned short Thunder_Read(unsigned short address)
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;Thunder.c,118 :: 		unsigned short tmp = 0;
;Thunder.c,120 :: 		address.B7 = 0;
LDRB	R1, [SP, #4]
BFC	R1, #7, #1
STRB	R1, [SP, #4]
;Thunder.c,121 :: 		address.B6 = 1;
LDRB	R1, [SP, #4]
ORR	R1, R1, #64
STRB	R1, [SP, #4]
;Thunder.c,122 :: 		Thunder_CS = 0;
MOVS	R2, #0
SXTB	R2, R2
MOVW	R1, #lo_addr(PTC_PDOR+0)
MOVT	R1, #hi_addr(PTC_PDOR+0)
STR	R2, [R1, #0]
;Thunder.c,123 :: 		SPI_Wr_Ptr(address);
LDRB	R0, [SP, #4]
MOVW	R4, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;Thunder.c,124 :: 		tmp = SPI_Rd_Ptr(0);
MOVS	R0, #0
MOVW	R4, #lo_addr(_SPI_Rd_Ptr+0)
MOVT	R4, #hi_addr(_SPI_Rd_Ptr+0)
LDR	R4, [R4, #0]
BLX	R4
;Thunder.c,125 :: 		Thunder_CS = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R1, #lo_addr(PTC_PDOR+0)
MOVT	R1, #hi_addr(PTC_PDOR+0)
STR	R2, [R1, #0]
;Thunder.c,127 :: 		return tmp;
UXTB	R0, R0
;Thunder.c,128 :: 		}
L_end_Thunder_Read:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _Thunder_Read
_Thunder_Init:
;Thunder.c,131 :: 		void Thunder_Init(void)
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Thunder.c,134 :: 		SPI_Set_Active(SPI0_Read, SPI0_Write);
MOVW	R1, #lo_addr(_SPI0_Write+0)
MOVT	R1, #hi_addr(_SPI0_Write+0)
MOVW	R0, #lo_addr(_SPI0_Read+0)
MOVT	R0, #hi_addr(_SPI0_Read+0)
BL	_SPI_Set_Active+0
;Thunder.c,135 :: 		Thunder_CS = 1;                      // Set CS to idle
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;Thunder.c,137 :: 		Thunder_Write(0x3C, 0x96);           // set all registers in default mode
MOVS	R1, #150
MOVS	R0, #60
BL	_Thunder_Write+0
;Thunder.c,138 :: 		Thunder_Write(0x3D, 0x96);           // calibrate internal oscillator
MOVS	R1, #150
MOVS	R0, #61
BL	_Thunder_Write+0
;Thunder.c,140 :: 		temp = Thunder_Read(0x00) & 0xC1;
MOVS	R0, #0
BL	_Thunder_Read+0
AND	R0, R0, #193
UXTB	R0, R0
;Thunder.c,141 :: 		Thunder_Write(0x00, ((_INDOR << 1) | temp)); // set to indoor
ORR	R0, R0, #36
UXTB	R1, R0
MOVS	R0, #0
BL	_Thunder_Write+0
;Thunder.c,143 :: 		temp = Thunder_Read(0x01) & 0x80;
MOVS	R0, #1
BL	_Thunder_Read+0
AND	R0, R0, #128
UXTB	R0, R0
;Thunder.c,144 :: 		Thunder_Write(0x01, 0x44 | temp);    // set NFL and WDTreshold
ORR	R0, R0, #68
UXTB	R1, R0
MOVS	R0, #1
BL	_Thunder_Write+0
;Thunder.c,146 :: 		temp = Thunder_Read(0x02) & 0x80;    // clear statistics, min number of ligtning, spike rejection
MOVS	R0, #2
BL	_Thunder_Read+0
AND	R0, R0, #128
UXTB	R0, R0
;Thunder.c,147 :: 		Thunder_Write(0x02, 0x40 | temp);
ORR	R0, R0, #64
UXTB	R1, R0
MOVS	R0, #2
BL	_Thunder_Write+0
;Thunder.c,149 :: 		temp = Thunder_Read(0x03) & 0x1F;    // Frequency division ratio(antenna),mask disturber, interrupt
MOVS	R0, #3
BL	_Thunder_Read+0
AND	R0, R0, #31
;Thunder.c,150 :: 		Thunder_Write(0x03, 0x00 | temp);
UXTB	R1, R0
MOVS	R0, #3
BL	_Thunder_Write+0
;Thunder.c,152 :: 		Thunder_Write(0x08, 0x00);           // LCO, SRCO, TRCO on IRQ, capacitors tuning
MOVS	R1, #0
MOVS	R0, #8
BL	_Thunder_Write+0
;Thunder.c,153 :: 		}
L_end_Thunder_Init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Thunder_Init
_Thunder_Read_Energy:
;Thunder.c,155 :: 		long int Thunder_Read_Energy()
SUB	SP, SP, #12
STR	LR, [SP, #0]
;Thunder.c,160 :: 		Out_thunder_energy = Thunder_Read(0x06) & 0x1F;
MOVS	R0, #6
BL	_Thunder_Read+0
AND	R0, R0, #31
UXTB	R0, R0
STR	R0, [SP, #8]
;Thunder.c,161 :: 		mid_byte = Thunder_Read(0x05);
MOVS	R0, #5
BL	_Thunder_Read+0
STRB	R0, [SP, #4]
;Thunder.c,162 :: 		low_byte = Thunder_Read(0x04);
MOVS	R0, #4
BL	_Thunder_Read+0
;Thunder.c,164 :: 		Out_thunder_energy = (Out_thunder_energy << 8);
LDR	R1, [SP, #8]
LSLS	R2, R1, #8
;Thunder.c,165 :: 		Out_thunder_energy = (Out_thunder_energy | mid_byte);
LDRB	R1, [SP, #4]
ORR	R1, R2, R1, LSL #0
;Thunder.c,166 :: 		Out_thunder_energy = (Out_thunder_energy << 8);
LSLS	R1, R1, #8
;Thunder.c,167 :: 		Out_thunder_energy = (Out_thunder_energy | low_byte);
ORR	R0, R1, R0, LSL #0
;Thunder.c,169 :: 		return Out_thunder_energy;
;Thunder.c,170 :: 		}
L_end_Thunder_Read_Energy:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _Thunder_Read_Energy
_Thunder_Read_distance:
;Thunder.c,173 :: 		unsigned int Thunder_Read_distance()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Thunder.c,177 :: 		Out_thunder_distance = Thunder_Read(0x07) & 0x3F;
MOVS	R0, #7
BL	_Thunder_Read+0
AND	R0, R0, #63
UXTB	R0, R0
; Out_thunder_distance start address is: 0 (R0)
;Thunder.c,179 :: 		return Out_thunder_distance;
UXTH	R0, R0
; Out_thunder_distance end address is: 0 (R0)
;Thunder.c,180 :: 		}
L_end_Thunder_Read_distance:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Thunder_Read_distance
_system_init:
;Thunder.c,182 :: 		void system_init()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Thunder.c,184 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;Thunder.c,185 :: 		GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;Thunder.c,187 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
MOVW	R2, #lo_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVW	R1, #7
MOVT	R1, #33280
;Thunder.c,186 :: 		SPI0_Init_Advanced(1000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
MOVW	R0, #16960
MOVT	R0, #15
;Thunder.c,187 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
BL	_SPI0_Init_Advanced+0
;Thunder.c,189 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _system_init
_display_init:
;Thunder.c,191 :: 		void display_init()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Thunder.c,193 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R1, #lo_addr(_SPI2_Write+0)
MOVT	R1, #hi_addr(_SPI2_Write+0)
MOVW	R0, #lo_addr(_SPI2_Read+0)
MOVT	R0, #hi_addr(_SPI2_Read+0)
BL	_SPI_Set_Active+0
;Thunder.c,195 :: 		OLED_Init();
BL	_OLED_Init+0
;Thunder.c,196 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;Thunder.c,198 :: 		OLED_DrawImage( thunder_bmp, 0, 0 );
MOVW	R0, #lo_addr(_thunder_bmp+0)
MOVT	R0, #hi_addr(_thunder_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Thunder.c,199 :: 		}
L_end_display_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _display_init
_main:
;Thunder.c,202 :: 		void main() org 0x1000
SUB	SP, SP, #4
;Thunder.c,204 :: 		system_init();
BL	_system_init+0
;Thunder.c,206 :: 		display_init();
BL	_display_init+0
;Thunder.c,208 :: 		Thunder_Init();
BL	_Thunder_Init+0
;Thunder.c,211 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;Thunder.c,212 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;Thunder.c,213 :: 		PORTB_PCR13bits.IRQC = 0xB;
MOVS	R2, #11
MOVW	R1, #lo_addr(PORTB_PCR13bits+0)
MOVT	R1, #hi_addr(PORTB_PCR13bits+0)
LDR	R0, [R1, #0]
BFI	R0, R2, #16, #4
STR	R0, [R1, #0]
;Thunder.c,215 :: 		while (1)
L_main0:
;Thunder.c,217 :: 		if ( 1 == isThunderDetected )
MOVW	R0, #lo_addr(Thunder_isThunderDetected+0)
MOVT	R0, #hi_addr(Thunder_isThunderDetected+0)
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	NE
BNE	L_main2
;Thunder.c,219 :: 		NVIC_IntDisable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntDisable+0
;Thunder.c,220 :: 		SPI_Set_Active(SPI0_Read, SPI0_Write);
MOVW	R1, #lo_addr(_SPI0_Write+0)
MOVT	R1, #hi_addr(_SPI0_Write+0)
MOVW	R0, #lo_addr(_SPI0_Read+0)
MOVT	R0, #hi_addr(_SPI0_Read+0)
BL	_SPI_Set_Active+0
;Thunder.c,222 :: 		interrupt_source = Thunder_Read(0x03) & 0x0F;
MOVS	R0, #3
BL	_Thunder_Read+0
AND	R1, R0, #15
MOVW	R0, #lo_addr(_interrupt_source+0)
MOVT	R0, #hi_addr(_interrupt_source+0)
STRB	R1, [R0, #0]
;Thunder.c,223 :: 		distance = Thunder_Read_distance();
BL	_Thunder_Read_distance+0
MOVW	R1, #lo_addr(_distance+0)
MOVT	R1, #hi_addr(_distance+0)
STRH	R0, [R1, #0]
;Thunder.c,224 :: 		value = Thunder_Read_Energy();
BL	_Thunder_Read_Energy+0
MOVW	R1, #lo_addr(_value+0)
MOVT	R1, #hi_addr(_value+0)
STRH	R0, [R1, #0]
;Thunder.c,226 :: 		switch (interrupt_source){
IT	AL
BAL	L_main3
;Thunder.c,227 :: 		case 4:
L_main5:
;Thunder.c,229 :: 		IntToStr((distance*2), Out_Text);
MOVW	R0, #lo_addr(_distance+0)
MOVT	R0, #hi_addr(_distance+0)
LDRH	R0, [R0, #0]
LSLS	R0, R0, #1
MOVW	R1, #lo_addr(_Out_Text+0)
MOVT	R1, #hi_addr(_Out_Text+0)
SXTH	R0, R0
BL	_IntToStr+0
;Thunder.c,231 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R1, #lo_addr(_SPI2_Write+0)
MOVT	R1, #hi_addr(_SPI2_Write+0)
MOVW	R0, #lo_addr(_SPI2_Read+0)
MOVT	R0, #hi_addr(_SPI2_Read+0)
BL	_SPI_Set_Active+0
;Thunder.c,232 :: 		OLED_DrawImage( thundera_bmp, 0, 0 );
MOVW	R0, #lo_addr(_thundera_bmp+0)
MOVT	R0, #hi_addr(_thundera_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Thunder.c,233 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;Thunder.c,234 :: 		OLED_WriteText(Out_Text, 41, 82 );
MOVS	R2, #82
MOVS	R1, #41
MOVW	R0, #lo_addr(_Out_Text+0)
MOVT	R0, #hi_addr(_Out_Text+0)
BL	_OLED_WriteText+0
;Thunder.c,235 :: 		OLED_WriteText("Distance:", 10, 82 );
MOVW	R0, #lo_addr(?lstr1_Thunder+0)
MOVT	R0, #hi_addr(?lstr1_Thunder+0)
MOVS	R2, #82
MOVS	R1, #10
BL	_OLED_WriteText+0
;Thunder.c,236 :: 		OLED_WriteText("Thundering", 17, 71 );
MOVW	R0, #lo_addr(?lstr2_Thunder+0)
MOVT	R0, #hi_addr(?lstr2_Thunder+0)
MOVS	R2, #71
MOVS	R1, #17
BL	_OLED_WriteText+0
;Thunder.c,237 :: 		OLED_WriteText("km", 70, 82 );
MOVW	R0, #lo_addr(?lstr3_Thunder+0)
MOVT	R0, #hi_addr(?lstr3_Thunder+0)
MOVS	R2, #82
MOVS	R1, #70
BL	_OLED_WriteText+0
;Thunder.c,239 :: 		delay_ms(3000);
MOVW	R7, #3582
MOVT	R7, #1831
NOP
NOP
L_main6:
SUBS	R7, R7, #1
BNE	L_main6
NOP
NOP
NOP
;Thunder.c,240 :: 		OLED_DrawImage( thunder_bmp, 0, 0 );
MOVW	R0, #lo_addr(_thunder_bmp+0)
MOVT	R0, #hi_addr(_thunder_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Thunder.c,241 :: 		break;
IT	AL
BAL	L_main4
;Thunder.c,243 :: 		case 2:
L_main8:
;Thunder.c,245 :: 		SPI_Set_Active(SPI2_Read, SPI2_Write);
MOVW	R1, #lo_addr(_SPI2_Write+0)
MOVT	R1, #hi_addr(_SPI2_Write+0)
MOVW	R0, #lo_addr(_SPI2_Read+0)
MOVT	R0, #hi_addr(_SPI2_Read+0)
BL	_SPI_Set_Active+0
;Thunder.c,246 :: 		OLED_DrawImage( thundera_bmp, 0, 0 );
MOVW	R0, #lo_addr(_thundera_bmp+0)
MOVT	R0, #hi_addr(_thundera_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Thunder.c,247 :: 		OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;Thunder.c,248 :: 		OLED_WriteText("Disturbance", 20, 75 );
MOVW	R0, #lo_addr(?lstr4_Thunder+0)
MOVT	R0, #hi_addr(?lstr4_Thunder+0)
MOVS	R2, #75
MOVS	R1, #20
BL	_OLED_WriteText+0
;Thunder.c,250 :: 		delay_ms(2000);
MOVW	R7, #46078
MOVT	R7, #1220
NOP
NOP
L_main9:
SUBS	R7, R7, #1
BNE	L_main9
NOP
NOP
NOP
;Thunder.c,251 :: 		OLED_DrawImage( thunder_bmp, 0, 0 );
MOVW	R0, #lo_addr(_thunder_bmp+0)
MOVT	R0, #hi_addr(_thunder_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;Thunder.c,252 :: 		break;
IT	AL
BAL	L_main4
;Thunder.c,254 :: 		}
L_main3:
MOVW	R0, #lo_addr(_interrupt_source+0)
MOVT	R0, #hi_addr(_interrupt_source+0)
LDRB	R0, [R0, #0]
CMP	R0, #4
IT	EQ
BEQ	L_main5
MOVW	R0, #lo_addr(_interrupt_source+0)
MOVT	R0, #hi_addr(_interrupt_source+0)
LDRB	R0, [R0, #0]
CMP	R0, #2
IT	EQ
BEQ	L_main8
L_main4:
;Thunder.c,255 :: 		isThunderDetected = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(Thunder_isThunderDetected+0)
MOVT	R0, #hi_addr(Thunder_isThunderDetected+0)
STRB	R1, [R0, #0]
;Thunder.c,256 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;Thunder.c,257 :: 		}
L_main2:
;Thunder.c,258 :: 		}
IT	AL
BAL	L_main0
;Thunder.c,259 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_External1Int:
;Thunder.c,265 :: 		void External1Int() iv IVT_INT_PORTB ics ICS_AUTO
;Thunder.c,267 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;Thunder.c,268 :: 		isThunderDetected = 1;
MOVS	R1, #1
MOVW	R0, #lo_addr(Thunder_isThunderDetected+0)
MOVT	R0, #hi_addr(Thunder_isThunderDetected+0)
STRB	R1, [R0, #0]
;Thunder.c,269 :: 		}
L_end_External1Int:
BX	LR
; end of _External1Int
