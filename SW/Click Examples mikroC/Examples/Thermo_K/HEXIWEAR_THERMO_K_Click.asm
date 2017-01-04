_Write_MCP9600_Data:
;HEXIWEAR_THERMO_K_Click.c,24 :: 		char Write_MCP9600_Data( char RegAddr, char _data )
; _data start address is: 4 (R1)
; RegAddr start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; _data end address is: 4 (R1)
; RegAddr end address is: 0 (R0)
; RegAddr start address is: 0 (R0)
; _data start address is: 4 (R1)
;HEXIWEAR_THERMO_K_Click.c,26 :: 		tmp_data[0] = RegAddr;                                                        // Register address
MOVW	R2, #lo_addr(_tmp_data+0)
MOVT	R2, #hi_addr(_tmp_data+0)
STRB	R0, [R2, #0]
; RegAddr end address is: 0 (R0)
;HEXIWEAR_THERMO_K_Click.c,27 :: 		tmp_data[1] = _data;
MOVW	R2, #lo_addr(_tmp_data+1)
MOVT	R2, #hi_addr(_tmp_data+1)
STRB	R1, [R2, #0]
; _data end address is: 4 (R1)
;HEXIWEAR_THERMO_K_Click.c,29 :: 		I2C_Start();                                                                  // Issue I2C start signal
BL	_I2C_Start+0
;HEXIWEAR_THERMO_K_Click.c,30 :: 		I2C_Write( MCP9600_I2C_ADDR, tmp_data, 2, END_MODE_STOP );                    // Send two bytes (tmp_data[0] and tmp_data[1])
MOVW	R3, #1
MOVS	R2, #2
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Write+0
;HEXIWEAR_THERMO_K_Click.c,31 :: 		}
L_end_Write_MCP9600_Data:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Write_MCP9600_Data
_Read_MCP9600_Data:
;HEXIWEAR_THERMO_K_Click.c,40 :: 		char Read_MCP9600_Data( char RegAddr )
; RegAddr start address is: 0 (R0)
SUB	SP, SP, #4
STR	LR, [SP, #0]
; RegAddr end address is: 0 (R0)
; RegAddr start address is: 0 (R0)
;HEXIWEAR_THERMO_K_Click.c,42 :: 		tmp_data[0] = RegAddr;                                                        // Register address
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
STRB	R0, [R1, #0]
; RegAddr end address is: 0 (R0)
;HEXIWEAR_THERMO_K_Click.c,44 :: 		I2C_Start();                                                                  // Issue I2C start signal
BL	_I2C_Start+0
;HEXIWEAR_THERMO_K_Click.c,45 :: 		I2C_Write( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_RESTART );                 // Send byte (tmp_data[0])
MOVW	R3, #0
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Write+0
;HEXIWEAR_THERMO_K_Click.c,46 :: 		Delay_us( 50 );                                                               // delay 50 us
MOVW	R7, #1998
MOVT	R7, #0
NOP
NOP
L_Read_MCP9600_Data0:
SUBS	R7, R7, #1
BNE	L_Read_MCP9600_Data0
NOP
NOP
NOP
;HEXIWEAR_THERMO_K_Click.c,47 :: 		I2C_Read( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_STOP);                      // Read register data value and store it in tmp_data
MOVW	R3, #1
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Read+0
;HEXIWEAR_THERMO_K_Click.c,49 :: 		return tmp_data[0];                                                           // Return MCP9600 Data value
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
LDRB	R0, [R1, #0]
;HEXIWEAR_THERMO_K_Click.c,50 :: 		}
L_end_Read_MCP9600_Data:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Read_MCP9600_Data
_Read_MCP9600_Status:
;HEXIWEAR_THERMO_K_Click.c,59 :: 		char Read_MCP9600_Status()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_THERMO_K_Click.c,63 :: 		tmp_data[0] = MCP9600_Status;                                                 // Register address
MOVS	R1, #4
MOVW	R0, #lo_addr(_tmp_data+0)
MOVT	R0, #hi_addr(_tmp_data+0)
STRB	R1, [R0, #0]
;HEXIWEAR_THERMO_K_Click.c,65 :: 		I2C_Start();                                                                  // Issue I2C start signal
BL	_I2C_Start+0
;HEXIWEAR_THERMO_K_Click.c,66 :: 		I2C_Write( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_RESTART );                 // Send byte (tmp_data[0])
MOVW	R3, #0
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Write+0
;HEXIWEAR_THERMO_K_Click.c,67 :: 		Delay_us( 50 );                                                               // delay 50 us
MOVW	R7, #1998
MOVT	R7, #0
NOP
NOP
L_Read_MCP9600_Status2:
SUBS	R7, R7, #1
BNE	L_Read_MCP9600_Status2
NOP
NOP
NOP
;HEXIWEAR_THERMO_K_Click.c,68 :: 		I2C_Read( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_STOP );                     // Read register data value and store it in tmp_data
MOVW	R3, #1
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Read+0
;HEXIWEAR_THERMO_K_Click.c,72 :: 		return DataSum;                                                                 // Return MCP9600 Data value
MOVW	R0, #lo_addr(_tmp_data+0)
MOVT	R0, #hi_addr(_tmp_data+0)
LDRB	R0, [R0, #0]
;HEXIWEAR_THERMO_K_Click.c,73 :: 		}
L_end_Read_MCP9600_Status:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Read_MCP9600_Status
_Read_Temperature:
;HEXIWEAR_THERMO_K_Click.c,82 :: 		float Read_Temperature()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;HEXIWEAR_THERMO_K_Click.c,86 :: 		tmp_data[0] = MCP9600_TH;                                                     // Thermocouple Temperature register
MOVS	R1, #0
MOVW	R0, #lo_addr(_tmp_data+0)
MOVT	R0, #hi_addr(_tmp_data+0)
STRB	R1, [R0, #0]
;HEXIWEAR_THERMO_K_Click.c,88 :: 		I2C_Start();                                                                  // Issue I2C start signal
BL	_I2C_Start+0
;HEXIWEAR_THERMO_K_Click.c,89 :: 		I2C_Write( MCP9600_I2C_ADDR, tmp_data, 1, END_MODE_RESTART );                 // Send byte (tmp_data[0])
MOVW	R3, #0
MOVS	R2, #1
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Write+0
;HEXIWEAR_THERMO_K_Click.c,90 :: 		Delay_us( 50 );                                                               // delay 50 us
MOVW	R7, #1998
MOVT	R7, #0
NOP
NOP
L_Read_Temperature4:
SUBS	R7, R7, #1
BNE	L_Read_Temperature4
NOP
NOP
NOP
;HEXIWEAR_THERMO_K_Click.c,91 :: 		I2C_Read( MCP9600_I2C_ADDR, tmp_data, 2, END_MODE_STOP );                     // Read thermocouple temperature and store it in tmp_data
MOVW	R3, #1
MOVS	R2, #2
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
MOVS	R0, #96
BL	_I2C_Read+0
;HEXIWEAR_THERMO_K_Click.c,93 :: 		if( (tmp_data[0] & 0x80) == 0x80 )
MOVW	R0, #lo_addr(_tmp_data+0)
MOVT	R0, #hi_addr(_tmp_data+0)
LDRB	R0, [R0, #0]
AND	R0, R0, #128
UXTB	R0, R0
CMP	R0, #128
IT	NE
BNE	L_Read_Temperature6
;HEXIWEAR_THERMO_K_Click.c,95 :: 		tmp_data[0] = tmp_data[0] & 0x7F;                                           // Clear SIGN
MOVW	R1, #lo_addr(_tmp_data+0)
MOVT	R1, #hi_addr(_tmp_data+0)
LDRB	R0, [R1, #0]
AND	R0, R0, #127
UXTB	R0, R0
STRB	R0, [R1, #0]
;HEXIWEAR_THERMO_K_Click.c,96 :: 		Temperature = 1024 - ( tmp_data[0] * 16 + tmp_data[1] / 16 );
LSLS	R1, R0, #4
SXTH	R1, R1
MOVW	R0, #lo_addr(_tmp_data+1)
MOVT	R0, #hi_addr(_tmp_data+1)
LDRB	R0, [R0, #0]
LSRS	R0, R0, #4
UXTB	R0, R0
ADDS	R0, R1, R0
SXTH	R0, R0
RSB	R0, R0, #1024
SXTH	R0, R0
VMOV	S0, R0
VCVT.F32	#1, S0, S0
; Temperature start address is: 0 (R0)
;HEXIWEAR_THERMO_K_Click.c,97 :: 		}
; Temperature end address is: 0 (R0)
IT	AL
BAL	L_Read_Temperature7
L_Read_Temperature6:
;HEXIWEAR_THERMO_K_Click.c,99 :: 		Temperature = ( tmp_data[0] * 16 + (float)tmp_data[1] / 16 );               // Temperature = Ambient Temperature (°C)
MOVW	R0, #lo_addr(_tmp_data+0)
MOVT	R0, #hi_addr(_tmp_data+0)
LDRB	R0, [R0, #0]
LSLS	R1, R0, #4
SXTH	R1, R1
MOVW	R0, #lo_addr(_tmp_data+1)
MOVT	R0, #hi_addr(_tmp_data+1)
LDRB	R0, [R0, #0]
VMOV	S1, R0
VCVT.F32	#0, S1, S1
VMOV.F32	S0, #16
VDIV.F32	S1, S1, S0
VMOV	S0, R1
VCVT.F32	#1, S0, S0
VADD.F32	S0, S0, S1
; Temperature start address is: 4 (R1)
VMOV.F32	S1, S0
; Temperature end address is: 4 (R1)
VMOV.F32	S0, S1
L_Read_Temperature7:
;HEXIWEAR_THERMO_K_Click.c,101 :: 		return Temperature;                                                           // Return Thermocouple temperature data
; Temperature start address is: 0 (R0)
; Temperature end address is: 0 (R0)
;HEXIWEAR_THERMO_K_Click.c,102 :: 		}
L_end_Read_Temperature:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _Read_Temperature
_updateLabel:
;HEXIWEAR_THERMO_K_Click.c,111 :: 		void updateLabel( char *newText, int x, int y, char* lbl )
SUB	SP, SP, #20
STR	LR, [SP, #0]
STR	R0, [SP, #4]
STRH	R1, [SP, #8]
STRH	R2, [SP, #12]
STR	R3, [SP, #16]
;HEXIWEAR_THERMO_K_Click.c,113 :: 		OLED_SetFont( guiFont_Tahoma_10_Regular , OLED_COLOR_BLACK, 0 );
MOVW	R4, #lo_addr(_guiFont_Tahoma_10_Regular+0)
MOVT	R4, #hi_addr(_guiFont_Tahoma_10_Regular+0)
MOVS	R2, #0
MOVW	R1, #0
MOV	R0, R4
BL	_OLED_SetFont+0
;HEXIWEAR_THERMO_K_Click.c,114 :: 		OLED_WriteText( lbl, x, y );
LDRSH	R2, [SP, #12]
LDRSH	R1, [SP, #8]
LDR	R0, [SP, #16]
BL	_OLED_WriteText+0
;HEXIWEAR_THERMO_K_Click.c,115 :: 		strcpy( lbl, newText );
LDR	R1, [SP, #4]
LDR	R0, [SP, #16]
BL	_strcpy+0
;HEXIWEAR_THERMO_K_Click.c,116 :: 		OLED_SetFont( guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R4, #lo_addr(_guiFont_Tahoma_10_Regular+0)
MOVT	R4, #hi_addr(_guiFont_Tahoma_10_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
MOV	R0, R4
BL	_OLED_SetFont+0
;HEXIWEAR_THERMO_K_Click.c,117 :: 		OLED_WriteText( lbl, x, y );
LDRSH	R2, [SP, #12]
LDRSH	R1, [SP, #8]
LDR	R0, [SP, #16]
BL	_OLED_WriteText+0
;HEXIWEAR_THERMO_K_Click.c,118 :: 		}
L_end_updateLabel:
LDR	LR, [SP, #0]
ADD	SP, SP, #20
BX	LR
; end of _updateLabel
_main:
;HEXIWEAR_THERMO_K_Click.c,123 :: 		void main()
;HEXIWEAR_THERMO_K_Click.c,125 :: 		OLED_Init();                                                                  // Initialize OLED display
BL	_OLED_Init+0
;HEXIWEAR_THERMO_K_Click.c,126 :: 		I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
MOVW	R1, #lo_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVT	R1, #hi_addr(__GPIO_Module_I2C0_PD8_9+0)
MOVW	R0, #34464
MOVT	R0, #1
BL	_I2C0_Init_Advanced+0
;HEXIWEAR_THERMO_K_Click.c,127 :: 		delay_ms( 200 );
MOVW	R7, #4606
MOVT	R7, #122
NOP
NOP
L_main8:
SUBS	R7, R7, #1
BNE	L_main8
NOP
NOP
NOP
;HEXIWEAR_THERMO_K_Click.c,129 :: 		OLED_FillScreen( OLED_COLOR_BLACK );
MOVW	R0, #0
BL	_OLED_FillScreen+0
;HEXIWEAR_THERMO_K_Click.c,130 :: 		OLED_DrawImage( thermo_K_bmp, 0, 10 );
MOVS	R2, #10
MOVS	R1, #0
MOVW	R0, #lo_addr(_thermo_K_bmp+0)
MOVT	R0, #hi_addr(_thermo_K_bmp+0)
BL	_OLED_DrawImage+0
;HEXIWEAR_THERMO_K_Click.c,131 :: 		OLED_SetFont( guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0 );
MOVW	R0, #lo_addr(_guiFont_Tahoma_10_Regular+0)
MOVT	R0, #hi_addr(_guiFont_Tahoma_10_Regular+0)
MOVS	R2, #0
MOVW	R1, #65535
BL	_OLED_SetFont+0
;HEXIWEAR_THERMO_K_Click.c,132 :: 		OLED_WriteText( "Thermo K click", 5, 75 );
MOVW	R0, #lo_addr(?lstr1_HEXIWEAR_THERMO_K_Click+0)
MOVT	R0, #hi_addr(?lstr1_HEXIWEAR_THERMO_K_Click+0)
MOVS	R2, #75
MOVS	R1, #5
BL	_OLED_WriteText+0
;HEXIWEAR_THERMO_K_Click.c,134 :: 		while(1)
L_main10:
;HEXIWEAR_THERMO_K_Click.c,136 :: 		status = Read_MCP9600_Status();
BL	_Read_MCP9600_Status+0
MOVW	R1, #lo_addr(_status+0)
MOVT	R1, #hi_addr(_status+0)
STRB	R0, [R1, #0]
;HEXIWEAR_THERMO_K_Click.c,137 :: 		Temp_Data_Ready = (status & 0x40);
AND	R1, R0, #64
UXTB	R1, R1
MOVW	R0, #lo_addr(_Temp_Data_Ready+0)
MOVT	R0, #hi_addr(_Temp_Data_Ready+0)
STRB	R1, [R0, #0]
;HEXIWEAR_THERMO_K_Click.c,139 :: 		if ( Temp_Data_Ready )
CMP	R1, #0
IT	EQ
BEQ	L_main12
;HEXIWEAR_THERMO_K_Click.c,141 :: 		sprintf( _txt, "%2.1fºC", Read_Temperature() );                           // Format Temperature Data and store it to txt
BL	_Read_Temperature+0
MOVW	R1, #lo_addr(?lstr_2_HEXIWEAR_THERMO_K_Click+0)
MOVT	R1, #hi_addr(?lstr_2_HEXIWEAR_THERMO_K_Click+0)
MOVW	R0, #lo_addr(__txt+0)
MOVT	R0, #hi_addr(__txt+0)
VPUSH	#0, (S0)
PUSH	(R1)
PUSH	(R0)
BL	_sprintf+0
ADD	SP, SP, #12
;HEXIWEAR_THERMO_K_Click.c,142 :: 		res = strcmp( _txt, old_txt );                                            // Compare old_txt and txt
MOVW	R1, #lo_addr(_old_txt+0)
MOVT	R1, #hi_addr(_old_txt+0)
MOVW	R0, #lo_addr(__txt+0)
MOVT	R0, #hi_addr(__txt+0)
BL	_strcmp+0
MOVW	R1, #lo_addr(_res+0)
MOVT	R1, #hi_addr(_res+0)
STRB	R0, [R1, #0]
;HEXIWEAR_THERMO_K_Click.c,144 :: 		if( res != 0 )
UXTB	R0, R0
CMP	R0, #0
IT	EQ
BEQ	L_main13
;HEXIWEAR_THERMO_K_Click.c,146 :: 		updateLabel( _txt, 55, 20, lab1 );                                      // Write temperature value on display
MOVW	R3, #lo_addr(_lab1+0)
MOVT	R3, #hi_addr(_lab1+0)
MOVS	R2, #20
SXTH	R2, R2
MOVS	R1, #55
SXTH	R1, R1
MOVW	R0, #lo_addr(__txt+0)
MOVT	R0, #hi_addr(__txt+0)
BL	_updateLabel+0
;HEXIWEAR_THERMO_K_Click.c,147 :: 		strcpy( old_txt, _txt );                                                // Copy txt to old_txt string array
MOVW	R1, #lo_addr(__txt+0)
MOVT	R1, #hi_addr(__txt+0)
MOVW	R0, #lo_addr(_old_txt+0)
MOVT	R0, #hi_addr(_old_txt+0)
BL	_strcpy+0
;HEXIWEAR_THERMO_K_Click.c,148 :: 		}
L_main13:
;HEXIWEAR_THERMO_K_Click.c,149 :: 		}
L_main12:
;HEXIWEAR_THERMO_K_Click.c,150 :: 		delay_ms( 500 );
MOVW	R7, #11518
MOVT	R7, #305
NOP
NOP
L_main14:
SUBS	R7, R7, #1
BNE	L_main14
NOP
NOP
NOP
;HEXIWEAR_THERMO_K_Click.c,151 :: 		}
IT	AL
BAL	L_main10
;HEXIWEAR_THERMO_K_Click.c,152 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
