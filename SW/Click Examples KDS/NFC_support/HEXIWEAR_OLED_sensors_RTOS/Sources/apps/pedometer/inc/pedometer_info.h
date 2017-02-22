/**
 * various defines
 */

#pragma once

#define KEYNETIK_APPID  ( 20 )
#define PEDOMETER_APPID ( 21 )

#define PEDOMETER_STATUS_ACTIVITY_BITNUM ( 0 )
#define PEDOMETER_STATUS_SUSPEND_BITNUM  ( 3 )
#define PEDOMETER_STATUS_ACTCHG_BITNUM   ( 4 )
#define PEDOMETER_STATUS_STEPCHG_BITNUM  ( 5 )
#define PEDOMETER_STATUS_SUSPCHG_BITNUM  ( 6 )
#define PEDOMETER_STATUS_MRGFLG_BITNUM   ( 7 )

#define PEDOMETER_STATUS_CHG_MASK         (\
                                              PEDOMETER_STATUS_ACTCHG_MASK\
                                            | PEDOMETER_STATUS_STEPCHG_MASK\
                                            | PEDOMETER_STATUS_SUSPCHG_MASK\
                                          )

#define PEDOMETER_STATUS_ACTIVITY_MASK   ( 7 << PEDOMETER_STATUS_ACTIVITY_BITNUM )
#define PEDOMETER_STATUS_SUSPEND_MASK    ( 1 << PEDOMETER_STATUS_SUSPEND_BITNUM )
#define PEDOMETER_STATUS_ACTCHG_MASK     ( 1 << PEDOMETER_STATUS_ACTCHG_BITNUM )
#define PEDOMETER_STATUS_STEPCHG_MASK    ( 1 << PEDOMETER_STATUS_STEPCHG_BITNUM )
#define PEDOMETER_STATUS_SUSPCHG_MASK    ( 1 << PEDOMETER_STATUS_SUSPCHG_BITNUM )
#define PEDOMETER_STATUS_MRGFLG_MASK     ( 1 << PEDOMETER_STATUS_MRGFLG_BITNUM )


// tasks' info
#define PEDOMETER_STACK_SIZE ( 0x400 ) // todo: change to meaningful value
#define PEDOMETER_PRIO ( HEXIWEAR_APP_PRIO ) // todo: change to meaningful value

// queues' info
#define PEDOMETER_QUEUE_SIZE ( 3 )
