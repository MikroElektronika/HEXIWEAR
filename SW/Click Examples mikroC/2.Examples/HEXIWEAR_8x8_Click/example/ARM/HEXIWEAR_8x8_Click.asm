_main:
;HEXIWEAR_8x8_Click.c,76 :: 		void main()
;HEXIWEAR_8x8_Click.c,78 :: 		OLED_Init();
BL	_OLED_Init+0
;HEXIWEAR_8x8_Click.c,79 :: 		OLED_DrawImage( &RGB8x8_bmp, 0, 0 );
MOVW	R0, #lo_addr(_RGB8x8_bmp+0)
MOVT	R0, #hi_addr(_RGB8x8_bmp+0)
MOVS	R2, #0
MOVS	R1, #0
BL	_OLED_DrawImage+0
;HEXIWEAR_8x8_Click.c,81 :: 		GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
MOV	R1, #16
MOVW	R0, #lo_addr(PTC_PDOR+0)
MOVT	R0, #hi_addr(PTC_PDOR+0)
BL	_GPIO_Digital_Output+0
;HEXIWEAR_8x8_Click.c,83 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
MOVW	R2, #lo_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVT	R2, #hi_addr(__GPIO_Module_SPI0_PC5_7_6+0)
MOVW	R1, #7
MOVT	R1, #32768
;HEXIWEAR_8x8_Click.c,82 :: 		SPI0_Init_Advanced(5000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
MOVW	R0, #19264
MOVT	R0, #76
;HEXIWEAR_8x8_Click.c,83 :: 		_SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);
BL	_SPI0_Init_Advanced+0
;HEXIWEAR_8x8_Click.c,85 :: 		Delay_ms(400);
MOVW	R7, #9214
MOVT	R7, #244
NOP
NOP
L_main0:
SUBS	R7, R7, #1
BNE	L_main0
NOP
NOP
NOP
;HEXIWEAR_8x8_Click.c,87 :: 		led_eight_init();
BL	_led_eight_init+0
;HEXIWEAR_8x8_Click.c,89 :: 		while(1)
L_main2:
;HEXIWEAR_8x8_Click.c,91 :: 		led_eight_scroll_text(text_1, 10);
MOVS	R1, #10
MOVW	R0, #lo_addr(_text_1+0)
MOVT	R0, #hi_addr(_text_1+0)
BL	_led_eight_scroll_text+0
;HEXIWEAR_8x8_Click.c,92 :: 		led_eight_scroll_text(text_2, 10);
MOVS	R1, #10
MOVW	R0, #lo_addr(_text_2+0)
MOVT	R0, #hi_addr(_text_2+0)
BL	_led_eight_scroll_text+0
;HEXIWEAR_8x8_Click.c,93 :: 		led_eight_scroll_text(text_3, 10);
MOVS	R1, #10
MOVW	R0, #lo_addr(_text_3+0)
MOVT	R0, #hi_addr(_text_3+0)
BL	_led_eight_scroll_text+0
;HEXIWEAR_8x8_Click.c,94 :: 		}
IT	AL
BAL	L_main2
;HEXIWEAR_8x8_Click.c,95 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
