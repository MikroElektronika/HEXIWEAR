nfc_tag2_nt2_memblock_rd:
;nfc_tag2.c,81 :: 		)
; value start address is: 4 (R1)
; block start address is: 0 (R0)
SUB	SP, SP, #24
STR	LR, [SP, #0]
; value end address is: 4 (R1)
; block end address is: 0 (R0)
; block start address is: 0 (R0)
; value start address is: 4 (R1)
;nfc_tag2.c,83 :: 		uint8_t temp[ _NT2_BLOCK_SIZE_ ] = { 0 };
ADD	R11, SP, #8
ADD	R10, R11, #16
MOVW	R12, #lo_addr(?ICSnfc_tag2_nt2_memblock_rd_temp_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_tag2_nt2_memblock_rd_temp_L0+0)
BL	___CC2DW+0
;nfc_tag2.c,84 :: 		temp[ 0 ] = block;
ADD	R3, SP, #8
STRB	R0, [R3, #0]
; block end address is: 0 (R0)
;nfc_tag2.c,85 :: 		if( hal_nfctag2_read( _i2c_address, temp, sizeof( temp ) ) )
MOVW	R2, #lo_addr(nfc_tag2__i2c_address+0)
MOVT	R2, #hi_addr(nfc_tag2__i2c_address+0)
LDRB	R2, [R2, #0]
STR	R1, [SP, #4]
MOV	R1, R3
UXTB	R0, R2
MOVS	R2, #16
BL	_hal_nfctag2_read+0
LDR	R1, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memblock_rd0
; value end address is: 4 (R1)
;nfc_tag2.c,86 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memblock_rd
L_nfc_tag2_nt2_memblock_rd0:
;nfc_tag2.c,87 :: 		memcpy( ( void* )value, ( void* )temp, _NT2_BLOCK_SIZE_ );
; value start address is: 4 (R1)
ADD	R2, SP, #8
MOV	R0, R1
MOV	R1, R2
MOVS	R2, #16
SXTH	R2, R2
; value end address is: 4 (R1)
BL	_memcpy+0
;nfc_tag2.c,88 :: 		hal_delay( 5 );
MOVS	R0, #5
BL	_hal_delay+0
;nfc_tag2.c,89 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,90 :: 		}
L_end_nt2_memblock_rd:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of nfc_tag2_nt2_memblock_rd
nfc_tag2_nt2_memblock_wr:
;nfc_tag2.c,96 :: 		)
; value start address is: 4 (R1)
; block start address is: 0 (R0)
SUB	SP, SP, #24
STR	LR, [SP, #0]
; value end address is: 4 (R1)
; block end address is: 0 (R0)
; block start address is: 0 (R0)
; value start address is: 4 (R1)
;nfc_tag2.c,98 :: 		uint8_t temp[ _NT2_BLOCK_SIZE_ + 1 ] = { 0 };
ADD	R11, SP, #4
ADD	R10, R11, #17
MOVW	R12, #lo_addr(?ICSnfc_tag2_nt2_memblock_wr_temp_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_tag2_nt2_memblock_wr_temp_L0+0)
BL	___CC2DW+0
;nfc_tag2.c,99 :: 		temp[ 0 ] = block;
ADD	R2, SP, #4
STRB	R0, [R2, #0]
; block end address is: 0 (R0)
;nfc_tag2.c,100 :: 		memcpy( ( void* )( temp + 1 ), ( void* )value , _NT2_BLOCK_SIZE_ );
ADDS	R2, R2, #1
MOV	R0, R2
; value end address is: 4 (R1)
MOVS	R2, #16
SXTH	R2, R2
BL	_memcpy+0
;nfc_tag2.c,101 :: 		if( hal_nfctag2_write( _i2c_address, temp, sizeof( temp ) ) )
ADD	R3, SP, #4
MOVW	R2, #lo_addr(nfc_tag2__i2c_address+0)
MOVT	R2, #hi_addr(nfc_tag2__i2c_address+0)
LDRB	R2, [R2, #0]
MOV	R1, R3
UXTB	R0, R2
MOVS	R2, #17
BL	_hal_nfctag2_write+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memblock_wr1
;nfc_tag2.c,102 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memblock_wr
L_nfc_tag2_nt2_memblock_wr1:
;nfc_tag2.c,103 :: 		hal_delay( 5 );
MOVS	R0, #5
BL	_hal_delay+0
;nfc_tag2.c,104 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,105 :: 		}
L_end_nt2_memblock_wr:
LDR	LR, [SP, #0]
ADD	SP, SP, #24
BX	LR
; end of nfc_tag2_nt2_memblock_wr
nfc_tag2_nt2_memreg_rd:
;nfc_tag2.c,113 :: 		)
; offset start address is: 4 (R1)
SUB	SP, SP, #36
STR	LR, [SP, #0]
STRB	R0, [SP, #24]
STRH	R2, [SP, #28]
STR	R3, [SP, #32]
; offset end address is: 4 (R1)
; offset start address is: 4 (R1)
;nfc_tag2.c,115 :: 		uint8_t temp[ _NT2_BLOCK_SIZE_ ] = { 0 };
ADD	R11, SP, #8
ADD	R10, R11, #16
MOVW	R12, #lo_addr(?ICSnfc_tag2_nt2_memreg_rd_temp_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_tag2_nt2_memreg_rd_temp_L0+0)
BL	___CC2DW+0
; offset end address is: 4 (R1)
;nfc_tag2.c,117 :: 		while( ( offset + len ) > _NT2_BLOCK_SIZE_ )
L_nfc_tag2_nt2_memreg_rd2:
; offset start address is: 4 (R1)
LDRH	R4, [SP, #28]
ADDS	R4, R1, R4
UXTH	R4, R4
CMP	R4, #16
IT	LS
BLS	L_nfc_tag2_nt2_memreg_rd3
;nfc_tag2.c,119 :: 		if( nt2_memblock_rd( block++, temp ) )
ADD	R6, SP, #8
LDRB	R5, [SP, #24]
LDRB	R4, [SP, #24]
ADDS	R4, R4, #1
STRB	R4, [SP, #24]
STRB	R1, [SP, #4]
MOV	R1, R6
UXTB	R0, R5
BL	nfc_tag2_nt2_memblock_rd+0
LDRB	R1, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memreg_rd4
; offset end address is: 4 (R1)
;nfc_tag2.c,120 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memreg_rd
L_nfc_tag2_nt2_memreg_rd4:
;nfc_tag2.c,122 :: 		( void* )( temp + offset ), _NT2_BLOCK_SIZE_ - offset );
; offset start address is: 4 (R1)
RSB	R5, R1, #16
ADD	R4, SP, #8
ADDS	R4, R4, R1
STRB	R1, [SP, #4]
SXTH	R2, R5
MOV	R1, R4
;nfc_tag2.c,121 :: 		memcpy( ( void* )out,
LDR	R0, [SP, #32]
;nfc_tag2.c,122 :: 		( void* )( temp + offset ), _NT2_BLOCK_SIZE_ - offset );
BL	_memcpy+0
LDRB	R1, [SP, #4]
;nfc_tag2.c,123 :: 		len -= _NT2_BLOCK_SIZE_ - offset;
RSB	R5, R1, #16
SXTH	R5, R5
; offset end address is: 4 (R1)
LDRH	R4, [SP, #28]
SUB	R4, R4, R5
STRH	R4, [SP, #28]
;nfc_tag2.c,124 :: 		out += _NT2_BLOCK_SIZE_ - offset;
LDR	R4, [SP, #32]
ADDS	R4, R4, R5
STR	R4, [SP, #32]
;nfc_tag2.c,125 :: 		offset = 0;
; offset start address is: 28 (R7)
MOVS	R7, #0
;nfc_tag2.c,126 :: 		}
UXTB	R1, R7
; offset end address is: 28 (R7)
IT	AL
BAL	L_nfc_tag2_nt2_memreg_rd2
L_nfc_tag2_nt2_memreg_rd3:
;nfc_tag2.c,127 :: 		if( nt2_memblock_rd( block, temp ) )
; offset start address is: 4 (R1)
ADD	R4, SP, #8
STRB	R1, [SP, #4]
MOV	R1, R4
LDRB	R0, [SP, #24]
BL	nfc_tag2_nt2_memblock_rd+0
LDRB	R1, [SP, #4]
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memreg_rd5
; offset end address is: 4 (R1)
;nfc_tag2.c,128 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memreg_rd
L_nfc_tag2_nt2_memreg_rd5:
;nfc_tag2.c,129 :: 		memcpy( ( void* )out, ( void* )( temp + offset ), len );
; offset start address is: 4 (R1)
ADD	R4, SP, #8
ADDS	R4, R4, R1
; offset end address is: 4 (R1)
LDRH	R2, [SP, #28]
MOV	R1, R4
LDR	R0, [SP, #32]
BL	_memcpy+0
;nfc_tag2.c,130 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,131 :: 		}
L_end_nt2_memreg_rd:
LDR	LR, [SP, #0]
ADD	SP, SP, #36
BX	LR
; end of nfc_tag2_nt2_memreg_rd
nfc_tag2_nt2_memreg_wr:
;nfc_tag2.c,139 :: 		)
SUB	SP, SP, #36
STR	LR, [SP, #0]
STRB	R0, [SP, #20]
STRB	R1, [SP, #24]
STRH	R2, [SP, #28]
STR	R3, [SP, #32]
;nfc_tag2.c,141 :: 		uint8_t temp[ _NT2_BLOCK_SIZE_ ] = { 0 };
ADD	R11, SP, #4
ADD	R10, R11, #16
MOVW	R12, #lo_addr(?ICSnfc_tag2_nt2_memreg_wr_temp_L0+0)
MOVT	R12, #hi_addr(?ICSnfc_tag2_nt2_memreg_wr_temp_L0+0)
BL	___CC2DW+0
;nfc_tag2.c,143 :: 		while( ( offset + len ) > _NT2_BLOCK_SIZE_ )
L_nfc_tag2_nt2_memreg_wr6:
LDRH	R5, [SP, #28]
LDRB	R4, [SP, #24]
ADDS	R4, R4, R5
UXTH	R4, R4
CMP	R4, #16
IT	LS
BLS	L_nfc_tag2_nt2_memreg_wr7
;nfc_tag2.c,145 :: 		if( nt2_memblock_rd( block, temp ) )
ADD	R4, SP, #4
MOV	R1, R4
LDRB	R0, [SP, #20]
BL	nfc_tag2_nt2_memblock_rd+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memreg_wr8
;nfc_tag2.c,146 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memreg_wr
L_nfc_tag2_nt2_memreg_wr8:
;nfc_tag2.c,148 :: 		( void* )in, _NT2_BLOCK_SIZE_ - offset );
LDRB	R4, [SP, #24]
RSB	R6, R4, #16
;nfc_tag2.c,147 :: 		memcpy( ( void* )( temp + offset ),
ADD	R5, SP, #4
LDRB	R4, [SP, #24]
ADDS	R4, R5, R4
;nfc_tag2.c,148 :: 		( void* )in, _NT2_BLOCK_SIZE_ - offset );
SXTH	R2, R6
LDR	R1, [SP, #32]
;nfc_tag2.c,147 :: 		memcpy( ( void* )( temp + offset ),
MOV	R0, R4
;nfc_tag2.c,148 :: 		( void* )in, _NT2_BLOCK_SIZE_ - offset );
BL	_memcpy+0
;nfc_tag2.c,149 :: 		if( nt2_memblock_wr( block++, temp ) )
ADD	R6, SP, #4
LDRB	R5, [SP, #20]
LDRB	R4, [SP, #20]
ADDS	R4, R4, #1
STRB	R4, [SP, #20]
MOV	R1, R6
UXTB	R0, R5
BL	nfc_tag2_nt2_memblock_wr+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memreg_wr9
;nfc_tag2.c,150 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memreg_wr
L_nfc_tag2_nt2_memreg_wr9:
;nfc_tag2.c,151 :: 		len -= _NT2_BLOCK_SIZE_ - offset;
LDRB	R4, [SP, #24]
RSB	R5, R4, #16
SXTH	R5, R5
LDRH	R4, [SP, #28]
SUB	R4, R4, R5
STRH	R4, [SP, #28]
;nfc_tag2.c,152 :: 		in += _NT2_BLOCK_SIZE_ - offset;
LDR	R4, [SP, #32]
ADDS	R4, R4, R5
STR	R4, [SP, #32]
;nfc_tag2.c,153 :: 		offset = 0;
MOVS	R4, #0
STRB	R4, [SP, #24]
;nfc_tag2.c,154 :: 		}
IT	AL
BAL	L_nfc_tag2_nt2_memreg_wr6
L_nfc_tag2_nt2_memreg_wr7:
;nfc_tag2.c,155 :: 		if( nt2_memblock_rd( block, temp ) )
ADD	R4, SP, #4
MOV	R1, R4
LDRB	R0, [SP, #20]
BL	nfc_tag2_nt2_memblock_rd+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memreg_wr10
;nfc_tag2.c,156 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memreg_wr
L_nfc_tag2_nt2_memreg_wr10:
;nfc_tag2.c,157 :: 		memcpy( ( void* )( temp + offset ), ( void* )in, len );
ADD	R5, SP, #4
LDRB	R4, [SP, #24]
ADDS	R4, R5, R4
LDRH	R2, [SP, #28]
LDR	R1, [SP, #32]
MOV	R0, R4
BL	_memcpy+0
;nfc_tag2.c,158 :: 		if( nt2_memblock_wr( block, temp ) )
ADD	R4, SP, #4
MOV	R1, R4
LDRB	R0, [SP, #20]
BL	nfc_tag2_nt2_memblock_wr+0
CMP	R0, #0
IT	EQ
BEQ	L_nfc_tag2_nt2_memreg_wr11
;nfc_tag2.c,159 :: 		return 1;
MOVS	R0, #1
SXTH	R0, R0
IT	AL
BAL	L_end_nt2_memreg_wr
L_nfc_tag2_nt2_memreg_wr11:
;nfc_tag2.c,160 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,161 :: 		}
L_end_nt2_memreg_wr:
LDR	LR, [SP, #0]
ADD	SP, SP, #36
BX	LR
; end of nfc_tag2_nt2_memreg_wr
_nfctag2_init:
;nfc_tag2.c,167 :: 		int nfctag2_init( uint8_t i2c_address )
; i2c_address start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; i2c_address end address is: 0 (R0)
; i2c_address start address is: 0 (R0)
;nfc_tag2.c,169 :: 		_i2c_address = i2c_address >> 1;
LSRS	R2, R0, #1
; i2c_address end address is: 0 (R0)
MOVW	R1, #lo_addr(nfc_tag2__i2c_address+0)
MOVT	R1, #hi_addr(nfc_tag2__i2c_address+0)
STRB	R2, [R1, #0]
;nfc_tag2.c,170 :: 		if( hal_nfctag2_init() )
BL	_hal_nfctag2_init+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_init12
;nfc_tag2.c,171 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_init
L_nfctag2_init12:
;nfc_tag2.c,172 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,173 :: 		}
L_end_nfctag2_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _nfctag2_init
_nfctag2_i2c_addres:
;nfc_tag2.c,175 :: 		int nfctag2_i2c_addres( uint8_t new_address )
; new_address start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; new_address end address is: 0 (R0)
; new_address start address is: 0 (R0)
;nfc_tag2.c,177 :: 		uint8_t tmp = new_address;
STRB	R0, [SP, #4]
; new_address end address is: 0 (R0)
;nfc_tag2.c,178 :: 		if( nt2_memreg_wr( 0, 0, 1, &tmp ) )
ADD	R1, SP, #4
MOV	R3, R1
MOVS	R2, #1
MOVS	R1, #0
MOVS	R0, #0
BL	nfc_tag2_nt2_memreg_wr+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_i2c_addres13
;nfc_tag2.c,179 :: 		return NT2_BLOCK_WRITE_ERR;
MOVW	R0, #65533
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_i2c_addres
L_nfctag2_i2c_addres13:
;nfc_tag2.c,180 :: 		_i2c_address = tmp >> 1;
LDRB	R1, [SP, #4]
LSRS	R2, R1, #1
MOVW	R1, #lo_addr(nfc_tag2__i2c_address+0)
MOVT	R1, #hi_addr(nfc_tag2__i2c_address+0)
STRB	R2, [R1, #0]
;nfc_tag2.c,181 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,182 :: 		}
L_end_nfctag2_i2c_addres:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_i2c_addres
_nfctag2_get:
;nfc_tag2.c,184 :: 		int nfctag2_get( NFCTAG2_SET reg, uint8_t *output )
; output start address is: 4 (R1)
; reg start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; output end address is: 4 (R1)
; reg end address is: 0 (R0)
; reg start address is: 0 (R0)
; output start address is: 4 (R1)
;nfc_tag2.c,188 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
MOVS	R2, #3
MUL	R3, R2, R0
; reg end address is: 0 (R0)
MOVW	R2, #lo_addr(nfc_tag2_MEMORY+0)
MOVT	R2, #hi_addr(nfc_tag2_MEMORY+0)
ADDS	R5, R2, R3
ADDS	R2, R5, #2
LDRB	R2, [R2, #0]
UXTB	R4, R2
;nfc_tag2.c,187 :: 		if( nt2_memreg_rd( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
ADDS	R2, R5, #1
LDRB	R2, [R2, #0]
UXTB	R3, R2
LDRB	R2, [R5, #0]
;nfc_tag2.c,188 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
;nfc_tag2.c,187 :: 		if( nt2_memreg_rd( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
STRB	R3, [SP, #4]
; output end address is: 4 (R1)
UXTB	R0, R2
;nfc_tag2.c,188 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
UXTH	R2, R4
MOV	R3, R1
;nfc_tag2.c,187 :: 		if( nt2_memreg_rd( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
LDRB	R1, [SP, #4]
;nfc_tag2.c,188 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
BL	nfc_tag2_nt2_memreg_rd+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_get14
;nfc_tag2.c,189 :: 		return NT2_BLOCK_READ_ERR;
MOVW	R0, #65534
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_get
L_nfctag2_get14:
;nfc_tag2.c,190 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,191 :: 		}
L_end_nfctag2_get:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_get
_nfctag2_set:
;nfc_tag2.c,193 :: 		int nfctag2_set( NFCTAG2_SET reg, uint8_t *value )
; value start address is: 4 (R1)
; reg start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; value end address is: 4 (R1)
; reg end address is: 0 (R0)
; reg start address is: 0 (R0)
; value start address is: 4 (R1)
;nfc_tag2.c,197 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
MOVS	R2, #3
MUL	R3, R2, R0
; reg end address is: 0 (R0)
MOVW	R2, #lo_addr(nfc_tag2_MEMORY+0)
MOVT	R2, #hi_addr(nfc_tag2_MEMORY+0)
ADDS	R5, R2, R3
ADDS	R2, R5, #2
LDRB	R2, [R2, #0]
UXTB	R4, R2
;nfc_tag2.c,196 :: 		if( nt2_memreg_wr( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
ADDS	R2, R5, #1
LDRB	R2, [R2, #0]
UXTB	R3, R2
LDRB	R2, [R5, #0]
;nfc_tag2.c,197 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
;nfc_tag2.c,196 :: 		if( nt2_memreg_wr( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
STRB	R3, [SP, #4]
; value end address is: 4 (R1)
UXTB	R0, R2
;nfc_tag2.c,197 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
UXTH	R2, R4
MOV	R3, R1
;nfc_tag2.c,196 :: 		if( nt2_memreg_wr( MEMORY[ reg ][ MM_BLOCK ], MEMORY[ reg ][ MM_OFFSET ],
LDRB	R1, [SP, #4]
;nfc_tag2.c,197 :: 		MEMORY[ reg ][ MM_SIZE ], ptr ) )
BL	nfc_tag2_nt2_memreg_wr+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_set15
;nfc_tag2.c,198 :: 		return NT2_BLOCK_WRITE_ERR;
MOVW	R0, #65533
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_set
L_nfctag2_set15:
;nfc_tag2.c,199 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,200 :: 		}
L_end_nfctag2_set:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_set
_nfctag2_config_get:
;nfc_tag2.c,202 :: 		uint8_t nfctag2_config_get( NFCTAG2_CFG reg )
; reg start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; reg end address is: 0 (R0)
; reg start address is: 0 (R0)
;nfc_tag2.c,205 :: 		if( nt2_memreg_rd( _NT2_CONFIG_REG_, reg, 1, &regdat ) )
ADD	R1, SP, #4
MOV	R3, R1
MOVS	R2, #1
UXTB	R1, R0
; reg end address is: 0 (R0)
MOVS	R0, #58
BL	nfc_tag2_nt2_memreg_rd+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_config_get16
;nfc_tag2.c,206 :: 		return NT2_BLOCK_READ_ERR;
MOVS	R0, #-2
IT	AL
BAL	L_end_nfctag2_config_get
L_nfctag2_config_get16:
;nfc_tag2.c,207 :: 		return regdat;
LDRB	R0, [SP, #4]
;nfc_tag2.c,208 :: 		}
L_end_nfctag2_config_get:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_config_get
_nfctag2_config_set:
;nfc_tag2.c,210 :: 		int nfctag2_config_set( NFCTAG2_CFG reg, uint8_t input )
; reg start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R1, [SP, #4]
; reg end address is: 0 (R0)
; reg start address is: 0 (R0)
;nfc_tag2.c,212 :: 		if( nt2_memreg_wr( _NT2_CONFIG_REG_, reg, 1, &input ) )
ADD	R2, SP, #4
MOV	R3, R2
MOVS	R2, #1
UXTB	R1, R0
; reg end address is: 0 (R0)
MOVS	R0, #58
BL	nfc_tag2_nt2_memreg_wr+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_config_set17
;nfc_tag2.c,213 :: 		return NT2_BLOCK_WRITE_ERR;
MOVW	R0, #65533
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_config_set
L_nfctag2_config_set17:
;nfc_tag2.c,214 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,215 :: 		}
L_end_nfctag2_config_set:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_config_set
_nfctag2_session_get:
;nfc_tag2.c,217 :: 		uint8_t nfctag2_session_get( NFCTAG2_CFG reg )
; reg start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; reg end address is: 0 (R0)
; reg start address is: 0 (R0)
;nfc_tag2.c,220 :: 		uint8_t temp[ 2 ] = { 0 };
MOVS	R1, #0
STRB	R1, [SP, #5]
MOVS	R1, #0
STRB	R1, [SP, #6]
;nfc_tag2.c,221 :: 		temp[ 0 ] = _NT2_SESSION_REG_;
ADD	R4, SP, #5
MOVS	R1, #254
STRB	R1, [R4, #0]
;nfc_tag2.c,222 :: 		temp[ 1 ] = reg;
ADDS	R1, R4, #1
STRB	R0, [R1, #0]
; reg end address is: 0 (R0)
;nfc_tag2.c,223 :: 		if( hal_nfctag2_transfer( _i2c_address, temp, 2, &regdat, 1 ) )
MOVS	R3, #1
ADD	R2, SP, #4
MOVW	R1, #lo_addr(nfc_tag2__i2c_address+0)
MOVT	R1, #hi_addr(nfc_tag2__i2c_address+0)
LDRB	R1, [R1, #0]
PUSH	(R3)
MOV	R3, R2
MOVS	R2, #2
UXTB	R0, R1
MOV	R1, R4
BL	_hal_nfctag2_transfer+0
ADD	SP, SP, #4
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_session_get18
;nfc_tag2.c,224 :: 		return NT2_BLOCK_WRITE_ERR;
MOVS	R0, #-3
IT	AL
BAL	L_end_nfctag2_session_get
L_nfctag2_session_get18:
;nfc_tag2.c,225 :: 		hal_delay( 5 );
MOVS	R0, #5
BL	_hal_delay+0
;nfc_tag2.c,226 :: 		return regdat;
LDRB	R0, [SP, #4]
;nfc_tag2.c,227 :: 		}
L_end_nfctag2_session_get:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_session_get
_nfctag2_session_set:
;nfc_tag2.c,229 :: 		int nfctag2_session_set( NFCTAG2_CFG reg, uint8_t mask, uint8_t value )
; value start address is: 8 (R2)
; mask start address is: 4 (R1)
; reg start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; value end address is: 8 (R2)
; mask end address is: 4 (R1)
; reg end address is: 0 (R0)
; reg start address is: 0 (R0)
; mask start address is: 4 (R1)
; value start address is: 8 (R2)
;nfc_tag2.c,231 :: 		uint8_t temp[ 4 ] = { 0 };
MOVS	R3, #0
STRB	R3, [SP, #4]
MOVS	R3, #0
STRB	R3, [SP, #5]
STRB	R3, [SP, #6]
STRB	R3, [SP, #7]
;nfc_tag2.c,232 :: 		temp[ 0 ] = _NT2_SESSION_REG_;
ADD	R4, SP, #4
MOVS	R3, #254
STRB	R3, [R4, #0]
;nfc_tag2.c,233 :: 		temp[ 1 ] = reg;
ADDS	R3, R4, #1
STRB	R0, [R3, #0]
; reg end address is: 0 (R0)
;nfc_tag2.c,234 :: 		temp[ 2 ] = mask;
ADDS	R3, R4, #2
STRB	R1, [R3, #0]
; mask end address is: 4 (R1)
;nfc_tag2.c,235 :: 		temp[ 3 ] = value;
ADDS	R3, R4, #3
STRB	R2, [R3, #0]
; value end address is: 8 (R2)
;nfc_tag2.c,236 :: 		if( hal_nfctag2_write( _i2c_address, temp, 4 ) )
MOVW	R3, #lo_addr(nfc_tag2__i2c_address+0)
MOVT	R3, #hi_addr(nfc_tag2__i2c_address+0)
LDRB	R3, [R3, #0]
MOVS	R2, #4
MOV	R1, R4
UXTB	R0, R3
BL	_hal_nfctag2_write+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_session_set19
;nfc_tag2.c,237 :: 		return NT2_BLOCK_WRITE_ERR;
MOVW	R0, #65533
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_session_set
L_nfctag2_session_set19:
;nfc_tag2.c,238 :: 		hal_delay( 5 );
MOVS	R0, #5
BL	_hal_delay+0
;nfc_tag2.c,239 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,240 :: 		}
L_end_nfctag2_session_set:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_session_set
_nfctag2_memory_read:
;nfc_tag2.c,242 :: 		int nfctag2_memory_read( uint16_t mem_offset, uint8_t *buffer, uint16_t count )
; count start address is: 8 (R2)
; buffer start address is: 4 (R1)
; mem_offset start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; count end address is: 8 (R2)
; buffer end address is: 4 (R1)
; mem_offset end address is: 0 (R0)
; mem_offset start address is: 0 (R0)
; buffer start address is: 4 (R1)
; count start address is: 8 (R2)
;nfc_tag2.c,244 :: 		uint8_t blk = ( mem_offset / _NT2_BLOCK_SIZE_ ) + _NT2_USER_MEMORY_;
LSRS	R3, R0, #4
UXTH	R3, R3
ADDS	R4, R3, #1
;nfc_tag2.c,245 :: 		uint8_t off = mem_offset % _NT2_BLOCK_SIZE_;
AND	R3, R0, #15
; mem_offset end address is: 0 (R0)
;nfc_tag2.c,247 :: 		if( nt2_memreg_rd( blk, off, count, ptr ) )
STRH	R3, [SP, #4]
; buffer end address is: 4 (R1)
UXTB	R0, R4
; count end address is: 8 (R2)
MOV	R3, R1
LDRB	R1, [SP, #4]
BL	nfc_tag2_nt2_memreg_rd+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_memory_read20
;nfc_tag2.c,248 :: 		return NT2_BLOCK_READ_ERR;
MOVW	R0, #65534
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_memory_read
L_nfctag2_memory_read20:
;nfc_tag2.c,249 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,250 :: 		}
L_end_nfctag2_memory_read:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_memory_read
_nfctag2_memory_write:
;nfc_tag2.c,252 :: 		int nfctag2_memory_write( uint16_t mem_offset, uint8_t *buffer, uint16_t count )
; count start address is: 8 (R2)
; buffer start address is: 4 (R1)
; mem_offset start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; count end address is: 8 (R2)
; buffer end address is: 4 (R1)
; mem_offset end address is: 0 (R0)
; mem_offset start address is: 0 (R0)
; buffer start address is: 4 (R1)
; count start address is: 8 (R2)
;nfc_tag2.c,254 :: 		uint8_t blk = ( mem_offset / _NT2_BLOCK_SIZE_ ) + _NT2_USER_MEMORY_;
LSRS	R3, R0, #4
UXTH	R3, R3
ADDS	R4, R3, #1
;nfc_tag2.c,255 :: 		uint8_t off = mem_offset % _NT2_BLOCK_SIZE_;
AND	R3, R0, #15
; mem_offset end address is: 0 (R0)
;nfc_tag2.c,257 :: 		if( nt2_memreg_wr( blk, off, count, ptr ) )
STRH	R3, [SP, #4]
; buffer end address is: 4 (R1)
UXTB	R0, R4
; count end address is: 8 (R2)
MOV	R3, R1
LDRB	R1, [SP, #4]
BL	nfc_tag2_nt2_memreg_wr+0
CMP	R0, #0
IT	EQ
BEQ	L_nfctag2_memory_write21
;nfc_tag2.c,258 :: 		return NT2_BLOCK_WRITE_ERR;
MOVW	R0, #65533
SXTH	R0, R0
IT	AL
BAL	L_end_nfctag2_memory_write
L_nfctag2_memory_write21:
;nfc_tag2.c,259 :: 		return NT2_OK;
MOVS	R0, #0
SXTH	R0, R0
;nfc_tag2.c,260 :: 		}
L_end_nfctag2_memory_write:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _nfctag2_memory_write
