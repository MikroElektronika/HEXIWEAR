// File: arm_common_tables.h

// Declarations of resources in the ARM RFFT module.

#ifndef _arm_common_tables_h_
#define _arm_common_tables_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// floating-point bit reversal tables
#define ARMBITREVINDEXTABLE__16_TABLE_LENGTH ((uint16_t)20  )
#define ARMBITREVINDEXTABLE__32_TABLE_LENGTH ((uint16_t)48  )
#define ARMBITREVINDEXTABLE__64_TABLE_LENGTH ((uint16_t)56  )
#define ARMBITREVINDEXTABLE_128_TABLE_LENGTH ((uint16_t)208 )
#define ARMBITREVINDEXTABLE_256_TABLE_LENGTH ((uint16_t)440 )
#define ARMBITREVINDEXTABLE_512_TABLE_LENGTH ((uint16_t)448 )
#define ARMBITREVINDEXTABLE1024_TABLE_LENGTH ((uint16_t)1800)
#define ARMBITREVINDEXTABLE2048_TABLE_LENGTH ((uint16_t)3808)
#define ARMBITREVINDEXTABLE4096_TABLE_LENGTH ((uint16_t)4032)

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

extern const uint16_t
    armBitRevIndexTable16[ ARMBITREVINDEXTABLE__16_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable32[ ARMBITREVINDEXTABLE__32_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable64[ ARMBITREVINDEXTABLE__64_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable128[ ARMBITREVINDEXTABLE_128_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable256[ ARMBITREVINDEXTABLE_256_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable512[ ARMBITREVINDEXTABLE_512_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable1024[ ARMBITREVINDEXTABLE1024_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable2048[ ARMBITREVINDEXTABLE2048_TABLE_LENGTH ];
extern const uint16_t
    armBitRevIndexTable4096[ ARMBITREVINDEXTABLE4096_TABLE_LENGTH ];

extern const double twiddleCoef_16[32];
extern const double twiddleCoef_32[64];
extern const double twiddleCoef_64[128];
extern const double twiddleCoef_128[256];
extern const double twiddleCoef_256[512];
extern const double twiddleCoef_512[1024];
extern const double twiddleCoef_1024[2048];
extern const double twiddleCoef_2048[4096];

extern const double twiddleCoef_rfft_32[32];
extern const double twiddleCoef_rfft_64[64];
extern const double twiddleCoef_rfft_128[128];
extern const double twiddleCoef_rfft_256[256];
extern const double twiddleCoef_rfft_512[512];
extern const double twiddleCoef_rfft_1024[1024];
extern const double twiddleCoef_rfft_2048[2048];
extern const double twiddleCoef_rfft_4096[4096];

#endif