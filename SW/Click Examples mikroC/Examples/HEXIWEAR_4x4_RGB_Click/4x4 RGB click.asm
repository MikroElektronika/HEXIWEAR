_RGBLed_ZeroBit:
;4x4 RGB click.c,102 :: 		void RGBLed_ZeroBit() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,103 :: 		RGBLed_Data = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,104 :: 		Delay_Cyc(3);
MOVS	R0, #3
BL	_Delay_Cyc+0
;4x4 RGB click.c,105 :: 		RGBLed_Data = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,106 :: 		Delay_Cyc(7);
MOVS	R0, #7
BL	_Delay_Cyc+0
;4x4 RGB click.c,107 :: 		}
L_end_RGBLed_ZeroBit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _RGBLed_ZeroBit
_RGBLed_OneBit:
;4x4 RGB click.c,109 :: 		void RGBLed_OneBit() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,110 :: 		RGBLed_Data = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,111 :: 		Delay_Cyc(7);
MOVS	R0, #7
BL	_Delay_Cyc+0
;4x4 RGB click.c,112 :: 		RGBLed_Data = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,113 :: 		Delay_Cyc(6);
MOVS	R0, #6
BL	_Delay_Cyc+0
;4x4 RGB click.c,114 :: 		}
L_end_RGBLed_OneBit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _RGBLed_OneBit
_RGBLed_ResetDelay:
;4x4 RGB click.c,116 :: 		void RGBLed_ResetDelay() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,117 :: 		Delay_50us();
BL	_Delay_50us+0
;4x4 RGB click.c,118 :: 		Delay_10us();
BL	_Delay_10us+0
;4x4 RGB click.c,119 :: 		}
L_end_RGBLed_ResetDelay:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _RGBLed_ResetDelay
_RGBLed_InitDiode:
;4x4 RGB click.c,121 :: 		void RGBLed_InitDiode(unsigned long ARGBColor, unsigned long * AdiodeArray) {
; AdiodeArray start address is: 4 (R1)
; ARGBColor start address is: 0 (R0)
; AdiodeArray end address is: 4 (R1)
; ARGBColor end address is: 0 (R0)
; ARGBColor start address is: 0 (R0)
; AdiodeArray start address is: 4 (R1)
;4x4 RGB click.c,122 :: 		*AdiodeArray = (ARGBColor & 0x000000FF) | ((ARGBColor >> 16) << 8) | ((ARGBColor >> 8) << 16);
AND	R3, R0, #255
LSRS	R2, R0, #16
LSLS	R2, R2, #8
ORRS	R3, R2
LSRS	R2, R0, #8
; ARGBColor end address is: 0 (R0)
LSLS	R2, R2, #16
ORR	R2, R3, R2, LSL #0
STR	R2, [R1, #0]
; AdiodeArray end address is: 4 (R1)
;4x4 RGB click.c,123 :: 		}
L_end_RGBLed_InitDiode:
BX	LR
; end of _RGBLed_InitDiode
_RGBLed_SetColor:
;4x4 RGB click.c,125 :: 		void RGBLed_SetColor(unsigned long * AdiodeArray) {
; AdiodeArray start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; AdiodeArray end address is: 0 (R0)
; AdiodeArray start address is: 0 (R0)
;4x4 RGB click.c,128 :: 		for (i = 23; i >= 0; i--) {
; i start address is: 16 (R4)
MOVS	R4, #23
SXTB	R4, R4
; AdiodeArray end address is: 0 (R0)
; i end address is: 16 (R4)
MOV	R3, R0
L_RGBLed_SetColor0:
; i start address is: 16 (R4)
; AdiodeArray start address is: 12 (R3)
; AdiodeArray start address is: 12 (R3)
; AdiodeArray end address is: 12 (R3)
CMP	R4, #0
IT	LT
BLT	L_RGBLed_SetColor1
; AdiodeArray end address is: 12 (R3)
;4x4 RGB click.c,129 :: 		if (( (*AdiodeArray) & (1ul << i)) == 0) {
; AdiodeArray start address is: 12 (R3)
LDR	R2, [R3, #0]
MOV	R1, #1
LSLS	R1, R4
AND	R1, R2, R1, LSL #0
CMP	R1, #0
IT	NE
BNE	L_RGBLed_SetColor3
;4x4 RGB click.c,130 :: 		RGBLed_ZeroBit();
BL	_RGBLed_ZeroBit+0
;4x4 RGB click.c,131 :: 		}
IT	AL
BAL	L_RGBLed_SetColor4
L_RGBLed_SetColor3:
;4x4 RGB click.c,133 :: 		RGBLed_OneBit();
BL	_RGBLed_OneBit+0
;4x4 RGB click.c,134 :: 		}
L_RGBLed_SetColor4:
;4x4 RGB click.c,128 :: 		for (i = 23; i >= 0; i--) {
SUBS	R4, R4, #1
SXTB	R4, R4
;4x4 RGB click.c,135 :: 		}
; AdiodeArray end address is: 12 (R3)
; i end address is: 16 (R4)
IT	AL
BAL	L_RGBLed_SetColor0
L_RGBLed_SetColor1:
;4x4 RGB click.c,136 :: 		}
L_end_RGBLed_SetColor:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _RGBLed_SetColor
_RGBLed_SetDiode:
;4x4 RGB click.c,138 :: 		void RGBLed_SetDiode(char ANum, unsigned long AColor, unsigned long * AdiodeArray) {
; AdiodeArray start address is: 8 (R2)
; AColor start address is: 4 (R1)
; ANum start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
MOV	R3, R2
MOV	R2, R1
UXTB	R1, R0
; AdiodeArray end address is: 8 (R2)
; AColor end address is: 4 (R1)
; ANum end address is: 0 (R0)
; ANum start address is: 4 (R1)
; AColor start address is: 8 (R2)
; AdiodeArray start address is: 12 (R3)
;4x4 RGB click.c,141 :: 		for (i = 0; i < MAX_SIZE; i++) {
; i start address is: 0 (R0)
MOVS	R0, #0
; ANum end address is: 4 (R1)
; AColor end address is: 8 (R2)
; AdiodeArray end address is: 12 (R3)
; i end address is: 0 (R0)
UXTB	R7, R1
MOV	R6, R2
MOV	R5, R3
UXTB	R8, R0
L_RGBLed_SetDiode5:
; i start address is: 32 (R8)
; ANum start address is: 28 (R7)
; AColor start address is: 24 (R6)
; AdiodeArray start address is: 20 (R5)
; AdiodeArray start address is: 20 (R5)
; AdiodeArray end address is: 20 (R5)
; AColor start address is: 24 (R6)
; AColor end address is: 24 (R6)
; ANum start address is: 28 (R7)
; ANum end address is: 28 (R7)
CMP	R8, #16
IT	CS
BCS	L_RGBLed_SetDiode6
; AdiodeArray end address is: 20 (R5)
; AColor end address is: 24 (R6)
; ANum end address is: 28 (R7)
;4x4 RGB click.c,142 :: 		if (i == (ANum - 1)) {
; ANum start address is: 28 (R7)
; AColor start address is: 24 (R6)
; AdiodeArray start address is: 20 (R5)
SUBS	R3, R7, #1
SXTH	R3, R3
CMP	R8, R3
IT	NE
BNE	L_RGBLed_SetDiode8
;4x4 RGB click.c,143 :: 		RGBLed_InitDiode(AColor, &AdiodeArray[i]);
LSL	R3, R8, #2
ADDS	R3, R5, R3
MOV	R1, R3
MOV	R0, R6
BL	_RGBLed_InitDiode+0
;4x4 RGB click.c,144 :: 		RGBLed_SetColor(&AdiodeArray[i]);
LSL	R3, R8, #2
ADDS	R3, R5, R3
MOV	R0, R3
BL	_RGBLed_SetColor+0
;4x4 RGB click.c,145 :: 		}
IT	AL
BAL	L_RGBLed_SetDiode9
L_RGBLed_SetDiode8:
;4x4 RGB click.c,147 :: 		RGBLed_SetColor(&AdiodeArray[i]);
LSL	R3, R8, #2
ADDS	R3, R5, R3
MOV	R0, R3
BL	_RGBLed_SetColor+0
;4x4 RGB click.c,148 :: 		}
L_RGBLed_SetDiode9:
;4x4 RGB click.c,141 :: 		for (i = 0; i < MAX_SIZE; i++) {
ADD	R8, R8, #1
UXTB	R8, R8
;4x4 RGB click.c,149 :: 		}
; AdiodeArray end address is: 20 (R5)
; AColor end address is: 24 (R6)
; ANum end address is: 28 (R7)
; i end address is: 32 (R8)
IT	AL
BAL	L_RGBLed_SetDiode5
L_RGBLed_SetDiode6:
;4x4 RGB click.c,150 :: 		RGBLed_ResetDelay();
BL	_RGBLed_ResetDelay+0
;4x4 RGB click.c,151 :: 		}
L_end_RGBLed_SetDiode:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _RGBLed_SetDiode
_RGBLed_InitHW:
;4x4 RGB click.c,153 :: 		void RGBLed_InitHW() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,154 :: 		GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11);        // Initialize data output pin
MOV	R1, #2048
MOVW	R0, #lo_addr(PTB_PDOR+0)
MOVT	R0, #hi_addr(PTB_PDOR+0)
BL	_GPIO_Digital_Output+0
;4x4 RGB click.c,155 :: 		}
L_end_RGBLed_InitHW:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _RGBLed_InitHW
_Delay_time:
;4x4 RGB click.c,158 :: 		void Delay_time() {
;4x4 RGB click.c,160 :: 		for (n1=1; n1<=n; n1++)
; n1 start address is: 4 (R1)
MOVS	R1, #1
; n1 end address is: 4 (R1)
L_Delay_time10:
; n1 start address is: 4 (R1)
MOVW	R0, #lo_addr(_n+0)
MOVT	R0, #hi_addr(_n+0)
LDRSH	R0, [R0, #0]
CMP	R1, R0
IT	HI
BHI	L_Delay_time11
;4x4 RGB click.c,161 :: 		delay_ms(5);
MOVW	R7, #3390
MOVT	R7, #3
NOP
NOP
L_Delay_time13:
SUBS	R7, R7, #1
BNE	L_Delay_time13
NOP
NOP
NOP
;4x4 RGB click.c,160 :: 		for (n1=1; n1<=n; n1++)
ADDS	R1, R1, #1
UXTH	R1, R1
;4x4 RGB click.c,161 :: 		delay_ms(5);
; n1 end address is: 4 (R1)
IT	AL
BAL	L_Delay_time10
L_Delay_time11:
;4x4 RGB click.c,162 :: 		}
L_end_Delay_time:
BX	LR
; end of _Delay_time
_Snake:
;4x4 RGB click.c,165 :: 		void Snake() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,166 :: 		RGBLed_SetDiode(4, TempColor, DiodeArray);  // Turn on diode 4 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #4
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,167 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,168 :: 		RGBLed_SetDiode(3, TempColor, DiodeArray);  // Turn on diode 3 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #3
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,169 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,170 :: 		RGBLed_SetDiode(2, TempColor, DiodeArray);  // Turn on diode 2 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #2
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,171 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,172 :: 		RGBLed_SetDiode(1, TempColor, DiodeArray);  // Turn on diode 1 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #1
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,173 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,174 :: 		RGBLed_SetDiode(5, TempColor, DiodeArray);  // Turn on diode 5 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #5
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,175 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,176 :: 		RGBLed_SetDiode(9, TempColor, DiodeArray);  // Turn on diode 9 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #9
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,177 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,178 :: 		RGBLed_SetDiode(13, TempColor, DiodeArray); // Turn on diode 13 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #13
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,179 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,180 :: 		RGBLed_SetDiode(14, TempColor, DiodeArray); // Turn on diode 14 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #14
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,181 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,182 :: 		RGBLed_SetDiode(15, TempColor, DiodeArray); // Turn on diode 15 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #15
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,183 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,184 :: 		RGBLed_SetDiode(16, TempColor, DiodeArray); // Turn on diode 16 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #16
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,185 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,186 :: 		RGBLed_SetDiode(12, TempColor, DiodeArray); // Turn on diode 12 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #12
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,187 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,188 :: 		RGBLed_SetDiode(8, TempColor, DiodeArray);  // Turn on diode 8 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #8
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,189 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,190 :: 		RGBLed_SetDiode(7, TempColor, DiodeArray);  // Turn on diode 7 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #7
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,191 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,192 :: 		RGBLed_SetDiode(6, TempColor, DiodeArray);  // Turn on diode 6 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #6
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,193 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,194 :: 		RGBLed_SetDiode(10, TempColor, DiodeArray); // Turn on diode 10 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #10
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,195 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,196 :: 		RGBLed_SetDiode(11, TempColor, DiodeArray); // Turn on diode 11 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #11
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,197 :: 		}
L_end_Snake:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Snake
_Snake_return:
;4x4 RGB click.c,199 :: 		void Snake_return ()  {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,200 :: 		RGBLed_SetDiode(11, TempColor, DiodeArray); // Turn on diode 11 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #11
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,201 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,202 :: 		RGBLed_SetDiode(10, TempColor, DiodeArray); // Turn on diode 10 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #10
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,203 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,204 :: 		RGBLed_SetDiode(6, TempColor, DiodeArray);  // Turn on diode 6 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #6
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,205 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,206 :: 		RGBLed_SetDiode(7, TempColor, DiodeArray);  // Turn on diode 7 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #7
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,207 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,208 :: 		RGBLed_SetDiode(8, TempColor, DiodeArray);  // Turn on diode 8 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #8
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,209 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,210 :: 		RGBLed_SetDiode(12, TempColor, DiodeArray); // Turn on diode 12 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #12
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,211 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,212 :: 		RGBLed_SetDiode(16, TempColor, DiodeArray); // Turn on diode 16 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #16
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,213 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,214 :: 		RGBLed_SetDiode(15, TempColor, DiodeArray); // Turn on diode 15 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #15
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,215 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,216 :: 		RGBLed_SetDiode(14, TempColor, DiodeArray); // Turn on diode 14 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #14
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,217 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,218 :: 		RGBLed_SetDiode(13, TempColor, DiodeArray); // Turn on diode 13 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #13
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,219 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,220 :: 		RGBLed_SetDiode(9, TempColor, DiodeArray);  // Turn on diode 9 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #9
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,221 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,222 :: 		RGBLed_SetDiode(5, TempColor, DiodeArray);  // Turn on diode 5 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #5
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,223 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,224 :: 		RGBLed_SetDiode(1, TempColor, DiodeArray);  // Turn on diode 1 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #1
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,225 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,226 :: 		RGBLed_SetDiode(2, TempColor, DiodeArray);  // Turn on diode 2 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #2
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,227 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,228 :: 		RGBLed_SetDiode(3, TempColor, DiodeArray);  // Turn on diode 3 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #3
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,229 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,230 :: 		RGBLed_SetDiode(4, TempColor, DiodeArray);  // Turn on diode 4 with the desired color
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
MOVS	R0, #4
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,231 :: 		Delay_time();
BL	_Delay_time+0
;4x4 RGB click.c,232 :: 		}
L_end_Snake_return:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Snake_return
_FillScreen:
;4x4 RGB click.c,235 :: 		void FillScreen() {
SUB	SP, SP, #4
STR	LR, [SP, #0]
;4x4 RGB click.c,237 :: 		for (n2=1; n2<=16; n2++) {
; n2 start address is: 36 (R9)
MOVW	R9, #1
; n2 end address is: 36 (R9)
L_FillScreen15:
; n2 start address is: 36 (R9)
CMP	R9, #16
IT	HI
BHI	L_FillScreen16
;4x4 RGB click.c,238 :: 		RGBLed_SetDiode(n2, TempColor, DiodeArray);
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
LDR	R0, [R0, #0]
MOVW	R2, #lo_addr(_DiodeArray+0)
MOVT	R2, #hi_addr(_DiodeArray+0)
MOV	R1, R0
UXTB	R0, R9
BL	_RGBLed_SetDiode+0
;4x4 RGB click.c,239 :: 		delay_ms(100);
MOVW	R7, #2302
MOVT	R7, #61
NOP
NOP
L_FillScreen18:
SUBS	R7, R7, #1
BNE	L_FillScreen18
NOP
NOP
NOP
;4x4 RGB click.c,237 :: 		for (n2=1; n2<=16; n2++) {
ADD	R9, R9, #1
UXTH	R9, R9
;4x4 RGB click.c,240 :: 		}
; n2 end address is: 36 (R9)
IT	AL
BAL	L_FillScreen15
L_FillScreen16:
;4x4 RGB click.c,241 :: 		}
L_end_FillScreen:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _FillScreen
_main:
;4x4 RGB click.c,244 :: 		void main()
SUB	SP, SP, #8
;4x4 RGB click.c,246 :: 		OLED_Init();
BL	_OLED_Init+0
;4x4 RGB click.c,247 :: 		OLED_DrawImage( A4x4RGB_bmp, 0, 0 );
MOVW	R0, #lo_addr(_A4x4RGB_bmp+0)
MOVT	R0, #hi_addr(_A4x4RGB_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;4x4 RGB click.c,248 :: 		RGBLed_InitHW();            // Initialize RGB HW
BL	_RGBLed_InitHW+0
;4x4 RGB click.c,249 :: 		TempColor = 0x002F2F2F;     // White
MOVW	R1, #12079
MOVT	R1, #47
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,250 :: 		FillScreen();               // Fill screen with color
BL	_FillScreen+0
;4x4 RGB click.c,251 :: 		while(1)
L_main20:
;4x4 RGB click.c,254 :: 		n=20;                       // 20*5ms = 100ms delay
MOVS	R1, #20
SXTH	R1, R1
MOVW	R0, #lo_addr(_n+0)
MOVT	R0, #hi_addr(_n+0)
STR	R0, [SP, #4]
STRH	R1, [R0, #0]
;4x4 RGB click.c,255 :: 		TempColor = 0x0000002F;     // Blue color
MOVS	R1, #47
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
STR	R0, [SP, #0]
STR	R1, [R0, #0]
;4x4 RGB click.c,256 :: 		Snake();
BL	_Snake+0
;4x4 RGB click.c,257 :: 		TempColor = 0x00002F2F;     // Bright blue color
MOVW	R1, #12079
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,258 :: 		Snake_return ();
BL	_Snake_return+0
;4x4 RGB click.c,261 :: 		n=15;                       // 15*5ms = 75ms delay
MOVS	R1, #15
SXTH	R1, R1
MOVW	R0, #lo_addr(_n+0)
MOVT	R0, #hi_addr(_n+0)
STRH	R1, [R0, #0]
;4x4 RGB click.c,262 :: 		TempColor = 0x00002F00;     // Green colcor
MOVW	R1, #12032
LDR	R0, [SP, #0]
STR	R1, [R0, #0]
;4x4 RGB click.c,263 :: 		Snake();
BL	_Snake+0
;4x4 RGB click.c,264 :: 		TempColor = 0x002F2F00;     // Yellow color back
MOVW	R1, #12032
MOVT	R1, #47
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,265 :: 		Snake_return();
BL	_Snake_return+0
;4x4 RGB click.c,268 :: 		TempColor = 0x002F0000;     // Red color
MOV	R1, #3080192
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,269 :: 		n=10;                       // 10*5ms = 50ms delay
MOVS	R1, #10
SXTH	R1, R1
LDR	R0, [SP, #4]
STRH	R1, [R0, #0]
;4x4 RGB click.c,270 :: 		Snake();
BL	_Snake+0
;4x4 RGB click.c,271 :: 		TempColor = 0x002F002F;     // Purple color back
MOV	R1, #3080239
MOVW	R0, #lo_addr(_TempColor+0)
MOVT	R0, #hi_addr(_TempColor+0)
STR	R1, [R0, #0]
;4x4 RGB click.c,272 :: 		Snake_return ();
BL	_Snake_return+0
;4x4 RGB click.c,275 :: 		n=5;                        // 5*5ms = 25ms delay
MOVS	R1, #5
SXTH	R1, R1
MOVW	R0, #lo_addr(_n+0)
MOVT	R0, #hi_addr(_n+0)
STRH	R1, [R0, #0]
;4x4 RGB click.c,276 :: 		TempColor = 0x002F2F2F;     // White
MOVW	R1, #12079
MOVT	R1, #47
LDR	R0, [SP, #0]
STR	R1, [R0, #0]
;4x4 RGB click.c,277 :: 		Snake_return ();
BL	_Snake_return+0
;4x4 RGB click.c,278 :: 		}
IT	AL
BAL	L_main20
;4x4 RGB click.c,279 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
