_OLED_PowerOn:
;OLED_driver.c,79 :: 		void OLED_PowerOn(void)
SUB	SP, SP, #4
;OLED_driver.c,81 :: 		OLED_Pwr_bit = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,82 :: 		}
L_end_OLED_PowerOn:
ADD	SP, SP, #4
BX	LR
; end of _OLED_PowerOn
_OLED_PowerOff:
;OLED_driver.c,88 :: 		void OLED_PowerOff(void)
SUB	SP, SP, #4
;OLED_driver.c,90 :: 		OLED_Pwr_bit = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,91 :: 		}
L_end_OLED_PowerOff:
ADD	SP, SP, #4
BX	LR
; end of _OLED_PowerOff
_OLED_SendCmd:
;OLED_driver.c,106 :: 		)
; isFirst start address is: 4 (R1)
; cmd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; isFirst end address is: 4 (R1)
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; isFirst start address is: 4 (R1)
;OLED_driver.c,108 :: 		if ( isFirst )
CMP	R1, #0
IT	EQ
BEQ	L_OLED_SendCmd0
; isFirst end address is: 4 (R1)
;OLED_driver.c,110 :: 		OLED_DC_bit = 0;
MOVS	R3, #0
SXTB	R3, R3
MOVW	R2, #lo_addr(PTD_PDOR+0)
MOVT	R2, #hi_addr(PTD_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,111 :: 		}
IT	AL
BAL	L_OLED_SendCmd1
L_OLED_SendCmd0:
;OLED_driver.c,114 :: 		OLED_DC_bit = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTD_PDOR+0)
MOVT	R2, #hi_addr(PTD_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,115 :: 		}
L_OLED_SendCmd1:
;OLED_driver.c,117 :: 		OLED_CS_bit = 0;
MOVS	R3, #0
SXTB	R3, R3
MOVW	R2, #lo_addr(PTB_PDOR+0)
MOVT	R2, #hi_addr(PTB_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,119 :: 		SPI2_Write((uint8_t)cmd);
UXTB	R0, R0
; cmd end address is: 0 (R0)
BL	_SPI2_Write+0
;OLED_driver.c,121 :: 		OLED_CS_bit = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTB_PDOR+0)
MOVT	R2, #hi_addr(PTB_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,123 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,124 :: 		}
L_end_OLED_SendCmd:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_SendCmd
_OLED_Init:
;OLED_driver.c,136 :: 		oled_status_t OLED_Init(void)
SUB	SP, SP, #4
STR	LR, [SP, #0]
;OLED_driver.c,138 :: 		oled_text_properties.alignParam = OLED_TEXT_ALIGN_CENTER;
MOVS	R1, #3
MOVW	R0, #lo_addr(OLED_driver_oled_text_properties+6)
MOVT	R0, #hi_addr(OLED_driver_oled_text_properties+6)
STRB	R1, [R0, #0]
;OLED_driver.c,139 :: 		oled_text_properties.background = NULL;
MOVS	R1, #0
MOVW	R0, #lo_addr(OLED_driver_oled_text_properties+8)
MOVT	R0, #hi_addr(OLED_driver_oled_text_properties+8)
STR	R1, [R0, #0]
;OLED_driver.c,141 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_13);
MOV	R1, #8192
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,142 :: 		GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_15);
MOV	R1, #32768
MOVW	R0, #lo_addr(PTD_PDOR+0)
MOVT	R0, #hi_addr(PTD_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,143 :: 		GPIO_Digital_Output(&PTE_PDOR, _GPIO_PINMASK_6);
MOV	R1, #64
MOVW	R0, #lo_addr(PTE_PDOR+0)
MOVT	R0, #hi_addr(PTE_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,144 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_20);
MOV	R1, #1048576
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,147 :: 		_SPI_CFG_CLK_IDLE_HIGH | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI2_PB21_23_22);
MOVW	R2, #lo_addr(__GPIO_Module_SPI2_PB21_23_22+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI2_PB21_23_22+0)
MOVW	R1, #7
MOVT	R1, #34304
;OLED_driver.c,146 :: 		SPI2_Init_Advanced(18000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
MOVW	R0, #43136
MOVT	R0, #274
;OLED_driver.c,147 :: 		_SPI_CFG_CLK_IDLE_HIGH | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI2_PB21_23_22);
BL	_SPI2_Init_Advanced+0
;OLED_driver.c,148 :: 		PORTB_PCR21bits.DSE = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PORTB_PCR21bits+0)
MOVT	R0, #hi_addr(PORTB_PCR21bits+0)
STR	R1, [R0, #0]
;OLED_driver.c,149 :: 		PORTB_PCR22bits.DSE = 1;
MOVW	R0, #lo_addr(PORTB_PCR22bits+0)
MOVT	R0, #hi_addr(PORTB_PCR22bits+0)
STR	R1, [R0, #0]
;OLED_driver.c,150 :: 		PORTB_PCR23bits.DSE = 1;
MOVW	R0, #lo_addr(PORTB_PCR23bits+0)
MOVT	R0, #hi_addr(PORTB_PCR23bits+0)
STR	R1, [R0, #0]
;OLED_driver.c,155 :: 		OLED_PowerOff();
BL	_OLED_PowerOff+0
;OLED_driver.c,156 :: 		Delay_1ms();
BL	_Delay_1ms+0
;OLED_driver.c,157 :: 		OLED_RST_bit = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTE_PDOR+0)
MOVT	R0, #hi_addr(PTE_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,158 :: 		Delay_1ms();
BL	_Delay_1ms+0
;OLED_driver.c,159 :: 		OLED_RST_bit = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTE_PDOR+0)
MOVT	R0, #hi_addr(PTE_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,160 :: 		Delay_1ms();
BL	_Delay_1ms+0
;OLED_driver.c,161 :: 		OLED_PowerOn();
BL	_OLED_PowerOn+0
;OLED_driver.c,163 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #253
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init2
;OLED_driver.c,165 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,166 :: 		}
L_OLED_Init2:
;OLED_driver.c,167 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_UNLOCK, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #18
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init3
;OLED_driver.c,169 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,170 :: 		}
L_OLED_Init3:
;OLED_driver.c,172 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #253
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init4
;OLED_driver.c,174 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,175 :: 		}
L_OLED_Init4:
;OLED_driver.c,176 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_ACC_TO_CMD_YES, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #177
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init5
;OLED_driver.c,178 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,179 :: 		}
L_OLED_Init5:
;OLED_driver.c,181 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #174
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init6
;OLED_driver.c,183 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,184 :: 		}
L_OLED_Init6:
;OLED_driver.c,186 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #179
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init7
;OLED_driver.c,188 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,189 :: 		}
L_OLED_Init7:
;OLED_driver.c,190 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xF1, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #241
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init8
;OLED_driver.c,192 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,193 :: 		}
L_OLED_Init8:
;OLED_driver.c,195 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_MUX_RATIO, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #202
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init9
;OLED_driver.c,197 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,198 :: 		}
L_OLED_Init9:
;OLED_driver.c,199 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #95
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init10
;OLED_driver.c,201 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,202 :: 		}
L_OLED_Init10:
;OLED_driver.c,204 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #160
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init11
;OLED_driver.c,206 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,207 :: 		}
L_OLED_Init11:
;OLED_driver.c,208 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #96
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init12
;OLED_driver.c,210 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,211 :: 		}
L_OLED_Init12:
;OLED_driver.c,213 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #21
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init13
;OLED_driver.c,215 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,216 :: 		}
L_OLED_Init13:
;OLED_driver.c,217 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #0
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init14
;OLED_driver.c,219 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,220 :: 		}
L_OLED_Init14:
;OLED_driver.c,221 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #95
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init15
;OLED_driver.c,223 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,224 :: 		}
L_OLED_Init15:
;OLED_driver.c,226 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #117
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init16
;OLED_driver.c,228 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,229 :: 		}
L_OLED_Init16:
;OLED_driver.c,230 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #0
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init17
;OLED_driver.c,232 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,233 :: 		}
L_OLED_Init17:
;OLED_driver.c,234 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #95
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init18
;OLED_driver.c,236 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,237 :: 		}
L_OLED_Init18:
;OLED_driver.c,239 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_STARTLINE, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #161
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init19
;OLED_driver.c,241 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,242 :: 		}
L_OLED_Init19:
;OLED_driver.c,243 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x80, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #128
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init20
;OLED_driver.c,245 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,246 :: 		}
L_OLED_Init20:
;OLED_driver.c,248 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFFSET, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #162
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init21
;OLED_driver.c,250 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,251 :: 		}
L_OLED_Init21:
;OLED_driver.c,252 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x60, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #96
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init22
;OLED_driver.c,254 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,255 :: 		}
L_OLED_Init22:
;OLED_driver.c,257 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #177
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init23
;OLED_driver.c,259 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,260 :: 		}
L_OLED_Init23:
;OLED_driver.c,261 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x32, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #50
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init24
;OLED_driver.c,263 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,264 :: 		}
L_OLED_Init24:
;OLED_driver.c,266 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_VCOMH, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #190
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init25
;OLED_driver.c,268 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,269 :: 		}
L_OLED_Init25:
;OLED_driver.c,270 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x05, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #5
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init26
;OLED_driver.c,272 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,273 :: 		}
L_OLED_Init26:
;OLED_driver.c,275 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_NORMALDISPLAY, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #166
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init27
;OLED_driver.c,277 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,278 :: 		}
L_OLED_Init27:
;OLED_driver.c,280 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_CONTRASTABC, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #193
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init28
;OLED_driver.c,282 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,283 :: 		}
L_OLED_Init28:
;OLED_driver.c,284 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #138
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init29
;OLED_driver.c,286 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,287 :: 		}
L_OLED_Init29:
;OLED_driver.c,288 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x51, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #81
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init30
;OLED_driver.c,290 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,291 :: 		}
L_OLED_Init30:
;OLED_driver.c,292 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #138
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init31
;OLED_driver.c,294 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,295 :: 		}
L_OLED_Init31:
;OLED_driver.c,297 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #199
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init32
;OLED_driver.c,299 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,300 :: 		}
L_OLED_Init32:
;OLED_driver.c,301 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xCF, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #207
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init33
;OLED_driver.c,303 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,304 :: 		}
L_OLED_Init33:
;OLED_driver.c,306 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SETVSL, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #180
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init34
;OLED_driver.c,308 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,309 :: 		}
L_OLED_Init34:
;OLED_driver.c,310 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xA0, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #160
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init35
;OLED_driver.c,312 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,313 :: 		}
L_OLED_Init35:
;OLED_driver.c,314 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xB5, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #181
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init36
;OLED_driver.c,316 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,317 :: 		}
L_OLED_Init36:
;OLED_driver.c,318 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x55, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #85
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init37
;OLED_driver.c,320 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,321 :: 		}
L_OLED_Init37:
;OLED_driver.c,323 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE2, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #182
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init38
;OLED_driver.c,325 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,326 :: 		}
L_OLED_Init38:
;OLED_driver.c,327 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x01, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #1
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init39
;OLED_driver.c,329 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,330 :: 		}
L_OLED_Init39:
;OLED_driver.c,332 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #175
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init40
;OLED_driver.c,334 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,335 :: 		}
L_OLED_Init40:
;OLED_driver.c,337 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,338 :: 		}
L_end_OLED_Init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_Init
_OLED_SendData:
;OLED_driver.c,351 :: 		)
; dataSize start address is: 4 (R1)
; dataToSend start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R5, R0
MOV	R6, R1
; dataSize end address is: 4 (R1)
; dataToSend end address is: 0 (R0)
; dataToSend start address is: 20 (R5)
; dataSize start address is: 24 (R6)
;OLED_driver.c,356 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #92
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_SendData41
; dataToSend end address is: 20 (R5)
; dataSize end address is: 24 (R6)
;OLED_driver.c,358 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_SendData
;OLED_driver.c,359 :: 		}
L_OLED_SendData41:
;OLED_driver.c,362 :: 		OLED_DC_bit = 1;
; dataSize start address is: 24 (R6)
; dataToSend start address is: 20 (R5)
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTD_PDOR+0)
MOVT	R2, #hi_addr(PTD_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,363 :: 		OLED_CS_bit = 0;
MOVS	R3, #0
SXTB	R3, R3
MOVW	R2, #lo_addr(PTB_PDOR+0)
MOVT	R2, #hi_addr(PTB_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,365 :: 		bufPtr = dataToSend;
; bufPtr start address is: 0 (R0)
MOV	R0, R5
; dataToSend end address is: 20 (R5)
; bufPtr end address is: 0 (R0)
MOV	R5, R0
MOV	R0, R6
;OLED_driver.c,367 :: 		while(dataSize--)
L_OLED_SendData42:
; bufPtr start address is: 20 (R5)
; dataSize start address is: 0 (R0)
MOV	R3, R0
SUBS	R2, R0, #1
; dataSize end address is: 0 (R0)
; dataSize start address is: 24 (R6)
MOV	R6, R2
; dataSize end address is: 24 (R6)
CMP	R3, #0
IT	EQ
BEQ	L_OLED_SendData43
; dataSize end address is: 24 (R6)
;OLED_driver.c,369 :: 		SPI2_Write(*(bufPtr++));
; dataSize start address is: 24 (R6)
LDRB	R2, [R5, #0]
UXTH	R0, R2
BL	_SPI2_Write+0
ADDS	R5, R5, #1
;OLED_driver.c,370 :: 		}
MOV	R0, R6
; dataSize end address is: 24 (R6)
; bufPtr end address is: 20 (R5)
IT	AL
BAL	L_OLED_SendData42
L_OLED_SendData43:
;OLED_driver.c,372 :: 		OLED_CS_bit = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTB_PDOR+0)
MOVT	R2, #hi_addr(PTB_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,373 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,374 :: 		}
L_end_OLED_SendData:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_SendData
_OLED_DrawBox:
;OLED_driver.c,395 :: 		)
; height start address is: 12 (R3)
; width start address is: 8 (R2)
; yCrd start address is: 4 (R1)
; xCrd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
UXTH	R10, R0
UXTH	R9, R1
UXTH	R5, R2
UXTH	R8, R3
; height end address is: 12 (R3)
; width end address is: 8 (R2)
; yCrd end address is: 4 (R1)
; xCrd end address is: 0 (R0)
; xCrd start address is: 40 (R10)
; yCrd start address is: 36 (R9)
; width start address is: 20 (R5)
; height start address is: 32 (R8)
; color start address is: 24 (R6)
LDRH	R6, [SP, #4]
;OLED_driver.c,397 :: 		oled_status_t status = OLED_STATUS_SUCCESS;
;OLED_driver.c,400 :: 		boxSize = width*height;
MUL	R4, R5, R8
UXTH	R4, R4
; boxSize start address is: 28 (R7)
UXTH	R7, R4
;OLED_driver.c,403 :: 		if (AreCoordsNotValid(xCrd, yCrd, width, height))
ADD	R4, R10, R5, LSL #0
UXTH	R4, R4
SUBS	R4, R4, #1
UXTH	R4, R4
CMP	R4, #96
IT	HI
BHI	L_OLED_DrawBox45
CMP	R10, #0
IT	CC
BCC	L_OLED_DrawBox45
ADD	R4, R9, R8, LSL #0
UXTH	R4, R4
SUBS	R4, R4, #1
UXTH	R4, R4
CMP	R4, #96
IT	HI
BHI	L_OLED_DrawBox45
CMP	R9, #0
IT	CC
BCC	L_OLED_DrawBox45
MOVS	R4, #0
IT	AL
BAL	L_OLED_DrawBox44
L_OLED_DrawBox45:
MOVS	R4, #1
L_OLED_DrawBox44:
CMP	R4, #0
IT	EQ
BEQ	L_OLED_DrawBox46
; width end address is: 20 (R5)
; height end address is: 32 (R8)
; boxSize end address is: 28 (R7)
; xCrd end address is: 40 (R10)
; yCrd end address is: 36 (R9)
; color end address is: 24 (R6)
;OLED_driver.c,405 :: 		status = OLED_STATUS_INIT_ERROR;
; status start address is: 0 (R0)
MOVS	R0, #3
;OLED_driver.c,406 :: 		}
; status end address is: 0 (R0)
IT	AL
BAL	L_OLED_DrawBox47
L_OLED_DrawBox46:
;OLED_driver.c,419 :: 		OLED_AdjustColumnOffset(xCrd);
; color start address is: 24 (R6)
; yCrd start address is: 36 (R9)
; xCrd start address is: 40 (R10)
; boxSize start address is: 28 (R7)
; height start address is: 32 (R8)
; width start address is: 20 (R5)
ADD	R10, R10, #16
UXTH	R10, R10
;OLED_driver.c,420 :: 		OLED_AdjustRowOffset(yCrd);
;OLED_driver.c,422 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #21
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox48
; width end address is: 20 (R5)
; height end address is: 32 (R8)
; boxSize end address is: 28 (R7)
; xCrd end address is: 40 (R10)
; yCrd end address is: 36 (R9)
; color end address is: 24 (R6)
;OLED_driver.c,424 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,425 :: 		}
L_OLED_DrawBox48:
;OLED_driver.c,426 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd, OTHER_BYTE ) )
; color start address is: 24 (R6)
; yCrd start address is: 36 (R9)
; xCrd start address is: 40 (R10)
; boxSize start address is: 28 (R7)
; height start address is: 32 (R8)
; width start address is: 20 (R5)
MOVS	R1, #0
UXTH	R0, R10
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox49
; width end address is: 20 (R5)
; height end address is: 32 (R8)
; boxSize end address is: 28 (R7)
; xCrd end address is: 40 (R10)
; yCrd end address is: 36 (R9)
; color end address is: 24 (R6)
;OLED_driver.c,428 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,429 :: 		}
L_OLED_DrawBox49:
;OLED_driver.c,430 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd + (width-1), OTHER_BYTE ) )
; color start address is: 24 (R6)
; yCrd start address is: 36 (R9)
; xCrd start address is: 40 (R10)
; boxSize start address is: 28 (R7)
; height start address is: 32 (R8)
; width start address is: 20 (R5)
SUBS	R4, R5, #1
UXTH	R4, R4
; width end address is: 20 (R5)
ADD	R4, R10, R4, LSL #0
UXTH	R4, R4
; xCrd end address is: 40 (R10)
MOVS	R1, #0
UXTH	R0, R4
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox50
; height end address is: 32 (R8)
; boxSize end address is: 28 (R7)
; yCrd end address is: 36 (R9)
; color end address is: 24 (R6)
;OLED_driver.c,432 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,433 :: 		}
L_OLED_DrawBox50:
;OLED_driver.c,435 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
; color start address is: 24 (R6)
; yCrd start address is: 36 (R9)
; boxSize start address is: 28 (R7)
; height start address is: 32 (R8)
MOVS	R1, #1
MOVS	R0, #117
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox51
; height end address is: 32 (R8)
; boxSize end address is: 28 (R7)
; yCrd end address is: 36 (R9)
; color end address is: 24 (R6)
;OLED_driver.c,437 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,438 :: 		}
L_OLED_DrawBox51:
;OLED_driver.c,439 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd, OTHER_BYTE ) )
; color start address is: 24 (R6)
; yCrd start address is: 36 (R9)
; boxSize start address is: 28 (R7)
; height start address is: 32 (R8)
MOVS	R1, #0
UXTH	R0, R9
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox52
; height end address is: 32 (R8)
; boxSize end address is: 28 (R7)
; yCrd end address is: 36 (R9)
; color end address is: 24 (R6)
;OLED_driver.c,441 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,442 :: 		}
L_OLED_DrawBox52:
;OLED_driver.c,443 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd + (height-1), OTHER_BYTE ) )
; color start address is: 24 (R6)
; yCrd start address is: 36 (R9)
; boxSize start address is: 28 (R7)
; height start address is: 32 (R8)
SUB	R4, R8, #1
UXTH	R4, R4
; height end address is: 32 (R8)
ADD	R4, R9, R4, LSL #0
UXTH	R4, R4
; yCrd end address is: 36 (R9)
MOVS	R1, #0
UXTH	R0, R4
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox53
; boxSize end address is: 28 (R7)
; color end address is: 24 (R6)
;OLED_driver.c,445 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,446 :: 		}
L_OLED_DrawBox53:
;OLED_driver.c,448 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
; color start address is: 24 (R6)
; boxSize start address is: 28 (R7)
MOVS	R1, #1
MOVS	R0, #92
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox54
; boxSize end address is: 28 (R7)
; color end address is: 24 (R6)
;OLED_driver.c,450 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,451 :: 		}
L_OLED_DrawBox54:
;OLED_driver.c,453 :: 		OLED_DC_bit = 1;
; color start address is: 24 (R6)
; boxSize start address is: 28 (R7)
MOVS	R5, #1
SXTB	R5, R5
MOVW	R4, #lo_addr(PTD_PDOR+0)
MOVT	R4, #hi_addr(PTD_PDOR+0)
STR	R5, [R4, #0]
;OLED_driver.c,454 :: 		OLED_CS_bit = 0;
MOVS	R5, #0
SXTB	R5, R5
MOVW	R4, #lo_addr(PTB_PDOR+0)
MOVT	R4, #hi_addr(PTB_PDOR+0)
STR	R5, [R4, #0]
;OLED_driver.c,455 :: 		for(cnt = 0; cnt < boxSize; cnt++)
; cnt start address is: 0 (R0)
MOVS	R0, #0
; boxSize end address is: 28 (R7)
; cnt end address is: 0 (R0)
MOV	R5, R7
UXTH	R7, R0
L_OLED_DrawBox55:
; cnt start address is: 28 (R7)
; boxSize start address is: 20 (R5)
; color start address is: 24 (R6)
; color end address is: 24 (R6)
CMP	R7, R5
IT	CS
BCS	L_OLED_DrawBox56
; color end address is: 24 (R6)
;OLED_driver.c,457 :: 		SPI2_Write((uint8_t)(color >> 8));
; color start address is: 24 (R6)
LSRS	R4, R6, #8
UXTB	R0, R4
BL	_SPI2_Write+0
;OLED_driver.c,458 :: 		SPI2_Write((uint8_t)color);
UXTB	R0, R6
BL	_SPI2_Write+0
;OLED_driver.c,455 :: 		for(cnt = 0; cnt < boxSize; cnt++)
ADDS	R7, R7, #1
UXTH	R7, R7
;OLED_driver.c,459 :: 		}
; boxSize end address is: 20 (R5)
; color end address is: 24 (R6)
; cnt end address is: 28 (R7)
IT	AL
BAL	L_OLED_DrawBox55
L_OLED_DrawBox56:
;OLED_driver.c,460 :: 		OLED_CS_bit = 1;
MOVS	R5, #1
SXTB	R5, R5
MOVW	R4, #lo_addr(PTB_PDOR+0)
MOVT	R4, #hi_addr(PTB_PDOR+0)
STR	R5, [R4, #0]
;OLED_driver.c,462 :: 		status = OLED_STATUS_SUCCESS;
; status start address is: 0 (R0)
MOVS	R0, #0
; status end address is: 0 (R0)
;OLED_driver.c,463 :: 		}
L_OLED_DrawBox47:
;OLED_driver.c,465 :: 		return status;
; status start address is: 0 (R0)
; status end address is: 0 (R0)
;OLED_driver.c,466 :: 		}
L_end_OLED_DrawBox:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_DrawBox
_OLED_FillScreen:
;OLED_driver.c,477 :: 		oled_status_t OLED_FillScreen( uint16_t color )
; color start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; color end address is: 0 (R0)
; color start address is: 0 (R0)
;OLED_driver.c,479 :: 		return OLED_DrawBox(0, 0, 96, 96, color);;
PUSH	(R0)
MOVS	R3, #96
MOVS	R2, #96
MOVS	R1, #0
MOVS	R0, #0
; color end address is: 0 (R0)
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;OLED_driver.c,480 :: 		}
L_end_OLED_FillScreen:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_FillScreen
_OLED_DrawPixel:
;OLED_driver.c,498 :: 		)
; color start address is: 8 (R2)
; yCrd start address is: 4 (R1)
; xCrd start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
SXTH	R10, R0
SXTH	R11, R1
; color end address is: 8 (R2)
; yCrd end address is: 4 (R1)
; xCrd end address is: 0 (R0)
; xCrd start address is: 40 (R10)
; yCrd start address is: 44 (R11)
; color start address is: 8 (R2)
;OLED_driver.c,501 :: 		if AreCoordsNotValid( xCrd, yCrd, 1, 1 )
ADD	R3, R10, #1
SXTH	R3, R3
SUBS	R3, R3, #1
SXTH	R3, R3
CMP	R3, #96
IT	GT
BGT	L_OLED_DrawPixel59
CMP	R10, #0
IT	LT
BLT	L_OLED_DrawPixel59
ADD	R3, R11, #1
SXTH	R3, R3
SUBS	R3, R3, #1
SXTH	R3, R3
CMP	R3, #96
IT	GT
BGT	L_OLED_DrawPixel59
CMP	R11, #0
IT	LT
BLT	L_OLED_DrawPixel59
MOVS	R3, #0
IT	AL
BAL	L_OLED_DrawPixel58
L_OLED_DrawPixel59:
MOVS	R3, #1
L_OLED_DrawPixel58:
CMP	R3, #0
IT	EQ
BEQ	L_OLED_DrawPixel60
; xCrd end address is: 40 (R10)
; yCrd end address is: 44 (R11)
; color end address is: 8 (R2)
;OLED_driver.c,503 :: 		return OLED_STATUS_INIT_ERROR;
MOVS	R0, #3
IT	AL
BAL	L_end_OLED_DrawPixel
;OLED_driver.c,504 :: 		}
L_OLED_DrawPixel60:
;OLED_driver.c,508 :: 		uint16_t dot = color;
; color start address is: 8 (R2)
; yCrd start address is: 44 (R11)
; xCrd start address is: 40 (R10)
STRH	R2, [SP, #4]
; color end address is: 8 (R2)
;OLED_driver.c,511 :: 		SetBorders( xCrd, yCrd, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);
MOVS	R3, #96
MOVS	R2, #96
UXTB	R1, R11
; yCrd end address is: 44 (R11)
UXTB	R0, R10
; xCrd end address is: 40 (R10)
BL	OLED_driver_SetBorders+0
;OLED_driver.c,513 :: 		OLED_SwapMe(dot);
LDRH	R3, [SP, #4]
AND	R3, R3, #65280
UXTH	R3, R3
LSRS	R4, R3, #8
UXTH	R4, R4
LDRH	R3, [SP, #4]
AND	R3, R3, #255
UXTH	R3, R3
LSLS	R3, R3, #8
UXTH	R3, R3
ORR	R3, R4, R3, LSL #0
STRH	R3, [SP, #4]
;OLED_driver.c,516 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)&dot, 2 ) )
ADD	R3, SP, #4
MOVS	R1, #2
MOV	R0, R3
BL	_OLED_SendData+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawPixel62
;OLED_driver.c,518 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawPixel
;OLED_driver.c,519 :: 		}
L_OLED_DrawPixel62:
;OLED_driver.c,520 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,522 :: 		}
L_end_OLED_DrawPixel:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _OLED_DrawPixel
OLED_driver_SetBorders:
;OLED_driver.c,539 :: 		)
; height start address is: 12 (R3)
; width start address is: 8 (R2)
; yCrd start address is: 4 (R1)
; xCrd start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; height end address is: 12 (R3)
; width end address is: 8 (R2)
; yCrd end address is: 4 (R1)
; xCrd end address is: 0 (R0)
; xCrd start address is: 0 (R0)
; yCrd start address is: 4 (R1)
; width start address is: 8 (R2)
; height start address is: 12 (R3)
;OLED_driver.c,544 :: 		OLED_AdjustColumnOffset(xCrd);
ADDW	R4, R0, #16
; xCrd end address is: 0 (R0)
; xCrd start address is: 24 (R6)
UXTB	R6, R4
;OLED_driver.c,545 :: 		OLED_AdjustRowOffset(yCrd);
UXTB	R4, R1
; yCrd end address is: 4 (R1)
; yCrd start address is: 20 (R5)
UXTB	R5, R4
; width end address is: 8 (R2)
; height end address is: 12 (R3)
; yCrd end address is: 20 (R5)
; xCrd end address is: 24 (R6)
UXTB	R8, R2
UXTB	R7, R3
;OLED_driver.c,547 :: 		while (1)
L_OLED_driver_SetBorders63:
;OLED_driver.c,549 :: 		oledStatus = OLED_STATUS_SUCCESS;
; yCrd start address is: 20 (R5)
; xCrd start address is: 24 (R6)
; height start address is: 28 (R7)
; width start address is: 32 (R8)
; oledStatus start address is: 36 (R9)
MOVW	R9, #0
;OLED_driver.c,551 :: 		oledStatus |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
MOVS	R1, #1
MOVS	R0, #21
BL	_OLED_SendCmd+0
ORR	R9, R9, R0, LSL #0
UXTB	R9, R9
;OLED_driver.c,552 :: 		oledStatus |= OLED_SendCmd( xCrd, OTHER_BYTE );
MOVS	R1, #0
UXTB	R0, R6
BL	_OLED_SendCmd+0
ORR	R9, R9, R0, LSL #0
UXTB	R9, R9
;OLED_driver.c,553 :: 		oledStatus |= OLED_SendCmd( xCrd + (width-1), OTHER_BYTE );
SUB	R4, R8, #1
SXTH	R4, R4
ADDS	R4, R6, R4
SXTH	R4, R4
MOVS	R1, #0
SXTH	R0, R4
BL	_OLED_SendCmd+0
ORR	R9, R9, R0, LSL #0
UXTB	R9, R9
;OLED_driver.c,554 :: 		oledStatus |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
MOVS	R1, #1
MOVS	R0, #117
BL	_OLED_SendCmd+0
ORR	R9, R9, R0, LSL #0
UXTB	R9, R9
;OLED_driver.c,555 :: 		oledStatus |= OLED_SendCmd( yCrd, OTHER_BYTE );
MOVS	R1, #0
UXTB	R0, R5
BL	_OLED_SendCmd+0
ORR	R9, R9, R0, LSL #0
UXTB	R9, R9
;OLED_driver.c,556 :: 		oledStatus |= OLED_SendCmd( yCrd + (height-1), OTHER_BYTE );
SUBS	R4, R7, #1
SXTH	R4, R4
ADDS	R4, R5, R4
SXTH	R4, R4
MOVS	R1, #0
SXTH	R0, R4
BL	_OLED_SendCmd+0
ORR	R4, R9, R0, LSL #0
UXTB	R4, R4
;OLED_driver.c,558 :: 		if ( OLED_STATUS_SUCCESS == oledStatus)
CMP	R4, #0
IT	NE
BNE	L_OLED_driver_SetBorders65
; yCrd end address is: 20 (R5)
; xCrd end address is: 24 (R6)
; height end address is: 28 (R7)
; width end address is: 32 (R8)
; oledStatus end address is: 36 (R9)
;OLED_driver.c,560 :: 		break;
IT	AL
BAL	L_OLED_driver_SetBorders64
;OLED_driver.c,561 :: 		}
L_OLED_driver_SetBorders65:
;OLED_driver.c,562 :: 		}
; oledStatus start address is: 36 (R9)
; width start address is: 32 (R8)
; height start address is: 28 (R7)
; xCrd start address is: 24 (R6)
; yCrd start address is: 20 (R5)
; yCrd end address is: 20 (R5)
; xCrd end address is: 24 (R6)
; height end address is: 28 (R7)
; width end address is: 32 (R8)
; oledStatus end address is: 36 (R9)
IT	AL
BAL	L_OLED_driver_SetBorders63
L_OLED_driver_SetBorders64:
;OLED_driver.c,563 :: 		}
L_end_SetBorders:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of OLED_driver_SetBorders
OLED_driver_OLED_Swap:
;OLED_driver.c,575 :: 		)
; imgSize start address is: 8 (R2)
; imgSrc start address is: 4 (R1)
; imgDst start address is: 0 (R0)
SUB	SP, SP, #4
UXTH	R3, R2
MOV	R2, R1
; imgSize end address is: 8 (R2)
; imgSrc end address is: 4 (R1)
; imgDst end address is: 0 (R0)
; imgDst start address is: 0 (R0)
; imgSrc start address is: 8 (R2)
; imgSize start address is: 12 (R3)
;OLED_driver.c,578 :: 		for (var = 0; var < imgSize; var++)
; var start address is: 4 (R1)
MOVS	R1, #0
; imgDst end address is: 0 (R0)
; imgSrc end address is: 8 (R2)
; imgSize end address is: 12 (R3)
; var end address is: 4 (R1)
MOV	R4, R2
MOV	R2, R0
UXTH	R0, R3
L_OLED_driver_OLED_Swap66:
; var start address is: 4 (R1)
; imgSize start address is: 0 (R0)
; imgSrc start address is: 16 (R4)
; imgDst start address is: 8 (R2)
CMP	R1, R0
IT	CS
BCS	L_OLED_driver_OLED_Swap67
;OLED_driver.c,580 :: 		*imgDst = *imgSrc << 8;
LDRB	R3, [R4, #0]
LSLS	R3, R3, #8
STRH	R3, [R2, #0]
;OLED_driver.c,581 :: 		imgSrc++;
ADDS	R3, R4, #1
; imgSrc end address is: 16 (R4)
; imgSrc start address is: 20 (R5)
MOV	R5, R3
;OLED_driver.c,582 :: 		*imgDst |= *imgSrc;
LDRB	R4, [R3, #0]
LDRH	R3, [R2, #0]
ORRS	R3, R4
STRH	R3, [R2, #0]
;OLED_driver.c,583 :: 		imgDst++;
ADDS	R2, R2, #2
;OLED_driver.c,584 :: 		imgSrc++;
ADDS	R3, R5, #1
; imgSrc end address is: 20 (R5)
; imgSrc start address is: 16 (R4)
MOV	R4, R3
;OLED_driver.c,578 :: 		for (var = 0; var < imgSize; var++)
ADDS	R1, R1, #1
;OLED_driver.c,585 :: 		}
; imgSize end address is: 0 (R0)
; imgDst end address is: 8 (R2)
; imgSrc end address is: 16 (R4)
; var end address is: 4 (R1)
IT	AL
BAL	L_OLED_driver_OLED_Swap66
L_OLED_driver_OLED_Swap67:
;OLED_driver.c,586 :: 		}
L_end_OLED_Swap:
ADD	SP, SP, #4
BX	LR
; end of OLED_driver_OLED_Swap
_OLED_GetImageDimensions:
;OLED_driver.c,592 :: 		void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image)
; image start address is: 8 (R2)
; height start address is: 4 (R1)
; width start address is: 0 (R0)
SUB	SP, SP, #4
; image end address is: 8 (R2)
; height end address is: 4 (R1)
; width end address is: 0 (R0)
; width start address is: 0 (R0)
; height start address is: 4 (R1)
; image start address is: 8 (R2)
;OLED_driver.c,594 :: 		*height = image[2] + (image[3] << 8);
ADDS	R3, R2, #2
LDRB	R4, [R3, #0]
ADDS	R3, R2, #3
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R3, R4, R3
STRB	R3, [R1, #0]
; height end address is: 4 (R1)
;OLED_driver.c,595 :: 		*width  = image[4] + (image[5] << 8);
ADDS	R3, R2, #4
LDRB	R4, [R3, #0]
ADDS	R3, R2, #5
; image end address is: 8 (R2)
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R3, R4, R3
STRB	R3, [R0, #0]
; width end address is: 0 (R0)
;OLED_driver.c,596 :: 		}
L_end_OLED_GetImageDimensions:
ADD	SP, SP, #4
BX	LR
; end of _OLED_GetImageDimensions
_OLED_DrawImage:
;OLED_driver.c,602 :: 		oled_status_t OLED_DrawImage (const uint8_t* image, uint8_t xCrd, uint8_t yCrd)
; yCrd start address is: 8 (R2)
; xCrd start address is: 4 (R1)
; image start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
UXTB	R10, R1
UXTB	R11, R2
; yCrd end address is: 8 (R2)
; xCrd end address is: 4 (R1)
; image end address is: 0 (R0)
; image start address is: 0 (R0)
; xCrd start address is: 40 (R10)
; yCrd start address is: 44 (R11)
;OLED_driver.c,604 :: 		oled_status_t status = OLED_STATUS_SUCCESS;
;OLED_driver.c,608 :: 		ptr = image;
; ptr start address is: 4 (R1)
MOV	R1, R0
;OLED_driver.c,610 :: 		ptr += 2;
ADDS	R4, R1, #2
; ptr end address is: 4 (R1)
;OLED_driver.c,611 :: 		height = *ptr;
LDRB	R3, [R4, #0]
; height start address is: 4 (R1)
UXTB	R1, R3
;OLED_driver.c,612 :: 		ptr++;
ADDS	R4, R4, #1
;OLED_driver.c,613 :: 		height += (*ptr) << 8;
LDRB	R3, [R4, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R3, R1, R3
; height end address is: 4 (R1)
; height start address is: 48 (R12)
UXTH	R12, R3
;OLED_driver.c,615 :: 		ptr++;
ADDS	R4, R4, #1
;OLED_driver.c,616 :: 		width = *ptr;
LDRB	R1, [R4, #0]
; width start address is: 4 (R1)
UXTB	R1, R1
;OLED_driver.c,617 :: 		ptr++;
ADDS	R3, R4, #1
;OLED_driver.c,618 :: 		width += (*ptr)<<8;
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R3, R1, R3
UXTH	R3, R3
UXTH	R1, R3
;OLED_driver.c,621 :: 		if AreCoordsNotValid( xCrd, yCrd, width, height )
ADD	R3, R10, R3, LSL #0
UXTH	R3, R3
SUBS	R3, R3, #1
UXTH	R3, R3
CMP	R3, #96
IT	HI
BHI	L_OLED_DrawImage70
CMP	R10, #0
IT	CC
BCC	L_OLED_DrawImage70
ADD	R3, R11, R12, LSL #0
UXTH	R3, R3
SUBS	R3, R3, #1
UXTH	R3, R3
CMP	R3, #96
IT	HI
BHI	L_OLED_DrawImage70
CMP	R11, #0
IT	CC
BCC	L_OLED_DrawImage70
MOVS	R3, #0
IT	AL
BAL	L_OLED_DrawImage69
L_OLED_DrawImage70:
MOVS	R3, #1
L_OLED_DrawImage69:
CMP	R3, #0
IT	EQ
BEQ	L_OLED_DrawImage71
; image end address is: 0 (R0)
;OLED_driver.c,624 :: 		}
IT	AL
BAL	L_OLED_DrawImage72
L_OLED_DrawImage71:
;OLED_driver.c,628 :: 		OLED_Swap( screenBuf, (const uint8_t*)( image ) + 6 , width * height );
; image start address is: 0 (R0)
MUL	R4, R1, R12
ADDS	R3, R0, #6
; image end address is: 0 (R0)
STRH	R1, [SP, #4]
UXTH	R2, R4
MOV	R1, R3
MOVW	R0, #lo_addr(OLED_driver_screenBuf+0)
MOVT	R0, #hi_addr(OLED_driver_screenBuf+0)
BL	OLED_driver_OLED_Swap+0
LDRH	R1, [SP, #4]
;OLED_driver.c,632 :: 		}
L_OLED_DrawImage72:
;OLED_driver.c,635 :: 		SetBorders( xCrd, yCrd, width, height );
STRH	R1, [SP, #4]
UXTB	R3, R12
UXTB	R2, R1
UXTB	R1, R11
; yCrd end address is: 44 (R11)
UXTB	R0, R10
; xCrd end address is: 40 (R10)
BL	OLED_driver_SetBorders+0
LDRH	R1, [SP, #4]
;OLED_driver.c,638 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)screenBuf, width * height * OLED_BYTES_PER_PIXEL ) )
MUL	R3, R1, R12
UXTH	R3, R3
; height end address is: 48 (R12)
; width end address is: 4 (R1)
LSLS	R3, R3, #1
UXTH	R3, R3
UXTH	R1, R3
MOVW	R0, #lo_addr(OLED_driver_screenBuf+0)
MOVT	R0, #hi_addr(OLED_driver_screenBuf+0)
BL	_OLED_SendData+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawImage73
;OLED_driver.c,640 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawImage
;OLED_driver.c,641 :: 		}
L_OLED_DrawImage73:
;OLED_driver.c,643 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,644 :: 		}
L_end_OLED_DrawImage:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _OLED_DrawImage
_OLED_SetFont:
;OLED_driver.c,650 :: 		void OLED_SetFont(const uint8_t *activeFont, uint16_t font_color, uint8_t font_orientation)
; font_orientation start address is: 8 (R2)
; font_color start address is: 4 (R1)
; activeFont start address is: 0 (R0)
SUB	SP, SP, #4
; font_orientation end address is: 8 (R2)
; font_color end address is: 4 (R1)
; activeFont end address is: 0 (R0)
; activeFont start address is: 0 (R0)
; font_color start address is: 4 (R1)
; font_orientation start address is: 8 (R2)
;OLED_driver.c,652 :: 		_font = activeFont;
MOVW	R3, #lo_addr(OLED_driver__font+0)
MOVT	R3, #hi_addr(OLED_driver__font+0)
STR	R0, [R3, #0]
;OLED_driver.c,653 :: 		_fontFirstChar = activeFont[2] + (activeFont[3] << 8);
ADDS	R3, R0, #2
LDRB	R4, [R3, #0]
ADDS	R3, R0, #3
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R4, R4, R3
MOVW	R3, #lo_addr(OLED_driver__fontFirstChar+0)
MOVT	R3, #hi_addr(OLED_driver__fontFirstChar+0)
STRH	R4, [R3, #0]
;OLED_driver.c,654 :: 		_fontLastChar = activeFont[4] + (activeFont[5] << 8);
ADDS	R3, R0, #4
LDRB	R4, [R3, #0]
ADDS	R3, R0, #5
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R4, R4, R3
MOVW	R3, #lo_addr(OLED_driver__fontLastChar+0)
MOVT	R3, #hi_addr(OLED_driver__fontLastChar+0)
STRH	R4, [R3, #0]
;OLED_driver.c,655 :: 		_fontHeight = activeFont[6];
ADDS	R3, R0, #6
; activeFont end address is: 0 (R0)
LDRB	R4, [R3, #0]
MOVW	R3, #lo_addr(OLED_driver__fontHeight+0)
MOVT	R3, #hi_addr(OLED_driver__fontHeight+0)
STRH	R4, [R3, #0]
;OLED_driver.c,657 :: 		FontColor = font_color;
MOVW	R3, #lo_addr(OLED_driver_FontColor+0)
MOVT	R3, #hi_addr(OLED_driver_FontColor+0)
STRH	R1, [R3, #0]
; font_color end address is: 4 (R1)
;OLED_driver.c,658 :: 		FontOrientation = font_orientation;
MOVW	R3, #lo_addr(OLED_driver_FontOrientation+0)
MOVT	R3, #hi_addr(OLED_driver_FontOrientation+0)
STRB	R2, [R3, #0]
; font_orientation end address is: 8 (R2)
;OLED_driver.c,659 :: 		FontInitialized = 1;
MOVS	R4, #1
MOVW	R3, #lo_addr(OLED_driver_FontInitialized+0)
MOVT	R3, #hi_addr(OLED_driver_FontInitialized+0)
STRB	R4, [R3, #0]
;OLED_driver.c,660 :: 		ExternalFontSet = 0;
MOVS	R4, #0
MOVW	R3, #lo_addr(_ExternalFontSet+0)
MOVT	R3, #hi_addr(_ExternalFontSet+0)
STRB	R4, [R3, #0]
;OLED_driver.c,661 :: 		}
L_end_OLED_SetFont:
ADD	SP, SP, #4
BX	LR
; end of _OLED_SetFont
_OLED_WriteText:
;OLED_driver.c,668 :: 		void OLED_WriteText(uint8_t *text, uint16_t x, uint16_t y) {
; y start address is: 8 (R2)
; x start address is: 4 (R1)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STR	R0, [SP, #8]
; y end address is: 8 (R2)
; x end address is: 4 (R1)
; x start address is: 4 (R1)
; y start address is: 8 (R2)
;OLED_driver.c,671 :: 		if (x >= OLED_SCREEN_WIDTH)
CMP	R1, #96
IT	CC
BCC	L_OLED_WriteText74
; x end address is: 4 (R1)
; y end address is: 8 (R2)
;OLED_driver.c,672 :: 		return;
IT	AL
BAL	L_end_OLED_WriteText
L_OLED_WriteText74:
;OLED_driver.c,673 :: 		if (y >= OLED_SCREEN_HEIGHT)
; y start address is: 8 (R2)
; x start address is: 4 (R1)
CMP	R2, #96
IT	CC
BCC	L_OLED_WriteText75
; x end address is: 4 (R1)
; y end address is: 8 (R2)
;OLED_driver.c,674 :: 		return;
IT	AL
BAL	L_end_OLED_WriteText
L_OLED_WriteText75:
;OLED_driver.c,676 :: 		i = 0;
; y start address is: 8 (R2)
; x start address is: 4 (R1)
MOVS	R3, #0
STRH	R3, [SP, #4]
;OLED_driver.c,677 :: 		OLED_MoveCursor(x, y);
UXTH	R0, R1
; y end address is: 8 (R2)
UXTH	R1, R2
; x end address is: 4 (R1)
BL	OLED_driver_OLED_MoveCursor+0
;OLED_driver.c,678 :: 		while (text[i])
L_OLED_WriteText76:
LDRH	R4, [SP, #4]
LDR	R3, [SP, #8]
ADDS	R3, R3, R4
LDRB	R3, [R3, #0]
CMP	R3, #0
IT	EQ
BEQ	L_OLED_WriteText77
;OLED_driver.c,679 :: 		OLED_WriteChar(text[i++]);
LDRH	R4, [SP, #4]
LDR	R3, [SP, #8]
ADDS	R3, R3, R4
LDRB	R3, [R3, #0]
UXTH	R0, R3
BL	OLED_driver_OLED_WriteChar+0
LDRH	R3, [SP, #4]
ADDS	R3, R3, #1
STRH	R3, [SP, #4]
IT	AL
BAL	L_OLED_WriteText76
L_OLED_WriteText77:
;OLED_driver.c,680 :: 		}
L_end_OLED_WriteText:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _OLED_WriteText
OLED_driver_OLED_MoveCursor:
;OLED_driver.c,686 :: 		static void OLED_MoveCursor(uint16_t _x, uint16_t _y)
; _y start address is: 4 (R1)
; _x start address is: 0 (R0)
SUB	SP, SP, #4
; _y end address is: 4 (R1)
; _x end address is: 0 (R0)
; _x start address is: 0 (R0)
; _y start address is: 4 (R1)
;OLED_driver.c,688 :: 		x_cord = _x;
MOVW	R2, #lo_addr(OLED_driver_x_cord+0)
MOVT	R2, #hi_addr(OLED_driver_x_cord+0)
STRH	R0, [R2, #0]
; _x end address is: 0 (R0)
;OLED_driver.c,689 :: 		y_cord = _y;
MOVW	R2, #lo_addr(OLED_driver_y_cord+0)
MOVT	R2, #hi_addr(OLED_driver_y_cord+0)
STRH	R1, [R2, #0]
; _y end address is: 4 (R1)
;OLED_driver.c,690 :: 		}
L_end_OLED_MoveCursor:
ADD	SP, SP, #4
BX	LR
; end of OLED_driver_OLED_MoveCursor
OLED_driver_OLED_WriteChar:
;OLED_driver.c,696 :: 		static void OLED_WriteChar(uint16_t ch)
; ch start address is: 0 (R0)
SUB	SP, SP, #24
STR	LR, [SP, #0]
UXTH	R5, R0
; ch end address is: 0 (R0)
; ch start address is: 20 (R5)
;OLED_driver.c,698 :: 		uint8_t chWidth = 0;
;OLED_driver.c,700 :: 		uint16_t x = 0, y;
MOVW	R1, #0
STRH	R1, [SP, #20]
MOVS	R1, #0
STRB	R1, [SP, #22]
;OLED_driver.c,701 :: 		uint8_t temp = 0, mask;
;OLED_driver.c,707 :: 		if(FontInitialized == 0)
MOVW	R1, #lo_addr(OLED_driver_FontInitialized+0)
MOVT	R1, #hi_addr(OLED_driver_FontInitialized+0)
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar78
;OLED_driver.c,709 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, FO_HORIZONTAL); //default font
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #0
BL	_OLED_SetFont+0
;OLED_driver.c,710 :: 		FontInitialized = 1;
MOVS	R2, #1
MOVW	R1, #lo_addr(OLED_driver_FontInitialized+0)
MOVT	R1, #hi_addr(OLED_driver_FontInitialized+0)
STRB	R2, [R1, #0]
;OLED_driver.c,711 :: 		}
L_OLED_driver_OLED_WriteChar78:
;OLED_driver.c,713 :: 		if (ch < _fontFirstChar)
MOVW	R1, #lo_addr(OLED_driver__fontFirstChar+0)
MOVT	R1, #hi_addr(OLED_driver__fontFirstChar+0)
LDRH	R1, [R1, #0]
CMP	R5, R1
IT	CS
BCS	L_OLED_driver_OLED_WriteChar79
; ch end address is: 20 (R5)
;OLED_driver.c,715 :: 		return;
IT	AL
BAL	L_end_OLED_WriteChar
;OLED_driver.c,716 :: 		}
L_OLED_driver_OLED_WriteChar79:
;OLED_driver.c,717 :: 		if (ch > _fontLastChar)
; ch start address is: 20 (R5)
MOVW	R1, #lo_addr(OLED_driver__fontLastChar+0)
MOVT	R1, #hi_addr(OLED_driver__fontLastChar+0)
LDRH	R1, [R1, #0]
CMP	R5, R1
IT	LS
BLS	L_OLED_driver_OLED_WriteChar80
; ch end address is: 20 (R5)
;OLED_driver.c,719 :: 		return;
IT	AL
BAL	L_end_OLED_WriteChar
;OLED_driver.c,720 :: 		}
L_OLED_driver_OLED_WriteChar80:
;OLED_driver.c,723 :: 		tmp = (ch - _fontFirstChar) << 2;
; ch start address is: 20 (R5)
MOVW	R1, #lo_addr(OLED_driver__fontFirstChar+0)
MOVT	R1, #hi_addr(OLED_driver__fontFirstChar+0)
LDRH	R1, [R1, #0]
SUB	R1, R5, R1
UXTH	R1, R1
; ch end address is: 20 (R5)
LSLS	R2, R1, #2
UXTH	R2, R2
;OLED_driver.c,724 :: 		pChTable = _font + 8 + tmp;
MOVW	R4, #lo_addr(OLED_driver__font+0)
MOVT	R4, #hi_addr(OLED_driver__font+0)
LDR	R1, [R4, #0]
ADDS	R1, #8
ADDS	R3, R1, R2
;OLED_driver.c,725 :: 		chWidth = *pChTable;
LDRB	R12, [R3, #0]
; chWidth start address is: 48 (R12)
;OLED_driver.c,727 :: 		offset = (uint32_t) pChTable[1] + ((uint32_t)pChTable[2] << 8) + ((uint32_t)pChTable[3] << 16);
ADDS	R1, R3, #1
LDRB	R1, [R1, #0]
UXTB	R2, R1
ADDS	R1, R3, #2
LDRB	R1, [R1, #0]
LSLS	R1, R1, #8
ADDS	R2, R2, R1
ADDS	R1, R3, #3
LDRB	R1, [R1, #0]
LSLS	R1, R1, #16
ADDS	R2, R2, R1
;OLED_driver.c,729 :: 		pChBitMap = _font + offset;
MOV	R1, R4
LDR	R1, [R1, #0]
ADDS	R1, R1, R2
STR	R1, [SP, #16]
;OLED_driver.c,731 :: 		if ((FontOrientation == FO_HORIZONTAL) || (FontOrientation == FO_VERTICAL_COLUMN))
MOVW	R1, #lo_addr(OLED_driver_FontOrientation+0)
MOVT	R1, #hi_addr(OLED_driver_FontOrientation+0)
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	EQ
BEQ	L_OLED_driver_OLED_WriteChar105
MOVW	R1, #lo_addr(OLED_driver_FontOrientation+0)
MOVT	R1, #hi_addr(OLED_driver_FontOrientation+0)
LDRB	R1, [R1, #0]
CMP	R1, #2
IT	EQ
BEQ	L_OLED_driver_OLED_WriteChar104
IT	AL
BAL	L_OLED_driver_OLED_WriteChar83
L_OLED_driver_OLED_WriteChar105:
L_OLED_driver_OLED_WriteChar104:
;OLED_driver.c,733 :: 		y = y_cord;
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
; y start address is: 8 (R2)
LDRH	R2, [R1, #0]
;OLED_driver.c,734 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
MOVS	R1, #0
STRB	R1, [SP, #13]
; chWidth end address is: 48 (R12)
; y end address is: 8 (R2)
UXTB	R3, R12
UXTH	R0, R2
L_OLED_driver_OLED_WriteChar84:
; y start address is: 0 (R0)
; chWidth start address is: 12 (R3)
MOVW	R1, #lo_addr(OLED_driver__fontHeight+0)
MOVT	R1, #hi_addr(OLED_driver__fontHeight+0)
LDRH	R2, [R1, #0]
LDRB	R1, [SP, #13]
CMP	R1, R2
IT	CS
BCS	L_OLED_driver_OLED_WriteChar85
;OLED_driver.c,736 :: 		x = x_cord;
MOVW	R1, #lo_addr(OLED_driver_x_cord+0)
MOVT	R1, #hi_addr(OLED_driver_x_cord+0)
LDRH	R1, [R1, #0]
STRH	R1, [SP, #20]
;OLED_driver.c,737 :: 		mask = 0;
; mask start address is: 24 (R6)
MOVS	R6, #0
;OLED_driver.c,738 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
MOVS	R1, #0
STRB	R1, [SP, #12]
; y end address is: 0 (R0)
; chWidth end address is: 12 (R3)
; mask end address is: 24 (R6)
UXTH	R2, R0
UXTB	R12, R3
L_OLED_driver_OLED_WriteChar87:
; mask start address is: 24 (R6)
; chWidth start address is: 48 (R12)
; y start address is: 8 (R2)
LDRB	R1, [SP, #12]
CMP	R1, R12
IT	CS
BCS	L_OLED_driver_OLED_WriteChar88
;OLED_driver.c,740 :: 		if (mask == 0)
CMP	R6, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar106
; mask end address is: 24 (R6)
;OLED_driver.c,742 :: 		temp = *pChBitMap++;
LDR	R1, [SP, #16]
LDRB	R1, [R1, #0]
STRB	R1, [SP, #22]
LDR	R1, [SP, #16]
ADDS	R1, R1, #1
STR	R1, [SP, #16]
;OLED_driver.c,743 :: 		mask = 0x01;
; mask start address is: 24 (R6)
MOVS	R6, #1
; mask end address is: 24 (R6)
UXTB	R0, R6
;OLED_driver.c,744 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar90
L_OLED_driver_OLED_WriteChar106:
;OLED_driver.c,740 :: 		if (mask == 0)
UXTB	R0, R6
;OLED_driver.c,744 :: 		}
L_OLED_driver_OLED_WriteChar90:
;OLED_driver.c,746 :: 		if (temp & mask)
; mask start address is: 0 (R0)
LDRB	R1, [SP, #22]
ANDS	R1, R0
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L_OLED_driver_OLED_WriteChar91
;OLED_driver.c,748 :: 		OLED_DrawPixel(x, y, FontColor);
MOVW	R1, #lo_addr(OLED_driver_FontColor+0)
MOVT	R1, #hi_addr(OLED_driver_FontColor+0)
LDRH	R1, [R1, #0]
STRB	R0, [SP, #4]
STRH	R2, [SP, #6]
STRH	R2, [SP, #8]
LDRH	R0, [SP, #20]
UXTH	R2, R1
LDRSH	R1, [SP, #8]
BL	_OLED_DrawPixel+0
LDRH	R2, [SP, #6]
LDRB	R0, [SP, #4]
;OLED_driver.c,749 :: 		}
L_OLED_driver_OLED_WriteChar91:
;OLED_driver.c,751 :: 		x++;
LDRH	R1, [SP, #20]
ADDS	R1, R1, #1
STRH	R1, [SP, #20]
;OLED_driver.c,752 :: 		mask <<= 1;
LSLS	R1, R0, #1
; mask end address is: 0 (R0)
; mask start address is: 24 (R6)
UXTB	R6, R1
;OLED_driver.c,738 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
LDRB	R1, [SP, #12]
ADDS	R1, R1, #1
STRB	R1, [SP, #12]
;OLED_driver.c,753 :: 		}
; mask end address is: 24 (R6)
IT	AL
BAL	L_OLED_driver_OLED_WriteChar87
L_OLED_driver_OLED_WriteChar88:
;OLED_driver.c,754 :: 		y++;
ADDS	R2, R2, #1
UXTH	R2, R2
;OLED_driver.c,734 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
LDRB	R1, [SP, #13]
ADDS	R1, R1, #1
STRB	R1, [SP, #13]
;OLED_driver.c,755 :: 		}
UXTB	R3, R12
; chWidth end address is: 48 (R12)
; y end address is: 8 (R2)
UXTH	R0, R2
IT	AL
BAL	L_OLED_driver_OLED_WriteChar84
L_OLED_driver_OLED_WriteChar85:
;OLED_driver.c,758 :: 		if (FontOrientation == FO_HORIZONTAL)
; y start address is: 0 (R0)
MOVW	R1, #lo_addr(OLED_driver_FontOrientation+0)
MOVT	R1, #hi_addr(OLED_driver_FontOrientation+0)
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar92
; y end address is: 0 (R0)
;OLED_driver.c,760 :: 		x_cord = x + 1;
LDRH	R1, [SP, #20]
ADDS	R2, R1, #1
MOVW	R1, #lo_addr(OLED_driver_x_cord+0)
MOVT	R1, #hi_addr(OLED_driver_x_cord+0)
STRH	R2, [R1, #0]
;OLED_driver.c,761 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar93
L_OLED_driver_OLED_WriteChar92:
;OLED_driver.c,764 :: 		y_cord = y; // visini nego sirini, nema potrebe da se dodaje jedan pixel kao
; y start address is: 0 (R0)
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
STRH	R0, [R1, #0]
; y end address is: 0 (R0)
;OLED_driver.c,765 :: 		}
L_OLED_driver_OLED_WriteChar93:
;OLED_driver.c,766 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar94
L_OLED_driver_OLED_WriteChar83:
;OLED_driver.c,769 :: 		y = x_cord;
; chWidth start address is: 48 (R12)
MOVW	R1, #lo_addr(OLED_driver_x_cord+0)
MOVT	R1, #hi_addr(OLED_driver_x_cord+0)
; y start address is: 12 (R3)
LDRH	R3, [R1, #0]
;OLED_driver.c,770 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
MOVS	R1, #0
STRB	R1, [SP, #13]
; y end address is: 12 (R3)
; chWidth end address is: 48 (R12)
UXTH	R0, R3
UXTB	R3, R12
L_OLED_driver_OLED_WriteChar95:
; y start address is: 0 (R0)
; chWidth start address is: 12 (R3)
MOVW	R1, #lo_addr(OLED_driver__fontHeight+0)
MOVT	R1, #hi_addr(OLED_driver__fontHeight+0)
LDRH	R2, [R1, #0]
LDRB	R1, [SP, #13]
CMP	R1, R2
IT	CS
BCS	L_OLED_driver_OLED_WriteChar96
;OLED_driver.c,772 :: 		x = y_cord;
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
LDRH	R1, [R1, #0]
STRH	R1, [SP, #20]
;OLED_driver.c,773 :: 		mask = 0;
; mask start address is: 24 (R6)
MOVS	R6, #0
;OLED_driver.c,774 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
MOVS	R1, #0
STRB	R1, [SP, #12]
; y end address is: 0 (R0)
; chWidth end address is: 12 (R3)
; mask end address is: 24 (R6)
UXTH	R2, R0
UXTB	R12, R3
L_OLED_driver_OLED_WriteChar98:
; mask start address is: 24 (R6)
; chWidth start address is: 48 (R12)
; y start address is: 8 (R2)
LDRB	R1, [SP, #12]
CMP	R1, R12
IT	CS
BCS	L_OLED_driver_OLED_WriteChar99
;OLED_driver.c,776 :: 		if (mask == 0)
CMP	R6, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar107
; mask end address is: 24 (R6)
;OLED_driver.c,778 :: 		temp = *pChBitMap++;
LDR	R1, [SP, #16]
LDRB	R1, [R1, #0]
STRB	R1, [SP, #22]
LDR	R1, [SP, #16]
ADDS	R1, R1, #1
STR	R1, [SP, #16]
;OLED_driver.c,779 :: 		mask = 0x01;
; mask start address is: 24 (R6)
MOVS	R6, #1
; mask end address is: 24 (R6)
UXTB	R0, R6
;OLED_driver.c,780 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar101
L_OLED_driver_OLED_WriteChar107:
;OLED_driver.c,776 :: 		if (mask == 0)
UXTB	R0, R6
;OLED_driver.c,780 :: 		}
L_OLED_driver_OLED_WriteChar101:
;OLED_driver.c,782 :: 		if (temp & mask)
; mask start address is: 0 (R0)
LDRB	R1, [SP, #22]
ANDS	R1, R0
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L_OLED_driver_OLED_WriteChar102
;OLED_driver.c,784 :: 		OLED_DrawPixel(y, x, FontColor);
MOVW	R1, #lo_addr(OLED_driver_FontColor+0)
MOVT	R1, #hi_addr(OLED_driver_FontColor+0)
LDRH	R1, [R1, #0]
STRB	R0, [SP, #4]
STRH	R2, [SP, #6]
SXTH	R0, R2
UXTH	R2, R1
LDRH	R1, [SP, #20]
BL	_OLED_DrawPixel+0
LDRH	R2, [SP, #6]
LDRB	R0, [SP, #4]
;OLED_driver.c,785 :: 		}
L_OLED_driver_OLED_WriteChar102:
;OLED_driver.c,787 :: 		x--;
LDRH	R1, [SP, #20]
SUBS	R1, R1, #1
STRH	R1, [SP, #20]
;OLED_driver.c,788 :: 		mask <<= 1;
LSLS	R1, R0, #1
; mask end address is: 0 (R0)
; mask start address is: 24 (R6)
UXTB	R6, R1
;OLED_driver.c,774 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
LDRB	R1, [SP, #12]
ADDS	R1, R1, #1
STRB	R1, [SP, #12]
;OLED_driver.c,789 :: 		}
; mask end address is: 24 (R6)
IT	AL
BAL	L_OLED_driver_OLED_WriteChar98
L_OLED_driver_OLED_WriteChar99:
;OLED_driver.c,791 :: 		y++;
ADDS	R1, R2, #1
; y end address is: 8 (R2)
; y start address is: 12 (R3)
UXTH	R3, R1
;OLED_driver.c,770 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
LDRB	R1, [SP, #13]
ADDS	R1, R1, #1
STRB	R1, [SP, #13]
;OLED_driver.c,792 :: 		}
UXTH	R0, R3
; y end address is: 12 (R3)
; chWidth end address is: 48 (R12)
UXTB	R3, R12
IT	AL
BAL	L_OLED_driver_OLED_WriteChar95
L_OLED_driver_OLED_WriteChar96:
;OLED_driver.c,795 :: 		y_cord = x - 1;
LDRH	R1, [SP, #20]
SUBS	R2, R1, #1
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
STRH	R2, [R1, #0]
;OLED_driver.c,796 :: 		}
L_OLED_driver_OLED_WriteChar94:
;OLED_driver.c,797 :: 		}
L_end_OLED_WriteChar:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of OLED_driver_OLED_WriteChar
_OLED_SetTextProperties:
;OLED_driver.c,799 :: 		void OLED_SetTextProperties(oled_text_properties_t *textProperties)
; textProperties start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; textProperties end address is: 0 (R0)
; textProperties start address is: 0 (R0)
;OLED_driver.c,801 :: 		oled_text_properties.font       = textProperties->font;
LDR	R1, [R0, #0]
MOVW	R4, #lo_addr(OLED_driver_oled_text_properties+0)
MOVT	R4, #hi_addr(OLED_driver_oled_text_properties+0)
STR	R1, [R4, #0]
;OLED_driver.c,802 :: 		oled_text_properties.fontColor  = textProperties->fontColor;
ADDS	R1, R0, #4
LDRH	R1, [R1, #0]
MOVW	R3, #lo_addr(OLED_driver_oled_text_properties+4)
MOVT	R3, #hi_addr(OLED_driver_oled_text_properties+4)
STRH	R1, [R3, #0]
;OLED_driver.c,803 :: 		oled_text_properties.alignParam = textProperties->alignParam;
ADDS	R1, R0, #6
LDRB	R2, [R1, #0]
MOVW	R1, #lo_addr(OLED_driver_oled_text_properties+6)
MOVT	R1, #hi_addr(OLED_driver_oled_text_properties+6)
STRB	R2, [R1, #0]
;OLED_driver.c,804 :: 		oled_text_properties.background = textProperties->background;
ADDW	R1, R0, #8
; textProperties end address is: 0 (R0)
LDR	R2, [R1, #0]
MOVW	R1, #lo_addr(OLED_driver_oled_text_properties+8)
MOVT	R1, #hi_addr(OLED_driver_oled_text_properties+8)
STR	R2, [R1, #0]
;OLED_driver.c,806 :: 		OLED_SetFont( oled_text_properties.font, oled_text_properties.fontColor, 0 );
MOV	R1, R3
LDRH	R2, [R1, #0]
MOV	R1, R4
LDR	R1, [R1, #0]
MOV	R0, R1
UXTH	R1, R2
MOVS	R2, #0
BL	_OLED_SetFont+0
;OLED_driver.c,807 :: 		}
L_end_OLED_SetTextProperties:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_SetTextProperties
