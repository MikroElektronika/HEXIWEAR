eight_x_eight_hw_refresh:
;eight_x_eight_hw.c,111 :: 		static refresh()
SUB	SP, SP, #16
STR	LR, [SP, #0]
;eight_x_eight_hw.c,115 :: 		uint8_t result = 0;
; result start address is: 20 (R5)
MOVS	R5, #0
;eight_x_eight_hw.c,116 :: 		uint8_t *ptr = frame_buffer;
; ptr start address is: 8 (R2)
MOVW	R2, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R2, #hi_addr(eight_x_eight_hw_frame_buffer+0)
;eight_x_eight_hw.c,118 :: 		for( i = 7, j = 0; i >= 0; i--, j++ )
; i start address is: 16 (R4)
MOVS	R4, #7
SXTH	R4, R4
; j start address is: 12 (R3)
MOVS	R3, #0
SXTH	R3, R3
; ptr end address is: 8 (R2)
; result end address is: 20 (R5)
; i end address is: 16 (R4)
; j end address is: 12 (R3)
L_eight_x_eight_hw_refresh0:
; j start address is: 12 (R3)
; i start address is: 16 (R4)
; ptr start address is: 8 (R2)
; result start address is: 20 (R5)
CMP	R4, #0
IT	LT
BLT	L_eight_x_eight_hw_refresh1
;eight_x_eight_hw.c,120 :: 		for( k = 7, m = 7; k >= 0; k--, m--)
; k start address is: 0 (R0)
MOVS	R0, #7
SXTH	R0, R0
; k end address is: 0 (R0)
; ptr end address is: 8 (R2)
; result end address is: 20 (R5)
; i end address is: 16 (R4)
; j end address is: 12 (R3)
SXTH	R6, R0
L_eight_x_eight_hw_refresh3:
; k start address is: 24 (R6)
; result start address is: 20 (R5)
; ptr start address is: 8 (R2)
; i start address is: 16 (R4)
; j start address is: 12 (R3)
CMP	R6, #0
IT	LT
BLT	L_eight_x_eight_hw_refresh4
;eight_x_eight_hw.c,122 :: 		result |=  ( ptr[7 - k] & ( 1 << j  ) ) >> j << k; //Rotate 270 deg
RSB	R0, R6, #7
SXTH	R0, R0
ADDS	R0, R2, R0
LDRB	R1, [R0, #0]
MOVS	R0, #1
SXTH	R0, R0
LSLS	R0, R3
SXTH	R0, R0
AND	R0, R1, R0, LSL #0
SXTH	R0, R0
ASRS	R0, R3
SXTH	R0, R0
LSLS	R0, R6
SXTH	R0, R0
ORR	R0, R5, R0, LSL #0
UXTB	R5, R0
;eight_x_eight_hw.c,120 :: 		for( k = 7, m = 7; k >= 0; k--, m--)
SUBS	R6, R6, #1
SXTH	R6, R6
;eight_x_eight_hw.c,123 :: 		}
; k end address is: 24 (R6)
IT	AL
BAL	L_eight_x_eight_hw_refresh3
L_eight_x_eight_hw_refresh4:
;eight_x_eight_hw.c,125 :: 		buffer[0] = j + 1;
ADD	R1, SP, #12
ADDS	R0, R3, #1
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,126 :: 		buffer[1] = result;
ADDS	R0, R1, #1
STRB	R5, [R0, #0]
; result end address is: 20 (R5)
;eight_x_eight_hw.c,127 :: 		led_eight_hal_write( buffer );
STRH	R3, [SP, #4]
STRH	R4, [SP, #6]
STR	R2, [SP, #8]
MOV	R0, R1
BL	_led_eight_hal_write+0
LDR	R2, [SP, #8]
LDRSH	R4, [SP, #6]
LDRSH	R3, [SP, #4]
;eight_x_eight_hw.c,128 :: 		result = 0;
; result start address is: 20 (R5)
MOVS	R5, #0
;eight_x_eight_hw.c,118 :: 		for( i = 7, j = 0; i >= 0; i--, j++ )
SUBS	R4, R4, #1
SXTH	R4, R4
ADDS	R3, R3, #1
SXTH	R3, R3
;eight_x_eight_hw.c,129 :: 		}
; ptr end address is: 8 (R2)
; result end address is: 20 (R5)
; i end address is: 16 (R4)
; j end address is: 12 (R3)
IT	AL
BAL	L_eight_x_eight_hw_refresh0
L_eight_x_eight_hw_refresh1:
;eight_x_eight_hw.c,131 :: 		return;
;eight_x_eight_hw.c,132 :: 		}
L_end_refresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of eight_x_eight_hw_refresh
eight_x_eight_hw_scroll_refresh:
;eight_x_eight_hw.c,134 :: 		static scroll_refresh()
SUB	SP, SP, #16
STR	LR, [SP, #0]
;eight_x_eight_hw.c,138 :: 		uint8_t result = 0;
; result start address is: 24 (R6)
MOVS	R6, #0
;eight_x_eight_hw.c,139 :: 		uint8_t *ptr = frame_buffer;
MOVW	R0, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R0, #hi_addr(eight_x_eight_hw_frame_buffer+0)
STR	R0, [SP, #12]
;eight_x_eight_hw.c,141 :: 		for( i = 7, j = 0; i >= 0; i--, j++ )
MOVS	R0, #7
SXTH	R0, R0
STRH	R0, [SP, #8]
; j start address is: 12 (R3)
MOVS	R3, #0
SXTH	R3, R3
; result end address is: 24 (R6)
; j end address is: 12 (R3)
L_eight_x_eight_hw_scroll_refresh6:
; j start address is: 12 (R3)
; result start address is: 24 (R6)
LDRSH	R0, [SP, #8]
CMP	R0, #0
IT	LT
BLT	L_eight_x_eight_hw_scroll_refresh7
;eight_x_eight_hw.c,143 :: 		for( k = 7, m = 7; k >= 0; k--, m--)
; k start address is: 20 (R5)
MOVS	R5, #7
SXTH	R5, R5
; k end address is: 20 (R5)
; result end address is: 24 (R6)
; j end address is: 12 (R3)
SXTH	R2, R3
SXTH	R4, R5
UXTB	R5, R6
L_eight_x_eight_hw_scroll_refresh9:
; k start address is: 16 (R4)
; result start address is: 20 (R5)
; j start address is: 8 (R2)
CMP	R4, #0
IT	LT
BLT	L_eight_x_eight_hw_scroll_refresh10
;eight_x_eight_hw.c,145 :: 		result |=  ( ptr[7 - k] & ( 1 << j  ) ) >> j << k; //Rotate 270 deg
RSB	R1, R4, #7
SXTH	R1, R1
LDR	R0, [SP, #12]
ADDS	R0, R0, R1
LDRB	R1, [R0, #0]
MOVS	R0, #1
SXTH	R0, R0
LSLS	R0, R2
SXTH	R0, R0
AND	R0, R1, R0, LSL #0
SXTH	R0, R0
ASRS	R0, R2
SXTH	R0, R0
LSLS	R0, R4
SXTH	R0, R0
ORR	R0, R5, R0, LSL #0
; result end address is: 20 (R5)
; result start address is: 24 (R6)
UXTB	R6, R0
;eight_x_eight_hw.c,143 :: 		for( k = 7, m = 7; k >= 0; k--, m--)
SUBS	R0, R4, #1
; k end address is: 16 (R4)
; k start address is: 0 (R0)
;eight_x_eight_hw.c,146 :: 		}
; k end address is: 0 (R0)
; result end address is: 24 (R6)
UXTB	R5, R6
SXTH	R4, R0
IT	AL
BAL	L_eight_x_eight_hw_scroll_refresh9
L_eight_x_eight_hw_scroll_refresh10:
;eight_x_eight_hw.c,148 :: 		result = led_eight_reverse_byte( result );  //Reverse bits on each digit
; result start address is: 20 (R5)
STRH	R2, [SP, #4]
; result end address is: 20 (R5)
UXTB	R0, R5
BL	eight_x_eight_hw_led_eight_reverse_byte+0
LDRSH	R2, [SP, #4]
; result start address is: 12 (R3)
UXTB	R3, R0
;eight_x_eight_hw.c,150 :: 		buffer[0] = j + 1;
ADD	R1, SP, #10
ADDS	R0, R2, #1
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,151 :: 		buffer[1] = result;
ADDS	R0, R1, #1
STRB	R3, [R0, #0]
; result end address is: 12 (R3)
;eight_x_eight_hw.c,152 :: 		led_eight_hal_write( buffer );
STRH	R2, [SP, #4]
MOV	R0, R1
BL	_led_eight_hal_write+0
LDRSH	R2, [SP, #4]
;eight_x_eight_hw.c,153 :: 		result = 0;
; result start address is: 24 (R6)
MOVS	R6, #0
;eight_x_eight_hw.c,141 :: 		for( i = 7, j = 0; i >= 0; i--, j++ )
LDRSH	R0, [SP, #8]
SUBS	R0, R0, #1
STRH	R0, [SP, #8]
ADDS	R0, R2, #1
; j end address is: 8 (R2)
; j start address is: 12 (R3)
SXTH	R3, R0
;eight_x_eight_hw.c,154 :: 		}
; result end address is: 24 (R6)
; j end address is: 12 (R3)
IT	AL
BAL	L_eight_x_eight_hw_scroll_refresh6
L_eight_x_eight_hw_scroll_refresh7:
;eight_x_eight_hw.c,156 :: 		return;
;eight_x_eight_hw.c,157 :: 		}
L_end_scroll_refresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of eight_x_eight_hw_scroll_refresh
eight_x_eight_hw_led_eight_reverse_byte:
;eight_x_eight_hw.c,159 :: 		static uint8_t led_eight_reverse_byte( uint8_t b )
; b start address is: 0 (R0)
; b end address is: 0 (R0)
; b start address is: 0 (R0)
;eight_x_eight_hw.c,161 :: 		b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
AND	R1, R0, #240
UXTB	R1, R1
LSRS	R2, R1, #4
UXTB	R2, R2
AND	R1, R0, #15
UXTB	R1, R1
; b end address is: 0 (R0)
LSLS	R1, R1, #4
UXTH	R1, R1
ORR	R3, R2, R1, LSL #0
;eight_x_eight_hw.c,162 :: 		b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
UXTB	R1, R3
AND	R1, R1, #204
UXTB	R1, R1
LSRS	R2, R1, #2
UXTB	R2, R2
UXTB	R1, R3
AND	R1, R1, #51
UXTB	R1, R1
LSLS	R1, R1, #2
UXTH	R1, R1
ORR	R3, R2, R1, LSL #0
;eight_x_eight_hw.c,163 :: 		b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
UXTB	R1, R3
AND	R1, R1, #170
UXTB	R1, R1
LSRS	R2, R1, #1
UXTB	R2, R2
UXTB	R1, R3
AND	R1, R1, #85
UXTB	R1, R1
LSLS	R1, R1, #1
UXTH	R1, R1
ORR	R1, R2, R1, LSL #0
;eight_x_eight_hw.c,164 :: 		return b;
UXTB	R0, R1
;eight_x_eight_hw.c,165 :: 		}
L_end_led_eight_reverse_byte:
BX	LR
; end of eight_x_eight_hw_led_eight_reverse_byte
_led_eight_init:
;eight_x_eight_hw.c,167 :: 		void led_eight_init()
SUB	SP, SP, #12
STR	LR, [SP, #0]
;eight_x_eight_hw.c,170 :: 		led_eight_hal_init();
BL	_led_eight_hal_init+0
;eight_x_eight_hw.c,172 :: 		buffer[0] = DEC_MODE;          //Decode mode set to No Decoding
ADD	R2, SP, #4
STR	R2, [SP, #8]
MOVS	R0, #9
STRB	R0, [R2, #0]
;eight_x_eight_hw.c,173 :: 		buffer[1] = DEC_NONE;
ADDS	R1, R2, #1
MOVS	R0, #0
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,174 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,176 :: 		buffer[0] = SCN_LMT;           //Scan Limit set to all ( show all leds )
ADD	R1, SP, #4
MOVS	R0, #11
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,177 :: 		buffer[1] = SCN_7;
LDR	R2, [SP, #8]
ADDS	R1, R2, #1
MOVS	R0, #7
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,178 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,180 :: 		buffer[0] = INTNS;             //Intensity set to max on init
ADD	R1, SP, #4
MOVS	R0, #10
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,181 :: 		buffer[1] = INTNS_31;
LDR	R2, [SP, #8]
ADDS	R1, R2, #1
MOVS	R0, #15
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,182 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,184 :: 		buffer[0] = DISP_TEST;         //Display Test set to Off
ADD	R1, SP, #4
MOVS	R0, #15
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,185 :: 		buffer[1] = 0x00;
LDR	R2, [SP, #8]
ADDS	R1, R2, #1
MOVS	R0, #0
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,186 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,188 :: 		buffer[0] = SHUT_DOWN;         //ShutDown Mode set to Normal Operation
ADD	R1, SP, #4
MOVS	R0, #12
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,189 :: 		buffer[1] = SHUT_DOWN_N;
LDR	R2, [SP, #8]
ADDS	R1, R2, #1
MOVS	R0, #1
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,190 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,192 :: 		return;
;eight_x_eight_hw.c,193 :: 		}
L_end_led_eight_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _led_eight_init
_led_eight_display_one_col:
;eight_x_eight_hw.c,196 :: 		void led_eight_display_one_col( uint8_t row, uint8_t col )
; col start address is: 4 (R1)
; row start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; col end address is: 4 (R1)
; row end address is: 0 (R0)
; row start address is: 0 (R0)
; col start address is: 4 (R1)
;eight_x_eight_hw.c,199 :: 		buffer[0] = 8 - row;
ADD	R3, SP, #4
RSB	R2, R0, #8
; row end address is: 0 (R0)
STRB	R2, [R3, #0]
;eight_x_eight_hw.c,200 :: 		buffer[1] = col;
ADDS	R2, R3, #1
STRB	R1, [R2, #0]
; col end address is: 4 (R1)
;eight_x_eight_hw.c,201 :: 		led_eight_hal_write( buffer );
MOV	R0, R3
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,203 :: 		return;
;eight_x_eight_hw.c,204 :: 		}
L_end_led_eight_display_one_col:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _led_eight_display_one_col
_led_eight_display_image:
;eight_x_eight_hw.c,206 :: 		void led_eight_display_image( uint8_t* image )
; image start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; image end address is: 0 (R0)
; image start address is: 0 (R0)
;eight_x_eight_hw.c,210 :: 		if( image == NULL )
CMP	R0, #0
IT	NE
BNE	L_led_eight_display_image12
; image end address is: 0 (R0)
;eight_x_eight_hw.c,211 :: 		return;
IT	AL
BAL	L_end_led_eight_display_image
L_led_eight_display_image12:
;eight_x_eight_hw.c,213 :: 		for( i = 0; i <=7; i++ )
; i start address is: 12 (R3)
; image start address is: 0 (R0)
MOVS	R3, #0
SXTH	R3, R3
; i end address is: 12 (R3)
L_led_eight_display_image13:
; i start address is: 12 (R3)
; image start address is: 0 (R0)
; image end address is: 0 (R0)
CMP	R3, #7
IT	GT
BGT	L_led_eight_display_image14
; image end address is: 0 (R0)
;eight_x_eight_hw.c,215 :: 		frame_buffer[i] = image[i];
; image start address is: 0 (R0)
MOVW	R1, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R1, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R2, R1, R3
ADDS	R1, R0, R3
LDRB	R1, [R1, #0]
STRB	R1, [R2, #0]
;eight_x_eight_hw.c,213 :: 		for( i = 0; i <=7; i++ )
ADDS	R3, R3, #1
SXTH	R3, R3
;eight_x_eight_hw.c,216 :: 		}
; image end address is: 0 (R0)
; i end address is: 12 (R3)
IT	AL
BAL	L_led_eight_display_image13
L_led_eight_display_image14:
;eight_x_eight_hw.c,217 :: 		refresh();
BL	eight_x_eight_hw_refresh+0
;eight_x_eight_hw.c,219 :: 		return;
;eight_x_eight_hw.c,220 :: 		}
L_end_led_eight_display_image:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _led_eight_display_image
_led_eight_display_const_image:
;eight_x_eight_hw.c,222 :: 		void led_eight_display_const_image( const uint8_t* image )
; image start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; image end address is: 0 (R0)
; image start address is: 0 (R0)
;eight_x_eight_hw.c,226 :: 		if( image == NULL )
CMP	R0, #0
IT	NE
BNE	L_led_eight_display_const_image16
; image end address is: 0 (R0)
;eight_x_eight_hw.c,227 :: 		return;
IT	AL
BAL	L_end_led_eight_display_const_image
L_led_eight_display_const_image16:
;eight_x_eight_hw.c,229 :: 		for( i = 0; i <=7; i++ )
; i start address is: 12 (R3)
; image start address is: 0 (R0)
MOVS	R3, #0
SXTH	R3, R3
; i end address is: 12 (R3)
L_led_eight_display_const_image17:
; i start address is: 12 (R3)
; image start address is: 0 (R0)
; image end address is: 0 (R0)
CMP	R3, #7
IT	GT
BGT	L_led_eight_display_const_image18
; image end address is: 0 (R0)
;eight_x_eight_hw.c,231 :: 		frame_buffer[i] = image[i];
; image start address is: 0 (R0)
MOVW	R1, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R1, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R2, R1, R3
ADDS	R1, R0, R3
LDRB	R1, [R1, #0]
STRB	R1, [R2, #0]
;eight_x_eight_hw.c,229 :: 		for( i = 0; i <=7; i++ )
ADDS	R3, R3, #1
SXTH	R3, R3
;eight_x_eight_hw.c,232 :: 		}
; image end address is: 0 (R0)
; i end address is: 12 (R3)
IT	AL
BAL	L_led_eight_display_const_image17
L_led_eight_display_const_image18:
;eight_x_eight_hw.c,233 :: 		refresh();
BL	eight_x_eight_hw_refresh+0
;eight_x_eight_hw.c,235 :: 		return;
;eight_x_eight_hw.c,236 :: 		}
L_end_led_eight_display_const_image:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _led_eight_display_const_image
_led_eight_display_string:
;eight_x_eight_hw.c,238 :: 		void led_eight_display_string( uint8_t* str, uint8_t delay )
; str start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R1, [SP, #8]
; str end address is: 0 (R0)
; str start address is: 0 (R0)
;eight_x_eight_hw.c,240 :: 		uint8_t *ptr = str;
STR	R0, [SP, #4]
;eight_x_eight_hw.c,243 :: 		if( ptr == NULL )
CMP	R0, #0
IT	NE
BNE	L_led_eight_display_string20
; str end address is: 0 (R0)
;eight_x_eight_hw.c,244 :: 		return;
IT	AL
BAL	L_end_led_eight_display_string
L_led_eight_display_string20:
;eight_x_eight_hw.c,246 :: 		while( *ptr != NULL )
L_led_eight_display_string21:
LDR	R2, [SP, #4]
LDRB	R2, [R2, #0]
CMP	R2, #0
IT	EQ
BEQ	L_led_eight_display_string22
;eight_x_eight_hw.c,248 :: 		for( i = 0; i < 8; i++ )
; i start address is: 20 (R5)
MOVS	R5, #0
SXTH	R5, R5
; i end address is: 20 (R5)
SXTH	R0, R5
L_led_eight_display_string23:
; i start address is: 0 (R0)
CMP	R0, #8
IT	GE
BGE	L_led_eight_display_string24
;eight_x_eight_hw.c,249 :: 		frame_buffer[i] = font[( *ptr * 8 ) + i];
MOVW	R2, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R2, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R4, R2, R0
LDR	R2, [SP, #4]
LDRB	R2, [R2, #0]
LSLS	R2, R2, #3
SXTH	R2, R2
ADDS	R3, R2, R0
SXTH	R3, R3
MOVW	R2, #lo_addr(_font+0)
MOVT	R2, #hi_addr(_font+0)
ADDS	R2, R2, R3
LDRB	R2, [R2, #0]
STRB	R2, [R4, #0]
;eight_x_eight_hw.c,248 :: 		for( i = 0; i < 8; i++ )
ADDS	R2, R0, #1
; i end address is: 0 (R0)
; i start address is: 20 (R5)
SXTH	R5, R2
;eight_x_eight_hw.c,249 :: 		frame_buffer[i] = font[( *ptr * 8 ) + i];
SXTH	R0, R5
; i end address is: 20 (R5)
IT	AL
BAL	L_led_eight_display_string23
L_led_eight_display_string24:
;eight_x_eight_hw.c,251 :: 		refresh();
BL	eight_x_eight_hw_refresh+0
;eight_x_eight_hw.c,252 :: 		vDelay_ms( delay );
LDRB	R0, [SP, #8]
BL	_VDelay_ms+0
;eight_x_eight_hw.c,253 :: 		ptr++;
LDR	R2, [SP, #4]
ADDS	R2, R2, #1
STR	R2, [SP, #4]
;eight_x_eight_hw.c,254 :: 		}
IT	AL
BAL	L_led_eight_display_string21
L_led_eight_display_string22:
;eight_x_eight_hw.c,255 :: 		}
L_end_led_eight_display_string:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _led_eight_display_string
_led_eight_scroll_text:
;eight_x_eight_hw.c,257 :: 		void led_eight_scroll_text( uint8_t* str, uint8_t delay)
; str start address is: 0 (R0)
SUB	SP, SP, #20
STR	LR, [SP, #0]
STRB	R1, [SP, #16]
; str end address is: 0 (R0)
; str start address is: 0 (R0)
;eight_x_eight_hw.c,259 :: 		uint8_t *ptr = str;          //Holds Pointer
STR	R0, [SP, #12]
; str end address is: 0 (R0)
;eight_x_eight_hw.c,260 :: 		uint8_t *p_font = 0;
;eight_x_eight_hw.c,263 :: 		memset( frame_buffer, 0, sizeof(frame_buffer) );
MOVS	R2, #8
SXTH	R2, R2
MOVS	R1, #0
MOVW	R0, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R0, #hi_addr(eight_x_eight_hw_frame_buffer+0)
BL	_memset+0
;eight_x_eight_hw.c,265 :: 		if( ptr == NULL )           //Sanity Check
LDR	R2, [SP, #12]
CMP	R2, #0
IT	NE
BNE	L_led_eight_scroll_text26
;eight_x_eight_hw.c,266 :: 		return;
IT	AL
BAL	L_end_led_eight_scroll_text
L_led_eight_scroll_text26:
;eight_x_eight_hw.c,270 :: 		while( *ptr != NULL )
L_led_eight_scroll_text27:
LDR	R2, [SP, #12]
LDRB	R2, [R2, #0]
CMP	R2, #0
IT	EQ
BEQ	L_led_eight_scroll_text28
;eight_x_eight_hw.c,272 :: 		for( i = 0, m = 8; i < 8; i++, m-- )
; i start address is: 24 (R6)
MOVS	R6, #0
SXTH	R6, R6
; m start address is: 20 (R5)
MOVS	R5, #8
SXTH	R5, R5
; i end address is: 24 (R6)
; m end address is: 20 (R5)
L_led_eight_scroll_text29:
; m start address is: 20 (R5)
; i start address is: 24 (R6)
CMP	R6, #8
IT	GE
BGE	L_led_eight_scroll_text30
;eight_x_eight_hw.c,274 :: 		for( j = 0, k = 8; j < 8; j++, k-- )
; j start address is: 28 (R7)
MOVS	R7, #0
SXTH	R7, R7
; j end address is: 28 (R7)
; i end address is: 24 (R6)
; m end address is: 20 (R5)
SXTH	R1, R6
SXTH	R0, R7
L_led_eight_scroll_text32:
; j start address is: 0 (R0)
; i start address is: 4 (R1)
; m start address is: 20 (R5)
CMP	R0, #8
IT	GE
BGE	L_led_eight_scroll_text33
;eight_x_eight_hw.c,276 :: 		frame_buffer[j] <<= 1;
MOVW	R2, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R2, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R3, R2, R0
LDRB	R2, [R3, #0]
LSLS	R2, R2, #1
STRB	R2, [R3, #0]
;eight_x_eight_hw.c,277 :: 		frame_buffer[j] |=  ( font[( *ptr * 8) + m ] & ( 1 << j) ) >> j;
MOVW	R2, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R2, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R4, R2, R0
LDR	R2, [SP, #12]
LDRB	R2, [R2, #0]
LSLS	R2, R2, #3
SXTH	R2, R2
ADDS	R3, R2, R5
SXTH	R3, R3
MOVW	R2, #lo_addr(_font+0)
MOVT	R2, #hi_addr(_font+0)
ADDS	R2, R2, R3
LDRB	R3, [R2, #0]
MOVS	R2, #1
SXTH	R2, R2
LSLS	R2, R0
SXTH	R2, R2
AND	R2, R3, R2, LSL #0
SXTH	R2, R2
ASR	R3, R2, R0
SXTH	R3, R3
LDRB	R2, [R4, #0]
ORRS	R2, R3
STRB	R2, [R4, #0]
;eight_x_eight_hw.c,278 :: 		scroll_refresh();
STRH	R5, [SP, #4]
STRH	R1, [SP, #6]
STRH	R0, [SP, #8]
BL	eight_x_eight_hw_scroll_refresh+0
LDRSH	R0, [SP, #8]
LDRSH	R1, [SP, #6]
LDRSH	R5, [SP, #4]
;eight_x_eight_hw.c,279 :: 		vDelay_ms( delay );
STRH	R1, [SP, #4]
STRH	R0, [SP, #6]
LDRB	R0, [SP, #16]
BL	_VDelay_ms+0
LDRSH	R0, [SP, #6]
LDRSH	R1, [SP, #4]
;eight_x_eight_hw.c,274 :: 		for( j = 0, k = 8; j < 8; j++, k-- )
ADDS	R2, R0, #1
; j end address is: 0 (R0)
; j start address is: 28 (R7)
SXTH	R7, R2
;eight_x_eight_hw.c,280 :: 		}
; j end address is: 28 (R7)
SXTH	R0, R7
IT	AL
BAL	L_led_eight_scroll_text32
L_led_eight_scroll_text33:
;eight_x_eight_hw.c,272 :: 		for( i = 0, m = 8; i < 8; i++, m-- )
ADDS	R2, R1, #1
; i end address is: 4 (R1)
; i start address is: 24 (R6)
SXTH	R6, R2
SUBS	R5, R5, #1
SXTH	R5, R5
;eight_x_eight_hw.c,282 :: 		}
; i end address is: 24 (R6)
; m end address is: 20 (R5)
IT	AL
BAL	L_led_eight_scroll_text29
L_led_eight_scroll_text30:
;eight_x_eight_hw.c,283 :: 		ptr++;
LDR	R2, [SP, #12]
ADDS	R2, R2, #1
STR	R2, [SP, #12]
;eight_x_eight_hw.c,284 :: 		}
IT	AL
BAL	L_led_eight_scroll_text27
L_led_eight_scroll_text28:
;eight_x_eight_hw.c,286 :: 		}
L_end_led_eight_scroll_text:
LDR	LR, [SP, #0]
ADD	SP, SP, #20
BX	LR
; end of _led_eight_scroll_text
_led_eight_display_shift_left:
;eight_x_eight_hw.c,288 :: 		void led_eight_display_shift_left()
SUB	SP, SP, #12
STR	LR, [SP, #0]
;eight_x_eight_hw.c,293 :: 		for( i = 0; i < 8; i++ )
; i start address is: 8 (R2)
MOVS	R2, #0
SXTH	R2, R2
; i end address is: 8 (R2)
L_led_eight_display_shift_left35:
; i start address is: 8 (R2)
CMP	R2, #8
IT	GE
BGE	L_led_eight_display_shift_left36
;eight_x_eight_hw.c,295 :: 		temp_buffer[i] = frame_buffer[i];
ADD	R0, SP, #4
ADDS	R1, R0, R2
MOVW	R0, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R0, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R0, R0, R2
LDRB	R0, [R0, #0]
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,293 :: 		for( i = 0; i < 8; i++ )
ADDS	R2, R2, #1
SXTH	R2, R2
;eight_x_eight_hw.c,296 :: 		}
; i end address is: 8 (R2)
IT	AL
BAL	L_led_eight_display_shift_left35
L_led_eight_display_shift_left36:
;eight_x_eight_hw.c,297 :: 		for( j = 7; j > 0; j-- )
; j start address is: 12 (R3)
MOVS	R3, #7
SXTH	R3, R3
; j end address is: 12 (R3)
L_led_eight_display_shift_left38:
; j start address is: 12 (R3)
CMP	R3, #0
IT	LE
BLE	L_led_eight_display_shift_left39
;eight_x_eight_hw.c,299 :: 		frame_buffer[j] = temp_buffer[ j - 1 ];
MOVW	R0, #lo_addr(eight_x_eight_hw_frame_buffer+0)
MOVT	R0, #hi_addr(eight_x_eight_hw_frame_buffer+0)
ADDS	R2, R0, R3
SUBS	R1, R3, #1
SXTH	R1, R1
ADD	R0, SP, #4
ADDS	R0, R0, R1
LDRB	R0, [R0, #0]
STRB	R0, [R2, #0]
;eight_x_eight_hw.c,297 :: 		for( j = 7; j > 0; j-- )
SUBS	R3, R3, #1
SXTH	R3, R3
;eight_x_eight_hw.c,300 :: 		}
; j end address is: 12 (R3)
IT	AL
BAL	L_led_eight_display_shift_left38
L_led_eight_display_shift_left39:
;eight_x_eight_hw.c,301 :: 		refresh();
BL	eight_x_eight_hw_refresh+0
;eight_x_eight_hw.c,303 :: 		return;
;eight_x_eight_hw.c,305 :: 		}
L_end_led_eight_display_shift_left:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _led_eight_display_shift_left
_led_eight_set_intensity:
;eight_x_eight_hw.c,307 :: 		void led_eight_set_intensity( uint8_t intensity )
; intensity start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; intensity end address is: 0 (R0)
; intensity start address is: 0 (R0)
;eight_x_eight_hw.c,311 :: 		if( intensity > 15 || intensity < 0 )
CMP	R0, #15
IT	HI
BHI	L__led_eight_set_intensity49
CMP	R0, #0
IT	CC
BCC	L__led_eight_set_intensity48
IT	AL
BAL	L_led_eight_set_intensity43
; intensity end address is: 0 (R0)
L__led_eight_set_intensity49:
L__led_eight_set_intensity48:
;eight_x_eight_hw.c,312 :: 		return;
IT	AL
BAL	L_end_led_eight_set_intensity
L_led_eight_set_intensity43:
;eight_x_eight_hw.c,314 :: 		buffer[0] = INTNS;
; intensity start address is: 0 (R0)
ADD	R2, SP, #4
MOVS	R1, #10
STRB	R1, [R2, #0]
;eight_x_eight_hw.c,315 :: 		buffer[1] = intensity;
ADDS	R1, R2, #1
STRB	R0, [R1, #0]
; intensity end address is: 0 (R0)
;eight_x_eight_hw.c,316 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,318 :: 		return;
;eight_x_eight_hw.c,319 :: 		}
L_end_led_eight_set_intensity:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _led_eight_set_intensity
_led_eight_set_scan_limit:
;eight_x_eight_hw.c,321 :: 		void led_eight_set_scan_limit( uint8_t scan_limit )
; scan_limit start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; scan_limit end address is: 0 (R0)
; scan_limit start address is: 0 (R0)
;eight_x_eight_hw.c,325 :: 		if( scan_limit > 7 || scan_limit < 0 )
CMP	R0, #7
IT	HI
BHI	L__led_eight_set_scan_limit52
CMP	R0, #0
IT	CC
BCC	L__led_eight_set_scan_limit51
IT	AL
BAL	L_led_eight_set_scan_limit46
; scan_limit end address is: 0 (R0)
L__led_eight_set_scan_limit52:
L__led_eight_set_scan_limit51:
;eight_x_eight_hw.c,326 :: 		return;
IT	AL
BAL	L_end_led_eight_set_scan_limit
L_led_eight_set_scan_limit46:
;eight_x_eight_hw.c,328 :: 		buffer[0] = SCN_LMT;
; scan_limit start address is: 0 (R0)
ADD	R2, SP, #4
MOVS	R1, #11
STRB	R1, [R2, #0]
;eight_x_eight_hw.c,329 :: 		buffer[1] = scan_limit;
ADDS	R1, R2, #1
STRB	R0, [R1, #0]
; scan_limit end address is: 0 (R0)
;eight_x_eight_hw.c,330 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,332 :: 		return;
;eight_x_eight_hw.c,333 :: 		}
L_end_led_eight_set_scan_limit:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _led_eight_set_scan_limit
_led_eight_shut_down:
;eight_x_eight_hw.c,335 :: 		void led_eight_shut_down( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;eight_x_eight_hw.c,339 :: 		buffer[0] = SHUT_DOWN;
ADD	R2, SP, #4
MOVS	R0, #12
STRB	R0, [R2, #0]
;eight_x_eight_hw.c,340 :: 		buffer[1] = SHUT_DOWN_D;
ADDS	R1, R2, #1
MOVS	R0, #0
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,341 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,343 :: 		return;
;eight_x_eight_hw.c,344 :: 		}
L_end_led_eight_shut_down:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _led_eight_shut_down
_led_eight_display_test:
;eight_x_eight_hw.c,346 :: 		void led_eight_display_test( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;eight_x_eight_hw.c,350 :: 		buffer[0] = DISP_TEST;
ADD	R2, SP, #4
MOVS	R0, #15
STRB	R0, [R2, #0]
;eight_x_eight_hw.c,351 :: 		buffer[1] = 0x01;
ADDS	R1, R2, #1
MOVS	R0, #1
STRB	R0, [R1, #0]
;eight_x_eight_hw.c,352 :: 		led_eight_hal_write( buffer );
MOV	R0, R2
BL	_led_eight_hal_write+0
;eight_x_eight_hw.c,354 :: 		return;
;eight_x_eight_hw.c,355 :: 		}
L_end_led_eight_display_test:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _led_eight_display_test
