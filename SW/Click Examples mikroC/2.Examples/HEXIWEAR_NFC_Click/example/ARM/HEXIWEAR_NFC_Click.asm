_auth:
;HEXIWEAR_NFC_Click.c,118 :: 		char *auth( uint8_t x )
; x start address is: 0 (R0)
SUB	SP, SP, #4
; x end address is: 0 (R0)
; x start address is: 0 (R0)
;HEXIWEAR_NFC_Click.c,120 :: 		switch( x )
IT	AL
BAL	L_auth0
; x end address is: 0 (R0)
;HEXIWEAR_NFC_Click.c,122 :: 		case 0x01:
L_auth2:
;HEXIWEAR_NFC_Click.c,123 :: 		return "Open";
MOVW	R0, #lo_addr(?lstr1_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr1_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,124 :: 		case 0x02:
L_auth3:
;HEXIWEAR_NFC_Click.c,125 :: 		return "WPA-Personal";
MOVW	R0, #lo_addr(?lstr2_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr2_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,126 :: 		case 0x04:
L_auth4:
;HEXIWEAR_NFC_Click.c,127 :: 		return "Shared";
MOVW	R0, #lo_addr(?lstr3_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr3_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,128 :: 		case 0x08:
L_auth5:
;HEXIWEAR_NFC_Click.c,129 :: 		return "WPA-Entreprise";
MOVW	R0, #lo_addr(?lstr4_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr4_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,130 :: 		case 0x10:
L_auth6:
;HEXIWEAR_NFC_Click.c,131 :: 		return "WPA2-Entreprise";
MOVW	R0, #lo_addr(?lstr5_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr5_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,132 :: 		case 0x20:
L_auth7:
;HEXIWEAR_NFC_Click.c,133 :: 		return "WPA2-Personal";
MOVW	R0, #lo_addr(?lstr6_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr6_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,134 :: 		default:
L_auth8:
;HEXIWEAR_NFC_Click.c,135 :: 		return "unknown";
MOVW	R0, #lo_addr(?lstr7_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr7_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_auth
;HEXIWEAR_NFC_Click.c,136 :: 		}
L_auth0:
; x start address is: 0 (R0)
CMP	R0, #1
IT	EQ
BEQ	L_auth2
CMP	R0, #2
IT	EQ
BEQ	L_auth3
CMP	R0, #4
IT	EQ
BEQ	L_auth4
CMP	R0, #8
IT	EQ
BEQ	L_auth5
CMP	R0, #16
IT	EQ
BEQ	L_auth6
CMP	R0, #32
IT	EQ
BEQ	L_auth7
; x end address is: 0 (R0)
IT	AL
BAL	L_auth8
;HEXIWEAR_NFC_Click.c,137 :: 		}
L_end_auth:
ADD	SP, SP, #4
BX	LR
; end of _auth
_encrypt:
;HEXIWEAR_NFC_Click.c,139 :: 		char *encrypt( uint8_t x )
; x start address is: 0 (R0)
SUB	SP, SP, #4
; x end address is: 0 (R0)
; x start address is: 0 (R0)
;HEXIWEAR_NFC_Click.c,141 :: 		switch( x )
IT	AL
BAL	L_encrypt9
; x end address is: 0 (R0)
;HEXIWEAR_NFC_Click.c,143 :: 		case 0x01:
L_encrypt11:
;HEXIWEAR_NFC_Click.c,144 :: 		return "None";
MOVW	R0, #lo_addr(?lstr8_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr8_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_encrypt
;HEXIWEAR_NFC_Click.c,145 :: 		case 0x02:
L_encrypt12:
;HEXIWEAR_NFC_Click.c,146 :: 		return "WEP";
MOVW	R0, #lo_addr(?lstr9_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr9_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_encrypt
;HEXIWEAR_NFC_Click.c,147 :: 		case 0x04:
L_encrypt13:
;HEXIWEAR_NFC_Click.c,148 :: 		return "TKIP";
MOVW	R0, #lo_addr(?lstr10_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr10_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_encrypt
;HEXIWEAR_NFC_Click.c,149 :: 		case 0x08:
L_encrypt14:
;HEXIWEAR_NFC_Click.c,150 :: 		return "AES";
MOVW	R0, #lo_addr(?lstr11_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr11_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_encrypt
;HEXIWEAR_NFC_Click.c,151 :: 		case 0x10:
L_encrypt15:
;HEXIWEAR_NFC_Click.c,152 :: 		return "AES/TKIP";
MOVW	R0, #lo_addr(?lstr12_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr12_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_encrypt
;HEXIWEAR_NFC_Click.c,153 :: 		default:
L_encrypt16:
;HEXIWEAR_NFC_Click.c,154 :: 		return "unknown";
MOVW	R0, #lo_addr(?lstr13_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr13_HEXIWEAR_NFC_Click+0)
IT	AL
BAL	L_end_encrypt
;HEXIWEAR_NFC_Click.c,155 :: 		}
L_encrypt9:
; x start address is: 0 (R0)
CMP	R0, #1
IT	EQ
BEQ	L_encrypt11
CMP	R0, #2
IT	EQ
BEQ	L_encrypt12
CMP	R0, #4
IT	EQ
BEQ	L_encrypt13
CMP	R0, #8
IT	EQ
BEQ	L_encrypt14
CMP	R0, #16
IT	EQ
BEQ	L_encrypt15
; x end address is: 0 (R0)
IT	AL
BAL	L_encrypt16
;HEXIWEAR_NFC_Click.c,156 :: 		}
L_end_encrypt:
ADD	SP, SP, #4
BX	LR
; end of _encrypt
_ndef_pull_cb:
;HEXIWEAR_NFC_Click.c,160 :: 		void ndef_pull_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size )
; p_ndef_record start address is: 0 (R0)
SUB	SP, SP, #92
STR	LR, [SP, #0]
; p_ndef_record end address is: 0 (R0)
; p_ndef_record start address is: 0 (R0)
;HEXIWEAR_NFC_Click.c,167 :: 		if( p_ndef_record[0] == 0xD1 )
LDRB	R2, [R0, #0]
CMP	R2, #209
IT	NE
BNE	L_ndef_pull_cb17
;HEXIWEAR_NFC_Click.c,169 :: 		switch( p_ndef_record[3] )
ADDS	R2, R0, #3
STR	R2, [SP, #88]
IT	AL
BAL	L_ndef_pull_cb18
;HEXIWEAR_NFC_Click.c,171 :: 		case 'T':
L_ndef_pull_cb20:
;HEXIWEAR_NFC_Click.c,172 :: 		p_ndef_record[7 + p_ndef_record[2]] = '\0';
ADDS	R2, R0, #2
LDRB	R2, [R2, #0]
ADDS	R2, R2, #7
SXTH	R2, R2
ADDS	R3, R0, R2
MOVS	R2, #0
STRB	R2, [R3, #0]
;HEXIWEAR_NFC_Click.c,177 :: 		&p_ndef_record[7] );
ADDS	R6, R0, #7
;HEXIWEAR_NFC_Click.c,176 :: 		p_ndef_record[6],
ADDS	R2, R0, #6
LDRB	R2, [R2, #0]
UXTB	R5, R2
;HEXIWEAR_NFC_Click.c,175 :: 		p_ndef_record[5],
ADDS	R2, R0, #5
LDRB	R2, [R2, #0]
UXTB	R4, R2
;HEXIWEAR_NFC_Click.c,174 :: 		"   Text record (language = %c%c): %s\n",
MOVW	R3, #lo_addr(?lstr_14_HEXIWEAR_NFC_Click+0)
MOVT	R3, #hi_addr(?lstr_14_HEXIWEAR_NFC_Click+0)
;HEXIWEAR_NFC_Click.c,173 :: 		sprinti( tmp_txt,
ADD	R2, SP, #8
;HEXIWEAR_NFC_Click.c,177 :: 		&p_ndef_record[7] );
STR	R0, [SP, #4]
PUSH	(R6)
;HEXIWEAR_NFC_Click.c,176 :: 		p_ndef_record[6],
PUSH	(R5)
;HEXIWEAR_NFC_Click.c,175 :: 		p_ndef_record[5],
PUSH	(R4)
;HEXIWEAR_NFC_Click.c,174 :: 		"   Text record (language = %c%c): %s\n",
PUSH	(R3)
;HEXIWEAR_NFC_Click.c,173 :: 		sprinti( tmp_txt,
PUSH	(R2)
;HEXIWEAR_NFC_Click.c,177 :: 		&p_ndef_record[7] );
BL	_sprinti+0
ADD	SP, SP, #20
;HEXIWEAR_NFC_Click.c,180 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
MOVW	R2, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R2, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVW	R1, #31695
MOV	R0, R2
MOVS	R2, #0
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,181 :: 		OLED_WriteText("Text record:", 4, 55);
MOVW	R2, #lo_addr(?lstr15_HEXIWEAR_NFC_Click+0)
MOVT	R2, #hi_addr(?lstr15_HEXIWEAR_NFC_Click+0)
MOVS	R1, #4
MOV	R0, R2
MOVS	R2, #55
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,182 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
MOVW	R2, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R2, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVW	R1, #65535
MOV	R0, R2
MOVS	R2, #0
BL	_OLED_SetFont+0
LDR	R0, [SP, #4]
;HEXIWEAR_NFC_Click.c,183 :: 		OLED_WriteText(&p_ndef_record[7], 4, 70);
ADDS	R2, R0, #7
; p_ndef_record end address is: 0 (R0)
MOVS	R1, #4
MOV	R0, R2
MOVS	R2, #70
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,185 :: 		break;
IT	AL
BAL	L_ndef_pull_cb19
;HEXIWEAR_NFC_Click.c,187 :: 		case 'U':
L_ndef_pull_cb21:
;HEXIWEAR_NFC_Click.c,189 :: 		NDEF_PRINT_URI_CODE( p_ndef_record[4] )
; p_ndef_record start address is: 0 (R0)
ADDS	R3, R0, #4
IT	AL
BAL	L_ndef_pull_cb22
L_ndef_pull_cb24:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb25:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb26:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb27:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb28:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb29:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb30:
IT	AL
BAL	L_ndef_pull_cb23
L_ndef_pull_cb22:
LDRB	R2, [R3, #0]
CMP	R2, #1
IT	EQ
BEQ	L_ndef_pull_cb24
LDRB	R2, [R3, #0]
CMP	R2, #2
IT	EQ
BEQ	L_ndef_pull_cb25
LDRB	R2, [R3, #0]
CMP	R2, #3
IT	EQ
BEQ	L_ndef_pull_cb26
LDRB	R2, [R3, #0]
CMP	R2, #4
IT	EQ
BEQ	L_ndef_pull_cb27
LDRB	R2, [R3, #0]
CMP	R2, #5
IT	EQ
BEQ	L_ndef_pull_cb28
LDRB	R2, [R3, #0]
CMP	R2, #6
IT	EQ
BEQ	L_ndef_pull_cb29
IT	AL
BAL	L_ndef_pull_cb30
L_ndef_pull_cb23:
;HEXIWEAR_NFC_Click.c,190 :: 		p_ndef_record[4 + p_ndef_record[2]] = '\0';
ADDS	R2, R0, #2
LDRB	R2, [R2, #0]
ADDS	R2, R2, #4
SXTH	R2, R2
ADDS	R3, R0, R2
MOVS	R2, #0
STRB	R2, [R3, #0]
;HEXIWEAR_NFC_Click.c,191 :: 		sprinti( tmp_txt, "%s\n", &p_ndef_record[5] );
ADDS	R4, R0, #5
; p_ndef_record end address is: 0 (R0)
MOVW	R3, #lo_addr(?lstr_16_HEXIWEAR_NFC_Click+0)
MOVT	R3, #hi_addr(?lstr_16_HEXIWEAR_NFC_Click+0)
ADD	R2, SP, #8
PUSH	(R4)
PUSH	(R3)
PUSH	(R2)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,194 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
MOVW	R2, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R2, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVW	R1, #31695
MOV	R0, R2
MOVS	R2, #0
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,195 :: 		OLED_WriteText("URI record:", 4, 55);
MOVW	R2, #lo_addr(?lstr17_HEXIWEAR_NFC_Click+0)
MOVT	R2, #hi_addr(?lstr17_HEXIWEAR_NFC_Click+0)
MOVS	R1, #4
MOV	R0, R2
MOVS	R2, #55
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,196 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
MOVW	R2, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R2, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVW	R1, #65535
MOV	R0, R2
MOVS	R2, #0
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,197 :: 		OLED_WriteText(tmp_txt, 4, 70);
ADD	R2, SP, #8
MOVS	R1, #4
MOV	R0, R2
MOVS	R2, #70
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,199 :: 		break;
IT	AL
BAL	L_ndef_pull_cb19
;HEXIWEAR_NFC_Click.c,201 :: 		default:
L_ndef_pull_cb31:
;HEXIWEAR_NFC_Click.c,202 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
MOVW	R2, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R2, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVW	R1, #31695
MOV	R0, R2
MOVS	R2, #0
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,203 :: 		OLED_WriteText("Unsupported", 4, 55);
MOVW	R2, #lo_addr(?lstr18_HEXIWEAR_NFC_Click+0)
MOVT	R2, #hi_addr(?lstr18_HEXIWEAR_NFC_Click+0)
MOVS	R1, #4
MOV	R0, R2
MOVS	R2, #55
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,205 :: 		break;
IT	AL
BAL	L_ndef_pull_cb19
;HEXIWEAR_NFC_Click.c,206 :: 		}
L_ndef_pull_cb18:
; p_ndef_record start address is: 0 (R0)
LDR	R3, [SP, #88]
LDRB	R2, [R3, #0]
CMP	R2, #84
IT	EQ
BEQ	L_ndef_pull_cb20
LDRB	R2, [R3, #0]
CMP	R2, #85
IT	EQ
BEQ	L_ndef_pull_cb21
; p_ndef_record end address is: 0 (R0)
IT	AL
BAL	L_ndef_pull_cb31
L_ndef_pull_cb19:
;HEXIWEAR_NFC_Click.c,207 :: 		}
IT	AL
BAL	L_ndef_pull_cb32
L_ndef_pull_cb17:
;HEXIWEAR_NFC_Click.c,269 :: 		;
L_ndef_pull_cb32:
;HEXIWEAR_NFC_Click.c,273 :: 		}
L_end_ndef_pull_cb:
LDR	LR, [SP, #0]
ADD	SP, SP, #92
BX	LR
; end of _ndef_pull_cb
_ndef_push_cb:
;HEXIWEAR_NFC_Click.c,277 :: 		void ndef_push_cb( uint8_t *p_ndef_record, uint16_t ndef_record_size )
SUB	SP, SP, #4
;HEXIWEAR_NFC_Click.c,280 :: 		}
L_end_ndef_push_cb:
ADD	SP, SP, #4
BX	LR
; end of _ndef_push_cb
_mi_fare_scenario:
;HEXIWEAR_NFC_Click.c,284 :: 		void mi_fare_scenario()
SUB	SP, SP, #380
STR	LR, [SP, #0]
;HEXIWEAR_NFC_Click.c,291 :: 		uint8_t auth[] = {0x40, 0x01, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
ADDW	R11, SP, #345
ADD	R10, R11, #32
MOVW	R12, #lo_addr(?ICSmi_fare_scenario_auth_L0+0)
MOVT	R12, #hi_addr(?ICSmi_fare_scenario_auth_L0+0)
BL	___CC2DW+0
;HEXIWEAR_NFC_Click.c,293 :: 		uint8_t read[] = {0x10, 0x30, 0x04};
;HEXIWEAR_NFC_Click.c,295 :: 		uint8_t write_part1[] = {0x10, 0xA0, 0x04};
;HEXIWEAR_NFC_Click.c,300 :: 		};
;HEXIWEAR_NFC_Click.c,304 :: 		status = nfc_reader_tag_cmd( auth, sizeof( auth ), resp, &resp_size );
ADD	R2, SP, #264
ADD	R1, SP, #8
ADDW	R0, SP, #345
MOV	R3, R2
MOV	R2, R1
MOVS	R1, #9
BL	_nfc_reader_tag_cmd+0
;HEXIWEAR_NFC_Click.c,306 :: 		if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
UXTB	R0, R0
CMP	R0, #1
IT	EQ
BEQ	L__mi_fare_scenario99
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L__mi_fare_scenario98
IT	AL
BAL	L_mi_fare_scenario35
L__mi_fare_scenario99:
L__mi_fare_scenario98:
;HEXIWEAR_NFC_Click.c,309 :: 		auth[1], resp[resp_size - 1] );
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R3, R0
ADDW	R0, SP, #345
ADDS	R0, R0, #1
LDRB	R0, [R0, #0]
UXTB	R2, R0
;HEXIWEAR_NFC_Click.c,308 :: 		sprinti( tmp_txt, " Authenticate sector %d failed with error 0x%02x\n",
MOVW	R1, #lo_addr(?lstr_19_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_19_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
;HEXIWEAR_NFC_Click.c,309 :: 		auth[1], resp[resp_size - 1] );
PUSH	(R3)
PUSH	(R2)
;HEXIWEAR_NFC_Click.c,308 :: 		sprinti( tmp_txt, " Authenticate sector %d failed with error 0x%02x\n",
PUSH	(R1)
PUSH	(R0)
;HEXIWEAR_NFC_Click.c,309 :: 		auth[1], resp[resp_size - 1] );
BL	_sprinti+0
ADD	SP, SP, #16
;HEXIWEAR_NFC_Click.c,311 :: 		return;
IT	AL
BAL	L_end_mi_fare_scenario
;HEXIWEAR_NFC_Click.c,312 :: 		}
L_mi_fare_scenario35:
;HEXIWEAR_NFC_Click.c,313 :: 		sprinti( tmp_txt, " Authenticate sector %d succeed\n", auth[1] );
ADDW	R0, SP, #345
ADDS	R0, R0, #1
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_20_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_20_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,317 :: 		status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );
ADD	R2, SP, #264
ADD	R1, SP, #8
ADD	R0, SP, #354
MOV	R3, R2
MOV	R2, R1
MOVS	R1, #3
BL	_nfc_reader_tag_cmd+0
;HEXIWEAR_NFC_Click.c,319 :: 		if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
UXTB	R0, R0
CMP	R0, #1
IT	EQ
BEQ	L__mi_fare_scenario101
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L__mi_fare_scenario100
IT	AL
BAL	L_mi_fare_scenario38
L__mi_fare_scenario101:
L__mi_fare_scenario100:
;HEXIWEAR_NFC_Click.c,322 :: 		read[2], resp[resp_size - 1] );
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R3, R0
ADD	R0, SP, #354
ADDS	R0, R0, #2
LDRB	R0, [R0, #0]
UXTB	R2, R0
;HEXIWEAR_NFC_Click.c,321 :: 		sprinti( tmp_txt, " Read block %d failed with error 0x%02x\n",
MOVW	R1, #lo_addr(?lstr_21_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_21_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
;HEXIWEAR_NFC_Click.c,322 :: 		read[2], resp[resp_size - 1] );
PUSH	(R3)
PUSH	(R2)
;HEXIWEAR_NFC_Click.c,321 :: 		sprinti( tmp_txt, " Read block %d failed with error 0x%02x\n",
PUSH	(R1)
PUSH	(R0)
;HEXIWEAR_NFC_Click.c,322 :: 		read[2], resp[resp_size - 1] );
BL	_sprinti+0
ADD	SP, SP, #16
;HEXIWEAR_NFC_Click.c,324 :: 		return;
IT	AL
BAL	L_end_mi_fare_scenario
;HEXIWEAR_NFC_Click.c,325 :: 		}
L_mi_fare_scenario38:
;HEXIWEAR_NFC_Click.c,327 :: 		sprinti( tmp_txt, " Read block %d: ", read[2] );
ADD	R0, SP, #354
ADDS	R0, R0, #2
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_22_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_22_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,330 :: 		for( i = 0; i < resp_size - 2; i++ )
; i start address is: 12 (R3)
MOVS	R3, #0
; i end address is: 12 (R3)
L_mi_fare_scenario39:
; i start address is: 12 (R3)
LDRB	R0, [SP, #264]
SUBS	R0, R0, #2
SXTH	R0, R0
CMP	R3, R0
IT	GE
BGE	L_mi_fare_scenario40
;HEXIWEAR_NFC_Click.c,332 :: 		sprinti( tmp_txt, "0x%02X ", resp[i + 1] );
ADDS	R1, R3, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_23_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_23_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
STRB	R3, [SP, #4]
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
LDRB	R3, [SP, #4]
;HEXIWEAR_NFC_Click.c,330 :: 		for( i = 0; i < resp_size - 2; i++ )
ADDS	R3, R3, #1
UXTB	R3, R3
;HEXIWEAR_NFC_Click.c,334 :: 		}
; i end address is: 12 (R3)
IT	AL
BAL	L_mi_fare_scenario39
L_mi_fare_scenario40:
;HEXIWEAR_NFC_Click.c,339 :: 		&resp_size );
ADD	R2, SP, #264
;HEXIWEAR_NFC_Click.c,338 :: 		status = nfc_reader_tag_cmd( write_part1, sizeof( write_part1 ), resp,
ADD	R1, SP, #8
ADDW	R0, SP, #357
;HEXIWEAR_NFC_Click.c,339 :: 		&resp_size );
MOV	R3, R2
;HEXIWEAR_NFC_Click.c,338 :: 		status = nfc_reader_tag_cmd( write_part1, sizeof( write_part1 ), resp,
MOV	R2, R1
MOVS	R1, #3
;HEXIWEAR_NFC_Click.c,339 :: 		&resp_size );
BL	_nfc_reader_tag_cmd+0
;HEXIWEAR_NFC_Click.c,341 :: 		if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
UXTB	R0, R0
CMP	R0, #1
IT	EQ
BEQ	L__mi_fare_scenario103
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L__mi_fare_scenario102
IT	AL
BAL	L_mi_fare_scenario44
L__mi_fare_scenario103:
L__mi_fare_scenario102:
;HEXIWEAR_NFC_Click.c,344 :: 		write_part1[2], resp[resp_size - 1] );
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R3, R0
ADDW	R0, SP, #357
ADDS	R0, R0, #2
LDRB	R0, [R0, #0]
UXTB	R2, R0
;HEXIWEAR_NFC_Click.c,343 :: 		sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
MOVW	R1, #lo_addr(?lstr_24_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_24_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
;HEXIWEAR_NFC_Click.c,344 :: 		write_part1[2], resp[resp_size - 1] );
PUSH	(R3)
PUSH	(R2)
;HEXIWEAR_NFC_Click.c,343 :: 		sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
PUSH	(R1)
PUSH	(R0)
;HEXIWEAR_NFC_Click.c,344 :: 		write_part1[2], resp[resp_size - 1] );
BL	_sprinti+0
ADD	SP, SP, #16
;HEXIWEAR_NFC_Click.c,346 :: 		return;
IT	AL
BAL	L_end_mi_fare_scenario
;HEXIWEAR_NFC_Click.c,347 :: 		}
L_mi_fare_scenario44:
;HEXIWEAR_NFC_Click.c,349 :: 		&resp_size );
ADD	R2, SP, #264
;HEXIWEAR_NFC_Click.c,348 :: 		status = nfc_reader_tag_cmd( write_part2, sizeof( write_part2 ), resp,
ADD	R1, SP, #8
ADD	R0, SP, #360
;HEXIWEAR_NFC_Click.c,349 :: 		&resp_size );
MOV	R3, R2
;HEXIWEAR_NFC_Click.c,348 :: 		status = nfc_reader_tag_cmd( write_part2, sizeof( write_part2 ), resp,
MOV	R2, R1
MOVS	R1, #17
;HEXIWEAR_NFC_Click.c,349 :: 		&resp_size );
BL	_nfc_reader_tag_cmd+0
;HEXIWEAR_NFC_Click.c,351 :: 		if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
UXTB	R0, R0
CMP	R0, #1
IT	EQ
BEQ	L__mi_fare_scenario105
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L__mi_fare_scenario104
IT	AL
BAL	L_mi_fare_scenario47
L__mi_fare_scenario105:
L__mi_fare_scenario104:
;HEXIWEAR_NFC_Click.c,355 :: 		resp[resp_size - 1] );
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R3, R0
;HEXIWEAR_NFC_Click.c,354 :: 		write_part1[2],
ADDW	R0, SP, #357
ADDS	R0, R0, #2
LDRB	R0, [R0, #0]
UXTB	R2, R0
;HEXIWEAR_NFC_Click.c,353 :: 		sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
MOVW	R1, #lo_addr(?lstr_25_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_25_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
;HEXIWEAR_NFC_Click.c,355 :: 		resp[resp_size - 1] );
PUSH	(R3)
;HEXIWEAR_NFC_Click.c,354 :: 		write_part1[2],
PUSH	(R2)
;HEXIWEAR_NFC_Click.c,353 :: 		sprinti( tmp_txt, " Write block %d failed with error 0x%02x\n",
PUSH	(R1)
PUSH	(R0)
;HEXIWEAR_NFC_Click.c,355 :: 		resp[resp_size - 1] );
BL	_sprinti+0
ADD	SP, SP, #16
;HEXIWEAR_NFC_Click.c,357 :: 		return;
IT	AL
BAL	L_end_mi_fare_scenario
;HEXIWEAR_NFC_Click.c,358 :: 		}
L_mi_fare_scenario47:
;HEXIWEAR_NFC_Click.c,360 :: 		sprinti( tmp_txt, " Block %d written\n", write_part1[2] );
ADDW	R0, SP, #357
ADDS	R0, R0, #2
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_26_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_26_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,363 :: 		status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );
ADD	R2, SP, #264
ADD	R1, SP, #8
ADD	R0, SP, #354
MOV	R3, R2
MOV	R2, R1
MOVS	R1, #3
BL	_nfc_reader_tag_cmd+0
;HEXIWEAR_NFC_Click.c,365 :: 		if( ( status == 1 ) || ( resp[resp_size - 1] != 0 ) )
UXTB	R0, R0
CMP	R0, #1
IT	EQ
BEQ	L__mi_fare_scenario107
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	NE
BNE	L__mi_fare_scenario106
IT	AL
BAL	L_mi_fare_scenario50
L__mi_fare_scenario107:
L__mi_fare_scenario106:
;HEXIWEAR_NFC_Click.c,367 :: 		sprinti( tmp_txt, " Read failed with error 0x%02x\n", resp[resp_size - 1] );
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_27_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_27_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,369 :: 		return;
IT	AL
BAL	L_end_mi_fare_scenario
;HEXIWEAR_NFC_Click.c,370 :: 		}
L_mi_fare_scenario50:
;HEXIWEAR_NFC_Click.c,372 :: 		sprinti( tmp_txt, " Read block %d: ", read[2] );
ADD	R0, SP, #354
ADDS	R0, R0, #2
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_28_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_28_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,375 :: 		for( i = 0; i < resp_size - 2; i++ )
; i start address is: 12 (R3)
MOVS	R3, #0
; i end address is: 12 (R3)
L_mi_fare_scenario51:
; i start address is: 12 (R3)
LDRB	R0, [SP, #264]
SUBS	R0, R0, #2
SXTH	R0, R0
CMP	R3, R0
IT	GE
BGE	L_mi_fare_scenario52
;HEXIWEAR_NFC_Click.c,377 :: 		sprinti( tmp_txt, "0x%02X ", resp[i + 1] );
ADDS	R1, R3, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
UXTB	R2, R0
MOVW	R1, #lo_addr(?lstr_29_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr_29_HEXIWEAR_NFC_Click+0)
ADDW	R0, SP, #265
STRB	R3, [SP, #4]
PUSH	(R2)
PUSH	(R1)
PUSH	(R0)
BL	_sprinti+0
ADD	SP, SP, #12
LDRB	R3, [SP, #4]
;HEXIWEAR_NFC_Click.c,375 :: 		for( i = 0; i < resp_size - 2; i++ )
ADDS	R3, R3, #1
UXTB	R3, R3
;HEXIWEAR_NFC_Click.c,379 :: 		}
; i end address is: 12 (R3)
IT	AL
BAL	L_mi_fare_scenario51
L_mi_fare_scenario52:
;HEXIWEAR_NFC_Click.c,383 :: 		while( 1 )
L_mi_fare_scenario54:
;HEXIWEAR_NFC_Click.c,385 :: 		Delay_ms( 500 );
MOVW	R7, #11518
MOVT	R7, #305
NOP
NOP
L_mi_fare_scenario56:
SUBS	R7, R7, #1
BNE	L_mi_fare_scenario56
NOP
NOP
NOP
;HEXIWEAR_NFC_Click.c,386 :: 		status = nfc_reader_tag_cmd( read, sizeof( read ), resp, &resp_size );
ADD	R2, SP, #264
ADD	R1, SP, #8
ADD	R0, SP, #354
MOV	R3, R2
MOV	R2, R1
MOVS	R1, #3
BL	_nfc_reader_tag_cmd+0
;HEXIWEAR_NFC_Click.c,388 :: 		if( ( status == 1 ) || ( resp[resp_size - 1] == 0xb2 ) )
UXTB	R0, R0
CMP	R0, #1
IT	EQ
BEQ	L__mi_fare_scenario109
LDRB	R0, [SP, #264]
SUBS	R1, R0, #1
SXTH	R1, R1
ADD	R0, SP, #8
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
CMP	R0, #178
IT	EQ
BEQ	L__mi_fare_scenario108
IT	AL
BAL	L_mi_fare_scenario60
L__mi_fare_scenario109:
L__mi_fare_scenario108:
;HEXIWEAR_NFC_Click.c,389 :: 		break;
IT	AL
BAL	L_mi_fare_scenario55
L_mi_fare_scenario60:
;HEXIWEAR_NFC_Click.c,390 :: 		}
IT	AL
BAL	L_mi_fare_scenario54
L_mi_fare_scenario55:
;HEXIWEAR_NFC_Click.c,391 :: 		}
L_end_mi_fare_scenario:
LDR	LR, [SP, #0]
ADD	SP, SP, #380
BX	LR
; end of _mi_fare_scenario
_init_ExtPinInt:
;HEXIWEAR_NFC_Click.c,393 :: 		void init_ExtPinInt()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_NFC_Click.c,395 :: 		GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);
MOV	R1, #8192
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Input+0
;HEXIWEAR_NFC_Click.c,396 :: 		NVIC_IntEnable( IVT_INT_PORTB );
MOVW	R0, #76
BL	_NVIC_IntEnable+0
;HEXIWEAR_NFC_Click.c,398 :: 		PORTB_PCR13 &= 0xFFF0FFFF;
MOVW	R0, #lo_addr(PORTB_PCR13+0)
MOVT	R0, #hi_addr(PORTB_PCR13+0)
LDR	R1, [R0, #0]
MVN	R0, #983040
ANDS	R1, R0
MOVW	R0, #lo_addr(PORTB_PCR13+0)
MOVT	R0, #hi_addr(PORTB_PCR13+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,399 :: 		PORTB_PCR13 |= (((unsigned long)0x9) << 16);
MOVW	R0, #lo_addr(PORTB_PCR13+0)
MOVT	R0, #hi_addr(PORTB_PCR13+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #589824
MOVW	R0, #lo_addr(PORTB_PCR13+0)
MOVT	R0, #hi_addr(PORTB_PCR13+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,400 :: 		}
L_end_init_ExtPinInt:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _init_ExtPinInt
_init_timer2:
;HEXIWEAR_NFC_Click.c,403 :: 		void init_timer2()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_NFC_Click.c,406 :: 		LPTMR_bit = 1;
MOVS	R2, #1
SXTB	R2, R2
MOVW	R0, #lo_addr(LPTMR_bit+0)
MOVT	R0, #hi_addr(LPTMR_bit+0)
STR	R2, [R0, #0]
;HEXIWEAR_NFC_Click.c,409 :: 		LPTMR0_PSR = 0XD;
MOVS	R1, #13
MOVW	R0, #lo_addr(LPTMR0_PSR+0)
MOVT	R0, #hi_addr(LPTMR0_PSR+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,412 :: 		LPTMR0_CSR = 0X40;
MOVS	R1, #64
MOVW	R0, #lo_addr(LPTMR0_CSR+0)
MOVT	R0, #hi_addr(LPTMR0_CSR+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,415 :: 		TIE_LPTMR0_CSR_bit = 1;
MOVW	R0, #lo_addr(TIE_LPTMR0_CSR_bit+0)
MOVT	R0, #hi_addr(TIE_LPTMR0_CSR_bit+0)
STR	R2, [R0, #0]
;HEXIWEAR_NFC_Click.c,416 :: 		NVIC_IntEnable( IVT_INT_LPTimer );
MOVW	R0, #74
BL	_NVIC_IntEnable+0
;HEXIWEAR_NFC_Click.c,419 :: 		LPTMR0_CMR = 10;
MOVS	R1, #10
MOVW	R0, #lo_addr(LPTMR0_CMR+0)
MOVT	R0, #hi_addr(LPTMR0_CMR+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,422 :: 		TEN_LPTMR0_CSR_bit = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(TEN_LPTMR0_CSR_bit+0)
MOVT	R0, #hi_addr(TEN_LPTMR0_CSR_bit+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,424 :: 		}
L_end_init_timer2:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _init_timer2
_system_init:
;HEXIWEAR_NFC_Click.c,426 :: 		int system_init()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;HEXIWEAR_NFC_Click.c,428 :: 		uint8_t mode = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;HEXIWEAR_NFC_Click.c,430 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_NFC_Click.c,431 :: 		OLED_DrawImage(NFC_bmp, 0, 0);
MOVW	R0, #lo_addr(_NFC_bmp+0)
MOVT	R0, #hi_addr(_NFC_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_NFC_Click.c,433 :: 		GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11);
MOV	R1, #2048
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_NFC_Click.c,435 :: 		GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_11);
MOV	R1, #2048
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_NFC_Click.c,440 :: 		Delay_ms( 100 );
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_system_init61:
SUBS	R7, R7, #1
BNE	L_system_init61
NOP
NOP
NOP
;HEXIWEAR_NFC_Click.c,444 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
MOVW	R0, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,445 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,446 :: 		OLED_WriteText("Start Test Loop", 4, 80);
MOVW	R0, #lo_addr(?lstr30_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr30_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,448 :: 		I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #34464
MOVT	R0, #1
BL	_I2C0_Init_Advanced+0
;HEXIWEAR_NFC_Click.c,450 :: 		Delay_ms( 100 );
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_system_init63:
SUBS	R7, R7, #1
BNE	L_system_init63
NOP
NOP
NOP
;HEXIWEAR_NFC_Click.c,458 :: 		init_ExtPinInt();
BL	_init_ExtPinInt+0
;HEXIWEAR_NFC_Click.c,459 :: 		init_timer2();
BL	_init_timer2+0
;HEXIWEAR_NFC_Click.c,460 :: 		EnableInterrupts();
BL	_EnableInterrupts+0
;HEXIWEAR_NFC_Click.c,471 :: 		( void * )ndef_push_cb );
MOVW	R0, #lo_addr(_ndef_push_cb+0)
MOVT	R0, #hi_addr(_ndef_push_cb+0)
MOV	R2, R0
;HEXIWEAR_NFC_Click.c,470 :: 		p2p_ndef_set_record( ( uint8_t * )NDEF_RECORD, sizeof( NDEF_RECORD ),
MOVS	R1, #11
MOVW	R0, #lo_addr(_NDEF_RECORD+0)
MOVT	R0, #hi_addr(_NDEF_RECORD+0)
;HEXIWEAR_NFC_Click.c,471 :: 		( void * )ndef_push_cb );
BL	_p2p_ndef_set_record+0
;HEXIWEAR_NFC_Click.c,474 :: 		p2p_ndef_register_pull_callback( ( void * )ndef_pull_cb );
MOVW	R0, #lo_addr(_ndef_pull_cb+0)
MOVT	R0, #hi_addr(_ndef_pull_cb+0)
BL	_p2p_ndef_register_pull_callback+0
;HEXIWEAR_NFC_Click.c,479 :: 		rw_ndef_register_pull_callback( ( void * )ndef_pull_cb );
MOVW	R0, #lo_addr(_ndef_pull_cb+0)
MOVT	R0, #hi_addr(_ndef_pull_cb+0)
BL	_rw_ndef_register_pull_callback+0
;HEXIWEAR_NFC_Click.c,486 :: 		mode |= NFC_MODE_P2P;
LDRB	R0, [SP, #4]
ORR	R0, R0, #2
UXTB	R0, R0
;HEXIWEAR_NFC_Click.c,489 :: 		mode |= NFC_MODE_RW;
ORR	R0, R0, #4
STRB	R0, [SP, #4]
;HEXIWEAR_NFC_Click.c,493 :: 		if( nfc_init( NFC_I2C_SLAVE ) )
MOVS	R0, #40
BL	_nfc_init+0
CMP	R0, #0
IT	EQ
BEQ	L_system_init65
;HEXIWEAR_NFC_Click.c,496 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,497 :: 		OLED_WriteText("Error!", 4, 80);
MOVW	R0, #lo_addr(?lstr31_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr31_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,498 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_system_init
;HEXIWEAR_NFC_Click.c,499 :: 		}
L_system_init65:
;HEXIWEAR_NFC_Click.c,500 :: 		else if( nfc_configure( mode ) )
LDRB	R0, [SP, #4]
BL	_nfc_configure+0
CMP	R0, #0
IT	EQ
BEQ	L_system_init67
;HEXIWEAR_NFC_Click.c,503 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,504 :: 		OLED_WriteText("Error!", 4, 80);
MOVW	R0, #lo_addr(?lstr32_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr32_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,505 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_system_init
;HEXIWEAR_NFC_Click.c,506 :: 		}
L_system_init67:
;HEXIWEAR_NFC_Click.c,507 :: 		else if( nfc_start_discovery( discovery_technologies, sizeof( discovery_technologies ) ) ) {
MOVS	R1, #8
MOVW	R0, #lo_addr(_discovery_technologies+0)
MOVT	R0, #hi_addr(_discovery_technologies+0)
BL	_nfc_start_discovery+0
CMP	R0, #0
IT	EQ
BEQ	L_system_init69
;HEXIWEAR_NFC_Click.c,509 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,510 :: 		OLED_WriteText("Error!", 4, 80);
MOVW	R0, #lo_addr(?lstr33_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr33_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,511 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_system_init
;HEXIWEAR_NFC_Click.c,512 :: 		}
L_system_init69:
;HEXIWEAR_NFC_Click.c,515 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,516 :: 		OLED_WriteText("Success!", 4, 80);
MOVW	R0, #lo_addr(?lstr34_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr34_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,517 :: 		incoming_flag = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_incoming_flag+0)
MOVT	R0, #hi_addr(_incoming_flag+0)
STRB	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,518 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;HEXIWEAR_NFC_Click.c,519 :: 		}
L_end_system_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _system_init
_process_radio:
;HEXIWEAR_NFC_Click.c,521 :: 		void process_radio( nfc_interface_t *radio )
SUB	SP, SP, #88
STR	LR, [SP, #0]
STR	R0, [SP, #84]
;HEXIWEAR_NFC_Click.c,535 :: 		if( radio->interface == INTF_NFCDEP )
LDR	R1, [SP, #84]
LDRB	R1, [R1, #0]
CMP	R1, #3
IT	NE
BNE	L_process_radio70
;HEXIWEAR_NFC_Click.c,538 :: 		if( ( radio->mode_tech & MODE_LISTEN ) == MODE_LISTEN )
LDR	R1, [SP, #84]
ADDS	R1, R1, #2
LDRB	R1, [R1, #0]
AND	R1, R1, #128
UXTB	R1, R1
CMP	R1, #128
IT	NE
BNE	L_process_radio71
;HEXIWEAR_NFC_Click.c,539 :: 		;//UART_Write_Text( " - P2P TARGET MODE: Activated from remote Initiator\r\n" );
IT	AL
BAL	L_process_radio72
L_process_radio71:
;HEXIWEAR_NFC_Click.c,541 :: 		;//UART_Write_Text( " - P2P INITIATOR MODE: Remote Target activated\r\n" );
L_process_radio72:
;HEXIWEAR_NFC_Click.c,543 :: 		nfc_process( NFC_MODE_P2P, radio );
LDR	R1, [SP, #84]
MOVS	R0, #2
BL	_nfc_process+0
;HEXIWEAR_NFC_Click.c,545 :: 		}
IT	AL
BAL	L_process_radio73
L_process_radio70:
;HEXIWEAR_NFC_Click.c,549 :: 		if( ( radio->mode_tech & MODE_MASK ) == MODE_POLL )
LDR	R1, [SP, #84]
ADDS	R1, R1, #2
LDRB	R1, [R1, #0]
AND	R1, R1, #240
UXTB	R1, R1
CMP	R1, #0
IT	NE
BNE	L_process_radio74
;HEXIWEAR_NFC_Click.c,552 :: 		if( radio->protocol == PROT_MIFARE )
LDR	R1, [SP, #84]
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
CMP	R1, #128
IT	NE
BNE	L_process_radio75
;HEXIWEAR_NFC_Click.c,567 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,568 :: 		OLED_WriteText("MIFARE card", 4, 80);
MOVW	R1, #lo_addr(?lstr35_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr35_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,570 :: 		nfc_restart_discovery();
BL	_nfc_restart_discovery+0
;HEXIWEAR_NFC_Click.c,571 :: 		Delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_process_radio76:
SUBS	R7, R7, #1
BNE	L_process_radio76
NOP
NOP
NOP
;HEXIWEAR_NFC_Click.c,572 :: 		}
IT	AL
BAL	L_process_radio78
L_process_radio75:
;HEXIWEAR_NFC_Click.c,574 :: 		else if( ( radio->protocol != PROT_NFCDEP )
LDR	R1, [SP, #84]
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
;HEXIWEAR_NFC_Click.c,575 :: 		&& ( radio->interface != INTF_UNDETERMINED ) )
CMP	R1, #5
IT	EQ
BEQ	L__process_radio112
LDR	R1, [SP, #84]
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	EQ
BEQ	L__process_radio111
L__process_radio110:
;HEXIWEAR_NFC_Click.c,577 :: 		sprinti( tmp_txt, " - POLL MODE: Remote T%dT activated\r\n", radio->protocol );
LDR	R1, [SP, #84]
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
UXTB	R3, R1
MOVW	R2, #lo_addr(?lstr_36_HEXIWEAR_NFC_Click+0)
MOVT	R2, #hi_addr(?lstr_36_HEXIWEAR_NFC_Click+0)
ADD	R1, SP, #4
PUSH	(R3)
PUSH	(R2)
PUSH	(R1)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,580 :: 		sprinti( tmp_txt, "Type %d Tag", radio->protocol );
LDR	R1, [SP, #84]
ADDS	R1, R1, #1
LDRB	R1, [R1, #0]
UXTB	R3, R1
MOVW	R2, #lo_addr(?lstr_37_HEXIWEAR_NFC_Click+0)
MOVT	R2, #hi_addr(?lstr_37_HEXIWEAR_NFC_Click+0)
ADD	R1, SP, #4
PUSH	(R3)
PUSH	(R2)
PUSH	(R1)
BL	_sprinti+0
ADD	SP, SP, #12
;HEXIWEAR_NFC_Click.c,582 :: 		OLED_DrawBox(0, 0, 96, 96, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #96
MOVS	R2, #96
MOVS	R1, #0
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,583 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0x7BCF, 0);
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #31695
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,584 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,585 :: 		OLED_WriteText("Detected:", 4, 10);
MOVW	R1, #lo_addr(?lstr38_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr38_HEXIWEAR_NFC_Click+0)
MOVS	R2, #10
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,586 :: 		OLED_SetFont(guiFont_Tahoma_8_Regular, 0xffff, 0);
MOVW	R1, #lo_addr(_guiFont_Tahoma_8_Regular+0)
MOVT	R1, #hi_addr(_guiFont_Tahoma_8_Regular+0)
MOVS	R2, #0
MOV	R0, R1
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_NFC_Click.c,587 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,588 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,589 :: 		OLED_WriteText(tmp_txt, 4, 25);
ADD	R1, SP, #4
MOVS	R2, #25
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,591 :: 		nfc_process( NFC_MODE_RW, radio );
LDR	R1, [SP, #84]
MOVS	R0, #4
BL	_nfc_process+0
;HEXIWEAR_NFC_Click.c,593 :: 		}
IT	AL
BAL	L_process_radio82
;HEXIWEAR_NFC_Click.c,575 :: 		&& ( radio->interface != INTF_UNDETERMINED ) )
L__process_radio112:
L__process_radio111:
;HEXIWEAR_NFC_Click.c,606 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,607 :: 		OLED_WriteText("Unknown dev", 4, 80);
MOVW	R1, #lo_addr(?lstr39_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr39_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,610 :: 		nfc_stop_discovery();
BL	_nfc_stop_discovery+0
;HEXIWEAR_NFC_Click.c,611 :: 		nfc_start_discovery( discovery_technologies, sizeof( discovery_technologies ) );
MOVS	R1, #8
MOVW	R0, #lo_addr(_discovery_technologies+0)
MOVT	R0, #hi_addr(_discovery_technologies+0)
BL	_nfc_start_discovery+0
;HEXIWEAR_NFC_Click.c,612 :: 		Delay_ms(1000);
MOVW	R7, #23038
MOVT	R7, #610
NOP
NOP
L_process_radio83:
SUBS	R7, R7, #1
BNE	L_process_radio83
NOP
NOP
NOP
;HEXIWEAR_NFC_Click.c,613 :: 		}
L_process_radio82:
L_process_radio78:
;HEXIWEAR_NFC_Click.c,616 :: 		OLED_DrawImage(NFC_bmp, 0, 0);
MOVW	R1, #lo_addr(_NFC_bmp+0)
MOVT	R1, #hi_addr(_NFC_bmp+0)
MOVS	R2, #0
MOV	R0, R1
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_NFC_Click.c,617 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R1, #0
PUSH	(R1)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,618 :: 		OLED_WriteText("Wait for device", 4, 80);
MOVW	R1, #lo_addr(?lstr40_HEXIWEAR_NFC_Click+0)
MOVT	R1, #hi_addr(?lstr40_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOV	R0, R1
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,619 :: 		}
IT	AL
BAL	L_process_radio85
L_process_radio74:
;HEXIWEAR_NFC_Click.c,624 :: 		}
L_process_radio85:
L_process_radio73:
;HEXIWEAR_NFC_Click.c,626 :: 		}
L_end_process_radio:
LDR	LR, [SP, #0]
ADD	SP, SP, #88
BX	LR
; end of _process_radio
_main:
;HEXIWEAR_NFC_Click.c,628 :: 		void main()
SUB	SP, SP, #8
;HEXIWEAR_NFC_Click.c,632 :: 		if( system_init() )
BL	_system_init+0
CMP	R0, #0
IT	EQ
BEQ	L_main86
;HEXIWEAR_NFC_Click.c,633 :: 		while( 1 );
L_main87:
IT	AL
BAL	L_main87
L_main86:
;HEXIWEAR_NFC_Click.c,636 :: 		OLED_DrawBox(0, 80, 96, 15, 0);
MOVS	R0, #0
PUSH	(R0)
MOVS	R3, #15
MOVS	R2, #96
MOVS	R1, #80
MOVS	R0, #0
BL	_OLED_DrawBox+0
ADD	SP, SP, #4
;HEXIWEAR_NFC_Click.c,637 :: 		OLED_WriteText("Wait for device", 4, 80);
MOVW	R0, #lo_addr(?lstr41_HEXIWEAR_NFC_Click+0)
MOVT	R0, #hi_addr(?lstr41_HEXIWEAR_NFC_Click+0)
MOVS	R2, #80
MOVS	R1, #4
BL	_OLED_WriteText+0
;HEXIWEAR_NFC_Click.c,639 :: 		while( 1 )
L_main89:
;HEXIWEAR_NFC_Click.c,642 :: 		if( incoming_flag )
MOVW	R0, #lo_addr(_incoming_flag+0)
MOVT	R0, #hi_addr(_incoming_flag+0)
LDRB	R0, [R0, #0]
CMP	R0, #0
IT	EQ
BEQ	L_main91
;HEXIWEAR_NFC_Click.c,645 :: 		nfc_wait_for_discovery_notification( &r_interface );
ADD	R0, SP, #4
BL	_nfc_wait_for_discovery_notification+0
;HEXIWEAR_NFC_Click.c,646 :: 		process_radio( &r_interface );
ADD	R0, SP, #4
BL	_process_radio+0
;HEXIWEAR_NFC_Click.c,647 :: 		incoming_flag = false;
MOVS	R1, #0
MOVW	R0, #lo_addr(_incoming_flag+0)
MOVT	R0, #hi_addr(_incoming_flag+0)
STRB	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,648 :: 		}
L_main91:
;HEXIWEAR_NFC_Click.c,650 :: 		}
IT	AL
BAL	L_main89
;HEXIWEAR_NFC_Click.c,651 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
_card_rx_ISR:
;HEXIWEAR_NFC_Click.c,654 :: 		void card_rx_ISR() iv IVT_INT_PORTB ics ICS_AUTO
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_NFC_Click.c,656 :: 		PORTB_ISFR = 0xFFFFFFFF;
MOV	R1, #-1
MOVW	R0, #lo_addr(PORTB_ISFR+0)
MOVT	R0, #hi_addr(PORTB_ISFR+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,657 :: 		nfc_rx_ready();
BL	_nfc_rx_ready+0
;HEXIWEAR_NFC_Click.c,658 :: 		incoming_flag = true;
MOVS	R1, #1
MOVW	R0, #lo_addr(_incoming_flag+0)
MOVT	R0, #hi_addr(_incoming_flag+0)
STRB	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,659 :: 		}
L_end_card_rx_ISR:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _card_rx_ISR
_timer2_interrupt:
;HEXIWEAR_NFC_Click.c,662 :: 		void timer2_interrupt() iv IVT_INT_LPTimer
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_NFC_Click.c,664 :: 		LPTMR0_CSR |= 0x80;
MOVW	R0, #lo_addr(LPTMR0_CSR+0)
MOVT	R0, #hi_addr(LPTMR0_CSR+0)
LDR	R0, [R0, #0]
ORR	R1, R0, #128
MOVW	R0, #lo_addr(LPTMR0_CSR+0)
MOVT	R0, #hi_addr(LPTMR0_CSR+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,665 :: 		PTA_PDOR.B11 = ~PTA_PDOR.B11;
MOVW	R1, #lo_addr(PTA_PDOR+0)
MOVT	R1, #hi_addr(PTA_PDOR+0)
LDR	R0, [R1, #0]
EOR	R1, R0, #1
MOVW	R0, #lo_addr(PTA_PDOR+0)
MOVT	R0, #hi_addr(PTA_PDOR+0)
STR	R1, [R0, #0]
;HEXIWEAR_NFC_Click.c,666 :: 		asm nop;
NOP
;HEXIWEAR_NFC_Click.c,667 :: 		nfc_timer_tick();
BL	_nfc_timer_tick+0
;HEXIWEAR_NFC_Click.c,668 :: 		}
L_end_timer2_interrupt:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _timer2_interrupt
