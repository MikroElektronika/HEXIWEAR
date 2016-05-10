/**
 * boot types
 */

#ifndef HG_BOOT_TYPES
#define HG_BOOT_TYPES

#include <stdint.h>
#include "EmbeddedTypes.h"
#include "boot_info.h"

typedef void (*vector_entry)(void);
typedef void pointer(void);

typedef union
{
  uint32_t Data[4];

  struct
  {
    uint32_t BackDoorKey[2];
    uint32_t Protection;
    uint32_t Config;
  };

} flash_config_t;

typedef PACKED_STRUCT
{
  uint8_t  newBootImageAvailable[ FLASH_WRITE_ALIGN ];
  uint8_t  firstTimeBoot[ FLASH_WRITE_ALIGN ];
  uint8_t  bootVersion[2];
  uint8_t  padding[4];

} bootInfo_t;

 #endif
