/* OLED screen SSD1351-related info
 * Project HEXIWEAR, 2015
 */

#ifndef HG_OLED_INFO
#define HG_OLED_INFO

// command byte number
#define FIRST_BYTE (1)
#define OTHER_BYTE (0)

#define OLED_COLUMN_OFFSET (16)
#define OLED_ROW_OFFSET    (0)

#define OLED_SCREEN_WIDTH  (96)
#define OLED_SCREEN_HEIGHT (96)

#define OLED_SCREEN_WIDTH_END  ( (OLED_SCREEN_WIDTH-1)  + OLED_COLUMN_OFFSET )
#define OLED_SCREEN_HEIGHT_END ( (OLED_SCREEN_HEIGHT-1) + OLED_ROW_OFFSET )

#define OLED_BYTES_PER_PIXEL ( 2 )

#define OLED_TRANSITION_STEP    ( 1 )
#define OLED_ACTION_DCON  ( 0xFE )
#define OLED_ACTION_DCOFF ( 0xFF )

#define OLED_CHAR_WIDTH_AUTO  ( 0xFF )
#define OLED_CHAR_WIDTH_MAX   ( 0xFE )
#define OLED_CHAR_WIDTH_NUM   ( 0xFD )
#define OLED_CHAR_WIDTH_KEEP  ( 0xFC )
#define OLED_CHAR_HEIGHT_AUTO ( 0xFB )
#define OLED_CHAR_HEIGHT_KEEP ( 0xFA )

#define OLED_SCREEN_SIZE ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT )
#define OLED_GRAM_SIZE ( OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL )

#define OLED_TEXT_HALIGN_SHIFT ( 0 )
#define OLED_TEXT_HALIGN_MASK  ( 0x03 << OLED_TEXT_HALIGN_SHIFT )

#define OLED_TEXT_VALIGN_SHIFT ( 4 )
#define OLED_TEXT_VALIGN_MASK  ( 0x03 << OLED_TEXT_VALIGN_SHIFT )

/**
 * remap settings
 */

#define REMAP_HORIZONTAL_INCREMENT ( 0 )
#define REMAP_VERTICAL_INCREMENT   ( 1 << 0 )

#define REMAP_COLUMNS_LEFT_TO_RIGHT ( 0 )
#define REMAP_COLUMNS_RIGHT_TO_LEFT ( 1 << 1 )

#define REMAP_ORDER_ABC ( 0 )
#define REMAP_ORDER_CBA ( 1 << 2 )

#define REMAP_SCAN_UP_TO_DOWN ( 0 )
#define REMAP_SCAN_DOWN_TO_UP ( 1 << 4 )

#define REMAP_COM_SPLIT_ODD_EVEN_DIS ( 0 )
#define REMAP_COM_SPLIT_ODD_EVEN_EN  ( 1 << 5 )

#define REMAP_COLOR_RGB565 ( 1 << 6 )


/**
 * macros
 */

#define OLED_SwapMe(x) x = ( ( x & 0xFF00 ) >> 8 ) | ( ( x & 0x00FF ) << 8 )

/**
 * set start/end column/row
 * the 2nd and 3rd byte represent the start and the end address, respectively
 */
#define OLED_CMD_SET_COLUMN ( 0x15 )
#define OLED_CMD_SET_ROW    ( 0x75 )

/**
 * scanning direction
 */

#define OLED_DIRECTION_HORIZONTAL (0)
#define OLED_DIRECTION_VERTICAL   (1)

/**
 * SPI-related
 */

/**
 * set display
 */
#define OLED_CMD_SET_DISPLAY_MODE_ALL_OFF (0xA4)
#define OLED_CMD_SET_DISPLAY_MODE_ALL_ON  (0xA5)
#define OLED_CMD_SET_DISPLAY_MODE_NORMAL  (0xA6)
#define OLED_CMD_SET_DISPLAY_MODE_INVERSE (0xA7)

/**
 * set lock command
 * the locked OLED driver MCU interface prohibits all commands
 * and memory access, except the 0xFD command
 */
#define OLED_CMD_SET_CMD_LOCK ( 0xFD /* << 8 */ )
// unlock OLED driver MCU interface for entering command (default upon reset)
#define OLED_UNLOCK           (0x12)
// lock OLED driver MCU interface for entering command
#define OLED_LOCK             (0x16)
// commands 0xA2, 0xB1, 0xB3, 0xBB, 0xBE, 0xC1 are inaccessible in both lock and unlock state (default upon reset)
#define OLED_ACC_TO_CMD_NO    (0xB0)
// commands 0xA2, 0xB1, 0xB3, 0xBB, 0xBE, 0xC1 are accessible in unlock state
#define OLED_ACC_TO_CMD_YES   (0xB1)

/**
 * NOP
 */
#define OLED_CMD_NOP (0xD1) // also, 0xE3

/**
 * set MUX ratio
 */
#define OLED_CMD_SET_MUX_RATIO (0xCA)

/**
 * set re-map / color depth
 */
#define OLED_CMD_SET_REMAP ( 0xA0 )

// set horisontal or vertical increment
#define OLED_ADDR_INC_HOR (0x00)
#define OLED_ADDR_INC_VER (0x01)

// column address mapping
#define OLED_COLUMN_ADDR_REMAP_0_TO_SEG0   (0x00)
#define OLED_COLUMN_ADDR_REMAP_127_TO_SEG0 (0x02)

// color sequence order
#define OLED_COLOR_SEQ_A_B_C (0x00)
#define OLED_COLOR_SEQ_C_B_A (0x04)

// scanning order (MR == MUX ratio)
#define OLED_SCAN_FROM_COM_0_TO_MR (0x00)
#define OLED_SCAN_FROM_COM_MR_TO_0 (0x10)

// COM splitting to odd and even
#define OLED_COM_SPLIT_DISABLE (0x00)
#define OLED_COM_SPLIT_ENABLE  (0x20)

// screen color depth
#define OLED_COLOR_DEPTH_256    (0x00)
#define OLED_COLOR_DEPTH_65K    (0x40)
#define OLED_COLOR_DEPTH_262K_1 (0x80)
#define OLED_COLOR_DEPTH_262K_2 (0xC0)

/**
 * set reset (phase 1) / pre-charge (phase 2) period in [DCLK]
 * this command is locked by command 0xFD by default
 */
#define OLED_CMD_SET_RESET_AND_PRECHARGE_PERIOD (0xB1)

#define OLED_RESET_PERIOD_5  (0x02)
#define OLED_RESET_PERIOD_7  (0x03)
#define OLED_RESET_PERIOD_9  (0x04)
#define OLED_RESET_PERIOD_11 (0x05)
#define OLED_RESET_PERIOD_13 (0x06)
#define OLED_RESET_PERIOD_15 (0x07)
#define OLED_RESET_PERIOD_17 (0x08)
#define OLED_RESET_PERIOD_19 (0x09)
#define OLED_RESET_PERIOD_21 (0x0A)
#define OLED_RESET_PERIOD_23 (0x0B)
#define OLED_RESET_PERIOD_25 (0x0C)
#define OLED_RESET_PERIOD_27 (0x0D)
#define OLED_RESET_PERIOD_29 (0x0E)
#define OLED_RESET_PERIOD_31 (0x0F)

#define OLED_PRECHARGE_PERIOD_3  (0x03)
#define OLED_PRECHARGE_PERIOD_4  (0x04)
#define OLED_PRECHARGE_PERIOD_5  (0x05)
#define OLED_PRECHARGE_PERIOD_6  (0x06)
#define OLED_PRECHARGE_PERIOD_7  (0x07)
#define OLED_PRECHARGE_PERIOD_8  (0x08)
#define OLED_PRECHARGE_PERIOD_9  (0x09)
#define OLED_PRECHARGE_PERIOD_10 (0x0A)
#define OLED_PRECHARGE_PERIOD_11 (0x0B)
#define OLED_PRECHARGE_PERIOD_12 (0x0C)
#define OLED_PRECHARGE_PERIOD_13 (0x0D)
#define OLED_PRECHARGE_PERIOD_14 (0x0E)
#define OLED_PRECHARGE_PERIOD_15 (0x0F)

/**
 * set front clock divider (divset) / oscillator frequency
 * this command is locked by command 0xFD by default
 */
#define OLED_CMD_SET_OSC_FREQ_AND_CLOCKDIV (0xB3)

// clock divider
#define OLED_CLOCKDIV_1    (0x00)
#define OLED_CLOCKDIV_2    (0x01)
#define OLED_CLOCKDIV_4    (0x02)
#define OLED_CLOCKDIV_8    (0x03)
#define OLED_CLOCKDIV_16   (0x04)
#define OLED_CLOCKDIV_32   (0x05)
#define OLED_CLOCKDIV_64   (0x06)
#define OLED_CLOCKDIV_128  (0x07)
#define OLED_CLOCKDIV_256  (0x08)
#define OLED_CLOCKDIV_512  (0x09)
#define OLED_CLOCKDIV_1024 (0x0A)

// oscillator frequency, frequency increases as level increases
#define OLED_OSC_FREQ (0xB0)

#define OLED_CMD_STARTLINE (0xA1)

#define OLED_CMD_WRITERAM       (0x5C)
#define OLED_CMD_READRAM        (0x5D)
#define OLED_CMD_DISPLAYOFFSET  (0xA2)
#define OLED_CMD_DISPLAYALLOFF  (0xA4)
#define OLED_CMD_DISPLAYALLON   (0xA5)
#define OLED_CMD_NORMALDISPLAY  (0xA6)
#define OLED_CMD_INVERTDISPLAY  (0xA7)
#define OLED_CMD_FUNCTIONSELECT (0xAB)
#define OLED_CMD_DISPLAYOFF     (0xAE)
#define OLED_CMD_DISPLAYON      (0xAF)
#define OLED_CMD_PRECHARGE      (0xB1)
#define OLED_CMD_DISPLAYENHANCE (0xB2)
#define OLED_CMD_SETVSL         (0xB4)
#define OLED_CMD_SETGPIO        (0xB5)
#define OLED_CMD_PRECHARGE2     (0xB6)
#define OLED_CMD_SETGRAY        (0xB8)
#define OLED_CMD_USELUT         (0xB9)
#define OLED_CMD_PRECHARGELEVEL (0xBB)
#define OLED_CMD_VCOMH          (0xBE)
#define OLED_CMD_CONTRASTABC    (0xC1)
#define OLED_CMD_CONTRASTMASTER (0xC7)
#define OLED_CMD_MUXRATIO       (0xCA)
#define OLED_CMD_COMMANDLOCK    (0xFD)
#define OLED_CMD_HORIZSCROLL    (0x96)
#define OLED_CMD_STOPSCROLL     (0x9E)
#define OLED_CMD_STARTSCROLL    (0x9F)

#endif