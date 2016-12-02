gsm4_at_parser__at_hash:
; cmd start address is: 0 (R0)
MOVE.L	R1, R0
; cmd end address is: 0 (R0)
; cmd start address is: 4 (R1)
; hash start address is: 0 (R0)
LDK.L	R0, #4321
; cmd end address is: 4 (R1)
; hash end address is: 0 (R0)
MOVE.L	R3, R1
L_gsm4_at_parser__at_hash0:
; hash start address is: 0 (R0)
; cmd start address is: 12 (R3)
; cmd start address is: 12 (R3)
MOVE.L	R2, R3
ADD.L	R1, R3, #1
MOVE.L	R3, R1
; cmd end address is: 12 (R3)
LDI.B	R1, R2, #0
; ch start address is: 8 (R2)
BEXTU.L	R2, R1, #256
CMP.S	R2, #0
JMPC	R30, Z, #1, L_gsm4_at_parser__at_hash1
; cmd end address is: 12 (R3)
; cmd start address is: 12 (R3)
ASHL.L	R1, R0, #5
ADD.L	R1, R1, R0
; hash end address is: 0 (R0)
ADD.L	R1, R1, R2
; hash start address is: 0 (R0)
MOVE.L	R0, R1
; cmd end address is: 12 (R3)
; ch end address is: 8 (R2)
JMP	L_gsm4_at_parser__at_hash0
L_gsm4_at_parser__at_hash1:
; hash end address is: 0 (R0)
L_end__at_hash:
RETURN	
; end of gsm4_at_parser__at_hash
gsm4_at_parser__at_search:
; cmd start address is: 0 (R0)
; cmd end address is: 0 (R0)
; cmd start address is: 0 (R0)
; cmd end address is: 0 (R0)
CALL	gsm4_at_parser__at_hash+0
; tmp_hash start address is: 0 (R0)
; i start address is: 12 (R3)
LDK.L	R3, #0
; i end address is: 12 (R3)
L_gsm4_at_parser__at_search2:
; i start address is: 12 (R3)
; tmp_hash start address is: 0 (R0)
; tmp_hash end address is: 0 (R0)
LDA.B	R1, gsm4_at_parser_at_cmd_storage_used+0
CMP.S	R3, R1
JMPC	R30, C, #0, L_gsm4_at_parser__at_search3
; tmp_hash end address is: 0 (R0)
; tmp_hash start address is: 0 (R0)
MUL.L	R2, R3, #24
LDK.L	R1, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R1, R1, R2
LDI.L	R1, R1, #0
CMP.L	R1, R0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_search5
; tmp_hash end address is: 0 (R0)
BEXTU.L	R0, R3, #0
; i end address is: 12 (R3)
JMP	L_end__at_search
L_gsm4_at_parser__at_search5:
; i start address is: 12 (R3)
; tmp_hash start address is: 0 (R0)
ADD.L	R3, R3, #1
BEXTU.L	R3, R3, #0
; tmp_hash end address is: 0 (R0)
; i end address is: 12 (R3)
JMP	L_gsm4_at_parser__at_search2
L_gsm4_at_parser__at_search3:
LDK.L	R0, #0
L_end__at_search:
RETURN	
; end of gsm4_at_parser__at_search
gsm4_at_parser__at_sub_parse:
; clean_out start address is: 4 (R1)
; raw_in start address is: 0 (R0)
LINK	LR, #16
MOVE.L	R7, R1
; clean_out end address is: 4 (R1)
; raw_in end address is: 0 (R0)
; raw_in start address is: 0 (R0)
; clean_out start address is: 28 (R7)
; end_pos start address is: 32 (R8)
LDK.L	R8, #0
; set_pos start address is: 36 (R9)
LDK.L	R9, #0
; get_pos start address is: 40 (R10)
LDK.L	R10, #0
; start_pos start address is: 44 (R11)
LDK.L	R11, #0
; tmp_ptr start address is: 16 (R4)
MOVE.L	R4, R0
; raw_in end address is: 0 (R0)
ADD.L	R27, SP, #0
ADD.L	R26, R27, #15
LDK.L	R28, #?ICSgsm4_at_parser__at_sub_parse_tmp_cmd_L0+0
CALL	___CC2DB+0
MOVE.L	R0, R4
CALL	_strlen+0
CMP.S	R0, #2
JMPC	R30, GT, #1, L_gsm4_at_parser__at_sub_parse6
; clean_out end address is: 28 (R7)
; end_pos end address is: 32 (R8)
; set_pos end address is: 36 (R9)
; get_pos end address is: 40 (R10)
; start_pos end address is: 44 (R11)
; tmp_ptr end address is: 16 (R4)
LDK.L	R0, #0
JMP	L_end__at_sub_parse
L_gsm4_at_parser__at_sub_parse6:
; tmp_ptr start address is: 16 (R4)
; start_pos start address is: 44 (R11)
; get_pos start address is: 40 (R10)
; set_pos start address is: 36 (R9)
; end_pos start address is: 32 (R8)
; clean_out start address is: 28 (R7)
ADD.L	R2, SP, #0
MOVE.L	R1, R4
MOVE.L	R0, R2
; tmp_ptr end address is: 16 (R4)
LDK.L	R2, #15
CALL	_strncpy+0
; c start address is: 4 (R1)
LDK.L	R1, #0
; clean_out end address is: 28 (R7)
; end_pos end address is: 32 (R8)
; set_pos end address is: 36 (R9)
; get_pos end address is: 40 (R10)
; start_pos end address is: 44 (R11)
; c end address is: 4 (R1)
MOVE.L	R0, R7
BEXTU.L	R7, R11, #256
BEXTU.L	R5, R8, #256
BEXTU.L	R6, R9, #256
BEXTU.L	R4, R10, #256
L_gsm4_at_parser__at_sub_parse7:
; c start address is: 4 (R1)
; start_pos start address is: 28 (R7)
; get_pos start address is: 16 (R4)
; set_pos start address is: 24 (R6)
; end_pos start address is: 20 (R5)
; clean_out start address is: 0 (R0)
CMP.B	R1, #15
JMPC	R30, C, #0, L_gsm4_at_parser__at_sub_parse86
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse10
CMP.B	R5, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse78
; end_pos end address is: 20 (R5)
; end_pos start address is: 8 (R2)
BEXTU.L	R2, R1, #256
; end_pos end address is: 8 (R2)
; c end address is: 4 (R1)
BEXTU.L	R1, R2, #256
JMP	L_gsm4_at_parser__at_sub_parse11
L_gsm4_at_parser__at_sub_parse78:
BEXTU.L	R1, R5, #256
L_gsm4_at_parser__at_sub_parse11:
; end_pos start address is: 4 (R1)
; end_pos end address is: 4 (R1)
JMP	L_gsm4_at_parser__at_sub_parse8
L_gsm4_at_parser__at_sub_parse10:
; c start address is: 4 (R1)
; end_pos start address is: 20 (R5)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #43
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse79
CMP.B	R7, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse80
; start_pos end address is: 28 (R7)
L_gsm4_at_parser__at_sub_parse61:
; start_pos start address is: 8 (R2)
BEXTU.L	R2, R1, #256
; start_pos end address is: 8 (R2)
BEXTU.L	R3, R2, #256
JMP	L_gsm4_at_parser__at_sub_parse63
L_gsm4_at_parser__at_sub_parse79:
BEXTU.L	R3, R7, #256
L_gsm4_at_parser__at_sub_parse63:
; start_pos start address is: 12 (R3)
; start_pos end address is: 12 (R3)
JMP	L_gsm4_at_parser__at_sub_parse62
L_gsm4_at_parser__at_sub_parse80:
BEXTU.L	R3, R7, #256
L_gsm4_at_parser__at_sub_parse62:
; start_pos start address is: 12 (R3)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #61
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse81
CMP.B	R6, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse82
; set_pos end address is: 24 (R6)
L_gsm4_at_parser__at_sub_parse60:
; set_pos start address is: 8 (R2)
BEXTU.L	R2, R1, #256
; set_pos end address is: 8 (R2)
BEXTU.L	R6, R2, #256
JMP	L_gsm4_at_parser__at_sub_parse65
L_gsm4_at_parser__at_sub_parse81:
L_gsm4_at_parser__at_sub_parse65:
; set_pos start address is: 24 (R6)
; set_pos end address is: 24 (R6)
JMP	L_gsm4_at_parser__at_sub_parse64
L_gsm4_at_parser__at_sub_parse82:
L_gsm4_at_parser__at_sub_parse64:
; set_pos start address is: 24 (R6)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #63
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse83
CMP.B	R4, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse84
; get_pos end address is: 16 (R4)
L_gsm4_at_parser__at_sub_parse59:
; get_pos start address is: 8 (R2)
BEXTU.L	R2, R1, #256
; get_pos end address is: 8 (R2)
BEXTU.L	R4, R2, #256
JMP	L_gsm4_at_parser__at_sub_parse67
L_gsm4_at_parser__at_sub_parse83:
L_gsm4_at_parser__at_sub_parse67:
; get_pos start address is: 16 (R4)
; get_pos end address is: 16 (R4)
JMP	L_gsm4_at_parser__at_sub_parse66
L_gsm4_at_parser__at_sub_parse84:
L_gsm4_at_parser__at_sub_parse66:
; get_pos start address is: 16 (R4)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #13
JMPC	R30, Z, #1, L_gsm4_at_parser__at_sub_parse70
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #10
JMPC	R30, Z, #1, L_gsm4_at_parser__at_sub_parse69
ADD.L	R2, SP, #0
ADD.L	R2, R2, R1
LDI.B	R2, R2, #0
CMP.B	R2, #58
JMPC	R30, Z, #1, L_gsm4_at_parser__at_sub_parse68
JMP	L_gsm4_at_parser__at_sub_parse25
L_gsm4_at_parser__at_sub_parse70:
L_gsm4_at_parser__at_sub_parse69:
L_gsm4_at_parser__at_sub_parse68:
CMP.B	R5, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse85
; end_pos end address is: 20 (R5)
L_gsm4_at_parser__at_sub_parse57:
; end_pos start address is: 8 (R2)
BEXTU.L	R2, R1, #256
; end_pos end address is: 8 (R2)
BEXTU.L	R5, R2, #256
L_gsm4_at_parser__at_sub_parse25:
; end_pos start address is: 20 (R5)
; end_pos end address is: 20 (R5)
JMP	L_gsm4_at_parser__at_sub_parse71
L_gsm4_at_parser__at_sub_parse85:
L_gsm4_at_parser__at_sub_parse71:
; end_pos start address is: 20 (R5)
ADD.L	R1, R1, #1
BEXTU.L	R1, R1, #256
; start_pos end address is: 12 (R3)
; end_pos end address is: 20 (R5)
; c end address is: 4 (R1)
BEXTU.L	R7, R3, #256
JMP	L_gsm4_at_parser__at_sub_parse7
L_gsm4_at_parser__at_sub_parse86:
BEXTU.L	R1, R5, #256
L_gsm4_at_parser__at_sub_parse8:
; end_pos start address is: 4 (R1)
; start_pos start address is: 28 (R7)
CMP.B	R6, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse73
CMP.B	R4, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse72
; set_pos end address is: 24 (R6)
; get_pos end address is: 16 (R4)
L_gsm4_at_parser__at_sub_parse56:
SUB.L	R3, R1, R7
; end_pos end address is: 4 (R1)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R7
; start_pos end address is: 28 (R7)
MOVE.L	R1, R2
BEXTS.L	R2, R3, #0
; clean_out end address is: 0 (R0)
CALL	_strncpy+0
LDK.L	R0, #4
JMP	L_end__at_sub_parse
L_gsm4_at_parser__at_sub_parse73:
; get_pos start address is: 16 (R4)
; set_pos start address is: 24 (R6)
; clean_out start address is: 0 (R0)
; start_pos start address is: 28 (R7)
L_gsm4_at_parser__at_sub_parse72:
CMP.B	R6, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse75
CMP.B	R4, #0
JMPC	R30, Z, #1, L_gsm4_at_parser__at_sub_parse74
; set_pos end address is: 24 (R6)
L_gsm4_at_parser__at_sub_parse55:
SUB.L	R3, R4, R7
; get_pos end address is: 16 (R4)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R7
; start_pos end address is: 28 (R7)
MOVE.L	R1, R2
BEXTS.L	R2, R3, #0
; clean_out end address is: 0 (R0)
CALL	_strncpy+0
LDK.L	R0, #3
JMP	L_end__at_sub_parse
L_gsm4_at_parser__at_sub_parse75:
; get_pos start address is: 16 (R4)
; set_pos start address is: 24 (R6)
; clean_out start address is: 0 (R0)
; start_pos start address is: 28 (R7)
L_gsm4_at_parser__at_sub_parse74:
CMP.B	R6, #0
JMPC	R30, Z, #1, L_gsm4_at_parser__at_sub_parse77
CMP.B	R4, #0
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse76
; get_pos end address is: 16 (R4)
L_gsm4_at_parser__at_sub_parse54:
SUB.L	R3, R6, R7
; set_pos end address is: 24 (R6)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R7
; start_pos end address is: 28 (R7)
MOVE.L	R1, R2
BEXTS.L	R2, R3, #0
; clean_out end address is: 0 (R0)
CALL	_strncpy+0
LDK.L	R0, #2
JMP	L_end__at_sub_parse
L_gsm4_at_parser__at_sub_parse77:
; get_pos start address is: 16 (R4)
; set_pos start address is: 24 (R6)
; clean_out start address is: 0 (R0)
; start_pos start address is: 28 (R7)
L_gsm4_at_parser__at_sub_parse76:
SUB.L	R2, R4, #1
; get_pos end address is: 16 (R4)
CMP.S	R6, R2
JMPC	R30, Z, #0, L_gsm4_at_parser__at_sub_parse38
SUB.L	R3, R6, R7
; set_pos end address is: 24 (R6)
ADD.L	R2, SP, #0
ADD.L	R2, R2, R7
; start_pos end address is: 28 (R7)
MOVE.L	R1, R2
BEXTS.L	R2, R3, #0
; clean_out end address is: 0 (R0)
CALL	_strncpy+0
LDK.L	R0, #1
JMP	L_end__at_sub_parse
L_gsm4_at_parser__at_sub_parse38:
LDK.L	R0, #0
L_end__at_sub_parse:
UNLINK	LR
RETURN	
; end of gsm4_at_parser__at_sub_parse
_at_parser_init:
LDK.L	R0, #?lstr1_gsm4_at_parser+0
CALL	_strlen+0
STA.B	gsm4_at_parser_header_size+0, R0
LDK.L	R0, #0
STA.B	gsm4_at_parser_at_cmd_storage_used+0, R0
; c start address is: 8 (R2)
LDK.L	R2, #0
; c end address is: 8 (R2)
L_at_parser_init39:
; c start address is: 8 (R2)
CMP.B	R2, #50
JMPC	R30, C, #0, L_at_parser_init40
MUL.L	R1, R2, #24
LDK.L	R0, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R1, R0, R1
LDK.L	R0, #0
STI.L	R1, #0, R0
MUL.L	R1, R2, #24
LDK.L	R0, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R0, R0, R1
ADD.L	R1, R0, #4
LDK.L	R0, #0
STI.L	R1, #0, R0
MUL.L	R1, R2, #24
LDK.L	R0, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R0, R0, R1
ADD.L	R1, R0, #8
LDK.L	R0, #0
STI.L	R1, #0, R0
MUL.L	R1, R2, #24
LDK.L	R0, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R0, R0, R1
ADD.L	R1, R0, #12
LDK.L	R0, #0
STI.L	R1, #0, R0
MUL.L	R1, R2, #24
LDK.L	R0, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R0, R0, R1
ADD.L	R1, R0, #16
LDK.L	R0, #0
STI.L	R1, #0, R0
MUL.L	R1, R2, #24
LDK.L	R0, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R0, R0, R1
ADD.L	R1, R0, #20
LDK.L	R0, #0
STI.L	R1, #0, R0
ADD.L	R2, R2, #1
BEXTU.L	R2, R2, #256
; c end address is: 8 (R2)
JMP	L_at_parser_init39
L_at_parser_init40:
L_end_at_parser_init:
RETURN	
; end of _at_parser_init
_at_parser_store:
; executer start address is: 20 (R5)
; tester start address is: 16 (R4)
; setter start address is: 12 (R3)
; getter start address is: 8 (R2)
; timeout start address is: 4 (R1)
; command start address is: 0 (R0)
LINK	LR, #24
MOVE.L	R8, R4
MOVE.L	R4, R0
MOVE.L	R9, R5
MOVE.L	R5, R1
MOVE.L	R6, R2
MOVE.L	R7, R3
; executer end address is: 20 (R5)
; tester end address is: 16 (R4)
; setter end address is: 12 (R3)
; getter end address is: 8 (R2)
; timeout end address is: 4 (R1)
; command end address is: 0 (R0)
; command start address is: 16 (R4)
; timeout start address is: 20 (R5)
; getter start address is: 24 (R6)
; setter start address is: 28 (R7)
; tester start address is: 32 (R8)
; executer start address is: 36 (R9)
MOVE.L	R0, R4
CALL	gsm4_at_parser__at_hash+0
STI.L	SP, #0, R0
STI.L	SP, #4, R5
; timeout end address is: 20 (R5)
STI.L	SP, #8, R6
; getter end address is: 24 (R6)
STI.L	SP, #12, R7
; setter end address is: 28 (R7)
STI.L	SP, #16, R8
; tester end address is: 32 (R8)
STI.L	SP, #20, R9
; executer end address is: 36 (R9)
MOVE.L	R0, R4
CALL	_strlen+0
LDA.B	R6, gsm4_at_parser_header_size+0
ADD.L	R6, R6, #15
CMP.S	R0, R6
JMPC	R30, GTE, #0, L_at_parser_store42
; command end address is: 16 (R4)
JMP	L_end_at_parser_store
L_at_parser_store42:
; command start address is: 16 (R4)
LDA.B	R6, gsm4_at_parser_at_cmd_storage_used+0
CMP.B	R6, #50
JMPC	R30, Z, #0, L_at_parser_store43
; command end address is: 16 (R4)
JMP	L_end_at_parser_store
L_at_parser_store43:
; command start address is: 16 (R4)
MOVE.L	R0, R4
; command end address is: 16 (R4)
CALL	gsm4_at_parser__at_search+0
CMP.S	R0, #0
JMPC	R30, Z, #1, L_at_parser_store44
JMP	L_end_at_parser_store
L_at_parser_store44:
LDA.B	R6, gsm4_at_parser_at_cmd_storage_used+0
MUL.L	R7, R6, #24
LDK.L	R6, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R7, R6, R7
ADD.L	R6, SP, #0
MEMCPY.B	R7, R6, #24
LDA.B	R6, gsm4_at_parser_at_cmd_storage_used+0
ADD.L	R6, R6, #1
STA.B	gsm4_at_parser_at_cmd_storage_used+0, R6
L_end_at_parser_store:
UNLINK	LR
RETURN	
; end of _at_parser_store
_at_parse:
; timeout start address is: 8 (R2)
; cb start address is: 4 (R1)
; input start address is: 0 (R0)
LINK	LR, #16
MOVE.L	R12, R1
MOVE.L	R13, R2
; timeout end address is: 8 (R2)
; cb end address is: 4 (R1)
; input end address is: 0 (R0)
; input start address is: 0 (R0)
; cb start address is: 48 (R12)
; timeout start address is: 52 (R13)
ADD.L	R27, SP, #0
ADD.L	R26, R27, #15
LDK.L	R28, #?ICSat_parse_cmd_temp_L0+0
CALL	___CC2DB+0
ADD.L	R3, SP, #0
MOVE.L	R1, R3
; input end address is: 0 (R0)
CALL	gsm4_at_parser__at_sub_parse+0
; cmd_type start address is: 16 (R4)
BEXTU.L	R4, R0, #256
CMP.B	R0, #0
JMPC	R30, Z, #0, L_at_parse45
; cmd_type end address is: 16 (R4)
LDA.L	R3, gsm4_at_parser_at_cmd_storage+16
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
LDA.L	R3, gsm4_at_parser_at_cmd_storage+4
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_end_at_parse
L_at_parse45:
; cmd_type start address is: 16 (R4)
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
ADD.L	R3, SP, #0
MOVE.L	R0, R3
CALL	gsm4_at_parser__at_search+0
; cmd_idx start address is: 4 (R1)
BEXTU.L	R1, R0, #0
CMP.S	R0, #0
JMPC	R30, Z, #0, L_at_parse46
; cmd_type end address is: 16 (R4)
; cmd_idx end address is: 4 (R1)
LDA.L	R3, gsm4_at_parser_at_cmd_storage+16
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
LDA.L	R3, gsm4_at_parser_at_cmd_storage+4
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_end_at_parse
L_at_parse46:
; cmd_idx start address is: 4 (R1)
; cmd_type start address is: 16 (R4)
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
JMP	L_at_parse47
; cmd_type end address is: 16 (R4)
L_at_parse49:
MUL.L	R4, R1, #24
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #12
LDI.L	R3, R3, #0
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
MUL.L	R4, R1, #24
; cmd_idx end address is: 4 (R1)
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #4
LDI.L	R3, R3, #0
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_at_parse48
L_at_parse50:
; cmd_idx start address is: 4 (R1)
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
MUL.L	R4, R1, #24
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #8
LDI.L	R3, R3, #0
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
MUL.L	R4, R1, #24
; cmd_idx end address is: 4 (R1)
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #4
LDI.L	R3, R3, #0
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_at_parse48
L_at_parse51:
; cmd_idx start address is: 4 (R1)
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
MUL.L	R4, R1, #24
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #16
LDI.L	R3, R3, #0
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
MUL.L	R4, R1, #24
; cmd_idx end address is: 4 (R1)
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #4
LDI.L	R3, R3, #0
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_at_parse48
L_at_parse52:
; cmd_idx start address is: 4 (R1)
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
MUL.L	R4, R1, #24
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #20
LDI.L	R3, R3, #0
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
MUL.L	R4, R1, #24
; cmd_idx end address is: 4 (R1)
LDK.L	R3, #gsm4_at_parser_at_cmd_storage+0
ADD.L	R3, R3, R4
ADD.L	R3, R3, #4
LDI.L	R3, R3, #0
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_at_parse48
L_at_parse53:
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
LDA.L	R3, gsm4_at_parser_at_cmd_storage+20
STI.L	R12, #0, R3
; cb end address is: 48 (R12)
LDA.L	R3, gsm4_at_parser_at_cmd_storage+4
STI.L	R13, #0, R3
; timeout end address is: 52 (R13)
JMP	L_at_parse48
L_at_parse47:
; cmd_idx start address is: 4 (R1)
; cmd_type start address is: 16 (R4)
; timeout start address is: 52 (R13)
; cb start address is: 48 (R12)
CMP.B	R4, #2
JMPC	R30, Z, #1, L_at_parse49
CMP.B	R4, #1
JMPC	R30, Z, #1, L_at_parse50
CMP.B	R4, #3
JMPC	R30, Z, #1, L_at_parse51
CMP.B	R4, #4
JMPC	R30, Z, #1, L_at_parse52
; cmd_idx end address is: 4 (R1)
CMP.B	R4, #0
JMPC	R30, Z, #1, L_at_parse53
; cb end address is: 48 (R12)
; timeout end address is: 52 (R13)
; cmd_type end address is: 16 (R4)
L_at_parse48:
L_end_at_parse:
UNLINK	LR
RETURN	
; end of _at_parse
