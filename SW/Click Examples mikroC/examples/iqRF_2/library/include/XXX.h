/**
 * @file                                                            XXX.h
 * @brief               	XXX
 *
 * @defgroup XXX
 * @brief			XXX Driver
 *
 * This is driver for ________________ ... ... ... ...
 *
 * @{
 *
 * ### Device Description ###
 * .... .... .... 
 * 
 *
 * ### Features ###
 * -
 * -
 * -
 *
 * ### Library Description
 *	...
 * 	...
 *
 * @example <clickname>_ARM.c
 * @example <clickname>_PIC.c
 * @example <clickname>_PIC32.c
 * @example <clickname>_dsPIC.c
 * @example <clickname>_AVR.c
 * @example <clickname>_FT90x.c
 *
 ******************************************************************************/

#ifndef XXX_H
#define XXX_H

#include ...

/**
 * @name 		Device Properties
 ******************************************************************************/
///@{

#define XXX_ADDRESS		0x00

///@}
/**
 * @name 		Return Values
 ******************************************************************************/
///@{

#define XXX_OK			(0)
#define XXX_ERR			(-1)

///@}
/**
 * @name 		Types
 ******************************************************************************/
///@{

typedef ...

///@}
/**
 * @name 		Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> XXX Initialization </h3>
 *
 * @param[in]   intput - <input description>
 * @param[out]  *output - <output description>
 *
 * @retval      XXX_OK
 * @retval      XXX_ERROR
 *
 * Initializes XXX 
 *
 * @note
 * This function must be called first.
 *
 */
int XXX_init( int input, int *output );

#ifdef __cplusplus
} // extern "C"
#endif
#endif
///@}
/**
 * @} 								End of File
 ******************************************************************************/
