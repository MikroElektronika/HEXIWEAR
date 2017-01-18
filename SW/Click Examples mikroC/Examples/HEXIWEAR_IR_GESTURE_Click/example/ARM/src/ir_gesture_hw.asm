ir_gesture_hw_get_mode:
;ir_gesture_hw.c,197 :: 		static uint8_t get_mode()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,202 :: 		ir_gesture_i2c_hal_read( APDS9960_ENABLE, &enable_value, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,204 :: 		return enable_value;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,205 :: 		}
L_end_get_mode:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of ir_gesture_hw_get_mode
ir_gesture_hw_set_mode:
;ir_gesture_hw.c,207 :: 		static void set_mode( ir_mode_t mode, bool enable )
; enable start address is: 4 (R1)
; mode start address is: 0 (R0)
SUB	SP, SP, #16
STR	LR, [SP, #0]
UXTB	R3, R0
; enable end address is: 4 (R1)
; mode end address is: 0 (R0)
; mode start address is: 12 (R3)
; enable start address is: 4 (R1)
;ir_gesture_hw.c,210 :: 		uint8_t reg_val = get_mode();
STRB	R1, [SP, #4]
STRB	R3, [SP, #8]
BL	ir_gesture_hw_get_mode+0
LDRB	R3, [SP, #8]
LDRB	R1, [SP, #4]
STRB	R0, [SP, #12]
;ir_gesture_hw.c,212 :: 		if( reg_val == ERROR )
CMP	R0, #255
IT	NE
BNE	L_ir_gesture_hw_set_mode0
; mode end address is: 12 (R3)
; enable end address is: 4 (R1)
;ir_gesture_hw.c,213 :: 		return;
IT	AL
BAL	L_end_set_mode
L_ir_gesture_hw_set_mode0:
;ir_gesture_hw.c,215 :: 		mode = MIN( mode, ALL );
; enable start address is: 4 (R1)
; mode start address is: 12 (R3)
CMP	R3, #7
IT	CS
BCS	L_ir_gesture_hw_set_mode1
; ?FLOC__ir_gesture_hw_set_mode?T3 start address is: 0 (R0)
UXTB	R0, R3
; mode end address is: 12 (R3)
UXTB	R2, R0
; ?FLOC__ir_gesture_hw_set_mode?T3 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_hw_set_mode2
L_ir_gesture_hw_set_mode1:
; ?FLOC__ir_gesture_hw_set_mode?T3 start address is: 8 (R2)
MOVS	R2, #7
; ?FLOC__ir_gesture_hw_set_mode?T3 end address is: 8 (R2)
L_ir_gesture_hw_set_mode2:
; ?FLOC__ir_gesture_hw_set_mode?T3 start address is: 8 (R2)
; mode start address is: 0 (R0)
UXTB	R0, R2
;ir_gesture_hw.c,217 :: 		if( mode == ALL )
CMP	R2, #7
IT	NE
BNE	L_ir_gesture_hw_set_mode3
; ?FLOC__ir_gesture_hw_set_mode?T3 end address is: 8 (R2)
; mode end address is: 0 (R0)
;ir_gesture_hw.c,219 :: 		reg_val = 0x00;
MOVS	R2, #0
STRB	R2, [SP, #12]
;ir_gesture_hw.c,221 :: 		if( enable )
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_hw_set_mode4
; enable end address is: 4 (R1)
;ir_gesture_hw.c,222 :: 		reg_val = 0x7F;
MOVS	R2, #127
STRB	R2, [SP, #12]
L_ir_gesture_hw_set_mode4:
;ir_gesture_hw.c,223 :: 		} else {
IT	AL
BAL	L_ir_gesture_hw_set_mode5
L_ir_gesture_hw_set_mode3:
;ir_gesture_hw.c,224 :: 		reg_val &= ~( 1 << mode );
; mode start address is: 0 (R0)
; enable start address is: 4 (R1)
MOVS	R2, #1
SXTH	R2, R2
LSLS	R2, R0
SXTH	R2, R2
MVN	R3, R2
SXTH	R3, R3
LDRB	R2, [SP, #12]
ANDS	R2, R3
STRB	R2, [SP, #12]
;ir_gesture_hw.c,226 :: 		if( enable )
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_hw_set_mode6
; enable end address is: 4 (R1)
;ir_gesture_hw.c,227 :: 		reg_val |= ( 1 << mode );
MOVS	R2, #1
SXTH	R2, R2
LSL	R3, R2, R0
SXTH	R3, R3
; mode end address is: 0 (R0)
LDRB	R2, [SP, #12]
ORRS	R2, R3
STRB	R2, [SP, #12]
L_ir_gesture_hw_set_mode6:
;ir_gesture_hw.c,228 :: 		}
L_ir_gesture_hw_set_mode5:
;ir_gesture_hw.c,231 :: 		ir_gesture_i2c_hal_write( APDS9960_ENABLE, &reg_val, 1 );
ADD	R2, SP, #12
MOV	R1, R2
MOVS	R2, #1
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,232 :: 		}
L_end_set_mode:
LDR	LR, [SP, #0]
ADD	SP, SP, #16
BX	LR
; end of ir_gesture_hw_set_mode
ir_gesture_hw_process_gesture_data:
;ir_gesture_hw.c,234 :: 		static uint8_t process_gesture_data( gesture_data_t *gesture_data )
; gesture_data start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; gesture_data end address is: 0 (R0)
; gesture_data start address is: 0 (R0)
;ir_gesture_hw.c,236 :: 		uint8_t u_first = 0;
ADD	R11, SP, #4
ADD	R10, R11, #8
MOVW	R12, #lo_addr(?ICSir_gesture_hw_process_gesture_data_u_first_L0+0)
MOVT	R12, #hi_addr(?ICSir_gesture_hw_process_gesture_data_u_first_L0+0)
BL	___CC2DW+0
;ir_gesture_hw.c,237 :: 		uint8_t d_first = 0;
;ir_gesture_hw.c,238 :: 		uint8_t l_first = 0;
;ir_gesture_hw.c,239 :: 		uint8_t r_first = 0;
;ir_gesture_hw.c,240 :: 		uint8_t u_last = 0;
;ir_gesture_hw.c,241 :: 		uint8_t d_last = 0;
;ir_gesture_hw.c,242 :: 		uint8_t l_last = 0;
;ir_gesture_hw.c,243 :: 		uint8_t r_last = 0;
;ir_gesture_hw.c,253 :: 		if( gesture_data->total_gestures <= 4 )
ADDW	R1, R0, #129
LDRB	R1, [R1, #0]
CMP	R1, #4
IT	HI
BHI	L_ir_gesture_hw_process_gesture_data7
; gesture_data end address is: 0 (R0)
;ir_gesture_hw.c,254 :: 		return -1;
MOVS	R0, #-1
IT	AL
BAL	L_end_process_gesture_data
L_ir_gesture_hw_process_gesture_data7:
;ir_gesture_hw.c,257 :: 		if( ( gesture_data->total_gestures <= 32 ) && ( gesture_data->total_gestures > 0 ) )
; gesture_data start address is: 0 (R0)
ADDW	R1, R0, #129
LDRB	R1, [R1, #0]
CMP	R1, #32
IT	HI
BHI	L_ir_gesture_hw_process_gesture_data206
ADDW	R1, R0, #129
LDRB	R1, [R1, #0]
CMP	R1, #0
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data207
L_ir_gesture_hw_process_gesture_data173:
;ir_gesture_hw.c,260 :: 		for( i = 0; i < gesture_data->total_gestures; i++ )
; i start address is: 28 (R7)
MOVS	R7, #0
SXTH	R7, R7
; i end address is: 28 (R7)
; gesture_data end address is: 0 (R0)
SXTH	R2, R7
L_ir_gesture_hw_process_gesture_data11:
; i start address is: 8 (R2)
; gesture_data start address is: 0 (R0)
ADDW	R1, R0, #129
LDRB	R1, [R1, #0]
CMP	R2, R1
IT	GE
BGE	L_ir_gesture_hw_process_gesture_data12
;ir_gesture_hw.c,262 :: 		if( ( gesture_data->u_data[i] > GESTURE_THRESHOLD_OUT ) &&
ADDS	R1, R0, R2
LDRB	R1, [R1, #0]
;ir_gesture_hw.c,263 :: 		( gesture_data->d_data[i] > GESTURE_THRESHOLD_OUT ) &&
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data177
ADDW	R1, R0, #32
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data176
;ir_gesture_hw.c,264 :: 		( gesture_data->l_data[i] > GESTURE_THRESHOLD_OUT ) &&
ADDW	R1, R0, #64
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data175
;ir_gesture_hw.c,265 :: 		( gesture_data->r_data[i] > GESTURE_THRESHOLD_OUT ) )
ADDW	R1, R0, #96
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data174
L_ir_gesture_hw_process_gesture_data172:
;ir_gesture_hw.c,268 :: 		u_first = gesture_data->u_data[i];
ADDS	R1, R0, R2
LDRB	R1, [R1, #0]
STRB	R1, [SP, #4]
;ir_gesture_hw.c,269 :: 		d_first = gesture_data->d_data[i];
ADDW	R1, R0, #32
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
STRB	R1, [SP, #5]
;ir_gesture_hw.c,270 :: 		l_first = gesture_data->l_data[i];
ADDW	R1, R0, #64
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
STRB	R1, [SP, #6]
;ir_gesture_hw.c,271 :: 		r_first = gesture_data->r_data[i];
ADDW	R1, R0, #96
ADDS	R1, R1, R2
; i end address is: 8 (R2)
LDRB	R1, [R1, #0]
STRB	R1, [SP, #7]
;ir_gesture_hw.c,272 :: 		break;
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data12
;ir_gesture_hw.c,263 :: 		( gesture_data->d_data[i] > GESTURE_THRESHOLD_OUT ) &&
L_ir_gesture_hw_process_gesture_data177:
; i start address is: 8 (R2)
L_ir_gesture_hw_process_gesture_data176:
;ir_gesture_hw.c,264 :: 		( gesture_data->l_data[i] > GESTURE_THRESHOLD_OUT ) &&
L_ir_gesture_hw_process_gesture_data175:
;ir_gesture_hw.c,265 :: 		( gesture_data->r_data[i] > GESTURE_THRESHOLD_OUT ) )
L_ir_gesture_hw_process_gesture_data174:
;ir_gesture_hw.c,260 :: 		for( i = 0; i < gesture_data->total_gestures; i++ )
ADDS	R1, R2, #1
; i end address is: 8 (R2)
; i start address is: 28 (R7)
SXTH	R7, R1
;ir_gesture_hw.c,274 :: 		}
; i end address is: 28 (R7)
SXTH	R2, R7
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data11
L_ir_gesture_hw_process_gesture_data12:
;ir_gesture_hw.c,277 :: 		if( ( u_first == 0 ) || ( d_first == 0 ) ||
LDRB	R1, [SP, #4]
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_hw_process_gesture_data181
LDRB	R1, [SP, #5]
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_hw_process_gesture_data180
;ir_gesture_hw.c,278 :: 		( l_first == 0 ) || ( r_first == 0 ) )
LDRB	R1, [SP, #6]
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_hw_process_gesture_data179
LDRB	R1, [SP, #7]
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_hw_process_gesture_data178
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data19
; gesture_data end address is: 0 (R0)
;ir_gesture_hw.c,277 :: 		if( ( u_first == 0 ) || ( d_first == 0 ) ||
L_ir_gesture_hw_process_gesture_data181:
L_ir_gesture_hw_process_gesture_data180:
;ir_gesture_hw.c,278 :: 		( l_first == 0 ) || ( r_first == 0 ) )
L_ir_gesture_hw_process_gesture_data179:
L_ir_gesture_hw_process_gesture_data178:
;ir_gesture_hw.c,279 :: 		return -1;
MOVS	R0, #-1
IT	AL
BAL	L_end_process_gesture_data
L_ir_gesture_hw_process_gesture_data19:
;ir_gesture_hw.c,281 :: 		for( i = gesture_data->total_gestures - 1; i >= 0; i-- )
; gesture_data start address is: 0 (R0)
ADDW	R1, R0, #129
LDRB	R1, [R1, #0]
SUBS	R2, R1, #1
SXTH	R2, R2
; i start address is: 8 (R2)
; i end address is: 8 (R2)
; gesture_data end address is: 0 (R0)
L_ir_gesture_hw_process_gesture_data20:
; i start address is: 8 (R2)
; gesture_data start address is: 0 (R0)
CMP	R2, #0
IT	LT
BLT	L_ir_gesture_hw_process_gesture_data21
;ir_gesture_hw.c,283 :: 		if( ( gesture_data->u_data[i] > GESTURE_THRESHOLD_OUT ) &&
ADDS	R1, R0, R2
LDRB	R1, [R1, #0]
;ir_gesture_hw.c,284 :: 		( gesture_data->d_data[i] > GESTURE_THRESHOLD_OUT ) &&
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data185
ADDW	R1, R0, #32
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data184
;ir_gesture_hw.c,285 :: 		( gesture_data->l_data[i] > GESTURE_THRESHOLD_OUT ) &&
ADDW	R1, R0, #64
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data183
;ir_gesture_hw.c,286 :: 		( gesture_data->r_data[i] > GESTURE_THRESHOLD_OUT ) )
ADDW	R1, R0, #96
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
CMP	R1, #10
IT	LS
BLS	L_ir_gesture_hw_process_gesture_data182
L_ir_gesture_hw_process_gesture_data170:
;ir_gesture_hw.c,289 :: 		u_last = gesture_data->u_data[i];
ADDS	R1, R0, R2
LDRB	R1, [R1, #0]
STRB	R1, [SP, #8]
;ir_gesture_hw.c,290 :: 		d_last = gesture_data->d_data[i];
ADDW	R1, R0, #32
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
STRB	R1, [SP, #9]
;ir_gesture_hw.c,291 :: 		l_last = gesture_data->l_data[i];
ADDW	R1, R0, #64
ADDS	R1, R1, R2
LDRB	R1, [R1, #0]
STRB	R1, [SP, #10]
;ir_gesture_hw.c,292 :: 		r_last = gesture_data->r_data[i];
ADDW	R1, R0, #96
ADDS	R1, R1, R2
; i end address is: 8 (R2)
LDRB	R1, [R1, #0]
STRB	R1, [SP, #11]
;ir_gesture_hw.c,293 :: 		break;
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data21
;ir_gesture_hw.c,284 :: 		( gesture_data->d_data[i] > GESTURE_THRESHOLD_OUT ) &&
L_ir_gesture_hw_process_gesture_data185:
; i start address is: 8 (R2)
L_ir_gesture_hw_process_gesture_data184:
;ir_gesture_hw.c,285 :: 		( gesture_data->l_data[i] > GESTURE_THRESHOLD_OUT ) &&
L_ir_gesture_hw_process_gesture_data183:
;ir_gesture_hw.c,286 :: 		( gesture_data->r_data[i] > GESTURE_THRESHOLD_OUT ) )
L_ir_gesture_hw_process_gesture_data182:
;ir_gesture_hw.c,281 :: 		for( i = gesture_data->total_gestures - 1; i >= 0; i-- )
SUBS	R1, R2, #1
; i end address is: 8 (R2)
; i start address is: 24 (R6)
SXTH	R6, R1
;ir_gesture_hw.c,295 :: 		}
; i end address is: 24 (R6)
SXTH	R2, R6
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data20
L_ir_gesture_hw_process_gesture_data21:
;ir_gesture_hw.c,257 :: 		if( ( gesture_data->total_gestures <= 32 ) && ( gesture_data->total_gestures > 0 ) )
MOV	R6, R0
; gesture_data end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data187
L_ir_gesture_hw_process_gesture_data206:
MOV	R6, R0
L_ir_gesture_hw_process_gesture_data187:
; gesture_data start address is: 24 (R6)
MOV	R7, R6
; gesture_data end address is: 24 (R6)
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data186
L_ir_gesture_hw_process_gesture_data207:
MOV	R7, R0
L_ir_gesture_hw_process_gesture_data186:
;ir_gesture_hw.c,299 :: 		ud_ratio_first = ( ( u_first - d_first ) * 100 ) / ( u_first + d_first );
; gesture_data start address is: 28 (R7)
LDRB	R2, [SP, #5]
LDRB	R1, [SP, #4]
SUB	R2, R1, R2
SXTH	R2, R2
MOVS	R1, #100
SXTH	R1, R1
MUL	R3, R2, R1
SXTH	R3, R3
LDRB	R2, [SP, #5]
LDRB	R1, [SP, #4]
ADDS	R1, R1, R2
SXTH	R1, R1
SDIV	R6, R3, R1
SXTH	R6, R6
;ir_gesture_hw.c,300 :: 		lr_ratio_first = ( ( l_first - r_first ) * 100 ) / ( l_first + r_first );
LDRB	R2, [SP, #7]
LDRB	R1, [SP, #6]
SUB	R2, R1, R2
SXTH	R2, R2
MOVS	R1, #100
SXTH	R1, R1
MUL	R3, R2, R1
SXTH	R3, R3
LDRB	R2, [SP, #7]
LDRB	R1, [SP, #6]
ADDS	R1, R1, R2
SXTH	R1, R1
SDIV	R5, R3, R1
SXTH	R5, R5
;ir_gesture_hw.c,301 :: 		ud_ratio_last = ( ( u_last - d_last ) * 100 ) / ( u_last + d_last );
LDRB	R2, [SP, #9]
LDRB	R1, [SP, #8]
SUB	R2, R1, R2
SXTH	R2, R2
MOVS	R1, #100
SXTH	R1, R1
MUL	R3, R2, R1
SXTH	R3, R3
LDRB	R2, [SP, #9]
LDRB	R1, [SP, #8]
ADDS	R1, R1, R2
SXTH	R1, R1
SDIV	R4, R3, R1
SXTH	R4, R4
;ir_gesture_hw.c,302 :: 		lr_ratio_last = ( ( l_last - r_last ) * 100 ) / ( l_last + r_last );
LDRB	R2, [SP, #11]
LDRB	R1, [SP, #10]
SUB	R2, R1, R2
SXTH	R2, R2
MOVS	R1, #100
SXTH	R1, R1
MUL	R3, R2, R1
SXTH	R3, R3
LDRB	R2, [SP, #11]
LDRB	R1, [SP, #10]
ADDS	R1, R1, R2
SXTH	R1, R1
SDIV	R1, R3, R1
SXTH	R1, R1
;ir_gesture_hw.c,305 :: 		ud_delta = ud_ratio_last - ud_ratio_first;
SUB	R3, R4, R6
SXTH	R3, R3
; ud_delta start address is: 16 (R4)
SXTH	R4, R3
;ir_gesture_hw.c,306 :: 		lr_delta = lr_ratio_last - lr_ratio_first;
SUB	R1, R1, R5
; lr_delta start address is: 20 (R5)
SXTH	R5, R1
;ir_gesture_hw.c,309 :: 		gesture_data->ud_delta += ud_delta;
ADDW	R2, R7, #132
LDRSH	R1, [R2, #0]
ADDS	R1, R1, R3
STRH	R1, [R2, #0]
;ir_gesture_hw.c,310 :: 		gesture_data->lr_delta += lr_delta;
ADDW	R2, R7, #134
LDRSH	R1, [R2, #0]
ADDS	R1, R1, R5
STRH	R1, [R2, #0]
;ir_gesture_hw.c,313 :: 		if( gesture_data->ud_delta >= GESTURE_SENSITIVITY_1 )
ADDW	R1, R7, #132
LDRSH	R1, [R1, #0]
CMP	R1, #50
IT	LT
BLT	L_ir_gesture_hw_process_gesture_data26
;ir_gesture_hw.c,314 :: 		gesture_data->ud_count = 1;
ADDW	R2, R7, #136
MOVS	R1, #1
SXTH	R1, R1
STRH	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data27
L_ir_gesture_hw_process_gesture_data26:
;ir_gesture_hw.c,315 :: 		else if( gesture_data->ud_delta <= -GESTURE_SENSITIVITY_1 )
ADDW	R1, R7, #132
LDRSH	R2, [R1, #0]
MVN	R1, #49
CMP	R2, R1
IT	GT
BGT	L_ir_gesture_hw_process_gesture_data28
;ir_gesture_hw.c,316 :: 		gesture_data->ud_count = -1;
ADDW	R2, R7, #136
MOVW	R1, #65535
SXTH	R1, R1
STRH	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data29
L_ir_gesture_hw_process_gesture_data28:
;ir_gesture_hw.c,318 :: 		gesture_data->ud_count = 0;
ADDW	R2, R7, #136
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [R2, #0]
L_ir_gesture_hw_process_gesture_data29:
L_ir_gesture_hw_process_gesture_data27:
;ir_gesture_hw.c,321 :: 		if( gesture_data->lr_delta >= GESTURE_SENSITIVITY_1 )
ADDW	R1, R7, #134
LDRSH	R1, [R1, #0]
CMP	R1, #50
IT	LT
BLT	L_ir_gesture_hw_process_gesture_data30
;ir_gesture_hw.c,322 :: 		gesture_data->lr_count = 1;
ADDW	R2, R7, #138
MOVS	R1, #1
SXTH	R1, R1
STRH	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data31
L_ir_gesture_hw_process_gesture_data30:
;ir_gesture_hw.c,323 :: 		else if( gesture_data->lr_delta <= -GESTURE_SENSITIVITY_1 )
ADDW	R1, R7, #134
LDRSH	R2, [R1, #0]
MVN	R1, #49
CMP	R2, R1
IT	GT
BGT	L_ir_gesture_hw_process_gesture_data32
;ir_gesture_hw.c,324 :: 		gesture_data->lr_count = -1;
ADDW	R2, R7, #138
MOVW	R1, #65535
SXTH	R1, R1
STRH	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data33
L_ir_gesture_hw_process_gesture_data32:
;ir_gesture_hw.c,326 :: 		gesture_data->lr_count = 0;
ADDW	R2, R7, #138
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [R2, #0]
L_ir_gesture_hw_process_gesture_data33:
L_ir_gesture_hw_process_gesture_data31:
;ir_gesture_hw.c,329 :: 		if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 0 ) )
ADDW	R1, R7, #136
LDRSH	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data201
ADDW	R1, R7, #138
LDRSH	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data200
L_ir_gesture_hw_process_gesture_data169:
;ir_gesture_hw.c,331 :: 		if( ( abs( ud_delta ) < GESTURE_SENSITIVITY_2 ) &&
SXTH	R0, R4
BL	_abs+0
;ir_gesture_hw.c,332 :: 		( abs( lr_delta ) < GESTURE_SENSITIVITY_2 ) )
CMP	R0, #20
IT	GE
BGE	L_ir_gesture_hw_process_gesture_data199
SXTH	R0, R5
BL	_abs+0
CMP	R0, #20
IT	GE
BGE	L_ir_gesture_hw_process_gesture_data198
L_ir_gesture_hw_process_gesture_data168:
;ir_gesture_hw.c,334 :: 		if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
CMP	R4, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data189
CMP	R5, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data188
L_ir_gesture_hw_process_gesture_data167:
;ir_gesture_hw.c,335 :: 		gesture_data->near_count++;
ADDW	R2, R7, #140
LDRSH	R1, [R2, #0]
ADDS	R1, R1, #1
STRH	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data43
;ir_gesture_hw.c,334 :: 		if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
L_ir_gesture_hw_process_gesture_data189:
L_ir_gesture_hw_process_gesture_data188:
;ir_gesture_hw.c,336 :: 		else if( ( ud_delta != 0 ) || ( lr_delta != 0 ) )
CMP	R4, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data191
CMP	R5, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data190
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data46
L_ir_gesture_hw_process_gesture_data191:
L_ir_gesture_hw_process_gesture_data190:
;ir_gesture_hw.c,337 :: 		gesture_data->far_count++;
ADDW	R2, R7, #142
LDRSH	R1, [R2, #0]
ADDS	R1, R1, #1
STRH	R1, [R2, #0]
L_ir_gesture_hw_process_gesture_data46:
L_ir_gesture_hw_process_gesture_data43:
;ir_gesture_hw.c,339 :: 		if( ( gesture_data->near_count >= 10 ) &&
ADDW	R1, R7, #140
LDRSH	R1, [R1, #0]
;ir_gesture_hw.c,340 :: 		( gesture_data->far_count >= 2 ) )
CMP	R1, #10
IT	LT
BLT	L_ir_gesture_hw_process_gesture_data197
ADDW	R1, R7, #142
LDRSH	R1, [R1, #0]
CMP	R1, #2
IT	LT
BLT	L_ir_gesture_hw_process_gesture_data196
L_ir_gesture_hw_process_gesture_data165:
;ir_gesture_hw.c,342 :: 		if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
CMP	R4, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data193
CMP	R5, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data192
; ud_delta end address is: 16 (R4)
; lr_delta end address is: 20 (R5)
L_ir_gesture_hw_process_gesture_data164:
;ir_gesture_hw.c,343 :: 		gesture_data->state = NEAR_STATE;
ADDW	R2, R7, #144
; gesture_data end address is: 28 (R7)
MOVS	R1, #1
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data53
;ir_gesture_hw.c,342 :: 		if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
L_ir_gesture_hw_process_gesture_data193:
; lr_delta start address is: 20 (R5)
; ud_delta start address is: 16 (R4)
; gesture_data start address is: 28 (R7)
L_ir_gesture_hw_process_gesture_data192:
;ir_gesture_hw.c,344 :: 		else if( ( ud_delta != 0 ) && ( lr_delta != 0 ) )
CMP	R4, #0
IT	EQ
BEQ	L_ir_gesture_hw_process_gesture_data195
; ud_delta end address is: 16 (R4)
CMP	R5, #0
IT	EQ
BEQ	L_ir_gesture_hw_process_gesture_data194
; lr_delta end address is: 20 (R5)
L_ir_gesture_hw_process_gesture_data163:
;ir_gesture_hw.c,345 :: 		gesture_data->state = FAR_STATE;
ADDW	R2, R7, #144
; gesture_data end address is: 28 (R7)
MOVS	R1, #2
STRB	R1, [R2, #0]
;ir_gesture_hw.c,344 :: 		else if( ( ud_delta != 0 ) && ( lr_delta != 0 ) )
L_ir_gesture_hw_process_gesture_data195:
L_ir_gesture_hw_process_gesture_data194:
;ir_gesture_hw.c,345 :: 		gesture_data->state = FAR_STATE;
L_ir_gesture_hw_process_gesture_data53:
;ir_gesture_hw.c,346 :: 		return 0;
MOVS	R0, #0
IT	AL
BAL	L_end_process_gesture_data
;ir_gesture_hw.c,340 :: 		( gesture_data->far_count >= 2 ) )
L_ir_gesture_hw_process_gesture_data197:
L_ir_gesture_hw_process_gesture_data196:
;ir_gesture_hw.c,332 :: 		( abs( lr_delta ) < GESTURE_SENSITIVITY_2 ) )
L_ir_gesture_hw_process_gesture_data199:
L_ir_gesture_hw_process_gesture_data198:
;ir_gesture_hw.c,349 :: 		} else {
IT	AL
BAL	L_ir_gesture_hw_process_gesture_data57
;ir_gesture_hw.c,329 :: 		if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 0 ) )
L_ir_gesture_hw_process_gesture_data201:
; lr_delta start address is: 20 (R5)
; ud_delta start address is: 16 (R4)
; gesture_data start address is: 28 (R7)
L_ir_gesture_hw_process_gesture_data200:
;ir_gesture_hw.c,350 :: 		if( ( abs( ud_delta ) < GESTURE_SENSITIVITY_2 ) &&
SXTH	R0, R4
BL	_abs+0
;ir_gesture_hw.c,351 :: 		( abs( lr_delta ) < GESTURE_SENSITIVITY_2 ) )
CMP	R0, #20
IT	GE
BGE	L_ir_gesture_hw_process_gesture_data205
SXTH	R0, R5
BL	_abs+0
CMP	R0, #20
IT	GE
BGE	L_ir_gesture_hw_process_gesture_data204
L_ir_gesture_hw_process_gesture_data162:
;ir_gesture_hw.c,353 :: 		if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
CMP	R4, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data203
; ud_delta end address is: 16 (R4)
CMP	R5, #0
IT	NE
BNE	L_ir_gesture_hw_process_gesture_data202
; lr_delta end address is: 20 (R5)
L_ir_gesture_hw_process_gesture_data161:
;ir_gesture_hw.c,354 :: 		gesture_data->near_count++;
ADDW	R2, R7, #140
LDRSH	R1, [R2, #0]
ADDS	R1, R1, #1
STRH	R1, [R2, #0]
;ir_gesture_hw.c,353 :: 		if( ( ud_delta == 0 ) && ( lr_delta == 0 ) )
L_ir_gesture_hw_process_gesture_data203:
L_ir_gesture_hw_process_gesture_data202:
;ir_gesture_hw.c,356 :: 		if( gesture_data->near_count >= 10 )
ADDW	R1, R7, #140
LDRSH	R1, [R1, #0]
CMP	R1, #10
IT	LT
BLT	L_ir_gesture_hw_process_gesture_data64
;ir_gesture_hw.c,358 :: 		gesture_data->ud_count = 0;
ADDW	R2, R7, #136
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [R2, #0]
;ir_gesture_hw.c,359 :: 		gesture_data->lr_count = 0;
ADDW	R2, R7, #138
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [R2, #0]
;ir_gesture_hw.c,360 :: 		gesture_data->ud_delta = 0;
ADDW	R2, R7, #132
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [R2, #0]
;ir_gesture_hw.c,361 :: 		gesture_data->lr_delta = 0;
ADDW	R2, R7, #134
; gesture_data end address is: 28 (R7)
MOVS	R1, #0
SXTH	R1, R1
STRH	R1, [R2, #0]
;ir_gesture_hw.c,362 :: 		}
L_ir_gesture_hw_process_gesture_data64:
;ir_gesture_hw.c,351 :: 		( abs( lr_delta ) < GESTURE_SENSITIVITY_2 ) )
L_ir_gesture_hw_process_gesture_data205:
L_ir_gesture_hw_process_gesture_data204:
;ir_gesture_hw.c,364 :: 		}
L_ir_gesture_hw_process_gesture_data57:
;ir_gesture_hw.c,365 :: 		return -1;
MOVS	R0, #-1
;ir_gesture_hw.c,366 :: 		}
L_end_process_gesture_data:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of ir_gesture_hw_process_gesture_data
ir_gesture_hw_decode_gesture:
;ir_gesture_hw.c,369 :: 		static uint8_t decode_gesture( gesture_data_t *gesture_data )
; gesture_data start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
MOV	R3, R0
; gesture_data end address is: 0 (R0)
; gesture_data start address is: 12 (R3)
;ir_gesture_hw.c,372 :: 		if( gesture_data->state == NEAR_STATE )
ADDW	R1, R3, #144
LDRB	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture65
;ir_gesture_hw.c,374 :: 		gesture_data->motion = DIR_NEAR;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #5
STRB	R1, [R2, #0]
;ir_gesture_hw.c,375 :: 		return 0;
MOVS	R0, #0
IT	AL
BAL	L_end_decode_gesture
;ir_gesture_hw.c,376 :: 		} else if ( gesture_data->state == FAR_STATE ) {
L_ir_gesture_hw_decode_gesture65:
; gesture_data start address is: 12 (R3)
ADDW	R1, R3, #144
LDRB	R1, [R1, #0]
CMP	R1, #2
IT	NE
BNE	L_ir_gesture_hw_decode_gesture67
;ir_gesture_hw.c,377 :: 		gesture_data->motion = DIR_FAR;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #6
STRB	R1, [R2, #0]
;ir_gesture_hw.c,378 :: 		return 0;
MOVS	R0, #0
IT	AL
BAL	L_end_decode_gesture
;ir_gesture_hw.c,379 :: 		}
L_ir_gesture_hw_decode_gesture67:
;ir_gesture_hw.c,382 :: 		if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 0 ) )
; gesture_data start address is: 12 (R3)
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #-1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture217
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_hw_decode_gesture216
L_ir_gesture_hw_decode_gesture215:
;ir_gesture_hw.c,383 :: 		gesture_data->motion = DIR_UP;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #3
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture71
;ir_gesture_hw.c,382 :: 		if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 0 ) )
L_ir_gesture_hw_decode_gesture217:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture216:
;ir_gesture_hw.c,384 :: 		else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 0) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture219
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_hw_decode_gesture218
L_ir_gesture_hw_decode_gesture214:
;ir_gesture_hw.c,385 :: 		gesture_data->motion = DIR_DOWN;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #4
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture75
;ir_gesture_hw.c,384 :: 		else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 0) )
L_ir_gesture_hw_decode_gesture219:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture218:
;ir_gesture_hw.c,386 :: 		else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 1) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_hw_decode_gesture221
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture220
L_ir_gesture_hw_decode_gesture213:
;ir_gesture_hw.c,387 :: 		gesture_data->motion = DIR_RIGHT;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #2
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture79
;ir_gesture_hw.c,386 :: 		else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == 1) )
L_ir_gesture_hw_decode_gesture221:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture220:
;ir_gesture_hw.c,388 :: 		else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == -1) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_hw_decode_gesture223
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #-1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture222
L_ir_gesture_hw_decode_gesture212:
;ir_gesture_hw.c,389 :: 		gesture_data->motion = DIR_LEFT;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #1
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture83
;ir_gesture_hw.c,388 :: 		else if( ( gesture_data->ud_count == 0 ) && ( gesture_data->lr_count == -1) )
L_ir_gesture_hw_decode_gesture223:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture222:
;ir_gesture_hw.c,390 :: 		else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 1) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #-1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture225
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture224
L_ir_gesture_hw_decode_gesture211:
;ir_gesture_hw.c,392 :: 		if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
ADDW	R1, R3, #132
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
STRH	R0, [SP, #4]
ADDW	R1, R3, #134
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
LDRSH	R1, [SP, #4]
CMP	R1, R0
IT	LE
BLE	L_ir_gesture_hw_decode_gesture87
;ir_gesture_hw.c,393 :: 		gesture_data->motion = DIR_UP;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #3
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture88
L_ir_gesture_hw_decode_gesture87:
;ir_gesture_hw.c,395 :: 		gesture_data->motion = DIR_RIGHT;
; gesture_data start address is: 12 (R3)
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #2
STRB	R1, [R2, #0]
L_ir_gesture_hw_decode_gesture88:
;ir_gesture_hw.c,396 :: 		}
IT	AL
BAL	L_ir_gesture_hw_decode_gesture89
;ir_gesture_hw.c,390 :: 		else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == 1) )
L_ir_gesture_hw_decode_gesture225:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture224:
;ir_gesture_hw.c,397 :: 		else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == -1) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture227
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #-1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture226
L_ir_gesture_hw_decode_gesture210:
;ir_gesture_hw.c,399 :: 		if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
ADDW	R1, R3, #132
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
STRH	R0, [SP, #4]
ADDW	R1, R3, #134
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
LDRSH	R1, [SP, #4]
CMP	R1, R0
IT	LE
BLE	L_ir_gesture_hw_decode_gesture93
;ir_gesture_hw.c,400 :: 		gesture_data->motion = DIR_DOWN;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #4
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture94
L_ir_gesture_hw_decode_gesture93:
;ir_gesture_hw.c,402 :: 		gesture_data->motion = DIR_LEFT;
; gesture_data start address is: 12 (R3)
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #1
STRB	R1, [R2, #0]
L_ir_gesture_hw_decode_gesture94:
;ir_gesture_hw.c,403 :: 		}
IT	AL
BAL	L_ir_gesture_hw_decode_gesture95
;ir_gesture_hw.c,397 :: 		else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == -1) )
L_ir_gesture_hw_decode_gesture227:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture226:
;ir_gesture_hw.c,404 :: 		else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == -1) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #-1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture229
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #-1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture228
L_ir_gesture_hw_decode_gesture209:
;ir_gesture_hw.c,406 :: 		if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
ADDW	R1, R3, #132
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
STRH	R0, [SP, #4]
ADDW	R1, R3, #134
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
LDRSH	R1, [SP, #4]
CMP	R1, R0
IT	LE
BLE	L_ir_gesture_hw_decode_gesture99
;ir_gesture_hw.c,407 :: 		gesture_data->motion = DIR_UP;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #3
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture100
L_ir_gesture_hw_decode_gesture99:
;ir_gesture_hw.c,409 :: 		gesture_data->motion = DIR_LEFT;
; gesture_data start address is: 12 (R3)
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #1
STRB	R1, [R2, #0]
L_ir_gesture_hw_decode_gesture100:
;ir_gesture_hw.c,410 :: 		}
IT	AL
BAL	L_ir_gesture_hw_decode_gesture101
;ir_gesture_hw.c,404 :: 		else if( ( gesture_data->ud_count == -1 ) && ( gesture_data->lr_count == -1) )
L_ir_gesture_hw_decode_gesture229:
; gesture_data start address is: 12 (R3)
L_ir_gesture_hw_decode_gesture228:
;ir_gesture_hw.c,411 :: 		else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 1) )
ADDW	R1, R3, #136
LDRSH	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture231
ADDW	R1, R3, #138
LDRSH	R1, [R1, #0]
CMP	R1, #1
IT	NE
BNE	L_ir_gesture_hw_decode_gesture230
L_ir_gesture_hw_decode_gesture208:
;ir_gesture_hw.c,413 :: 		if( abs( gesture_data->ud_delta ) > abs( gesture_data->lr_delta) )
ADDW	R1, R3, #132
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
STRH	R0, [SP, #4]
ADDW	R1, R3, #134
LDRSH	R1, [R1, #0]
SXTH	R0, R1
BL	_abs+0
LDRSH	R1, [SP, #4]
CMP	R1, R0
IT	LE
BLE	L_ir_gesture_hw_decode_gesture105
;ir_gesture_hw.c,414 :: 		gesture_data->motion = DIR_DOWN;
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #4
STRB	R1, [R2, #0]
IT	AL
BAL	L_ir_gesture_hw_decode_gesture106
L_ir_gesture_hw_decode_gesture105:
;ir_gesture_hw.c,416 :: 		gesture_data->motion = DIR_RIGHT;
; gesture_data start address is: 12 (R3)
ADDW	R2, R3, #145
; gesture_data end address is: 12 (R3)
MOVS	R1, #2
STRB	R1, [R2, #0]
L_ir_gesture_hw_decode_gesture106:
;ir_gesture_hw.c,417 :: 		}
IT	AL
BAL	L_ir_gesture_hw_decode_gesture107
;ir_gesture_hw.c,411 :: 		else if( ( gesture_data->ud_count == 1 ) && ( gesture_data->lr_count == 1) )
L_ir_gesture_hw_decode_gesture231:
L_ir_gesture_hw_decode_gesture230:
;ir_gesture_hw.c,419 :: 		return -1;
MOVS	R0, #-1
IT	AL
BAL	L_end_decode_gesture
L_ir_gesture_hw_decode_gesture107:
L_ir_gesture_hw_decode_gesture101:
L_ir_gesture_hw_decode_gesture95:
L_ir_gesture_hw_decode_gesture89:
L_ir_gesture_hw_decode_gesture83:
L_ir_gesture_hw_decode_gesture79:
L_ir_gesture_hw_decode_gesture75:
L_ir_gesture_hw_decode_gesture71:
;ir_gesture_hw.c,421 :: 		return 0;
MOVS	R0, #0
;ir_gesture_hw.c,422 :: 		}
L_end_decode_gesture:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of ir_gesture_hw_decode_gesture
_ir_gesture_init:
;ir_gesture_hw.c,426 :: 		int ir_gesture_init( uint8_t address )
; address start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; address end address is: 0 (R0)
; address start address is: 0 (R0)
;ir_gesture_hw.c,431 :: 		if( ir_gesture_i2c_init( address ) )
; address end address is: 0 (R0)
BL	_ir_gesture_i2c_init+0
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_init108
;ir_gesture_hw.c,432 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_ir_gesture_init
L_ir_gesture_init108:
;ir_gesture_hw.c,434 :: 		ir_gesture_i2c_hal_read( APDS9960_ID, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #146
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,436 :: 		if( !( temp == APDS9960_ID_1 || temp == APDS9960_ID_2 ) )
LDRB	R1, [SP, #4]
CMP	R1, #171
IT	EQ
BEQ	L_ir_gesture_init110
LDRB	R1, [SP, #4]
CMP	R1, #156
IT	EQ
BEQ	L_ir_gesture_init110
MOVS	R1, #0
IT	AL
BAL	L_ir_gesture_init109
L_ir_gesture_init110:
MOVS	R1, #1
L_ir_gesture_init109:
CMP	R1, #0
IT	NE
BNE	L_ir_gesture_init111
;ir_gesture_hw.c,437 :: 		return -1;
MOVW	R0, #65535
SXTH	R0, R0
IT	AL
BAL	L_end_ir_gesture_init
L_ir_gesture_init111:
;ir_gesture_hw.c,440 :: 		set_mode( ALL, false );
MOVS	R1, #0
MOVS	R0, #7
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,443 :: 		temp = DEFAULT_ATIME;
MOVS	R1, #219
STRB	R1, [SP, #4]
;ir_gesture_hw.c,444 :: 		ir_gesture_i2c_hal_write( APDS9960_ATIME, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #129
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,445 :: 		temp = DEFAULT_WTIME;
MOVS	R1, #246
STRB	R1, [SP, #4]
;ir_gesture_hw.c,446 :: 		ir_gesture_i2c_hal_write( APDS9960_WTIME, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #131
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,447 :: 		temp = DEFAULT_PROX_PPULSE;
MOVS	R1, #135
STRB	R1, [SP, #4]
;ir_gesture_hw.c,448 :: 		ir_gesture_i2c_hal_write( APDS9960_PPULSE, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #142
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,449 :: 		temp = DEFAULT_POFFSET_UR;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,450 :: 		ir_gesture_i2c_hal_write( APDS9960_POFFSET_UR, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #157
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,451 :: 		temp = DEFAULT_POFFSET_DL;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,452 :: 		ir_gesture_i2c_hal_write( APDS9960_POFFSET_DL, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #158
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,453 :: 		temp = DEFAULT_CONFIG1;
MOVS	R1, #96
STRB	R1, [SP, #4]
;ir_gesture_hw.c,454 :: 		ir_gesture_i2c_hal_write( APDS9960_CONFIG1, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #141
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,455 :: 		ir_gesture_set_led_drive( DEFAULT_LDRIVE );
MOVS	R0, #0
BL	_ir_gesture_set_led_drive+0
;ir_gesture_hw.c,456 :: 		ir_gesture_set_proximity_gain( DEFAULT_PGAIN );
MOVS	R0, #2
BL	_ir_gesture_set_proximity_gain+0
;ir_gesture_hw.c,457 :: 		ir_gesture_set_ambient_light_gain( DEFAULT_AGAIN );
MOVS	R0, #1
BL	_ir_gesture_set_ambient_light_gain+0
;ir_gesture_hw.c,458 :: 		ir_gesture_set_prox_int_low_thresh( DEFAULT_PILT );
MOVS	R0, #0
BL	_ir_gesture_set_prox_int_low_thresh+0
;ir_gesture_hw.c,459 :: 		ir_gesture_set_prox_int_high_thresh( DEFAULT_PIHT );
MOVS	R0, #50
BL	_ir_gesture_set_prox_int_high_thresh+0
;ir_gesture_hw.c,460 :: 		ir_gesture_set_light_int_low_threshold( DEFAULT_AILT );
MOVW	R0, #65535
BL	_ir_gesture_set_light_int_low_threshold+0
;ir_gesture_hw.c,461 :: 		ir_gesture_set_light_int_high_threshold( DEFAULT_AIHT );
MOVS	R0, #0
BL	_ir_gesture_set_light_int_high_threshold+0
;ir_gesture_hw.c,462 :: 		temp = DEFAULT_PERS;
MOVS	R1, #17
STRB	R1, [SP, #4]
;ir_gesture_hw.c,463 :: 		ir_gesture_i2c_hal_write( APDS9960_PERS, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #140
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,464 :: 		temp = DEFAULT_CONFIG2;
MOVS	R1, #1
STRB	R1, [SP, #4]
;ir_gesture_hw.c,465 :: 		ir_gesture_i2c_hal_write( APDS9960_CONFIG2, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #144
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,466 :: 		temp = DEFAULT_CONFIG3;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,467 :: 		ir_gesture_i2c_hal_write( APDS9960_CONFIG3, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,470 :: 		ir_gesture_set_enter_thresh( DEFAULT_GPENTH );
MOVS	R0, #40
BL	_ir_gesture_set_enter_thresh+0
;ir_gesture_hw.c,471 :: 		ir_gesture_set_exit_thresh( DEFAULT_GEXTH );
MOVS	R0, #30
BL	_ir_gesture_set_exit_thresh+0
;ir_gesture_hw.c,472 :: 		temp = DEFAULT_GCONF1;
MOVS	R1, #64
STRB	R1, [SP, #4]
;ir_gesture_hw.c,473 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF1, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #162
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,474 :: 		ir_gesture_set_gesture_gain( DEFAULT_GGAIN );
MOVS	R0, #2
BL	_ir_gesture_set_gesture_gain+0
;ir_gesture_hw.c,475 :: 		ir_gesture_set_gesture_led_drive( DEFAULT_GLDRIVE );
MOVS	R0, #0
BL	_ir_gesture_set_gesture_led_drive+0
;ir_gesture_hw.c,476 :: 		ir_gesture_set_wait_time( DEFAULT_GWTIME );
MOVS	R0, #1
BL	_ir_gesture_set_wait_time+0
;ir_gesture_hw.c,477 :: 		temp = DEFAULT_GOFFSET;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,478 :: 		ir_gesture_i2c_hal_write( APDS9960_GOFFSET_U, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #164
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,479 :: 		temp = DEFAULT_GOFFSET;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,480 :: 		ir_gesture_i2c_hal_write( APDS9960_GOFFSET_D, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #165
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,481 :: 		temp = DEFAULT_GOFFSET;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,482 :: 		ir_gesture_i2c_hal_write( APDS9960_GOFFSET_L, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #167
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,483 :: 		temp = DEFAULT_GOFFSET;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,484 :: 		ir_gesture_i2c_hal_write( APDS9960_GOFFSET_R, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #169
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,485 :: 		temp = DEFAULT_GPULSE;
MOVS	R1, #201
STRB	R1, [SP, #4]
;ir_gesture_hw.c,486 :: 		ir_gesture_i2c_hal_write( APDS9960_GPULSE, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #166
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,487 :: 		temp = DEFAULT_GCONF3;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,488 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF3, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #170
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,489 :: 		ir_gesture_set_gesture_int_enable( DEFAULT_GIEN );
MOVS	R0, #0
BL	_ir_gesture_set_gesture_int_enable+0
;ir_gesture_hw.c,491 :: 		return 0;
MOVS	R0, #0
SXTH	R0, R0
;ir_gesture_hw.c,492 :: 		}
L_end_ir_gesture_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_init
_ir_gesture_enable_power:
;ir_gesture_hw.c,495 :: 		void ir_gesture_enable_power()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;ir_gesture_hw.c,497 :: 		set_mode( POWER, true );
MOVS	R1, #1
MOVS	R0, #0
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,498 :: 		}
L_end_ir_gesture_enable_power:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_enable_power
_ir_gesture_disable_power:
;ir_gesture_hw.c,500 :: 		void ir_gesture_disable_power()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;ir_gesture_hw.c,502 :: 		set_mode( POWER, false );
MOVS	R1, #0
MOVS	R0, #0
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,503 :: 		}
L_end_ir_gesture_disable_power:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_disable_power
_ir_gesture_enable_light_sensor:
;ir_gesture_hw.c,506 :: 		void ir_gesture_enable_light_sensor( bool interrupt )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,509 :: 		ir_gesture_set_ambient_light_gain( DEFAULT_AGAIN );
MOVS	R0, #1
BL	_ir_gesture_set_ambient_light_gain+0
;ir_gesture_hw.c,511 :: 		ir_gesture_set_ambient_light_int_enable( interrupt );
LDRB	R0, [SP, #4]
BL	_ir_gesture_set_ambient_light_int_enable+0
;ir_gesture_hw.c,512 :: 		ir_gesture_enable_power();
BL	_ir_gesture_enable_power+0
;ir_gesture_hw.c,513 :: 		set_mode( AMBIENT_LIGHT, true );
MOVS	R1, #1
MOVS	R0, #1
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,514 :: 		}
L_end_ir_gesture_enable_light_sensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_enable_light_sensor
_ir_gesture_disable_light_sensor:
;ir_gesture_hw.c,516 :: 		void ir_gesture_disable_light_sensor()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;ir_gesture_hw.c,518 :: 		ir_gesture_set_ambient_light_int_enable( false );
MOVS	R0, #0
BL	_ir_gesture_set_ambient_light_int_enable+0
;ir_gesture_hw.c,519 :: 		set_mode( AMBIENT_LIGHT, false );
MOVS	R1, #0
MOVS	R0, #1
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,520 :: 		}
L_end_ir_gesture_disable_light_sensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_disable_light_sensor
_ir_gesture_enable_proximity_sensor:
;ir_gesture_hw.c,522 :: 		void ir_gesture_enable_proximity_sensor( bool interrupt )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,525 :: 		ir_gesture_set_proximity_gain( DEFAULT_PGAIN );
MOVS	R0, #2
BL	_ir_gesture_set_proximity_gain+0
;ir_gesture_hw.c,526 :: 		ir_gesture_set_led_drive( DEFAULT_LDRIVE );
MOVS	R0, #0
BL	_ir_gesture_set_led_drive+0
;ir_gesture_hw.c,528 :: 		ir_gesture_set_proximity_int_enable( interrupt );
LDRB	R0, [SP, #4]
BL	_ir_gesture_set_proximity_int_enable+0
;ir_gesture_hw.c,529 :: 		ir_gesture_enable_power();
BL	_ir_gesture_enable_power+0
;ir_gesture_hw.c,530 :: 		set_mode( PROXIMITY, true );
MOVS	R1, #1
MOVS	R0, #2
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,531 :: 		}
L_end_ir_gesture_enable_proximity_sensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_enable_proximity_sensor
_ir_gesture_disable_proximity_sensor:
;ir_gesture_hw.c,533 :: 		void ir_gesture_disable_proximity_sensor()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;ir_gesture_hw.c,535 :: 		ir_gesture_set_proximity_int_enable( false );
MOVS	R0, #0
BL	_ir_gesture_set_proximity_int_enable+0
;ir_gesture_hw.c,536 :: 		set_mode( PROXIMITY, false );
MOVS	R1, #0
MOVS	R0, #2
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,537 :: 		}
L_end_ir_gesture_disable_proximity_sensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_disable_proximity_sensor
_ir_gesture_enable_gesture_sensor:
;ir_gesture_hw.c,539 :: 		void ir_gesture_enable_gesture_sensor( bool interrupt )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,541 :: 		uint8_t temp = 0xff;
MOVS	R1, #255
STRB	R1, [SP, #4]
;ir_gesture_hw.c,549 :: 		ir_gesture_i2c_hal_write( APDS9960_WTIME, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #131
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,550 :: 		temp = DEFAULT_GESTURE_PPULSE;
MOVS	R1, #137
STRB	R1, [SP, #4]
;ir_gesture_hw.c,551 :: 		ir_gesture_i2c_hal_write( APDS9960_PPULSE, &temp, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #142
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,552 :: 		ir_gesture_set_led_boost( LED_BOOST_300 );
MOVS	R0, #3
BL	_ir_gesture_set_led_boost+0
;ir_gesture_hw.c,554 :: 		ir_gesture_set_gesture_int_enable( interrupt );
LDRB	R0, [SP, #8]
BL	_ir_gesture_set_gesture_int_enable+0
;ir_gesture_hw.c,556 :: 		ir_gesture_set_gesture_mode( true );
MOVS	R0, #1
BL	_ir_gesture_set_gesture_mode+0
;ir_gesture_hw.c,557 :: 		ir_gesture_enable_power();
BL	_ir_gesture_enable_power+0
;ir_gesture_hw.c,558 :: 		set_mode( WAIT, true );
MOVS	R1, #1
MOVS	R0, #3
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,559 :: 		set_mode( PROXIMITY, true );
MOVS	R1, #1
MOVS	R0, #2
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,560 :: 		set_mode( GESTURE, true );
MOVS	R1, #1
MOVS	R0, #6
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,561 :: 		}
L_end_ir_gesture_enable_gesture_sensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_enable_gesture_sensor
_ir_gesture_disable_gesture_sensor:
;ir_gesture_hw.c,563 :: 		void ir_gesture_disable_gesture_sensor()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;ir_gesture_hw.c,566 :: 		ir_gesture_set_gesture_int_enable( false );
MOVS	R0, #0
BL	_ir_gesture_set_gesture_int_enable+0
;ir_gesture_hw.c,567 :: 		ir_gesture_set_gesture_mode( false );
MOVS	R0, #0
BL	_ir_gesture_set_gesture_mode+0
;ir_gesture_hw.c,568 :: 		set_mode( GESTURE, false );
MOVS	R1, #0
MOVS	R0, #6
BL	ir_gesture_hw_set_mode+0
;ir_gesture_hw.c,569 :: 		}
L_end_ir_gesture_disable_gesture_sensor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _ir_gesture_disable_gesture_sensor
_ir_gesture_get_led_drive:
;ir_gesture_hw.c,572 :: 		uint8_t ir_gesture_get_led_drive()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,574 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,577 :: 		ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,580 :: 		val = ( val >> 6 ) & 0x03;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #6
UXTB	R0, R0
AND	R0, R0, #3
STRB	R0, [SP, #4]
;ir_gesture_hw.c,582 :: 		return val;
;ir_gesture_hw.c,583 :: 		}
L_end_ir_gesture_get_led_drive:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_led_drive
_ir_gesture_set_led_drive:
;ir_gesture_hw.c,585 :: 		void ir_gesture_set_led_drive( uint8_t drive )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,589 :: 		drive = MIN( drive, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_led_drive112
; ?FLOC___ir_gesture_set_led_drive?T608 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_led_drive?T608 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_led_drive113
L_ir_gesture_set_led_drive112:
; ?FLOC___ir_gesture_set_led_drive?T608 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_led_drive?T608 end address is: 0 (R0)
L_ir_gesture_set_led_drive113:
; ?FLOC___ir_gesture_set_led_drive?T608 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_led_drive?T608 end address is: 0 (R0)
;ir_gesture_hw.c,592 :: 		ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,595 :: 		val &= ~( 1 << 6 ) | ( 1 << 7 );
LDRB	R2, [SP, #4]
MOVW	R1, #65471
SXTH	R1, R1
AND	R3, R2, R1, LSL #0
STRB	R3, [SP, #4]
;ir_gesture_hw.c,596 :: 		drive = ( drive << 6 ) | val;
LDRB	R1, [SP, #8]
LSLS	R2, R1, #6
UXTH	R2, R2
UXTB	R1, R3
ORR	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,599 :: 		ir_gesture_i2c_hal_write( APDS9960_CONTROL, &drive, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,600 :: 		}
L_end_ir_gesture_set_led_drive:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_led_drive
_ir_gesture_get_gesture_led_drive:
;ir_gesture_hw.c,602 :: 		uint8_t ir_gesture_get_gesture_led_drive()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,604 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,607 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,610 :: 		val = ( val >> 3 ) & 0x03;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #3
UXTB	R0, R0
AND	R0, R0, #3
STRB	R0, [SP, #4]
;ir_gesture_hw.c,612 :: 		return val;
;ir_gesture_hw.c,613 :: 		}
L_end_ir_gesture_get_gesture_led_drive:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_gesture_led_drive
_ir_gesture_set_gesture_led_drive:
;ir_gesture_hw.c,615 :: 		void ir_gesture_set_gesture_led_drive( uint8_t drive )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,617 :: 		uint8_t val = 0;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,619 :: 		drive = MIN( drive, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_gesture_led_drive114
; ?FLOC___ir_gesture_set_gesture_led_drive?T619 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_gesture_led_drive?T619 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_gesture_led_drive115
L_ir_gesture_set_gesture_led_drive114:
; ?FLOC___ir_gesture_set_gesture_led_drive?T619 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_gesture_led_drive?T619 end address is: 0 (R0)
L_ir_gesture_set_gesture_led_drive115:
; ?FLOC___ir_gesture_set_gesture_led_drive?T619 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_gesture_led_drive?T619 end address is: 0 (R0)
;ir_gesture_hw.c,622 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,625 :: 		val &= ~( 1 << 3 ) | ( 1 << 4 );
LDRB	R2, [SP, #4]
MOVW	R1, #65527
SXTH	R1, R1
AND	R3, R2, R1, LSL #0
STRB	R3, [SP, #4]
;ir_gesture_hw.c,626 :: 		drive = ( drive << 3 ) | val;
LDRB	R1, [SP, #8]
LSLS	R2, R1, #3
UXTH	R2, R2
UXTB	R1, R3
ORR	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,629 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF2, &drive, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,630 :: 		}
L_end_ir_gesture_set_gesture_led_drive:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_gesture_led_drive
_ir_gesture_get_ambient_light_gain:
;ir_gesture_hw.c,633 :: 		uint8_t ir_gesture_get_ambient_light_gain()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,635 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,638 :: 		ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,641 :: 		val &= 0x03;
LDRB	R0, [SP, #4]
AND	R0, R0, #3
STRB	R0, [SP, #4]
;ir_gesture_hw.c,643 :: 		return val;
;ir_gesture_hw.c,644 :: 		}
L_end_ir_gesture_get_ambient_light_gain:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_ambient_light_gain
_ir_gesture_set_ambient_light_gain:
;ir_gesture_hw.c,646 :: 		void ir_gesture_set_ambient_light_gain( uint8_t drive )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,648 :: 		uint8_t val=0;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,650 :: 		drive = MIN( drive, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_ambient_light_gain116
; ?FLOC___ir_gesture_set_ambient_light_gain?T629 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_ambient_light_gain?T629 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_ambient_light_gain117
L_ir_gesture_set_ambient_light_gain116:
; ?FLOC___ir_gesture_set_ambient_light_gain?T629 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_ambient_light_gain?T629 end address is: 0 (R0)
L_ir_gesture_set_ambient_light_gain117:
; ?FLOC___ir_gesture_set_ambient_light_gain?T629 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_ambient_light_gain?T629 end address is: 0 (R0)
;ir_gesture_hw.c,653 :: 		ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,656 :: 		val &= ~( 1 << 0 ) | ( 1 << 1 );
LDRB	R2, [SP, #4]
MOVW	R1, #65534
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,657 :: 		drive |= val;
UXTB	R2, R1
LDRB	R1, [SP, #8]
ORRS	R1, R2
STRB	R1, [SP, #8]
;ir_gesture_hw.c,660 :: 		ir_gesture_i2c_hal_write( APDS9960_CONTROL, &drive, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,661 :: 		}
L_end_ir_gesture_set_ambient_light_gain:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_ambient_light_gain
_ir_gesture_get_proximity_gain:
;ir_gesture_hw.c,663 :: 		uint8_t ir_gesture_get_proximity_gain()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,668 :: 		ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,671 :: 		val = ( val >> 2 ) & 0x03;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #2
UXTB	R0, R0
AND	R0, R0, #3
STRB	R0, [SP, #4]
;ir_gesture_hw.c,673 :: 		return val;
;ir_gesture_hw.c,674 :: 		}
L_end_ir_gesture_get_proximity_gain:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_proximity_gain
_ir_gesture_set_proximity_gain:
;ir_gesture_hw.c,676 :: 		void ir_gesture_set_proximity_gain( uint8_t drive )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,678 :: 		uint8_t val=0;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,680 :: 		drive = MIN( drive, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_proximity_gain118
; ?FLOC___ir_gesture_set_proximity_gain?T639 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_proximity_gain?T639 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_proximity_gain119
L_ir_gesture_set_proximity_gain118:
; ?FLOC___ir_gesture_set_proximity_gain?T639 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_proximity_gain?T639 end address is: 0 (R0)
L_ir_gesture_set_proximity_gain119:
; ?FLOC___ir_gesture_set_proximity_gain?T639 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_proximity_gain?T639 end address is: 0 (R0)
;ir_gesture_hw.c,683 :: 		ir_gesture_i2c_hal_read( APDS9960_CONTROL, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,686 :: 		val &= ~( 1 << 2 ) | ( 1 << 3 );
LDRB	R2, [SP, #4]
MOVW	R1, #65531
SXTH	R1, R1
AND	R3, R2, R1, LSL #0
STRB	R3, [SP, #4]
;ir_gesture_hw.c,687 :: 		drive = ( drive << 2 ) | val;
LDRB	R1, [SP, #8]
LSLS	R2, R1, #2
UXTH	R2, R2
UXTB	R1, R3
ORR	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,690 :: 		ir_gesture_i2c_hal_write( APDS9960_CONTROL, &drive, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #143
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,691 :: 		}
L_end_ir_gesture_set_proximity_gain:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_proximity_gain
_ir_gesture_get_gesture_gain:
;ir_gesture_hw.c,693 :: 		uint8_t ir_gesture_get_gesture_gain()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,695 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,698 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,701 :: 		val = ( val >> 5 ) & 0x03;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #5
UXTB	R0, R0
AND	R0, R0, #3
STRB	R0, [SP, #4]
;ir_gesture_hw.c,703 :: 		return val;
;ir_gesture_hw.c,704 :: 		}
L_end_ir_gesture_get_gesture_gain:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_gesture_gain
_ir_gesture_set_gesture_gain:
;ir_gesture_hw.c,706 :: 		void ir_gesture_set_gesture_gain( uint8_t gain )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,710 :: 		gain = MIN( gain, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_gesture_gain120
; ?FLOC___ir_gesture_set_gesture_gain?T650 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_gesture_gain?T650 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_gesture_gain121
L_ir_gesture_set_gesture_gain120:
; ?FLOC___ir_gesture_set_gesture_gain?T650 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_gesture_gain?T650 end address is: 0 (R0)
L_ir_gesture_set_gesture_gain121:
; ?FLOC___ir_gesture_set_gesture_gain?T650 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_gesture_gain?T650 end address is: 0 (R0)
;ir_gesture_hw.c,713 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,716 :: 		val &= ~( 1 << 5 ) | ( 1 << 6 );
LDRB	R2, [SP, #4]
MOVW	R1, #65503
SXTH	R1, R1
AND	R3, R2, R1, LSL #0
STRB	R3, [SP, #4]
;ir_gesture_hw.c,717 :: 		gain = ( gain << 5 ) | val;
LDRB	R1, [SP, #8]
LSLS	R2, R1, #5
UXTH	R2, R2
UXTB	R1, R3
ORR	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,719 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF2, &gain, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,720 :: 		}
L_end_ir_gesture_set_gesture_gain:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_gesture_gain
_ir_gesture_get_light_int_low_threshold:
;ir_gesture_hw.c,723 :: 		uint16_t ir_gesture_get_light_int_low_threshold()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,729 :: 		ir_gesture_i2c_hal_read( APDS9960_AILTH, &val_byte, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #133
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,731 :: 		return_val = ( uint16_t )( val_byte << 8 );
LDRB	R0, [SP, #4]
LSLS	R0, R0, #8
STRH	R0, [SP, #6]
;ir_gesture_hw.c,734 :: 		ir_gesture_i2c_hal_read( APDS9960_AILTL, &val_byte, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #132
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,736 :: 		return ( return_val | val_byte );
LDRB	R1, [SP, #4]
LDRH	R0, [SP, #6]
ORRS	R0, R1
;ir_gesture_hw.c,737 :: 		}
L_end_ir_gesture_get_light_int_low_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_light_int_low_threshold
_ir_gesture_set_light_int_low_threshold:
;ir_gesture_hw.c,739 :: 		void ir_gesture_set_light_int_low_threshold( uint16_t threshold )
; threshold start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; threshold end address is: 0 (R0)
; threshold start address is: 0 (R0)
;ir_gesture_hw.c,745 :: 		val_low = threshold & 0x00FF;
AND	R1, R0, #255
STRB	R1, [SP, #4]
;ir_gesture_hw.c,746 :: 		val_high = ( threshold & 0xFF00 ) >> 8;
AND	R1, R0, #65280
UXTH	R1, R1
; threshold end address is: 0 (R0)
LSRS	R1, R1, #8
STRB	R1, [SP, #5]
;ir_gesture_hw.c,749 :: 		ir_gesture_i2c_hal_write( APDS9960_AILTL, &val_low, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #132
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,752 :: 		ir_gesture_i2c_hal_write( APDS9960_AILTH, &val_high, 1 );
ADD	R1, SP, #5
MOVS	R2, #1
MOVS	R0, #133
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,753 :: 		}
L_end_ir_gesture_set_light_int_low_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_light_int_low_threshold
_ir_gesture_get_light_int_high_threshold:
;ir_gesture_hw.c,755 :: 		uint16_t ir_gesture_get_light_int_high_threshold()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,761 :: 		ir_gesture_i2c_hal_read( APDS9960_AIHTH, &val_byte, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #135
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,763 :: 		return_val = ( uint16_t )( val_byte << 8 );
LDRB	R0, [SP, #4]
LSLS	R0, R0, #8
STRH	R0, [SP, #6]
;ir_gesture_hw.c,766 :: 		ir_gesture_i2c_hal_read( APDS9960_AIHTL, &val_byte, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #134
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,768 :: 		return ( return_val | val_byte );
LDRB	R1, [SP, #4]
LDRH	R0, [SP, #6]
ORRS	R0, R1
;ir_gesture_hw.c,769 :: 		}
L_end_ir_gesture_get_light_int_high_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_light_int_high_threshold
_ir_gesture_set_light_int_high_threshold:
;ir_gesture_hw.c,771 :: 		void ir_gesture_set_light_int_high_threshold( uint16_t threshold )
; threshold start address is: 0 (R0)
SUB	SP, SP, #8
STR	LR, [SP, #0]
; threshold end address is: 0 (R0)
; threshold start address is: 0 (R0)
;ir_gesture_hw.c,777 :: 		val_low = threshold & 0x00FF;
AND	R1, R0, #255
STRB	R1, [SP, #4]
;ir_gesture_hw.c,778 :: 		val_high = ( threshold & 0xFF00 ) >> 8;
AND	R1, R0, #65280
UXTH	R1, R1
; threshold end address is: 0 (R0)
LSRS	R1, R1, #8
STRB	R1, [SP, #5]
;ir_gesture_hw.c,781 :: 		ir_gesture_i2c_hal_write( APDS9960_AIHTH, &val_high, 1 );
ADD	R1, SP, #5
MOVS	R2, #1
MOVS	R0, #135
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,784 :: 		ir_gesture_i2c_hal_write( APDS9960_AIHTL, &val_low, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #134
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,785 :: 		}
L_end_ir_gesture_set_light_int_high_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_light_int_high_threshold
_ir_gesture_get_proximity_int_low_threshold:
;ir_gesture_hw.c,788 :: 		uint8_t ir_gesture_get_proximity_int_low_threshold()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,790 :: 		uint8_t threshold = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,793 :: 		ir_gesture_i2c_hal_read( APDS9960_PILT, &threshold, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #137
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,795 :: 		return threshold;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,796 :: 		}
L_end_ir_gesture_get_proximity_int_low_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_proximity_int_low_threshold
_ir_gesture_set_proximity_int_low_threshold:
;ir_gesture_hw.c,798 :: 		void ir_gesture_set_proximity_int_low_threshold( uint8_t threshold )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,801 :: 		ir_gesture_i2c_hal_write( APDS9960_PILT, &threshold, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #137
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,802 :: 		}
L_end_ir_gesture_set_proximity_int_low_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_proximity_int_low_threshold
_ir_gesture_get_proximity_int_high_threshold:
;ir_gesture_hw.c,804 :: 		uint8_t ir_gesture_get_proximity_int_high_threshold( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,806 :: 		uint8_t threshold = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,809 :: 		ir_gesture_i2c_hal_read( APDS9960_PIHT, &threshold, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #139
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,811 :: 		return threshold;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,812 :: 		}
L_end_ir_gesture_get_proximity_int_high_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_proximity_int_high_threshold
_ir_gesture_set_prox_int_high_threshold:
;ir_gesture_hw.c,814 :: 		void ir_gesture_set_prox_int_high_threshold( uint8_t threshold )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,817 :: 		ir_gesture_i2c_hal_write( APDS9960_PIHT, &threshold, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #139
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,818 :: 		}
L_end_ir_gesture_set_prox_int_high_threshold:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_prox_int_high_threshold
_ir_gesture_is_ambient_light_int_enable:
;ir_gesture_hw.c,821 :: 		bool ir_gesture_is_ambient_light_int_enable()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,823 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,826 :: 		ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,829 :: 		val = ( val >> 4 ) & 0x01;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #4
UXTB	R0, R0
AND	R0, R0, #1
UXTB	R0, R0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,831 :: 		return ( val == 1 ) ? true : false;
CMP	R0, #1
IT	NE
BNE	L_ir_gesture_is_ambient_light_int_enable122
; ?FLOC___ir_gesture_is_ambient_light_int_enable?T685 start address is: 0 (R0)
MOVS	R0, #1
SXTB	R0, R0
; ?FLOC___ir_gesture_is_ambient_light_int_enable?T685 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_is_ambient_light_int_enable123
L_ir_gesture_is_ambient_light_int_enable122:
; ?FLOC___ir_gesture_is_ambient_light_int_enable?T685 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_is_ambient_light_int_enable?T685 end address is: 0 (R0)
L_ir_gesture_is_ambient_light_int_enable123:
; ?FLOC___ir_gesture_is_ambient_light_int_enable?T685 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___ir_gesture_is_ambient_light_int_enable?T685 end address is: 0 (R0)
;ir_gesture_hw.c,832 :: 		}
L_end_ir_gesture_is_ambient_light_int_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_is_ambient_light_int_enable
_ir_gesture_set_ambient_light_int_enable:
;ir_gesture_hw.c,834 :: 		void ir_gesture_set_ambient_light_int_enable( bool enable )
; enable start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; enable end address is: 0 (R0)
; enable start address is: 0 (R0)
;ir_gesture_hw.c,836 :: 		uint8_t val = 0;
MOVS	R1, #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,839 :: 		ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );
ADD	R1, SP, #8
STRB	R0, [SP, #4]
MOVS	R2, #1
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_read+0
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,842 :: 		val &= ~( 1 << 0 );
LDRB	R2, [SP, #8]
MOVW	R1, #65534
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,844 :: 		if( enable )
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_set_ambient_light_int_enable124
; enable end address is: 0 (R0)
;ir_gesture_hw.c,845 :: 		val |= ( 1 << 0 );
LDRB	R1, [SP, #8]
ORR	R1, R1, #1
STRB	R1, [SP, #8]
L_ir_gesture_set_ambient_light_int_enable124:
;ir_gesture_hw.c,848 :: 		ir_gesture_i2c_hal_write( APDS9960_ENABLE, &val, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,849 :: 		}
L_end_ir_gesture_set_ambient_light_int_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_ambient_light_int_enable
_ir_gesture_is_proximity_int_enable:
;ir_gesture_hw.c,851 :: 		bool ir_gesture_is_proximity_int_enable()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,853 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,856 :: 		ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,859 :: 		val = ( val >> 5 ) & 0x01;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #5
UXTB	R0, R0
AND	R0, R0, #1
UXTB	R0, R0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,861 :: 		return ( val == 1 ) ? true : false;
CMP	R0, #1
IT	NE
BNE	L_ir_gesture_is_proximity_int_enable125
; ?FLOC___ir_gesture_is_proximity_int_enable?T695 start address is: 0 (R0)
MOVS	R0, #1
SXTB	R0, R0
; ?FLOC___ir_gesture_is_proximity_int_enable?T695 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_is_proximity_int_enable126
L_ir_gesture_is_proximity_int_enable125:
; ?FLOC___ir_gesture_is_proximity_int_enable?T695 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_is_proximity_int_enable?T695 end address is: 0 (R0)
L_ir_gesture_is_proximity_int_enable126:
; ?FLOC___ir_gesture_is_proximity_int_enable?T695 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___ir_gesture_is_proximity_int_enable?T695 end address is: 0 (R0)
;ir_gesture_hw.c,862 :: 		}
L_end_ir_gesture_is_proximity_int_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_is_proximity_int_enable
_ir_gesture_set_proximity_int_enable:
;ir_gesture_hw.c,864 :: 		void ir_gesture_set_proximity_int_enable( bool enable )
; enable start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; enable end address is: 0 (R0)
; enable start address is: 0 (R0)
;ir_gesture_hw.c,866 :: 		uint8_t val = 0;
MOVS	R1, #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,869 :: 		ir_gesture_i2c_hal_read( APDS9960_ENABLE, &val, 1 );
ADD	R1, SP, #8
STRB	R0, [SP, #4]
MOVS	R2, #1
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_read+0
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,872 :: 		val &= ~( 1 << 5 );
LDRB	R2, [SP, #8]
MOVW	R1, #65503
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,874 :: 		if( enable )
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_set_proximity_int_enable127
; enable end address is: 0 (R0)
;ir_gesture_hw.c,875 :: 		val |= ( 1 << 5 );
LDRB	R1, [SP, #8]
ORR	R1, R1, #32
STRB	R1, [SP, #8]
L_ir_gesture_set_proximity_int_enable127:
;ir_gesture_hw.c,878 :: 		ir_gesture_i2c_hal_write( APDS9960_ENABLE, &val, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #128
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,879 :: 		}
L_end_ir_gesture_set_proximity_int_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_proximity_int_enable
_ir_gesture_is_gesture_int_enable:
;ir_gesture_hw.c,881 :: 		bool ir_gesture_is_gesture_int_enable()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,883 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,886 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #171
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,889 :: 		val = ( val >> 1 ) & 0x01;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #1
UXTB	R0, R0
AND	R0, R0, #1
UXTB	R0, R0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,891 :: 		return ( val == 1 ) ? true : false;
CMP	R0, #1
IT	NE
BNE	L_ir_gesture_is_gesture_int_enable128
; ?FLOC___ir_gesture_is_gesture_int_enable?T705 start address is: 0 (R0)
MOVS	R0, #1
SXTB	R0, R0
; ?FLOC___ir_gesture_is_gesture_int_enable?T705 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_is_gesture_int_enable129
L_ir_gesture_is_gesture_int_enable128:
; ?FLOC___ir_gesture_is_gesture_int_enable?T705 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_is_gesture_int_enable?T705 end address is: 0 (R0)
L_ir_gesture_is_gesture_int_enable129:
; ?FLOC___ir_gesture_is_gesture_int_enable?T705 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___ir_gesture_is_gesture_int_enable?T705 end address is: 0 (R0)
;ir_gesture_hw.c,892 :: 		}
L_end_ir_gesture_is_gesture_int_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_is_gesture_int_enable
_ir_gesture_set_gesture_int_enable:
;ir_gesture_hw.c,894 :: 		void ir_gesture_set_gesture_int_enable( bool enable )
; enable start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; enable end address is: 0 (R0)
; enable start address is: 0 (R0)
;ir_gesture_hw.c,896 :: 		uint8_t val = 0;
MOVS	R1, #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,899 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );
ADD	R1, SP, #8
STRB	R0, [SP, #4]
MOVS	R2, #1
MOVS	R0, #171
BL	_ir_gesture_i2c_hal_read+0
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,902 :: 		val &= ~( 1 << 1 );
LDRB	R2, [SP, #8]
MOVW	R1, #65533
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,904 :: 		if( enable )
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_set_gesture_int_enable130
; enable end address is: 0 (R0)
;ir_gesture_hw.c,905 :: 		val |= ( 1 << 1 );
LDRB	R1, [SP, #8]
ORR	R1, R1, #2
STRB	R1, [SP, #8]
L_ir_gesture_set_gesture_int_enable130:
;ir_gesture_hw.c,908 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF4, &val, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #171
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,909 :: 		}
L_end_ir_gesture_set_gesture_int_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_gesture_int_enable
_ir_gesture_is_interrupted:
;ir_gesture_hw.c,912 :: 		bool ir_gesture_is_interrupted( gesture_irq_t interrupt )
; interrupt start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; interrupt end address is: 0 (R0)
; interrupt start address is: 0 (R0)
;ir_gesture_hw.c,916 :: 		if( interrupt != INT_AMBIENT_LIGHT && interrupt != INT_GESTURE &&
CMP	R0, #4
IT	EQ
BEQ	L__ir_gesture_is_interrupted235
CMP	R0, #2
IT	EQ
BEQ	L__ir_gesture_is_interrupted234
;ir_gesture_hw.c,917 :: 		interrupt != INT_PROXIMITY )
CMP	R0, #5
IT	EQ
BEQ	L__ir_gesture_is_interrupted233
; interrupt end address is: 0 (R0)
L__ir_gesture_is_interrupted232:
;ir_gesture_hw.c,918 :: 		return false;
MOVS	R0, #0
IT	AL
BAL	L_end_ir_gesture_is_interrupted
;ir_gesture_hw.c,916 :: 		if( interrupt != INT_AMBIENT_LIGHT && interrupt != INT_GESTURE &&
L__ir_gesture_is_interrupted235:
; interrupt start address is: 0 (R0)
L__ir_gesture_is_interrupted234:
;ir_gesture_hw.c,917 :: 		interrupt != INT_PROXIMITY )
L__ir_gesture_is_interrupted233:
;ir_gesture_hw.c,920 :: 		ir_gesture_i2c_hal_read( APDS9960_STATUS, &status, 1 );
ADD	R1, SP, #8
STRB	R0, [SP, #4]
MOVS	R2, #1
MOVS	R0, #147
BL	_ir_gesture_i2c_hal_read+0
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,922 :: 		return ( status & ( 1 << interrupt ) ) ? true : false;
MOVS	R1, #1
SXTH	R1, R1
LSL	R2, R1, R0
SXTH	R2, R2
; interrupt end address is: 0 (R0)
LDRB	R1, [SP, #8]
ANDS	R1, R2
SXTH	R1, R1
CMP	R1, #0
IT	EQ
BEQ	L_ir_gesture_is_interrupted134
; ?FLOC___ir_gesture_is_interrupted?T718 start address is: 0 (R0)
MOVS	R0, #1
SXTB	R0, R0
; ?FLOC___ir_gesture_is_interrupted?T718 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_is_interrupted135
L_ir_gesture_is_interrupted134:
; ?FLOC___ir_gesture_is_interrupted?T718 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_is_interrupted?T718 end address is: 0 (R0)
L_ir_gesture_is_interrupted135:
; ?FLOC___ir_gesture_is_interrupted?T718 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___ir_gesture_is_interrupted?T718 end address is: 0 (R0)
;ir_gesture_hw.c,923 :: 		}
L_end_ir_gesture_is_interrupted:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_is_interrupted
_ir_gesture_clear_ambient_light_int:
;ir_gesture_hw.c,926 :: 		void ir_gesture_clear_ambient_light_int()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,930 :: 		ir_gesture_i2c_hal_read( APDS9960_CICLEAR, &throwaway, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #230
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,931 :: 		}
L_end_ir_gesture_clear_ambient_light_int:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_clear_ambient_light_int
_ir_gesture_clear_proximity_int:
;ir_gesture_hw.c,933 :: 		void ir_gesture_clear_proximity_int()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,937 :: 		ir_gesture_i2c_hal_read( APDS9960_PICLEAR, &throwaway, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #229
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,938 :: 		}
L_end_ir_gesture_clear_proximity_int:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_clear_proximity_int
_ir_gesture_clear_gesture_int:
;ir_gesture_hw.c,940 :: 		void ir_gesture_clear_gesture_int() // TODO: Not correct, this is a clear all
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,944 :: 		ir_gesture_i2c_hal_read( APDS9960_AICLEAR, &throwaway, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #231
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,945 :: 		}
L_end_ir_gesture_clear_gesture_int:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_clear_gesture_int
_ir_gesture_read_ambient_light:
;ir_gesture_hw.c,948 :: 		uint16_t ir_gesture_read_ambient_light( )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,954 :: 		ir_gesture_i2c_hal_read( APDS9960_CDATAH, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #149
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,956 :: 		return_val = ( uint16_t )( temp << 8 );
LDRB	R0, [SP, #4]
LSLS	R0, R0, #8
STRH	R0, [SP, #6]
;ir_gesture_hw.c,959 :: 		ir_gesture_i2c_hal_read( APDS9960_CDATAL, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #148
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,961 :: 		return ( return_val | temp );
LDRB	R1, [SP, #4]
LDRH	R0, [SP, #6]
ORRS	R0, R1
;ir_gesture_hw.c,962 :: 		}
L_end_ir_gesture_read_ambient_light:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_read_ambient_light
_ir_gesture_read_red_light:
;ir_gesture_hw.c,964 :: 		uint16_t ir_gesture_read_red_light( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,970 :: 		ir_gesture_i2c_hal_read( APDS9960_RDATAH, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #151
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,972 :: 		return_val = ( uint16_t )( temp << 8 );
LDRB	R0, [SP, #4]
LSLS	R0, R0, #8
STRH	R0, [SP, #6]
;ir_gesture_hw.c,975 :: 		ir_gesture_i2c_hal_read( APDS9960_RDATAL, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #150
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,977 :: 		return ( return_val |= temp );
LDRB	R1, [SP, #4]
LDRH	R0, [SP, #6]
ORRS	R0, R1
;ir_gesture_hw.c,978 :: 		}
L_end_ir_gesture_read_red_light:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_read_red_light
_ir_gesture_read_green_light:
;ir_gesture_hw.c,980 :: 		uint16_t ir_gesture_read_green_light( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,986 :: 		ir_gesture_i2c_hal_read( APDS9960_GDATAH, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #153
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,988 :: 		return_val = ( uint16_t )( temp << 8 );
LDRB	R0, [SP, #4]
LSLS	R0, R0, #8
STRH	R0, [SP, #6]
;ir_gesture_hw.c,991 :: 		ir_gesture_i2c_hal_read( APDS9960_GDATAL, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #152
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,993 :: 		return ( return_val |= temp );
LDRB	R1, [SP, #4]
LDRH	R0, [SP, #6]
ORRS	R0, R1
;ir_gesture_hw.c,994 :: 		}
L_end_ir_gesture_read_green_light:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_read_green_light
_ir_gesture_read_blue_light:
;ir_gesture_hw.c,996 :: 		uint16_t ir_gesture_read_blue_light( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1002 :: 		ir_gesture_i2c_hal_read( APDS9960_BDATAH, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #155
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1004 :: 		return_val = ( uint16_t )( temp << 8 );
LDRB	R0, [SP, #4]
LSLS	R0, R0, #8
STRH	R0, [SP, #6]
;ir_gesture_hw.c,1007 :: 		ir_gesture_i2c_hal_read( APDS9960_BDATAL, &temp, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #154
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1009 :: 		return ( return_val |= temp );
LDRB	R1, [SP, #4]
LDRH	R0, [SP, #6]
ORRS	R0, R1
;ir_gesture_hw.c,1010 :: 		}
L_end_ir_gesture_read_blue_light:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_read_blue_light
_ir_gesture_get_led_boost:
;ir_gesture_hw.c,1012 :: 		uint8_t ir_gesture_get_led_boost()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1017 :: 		ir_gesture_i2c_hal_read( APDS9960_CONFIG2, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #144
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1020 :: 		val = ( val >> 4 ) & 0x03;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #4
UXTB	R0, R0
AND	R0, R0, #3
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1022 :: 		return val;
;ir_gesture_hw.c,1023 :: 		}
L_end_ir_gesture_get_led_boost:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_led_boost
_ir_gesture_set_led_boost:
;ir_gesture_hw.c,1025 :: 		void ir_gesture_set_led_boost( uint8_t boost )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,1029 :: 		boost = MIN( boost, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_led_boost136
; ?FLOC___ir_gesture_set_led_boost?T746 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_led_boost?T746 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_led_boost137
L_ir_gesture_set_led_boost136:
; ?FLOC___ir_gesture_set_led_boost?T746 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_led_boost?T746 end address is: 0 (R0)
L_ir_gesture_set_led_boost137:
; ?FLOC___ir_gesture_set_led_boost?T746 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_led_boost?T746 end address is: 0 (R0)
;ir_gesture_hw.c,1032 :: 		ir_gesture_i2c_hal_read( APDS9960_CONFIG2, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #144
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1035 :: 		val &= ~( 1 << 4 ) | ( 1 << 5 );
LDRB	R2, [SP, #4]
MOVW	R1, #65519
SXTH	R1, R1
AND	R3, R2, R1, LSL #0
STRB	R3, [SP, #4]
;ir_gesture_hw.c,1036 :: 		boost = ( boost << 4 ) | val;
LDRB	R1, [SP, #8]
LSLS	R2, R1, #4
UXTH	R2, R2
UXTB	R1, R3
ORR	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,1039 :: 		ir_gesture_i2c_hal_write( APDS9960_CONFIG2, &boost, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #144
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1040 :: 		}
L_end_ir_gesture_set_led_boost:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_led_boost
_ir_gesture_read_proximity:
;ir_gesture_hw.c,1043 :: 		uint8_t ir_gesture_read_proximity( void )
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1045 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1048 :: 		ir_gesture_i2c_hal_read( APDS9960_PDATA, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #156
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1050 :: 		return val;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1051 :: 		}
L_end_ir_gesture_read_proximity:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_read_proximity
_ir_gesture_get_prox_int_low_thresh:
;ir_gesture_hw.c,1053 :: 		uint8_t ir_gesture_get_prox_int_low_thresh()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1055 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1058 :: 		ir_gesture_i2c_hal_read( APDS9960_PILT, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #137
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1060 :: 		return val;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1061 :: 		}
L_end_ir_gesture_get_prox_int_low_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_prox_int_low_thresh
_ir_gesture_set_prox_int_low_thresh:
;ir_gesture_hw.c,1063 :: 		void ir_gesture_set_prox_int_low_thresh( uint8_t threshold )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1065 :: 		ir_gesture_i2c_hal_write( APDS9960_PILT, &threshold, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #137
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1066 :: 		}
L_end_ir_gesture_set_prox_int_low_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_prox_int_low_thresh
_ir_gesture_get_prox_int_high_thresh:
;ir_gesture_hw.c,1068 :: 		uint8_t ir_gesture_get_prox_int_high_thresh()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1070 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1073 :: 		ir_gesture_i2c_hal_read( APDS9960_PIHT, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #139
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1075 :: 		return val;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1076 :: 		}
L_end_ir_gesture_get_prox_int_high_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_prox_int_high_thresh
_ir_gesture_set_prox_int_high_thresh:
;ir_gesture_hw.c,1078 :: 		void ir_gesture_set_prox_int_high_thresh( uint8_t threshold )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1080 :: 		ir_gesture_i2c_hal_write( APDS9960_PIHT, &threshold, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #139
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1081 :: 		}
L_end_ir_gesture_set_prox_int_high_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_prox_int_high_thresh
_ir_gesture_is_prox_gain_comp_enable:
;ir_gesture_hw.c,1083 :: 		bool ir_gesture_is_prox_gain_comp_enable()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1085 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1088 :: 		ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1091 :: 		val = ( val >> 5 ) & 0x01;
LDRB	R0, [SP, #4]
LSRS	R0, R0, #5
UXTB	R0, R0
AND	R0, R0, #1
UXTB	R0, R0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1093 :: 		return ( val == 1 ) ? true : false;
CMP	R0, #1
IT	NE
BNE	L_ir_gesture_is_prox_gain_comp_enable138
; ?FLOC___ir_gesture_is_prox_gain_comp_enable?T762 start address is: 0 (R0)
MOVS	R0, #1
SXTB	R0, R0
; ?FLOC___ir_gesture_is_prox_gain_comp_enable?T762 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_is_prox_gain_comp_enable139
L_ir_gesture_is_prox_gain_comp_enable138:
; ?FLOC___ir_gesture_is_prox_gain_comp_enable?T762 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_is_prox_gain_comp_enable?T762 end address is: 0 (R0)
L_ir_gesture_is_prox_gain_comp_enable139:
; ?FLOC___ir_gesture_is_prox_gain_comp_enable?T762 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___ir_gesture_is_prox_gain_comp_enable?T762 end address is: 0 (R0)
;ir_gesture_hw.c,1094 :: 		}
L_end_ir_gesture_is_prox_gain_comp_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_is_prox_gain_comp_enable
_ir_gesture_set_prox_gain_comp_enable:
;ir_gesture_hw.c,1096 :: 		void ir_gesture_set_prox_gain_comp_enable( bool enable )
; enable start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; enable end address is: 0 (R0)
; enable start address is: 0 (R0)
;ir_gesture_hw.c,1098 :: 		uint8_t val=0;
MOVS	R1, #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,1101 :: 		ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );
ADD	R1, SP, #8
STRB	R0, [SP, #4]
MOVS	R2, #1
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_read+0
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1104 :: 		val &= ~( 1 << 5 );
LDRB	R2, [SP, #8]
MOVW	R1, #65503
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,1106 :: 		if( enable )
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_set_prox_gain_comp_enable140
; enable end address is: 0 (R0)
;ir_gesture_hw.c,1107 :: 		val |= ( 1 << 5 );
LDRB	R1, [SP, #8]
ORR	R1, R1, #32
STRB	R1, [SP, #8]
L_ir_gesture_set_prox_gain_comp_enable140:
;ir_gesture_hw.c,1110 :: 		ir_gesture_i2c_hal_write( APDS9960_CONFIG3, &val, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1111 :: 		}
L_end_ir_gesture_set_prox_gain_comp_enable:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_prox_gain_comp_enable
_ir_gesture_get_prox_photo_mask:
;ir_gesture_hw.c,1113 :: 		uint8_t ir_gesture_get_prox_photo_mask()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1115 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1118 :: 		ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1121 :: 		val &= 0x0f;
LDRB	R0, [SP, #4]
AND	R0, R0, #15
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1123 :: 		return val;
;ir_gesture_hw.c,1124 :: 		}
L_end_ir_gesture_get_prox_photo_mask:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_prox_photo_mask
_ir_gesture_set_prox_photo_mask:
;ir_gesture_hw.c,1126 :: 		void ir_gesture_set_prox_photo_mask( uint8_t mask )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,1128 :: 		uint8_t val=0;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,1130 :: 		mask = MIN( mask, 0x03 );
LDRB	R1, [SP, #8]
CMP	R1, #3
IT	CS
BCS	L_ir_gesture_set_prox_photo_mask141
; ?FLOC___ir_gesture_set_prox_photo_mask?T771 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_prox_photo_mask?T771 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_prox_photo_mask142
L_ir_gesture_set_prox_photo_mask141:
; ?FLOC___ir_gesture_set_prox_photo_mask?T771 start address is: 0 (R0)
MOVS	R0, #3
; ?FLOC___ir_gesture_set_prox_photo_mask?T771 end address is: 0 (R0)
L_ir_gesture_set_prox_photo_mask142:
; ?FLOC___ir_gesture_set_prox_photo_mask?T771 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_prox_photo_mask?T771 end address is: 0 (R0)
;ir_gesture_hw.c,1133 :: 		ir_gesture_i2c_hal_read( APDS9960_CONFIG3, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1136 :: 		val &= ~( 1 << 0 ) | ( 1 << 1 )| ( 1 << 2 )| ( 1 << 3 );
LDRB	R2, [SP, #4]
MOVW	R1, #65534
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,1137 :: 		mask |= val;
UXTB	R2, R1
LDRB	R1, [SP, #8]
ORRS	R1, R2
STRB	R1, [SP, #8]
;ir_gesture_hw.c,1140 :: 		ir_gesture_i2c_hal_write( APDS9960_CONFIG3, &mask, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #159
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1141 :: 		}
L_end_ir_gesture_set_prox_photo_mask:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_prox_photo_mask
_ir_gesture_available:
;ir_gesture_hw.c,1145 :: 		bool ir_gesture_available()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1150 :: 		ir_gesture_i2c_hal_read( APDS9960_GSTATUS, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #175
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1153 :: 		val &= APDS9960_GVALID;
LDRB	R0, [SP, #4]
AND	R0, R0, #1
UXTB	R0, R0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1156 :: 		return ( val == 1 ) ? true : false;
CMP	R0, #1
IT	NE
BNE	L_ir_gesture_available143
; ?FLOC___ir_gesture_available?T780 start address is: 0 (R0)
MOVS	R0, #1
SXTB	R0, R0
; ?FLOC___ir_gesture_available?T780 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_available144
L_ir_gesture_available143:
; ?FLOC___ir_gesture_available?T780 start address is: 0 (R0)
MOVS	R0, #0
SXTB	R0, R0
; ?FLOC___ir_gesture_available?T780 end address is: 0 (R0)
L_ir_gesture_available144:
; ?FLOC___ir_gesture_available?T780 start address is: 0 (R0)
UXTB	R0, R0
; ?FLOC___ir_gesture_available?T780 end address is: 0 (R0)
;ir_gesture_hw.c,1157 :: 		}
L_end_ir_gesture_available:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_available
_ir_gesture_read_gesture:
;ir_gesture_hw.c,1159 :: 		gesture_dir_t ir_gesture_read_gesture()
SUB	SP, SP, #288
STR	LR, [SP, #0]
;ir_gesture_hw.c,1161 :: 		uint8_t fifo_count = 0;
ADD	R11, SP, #6
ADD	R10, R11, #280
MOVW	R12, #lo_addr(?ICSir_gesture_read_gesture_fifo_count_L0+0)
MOVT	R12, #hi_addr(?ICSir_gesture_read_gesture_fifo_count_L0+0)
BL	___CC2DW+0
;ir_gesture_hw.c,1162 :: 		gesture_data_t gesture_data = {0};
;ir_gesture_hw.c,1163 :: 		uint8_t fifo_data[132] = {0};
;ir_gesture_hw.c,1167 :: 		if( !ir_gesture_available() || !( get_mode() & 0b01000001 ) )
BL	_ir_gesture_available+0
CMP	R0, #0
IT	EQ
BEQ	L__ir_gesture_read_gesture238
BL	ir_gesture_hw_get_mode+0
AND	R0, R0, #65
UXTB	R0, R0
CMP	R0, #0
IT	EQ
BEQ	L__ir_gesture_read_gesture237
IT	AL
BAL	L_ir_gesture_read_gesture147
L__ir_gesture_read_gesture238:
L__ir_gesture_read_gesture237:
;ir_gesture_hw.c,1168 :: 		return DIR_NONE;
MOVS	R0, #0
IT	AL
BAL	L_end_ir_gesture_read_gesture
L_ir_gesture_read_gesture147:
;ir_gesture_hw.c,1170 :: 		while( 1 )
L_ir_gesture_read_gesture148:
;ir_gesture_hw.c,1172 :: 		ir_gesture_hal_delay( FIFO_PAUSE_TIME );
MOVS	R0, #110
BL	_ir_gesture_hal_delay+0
;ir_gesture_hw.c,1174 :: 		if( ir_gesture_available() )
BL	_ir_gesture_available+0
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_read_gesture150
;ir_gesture_hw.c,1177 :: 		ir_gesture_i2c_hal_read( APDS9960_GFLVL, &fifo_count, 1 );
ADD	R0, SP, #6
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #174
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1179 :: 		if( fifo_count > 0 )
LDRB	R0, [SP, #6]
CMP	R0, #0
IT	LS
BLS	L_ir_gesture_read_gesture151
;ir_gesture_hw.c,1181 :: 		ir_gesture_i2c_hal_read( APDS9960_GFIFO_U, fifo_data, fifo_count * 4 );
LDRB	R0, [SP, #6]
LSLS	R1, R0, #2
ADD	R0, SP, #154
UXTH	R2, R1
MOV	R1, R0
MOVS	R0, #252
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1184 :: 		for( i = 0; i < fifo_count; i += 4 )
MOVS	R0, #0
SXTH	R0, R0
STRH	R0, [SP, #4]
L_ir_gesture_read_gesture152:
LDRB	R1, [SP, #6]
LDRSH	R0, [SP, #4]
CMP	R0, R1
IT	GE
BGE	L_ir_gesture_read_gesture153
;ir_gesture_hw.c,1186 :: 		gesture_data.u_data[gesture_data.index] = fifo_data[i];
ADD	R1, SP, #8
LDRB	R0, [SP, #136]
ADDS	R1, R1, R0
ADD	R2, SP, #154
LDRSH	R0, [SP, #4]
ADDS	R0, R2, R0
LDRB	R0, [R0, #0]
STRB	R0, [R1, #0]
;ir_gesture_hw.c,1187 :: 		gesture_data.d_data[gesture_data.index] = fifo_data[i + 1];
ADD	R1, SP, #40
LDRB	R0, [SP, #136]
ADDS	R1, R1, R0
LDRSH	R0, [SP, #4]
ADDS	R0, R0, #1
SXTH	R0, R0
ADDS	R0, R2, R0
LDRB	R0, [R0, #0]
STRB	R0, [R1, #0]
;ir_gesture_hw.c,1188 :: 		gesture_data.l_data[gesture_data.index] = fifo_data[i + 2];
ADD	R1, SP, #72
LDRB	R0, [SP, #136]
ADDS	R1, R1, R0
LDRSH	R0, [SP, #4]
ADDS	R0, R0, #2
SXTH	R0, R0
ADDS	R0, R2, R0
LDRB	R0, [R0, #0]
STRB	R0, [R1, #0]
;ir_gesture_hw.c,1189 :: 		gesture_data.r_data[gesture_data.index] = fifo_data[i + 3];
ADD	R1, SP, #104
LDRB	R0, [SP, #136]
ADDS	R1, R1, R0
LDRSH	R0, [SP, #4]
ADDS	R0, R0, #3
SXTH	R0, R0
ADDS	R0, R2, R0
LDRB	R0, [R0, #0]
STRB	R0, [R1, #0]
;ir_gesture_hw.c,1190 :: 		gesture_data.index++;
LDRB	R0, [SP, #136]
ADDS	R0, R0, #1
STRB	R0, [SP, #136]
;ir_gesture_hw.c,1191 :: 		gesture_data.total_gestures++;
LDRB	R0, [SP, #137]
ADDS	R0, R0, #1
STRB	R0, [SP, #137]
;ir_gesture_hw.c,1184 :: 		for( i = 0; i < fifo_count; i += 4 )
LDRSH	R0, [SP, #4]
ADDS	R0, R0, #4
STRH	R0, [SP, #4]
;ir_gesture_hw.c,1192 :: 		}
IT	AL
BAL	L_ir_gesture_read_gesture152
L_ir_gesture_read_gesture153:
;ir_gesture_hw.c,1194 :: 		if( !process_gesture_data( &gesture_data ) )
ADD	R0, SP, #8
BL	ir_gesture_hw_process_gesture_data+0
CMP	R0, #0
IT	NE
BNE	L_ir_gesture_read_gesture155
;ir_gesture_hw.c,1196 :: 		if( !decode_gesture( &gesture_data ) )
ADD	R0, SP, #8
BL	ir_gesture_hw_decode_gesture+0
CMP	R0, #0
IT	NE
BNE	L_ir_gesture_read_gesture156
;ir_gesture_hw.c,1199 :: 		}
L_ir_gesture_read_gesture156:
;ir_gesture_hw.c,1200 :: 		}
L_ir_gesture_read_gesture155:
;ir_gesture_hw.c,1202 :: 		gesture_data.index = 0;
MOVS	R0, #0
STRB	R0, [SP, #136]
;ir_gesture_hw.c,1203 :: 		gesture_data.total_gestures = 0;
MOVS	R0, #0
STRB	R0, [SP, #137]
;ir_gesture_hw.c,1204 :: 		}
L_ir_gesture_read_gesture151:
;ir_gesture_hw.c,1205 :: 		} else {
IT	AL
BAL	L_ir_gesture_read_gesture157
L_ir_gesture_read_gesture150:
;ir_gesture_hw.c,1206 :: 		ir_gesture_hal_delay( FIFO_PAUSE_TIME );
MOVS	R0, #110
BL	_ir_gesture_hal_delay+0
;ir_gesture_hw.c,1207 :: 		decode_gesture( &gesture_data );
ADD	R0, SP, #8
BL	ir_gesture_hw_decode_gesture+0
;ir_gesture_hw.c,1209 :: 		return gesture_data.motion;
LDRB	R0, [SP, #153]
IT	AL
BAL	L_end_ir_gesture_read_gesture
;ir_gesture_hw.c,1210 :: 		}
L_ir_gesture_read_gesture157:
;ir_gesture_hw.c,1211 :: 		}
IT	AL
BAL	L_ir_gesture_read_gesture148
;ir_gesture_hw.c,1212 :: 		}
L_end_ir_gesture_read_gesture:
LDR	LR, [SP, #0]
ADD	SP, SP, #288
BX	LR
; end of _ir_gesture_read_gesture
_ir_gesture_get_gesture_mode:
;ir_gesture_hw.c,1214 :: 		uint8_t ir_gesture_get_gesture_mode()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1216 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1219 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #171
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1222 :: 		val &= 0x01;
LDRB	R0, [SP, #4]
AND	R0, R0, #1
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1224 :: 		return val;
;ir_gesture_hw.c,1225 :: 		}
L_end_ir_gesture_get_gesture_mode:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_gesture_mode
_ir_gesture_set_gesture_mode:
;ir_gesture_hw.c,1227 :: 		void ir_gesture_set_gesture_mode( bool mode )
; mode start address is: 0 (R0)
SUB	SP, SP, #12
STR	LR, [SP, #0]
; mode end address is: 0 (R0)
; mode start address is: 0 (R0)
;ir_gesture_hw.c,1232 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF4, &val, 1 );
ADD	R1, SP, #8
STRB	R0, [SP, #4]
MOVS	R2, #1
MOVS	R0, #171
BL	_ir_gesture_i2c_hal_read+0
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1235 :: 		val &= ~( 1 << 0 );
LDRB	R2, [SP, #8]
MOVW	R1, #65534
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #8]
;ir_gesture_hw.c,1237 :: 		if( mode )
CMP	R0, #0
IT	EQ
BEQ	L_ir_gesture_set_gesture_mode158
; mode end address is: 0 (R0)
;ir_gesture_hw.c,1238 :: 		val |= ( 1 << 0 );
LDRB	R1, [SP, #8]
ORR	R1, R1, #1
STRB	R1, [SP, #8]
L_ir_gesture_set_gesture_mode158:
;ir_gesture_hw.c,1241 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF4, &val, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #171
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1242 :: 		}
L_end_ir_gesture_set_gesture_mode:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_gesture_mode
_ir_gesture_enter_thresh:
;ir_gesture_hw.c,1244 :: 		uint8_t ir_gesture_enter_thresh()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1246 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1249 :: 		ir_gesture_i2c_hal_read( APDS9960_GPENTH, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #160
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1251 :: 		return val;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1252 :: 		}
L_end_ir_gesture_enter_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_enter_thresh
_ir_gesture_set_enter_thresh:
;ir_gesture_hw.c,1254 :: 		void ir_gesture_set_enter_thresh( uint8_t threshold )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1256 :: 		ir_gesture_i2c_hal_write( APDS9960_GPENTH, &threshold , 1);
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #160
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1257 :: 		}
L_end_ir_gesture_set_enter_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_enter_thresh
_ir_gesture_get_exit_thresh:
;ir_gesture_hw.c,1259 :: 		uint8_t ir_gesture_get_exit_thresh()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1261 :: 		uint8_t val = 0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1264 :: 		ir_gesture_i2c_hal_read( APDS9960_GEXTH, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #161
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1266 :: 		return val;
LDRB	R0, [SP, #4]
;ir_gesture_hw.c,1267 :: 		}
L_end_ir_gesture_get_exit_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_exit_thresh
_ir_gesture_set_exit_thresh:
;ir_gesture_hw.c,1269 :: 		void ir_gesture_set_exit_thresh( uint8_t threshold )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1271 :: 		ir_gesture_i2c_hal_write( APDS9960_GEXTH, &threshold, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #161
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1272 :: 		}
L_end_ir_gesture_set_exit_thresh:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_set_exit_thresh
_ir_gesture_get_wait_time:
;ir_gesture_hw.c,1274 :: 		uint8_t ir_gesture_get_wait_time()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;ir_gesture_hw.c,1276 :: 		uint8_t val=0;
MOVS	R0, #0
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1279 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );
ADD	R0, SP, #4
MOVS	R2, #1
MOV	R1, R0
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1282 :: 		val &= 0x07;
LDRB	R0, [SP, #4]
AND	R0, R0, #7
STRB	R0, [SP, #4]
;ir_gesture_hw.c,1284 :: 		return val;
;ir_gesture_hw.c,1285 :: 		}
L_end_ir_gesture_get_wait_time:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _ir_gesture_get_wait_time
_ir_gesture_set_wait_time:
;ir_gesture_hw.c,1287 :: 		void ir_gesture_set_wait_time( uint8_t time )
SUB	SP, SP, #12
STR	LR, [SP, #0]
STRB	R0, [SP, #8]
;ir_gesture_hw.c,1289 :: 		uint8_t val=0;
MOVS	R1, #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,1291 :: 		time = MIN( time, 0x07 );
LDRB	R1, [SP, #8]
CMP	R1, #7
IT	CS
BCS	L_ir_gesture_set_wait_time159
; ?FLOC___ir_gesture_set_wait_time?T843 start address is: 0 (R0)
LDRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_wait_time?T843 end address is: 0 (R0)
IT	AL
BAL	L_ir_gesture_set_wait_time160
L_ir_gesture_set_wait_time159:
; ?FLOC___ir_gesture_set_wait_time?T843 start address is: 0 (R0)
MOVS	R0, #7
; ?FLOC___ir_gesture_set_wait_time?T843 end address is: 0 (R0)
L_ir_gesture_set_wait_time160:
; ?FLOC___ir_gesture_set_wait_time?T843 start address is: 0 (R0)
STRB	R0, [SP, #8]
; ?FLOC___ir_gesture_set_wait_time?T843 end address is: 0 (R0)
;ir_gesture_hw.c,1294 :: 		ir_gesture_i2c_hal_read( APDS9960_GCONF2, &val, 1 );
ADD	R1, SP, #4
MOVS	R2, #1
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_read+0
;ir_gesture_hw.c,1297 :: 		val &= ~( 1 << 0 ) | ( 1 << 1 ) | ( 1 << 2 );
LDRB	R2, [SP, #4]
MOVW	R1, #65534
SXTH	R1, R1
AND	R1, R2, R1, LSL #0
STRB	R1, [SP, #4]
;ir_gesture_hw.c,1298 :: 		time |= val;
UXTB	R2, R1
LDRB	R1, [SP, #8]
ORRS	R1, R2
STRB	R1, [SP, #8]
;ir_gesture_hw.c,1301 :: 		ir_gesture_i2c_hal_write( APDS9960_GCONF2, &time, 1 );
ADD	R1, SP, #8
MOVS	R2, #1
MOVS	R0, #163
BL	_ir_gesture_i2c_hal_write+0
;ir_gesture_hw.c,1302 :: 		}
L_end_ir_gesture_set_wait_time:
LDR	LR, [SP, #0]
ADD	SP, SP, #12
BX	LR
; end of _ir_gesture_set_wait_time
