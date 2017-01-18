_led_eight_hal_cs_high:
;eight_x_eight_hal.c,51 :: 		void led_eight_hal_cs_high()
;eight_x_eight_hal.c,53 :: 		LED_EIGHT_CS = 1;
MOVS	R1, #1
SXTB	R1, R1
MOVW	R0, #lo_addr(LED_EIGHT_CS+0)
MOVT	R0, #hi_addr(LED_EIGHT_CS+0)
STR	R1, [R0, #0]
;eight_x_eight_hal.c,54 :: 		}
L_end_led_eight_hal_cs_high:
BX	LR
; end of _led_eight_hal_cs_high
_led_eight_hal_cs_low:
;eight_x_eight_hal.c,56 :: 		void led_eight_hal_cs_low()
;eight_x_eight_hal.c,58 :: 		LED_EIGHT_CS = 0;
MOVS	R1, #0
SXTB	R1, R1
MOVW	R0, #lo_addr(LED_EIGHT_CS+0)
MOVT	R0, #hi_addr(LED_EIGHT_CS+0)
STR	R1, [R0, #0]
;eight_x_eight_hal.c,59 :: 		}
L_end_led_eight_hal_cs_low:
BX	LR
; end of _led_eight_hal_cs_low
_led_eight_hal_init:
;eight_x_eight_hal.c,61 :: 		void led_eight_hal_init()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;eight_x_eight_hal.c,63 :: 		write_spi_p             = SPI_Wr_Ptr;
MOVW	R0, #lo_addr(_SPI_Wr_Ptr+0)
MOVT	R0, #hi_addr(_SPI_Wr_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(eight_x_eight_hal_write_spi_p+0)
MOVT	R0, #hi_addr(eight_x_eight_hal_write_spi_p+0)
STR	R1, [R0, #0]
;eight_x_eight_hal.c,64 :: 		read_spi_p              = SPI_Rd_Ptr;
MOVW	R0, #lo_addr(_SPI_Rd_Ptr+0)
MOVT	R0, #hi_addr(_SPI_Rd_Ptr+0)
LDR	R1, [R0, #0]
MOVW	R0, #lo_addr(eight_x_eight_hal_read_spi_p+0)
MOVT	R0, #hi_addr(eight_x_eight_hal_read_spi_p+0)
STR	R1, [R0, #0]
;eight_x_eight_hal.c,65 :: 		led_eight_hal_cs_high();
BL	_led_eight_hal_cs_high+0
;eight_x_eight_hal.c,66 :: 		}
L_end_led_eight_hal_init:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _led_eight_hal_init
_led_eight_hal_write:
;eight_x_eight_hal.c,68 :: 		void led_eight_hal_write( uint8_t *buffer )
SUB	SP, SP, #8
STR	LR, [SP, #0]
STR	R0, [SP, #4]
;eight_x_eight_hal.c,70 :: 		led_eight_hal_cs_low();
BL	_led_eight_hal_cs_low+0
;eight_x_eight_hal.c,71 :: 		write_spi_p( *( buffer )++ );
LDR	R1, [SP, #4]
LDRB	R1, [R1, #0]
UXTB	R4, R1
UXTH	R0, R4
MOVW	R4, #lo_addr(eight_x_eight_hal_write_spi_p+0)
MOVT	R4, #hi_addr(eight_x_eight_hal_write_spi_p+0)
LDR	R4, [R4, #0]
BLX	R4
LDR	R1, [SP, #4]
ADDS	R1, R1, #1
;eight_x_eight_hal.c,72 :: 		write_spi_p( *buffer );
LDRB	R1, [R1, #0]
UXTB	R4, R1
UXTH	R0, R4
MOVW	R4, #lo_addr(eight_x_eight_hal_write_spi_p+0)
MOVT	R4, #hi_addr(eight_x_eight_hal_write_spi_p+0)
LDR	R4, [R4, #0]
BLX	R4
;eight_x_eight_hal.c,73 :: 		led_eight_hal_cs_high();
BL	_led_eight_hal_cs_high+0
;eight_x_eight_hal.c,74 :: 		}
L_end_led_eight_hal_write:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _led_eight_hal_write
