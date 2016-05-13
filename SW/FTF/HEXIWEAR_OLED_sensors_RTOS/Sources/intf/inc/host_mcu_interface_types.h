/**
 * Interface-related data types
 * Project HEXIWEAR, 2015
 */

typedef enum
{
  hostInterface_rxState_idle           = 0,
  hostInterface_rxState_headerReceived = 3,
  hostInterface_rxState_dataWait       = 4,
  hostInterface_rxState_trailerWait    = 5

} hostInterface_rxState_t;
