/*
 * hal_ac_current.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Sep/2016) Module created                          Stefan Popovic
 *
 * 
 ******************************************************************************/
 #include "hal_ac_current.h"
  
/*                Preprocessors
 ******************************************************************************/

/*                Typedefs
 ******************************************************************************/


/*                Variables
 ******************************************************************************/

#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )
static void         ( *write_spi_p )            ( unsigned int data_out );
static unsigned int ( *read_spi_p )             ( unsigned int buffer );

#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )
static void         ( *write_spi_p )            ( unsigned char data_out );
static unsigned char( *read_spi_p )             ( unsigned char dummy );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static void         ( *write_spi_p )            ( unsigned long data_out );
static unsigned long( *read_spi_p )             ( unsigned long dummy );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static void         ( *write_spi_p )            ( unsigned char data_out );
static unsigned char( *read_spi_p )             ( unsigned char dummy );
#endif
/*                 Private Function Prototypes
 ******************************************************************************/

/*                 Private Function Definitions
 ******************************************************************************/

void hal_ac_current_delay( uint16_t ms )
{
#if defined(__MIKROC_PRO_FOR_ARM__)     || \
    defined( __MIKROC_PRO_FOR_FT90x__ ) || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_8051__ )  || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_PIC__ )
    while( ms-- )
        Delay_1ms();
#endif
}

void hal_ac_current_init( )
{
#if defined( __MIKROC_PRO_FOR_ARM__ )   || \
    defined( __MIKROC_PRO_FOR_AVR__ )   || \
    defined( __MIKROC_PRO_FOR_DSPIC__ ) || \
    defined( __MIKROC_PRO_FOR_PIC32__ ) || \
    defined( __MIKROC_PRO_FOR_8051__ )
    write_spi_p             = SPI_Wr_Ptr;
    read_spi_p              = SPI_Rd_Ptr;

#elif defined( __MIKROC_PRO_FOR_PIC__ )
    write_spi_p             = SPI1_Write;
    read_spi_p              = SPI1_Read;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    write_spi_p             = SPIM_Wr_Ptr;
    read_spi_p              = SPIM_Rd_Ptr;
#endif

}

void hal_ac_current_read
(
        uint8_t* buffer,
        uint16_t count
)
{
    uint8_t *ptr = buffer;

    while( count-- )
            *ptr++ = read_spi_p( 0x00 );
}

/*                                                                 End of File
 ******************************************************************************/