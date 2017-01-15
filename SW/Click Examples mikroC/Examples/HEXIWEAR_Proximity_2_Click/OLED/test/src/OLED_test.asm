_main:
;OLED_test.c,24 :: 		void main() org 0x1000
SUB	SP, SP, #4
;OLED_test.c,26 :: 		OLED_Init();
BL	_OLED_Init+0
;OLED_test.c,59 :: 		OLED_GetImageDimensions( &sampleImageArea.width, &sampleImageArea.height, bond_screen_bmp );
MOVW	R0, #lo_addr(_bond_screen_bmp+0)
MOVT	R0, #hi_addr(_bond_screen_bmp+0)
MOV	R2, R0
MOVW	R1, #lo_addr(_sampleImageArea+3)
MOVT	R1, #hi_addr(_sampleImageArea+3)
MOVW	R0, #lo_addr(_sampleImageArea+2)
MOVT	R0, #hi_addr(_sampleImageArea+2)
BL	_OLED_GetImageDimensions+0
;OLED_test.c,60 :: 		OLED_SetDynamicArea( &sampleImageArea );
MOVW	R0, #lo_addr(_sampleImageArea+0)
MOVT	R0, #hi_addr(_sampleImageArea+0)
BL	_OLED_SetDynamicArea+0
;OLED_test.c,62 :: 		OLED_DrawImage( bond_screen_bmp );
MOVW	R0, #lo_addr(_bond_screen_bmp+0)
MOVT	R0, #hi_addr(_bond_screen_bmp+0)
BL	_OLED_DrawImage+0
;OLED_test.c,64 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
