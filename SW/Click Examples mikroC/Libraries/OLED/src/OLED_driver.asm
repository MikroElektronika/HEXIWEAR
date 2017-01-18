_OLED_PowerOn:
;OLED_driver.c,79 :: 		void OLED_PowerOn(void)
;OLED_driver.c,81 :: 		OLED_Pwr_bit = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,82 :: 		}
L_end_OLED_PowerOn:
BX	LR
; end of _OLED_PowerOn
_OLED_PowerOff:
;OLED_driver.c,88 :: 		void OLED_PowerOff(void)
;OLED_driver.c,90 :: 		OLED_Pwr_bit = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,91 :: 		}
L_end_OLED_PowerOff:
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
;OLED_driver.c,119 :: 		SPI_Write((uint8_t)cmd);
UXTB	R0, R0
; cmd end address is: 0 (R0)
BL	_SPI_Write+0
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
;OLED_driver.c,141 :: 		MM_Init();
BL	_MM_Init+0
;OLED_driver.c,143 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_13);
MOV	R1, #8192
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,144 :: 		GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_15);
MOV	R1, #32768
MOVW	R0, #lo_addr(PTD_PDOR+0)
MOVT	R0, #hi_addr(PTD_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,145 :: 		GPIO_Digital_Output(&PTE_PDOR, _GPIO_PINMASK_6);
MOV	R1, #64
MOVW	R0, #lo_addr(PTE_PDOR+0)
MOVT	R0, #hi_addr(PTE_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,146 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_20);
MOV	R1, #1048576
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;OLED_driver.c,149 :: 		_SPI_CFG_CLK_IDLE_HIGH | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI2_PB21_23_22);
MOVW	R2, #lo_addr(__GPIO_Module_SPI2_PB21_23_22+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI2_PB21_23_22+0)
MOVW	R1, #7
MOVT	R1, #33792
;OLED_driver.c,148 :: 		SPI2_Init_Advanced(15000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
MOVW	R0, #57792
MOVT	R0, #228
;OLED_driver.c,149 :: 		_SPI_CFG_CLK_IDLE_HIGH | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI2_PB21_23_22);
BL	_SPI2_Init_Advanced+0
;OLED_driver.c,154 :: 		OLED_PowerOff();
BL	_OLED_PowerOff+0
;OLED_driver.c,155 :: 		Delay_1ms();
BL	_Delay_1ms+0
;OLED_driver.c,156 :: 		OLED_RST_bit = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTE_PDOR+0)
MOVT	R0, #hi_addr(PTE_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,157 :: 		Delay_1ms();
BL	_Delay_1ms+0
;OLED_driver.c,158 :: 		OLED_RST_bit = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTE_PDOR+0)
MOVT	R0, #hi_addr(PTE_PDOR+0)
STR	R1, [R0, #0]
;OLED_driver.c,159 :: 		Delay_1ms();
BL	_Delay_1ms+0
;OLED_driver.c,160 :: 		OLED_PowerOn();
BL	_OLED_PowerOn+0
;OLED_driver.c,162 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #253
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init2
;OLED_driver.c,164 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,165 :: 		}
L_OLED_Init2:
;OLED_driver.c,166 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_UNLOCK, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #18
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init3
;OLED_driver.c,168 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,169 :: 		}
L_OLED_Init3:
;OLED_driver.c,171 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_CMD_LOCK, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #253
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init4
;OLED_driver.c,173 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,174 :: 		}
L_OLED_Init4:
;OLED_driver.c,175 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_ACC_TO_CMD_YES, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #177
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init5
;OLED_driver.c,177 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,178 :: 		}
L_OLED_Init5:
;OLED_driver.c,180 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #174
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init6
;OLED_driver.c,182 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,183 :: 		}
L_OLED_Init6:
;OLED_driver.c,185 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #179
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init7
;OLED_driver.c,187 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,188 :: 		}
L_OLED_Init7:
;OLED_driver.c,189 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xF1, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #241
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init8
;OLED_driver.c,191 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,192 :: 		}
L_OLED_Init8:
;OLED_driver.c,194 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_MUX_RATIO, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #202
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init9
;OLED_driver.c,196 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,197 :: 		}
L_OLED_Init9:
;OLED_driver.c,198 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #95
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init10
;OLED_driver.c,200 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,201 :: 		}
L_OLED_Init10:
;OLED_driver.c,203 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_REMAP, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #160
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init11
;OLED_driver.c,205 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,206 :: 		}
L_OLED_Init11:
;OLED_driver.c,207 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_REMAP_SETTINGS, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #96
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init12
;OLED_driver.c,209 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,210 :: 		}
L_OLED_Init12:
;OLED_driver.c,212 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #21
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init13
;OLED_driver.c,214 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,215 :: 		}
L_OLED_Init13:
;OLED_driver.c,216 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #0
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init14
;OLED_driver.c,218 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,219 :: 		}
L_OLED_Init14:
;OLED_driver.c,220 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #95
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init15
;OLED_driver.c,222 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,223 :: 		}
L_OLED_Init15:
;OLED_driver.c,225 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #117
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init16
;OLED_driver.c,227 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,228 :: 		}
L_OLED_Init16:
;OLED_driver.c,229 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x00, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #0
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init17
;OLED_driver.c,231 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,232 :: 		}
L_OLED_Init17:
;OLED_driver.c,233 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x5F, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #95
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init18
;OLED_driver.c,235 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,236 :: 		}
L_OLED_Init18:
;OLED_driver.c,238 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_STARTLINE, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #161
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init19
;OLED_driver.c,240 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,241 :: 		}
L_OLED_Init19:
;OLED_driver.c,242 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x80, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #128
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init20
;OLED_driver.c,244 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,245 :: 		}
L_OLED_Init20:
;OLED_driver.c,247 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYOFFSET, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #162
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init21
;OLED_driver.c,249 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,250 :: 		}
L_OLED_Init21:
;OLED_driver.c,251 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x60, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #96
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init22
;OLED_driver.c,253 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,254 :: 		}
L_OLED_Init22:
;OLED_driver.c,256 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #177
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init23
;OLED_driver.c,258 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,259 :: 		}
L_OLED_Init23:
;OLED_driver.c,260 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x32, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #50
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init24
;OLED_driver.c,262 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,263 :: 		}
L_OLED_Init24:
;OLED_driver.c,265 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_VCOMH, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #190
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init25
;OLED_driver.c,267 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,268 :: 		}
L_OLED_Init25:
;OLED_driver.c,269 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x05, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #5
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init26
;OLED_driver.c,271 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,272 :: 		}
L_OLED_Init26:
;OLED_driver.c,274 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_NORMALDISPLAY, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #166
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init27
;OLED_driver.c,276 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,277 :: 		}
L_OLED_Init27:
;OLED_driver.c,279 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_CONTRASTABC, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #193
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init28
;OLED_driver.c,281 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,282 :: 		}
L_OLED_Init28:
;OLED_driver.c,283 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #138
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init29
;OLED_driver.c,285 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,286 :: 		}
L_OLED_Init29:
;OLED_driver.c,287 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x51, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #81
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init30
;OLED_driver.c,289 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,290 :: 		}
L_OLED_Init30:
;OLED_driver.c,291 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x8A, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #138
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init31
;OLED_driver.c,293 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,294 :: 		}
L_OLED_Init31:
;OLED_driver.c,296 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_CONTRASTMASTER, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #199
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init32
;OLED_driver.c,298 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,299 :: 		}
L_OLED_Init32:
;OLED_driver.c,300 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xCF, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #207
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init33
;OLED_driver.c,302 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,303 :: 		}
L_OLED_Init33:
;OLED_driver.c,305 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SETVSL, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #180
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init34
;OLED_driver.c,307 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,308 :: 		}
L_OLED_Init34:
;OLED_driver.c,309 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xA0, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #160
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init35
;OLED_driver.c,311 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,312 :: 		}
L_OLED_Init35:
;OLED_driver.c,313 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0xB5, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #181
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init36
;OLED_driver.c,315 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,316 :: 		}
L_OLED_Init36:
;OLED_driver.c,317 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x55, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #85
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init37
;OLED_driver.c,319 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,320 :: 		}
L_OLED_Init37:
;OLED_driver.c,322 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_PRECHARGE2, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #182
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init38
;OLED_driver.c,324 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,325 :: 		}
L_OLED_Init38:
;OLED_driver.c,326 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( 0x01, OTHER_BYTE ) )
MOVS	R1, #0
MOVS	R0, #1
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init39
;OLED_driver.c,328 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,329 :: 		}
L_OLED_Init39:
;OLED_driver.c,331 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #175
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_Init40
;OLED_driver.c,333 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_Init
;OLED_driver.c,334 :: 		}
L_OLED_Init40:
;OLED_driver.c,336 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,337 :: 		}
L_end_OLED_Init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_Init
_OLED_SendData:
;OLED_driver.c,350 :: 		)
SUB	SP, SP, #16
STR	LR, [SP, #0]
STR	R0, [SP, #8]
STR	R1, [SP, #12]
;OLED_driver.c,355 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #92
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_SendData41
;OLED_driver.c,357 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_SendData
;OLED_driver.c,358 :: 		}
L_OLED_SendData41:
;OLED_driver.c,361 :: 		OLED_DC_bit = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTD_PDOR+0)
MOVT	R2, #hi_addr(PTD_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,362 :: 		OLED_CS_bit = 0;
MOVS	R3, #0
SXTB	R3, R3
MOVW	R2, #lo_addr(PTB_PDOR+0)
MOVT	R2, #hi_addr(PTB_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,364 :: 		bufPtr = dataToSend;
; bufPtr start address is: 0 (R0)
LDR	R0, [SP, #8]
; bufPtr end address is: 0 (R0)
;OLED_driver.c,366 :: 		while(dataSize--)
L_OLED_SendData42:
; bufPtr start address is: 0 (R0)
LDR	R3, [SP, #12]
LDR	R2, [SP, #12]
SUBS	R2, R2, #1
STR	R2, [SP, #12]
CMP	R3, #0
IT	EQ
BEQ	L_OLED_SendData43
;OLED_driver.c,368 :: 		SPI_Write(*(bufPtr++));
LDRB	R2, [R0, #0]
STR	R0, [SP, #4]
UXTH	R0, R2
BL	_SPI_Write+0
LDR	R0, [SP, #4]
ADDS	R2, R0, #1
; bufPtr end address is: 0 (R0)
; bufPtr start address is: 4 (R1)
MOV	R1, R2
;OLED_driver.c,369 :: 		}
MOV	R0, R1
; bufPtr end address is: 4 (R1)
IT	AL
BAL	L_OLED_SendData42
L_OLED_SendData43:
;OLED_driver.c,371 :: 		OLED_CS_bit = 1;
MOVS	R3, #1
SXTB	R3, R3
MOVW	R2, #lo_addr(PTB_PDOR+0)
MOVT	R2, #hi_addr(PTB_PDOR+0)
STR	R3, [R2, #0]
;OLED_driver.c,372 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,373 :: 		}
L_end_OLED_SendData:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _OLED_SendData
_OLED_DrawBox:
;OLED_driver.c,394 :: 		)
; xCrd start address is: 0 (R0)
SUB	SP, SP, #28
STR	LR, [SP, #0]
STRH	R1, [SP, #16]
STRH	R2, [SP, #20]
STRH	R3, [SP, #24]
; xCrd end address is: 0 (R0)
; xCrd start address is: 0 (R0)
LDRH	R4, [SP, #28]
STRH	R4, [SP, #28]
;OLED_driver.c,396 :: 		oled_status_t status = OLED_STATUS_SUCCESS;
;OLED_driver.c,399 :: 		boxSize = width*height;
LDRH	R5, [SP, #24]
LDRH	R4, [SP, #20]
MULS	R4, R5, R4
UXTH	R4, R4
STR	R4, [SP, #12]
;OLED_driver.c,402 :: 		if (AreCoordsNotValid(xCrd, yCrd, width, height))
LDRH	R4, [SP, #20]
ADDS	R4, R0, R4
UXTH	R4, R4
SUBS	R4, R4, #1
UXTH	R4, R4
CMP	R4, #96
IT	HI
BHI	L_OLED_DrawBox45
CMP	R0, #0
IT	CC
BCC	L_OLED_DrawBox45
LDRH	R5, [SP, #24]
LDRH	R4, [SP, #16]
ADDS	R4, R4, R5
UXTH	R4, R4
SUBS	R4, R4, #1
UXTH	R4, R4
CMP	R4, #96
IT	HI
BHI	L_OLED_DrawBox45
LDRH	R4, [SP, #16]
CMP	R4, #0
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
; xCrd end address is: 0 (R0)
;OLED_driver.c,404 :: 		status = OLED_STATUS_INIT_ERROR;
; status start address is: 0 (R0)
MOVS	R0, #3
;OLED_driver.c,405 :: 		}
; status end address is: 0 (R0)
IT	AL
BAL	L_OLED_DrawBox47
L_OLED_DrawBox46:
;OLED_driver.c,418 :: 		OLED_AdjustColumnOffset(xCrd);
; xCrd start address is: 0 (R0)
ADDW	R4, R0, #16
; xCrd end address is: 0 (R0)
; xCrd start address is: 4 (R1)
UXTH	R1, R4
;OLED_driver.c,419 :: 		OLED_AdjustRowOffset(yCrd);
LDRH	R4, [SP, #16]
STRH	R4, [SP, #16]
;OLED_driver.c,421 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE ) )
STRH	R1, [SP, #4]
MOVS	R1, #1
MOVS	R0, #21
BL	_OLED_SendCmd+0
LDRH	R1, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox48
; xCrd end address is: 4 (R1)
;OLED_driver.c,423 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,424 :: 		}
L_OLED_DrawBox48:
;OLED_driver.c,425 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd, OTHER_BYTE ) )
; xCrd start address is: 4 (R1)
STRH	R1, [SP, #4]
UXTH	R0, R1
MOVS	R1, #0
BL	_OLED_SendCmd+0
LDRH	R1, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox49
; xCrd end address is: 4 (R1)
;OLED_driver.c,427 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,428 :: 		}
L_OLED_DrawBox49:
;OLED_driver.c,429 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( xCrd + (width-1), OTHER_BYTE ) )
; xCrd start address is: 4 (R1)
LDRH	R4, [SP, #20]
SUBS	R4, R4, #1
UXTH	R4, R4
ADDS	R4, R1, R4
UXTH	R4, R4
; xCrd end address is: 4 (R1)
MOVS	R1, #0
UXTH	R0, R4
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox50
;OLED_driver.c,431 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,432 :: 		}
L_OLED_DrawBox50:
;OLED_driver.c,434 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #117
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox51
;OLED_driver.c,436 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,437 :: 		}
L_OLED_DrawBox51:
;OLED_driver.c,438 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd, OTHER_BYTE ) )
MOVS	R1, #0
LDRH	R0, [SP, #16]
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox52
;OLED_driver.c,440 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,441 :: 		}
L_OLED_DrawBox52:
;OLED_driver.c,442 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( yCrd + (height-1), OTHER_BYTE ) )
LDRH	R4, [SP, #24]
SUBS	R5, R4, #1
UXTH	R5, R5
LDRH	R4, [SP, #16]
ADDS	R4, R4, R5
UXTH	R4, R4
MOVS	R1, #0
UXTH	R0, R4
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox53
;OLED_driver.c,444 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,445 :: 		}
L_OLED_DrawBox53:
;OLED_driver.c,447 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendCmd( OLED_CMD_WRITERAM, FIRST_BYTE ) )
MOVS	R1, #1
MOVS	R0, #92
BL	_OLED_SendCmd+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawBox54
;OLED_driver.c,449 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawBox
;OLED_driver.c,450 :: 		}
L_OLED_DrawBox54:
;OLED_driver.c,452 :: 		OLED_DC_bit = 1;
MOVS	R5, #1
SXTB	R5, R5
MOVW	R4, #lo_addr(PTD_PDOR+0)
MOVT	R4, #hi_addr(PTD_PDOR+0)
STR	R5, [R4, #0]
;OLED_driver.c,453 :: 		OLED_CS_bit = 0;
MOVS	R5, #0
SXTB	R5, R5
MOVW	R4, #lo_addr(PTB_PDOR+0)
MOVT	R4, #hi_addr(PTB_PDOR+0)
STR	R5, [R4, #0]
;OLED_driver.c,454 :: 		for(cnt = 0; cnt < boxSize; cnt++)
MOVS	R4, #0
STRH	R4, [SP, #8]
L_OLED_DrawBox55:
LDR	R5, [SP, #12]
LDRH	R4, [SP, #8]
CMP	R4, R5
IT	CS
BCS	L_OLED_DrawBox56
;OLED_driver.c,456 :: 		SPI_Write((uint8_t)(color >> 8));
LDRH	R4, [SP, #28]
LSRS	R4, R4, #8
UXTB	R0, R4
BL	_SPI_Write+0
;OLED_driver.c,457 :: 		SPI_Write((uint8_t)color);
LDRB	R0, [SP, #28]
BL	_SPI_Write+0
;OLED_driver.c,454 :: 		for(cnt = 0; cnt < boxSize; cnt++)
LDRH	R4, [SP, #8]
ADDS	R4, R4, #1
STRH	R4, [SP, #8]
;OLED_driver.c,458 :: 		}
IT	AL
BAL	L_OLED_DrawBox55
L_OLED_DrawBox56:
;OLED_driver.c,459 :: 		OLED_CS_bit = 1;
MOVS	R5, #1
SXTB	R5, R5
MOVW	R4, #lo_addr(PTB_PDOR+0)
MOVT	R4, #hi_addr(PTB_PDOR+0)
STR	R5, [R4, #0]
;OLED_driver.c,461 :: 		status = OLED_STATUS_SUCCESS;
; status start address is: 0 (R0)
MOVS	R0, #0
; status end address is: 0 (R0)
;OLED_driver.c,462 :: 		}
L_OLED_DrawBox47:
;OLED_driver.c,464 :: 		return status;
; status start address is: 0 (R0)
; status end address is: 0 (R0)
;OLED_driver.c,465 :: 		}
L_end_OLED_DrawBox:
LDR	LR, [SP, #0]
ADD	SP, SP, #28
BX	LR
; end of _OLED_DrawBox
_OLED_FillScreen:
;OLED_driver.c,476 :: 		oled_status_t OLED_FillScreen( uint16_t color )
; color start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; color end address is: 0 (R0)
; color start address is: 0 (R0)
;OLED_driver.c,478 :: 		return OLED_DrawBox(0, 0, 96, 96, color);;
PUSH	(R0)
MOVS	R3, #96
MOVS	R2, #96
MOVS	R1, #0
MOVS	R0, #0
; color end address is: 0 (R0)
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;OLED_driver.c,479 :: 		}
L_end_OLED_FillScreen:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _OLED_FillScreen
_OLED_DrawPixel:
;OLED_driver.c,497 :: 		)
; color start address is: 8 (R2)
; yCrd start address is: 4 (R1)
; xCrd start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; color end address is: 8 (R2)
; yCrd end address is: 4 (R1)
; xCrd end address is: 0 (R0)
; xCrd start address is: 0 (R0)
; yCrd start address is: 4 (R1)
; color start address is: 8 (R2)
;OLED_driver.c,500 :: 		if AreCoordsNotValid( xCrd, yCrd, 1, 1 )
ADDS	R3, R0, #1
SXTH	R3, R3
SUBS	R3, R3, #1
SXTH	R3, R3
CMP	R3, #96
IT	GT
BGT	L_OLED_DrawPixel59
CMP	R0, #0
IT	LT
BLT	L_OLED_DrawPixel59
ADDS	R3, R1, #1
SXTH	R3, R3
SUBS	R3, R3, #1
SXTH	R3, R3
CMP	R3, #96
IT	GT
BGT	L_OLED_DrawPixel59
CMP	R1, #0
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
; xCrd end address is: 0 (R0)
; yCrd end address is: 4 (R1)
; color end address is: 8 (R2)
;OLED_driver.c,502 :: 		return OLED_STATUS_INIT_ERROR;
MOVS	R0, #3
IT	AL
BAL	L_end_OLED_DrawPixel
;OLED_driver.c,503 :: 		}
L_OLED_DrawPixel60:
;OLED_driver.c,507 :: 		uint16_t dot = color;
; color start address is: 8 (R2)
; yCrd start address is: 4 (R1)
; xCrd start address is: 0 (R0)
STRH	R2, [SP, #4]
; color end address is: 8 (R2)
;OLED_driver.c,510 :: 		SetBorders( xCrd, yCrd, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT);
MOVS	R3, #96
MOVS	R2, #96
UXTB	R1, R1
; yCrd end address is: 4 (R1)
UXTB	R0, R0
; xCrd end address is: 0 (R0)
BL	OLED_driver_SetBorders+0
;OLED_driver.c,512 :: 		OLED_SwapMe(dot);
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
;OLED_driver.c,515 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendData( (uint8_t*)&dot, 2 ) )
ADD	R3, SP, #4
MOVS	R1, #2
MOV	R0, R3
BL	_OLED_SendData+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawPixel62
;OLED_driver.c,517 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawPixel
;OLED_driver.c,518 :: 		}
L_OLED_DrawPixel62:
;OLED_driver.c,519 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,521 :: 		}
L_end_OLED_DrawPixel:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _OLED_DrawPixel
OLED_driver_SetBorders:
;OLED_driver.c,538 :: 		)
SUB	SP, SP, #24
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
STRB	R1, [SP, #12]
STRB	R2, [SP, #16]
STRB	R3, [SP, #20]
;OLED_driver.c,543 :: 		OLED_AdjustColumnOffset(xCrd);
LDRB	R4, [SP, #8]
ADDS	R4, #16
STRB	R4, [SP, #8]
;OLED_driver.c,544 :: 		OLED_AdjustRowOffset(yCrd);
LDRB	R4, [SP, #12]
STRB	R4, [SP, #12]
;OLED_driver.c,546 :: 		while (1)
L_OLED_driver_SetBorders63:
;OLED_driver.c,548 :: 		oledStatus = OLED_STATUS_SUCCESS;
MOVS	R4, #0
STRB	R4, [SP, #4]
;OLED_driver.c,550 :: 		oledStatus |= OLED_SendCmd( OLED_CMD_SET_COLUMN, FIRST_BYTE );
MOVS	R1, #1
MOVS	R0, #21
BL	_OLED_SendCmd+0
LDRB	R4, [SP, #4]
ORRS	R4, R0
STRB	R4, [SP, #4]
;OLED_driver.c,551 :: 		oledStatus |= OLED_SendCmd( xCrd, OTHER_BYTE );
MOVS	R1, #0
LDRB	R0, [SP, #8]
BL	_OLED_SendCmd+0
LDRB	R4, [SP, #4]
ORRS	R4, R0
STRB	R4, [SP, #4]
;OLED_driver.c,552 :: 		oledStatus |= OLED_SendCmd( xCrd + (width-1), OTHER_BYTE );
LDRB	R4, [SP, #16]
SUBS	R5, R4, #1
SXTH	R5, R5
LDRB	R4, [SP, #8]
ADDS	R4, R4, R5
SXTH	R4, R4
MOVS	R1, #0
SXTH	R0, R4
BL	_OLED_SendCmd+0
LDRB	R4, [SP, #4]
ORRS	R4, R0
STRB	R4, [SP, #4]
;OLED_driver.c,553 :: 		oledStatus |= OLED_SendCmd( OLED_CMD_SET_ROW, FIRST_BYTE );
MOVS	R1, #1
MOVS	R0, #117
BL	_OLED_SendCmd+0
LDRB	R4, [SP, #4]
ORRS	R4, R0
STRB	R4, [SP, #4]
;OLED_driver.c,554 :: 		oledStatus |= OLED_SendCmd( yCrd, OTHER_BYTE );
MOVS	R1, #0
LDRB	R0, [SP, #12]
BL	_OLED_SendCmd+0
LDRB	R4, [SP, #4]
ORRS	R4, R0
STRB	R4, [SP, #4]
;OLED_driver.c,555 :: 		oledStatus |= OLED_SendCmd( yCrd + (height-1), OTHER_BYTE );
LDRB	R4, [SP, #20]
SUBS	R5, R4, #1
SXTH	R5, R5
LDRB	R4, [SP, #12]
ADDS	R4, R4, R5
SXTH	R4, R4
MOVS	R1, #0
SXTH	R0, R4
BL	_OLED_SendCmd+0
LDRB	R4, [SP, #4]
ORRS	R4, R0
UXTB	R4, R4
;OLED_driver.c,557 :: 		if ( OLED_STATUS_SUCCESS == oledStatus)
CMP	R4, #0
IT	NE
BNE	L_OLED_driver_SetBorders65
;OLED_driver.c,559 :: 		break;
IT	AL
BAL	L_OLED_driver_SetBorders64
;OLED_driver.c,560 :: 		}
L_OLED_driver_SetBorders65:
;OLED_driver.c,561 :: 		}
IT	AL
BAL	L_OLED_driver_SetBorders63
L_OLED_driver_SetBorders64:
;OLED_driver.c,562 :: 		}
L_end_SetBorders:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of OLED_driver_SetBorders
OLED_driver_OLED_Swap:
;OLED_driver.c,574 :: 		)
; imgSize start address is: 8 (R2)
; imgSrc start address is: 4 (R1)
; imgDst start address is: 0 (R0)
UXTH	R3, R2
MOV	R2, R1
; imgSize end address is: 8 (R2)
; imgSrc end address is: 4 (R1)
; imgDst end address is: 0 (R0)
; imgDst start address is: 0 (R0)
; imgSrc start address is: 8 (R2)
; imgSize start address is: 12 (R3)
;OLED_driver.c,577 :: 		for (var = 0; var < imgSize; var++)
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
;OLED_driver.c,579 :: 		*imgDst = *imgSrc << 8;
LDRB	R3, [R4, #0]
LSLS	R3, R3, #8
STRH	R3, [R2, #0]
;OLED_driver.c,580 :: 		imgSrc++;
ADDS	R3, R4, #1
; imgSrc end address is: 16 (R4)
; imgSrc start address is: 20 (R5)
MOV	R5, R3
;OLED_driver.c,581 :: 		*imgDst |= *imgSrc;
LDRB	R4, [R3, #0]
LDRH	R3, [R2, #0]
ORRS	R3, R4
STRH	R3, [R2, #0]
;OLED_driver.c,582 :: 		imgDst++;
ADDS	R2, R2, #2
;OLED_driver.c,583 :: 		imgSrc++;
ADDS	R3, R5, #1
; imgSrc end address is: 20 (R5)
; imgSrc start address is: 16 (R4)
MOV	R4, R3
;OLED_driver.c,577 :: 		for (var = 0; var < imgSize; var++)
ADDS	R1, R1, #1
;OLED_driver.c,584 :: 		}
; imgSize end address is: 0 (R0)
; imgDst end address is: 8 (R2)
; imgSrc end address is: 16 (R4)
; var end address is: 4 (R1)
IT	AL
BAL	L_OLED_driver_OLED_Swap66
L_OLED_driver_OLED_Swap67:
;OLED_driver.c,585 :: 		}
L_end_OLED_Swap:
BX	LR
; end of OLED_driver_OLED_Swap
_OLED_GetImageDimensions:
;OLED_driver.c,591 :: 		void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image)
; image start address is: 8 (R2)
; height start address is: 4 (R1)
; width start address is: 0 (R0)
; image end address is: 8 (R2)
; height end address is: 4 (R1)
; width end address is: 0 (R0)
; width start address is: 0 (R0)
; height start address is: 4 (R1)
; image start address is: 8 (R2)
;OLED_driver.c,593 :: 		*height = image[2] + (image[3] << 8);
ADDS	R3, R2, #2
LDRB	R4, [R3, #0]
ADDS	R3, R2, #3
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R3, R4, R3
STRB	R3, [R1, #0]
; height end address is: 4 (R1)
;OLED_driver.c,594 :: 		*width  = image[4] + (image[5] << 8);
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
;OLED_driver.c,595 :: 		}
L_end_OLED_GetImageDimensions:
BX	LR
; end of _OLED_GetImageDimensions
_OLED_DrawImage:
;OLED_driver.c,601 :: 		oled_status_t OLED_DrawImage (const uint8_t* image, uint8_t xCrd, uint8_t yCrd)
; yCrd start address is: 8 (R2)
; xCrd start address is: 4 (R1)
; image start address is: 0 (R0)
SUB	SP, SP, #16
STR	LR, [SP, #0]
; yCrd end address is: 8 (R2)
; xCrd end address is: 4 (R1)
; image end address is: 0 (R0)
; image start address is: 0 (R0)
; xCrd start address is: 4 (R1)
; yCrd start address is: 8 (R2)
;OLED_driver.c,603 :: 		oled_status_t status = OLED_STATUS_SUCCESS;
;OLED_driver.c,607 :: 		ptr = image;
; ptr start address is: 12 (R3)
MOV	R3, R0
;OLED_driver.c,609 :: 		ptr += 2;
ADDS	R4, R3, #2
; ptr end address is: 12 (R3)
;OLED_driver.c,610 :: 		height = *ptr;
LDRB	R5, [R4, #0]
; height start address is: 20 (R5)
UXTB	R5, R5
;OLED_driver.c,611 :: 		ptr++;
ADDS	R4, R4, #1
;OLED_driver.c,612 :: 		height += (*ptr) << 8;
LDRB	R3, [R4, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R5, R5, R3
UXTH	R5, R5
;OLED_driver.c,614 :: 		ptr++;
ADDS	R4, R4, #1
;OLED_driver.c,615 :: 		width = *ptr;
LDRB	R6, [R4, #0]
; width start address is: 24 (R6)
UXTB	R6, R6
;OLED_driver.c,616 :: 		ptr++;
ADDS	R3, R4, #1
;OLED_driver.c,617 :: 		width += (*ptr)<<8;
LDRB	R3, [R3, #0]
LSLS	R3, R3, #8
UXTH	R3, R3
ADDS	R3, R6, R3
UXTH	R3, R3
UXTH	R6, R3
;OLED_driver.c,620 :: 		if AreCoordsNotValid( xCrd, yCrd, width, height )
ADDS	R3, R1, R3
UXTH	R3, R3
SUBS	R3, R3, #1
UXTH	R3, R3
CMP	R3, #96
IT	HI
BHI	L_OLED_DrawImage70
CMP	R1, #0
IT	CC
BCC	L_OLED_DrawImage70
ADDS	R3, R2, R5
UXTH	R3, R3
SUBS	R3, R3, #1
UXTH	R3, R3
CMP	R3, #96
IT	HI
BHI	L_OLED_DrawImage70
CMP	R2, #0
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
;OLED_driver.c,623 :: 		}
IT	AL
BAL	L_OLED_DrawImage72
L_OLED_DrawImage71:
;OLED_driver.c,627 :: 		OLED_Swap( screenBuf, (const uint8_t*)( image ) + 6 , width * height );
; image start address is: 0 (R0)
MUL	R4, R6, R5
ADDS	R3, R0, #6
; image end address is: 0 (R0)
STRH	R5, [SP, #4]
STRB	R2, [SP, #8]
STRB	R1, [SP, #12]
UXTH	R2, R4
MOV	R1, R3
MOVW	R0, #lo_addr(OLED_driver_screenBuf+0)
MOVT	R0, #hi_addr(OLED_driver_screenBuf+0)
BL	OLED_driver_OLED_Swap+0
LDRB	R1, [SP, #12]
LDRB	R2, [SP, #8]
LDRH	R5, [SP, #4]
;OLED_driver.c,631 :: 		}
L_OLED_DrawImage72:
;OLED_driver.c,634 :: 		SetBorders( xCrd, yCrd, width, height );
STRH	R6, [SP, #4]
STRH	R5, [SP, #6]
UXTB	R3, R5
UXTB	R0, R1
UXTB	R1, R2
; yCrd end address is: 8 (R2)
UXTB	R2, R6
; xCrd end address is: 4 (R1)
BL	OLED_driver_SetBorders+0
LDRH	R5, [SP, #6]
LDRH	R6, [SP, #4]
;OLED_driver.c,637 :: 		if ( OLED_STATUS_SUCCESS != OLED_SendData( (const uint8_t*)screenBuf, width * height * OLED_BYTES_PER_PIXEL ) )
MUL	R3, R6, R5
UXTH	R3, R3
; height end address is: 20 (R5)
; width end address is: 24 (R6)
LSLS	R3, R3, #1
UXTH	R3, R3
UXTH	R1, R3
MOVW	R0, #lo_addr(OLED_driver_screenBuf+0)
MOVT	R0, #hi_addr(OLED_driver_screenBuf+0)
BL	_OLED_SendData+0
CMP	R0, #0
IT	EQ
BEQ	L_OLED_DrawImage73
;OLED_driver.c,639 :: 		return OLED_STATUS_PROTOCOL_ERROR;
MOVS	R0, #2
IT	AL
BAL	L_end_OLED_DrawImage
;OLED_driver.c,640 :: 		}
L_OLED_DrawImage73:
;OLED_driver.c,642 :: 		return OLED_STATUS_SUCCESS;
MOVS	R0, #0
;OLED_driver.c,643 :: 		}
L_end_OLED_DrawImage:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of _OLED_DrawImage
_OLED_SetFont:
;OLED_driver.c,649 :: 		void OLED_SetFont(const uint8_t *activeFont, uint16_t font_color, uint8_t font_orientation)
; font_orientation start address is: 8 (R2)
; font_color start address is: 4 (R1)
; activeFont start address is: 0 (R0)
; font_orientation end address is: 8 (R2)
; font_color end address is: 4 (R1)
; activeFont end address is: 0 (R0)
; activeFont start address is: 0 (R0)
; font_color start address is: 4 (R1)
; font_orientation start address is: 8 (R2)
;OLED_driver.c,651 :: 		_font = activeFont;
MOVW	R3, #lo_addr(OLED_driver__font+0)
MOVT	R3, #hi_addr(OLED_driver__font+0)
STR	R0, [R3, #0]
;OLED_driver.c,652 :: 		_fontFirstChar = activeFont[2] + (activeFont[3] << 8);
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
;OLED_driver.c,653 :: 		_fontLastChar = activeFont[4] + (activeFont[5] << 8);
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
;OLED_driver.c,654 :: 		_fontHeight = activeFont[6];
ADDS	R3, R0, #6
; activeFont end address is: 0 (R0)
LDRB	R4, [R3, #0]
MOVW	R3, #lo_addr(OLED_driver__fontHeight+0)
MOVT	R3, #hi_addr(OLED_driver__fontHeight+0)
STRH	R4, [R3, #0]
;OLED_driver.c,656 :: 		FontColor = font_color;
MOVW	R3, #lo_addr(OLED_driver_FontColor+0)
MOVT	R3, #hi_addr(OLED_driver_FontColor+0)
STRH	R1, [R3, #0]
; font_color end address is: 4 (R1)
;OLED_driver.c,657 :: 		FontOrientation = font_orientation;
MOVW	R3, #lo_addr(OLED_driver_FontOrientation+0)
MOVT	R3, #hi_addr(OLED_driver_FontOrientation+0)
STRB	R2, [R3, #0]
; font_orientation end address is: 8 (R2)
;OLED_driver.c,658 :: 		FontInitialized = 1;
MOVS	R4, #1
MOVW	R3, #lo_addr(OLED_driver_FontInitialized+0)
MOVT	R3, #hi_addr(OLED_driver_FontInitialized+0)
STRB	R4, [R3, #0]
;OLED_driver.c,659 :: 		ExternalFontSet = 0;
MOVS	R4, #0
MOVW	R3, #lo_addr(_ExternalFontSet+0)
MOVT	R3, #hi_addr(_ExternalFontSet+0)
STRB	R4, [R3, #0]
;OLED_driver.c,660 :: 		}
L_end_OLED_SetFont:
BX	LR
; end of _OLED_SetFont
_OLED_WriteText:
;OLED_driver.c,667 :: 		void OLED_WriteText(uint8_t *text, uint16_t x, uint16_t y) {
; y start address is: 8 (R2)
; x start address is: 4 (R1)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STR	R0, [SP, #8]
; y end address is: 8 (R2)
; x end address is: 4 (R1)
; x start address is: 4 (R1)
; y start address is: 8 (R2)
;OLED_driver.c,670 :: 		if (x >= OLED_SCREEN_WIDTH)
CMP	R1, #96
IT	CC
BCC	L_OLED_WriteText74
; x end address is: 4 (R1)
; y end address is: 8 (R2)
;OLED_driver.c,671 :: 		return;
IT	AL
BAL	L_end_OLED_WriteText
L_OLED_WriteText74:
;OLED_driver.c,672 :: 		if (y >= OLED_SCREEN_HEIGHT)
; y start address is: 8 (R2)
; x start address is: 4 (R1)
CMP	R2, #96
IT	CC
BCC	L_OLED_WriteText75
; x end address is: 4 (R1)
; y end address is: 8 (R2)
;OLED_driver.c,673 :: 		return;
IT	AL
BAL	L_end_OLED_WriteText
L_OLED_WriteText75:
;OLED_driver.c,675 :: 		i = 0;
; y start address is: 8 (R2)
; x start address is: 4 (R1)
MOVS	R3, #0
STRH	R3, [SP, #4]
;OLED_driver.c,676 :: 		OLED_MoveCursor(x, y);
UXTH	R0, R1
; y end address is: 8 (R2)
UXTH	R1, R2
; x end address is: 4 (R1)
BL	OLED_driver_OLED_MoveCursor+0
;OLED_driver.c,677 :: 		while (text[i])
L_OLED_WriteText76:
LDRH	R4, [SP, #4]
LDR	R3, [SP, #8]
ADDS	R3, R3, R4
LDRB	R3, [R3, #0]
CMP	R3, #0
IT	EQ
BEQ	L_OLED_WriteText77
;OLED_driver.c,678 :: 		OLED_WriteChar(text[i++]);
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
;OLED_driver.c,679 :: 		}
L_end_OLED_WriteText:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _OLED_WriteText
OLED_driver_OLED_MoveCursor:
;OLED_driver.c,685 :: 		static void OLED_MoveCursor(uint16_t _x, uint16_t _y)
; _y start address is: 4 (R1)
; _x start address is: 0 (R0)
; _y end address is: 4 (R1)
; _x end address is: 0 (R0)
; _x start address is: 0 (R0)
; _y start address is: 4 (R1)
;OLED_driver.c,687 :: 		x_cord = _x;
MOVW	R2, #lo_addr(OLED_driver_x_cord+0)
MOVT	R2, #hi_addr(OLED_driver_x_cord+0)
STRH	R0, [R2, #0]
; _x end address is: 0 (R0)
;OLED_driver.c,688 :: 		y_cord = _y;
MOVW	R2, #lo_addr(OLED_driver_y_cord+0)
MOVT	R2, #hi_addr(OLED_driver_y_cord+0)
STRH	R1, [R2, #0]
; _y end address is: 4 (R1)
;OLED_driver.c,689 :: 		}
L_end_OLED_MoveCursor:
BX	LR
; end of OLED_driver_OLED_MoveCursor
OLED_driver_OLED_WriteChar:
;OLED_driver.c,695 :: 		static void OLED_WriteChar(uint16_t ch)
; ch start address is: 0 (R0)
SUB	SP, SP, #24
STR	LR, [SP, #0]
UXTH	R7, R0
; ch end address is: 0 (R0)
; ch start address is: 28 (R7)
;OLED_driver.c,697 :: 		uint8_t chWidth = 0;
;OLED_driver.c,699 :: 		uint16_t x = 0, y;
; x start address is: 20 (R5)
MOVW	R5, #0
;OLED_driver.c,700 :: 		uint8_t temp = 0, mask;
; temp start address is: 24 (R6)
MOVS	R6, #0
;OLED_driver.c,706 :: 		if(FontInitialized == 0)
MOVW	R1, #lo_addr(OLED_driver_FontInitialized+0)
MOVT	R1, #hi_addr(OLED_driver_FontInitialized+0)
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar78
;OLED_driver.c,708 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, FO_HORIZONTAL); //default font
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #0
BL	_OLED_SetFont+0
;OLED_driver.c,709 :: 		FontInitialized = 1;
MOVS	R2, #1
MOVW	R1, #lo_addr(OLED_driver_FontInitialized+0)
MOVT	R1, #hi_addr(OLED_driver_FontInitialized+0)
STRB	R2, [R1, #0]
;OLED_driver.c,710 :: 		}
L_OLED_driver_OLED_WriteChar78:
;OLED_driver.c,712 :: 		if (ch < _fontFirstChar)
MOVW	R1, #lo_addr(OLED_driver__fontFirstChar+0)
MOVT	R1, #hi_addr(OLED_driver__fontFirstChar+0)
LDRH	R1, [R1, #0]
CMP	R7, R1
IT	CS
BCS	L_OLED_driver_OLED_WriteChar79
; ch end address is: 28 (R7)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
;OLED_driver.c,714 :: 		return;
IT	AL
BAL	L_end_OLED_WriteChar
;OLED_driver.c,715 :: 		}
L_OLED_driver_OLED_WriteChar79:
;OLED_driver.c,716 :: 		if (ch > _fontLastChar)
; x start address is: 20 (R5)
; temp start address is: 24 (R6)
; ch start address is: 28 (R7)
MOVW	R1, #lo_addr(OLED_driver__fontLastChar+0)
MOVT	R1, #hi_addr(OLED_driver__fontLastChar+0)
LDRH	R1, [R1, #0]
CMP	R7, R1
IT	LS
BLS	L_OLED_driver_OLED_WriteChar80
; ch end address is: 28 (R7)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
;OLED_driver.c,718 :: 		return;
IT	AL
BAL	L_end_OLED_WriteChar
;OLED_driver.c,719 :: 		}
L_OLED_driver_OLED_WriteChar80:
;OLED_driver.c,722 :: 		tmp = (ch - _fontFirstChar) << 2;
; x start address is: 20 (R5)
; temp start address is: 24 (R6)
; ch start address is: 28 (R7)
MOVW	R1, #lo_addr(OLED_driver__fontFirstChar+0)
MOVT	R1, #hi_addr(OLED_driver__fontFirstChar+0)
LDRH	R1, [R1, #0]
SUB	R1, R7, R1
UXTH	R1, R1
; ch end address is: 28 (R7)
LSLS	R2, R1, #2
UXTH	R2, R2
;OLED_driver.c,723 :: 		pChTable = _font + 8 + tmp;
MOVW	R4, #lo_addr(OLED_driver__font+0)
MOVT	R4, #hi_addr(OLED_driver__font+0)
LDR	R1, [R4, #0]
ADDS	R1, #8
ADDS	R3, R1, R2
;OLED_driver.c,724 :: 		chWidth = *pChTable;
LDRB	R0, [R3, #0]
; chWidth start address is: 0 (R0)
;OLED_driver.c,726 :: 		offset = (uint32_t) pChTable[1] + ((uint32_t)pChTable[2] << 8) + ((uint32_t)pChTable[3] << 16);
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
;OLED_driver.c,728 :: 		pChBitMap = _font + offset;
MOV	R1, R4
LDR	R1, [R1, #0]
ADDS	R4, R1, R2
; pChBitMap start address is: 16 (R4)
;OLED_driver.c,730 :: 		if ((FontOrientation == FO_HORIZONTAL) || (FontOrientation == FO_VERTICAL_COLUMN))
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
;OLED_driver.c,732 :: 		y = y_cord;
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
; y start address is: 12 (R3)
LDRH	R3, [R1, #0]
;OLED_driver.c,733 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
; yCnt start address is: 8 (R2)
MOVS	R2, #0
; pChBitMap end address is: 16 (R4)
; chWidth end address is: 0 (R0)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
; y end address is: 12 (R3)
; yCnt end address is: 8 (R2)
MOV	R8, R4
UXTH	R4, R5
L_OLED_driver_OLED_WriteChar84:
; yCnt start address is: 8 (R2)
; y start address is: 12 (R3)
; pChBitMap start address is: 32 (R8)
; chWidth start address is: 0 (R0)
; temp start address is: 24 (R6)
; x start address is: 16 (R4)
MOVW	R1, #lo_addr(OLED_driver__fontHeight+0)
MOVT	R1, #hi_addr(OLED_driver__fontHeight+0)
LDRH	R1, [R1, #0]
CMP	R2, R1
IT	CS
BCS	L_OLED_driver_OLED_WriteChar85
; x end address is: 16 (R4)
;OLED_driver.c,735 :: 		x = x_cord;
MOVW	R1, #lo_addr(OLED_driver_x_cord+0)
MOVT	R1, #hi_addr(OLED_driver_x_cord+0)
; x start address is: 20 (R5)
LDRH	R5, [R1, #0]
;OLED_driver.c,736 :: 		mask = 0;
; mask start address is: 28 (R7)
MOVS	R7, #0
;OLED_driver.c,737 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
; xCnt start address is: 16 (R4)
MOVS	R4, #0
; chWidth end address is: 0 (R0)
; pChBitMap end address is: 32 (R8)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
; mask end address is: 28 (R7)
; xCnt end address is: 16 (R4)
; y end address is: 12 (R3)
; yCnt end address is: 8 (R2)
L_OLED_driver_OLED_WriteChar87:
; xCnt start address is: 16 (R4)
; mask start address is: 28 (R7)
; x start address is: 20 (R5)
; temp start address is: 24 (R6)
; chWidth start address is: 0 (R0)
; pChBitMap start address is: 32 (R8)
; y start address is: 12 (R3)
; yCnt start address is: 8 (R2)
CMP	R4, R0
IT	CS
BCS	L_OLED_driver_OLED_WriteChar88
;OLED_driver.c,739 :: 		if (mask == 0)
CMP	R7, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar106
; temp end address is: 24 (R6)
; mask end address is: 28 (R7)
;OLED_driver.c,741 :: 		temp = *pChBitMap++;
LDRB	R6, [R8, #0]
; temp start address is: 24 (R6)
ADD	R8, R8, #1
;OLED_driver.c,742 :: 		mask = 0x01;
; mask start address is: 28 (R7)
MOVS	R7, #1
; pChBitMap end address is: 32 (R8)
; temp end address is: 24 (R6)
; mask end address is: 28 (R7)
;OLED_driver.c,743 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar90
L_OLED_driver_OLED_WriteChar106:
;OLED_driver.c,739 :: 		if (mask == 0)
;OLED_driver.c,743 :: 		}
L_OLED_driver_OLED_WriteChar90:
;OLED_driver.c,745 :: 		if (temp & mask)
; mask start address is: 28 (R7)
; pChBitMap start address is: 32 (R8)
; temp start address is: 24 (R6)
AND	R1, R6, R7, LSL #0
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L_OLED_driver_OLED_WriteChar91
;OLED_driver.c,747 :: 		OLED_DrawPixel(x, y, FontColor);
MOVW	R1, #lo_addr(OLED_driver_FontColor+0)
MOVT	R1, #hi_addr(OLED_driver_FontColor+0)
LDRH	R1, [R1, #0]
STRB	R6, [SP, #4]
STR	R8, [SP, #8]
STRB	R7, [SP, #12]
STRB	R2, [SP, #13]
STRH	R3, [SP, #14]
STRB	R0, [SP, #16]
STRH	R5, [SP, #18]
STRB	R4, [SP, #20]
UXTH	R2, R1
SXTH	R1, R3
SXTH	R0, R5
BL	_OLED_DrawPixel+0
LDRB	R4, [SP, #20]
LDRH	R5, [SP, #18]
LDRB	R0, [SP, #16]
LDRH	R3, [SP, #14]
LDRB	R2, [SP, #13]
LDRB	R7, [SP, #12]
LDR	R8, [SP, #8]
LDRB	R6, [SP, #4]
;OLED_driver.c,748 :: 		}
L_OLED_driver_OLED_WriteChar91:
;OLED_driver.c,750 :: 		x++;
ADDS	R5, R5, #1
UXTH	R5, R5
;OLED_driver.c,751 :: 		mask <<= 1;
LSLS	R1, R7, #1
UXTB	R7, R1
;OLED_driver.c,737 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
ADDS	R4, R4, #1
UXTB	R4, R4
;OLED_driver.c,752 :: 		}
; mask end address is: 28 (R7)
; xCnt end address is: 16 (R4)
IT	AL
BAL	L_OLED_driver_OLED_WriteChar87
L_OLED_driver_OLED_WriteChar88:
;OLED_driver.c,753 :: 		y++;
ADDS	R3, R3, #1
UXTH	R3, R3
;OLED_driver.c,733 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
ADDS	R2, R2, #1
UXTB	R2, R2
;OLED_driver.c,754 :: 		}
UXTH	R4, R5
; chWidth end address is: 0 (R0)
; pChBitMap end address is: 32 (R8)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
; yCnt end address is: 8 (R2)
IT	AL
BAL	L_OLED_driver_OLED_WriteChar84
L_OLED_driver_OLED_WriteChar85:
;OLED_driver.c,757 :: 		if (FontOrientation == FO_HORIZONTAL)
; x start address is: 16 (R4)
MOVW	R1, #lo_addr(OLED_driver_FontOrientation+0)
MOVT	R1, #hi_addr(OLED_driver_FontOrientation+0)
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar92
; y end address is: 12 (R3)
;OLED_driver.c,759 :: 		x_cord = x + 1;
ADDS	R2, R4, #1
; x end address is: 16 (R4)
MOVW	R1, #lo_addr(OLED_driver_x_cord+0)
MOVT	R1, #hi_addr(OLED_driver_x_cord+0)
STRH	R2, [R1, #0]
;OLED_driver.c,760 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar93
L_OLED_driver_OLED_WriteChar92:
;OLED_driver.c,763 :: 		y_cord = y; // visini nego sirini, nema potrebe da se dodaje jedan pixel kao
; y start address is: 12 (R3)
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
STRH	R3, [R1, #0]
; y end address is: 12 (R3)
;OLED_driver.c,764 :: 		}
L_OLED_driver_OLED_WriteChar93:
;OLED_driver.c,765 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar94
L_OLED_driver_OLED_WriteChar83:
;OLED_driver.c,768 :: 		y = x_cord;
; x start address is: 20 (R5)
; temp start address is: 24 (R6)
; chWidth start address is: 0 (R0)
; pChBitMap start address is: 16 (R4)
MOVW	R1, #lo_addr(OLED_driver_x_cord+0)
MOVT	R1, #hi_addr(OLED_driver_x_cord+0)
; y start address is: 12 (R3)
LDRH	R3, [R1, #0]
;OLED_driver.c,769 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
; yCnt start address is: 8 (R2)
MOVS	R2, #0
; pChBitMap end address is: 16 (R4)
; chWidth end address is: 0 (R0)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
; y end address is: 12 (R3)
; yCnt end address is: 8 (R2)
L_OLED_driver_OLED_WriteChar95:
; yCnt start address is: 8 (R2)
; y start address is: 12 (R3)
; pChBitMap start address is: 16 (R4)
; chWidth start address is: 0 (R0)
; temp start address is: 24 (R6)
; x start address is: 20 (R5)
MOVW	R1, #lo_addr(OLED_driver__fontHeight+0)
MOVT	R1, #hi_addr(OLED_driver__fontHeight+0)
LDRH	R1, [R1, #0]
CMP	R2, R1
IT	CS
BCS	L_OLED_driver_OLED_WriteChar96
; x end address is: 20 (R5)
;OLED_driver.c,771 :: 		x = y_cord;
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
; x start address is: 20 (R5)
LDRH	R5, [R1, #0]
;OLED_driver.c,772 :: 		mask = 0;
; mask start address is: 28 (R7)
MOVS	R7, #0
;OLED_driver.c,773 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
; xCnt start address is: 4 (R1)
MOVS	R1, #0
; pChBitMap end address is: 16 (R4)
; xCnt end address is: 4 (R1)
; chWidth end address is: 0 (R0)
; temp end address is: 24 (R6)
; x end address is: 20 (R5)
; mask end address is: 28 (R7)
; y end address is: 12 (R3)
; yCnt end address is: 8 (R2)
MOV	R8, R4
UXTB	R4, R1
L_OLED_driver_OLED_WriteChar98:
; xCnt start address is: 16 (R4)
; mask start address is: 28 (R7)
; x start address is: 20 (R5)
; temp start address is: 24 (R6)
; chWidth start address is: 0 (R0)
; pChBitMap start address is: 32 (R8)
; y start address is: 12 (R3)
; yCnt start address is: 8 (R2)
CMP	R4, R0
IT	CS
BCS	L_OLED_driver_OLED_WriteChar99
;OLED_driver.c,775 :: 		if (mask == 0)
CMP	R7, #0
IT	NE
BNE	L_OLED_driver_OLED_WriteChar107
; temp end address is: 24 (R6)
; mask end address is: 28 (R7)
;OLED_driver.c,777 :: 		temp = *pChBitMap++;
LDRB	R6, [R8, #0]
; temp start address is: 24 (R6)
ADD	R8, R8, #1
;OLED_driver.c,778 :: 		mask = 0x01;
; mask start address is: 28 (R7)
MOVS	R7, #1
; pChBitMap end address is: 32 (R8)
; temp end address is: 24 (R6)
; mask end address is: 28 (R7)
;OLED_driver.c,779 :: 		}
IT	AL
BAL	L_OLED_driver_OLED_WriteChar101
L_OLED_driver_OLED_WriteChar107:
;OLED_driver.c,775 :: 		if (mask == 0)
;OLED_driver.c,779 :: 		}
L_OLED_driver_OLED_WriteChar101:
;OLED_driver.c,781 :: 		if (temp & mask)
; mask start address is: 28 (R7)
; pChBitMap start address is: 32 (R8)
; temp start address is: 24 (R6)
AND	R1, R6, R7, LSL #0
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L_OLED_driver_OLED_WriteChar102
;OLED_driver.c,783 :: 		OLED_DrawPixel(y, x, FontColor);
MOVW	R1, #lo_addr(OLED_driver_FontColor+0)
MOVT	R1, #hi_addr(OLED_driver_FontColor+0)
LDRH	R1, [R1, #0]
STRB	R6, [SP, #4]
STR	R8, [SP, #8]
STRB	R7, [SP, #12]
STRB	R2, [SP, #13]
STRH	R3, [SP, #14]
STRB	R0, [SP, #16]
STRH	R5, [SP, #18]
STRB	R4, [SP, #20]
UXTH	R2, R1
SXTH	R1, R5
SXTH	R0, R3
BL	_OLED_DrawPixel+0
LDRB	R4, [SP, #20]
LDRH	R5, [SP, #18]
LDRB	R0, [SP, #16]
LDRH	R3, [SP, #14]
LDRB	R2, [SP, #13]
LDRB	R7, [SP, #12]
LDR	R8, [SP, #8]
LDRB	R6, [SP, #4]
;OLED_driver.c,784 :: 		}
L_OLED_driver_OLED_WriteChar102:
;OLED_driver.c,786 :: 		x--;
SUBS	R5, R5, #1
UXTH	R5, R5
;OLED_driver.c,787 :: 		mask <<= 1;
LSLS	R1, R7, #1
UXTB	R7, R1
;OLED_driver.c,773 :: 		for (xCnt = 0; xCnt < chWidth; xCnt++)
ADDS	R4, R4, #1
UXTB	R4, R4
;OLED_driver.c,788 :: 		}
; mask end address is: 28 (R7)
; xCnt end address is: 16 (R4)
IT	AL
BAL	L_OLED_driver_OLED_WriteChar98
L_OLED_driver_OLED_WriteChar99:
;OLED_driver.c,790 :: 		y++;
ADDS	R3, R3, #1
UXTH	R3, R3
;OLED_driver.c,769 :: 		for (yCnt = 0; yCnt < _fontHeight; yCnt++)
ADDS	R2, R2, #1
UXTB	R2, R2
;OLED_driver.c,791 :: 		}
; chWidth end address is: 0 (R0)
; pChBitMap end address is: 32 (R8)
; temp end address is: 24 (R6)
; y end address is: 12 (R3)
; yCnt end address is: 8 (R2)
MOV	R4, R8
IT	AL
BAL	L_OLED_driver_OLED_WriteChar95
L_OLED_driver_OLED_WriteChar96:
;OLED_driver.c,794 :: 		y_cord = x - 1;
SUBS	R2, R5, #1
; x end address is: 20 (R5)
MOVW	R1, #lo_addr(OLED_driver_y_cord+0)
MOVT	R1, #hi_addr(OLED_driver_y_cord+0)
STRH	R2, [R1, #0]
;OLED_driver.c,795 :: 		}
L_OLED_driver_OLED_WriteChar94:
;OLED_driver.c,796 :: 		}
L_end_OLED_WriteChar:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of OLED_driver_OLED_WriteChar
