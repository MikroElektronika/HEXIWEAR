nfc_host_rx:
;nfc.c,86 :: 		uint16_t *p_nbytes_read, uint16_t timeout )
; timeout start address is: 12 (R3)
; p_nbytes_read start address is: 8 (R2)
; rx_buff_size start address is: 4 (R1)
; p_rx_buff start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; timeout end address is: 12 (R3)
; p_nbytes_read end address is: 8 (R2)
; rx_buff_size end address is: 4 (R1)
; p_rx_buff end address is: 0 (R0)
; p_rx_buff start address is: 0 (R0)
; rx_buff_size start address is: 4 (R1)
; p_nbytes_read start address is: 8 (R2)
; timeout start address is: 12 (R3)
;nfc.c,88 :: 		timer_tick = 0;
MOVS	R5, #0
MOVW	R4, #lo_addr(nfc_timer_tick+0)
MOVT	R4, #hi_addr(nfc_timer_tick+0)
STR	R5, [R4, #0]
; p_rx_buff end address is: 0 (R0)
; rx_buff_size end address is: 4 (R1)
; p_nbytes_read end address is: 8 (R2)
; timeout end address is: 12 (R3)
STR	R2, [SP, #4]
STRH	R3, [SP, #8]
MOV	R3, R0
UXTH	R2, R1
LDRH	R0, [SP, #8]
LDR	R1, [SP, #4]
;nfc.c,91 :: 		while( !rx_flag )
L_nfc_host_rx0:
; timeout start address is: 0 (R0)
; timeout start address is: 0 (R0)
; timeout end address is: 0 (R0)
; p_nbytes_read start address is: 4 (R1)
; rx_buff_size start address is: 8 (R2)
; p_rx_buff start address is: 12 (R3)
MOVW	R4, #lo_addr(nfc_rx_flag+0)
MOVT	R4, #hi_addr(nfc_rx_flag+0)
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L_nfc_host_rx1
; timeout end address is: 0 (R0)
;nfc.c,93 :: 		if( timer_tick > ( timeout / 10 ) )
; timeout start address is: 0 (R0)
MOVS	R4, #10
UDIV	R5, R0, R4
UXTH	R5, R5
MOVW	R4, #lo_addr(nfc_timer_tick+0)
MOVT	R4, #hi_addr(nfc_timer_tick+0)
LDR	R4, [R4, #0]
CMP	R4, R5
IT	LS
BLS	L_nfc_host_rx2
; timeout end address is: 0 (R0)
; p_nbytes_read end address is: 4 (R1)
; rx_buff_size end address is: 8 (R2)
; p_rx_buff end address is: 12 (R3)
;nfc.c,94 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_host_rx
L_nfc_host_rx2:
;nfc.c,95 :: 		}
; p_rx_buff start address is: 12 (R3)
; rx_buff_size start address is: 8 (R2)
; p_nbytes_read start address is: 4 (R1)
; timeout start address is: 0 (R0)
; timeout end address is: 0 (R0)
IT	AL
BAL	L_nfc_host_rx0
L_nfc_host_rx1:
;nfc.c,98 :: 		if( nfc_hal_read( p_rx_buff, p_nbytes_read, rx_buff_size ) )
; rx_buff_size end address is: 8 (R2)
; p_nbytes_read end address is: 4 (R1)
MOV	R0, R3
; p_rx_buff end address is: 12 (R3)
BL	_nfc_hal_read+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_host_rx3
;nfc.c,99 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_host_rx
L_nfc_host_rx3:
;nfc.c,101 :: 		rx_flag = false;
MOVS	R5, #0
MOVW	R4, #lo_addr(nfc_rx_flag+0)
MOVT	R4, #hi_addr(nfc_rx_flag+0)
STRB	R5, [R4, #0]
;nfc.c,104 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,105 :: 		}
L_end_host_rx:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of nfc_host_rx
nfc_host_tx_rx:
;nfc.c,109 :: 		uint16_t *p_nbytes_read )
; tx_buff_len start address is: 4 (R1)
; p_tx_buff start address is: 0 (R0)
SUB	SP, SP, #116
STR	LR, [SP, #0]
MOV	R8, R0
UXTH	R9, R1
STR	R2, [SP, #108]
STRH	R3, [SP, #112]
; tx_buff_len end address is: 4 (R1)
; p_tx_buff end address is: 0 (R0)
; p_tx_buff start address is: 32 (R8)
; tx_buff_len start address is: 36 (R9)
LDR	R4, [SP, #116]
STR	R4, [SP, #116]
;nfc.c,114 :: 		char *ptr = p_tx_buff;
STR	R8, [SP, #96]
;nfc.c,115 :: 		char *ptr_rx = p_rx_buff;
LDR	R4, [SP, #108]
STR	R4, [SP, #100]
;nfc.c,119 :: 		IntToStr( tx_buff_len, tmp_txt );
ADD	R4, SP, #12
MOV	R1, R4
SXTH	R0, R9
BL	_IntToStr+0
;nfc.c,123 :: 		for( i = 0; i < tx_buff_len; i++ )
MOVS	R4, #0
SXTH	R4, R4
STRH	R4, [SP, #104]
; p_tx_buff end address is: 32 (R8)
; tx_buff_len end address is: 36 (R9)
MOV	R1, R8
UXTH	R0, R9
L_nfc_host_tx_rx4:
; tx_buff_len start address is: 0 (R0)
; p_tx_buff start address is: 4 (R1)
LDRSH	R4, [SP, #104]
CMP	R4, R0
IT	CS
BCS	L_nfc_host_tx_rx5
;nfc.c,125 :: 		ByteToHex( *ptr++, hex );
ADD	R5, SP, #92
LDR	R4, [SP, #96]
LDRB	R4, [R4, #0]
STR	R1, [SP, #4]
STRH	R0, [SP, #8]
MOV	R1, R5
UXTB	R0, R4
BL	_ByteToHex+0
LDR	R4, [SP, #96]
ADDS	R4, R4, #1
STR	R4, [SP, #96]
;nfc.c,126 :: 		sprinti( tmp_txt, "%s ", hex );
ADD	R6, SP, #92
MOVW	R5, #lo_addr(?lstr_1_nfc+0)
MOVT	R5, #hi_addr(?lstr_1_nfc+0)
ADD	R4, SP, #12
PUSH	(R6)
PUSH	(R5)
PUSH	(R4)
BL	_sprinti+0
ADD	SP, SP, #12
LDRH	R0, [SP, #8]
LDR	R1, [SP, #4]
;nfc.c,123 :: 		for( i = 0; i < tx_buff_len; i++ )
LDRSH	R4, [SP, #104]
ADDS	R4, R4, #1
STRH	R4, [SP, #104]
;nfc.c,128 :: 		}
IT	AL
BAL	L_nfc_host_tx_rx4
L_nfc_host_tx_rx5:
;nfc.c,133 :: 		if( nfc_hal_write( p_tx_buff, tx_buff_len ) )
STR	R1, [SP, #4]
; tx_buff_len end address is: 0 (R0)
UXTH	R1, R0
LDR	R0, [SP, #4]
; p_tx_buff end address is: 4 (R1)
BL	_nfc_hal_write+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_host_tx_rx7
;nfc.c,134 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_host_tx_rx
L_nfc_host_tx_rx7:
;nfc.c,135 :: 		else if( host_rx( p_rx_buff, rx_buff_size, p_nbytes_read, TIMEOUT_1S ) )
MOVW	R3, #1000
LDR	R2, [SP, #116]
LDRH	R1, [SP, #112]
LDR	R0, [SP, #108]
BL	nfc_host_rx+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_host_tx_rx9
;nfc.c,136 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_host_tx_rx
L_nfc_host_tx_rx9:
;nfc.c,140 :: 		IntToStr( *p_nbytes_read, tmp_txt );
ADD	R5, SP, #12
LDR	R4, [SP, #116]
LDRH	R4, [R4, #0]
SXTH	R4, R4
MOV	R1, R5
SXTH	R0, R4
BL	_IntToStr+0
;nfc.c,144 :: 		for( i = 0; i < *p_nbytes_read; i++ )
MOVS	R4, #0
SXTH	R4, R4
STRH	R4, [SP, #104]
L_nfc_host_tx_rx10:
LDR	R4, [SP, #116]
LDRH	R5, [R4, #0]
LDRSH	R4, [SP, #104]
CMP	R4, R5
IT	CS
BCS	L_nfc_host_tx_rx11
;nfc.c,146 :: 		ByteToHex( *ptr_rx++, hex );
ADD	R5, SP, #92
LDR	R4, [SP, #100]
LDRB	R4, [R4, #0]
MOV	R1, R5
UXTB	R0, R4
BL	_ByteToHex+0
LDR	R4, [SP, #100]
ADDS	R4, R4, #1
STR	R4, [SP, #100]
;nfc.c,147 :: 		sprinti( tmp_txt, "%s ", hex );
ADD	R6, SP, #92
MOVW	R5, #lo_addr(?lstr_2_nfc+0)
MOVT	R5, #hi_addr(?lstr_2_nfc+0)
ADD	R4, SP, #12
PUSH	(R6)
PUSH	(R5)
PUSH	(R4)
BL	_sprinti+0
ADD	SP, SP, #12
;nfc.c,144 :: 		for( i = 0; i < *p_nbytes_read; i++ )
LDRSH	R4, [SP, #104]
ADDS	R4, R4, #1
STRH	R4, [SP, #104]
;nfc.c,149 :: 		}
IT	AL
BAL	L_nfc_host_tx_rx10
L_nfc_host_tx_rx11:
;nfc.c,154 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,155 :: 		}
L_end_host_tx_rx:
LDR	LR, [SP, #0]
ADD	SP, SP, #116
BX	LR
; end of nfc_host_tx_rx
nfc_initialize_core:
;nfc.c,157 :: 		static int initialize_core()
SUB	SP, SP, #276
STR	LR, [SP, #0]
;nfc.c,159 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #4
ADDW	R10, R11, #269
MOVW	R12, #lo_addr(?ICSnfc_initialize_core_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_initialize_core_answer_L0+0)
BL	___CC2DW+0
;nfc.c,160 :: 		uint16_t answer_size = 0;
;nfc.c,161 :: 		int i = 10;
;nfc.c,162 :: 		uint8_t CORE_RESET_CMD[] = { 0x20, 0x00, 0x01, 0x01 };
;nfc.c,163 :: 		uint8_t CORE_INIT_CMD[]  = { 0x20, 0x01, 0x00 };
;nfc.c,167 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,168 :: 		OLED_WriteText("Reset and Init", 4, 80);
MOVW	R0, #lo_addr(?lstr3_nfc+0)
MOVT	R0, #hi_addr(?lstr3_nfc+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,171 :: 		while( host_tx_rx( CORE_RESET_CMD, sizeof( CORE_RESET_CMD ), answer, sizeof( answer ), &answer_size ) )
L_nfc_initialize_core13:
ADD	R2, SP, #262
ADD	R1, SP, #4
ADD	R0, SP, #266
PUSH	(R2)
MOVW	R3, #258
MOV	R2, R1
MOVS	R1, #4
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_initialize_core14
;nfc.c,173 :: 		if( i-- == 0 )
LDRSH	R1, [SP, #264]
LDRSH	R0, [SP, #264]
SUBS	R0, R0, #1
STRH	R0, [SP, #264]
CMP	R1, #0
IT	NE
BNE	L_nfc_initialize_core15
;nfc.c,175 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_initialize_core
;nfc.c,176 :: 		}
L_nfc_initialize_core15:
;nfc.c,177 :: 		nfc_hal_delay( 500 );
MOVW	R0, #500
BL	_nfc_hal_delay+0
;nfc.c,178 :: 		}
IT	AL
BAL	L_nfc_initialize_core13
L_nfc_initialize_core14:
;nfc.c,181 :: 		if( host_tx_rx( CORE_INIT_CMD, sizeof( CORE_INIT_CMD ), answer, sizeof( answer ), &answer_size ) )
ADD	R2, SP, #262
ADD	R1, SP, #4
ADD	R0, SP, #270
PUSH	(R2)
MOVW	R3, #258
MOV	R2, R1
MOVS	R1, #3
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_initialize_core16
;nfc.c,183 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_initialize_core
;nfc.c,184 :: 		}
L_nfc_initialize_core16:
;nfc.c,185 :: 		else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x01 ) || ( answer[3] != 0x00 ) )
ADD	R0, SP, #4
LDRB	R0, [R0, #0]
CMP	R0, #64
IT	NE
BNE	L_nfc_initialize_core147
ADD	R0, SP, #4
ADDS	R0, R0, #1
LDRB	R0, [R0, #0]
CMP	R0, #1
IT	NE
BNE	L_nfc_initialize_core146
ADD	R0, SP, #4
ADDS	R0, R0, #3
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L_nfc_initialize_core145
IT	AL
BAL	L_nfc_initialize_core20
L_nfc_initialize_core147:
L_nfc_initialize_core146:
L_nfc_initialize_core145:
;nfc.c,187 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_initialize_core
;nfc.c,188 :: 		}
L_nfc_initialize_core20:
;nfc.c,189 :: 		}
L_end_initialize_core:
LDR	LR, [SP, #0]
ADD	SP, SP, #276
BX	LR
; end of nfc_initialize_core
nfc_p2p_mode:
;nfc.c,231 :: 		static void p2p_mode( nfc_interface_t *rf_intf )
SUBW	SP, SP, #556
STR	LR, [SP, #0]
STR	R0, [SP, #536]
;nfc.c,233 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #266
ADDW	R10, R11, #269
MOVW	R12, #lo_addr(?ICSnfc_p2p_mode_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_p2p_mode_answer_L0+0)
BL	___CC2DW+0
;nfc.c,234 :: 		uint16_t answer_size = 0;
;nfc.c,235 :: 		uint8_t NCIL_LCP_SYMM[] = { 0x00, 0x00, 0x02, 0x00, 0x00 };
;nfc.c,236 :: 		uint8_t NCI_RESTART_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x03 };
;nfc.c,239 :: 		p2p_ndef_reset();
BL	_p2p_ndef_reset+0
;nfc.c,242 :: 		if( ( rf_intf->mode_tech & MODE_LISTEN ) != MODE_LISTEN )
LDR	R1, [SP, #536]
ADDS	R1, R1, #2
LDRB	R1, [R1, #0]
AND	R1, R1, #128
UXTB	R1, R1
CMP	R1, #128
IT	EQ
BEQ	L_nfc_p2p_mode21
;nfc.c,246 :: 		sizeof( answer ), &answer_size );
ADD	R3, SP, #524
;nfc.c,245 :: 		host_tx_rx( NCIL_LCP_SYMM, sizeof( NCIL_LCP_SYMM ), answer,
ADD	R2, SP, #266
ADDW	R1, SP, #526
;nfc.c,246 :: 		sizeof( answer ), &answer_size );
PUSH	(R3)
MOVW	R3, #258
;nfc.c,245 :: 		host_tx_rx( NCIL_LCP_SYMM, sizeof( NCIL_LCP_SYMM ), answer,
MOV	R0, R1
MOVS	R1, #5
;nfc.c,246 :: 		sizeof( answer ), &answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,247 :: 		}
L_nfc_p2p_mode21:
;nfc.c,250 :: 		while( host_rx( answer, sizeof( answer ), &answer_size,
L_nfc_p2p_mode22:
ADD	R2, SP, #524
ADD	R1, SP, #266
;nfc.c,251 :: 		TIMEOUT_2S ) == NFC_SUCCESS )
MOVW	R3, #2000
;nfc.c,250 :: 		while( host_rx( answer, sizeof( answer ), &answer_size,
MOV	R0, R1
MOVW	R1, #258
;nfc.c,251 :: 		TIMEOUT_2S ) == NFC_SUCCESS )
BL	nfc_host_rx+0
CMP	R0, #0
IT	NE
BNE	L_nfc_p2p_mode23
;nfc.c,254 :: 		if( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) )
ADD	R1, SP, #266
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_p2p_mode152
ADD	R1, SP, #266
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_p2p_mode151
L_nfc_p2p_mode150:
;nfc.c,256 :: 		uint8_t cmd[256]  = {0};
ADD	R11, SP, #8
ADD	R10, R11, #258
MOVW	R12, #lo_addr(?ICSnfc_p2p_mode_cmd_L2+0)
MOVT	R12, #hi_addr(?ICSnfc_p2p_mode_cmd_L2+0)
BL	___CC2DW+0
;nfc.c,257 :: 		uint16_t cmd_size = 0;
;nfc.c,260 :: 		( uint16_t * ) &cmd_size );
ADD	R5, SP, #264
;nfc.c,259 :: 		p2p_ndef_next( &answer[3], answer[2], &cmd[3],
ADD	R1, SP, #8
STR	R1, [SP, #552]
ADDS	R4, R1, #3
ADD	R3, SP, #266
STR	R3, [SP, #548]
ADDS	R1, R3, #2
LDRB	R1, [R1, #0]
UXTB	R2, R1
ADDS	R1, R3, #3
;nfc.c,260 :: 		( uint16_t * ) &cmd_size );
MOV	R3, R5
;nfc.c,259 :: 		p2p_ndef_next( &answer[3], answer[2], &cmd[3],
MOV	R0, R1
UXTH	R1, R2
MOV	R2, R4
;nfc.c,260 :: 		( uint16_t * ) &cmd_size );
BL	_p2p_ndef_next+0
;nfc.c,263 :: 		cmd[0] = 0x00;
ADD	R2, SP, #8
MOVS	R1, #0
STRB	R1, [R2, #0]
;nfc.c,264 :: 		cmd[1] = ( cmd_size & 0xFF00 ) >> 8;
LDR	R4, [SP, #552]
ADDS	R2, R4, #1
LDRH	R1, [SP, #264]
AND	R1, R1, #65280
UXTH	R1, R1
LSRS	R1, R1, #8
STRB	R1, [R2, #0]
;nfc.c,265 :: 		cmd[2] = cmd_size & 0x00FF;
ADDS	R2, R4, #2
LDRH	R1, [SP, #264]
AND	R1, R1, #255
STRB	R1, [R2, #0]
;nfc.c,268 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,267 :: 		host_tx_rx( cmd, cmd_size + 3, answer, sizeof( answer ),
LDRH	R1, [SP, #264]
ADDS	R2, R1, #3
LDR	R1, [SP, #548]
;nfc.c,268 :: 		&answer_size );
PUSH	(R3)
;nfc.c,267 :: 		host_tx_rx( cmd, cmd_size + 3, answer, sizeof( answer ),
STRH	R2, [SP, #8]
MOVW	R3, #258
MOV	R0, R4
MOV	R2, R1
LDRH	R1, [SP, #8]
;nfc.c,268 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,269 :: 		}
IT	AL
BAL	L_nfc_p2p_mode27
;nfc.c,254 :: 		if( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) )
L_nfc_p2p_mode152:
L_nfc_p2p_mode151:
;nfc.c,271 :: 		else if ( ( answer[0] == 0x60 ) && ( answer[1] == 0x08 ) )
ADD	R1, SP, #266
LDRB	R1, [R1, #0]
CMP	R1, #96
IT	NE
BNE	L_nfc_p2p_mode154
ADD	R1, SP, #266
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #8
IT	NE
BNE	L_nfc_p2p_mode153
L_nfc_p2p_mode149:
;nfc.c,272 :: 		break;
IT	AL
BAL	L_nfc_p2p_mode23
;nfc.c,271 :: 		else if ( ( answer[0] == 0x60 ) && ( answer[1] == 0x08 ) )
L_nfc_p2p_mode154:
L_nfc_p2p_mode153:
;nfc.c,274 :: 		else if( ( answer[0] == 0x61 ) && ( answer[1] == 0x06 ) )
ADD	R1, SP, #266
LDRB	R1, [R1, #0]
CMP	R1, #97
IT	NE
BNE	L_nfc_p2p_mode156
ADD	R1, SP, #266
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #6
IT	NE
BNE	L_nfc_p2p_mode155
L_nfc_p2p_mode148:
;nfc.c,277 :: 		break;
IT	AL
BAL	L_nfc_p2p_mode23
;nfc.c,274 :: 		else if( ( answer[0] == 0x61 ) && ( answer[1] == 0x06 ) )
L_nfc_p2p_mode156:
L_nfc_p2p_mode155:
;nfc.c,278 :: 		}
L_nfc_p2p_mode27:
;nfc.c,279 :: 		}
IT	AL
BAL	L_nfc_p2p_mode22
L_nfc_p2p_mode23:
;nfc.c,282 :: 		if( ( rf_intf->mode_tech & MODE_LISTEN ) != MODE_LISTEN )
LDR	R1, [SP, #536]
ADDS	R1, R1, #2
LDRB	R1, [R1, #0]
AND	R1, R1, #128
UXTB	R1, R1
CMP	R1, #128
IT	EQ
BEQ	L_nfc_p2p_mode35
;nfc.c,289 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,287 :: 		answer,
ADD	R2, SP, #266
;nfc.c,285 :: 		host_tx_rx( NCI_RESTART_DISCOVERY,
ADDW	R1, SP, #531
;nfc.c,289 :: 		&answer_size );
PUSH	(R3)
;nfc.c,288 :: 		sizeof( answer ),
MOVW	R3, #258
;nfc.c,287 :: 		answer,
;nfc.c,285 :: 		host_tx_rx( NCI_RESTART_DISCOVERY,
MOV	R0, R1
;nfc.c,286 :: 		sizeof( NCI_RESTART_DISCOVERY ),
MOVS	R1, #4
;nfc.c,289 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,292 :: 		&answer_size,
ADD	R2, SP, #524
;nfc.c,290 :: 		host_rx( answer,
ADD	R1, SP, #266
;nfc.c,293 :: 		TIMEOUT_2S );
MOVW	R3, #2000
;nfc.c,292 :: 		&answer_size,
;nfc.c,290 :: 		host_rx( answer,
MOV	R0, R1
;nfc.c,291 :: 		sizeof( answer ),
MOVW	R1, #258
;nfc.c,293 :: 		TIMEOUT_2S );
BL	nfc_host_rx+0
;nfc.c,294 :: 		}
L_nfc_p2p_mode35:
;nfc.c,295 :: 		}
L_end_p2p_mode:
LDR	LR, [SP, #0]
ADDW	SP, SP, #556
BX	LR
; end of nfc_p2p_mode
nfc_reader_mode:
;nfc.c,299 :: 		static void reader_mode( nfc_interface_t *rf_intf )
; rf_intf start address is: 0 (R0)
SUBW	SP, SP, #560
STR	LR, [SP, #0]
; rf_intf end address is: 0 (R0)
; rf_intf start address is: 0 (R0)
;nfc.c,302 :: 		uint8_t cmd[256]     = {0};
ADD	R11, SP, #266
ADDW	R10, R11, #289
MOVW	R12, #lo_addr(?ICSnfc_reader_mode_cmd_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_reader_mode_cmd_L0+0)
BL	___CC2DW+0
;nfc.c,303 :: 		uint16_t cmd_size    = 0;
;nfc.c,304 :: 		uint16_t answer_size = 0;
;nfc.c,308 :: 		};
;nfc.c,312 :: 		};
;nfc.c,316 :: 		};
;nfc.c,320 :: 		};
;nfc.c,321 :: 		uint8_t NCI_RESTART_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x03 };
;nfc.c,323 :: 		rw_ndef_reset( rf_intf->protocol );
ADDS	R1, R0, #1
LDRB	R1, [R1, #0]
STR	R0, [SP, #4]
UXTB	R0, R1
BL	_rw_ndef_reset+0
LDR	R0, [SP, #4]
;nfc.c,326 :: 		if ( rf_intf->protocol == PROT_T3T )
ADDS	R1, R0, #1
LDRB	R1, [R1, #0]
CMP	R1, #3
IT	NE
BNE	L_nfc_reader_mode36
;nfc.c,332 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,330 :: 		answer,
ADD	R2, SP, #8
;nfc.c,328 :: 		host_tx_rx( NCI_POLLING_CMD_T3T,
ADDW	R1, SP, #541
;nfc.c,331 :: 		sizeof( answer ),
STR	R0, [SP, #4]
;nfc.c,332 :: 		&answer_size );
PUSH	(R3)
;nfc.c,331 :: 		sizeof( answer ),
MOVW	R3, #258
;nfc.c,330 :: 		answer,
;nfc.c,328 :: 		host_tx_rx( NCI_POLLING_CMD_T3T,
MOV	R0, R1
;nfc.c,329 :: 		sizeof( NCI_POLLING_CMD_T3T ),
MOVS	R1, #7
;nfc.c,332 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,331 :: 		sizeof( answer ),
;nfc.c,335 :: 		&answer_size,
ADD	R2, SP, #524
;nfc.c,333 :: 		host_rx( answer,
ADD	R1, SP, #8
;nfc.c,336 :: 		TIMEOUT_1S );
MOVW	R3, #1000
;nfc.c,335 :: 		&answer_size,
;nfc.c,333 :: 		host_rx( answer,
MOV	R0, R1
;nfc.c,334 :: 		sizeof( answer ),
MOVW	R1, #258
;nfc.c,336 :: 		TIMEOUT_1S );
BL	nfc_host_rx+0
LDR	R0, [SP, #4]
;nfc.c,337 :: 		if ( ( answer[0] == 0x61 ) && ( answer[1] == 0x08 )
ADD	R1, SP, #8
LDRB	R1, [R1, #0]
CMP	R1, #97
IT	NE
BNE	L_nfc_reader_mode163
ADD	R1, SP, #8
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #8
IT	NE
BNE	L_nfc_reader_mode162
;nfc.c,338 :: 		&& ( answer[3] == 0x00 ) )
ADD	R1, SP, #8
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_reader_mode161
L_nfc_reader_mode160:
;nfc.c,339 :: 		rw_ndef_t3t_set_id_m( &answer[6] );
ADD	R1, SP, #8
ADDS	R1, R1, #6
STR	R0, [SP, #4]
MOV	R0, R1
BL	_rw_ndef_t3t_set_id_m+0
LDR	R0, [SP, #4]
IT	AL
BAL	L_nfc_reader_mode40
; rf_intf end address is: 0 (R0)
;nfc.c,337 :: 		if ( ( answer[0] == 0x61 ) && ( answer[1] == 0x08 )
L_nfc_reader_mode163:
L_nfc_reader_mode162:
;nfc.c,338 :: 		&& ( answer[3] == 0x00 ) )
L_nfc_reader_mode161:
;nfc.c,341 :: 		goto restart_discovery;
IT	AL
BAL	___reader_mode_restart_discovery
L_nfc_reader_mode40:
;nfc.c,342 :: 		}
; rf_intf start address is: 0 (R0)
L_nfc_reader_mode36:
;nfc.c,344 :: 		while( 1 )
L_nfc_reader_mode41:
;nfc.c,346 :: 		rw_ndef_read_next( &answer[3], answer[2], &cmd[3], ( uint16_t * ) &cmd_size );
; rf_intf start address is: 0 (R0)
; rf_intf end address is: 0 (R0)
ADDW	R5, SP, #522
ADD	R1, SP, #266
ADDS	R4, R1, #3
ADD	R3, SP, #8
ADDS	R1, R3, #2
LDRB	R1, [R1, #0]
UXTB	R2, R1
ADDS	R1, R3, #3
STR	R0, [SP, #4]
MOV	R3, R5
MOV	R0, R1
UXTH	R1, R2
MOV	R2, R4
BL	_rw_ndef_read_next+0
LDR	R0, [SP, #4]
;nfc.c,347 :: 		if( cmd_size == 0 )
LDRH	R1, [SP, #522]
CMP	R1, #0
IT	NE
BNE	L_nfc_reader_mode43
; rf_intf end address is: 0 (R0)
;nfc.c,350 :: 		break;
; rf_intf start address is: 0 (R0)
IT	AL
BAL	L_nfc_reader_mode42
;nfc.c,351 :: 		} else {
L_nfc_reader_mode43:
;nfc.c,353 :: 		cmd[0] = 0x00;
ADD	R4, SP, #266
MOVS	R1, #0
STRB	R1, [R4, #0]
;nfc.c,354 :: 		cmd[1] = ( cmd_size & 0xFF00 ) >> 8;
ADDS	R2, R4, #1
LDRH	R1, [SP, #522]
AND	R1, R1, #65280
UXTH	R1, R1
LSRS	R1, R1, #8
STRB	R1, [R2, #0]
;nfc.c,355 :: 		cmd[2] = cmd_size & 0x00FF;
ADDS	R2, R4, #2
LDRH	R1, [SP, #522]
AND	R1, R1, #255
STRB	R1, [R2, #0]
;nfc.c,357 :: 		host_tx_rx( cmd, cmd_size + 3, answer, sizeof( answer ), &answer_size );
ADD	R3, SP, #524
ADD	R2, SP, #8
LDRH	R1, [SP, #522]
ADDS	R1, R1, #3
STR	R0, [SP, #4]
PUSH	(R3)
MOVW	R3, #258
MOV	R0, R4
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,358 :: 		host_rx( answer, sizeof( answer ), &answer_size, TIMEOUT_2S );
ADD	R2, SP, #524
ADD	R1, SP, #8
MOVW	R3, #2000
MOV	R0, R1
MOVW	R1, #258
BL	nfc_host_rx+0
LDR	R0, [SP, #4]
;nfc.c,360 :: 		}
IT	AL
BAL	L_nfc_reader_mode41
L_nfc_reader_mode42:
;nfc.c,363 :: 		switch( rf_intf->protocol )
ADDS	R1, R0, #1
; rf_intf end address is: 0 (R0)
STR	R1, [SP, #556]
IT	AL
BAL	L_nfc_reader_mode45
;nfc.c,365 :: 		case PROT_T1T:
L_nfc_reader_mode47:
;nfc.c,366 :: 		do {
L_nfc_reader_mode48:
;nfc.c,367 :: 		nfc_hal_delay( 500 );
MOVW	R0, #500
BL	_nfc_hal_delay+0
;nfc.c,372 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,370 :: 		answer,
ADD	R2, SP, #8
;nfc.c,368 :: 		host_tx_rx( NCI_PRES_CHECK_T1T,
ADDW	R1, SP, #526
;nfc.c,372 :: 		&answer_size );
PUSH	(R3)
;nfc.c,371 :: 		sizeof( answer ),
MOVW	R3, #258
;nfc.c,370 :: 		answer,
;nfc.c,368 :: 		host_tx_rx( NCI_PRES_CHECK_T1T,
MOV	R0, R1
;nfc.c,369 :: 		sizeof( NCI_PRES_CHECK_T1T ),
MOVS	R1, #10
;nfc.c,372 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,375 :: 		&answer_size,
ADD	R2, SP, #524
;nfc.c,373 :: 		host_rx( answer,
ADD	R1, SP, #8
;nfc.c,376 :: 		TIMEOUT_1S );
MOVW	R3, #1000
;nfc.c,375 :: 		&answer_size,
;nfc.c,373 :: 		host_rx( answer,
MOV	R0, R1
;nfc.c,374 :: 		sizeof( answer ),
MOVW	R1, #258
;nfc.c,376 :: 		TIMEOUT_1S );
BL	nfc_host_rx+0
;nfc.c,377 :: 		} while ( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) );
ADD	R1, SP, #8
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_reader_mode165
ADD	R1, SP, #8
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_reader_mode164
IT	AL
BAL	L_nfc_reader_mode48
L_nfc_reader_mode165:
L_nfc_reader_mode164:
;nfc.c,379 :: 		break;
IT	AL
BAL	L_nfc_reader_mode46
;nfc.c,381 :: 		case PROT_T2T:
L_nfc_reader_mode53:
;nfc.c,382 :: 		do {
L_nfc_reader_mode54:
;nfc.c,383 :: 		nfc_hal_delay( 500 );
MOVW	R0, #500
BL	_nfc_hal_delay+0
;nfc.c,388 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,386 :: 		answer,
ADD	R2, SP, #8
;nfc.c,384 :: 		host_tx_rx( NCI_PRES_CHECK_T2T,
ADD	R1, SP, #536
;nfc.c,388 :: 		&answer_size );
PUSH	(R3)
;nfc.c,387 :: 		sizeof( answer ),
MOVW	R3, #258
;nfc.c,386 :: 		answer,
;nfc.c,384 :: 		host_tx_rx( NCI_PRES_CHECK_T2T,
MOV	R0, R1
;nfc.c,385 :: 		sizeof( NCI_PRES_CHECK_T2T ),
MOVS	R1, #5
;nfc.c,388 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,391 :: 		&answer_size,
ADD	R2, SP, #524
;nfc.c,389 :: 		host_rx( answer,
ADD	R1, SP, #8
;nfc.c,392 :: 		TIMEOUT_1S );
MOVW	R3, #1000
;nfc.c,391 :: 		&answer_size,
;nfc.c,389 :: 		host_rx( answer,
MOV	R0, R1
;nfc.c,390 :: 		sizeof( answer ),
MOVW	R1, #258
;nfc.c,392 :: 		TIMEOUT_1S );
BL	nfc_host_rx+0
;nfc.c,393 :: 		} while ( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) &&
ADD	R1, SP, #8
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_reader_mode168
ADD	R1, SP, #8
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_reader_mode167
;nfc.c,394 :: 		( answer[2] == 0x11 ) );
ADD	R1, SP, #8
ADDS	R1, R1, #2
LDRB	R1, [R1, #0]
CMP	R1, #17
IT	NE
BNE	L_nfc_reader_mode166
IT	AL
BAL	L_nfc_reader_mode54
;nfc.c,393 :: 		} while ( ( answer[0] == 0x00 ) && ( answer[1] == 0x00 ) &&
L_nfc_reader_mode168:
L_nfc_reader_mode167:
;nfc.c,394 :: 		( answer[2] == 0x11 ) );
L_nfc_reader_mode166:
;nfc.c,395 :: 		break;
IT	AL
BAL	L_nfc_reader_mode46
;nfc.c,397 :: 		case PROT_ISODEP:
L_nfc_reader_mode59:
;nfc.c,398 :: 		do {
L_nfc_reader_mode60:
;nfc.c,399 :: 		nfc_hal_delay( 500 );
MOVW	R0, #500
BL	_nfc_hal_delay+0
;nfc.c,404 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,402 :: 		answer,
ADD	R2, SP, #8
;nfc.c,400 :: 		host_tx_rx( NCI_PRES_CHECK_ISO_DEP,
ADD	R1, SP, #548
;nfc.c,404 :: 		&answer_size );
PUSH	(R3)
;nfc.c,403 :: 		sizeof( answer ),
MOVW	R3, #258
;nfc.c,402 :: 		answer,
;nfc.c,400 :: 		host_tx_rx( NCI_PRES_CHECK_ISO_DEP,
MOV	R0, R1
;nfc.c,401 :: 		sizeof( NCI_PRES_CHECK_ISO_DEP ),
MOVS	R1, #3
;nfc.c,404 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,405 :: 		host_rx( answer, sizeof( answer ),&answer_size, TIMEOUT_1S );
ADD	R2, SP, #524
ADD	R1, SP, #8
MOVW	R3, #1000
MOV	R0, R1
MOVW	R1, #258
BL	nfc_host_rx+0
;nfc.c,406 :: 		} while ( ( answer[0] == 0x6F ) && ( answer[1] == 0x11 ) &&
ADD	R1, SP, #8
LDRB	R1, [R1, #0]
CMP	R1, #111
IT	NE
BNE	L_nfc_reader_mode172
ADD	R1, SP, #8
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #17
IT	NE
BNE	L_nfc_reader_mode171
;nfc.c,407 :: 		( answer[2] == 0x01 ) && ( answer[3] == 0x01 ) );
ADD	R1, SP, #8
ADDS	R1, R1, #2
LDRB	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_nfc_reader_mode170
ADD	R1, SP, #8
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_nfc_reader_mode169
IT	AL
BAL	L_nfc_reader_mode60
;nfc.c,406 :: 		} while ( ( answer[0] == 0x6F ) && ( answer[1] == 0x11 ) &&
L_nfc_reader_mode172:
L_nfc_reader_mode171:
;nfc.c,407 :: 		( answer[2] == 0x01 ) && ( answer[3] == 0x01 ) );
L_nfc_reader_mode170:
L_nfc_reader_mode169:
;nfc.c,408 :: 		break;
IT	AL
BAL	L_nfc_reader_mode46
;nfc.c,410 :: 		default:
L_nfc_reader_mode65:
;nfc.c,412 :: 		break;
IT	AL
BAL	L_nfc_reader_mode46
;nfc.c,413 :: 		}
L_nfc_reader_mode45:
LDR	R2, [SP, #556]
LDRB	R1, [R2, #0]
CMP	R1, #1
IT	EQ
BEQ	L_nfc_reader_mode47
LDRB	R1, [R2, #0]
CMP	R1, #2
IT	EQ
BEQ	L_nfc_reader_mode53
LDRB	R1, [R2, #0]
CMP	R1, #4
IT	EQ
BEQ	L_nfc_reader_mode59
IT	AL
BAL	L_nfc_reader_mode65
L_nfc_reader_mode46:
;nfc.c,415 :: 		restart_discovery:
___reader_mode_restart_discovery:
;nfc.c,422 :: 		&answer_size );
ADD	R3, SP, #524
;nfc.c,420 :: 		answer,
ADD	R2, SP, #8
;nfc.c,418 :: 		host_tx_rx( NCI_RESTART_DISCOVERY,
ADDW	R1, SP, #551
;nfc.c,422 :: 		&answer_size );
PUSH	(R3)
;nfc.c,421 :: 		sizeof( answer ),
MOVW	R3, #258
;nfc.c,420 :: 		answer,
;nfc.c,418 :: 		host_tx_rx( NCI_RESTART_DISCOVERY,
MOV	R0, R1
;nfc.c,419 :: 		sizeof( NCI_RESTART_DISCOVERY ),
MOVS	R1, #4
;nfc.c,422 :: 		&answer_size );
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,425 :: 		&answer_size,
ADD	R2, SP, #524
;nfc.c,423 :: 		host_rx( answer,
ADD	R1, SP, #8
;nfc.c,426 :: 		TIMEOUT_1S );
MOVW	R3, #1000
;nfc.c,425 :: 		&answer_size,
;nfc.c,423 :: 		host_rx( answer,
MOV	R0, R1
;nfc.c,424 :: 		sizeof( answer ),
MOVW	R1, #258
;nfc.c,426 :: 		TIMEOUT_1S );
BL	nfc_host_rx+0
;nfc.c,427 :: 		}
L_end_reader_mode:
LDR	LR, [SP, #0]
ADDW	SP, SP, #560
BX	LR
; end of nfc_reader_mode
_nfc_reader_tag_cmd:
;nfc.c,430 :: 		uint8_t *answer, uint8_t *answer_size )
; command_size start address is: 4 (R1)
; command start address is: 0 (R0)
SUBW	SP, SP, #532
STR	LR, [SP, #0]
UXTB	R8, R1
STR	R2, [SP, #524]
STR	R3, [SP, #528]
; command_size end address is: 4 (R1)
; command end address is: 0 (R0)
; command start address is: 0 (R0)
; command_size start address is: 32 (R8)
;nfc.c,432 :: 		int status = NFC_ERROR;
ADD	R11, SP, #260
ADD	R10, R11, #262
MOVW	R12, #lo_addr(?ICSnfc_reader_tag_cmd_status_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_reader_tag_cmd_status_L0+0)
BL	___CC2DW+0
;nfc.c,434 :: 		uint8_t ans[ANSWER_MAX_SIZE] = {0};
;nfc.c,435 :: 		uint16_t ans_size = 0;;
;nfc.c,438 :: 		cmd[0] = 0x00;
ADD	R6, SP, #4
MOVS	R4, #0
STRB	R4, [R6, #0]
;nfc.c,439 :: 		cmd[1] = 0x00;
ADDS	R5, R6, #1
MOVS	R4, #0
STRB	R4, [R5, #0]
;nfc.c,440 :: 		cmd[2] = command_size;
ADDS	R4, R6, #2
STRB	R8, [R4, #0]
;nfc.c,441 :: 		memcpy( &cmd[3], command, command_size );
ADDS	R4, R6, #3
UXTB	R2, R8
MOV	R1, R0
; command end address is: 0 (R0)
MOV	R0, R4
BL	_memcpy+0
;nfc.c,442 :: 		host_tx_rx( cmd, command_size + 3, ans, sizeof( ans ), &ans_size );
ADD	R7, SP, #520
ADD	R6, SP, #262
ADD	R5, R8, #3
; command_size end address is: 32 (R8)
ADD	R4, SP, #4
MOVW	R3, #258
MOV	R2, R6
UXTH	R1, R5
MOV	R0, R4
PUSH	(R7)
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,445 :: 		host_rx( ans, sizeof( ans ), &ans_size, TIMEOUT_2S );
ADD	R5, SP, #520
ADD	R4, SP, #262
MOVW	R3, #2000
MOV	R2, R5
MOVW	R1, #258
MOV	R0, R4
BL	nfc_host_rx+0
;nfc.c,447 :: 		if ( ( ans[0] == 0x0 ) && ( ans[1] == 0x0 ) )
ADD	R4, SP, #262
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__nfc_reader_tag_cmd175
ADD	R4, SP, #262
ADDS	R4, R4, #1
LDRB	R4, [R4, #0]
CMP	R4, #0
IT	NE
BNE	L__nfc_reader_tag_cmd174
L__nfc_reader_tag_cmd173:
;nfc.c,448 :: 		status = NFC_SUCCESS;
MOVS	R4, #0
SXTH	R4, R4
STRH	R4, [SP, #260]
;nfc.c,447 :: 		if ( ( ans[0] == 0x0 ) && ( ans[1] == 0x0 ) )
L__nfc_reader_tag_cmd175:
L__nfc_reader_tag_cmd174:
;nfc.c,450 :: 		*answer_size = ans[2];
ADD	R6, SP, #262
ADDS	R4, R6, #2
LDRB	R5, [R4, #0]
LDR	R4, [SP, #528]
STRB	R5, [R4, #0]
;nfc.c,451 :: 		memcpy( answer, &ans[3], *answer_size );
LDR	R4, [SP, #528]
LDRB	R4, [R4, #0]
UXTB	R5, R4
ADDS	R4, R6, #3
SXTH	R2, R5
MOV	R1, R4
LDR	R0, [SP, #524]
BL	_memcpy+0
;nfc.c,453 :: 		return status;
LDRSH	R0, [SP, #260]
;nfc.c,454 :: 		}
L_end_nfc_reader_tag_cmd:
LDR	LR, [SP, #0]
ADDW	SP, SP, #532
BX	LR
; end of _nfc_reader_tag_cmd
_nfc_init:
;nfc.c,457 :: 		int nfc_init( uint8_t slave_address )
; slave_address start address is: 0 (R0)
SUB	SP, SP, #312
STR	LR, [SP, #0]
; slave_address end address is: 0 (R0)
; slave_address start address is: 0 (R0)
;nfc.c,460 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #8
ADDW	R10, R11, #279
MOVW	R12, #lo_addr(?ICSnfc_init_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_init_answer_L0+0)
BL	___CC2DW+0
;nfc.c,461 :: 		uint16_t answer_size = 0;
;nfc.c,462 :: 		uint8_t CORE_SET_POWER_MODE_CMD[] = { 0x2f, 0x00, 0x01, 0x00 };
;nfc.c,463 :: 		uint8_t TEST_ANTENNA_CMD[] = { 0x2f, 0x3d, 0x05, 0x20, 0x00, 0x00, 0x00, 0x00 };
;nfc.c,464 :: 		uint8_t TEST_PRBS_CMD[] = { 0x2f, 0x30, 0x04, 0x00, 0x00, 0x00, 0x1f };
;nfc.c,468 :: 		if( slave_address != NFC_I2C_SLAVE && slave_address != NFC_I2C_SLAVE_ALT )
CMP	R0, #40
IT	EQ
BEQ	L__nfc_init178
CMP	R0, #41
IT	EQ
BEQ	L__nfc_init177
; slave_address end address is: 0 (R0)
L__nfc_init176:
;nfc.c,469 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_init
;nfc.c,468 :: 		if( slave_address != NFC_I2C_SLAVE && slave_address != NFC_I2C_SLAVE_ALT )
L__nfc_init178:
; slave_address start address is: 0 (R0)
L__nfc_init177:
;nfc.c,472 :: 		nfc_hal_init( slave_address );
; slave_address end address is: 0 (R0)
BL	_nfc_hal_init+0
;nfc.c,476 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,477 :: 		OLED_WriteText("Start Test Mode", 4, 80);
MOVW	R1, #lo_addr(?lstr4_nfc+0)
MOVT	R1, #hi_addr(?lstr4_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,478 :: 		initialize_core();
BL	nfc_initialize_core+0
;nfc.c,484 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,485 :: 		OLED_WriteText("Disabe Standby", 4, 80);
MOVW	R1, #lo_addr(?lstr5_nfc+0)
MOVT	R1, #hi_addr(?lstr5_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,486 :: 		host_tx_rx( CORE_SET_POWER_MODE_CMD, sizeof( CORE_SET_POWER_MODE_CMD ), answer, sizeof( answer ), &answer_size );
ADD	R3, SP, #266
ADD	R2, SP, #8
ADD	R1, SP, #268
PUSH	(R3)
MOVW	R3, #258
MOV	R0, R1
MOVS	R1, #4
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,488 :: 		if( answer[3] == 0x00 )
ADD	R1, SP, #8
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_init72
;nfc.c,491 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,492 :: 		OLED_WriteText("Standby OFF", 4, 80);
MOVW	R1, #lo_addr(?lstr6_nfc+0)
MOVT	R1, #hi_addr(?lstr6_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,493 :: 		}
L_nfc_init72:
;nfc.c,495 :: 		for( i = 0, j = 4; i < 4; i++, j++ )
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [SP, #4]
MOVS	R1, #4
SXTH	R1, R1
STRH	R1, [SP, #6]
L_nfc_init73:
LDRSH	R1, [SP, #4]
CMP	R1, #4
IT	GE
BGE	L_nfc_init74
;nfc.c,498 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,499 :: 		OLED_WriteText("Test Antenna", 4, 80);
MOVW	R1, #lo_addr(?lstr7_nfc+0)
MOVT	R1, #hi_addr(?lstr7_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,500 :: 		TEST_ANTENNA_CMD[ j ] |= 0x01;
ADD	R3, SP, #272
STR	R3, [SP, #308]
LDRSH	R1, [SP, #6]
ADDS	R2, R3, R1
LDRB	R1, [R2, #0]
ORR	R1, R1, #1
STRB	R1, [R2, #0]
;nfc.c,502 :: 		host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );
ADD	R2, SP, #266
STR	R2, [SP, #304]
ADD	R1, SP, #8
STR	R1, [SP, #300]
PUSH	(R2)
MOV	R2, R1
MOVS	R1, #8
MOV	R0, R3
MOVW	R3, #258
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,504 :: 		TEST_ANTENNA_CMD[ j ] &= ~0x01;
ADD	R2, SP, #272
LDRSH	R1, [SP, #6]
ADDS	R3, R2, R1
LDRB	R2, [R3, #0]
MOVW	R1, #65534
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [R3, #0]
;nfc.c,506 :: 		host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );
LDR	R3, [SP, #308]
LDR	R2, [SP, #304]
LDR	R1, [SP, #300]
PUSH	(R2)
MOV	R2, R1
MOVS	R1, #8
MOV	R0, R3
MOVW	R3, #258
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,508 :: 		host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );
ADD	R3, SP, #266
ADD	R2, SP, #8
ADD	R1, SP, #272
PUSH	(R3)
MOVW	R3, #258
MOV	R0, R1
MOVS	R1, #8
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,510 :: 		TEST_ANTENNA_CMD[ j ] |= 0x01;
ADD	R2, SP, #272
LDRSH	R1, [SP, #6]
ADDS	R2, R2, R1
LDRB	R1, [R2, #0]
ORR	R1, R1, #1
STRB	R1, [R2, #0]
;nfc.c,512 :: 		host_tx_rx( TEST_ANTENNA_CMD, sizeof( TEST_ANTENNA_CMD ), answer, sizeof( answer ), &answer_size );
LDR	R3, [SP, #308]
LDR	R2, [SP, #304]
LDR	R1, [SP, #300]
PUSH	(R2)
MOV	R2, R1
MOVS	R1, #8
MOV	R0, R3
MOVW	R3, #258
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,495 :: 		for( i = 0, j = 4; i < 4; i++, j++ )
LDRSH	R1, [SP, #4]
ADDS	R1, R1, #1
STRH	R1, [SP, #4]
LDRSH	R1, [SP, #6]
ADDS	R1, R1, #1
STRH	R1, [SP, #6]
;nfc.c,513 :: 		}
IT	AL
BAL	L_nfc_init73
L_nfc_init74:
;nfc.c,515 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,516 :: 		OLED_WriteText("Start Testing", 4, 80);
MOVW	R1, #lo_addr(?lstr8_nfc+0)
MOVT	R1, #hi_addr(?lstr8_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,517 :: 		host_tx_rx( TEST_PRBS_CMD, sizeof( TEST_PRBS_CMD ), answer, sizeof( answer ), &answer_size );
ADD	R3, SP, #266
ADD	R2, SP, #8
ADD	R1, SP, #280
PUSH	(R3)
MOVW	R3, #258
MOV	R0, R1
MOVS	R1, #7
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,519 :: 		if( answer[3] == 0x00 )
ADD	R1, SP, #8
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_nfc_init76
;nfc.c,522 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,523 :: 		OLED_WriteText("Test Success", 4, 80);
MOVW	R1, #lo_addr(?lstr9_nfc+0)
MOVT	R1, #hi_addr(?lstr9_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,524 :: 		}
IT	AL
BAL	L_nfc_init77
L_nfc_init76:
;nfc.c,528 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,529 :: 		OLED_WriteText("Test Fail", 4, 80);
MOVW	R1, #lo_addr(?lstr10_nfc+0)
MOVT	R1, #hi_addr(?lstr10_nfc+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;nfc.c,530 :: 		}
L_nfc_init77:
;nfc.c,532 :: 		nfc_hal_reset();
BL	_nfc_hal_reset+0
;nfc.c,536 :: 		if( initialize_core() )
BL	nfc_initialize_core+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_init78
;nfc.c,537 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_init
L_nfc_init78:
;nfc.c,539 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,540 :: 		}
L_end_nfc_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #312
BX	LR
; end of _nfc_init
_nfc_rx_ready:
;nfc.c,542 :: 		void nfc_rx_ready()
SUB	SP, SP, #4
;nfc.c,544 :: 		rx_flag = true;
MOVS	R1, #1
MOVW	R0, #lo_addr(nfc_rx_flag+0)
MOVT	R0, #hi_addr(nfc_rx_flag+0)
STRB	R1, [R0, #0]
;nfc.c,545 :: 		}
L_end_nfc_rx_ready:
ADD	SP, SP, #4
BX	LR
; end of _nfc_rx_ready
_nfc_timer_tick:
;nfc.c,547 :: 		void nfc_timer_tick()
SUB	SP, SP, #4
;nfc.c,549 :: 		timer_tick++;
MOVW	R0, #lo_addr(nfc_timer_tick+0)
MOVT	R0, #hi_addr(nfc_timer_tick+0)
LDR	R0, [R0, #0]
ADDS	R1, R0, #1
MOVW	R0, #lo_addr(nfc_timer_tick+0)
MOVT	R0, #hi_addr(nfc_timer_tick+0)
STR	R1, [R0, #0]
;nfc.c,550 :: 		}
L_end_nfc_timer_tick:
ADD	SP, SP, #4
BX	LR
; end of _nfc_timer_tick
_nfc_configure:
;nfc.c,552 :: 		int nfc_configure( nfc_mode_t mode )
; mode start address is: 0 (R0)
SUBW	SP, SP, #604
STR	LR, [SP, #0]
UXTB	R5, R0
; mode end address is: 0 (R0)
; mode start address is: 20 (R5)
;nfc.c,555 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #264
ADD	R10, R11, #334
MOVW	R12, #lo_addr(?ICSnfc_configure_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_configure_answer_L0+0)
BL	___CC2DW+0
;nfc.c,556 :: 		uint16_t answer_size = 0;
;nfc.c,557 :: 		uint8_t item = 0;
;nfc.c,559 :: 		uint8_t NCI_DISCOVER_MAP_CMD[] = { 0x21, 0x00 };
;nfc.c,565 :: 		uint8_t DM_P2P[] = { 0x5, 0x3, 0x3 };
;nfc.c,566 :: 		uint8_t R_P2P[]  = { 0x1, 0x3, 0x0, 0x1, 0x5 };
;nfc.c,573 :: 		};
;nfc.c,580 :: 		};
;nfc.c,581 :: 		uint8_t NCI_PROPRIETARY_ACT_CMD[] = { 0x2F, 0x02, 0x00 };
;nfc.c,587 :: 		};
;nfc.c,591 :: 		};
;nfc.c,594 :: 		if( mode == NFC_MODE_NONE )
CMP	R5, #0
IT	NE
BNE	L_nfc_configure79
; mode end address is: 20 (R5)
;nfc.c,595 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure79:
;nfc.c,599 :: 		if( mode == NFC_MODE_RW )
; mode start address is: 20 (R5)
CMP	R5, #4
IT	NE
BNE	L_nfc_configure80
;nfc.c,602 :: 		answer, sizeof( answer ), &answer_size ) )
ADDW	R3, SP, #522
ADD	R2, SP, #264
;nfc.c,601 :: 		if( host_tx_rx( NCI_PROPRIETARY_ACT_CMD, sizeof( NCI_PROPRIETARY_ACT_CMD ),
ADDW	R1, SP, #583
;nfc.c,602 :: 		answer, sizeof( answer ), &answer_size ) )
STRB	R5, [SP, #4]
PUSH	(R3)
MOVW	R3, #258
;nfc.c,601 :: 		if( host_tx_rx( NCI_PROPRIETARY_ACT_CMD, sizeof( NCI_PROPRIETARY_ACT_CMD ),
MOV	R0, R1
MOVS	R1, #3
;nfc.c,602 :: 		answer, sizeof( answer ), &answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
LDRB	R5, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_nfc_configure81
; mode end address is: 20 (R5)
;nfc.c,603 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure81:
;nfc.c,604 :: 		else if( ( answer[0] != 0x4F ) || ( answer[1] != 0x02 ) ||
; mode start address is: 20 (R5)
ADD	R1, SP, #264
LDRB	R1, [R1, #0]
CMP	R1, #79
IT	NE
BNE	L__nfc_configure186
ADD	R1, SP, #264
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #2
IT	NE
BNE	L__nfc_configure185
;nfc.c,605 :: 		( answer[3] != 0x00 ) )
ADD	R1, SP, #264
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L__nfc_configure184
IT	AL
BAL	L_nfc_configure85
; mode end address is: 20 (R5)
;nfc.c,604 :: 		else if( ( answer[0] != 0x4F ) || ( answer[1] != 0x02 ) ||
L__nfc_configure186:
L__nfc_configure185:
;nfc.c,605 :: 		( answer[3] != 0x00 ) )
L__nfc_configure184:
;nfc.c,606 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure85:
;nfc.c,607 :: 		}
; mode start address is: 20 (R5)
L_nfc_configure80:
;nfc.c,611 :: 		item = 0;
; item start address is: 24 (R6)
MOVS	R6, #0
;nfc.c,620 :: 		if( mode & NFC_MODE_P2P )
AND	R1, R5, #2
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L__nfc_configure199
;nfc.c,622 :: 		memcpy( &command[4 + ( 3 * item )], ( void* )DM_P2P, sizeof( DM_P2P ) );
ADDW	R3, SP, #526
MOVS	R1, #3
SXTH	R1, R1
MULS	R1, R6, R1
SXTH	R1, R1
ADDS	R2, R1, #4
SXTH	R2, R2
ADD	R1, SP, #8
ADDS	R1, R1, R2
STRB	R5, [SP, #4]
MOVS	R2, #3
SXTH	R2, R2
MOV	R0, R1
MOV	R1, R3
BL	_memcpy+0
LDRB	R5, [SP, #4]
;nfc.c,623 :: 		item++;
ADDS	R6, R6, #1
UXTB	R6, R6
; item end address is: 24 (R6)
;nfc.c,624 :: 		}
IT	AL
BAL	L_nfc_configure86
L__nfc_configure199:
;nfc.c,620 :: 		if( mode & NFC_MODE_P2P )
;nfc.c,624 :: 		}
L_nfc_configure86:
;nfc.c,627 :: 		if( mode & NFC_MODE_RW )
; item start address is: 24 (R6)
AND	R1, R5, #4
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L__nfc_configure200
;nfc.c,629 :: 		memcpy( &command[4 + ( 3 * item )], ( void* )DM_RW, sizeof( DM_RW ) );
ADD	R3, SP, #568
MOVS	R1, #3
SXTH	R1, R1
MULS	R1, R6, R1
SXTH	R1, R1
ADDS	R2, R1, #4
SXTH	R2, R2
ADD	R1, SP, #8
ADDS	R1, R1, R2
STRB	R5, [SP, #4]
MOVS	R2, #15
SXTH	R2, R2
MOV	R0, R1
MOV	R1, R3
BL	_memcpy+0
LDRB	R5, [SP, #4]
;nfc.c,630 :: 		item += sizeof( DM_RW ) / 3;
ADDS	R1, R6, #5
UXTB	R6, R1
; item end address is: 24 (R6)
;nfc.c,631 :: 		}
IT	AL
BAL	L_nfc_configure87
L__nfc_configure200:
;nfc.c,627 :: 		if( mode & NFC_MODE_RW )
;nfc.c,631 :: 		}
L_nfc_configure87:
;nfc.c,634 :: 		if( item != 0 )
; item start address is: 24 (R6)
CMP	R6, #0
IT	EQ
BEQ	L_nfc_configure88
;nfc.c,636 :: 		memcpy( command, ( void *)NCI_DISCOVER_MAP_CMD, sizeof( NCI_DISCOVER_MAP_CMD ) );
ADD	R2, SP, #524
ADD	R1, SP, #8
STR	R1, [SP, #600]
STRB	R5, [SP, #4]
MOV	R0, R1
MOV	R1, R2
MOVS	R2, #2
SXTH	R2, R2
BL	_memcpy+0
;nfc.c,637 :: 		command[2] = 1 + ( item * 3 );
ADD	R1, SP, #8
ADDS	R2, R1, #2
MOVS	R1, #3
SXTH	R1, R1
MULS	R1, R6, R1
SXTH	R1, R1
ADDS	R1, R1, #1
STRB	R1, [R2, #0]
;nfc.c,638 :: 		command[3] = item;
LDR	R4, [SP, #600]
ADDS	R1, R4, #3
STRB	R6, [R1, #0]
; item end address is: 24 (R6)
;nfc.c,641 :: 		&answer_size ) )
ADDW	R3, SP, #522
;nfc.c,640 :: 		if( host_tx_rx( command, 3 + command[2], answer, sizeof( answer ),
ADD	R2, SP, #264
ADDS	R1, R4, #2
LDRB	R1, [R1, #0]
ADDS	R1, R1, #3
;nfc.c,641 :: 		&answer_size ) )
PUSH	(R3)
;nfc.c,640 :: 		if( host_tx_rx( command, 3 + command[2], answer, sizeof( answer ),
MOVW	R3, #258
UXTH	R1, R1
MOV	R0, R4
;nfc.c,641 :: 		&answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,640 :: 		if( host_tx_rx( command, 3 + command[2], answer, sizeof( answer ),
LDRB	R5, [SP, #4]
;nfc.c,641 :: 		&answer_size ) )
CMP	R0, #0
IT	EQ
BEQ	L_nfc_configure89
; mode end address is: 20 (R5)
;nfc.c,642 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure89:
;nfc.c,643 :: 		else if( ( answer[0] != 0x41 ) || ( answer[1] != 0x00 ) ||
; mode start address is: 20 (R5)
ADD	R1, SP, #264
LDRB	R1, [R1, #0]
CMP	R1, #65
IT	NE
BNE	L__nfc_configure189
ADD	R1, SP, #264
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L__nfc_configure188
;nfc.c,644 :: 		( answer[3] != 0x00 ) )
ADD	R1, SP, #264
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L__nfc_configure187
IT	AL
BAL	L_nfc_configure93
; mode end address is: 20 (R5)
;nfc.c,643 :: 		else if( ( answer[0] != 0x41 ) || ( answer[1] != 0x00 ) ||
L__nfc_configure189:
L__nfc_configure188:
;nfc.c,644 :: 		( answer[3] != 0x00 ) )
L__nfc_configure187:
;nfc.c,645 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure93:
;nfc.c,646 :: 		}
; mode start address is: 20 (R5)
L_nfc_configure88:
;nfc.c,650 :: 		item = 0;
; item start address is: 24 (R6)
MOVS	R6, #0
;nfc.c,659 :: 		if( mode & NFC_MODE_P2P )
AND	R1, R5, #2
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L__nfc_configure201
;nfc.c,661 :: 		memcpy( &command[5 + ( 5 * item )], ( void* )R_P2P, sizeof( R_P2P ) );
ADDW	R3, SP, #529
MOVS	R1, #5
SXTH	R1, R1
MULS	R1, R6, R1
SXTH	R1, R1
ADDS	R2, R1, #5
SXTH	R2, R2
ADD	R1, SP, #8
ADDS	R1, R1, R2
STRB	R5, [SP, #4]
MOVS	R2, #5
SXTH	R2, R2
MOV	R0, R1
MOV	R1, R3
BL	_memcpy+0
LDRB	R5, [SP, #4]
;nfc.c,662 :: 		item++;
ADDS	R6, R6, #1
UXTB	R6, R6
; item end address is: 24 (R6)
;nfc.c,663 :: 		}
IT	AL
BAL	L_nfc_configure94
L__nfc_configure201:
;nfc.c,659 :: 		if( mode & NFC_MODE_P2P )
;nfc.c,663 :: 		}
L_nfc_configure94:
;nfc.c,666 :: 		if( item != 0 )
; item start address is: 24 (R6)
CMP	R6, #0
IT	EQ
BEQ	L_nfc_configure95
;nfc.c,668 :: 		memcpy( command, ( void* )NCI_ROUTING, sizeof( NCI_ROUTING ) );
ADDW	R2, SP, #586
ADD	R1, SP, #8
STR	R1, [SP, #600]
STRB	R5, [SP, #4]
MOV	R0, R1
MOV	R1, R2
MOVS	R2, #5
SXTH	R2, R2
BL	_memcpy+0
;nfc.c,669 :: 		command[2] = 2 + ( item * 5 );
ADD	R1, SP, #8
ADDS	R2, R1, #2
MOVS	R1, #5
SXTH	R1, R1
MULS	R1, R6, R1
SXTH	R1, R1
ADDS	R1, R1, #2
STRB	R1, [R2, #0]
;nfc.c,670 :: 		command[4] = item;
LDR	R4, [SP, #600]
ADDS	R1, R4, #4
STRB	R6, [R1, #0]
; item end address is: 24 (R6)
;nfc.c,672 :: 		&answer_size ) )
ADDW	R3, SP, #522
;nfc.c,671 :: 		if( host_tx_rx( command, 3 + command[2] , answer, sizeof( answer ),
ADD	R2, SP, #264
ADDS	R1, R4, #2
LDRB	R1, [R1, #0]
ADDS	R1, R1, #3
;nfc.c,672 :: 		&answer_size ) )
PUSH	(R3)
;nfc.c,671 :: 		if( host_tx_rx( command, 3 + command[2] , answer, sizeof( answer ),
MOVW	R3, #258
UXTH	R1, R1
MOV	R0, R4
;nfc.c,672 :: 		&answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
;nfc.c,671 :: 		if( host_tx_rx( command, 3 + command[2] , answer, sizeof( answer ),
LDRB	R5, [SP, #4]
;nfc.c,672 :: 		&answer_size ) )
CMP	R0, #0
IT	EQ
BEQ	L_nfc_configure96
; mode end address is: 20 (R5)
;nfc.c,673 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure96:
;nfc.c,674 :: 		else if( ( answer[0] != 0x41 ) || ( answer[1] != 0x01 ) ||
; mode start address is: 20 (R5)
ADD	R1, SP, #264
LDRB	R1, [R1, #0]
CMP	R1, #65
IT	NE
BNE	L__nfc_configure192
ADD	R1, SP, #264
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L__nfc_configure191
;nfc.c,675 :: 		( answer[3] != 0x00 ) )
ADD	R1, SP, #264
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L__nfc_configure190
IT	AL
BAL	L_nfc_configure100
; mode end address is: 20 (R5)
;nfc.c,674 :: 		else if( ( answer[0] != 0x41 ) || ( answer[1] != 0x01 ) ||
L__nfc_configure192:
L__nfc_configure191:
;nfc.c,675 :: 		( answer[3] != 0x00 ) )
L__nfc_configure190:
;nfc.c,676 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure100:
;nfc.c,677 :: 		}
; mode start address is: 20 (R5)
L_nfc_configure95:
;nfc.c,686 :: 		if( mode & NFC_MODE_P2P )
AND	R1, R5, #2
UXTB	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L_nfc_configure101
;nfc.c,687 :: 		nci_set_config_nfca_selrsp[6] += 0x40;
ADDW	R1, SP, #591
ADDS	R2, R1, #6
LDRB	R1, [R2, #0]
ADDS	R1, #64
STRB	R1, [R2, #0]
L_nfc_configure101:
;nfc.c,690 :: 		if( nci_set_config_nfca_selrsp[6] != 0x00 )
ADDW	R1, SP, #591
ADDS	R1, R1, #6
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	EQ
BEQ	L_nfc_configure102
;nfc.c,694 :: 		answer, sizeof( answer ), &answer_size ) )
ADDW	R3, SP, #522
ADD	R2, SP, #264
;nfc.c,692 :: 		if( host_tx_rx( nci_set_config_nfca_selrsp,
ADDW	R1, SP, #591
;nfc.c,694 :: 		answer, sizeof( answer ), &answer_size ) )
STRB	R5, [SP, #4]
PUSH	(R3)
MOVW	R3, #258
;nfc.c,692 :: 		if( host_tx_rx( nci_set_config_nfca_selrsp,
MOV	R0, R1
;nfc.c,693 :: 		sizeof( nci_set_config_nfca_selrsp ),
MOVS	R1, #7
;nfc.c,694 :: 		answer, sizeof( answer ), &answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
LDRB	R5, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_nfc_configure103
; mode end address is: 20 (R5)
;nfc.c,695 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure103:
;nfc.c,696 :: 		else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x02 ) ||
; mode start address is: 20 (R5)
ADD	R1, SP, #264
LDRB	R1, [R1, #0]
CMP	R1, #64
IT	NE
BNE	L__nfc_configure195
ADD	R1, SP, #264
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #2
IT	NE
BNE	L__nfc_configure194
;nfc.c,697 :: 		( answer[3] != 0x00 ) )
ADD	R1, SP, #264
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L__nfc_configure193
IT	AL
BAL	L_nfc_configure107
; mode end address is: 20 (R5)
;nfc.c,696 :: 		else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x02 ) ||
L__nfc_configure195:
L__nfc_configure194:
;nfc.c,697 :: 		( answer[3] != 0x00 ) )
L__nfc_configure193:
;nfc.c,698 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure107:
;nfc.c,699 :: 		}
; mode start address is: 20 (R5)
L_nfc_configure102:
;nfc.c,704 :: 		if( mode & NFC_MODE_P2P )
AND	R1, R5, #2
UXTB	R1, R1
; mode end address is: 20 (R5)
CMP	R1, #0
IT	EQ
BEQ	L_nfc_configure108
;nfc.c,707 :: 		answer, sizeof( answer ),&answer_size ) )
ADDW	R3, SP, #522
ADD	R2, SP, #264
;nfc.c,706 :: 		if( host_tx_rx( NCI_SET_CONFIG_NFC, sizeof( NCI_SET_CONFIG_NFC ),
ADDW	R1, SP, #534
;nfc.c,707 :: 		answer, sizeof( answer ),&answer_size ) )
PUSH	(R3)
MOVW	R3, #258
;nfc.c,706 :: 		if( host_tx_rx( NCI_SET_CONFIG_NFC, sizeof( NCI_SET_CONFIG_NFC ),
MOV	R0, R1
MOVS	R1, #34
;nfc.c,707 :: 		answer, sizeof( answer ),&answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_configure109
;nfc.c,708 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure109:
;nfc.c,709 :: 		else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x02 ) ||
ADD	R1, SP, #264
LDRB	R1, [R1, #0]
CMP	R1, #64
IT	NE
BNE	L__nfc_configure198
ADD	R1, SP, #264
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #2
IT	NE
BNE	L__nfc_configure197
;nfc.c,710 :: 		( answer[3] != 0x00 ) )
ADD	R1, SP, #264
ADDS	R1, R1, #3
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L__nfc_configure196
IT	AL
BAL	L_nfc_configure113
;nfc.c,709 :: 		else if( ( answer[0] != 0x40 ) || ( answer[1] != 0x02 ) ||
L__nfc_configure198:
L__nfc_configure197:
;nfc.c,710 :: 		( answer[3] != 0x00 ) )
L__nfc_configure196:
;nfc.c,711 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_configure
L_nfc_configure113:
;nfc.c,712 :: 		}
L_nfc_configure108:
;nfc.c,715 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,716 :: 		}
L_end_nfc_configure:
LDR	LR, [SP, #0]
ADDW	SP, SP, #604
BX	LR
; end of _nfc_configure
_nfc_start_discovery:
;nfc.c,718 :: 		int nfc_start_discovery( uint8_t *p_tech_tab, uint8_t tech_tab_size )
SUBW	SP, SP, #540
STR	LR, [SP, #0]
STR	R0, [SP, #524]
STRB	R1, [SP, #528]
;nfc.c,721 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #260
ADD	R10, R11, #262
MOVW	R12, #lo_addr(?ICSnfc_start_discovery_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_start_discovery_answer_L0+0)
BL	___CC2DW+0
;nfc.c,722 :: 		uint16_t answer_size = 0;
;nfc.c,724 :: 		uint8_t NCI_DISCOVER_CMD[] = { 0x21, 0x03 };
;nfc.c,728 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R2, #0
PUSH	(R2)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;nfc.c,729 :: 		OLED_WriteText("Discovery Start", 4, 80);
MOVW	R2, #lo_addr(?lstr11_nfc+0)
MOVT	R2, #hi_addr(?lstr11_nfc+0)
MOVS	R1, #4
MOV	R0, R2
MOVS	R2, #80
BL	_OLED_WriteText+0
;nfc.c,732 :: 		memcpy( command, ( void* )NCI_DISCOVER_CMD, sizeof( NCI_DISCOVER_CMD ) );
ADD	R3, SP, #520
ADD	R2, SP, #4
STR	R2, [SP, #536]
MOV	R1, R3
MOV	R0, R2
MOVS	R2, #2
SXTH	R2, R2
BL	_memcpy+0
;nfc.c,735 :: 		command[2] = ( tech_tab_size * 2 ) + 1;
ADD	R2, SP, #4
ADDS	R3, R2, #2
LDRB	R2, [SP, #528]
LSLS	R2, R2, #1
SXTH	R2, R2
ADDS	R2, R2, #1
STRB	R2, [R3, #0]
;nfc.c,736 :: 		command[3] = tech_tab_size;
LDR	R2, [SP, #536]
ADDS	R3, R2, #3
LDRB	R2, [SP, #528]
STRB	R2, [R3, #0]
;nfc.c,738 :: 		for ( i = 0; i < tech_tab_size; i++ )
; i start address is: 0 (R0)
MOVS	R0, #0
; i end address is: 0 (R0)
L_nfc_start_discovery114:
; i start address is: 0 (R0)
LDRB	R2, [SP, #528]
CMP	R0, R2
IT	CS
BCS	L_nfc_start_discovery115
;nfc.c,740 :: 		command[( i * 2 ) + 4] = p_tech_tab[i];
LSLS	R2, R0, #1
SXTH	R2, R2
ADDS	R2, R2, #4
SXTH	R2, R2
ADD	R4, SP, #4
ADDS	R3, R4, R2
LDR	R2, [SP, #524]
ADDS	R2, R2, R0
LDRB	R2, [R2, #0]
STRB	R2, [R3, #0]
;nfc.c,741 :: 		command[( i * 2 ) + 5] = 0x01;
LSLS	R2, R0, #1
SXTH	R2, R2
ADDS	R2, R2, #5
SXTH	R2, R2
ADDS	R3, R4, R2
MOVS	R2, #1
STRB	R2, [R3, #0]
;nfc.c,738 :: 		for ( i = 0; i < tech_tab_size; i++ )
ADDS	R2, R0, #1
; i end address is: 0 (R0)
; i start address is: 4 (R1)
UXTB	R1, R2
;nfc.c,742 :: 		}
UXTB	R0, R1
; i end address is: 4 (R1)
IT	AL
BAL	L_nfc_start_discovery114
L_nfc_start_discovery115:
;nfc.c,745 :: 		&answer_size ) )
ADDW	R5, SP, #518
;nfc.c,744 :: 		if( host_tx_rx( command, ( tech_tab_size * 2 ) + 4, answer, sizeof( answer ),
ADD	R4, SP, #260
LDRB	R2, [SP, #528]
LSLS	R2, R2, #1
SXTH	R2, R2
ADDS	R3, R2, #4
ADD	R2, SP, #4
UXTH	R1, R3
MOVW	R3, #258
MOV	R0, R2
MOV	R2, R4
;nfc.c,745 :: 		&answer_size ) )
PUSH	(R5)
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_start_discovery117
;nfc.c,746 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_start_discovery
L_nfc_start_discovery117:
;nfc.c,747 :: 		else if ( ( answer[0] != 0x41 ) || ( answer[1] != 0x03 ) ||
ADD	R2, SP, #260
LDRB	R2, [R2, #0]
CMP	R2, #65
IT	NE
BNE	L__nfc_start_discovery205
ADD	R2, SP, #260
ADDS	R2, R2, #1
LDRB	R2, [R2, #0]
CMP	R2, #3
IT	NE
BNE	L__nfc_start_discovery204
;nfc.c,748 :: 		( answer[3] != 0x00 ) )
ADD	R2, SP, #260
ADDS	R2, R2, #3
LDRB	R2, [R2, #0]
CMP	R2, #0
IT	NE
BNE	L__nfc_start_discovery203
IT	AL
BAL	L_nfc_start_discovery121
;nfc.c,747 :: 		else if ( ( answer[0] != 0x41 ) || ( answer[1] != 0x03 ) ||
L__nfc_start_discovery205:
L__nfc_start_discovery204:
;nfc.c,748 :: 		( answer[3] != 0x00 ) )
L__nfc_start_discovery203:
;nfc.c,749 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_start_discovery
L_nfc_start_discovery121:
;nfc.c,751 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,752 :: 		}
L_end_nfc_start_discovery:
LDR	LR, [SP, #0]
ADDW	SP, SP, #540
BX	LR
; end of _nfc_start_discovery
_nfc_restart_discovery:
;nfc.c,754 :: 		int nfc_restart_discovery( void )
SUB	SP, SP, #268
STR	LR, [SP, #0]
;nfc.c,756 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #4
ADD	R10, R11, #264
MOVW	R12, #lo_addr(?ICSnfc_restart_discovery_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_restart_discovery_answer_L0+0)
BL	___CC2DW+0
;nfc.c,757 :: 		uint16_t answer_size = 0;
;nfc.c,758 :: 		uint8_t NCI_RESTART_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x03 };
;nfc.c,761 :: 		answer, sizeof( answer ), &answer_size ) )
ADD	R2, SP, #262
ADD	R1, SP, #4
;nfc.c,760 :: 		if( host_tx_rx( NCI_RESTART_DISCOVERY, sizeof( NCI_RESTART_DISCOVERY ),
ADD	R0, SP, #264
;nfc.c,761 :: 		answer, sizeof( answer ), &answer_size ) )
PUSH	(R2)
MOVW	R3, #258
MOV	R2, R1
;nfc.c,760 :: 		if( host_tx_rx( NCI_RESTART_DISCOVERY, sizeof( NCI_RESTART_DISCOVERY ),
MOVS	R1, #4
;nfc.c,761 :: 		answer, sizeof( answer ), &answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_restart_discovery122
;nfc.c,762 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_restart_discovery
L_nfc_restart_discovery122:
;nfc.c,763 :: 		else if( host_rx( answer, sizeof( answer ), &answer_size, TIMEOUT_1S ) )
ADD	R1, SP, #262
ADD	R0, SP, #4
MOVW	R3, #1000
MOV	R2, R1
MOVW	R1, #258
BL	nfc_host_rx+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_restart_discovery124
;nfc.c,764 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_restart_discovery
L_nfc_restart_discovery124:
;nfc.c,766 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,767 :: 		}
L_end_nfc_restart_discovery:
LDR	LR, [SP, #0]
ADD	SP, SP, #268
BX	LR
; end of _nfc_restart_discovery
_nfc_stop_discovery:
;nfc.c,769 :: 		int nfc_stop_discovery( void )
SUB	SP, SP, #268
STR	LR, [SP, #0]
;nfc.c,771 :: 		uint8_t answer[ANSWER_MAX_SIZE] = {0};
ADD	R11, SP, #4
ADD	R10, R11, #264
MOVW	R12, #lo_addr(?ICSnfc_stop_discovery_answer_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_stop_discovery_answer_L0+0)
BL	___CC2DW+0
;nfc.c,772 :: 		uint16_t answer_size = 0;
;nfc.c,773 :: 		uint8_t NCI_STOP_DISCOVERY[] = { 0x21, 0x06, 0x01, 0x00 };
;nfc.c,776 :: 		answer,sizeof( answer ), &answer_size ) )
ADD	R2, SP, #262
ADD	R1, SP, #4
;nfc.c,775 :: 		if( host_tx_rx( NCI_STOP_DISCOVERY, sizeof( NCI_STOP_DISCOVERY ),
ADD	R0, SP, #264
;nfc.c,776 :: 		answer,sizeof( answer ), &answer_size ) )
PUSH	(R2)
MOVW	R3, #258
MOV	R2, R1
;nfc.c,775 :: 		if( host_tx_rx( NCI_STOP_DISCOVERY, sizeof( NCI_STOP_DISCOVERY ),
MOVS	R1, #4
;nfc.c,776 :: 		answer,sizeof( answer ), &answer_size ) )
BL	nfc_host_tx_rx+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfc_stop_discovery125
;nfc.c,777 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_stop_discovery
L_nfc_stop_discovery125:
;nfc.c,778 :: 		else if( host_rx( answer, sizeof( answer ), &answer_size, TIMEOUT_1S ) )
ADD	R1, SP, #262
ADD	R0, SP, #4
MOVW	R3, #1000
MOV	R2, R1
MOVW	R1, #258
BL	nfc_host_rx+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_stop_discovery127
;nfc.c,779 :: 		return NFC_ERROR;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfc_stop_discovery
L_nfc_stop_discovery127:
;nfc.c,781 :: 		return NFC_SUCCESS;
MOVS	R0, #0
SXTH	R0, R0
;nfc.c,782 :: 		}
L_end_nfc_stop_discovery:
LDR	LR, [SP, #0]
ADD	SP, SP, #268
BX	LR
; end of _nfc_stop_discovery
_nfc_wait_for_discovery_notification:
;nfc.c,786 :: 		void nfc_wait_for_discovery_notification( nfc_interface_t *prf_intf )
; prf_intf start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; prf_intf end address is: 0 (R0)
; prf_intf start address is: 0 (R0)
;nfc.c,789 :: 		uint16_t answer_size = 0;
MOVW	R1, #0
STRH	R1, [SP, #8]
; prf_intf end address is: 0 (R0)
;nfc.c,791 :: 		do
L_nfc_wait_for_discovery_notification128:
;nfc.c,796 :: 		( answer[1] != 0x03 ) ) );
; prf_intf start address is: 0 (R0)
; prf_intf start address is: 0 (R0)
; prf_intf end address is: 0 (R0)
IT	AL
BAL	L__nfc_wait_for_discovery_notification208
L__nfc_wait_for_discovery_notification211:
L__nfc_wait_for_discovery_notification208:
;nfc.c,793 :: 		host_rx( answer, sizeof( answer), &answer_size,
; prf_intf start address is: 0 (R0)
; prf_intf end address is: 0 (R0)
ADD	R1, SP, #8
;nfc.c,794 :: 		TIMEOUT_INFINITE );
STR	R0, [SP, #4]
MOVS	R3, #0
;nfc.c,793 :: 		host_rx( answer, sizeof( answer), &answer_size,
MOV	R2, R1
MOVW	R1, #258
MOVW	R0, #lo_addr(_answer+0)
MOVT	R0, #hi_addr(_answer+0)
;nfc.c,794 :: 		TIMEOUT_INFINITE );
BL	nfc_host_rx+0
LDR	R0, [SP, #4]
;nfc.c,796 :: 		( answer[1] != 0x03 ) ) );
MOVW	R1, #lo_addr(_answer+0)
MOVT	R1, #hi_addr(_answer+0)
LDRB	R1, [R1, #0]
CMP	R1, #97
IT	NE
BNE	L__nfc_wait_for_discovery_notification211
; prf_intf end address is: 0 (R0)
; prf_intf start address is: 0 (R0)
MOVW	R1, #lo_addr(_answer+1)
MOVT	R1, #hi_addr(_answer+1)
LDRB	R1, [R1, #0]
CMP	R1, #5
IT	EQ
BEQ	L__nfc_wait_for_discovery_notification210
MOVW	R1, #lo_addr(_answer+1)
MOVT	R1, #hi_addr(_answer+1)
LDRB	R1, [R1, #0]
CMP	R1, #3
IT	EQ
BEQ	L__nfc_wait_for_discovery_notification209
IT	AL
BAL	L_nfc_wait_for_discovery_notification128
L__nfc_wait_for_discovery_notification210:
L__nfc_wait_for_discovery_notification209:
L__nfc_wait_for_discovery_notification206:
;nfc.c,799 :: 		if( answer[1] == 0x05 )
MOVW	R1, #lo_addr(_answer+1)
MOVT	R1, #hi_addr(_answer+1)
LDRB	R1, [R1, #0]
CMP	R1, #5
IT	NE
BNE	L_nfc_wait_for_discovery_notification135
;nfc.c,801 :: 		prf_intf->interface = answer[4];
MOVW	R1, #lo_addr(_answer+4)
MOVT	R1, #hi_addr(_answer+4)
LDRB	R1, [R1, #0]
STRB	R1, [R0, #0]
;nfc.c,802 :: 		prf_intf->protocol  = answer[5];
ADDS	R2, R0, #1
MOVW	R1, #lo_addr(_answer+5)
MOVT	R1, #hi_addr(_answer+5)
LDRB	R1, [R1, #0]
STRB	R1, [R2, #0]
;nfc.c,803 :: 		prf_intf->mode_tech = answer[6];
ADDS	R2, R0, #2
; prf_intf end address is: 0 (R0)
MOVW	R1, #lo_addr(_answer+6)
MOVT	R1, #hi_addr(_answer+6)
LDRB	R1, [R1, #0]
STRB	R1, [R2, #0]
;nfc.c,804 :: 		} else { /* RF_DISCOVER_NTF */
IT	AL
BAL	L_nfc_wait_for_discovery_notification136
L_nfc_wait_for_discovery_notification135:
;nfc.c,805 :: 		prf_intf->interface = INTF_UNDETERMINED;
; prf_intf start address is: 0 (R0)
MOVS	R1, #0
STRB	R1, [R0, #0]
;nfc.c,806 :: 		prf_intf->protocol = answer[4];
ADDS	R2, R0, #1
MOVW	R1, #lo_addr(_answer+4)
MOVT	R1, #hi_addr(_answer+4)
LDRB	R1, [R1, #0]
STRB	R1, [R2, #0]
;nfc.c,807 :: 		prf_intf->mode_tech = answer[5];
ADDS	R2, R0, #2
; prf_intf end address is: 0 (R0)
MOVW	R1, #lo_addr(_answer+5)
MOVT	R1, #hi_addr(_answer+5)
LDRB	R1, [R1, #0]
STRB	R1, [R2, #0]
;nfc.c,810 :: 		while( answer[answer_size - 1] == 0x02 )
L_nfc_wait_for_discovery_notification137:
LDRH	R1, [SP, #8]
SUBS	R2, R1, #1
UXTH	R2, R2
MOVW	R1, #lo_addr(_answer+0)
MOVT	R1, #hi_addr(_answer+0)
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #2
IT	NE
BNE	L_nfc_wait_for_discovery_notification138
;nfc.c,811 :: 		host_rx( answer, sizeof( answer ), &answer_size, TIMEOUT_1S );
ADD	R1, SP, #8
MOVW	R3, #1000
MOV	R2, R1
MOVW	R1, #258
MOVW	R0, #lo_addr(_answer+0)
MOVT	R0, #hi_addr(_answer+0)
BL	nfc_host_rx+0
IT	AL
BAL	L_nfc_wait_for_discovery_notification137
L_nfc_wait_for_discovery_notification138:
;nfc.c,812 :: 		}
L_nfc_wait_for_discovery_notification136:
;nfc.c,813 :: 		}
L_end_nfc_wait_for_discovery_notification:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _nfc_wait_for_discovery_notification
_nfc_process:
;nfc.c,815 :: 		void nfc_process( uint8_t mode, nfc_interface_t *rf_intf )
; rf_intf start address is: 4 (R1)
; mode start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; rf_intf end address is: 4 (R1)
; mode end address is: 0 (R0)
; mode start address is: 0 (R0)
; rf_intf start address is: 4 (R1)
;nfc.c,817 :: 		switch ( mode )
IT	AL
BAL	L_nfc_process139
; mode end address is: 0 (R0)
;nfc.c,826 :: 		case NFC_MODE_P2P:
L_nfc_process141:
;nfc.c,827 :: 		p2p_mode( rf_intf );
MOV	R0, R1
; rf_intf end address is: 4 (R1)
BL	nfc_p2p_mode+0
;nfc.c,828 :: 		break;
IT	AL
BAL	L_nfc_process140
;nfc.c,832 :: 		case NFC_MODE_RW:
L_nfc_process142:
;nfc.c,833 :: 		reader_mode( rf_intf );
; rf_intf start address is: 4 (R1)
MOV	R0, R1
; rf_intf end address is: 4 (R1)
BL	nfc_reader_mode+0
;nfc.c,834 :: 		break;
IT	AL
BAL	L_nfc_process140
;nfc.c,837 :: 		default:
L_nfc_process143:
;nfc.c,838 :: 		break;
IT	AL
BAL	L_nfc_process140
;nfc.c,839 :: 		}
L_nfc_process139:
; rf_intf start address is: 4 (R1)
; mode start address is: 0 (R0)
CMP	R0, #2
IT	EQ
BEQ	L_nfc_process141
CMP	R0, #4
IT	EQ
BEQ	L_nfc_process142
; mode end address is: 0 (R0)
; rf_intf end address is: 4 (R1)
IT	AL
BAL	L_nfc_process143
L_nfc_process140:
;nfc.c,840 :: 		}
L_end_nfc_process:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _nfc_process
