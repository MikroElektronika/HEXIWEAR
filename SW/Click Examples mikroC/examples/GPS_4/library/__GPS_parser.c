/*

    __GPS_parser.c

    Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

--------------------------------------------------------------------------------

    Version : 0.0.2

    Revision Log :

 - 0.0.1 (Aug/2015) Module created                   Richard Lowe
 - 0.0.2 (Apr/2017) Standardization and minor fixes  Djordje Rosic
    
        
        To Do List :

 - Write get functions for TXT and ZDA messages.

*******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include "__GPS_defs.h"
#include "__GPS_parser.h"

#ifdef  __MIKROC_PRO_FOR_AVR__
#elif __MIKROC_PRO_FOR_PIC__ 
#elif __MIKROC_PRO_FOR_DSPIC__ 
#elif __MIKROC_PRO_FOR_PIC32__ 
#elif __MIKROC_PRO_FOR_8051__ 
#elif __MIKROC_PRO_FOR_FT90x__
#elif __MIKROC_PRO_FOR_ARM__
#else
#define ON_PC
#endif

#define field( NAME )  fields->tokens[ NAME ][ 0 ]
#define token( NAME )  fields->tokens[ NAME ]


/* Globals
 ******************************************************************************/
/* Used in Parsing */
static volatile char bufferSentence[ BUFFER_MAX ];
static char processBuffer[ BUFFER_MAX ];
static volatile uint8_t bufferPosition;
static volatile bool processFlag;

/* Global information recieved from several sentences */
static T_GPS_location currentLongitude;
static T_GPS_location currentLatitude;
static T_GPS_time currentTime;
static T_GPS_utcTime currentFix;

// Type of parsing to be done.
#define TIME 0
#define LOCATION_LAT 1
#define LOCATION_LON 2


// GGA fields
#define GGA_fix_tIME 0
#define GGA_LAT 1
#define GGA_LAT_AZMUTH 2
#define GGA_LON 3
#define GGA_LON_AZMUTH 4
#define GGA_FIX_QUALITY 5
#define GGA_NUM_SATS 6
#define GGA_HORT_DIL 7
#define GGA_ALT 8
#define GGA_METERS 9
#define GGA_HEIGHT 10
#define GGA_METERS2 11
#define GGA_LAST_UPD 12
#define GGA_STATION_ID 13
static T_GPS_gga currentGga;

// GLL fields
#define GLL_LOCATION_LAT 0
#define GLL_LOCATION_LAT_AZMUTH 1
#define GLL_LOCATION_LON 2
#define GLL_LOCATION_LON_AZMUTH 3
#define GLL_fix_tIME 4
#define GLL_DATA_ACTIVE 5
static T_GPS_gll currentGll;

// GSA fields
#define GSA_AUTO_SELECTION 0
#define GSA_DIM_FIX 1
#define GSA_SAT_1 2
#define GSA_SAT_2 3
#define GSA_SAT_3 4
#define GSA_SAT_4 5
#define GSA_SAT_5 6
#define GSA_SAT_6 7
#define GSA_SAT_7 8
#define GSA_SAT_8 9
#define GSA_SAT_9 10
#define GSA_SAT_10 11
#define GSA_SAT_11 12
#define GSA_SAT_12 13
#define GSA_PDOP 14
#define GSA_HDOP 15
#define GSA_VDOP 16
static T_GPS_gsa currentGsa;

// GSV fields
#define GSV_NUM_SENTENCE 0
#define GSV_SENTENCE 1
#define GSV_NUM_SATS 2
#define GSV_SAT1_PRN 3
#define GSV_ELEVATION1 4
#define GSV_AZIMUTH1 5
#define GSV_SNR1 6
#define GSV_SAT2_PRN 7
#define GSV_ELEVATION2 8
#define GSV_AZIMUTH2 9
#define GSV_SNR2 10
#define GSV_SAT3_PRN 11
#define GSV_ELEVATION3 12
#define GSV_AZIMUTH3 13
#define GSV_SNR3 14
#define GSV_SAT4_PRN 15
#define GSV_ELEVATION4 16
#define GSV_AZIMUTH4 17
#define GSV_SNR4 18
static T_GPS_gsv currentGsv[3];

// RMC fields
#define RMC_FIX 0
#define RMC_STATUS 1
#define RMC_LAT 2
#define RMC_LAT_AZMUTH 3
#define RMC_LON 4
#define RMC_LON_AZMUTH 5
#define RMC_SPEED 6
#define RMC_TRACK 7
#define RMC_DATE 8
#define RMC_MAG 9
#define RMC_MAG_AZMUTH 10
#define RMC_MODE 11
static T_GPS_rmc currentRmc;

// VTG fields
#define VTG_TRACK 0
#define VTG_MAG_TRACK 2
#define VTG_SPEED_KNOTS 4
#define VTG_SPEED_KM 5
static T_GPS_vtg currentVtg;

#ifdef _GPS_DTM
// DTM fields
#define DTM_LOCAL_DATUM 0
#define DTM_LOCAL_SUBCODE 1
#define DTM_LATITUDE_OFFSET 2
#define DTM_LATITUDE_OFFSET_MARK 3
#define DTM_LONGITUDE_OFFSET 4
#define DTM_LONGITUDE_OFFSET_MARK 5
#define DTM_ALTITUDE_OFFSET 6
#define DTM_DATUM 7
static T_GPS_dtm currentDtm;
#endif

#ifdef _GPS_GBS
// GBS fields
#define GBS_UTC 0
#define GBS_LAT_ERROR 1
#define GBS_LON_ERROR 2
#define GBS_ALT_ERROR 3
#define GBS_FAILED_SAT_ID 4
#define GBS_PROB_MISS 5
#define GBS_FAILED_EST 6
#define GBS_STD_DEVIATION 7
static T_GPS_gbs currentGbs;
#endif

#ifdef _GPS_GPQ
static T_GPS_gpq currentGpq;
#endif

#ifdef _GPS_GRS
// GRS fields
#define GRS_UTC 0
#define GRS_MODE 1
#define GRS_RANGE 2
static T_GPS_grs currentGrs;
#endif

#ifdef _GPS_GST
// GST fields
#define GST_UTC 0
#define GST_RMS 1
#define GST_STD_MAJ 2
#define GST_STD_MIN 3
#define GST_ORIENTATION 4
#define GST_STD_LAT 5
#define GST_STD_LON 6
#define GST_STD_ALT 7
static T_GPS_gst currentGst;
#endif

#ifdef _GPS_THS
static T_GPS_ths currentThs;
#endif

#ifdef _GPS_TXT
// TXT fields
#define TXT_TOTAL_PACKAGE 0
#define TXT_MESSAGE_NUM 1
#define TXT_TYPE 2
#define TXT_MESSGE 3
static char txtMessage [MAX_TXT_MESSAGE];
static T_GPS_txt currentTxt[MAX_TXT_PACKAGES];
#endif

#ifdef _GPS_ZDA
// ZDA fields
#define ZDA_TIME 0
#define ZDA_DAY 1
#define ZDA_MONTH 2
#define ZDA_YEAR 3
#define ZDA_LOCAL_HOURS 4
#define ZDA_LOCAL_MINUTES 5
static T_GPS_zda currentZda;
#endif

// buffer used in parsing sentence
typedef struct
{
    int8_t num_of_fields;
    char tokens[ MAX_FIELDS ][ MAX_FIELD_SIZE ];
} T_GPS_fields;


/*                 Private Function Prototypes
 ******************************************************************************/
static char * strcpyPrivate(char *pS1, char *pS2);

static void processGGA (char *pSentence) ;
static void processGLL (char *pSentence) ;
static void processGSA (char *pSentence) ;
static void processGSV (char *pSentence) ;
static void processRMC (char *pSentence) ;
#ifdef _GPS_DTM
static void processDTM (char *pSentence) ;
#endif
#ifdef _GPS_GBS
static void processGBS (char *pSentence) ;
#endif
#ifdef _GPS_GPQ
static void processGPQ (char *pSentence) ;
#endif
#ifdef _GPS_GRS
static void processGRS (char *pSentence) ;
#endif
#ifdef _GPS_GST
static void processGST (char *pSentence) ;
#endif
#ifdef _GPS_THS
static void processTHS (char *pSentence) ;
#endif
#ifdef _GPS_TXT
static void processTXT (char *pSentence) ;
#endif
#ifdef _GPS_VTG
static void processVTG (char *pSentence) ;
#endif
#ifdef _GPS_ZDA
static void processZDA (char *pSentence) ;
#endif

// Router of sentence parsing
/* parses the sentence into fields */
static T_GPS_fields * parseFields (char *pSentence) ;
/* Removes leading 0 and returns float */
static double getNumberFloat (char *pStr) ;
/* Removes leading 0 and returns uint16_t */
static uint16_t getNumber (char *pStr) ;
/* gets the time from string and populates time pointer */
static void getTime (char *pStr, T_GPS_utcTime *pTime) ;
/* gets time as well as date from string and populates pointer */
static void getDate (char *pStr, T_GPS_time *pTime) ;
/* Parses location both degrees, minutes, and azmuth */
static void getLocation (char *pStr, T_GPS_location *pLocation, uint16_t type);
/* for those platforms not found on the MikroC compiler */
static int xtoi (char *pHexstring) ;
/* Utility function to calculate valid sentence */
static bool validateChecksum (char *pSentence) ;
/* Main processing function */
static void processSentence (char *pSentence) ;

/*                 Private Function Definitions
 ******************************************************************************/

/* copy of standard strcpy function used to avoid reentrance in PIC */
static char * strcpyPrivate(char *pS1, char *pS2)
{
    char *s = pS1;
    while ((*s++ = *pS2++) != 0)
        ;
    return (pS1);
}


static void processGGA (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;
    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GGA_fix_tIME:
        {
            if (field (GGA_fix_tIME) )
            {
                currentGga.fixTime = &currentFix;
                getTime (token (GGA_fix_tIME) , currentGga.fixTime) ;
            }
            break;
        }
        case GGA_LAT:
        {
            if (field (GGA_LAT) )
            {
                currentGga.latitude = &currentLatitude;
                getLocation(token (GGA_LAT),currentGga.latitude,LOCATION_LAT);
            }
            break;
        }
        case GGA_LAT_AZMUTH:
        {
            if (field (GGA_LAT_AZMUTH) )
            {
                if (field (GGA_LAT_AZMUTH) == 'N')
                    currentGga.latitude->azmuth = GPS_AZIMUTH_NORTH;
                else if (field (GGA_LAT_AZMUTH) == 'S')
                    currentGga.latitude->azmuth = GPS_AZIMUTH_SOUTH;
                else
                    currentGga.latitude->azmuth = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case GGA_LON:
        {
            if (field (GGA_LON) )
            {
                currentGga.longitude = &currentLongitude;
                getLocation(token (GGA_LON),currentGga.longitude,LOCATION_LON);
            }
            break;
        }
        case GGA_LON_AZMUTH:
        {
            if (field (GGA_LON_AZMUTH) )
            {
                if (field (GGA_LON_AZMUTH) == 'E')
                    currentGga.longitude->azmuth = GPS_AZIMUTH_EAST;
                else if (field (GGA_LON_AZMUTH) == 'W')
                    currentGga.longitude->azmuth = GPS_AZIMUTH_WEST;
                else
                    currentGga.longitude->azmuth = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case GGA_FIX_QUALITY:
        {
            if (field (GGA_FIX_QUALITY) )
                currentGga.fix = getNumber (token (GGA_FIX_QUALITY) ) ;
            break;
        }
        case GGA_NUM_SATS:
        {
            if (field (GGA_NUM_SATS) )
                currentGga.numberOfSats = getNumber (token (GGA_NUM_SATS) ) ;
            break;
        }
        case GGA_HORT_DIL:
        {
            if (field (GGA_HORT_DIL) )
                currentGga.horizontalDilution = 
                getNumberFloat (token (GGA_HORT_DIL) ) ;
            break;
        }
        case GGA_ALT:
        {
            if (field (GGA_ALT) )
                currentGga.altitude = getNumberFloat (token (GGA_ALT) ) ;
            break;
        }
        case GGA_HEIGHT:
        {
            if (field (GGA_HEIGHT) )
                currentGga.height = getNumberFloat (token (GGA_HEIGHT) ) ;
            break;
        }
        case GGA_LAST_UPD:
        {
            if (field (GGA_LAST_UPD) )
                currentGga.lastUpdate = getNumberFloat (token (GGA_LAST_UPD));
            break;
        }
        case GGA_STATION_ID:
        {
            if (field (GGA_STATION_ID) )
                currentGga.stationId = getNumberFloat (token (GGA_STATION_ID));
            break;
        }
        };
    }
    return;
}

static void processGLL (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GLL_LOCATION_LAT:
        {
            if (field (GLL_LOCATION_LAT) )
            {
                currentGll.latitude = &currentLatitude;
                getLocation (token (GLL_LOCATION_LAT) , 
                currentGll.latitude, LOCATION_LAT) ;
            }
            break;
        }
        case GLL_LOCATION_LAT_AZMUTH:
        {
            if (field (GLL_LOCATION_LAT_AZMUTH) )
            {
                if (field (GLL_LOCATION_LAT_AZMUTH) == 'N')
                    currentGll.latitude->azmuth = GPS_AZIMUTH_NORTH;
                else if (field (GLL_LOCATION_LAT_AZMUTH) == 'S')
                    currentGll.latitude->azmuth = GPS_AZIMUTH_SOUTH;
                else
                    currentGll.latitude->azmuth = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case GLL_LOCATION_LON:
        {
            if (field (GLL_LOCATION_LON) )
            {
                currentGll.longitude = &currentLongitude;
                getLocation (token (GLL_LOCATION_LON) , 
                currentGll.longitude, LOCATION_LON) ;
            }
            break;
        }
        case GLL_fix_tIME:
        {
            if (field (GLL_fix_tIME) )
            {
                currentGll.fixTime = &currentFix;
                getTime (token (GLL_fix_tIME) , currentGll.fixTime) ;
            }
            break;
        }
        case GLL_DATA_ACTIVE:
        {
            if (field (GLL_DATA_ACTIVE) )
            {
                if (field (GLL_DATA_ACTIVE) == 'A')
                    currentGll.active = GPS_LORAN_ACTIVE;
                else if (field (GLL_DATA_ACTIVE) == 'V')
                    currentGll.active = GPS_LORAN_VOID;
                else
                    currentGll.active = GPS_LORAN_UNKNOWN;
            }
            break;
        }
        };
    }
}

static void processGSA (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GSA_AUTO_SELECTION:
        {
            if (field (GSA_AUTO_SELECTION) )
            {
                if (field (GSA_AUTO_SELECTION) == 'A')
                    currentGsa.mode = GPS_GSA_AUTO_MODE;
                else if (field (GSA_AUTO_SELECTION) == 'M')
                    currentGsa.mode = GPS_GSA_MANUAL_MODE;
                else
                    currentGsa.mode = GPS_GSA_UNKNOWN;
            }
            break;
        }
        case GSA_DIM_FIX:
        {
            if (field (GSA_DIM_FIX) )
                currentGsa.fix = getNumber (token (GSA_DIM_FIX) ) ;
            break;
        }
        case GSA_SAT_1:
        {
            if (field (GSA_SAT_1) )
                currentGsa.sats[ 0 ] = getNumber (token (GSA_SAT_1) ) ;
            break;
        }
        case GSA_SAT_2:
        {
            if (field (GSA_SAT_2) )
                currentGsa.sats[ 1 ] = getNumber (token (GSA_SAT_2) ) ;
            break;
        }
        case GSA_SAT_3:
        {
            if (field (GSA_SAT_3) )
                currentGsa.sats[ 2 ] = getNumber (token (GSA_SAT_3) ) ;
            break;
        }
        case GSA_SAT_4:
        {
            if (field (GSA_SAT_4) )
                currentGsa.sats[ 3 ] = getNumber (token (GSA_SAT_4) ) ;
            break;
        }
        case GSA_SAT_5:
        {
            if (field (GSA_SAT_5) )
                currentGsa.sats[ 4 ] = getNumber (token (GSA_SAT_5) ) ;
            break;
        }
        case GSA_SAT_6:
        {
            if (field (GSA_SAT_6) )
                currentGsa.sats[ 5 ] = getNumber (token (GSA_SAT_6) ) ;
            break;
        }
        case GSA_SAT_7:
        {
            if (field (GSA_SAT_7) )
                currentGsa.sats[ 6 ] = getNumber (token (GSA_SAT_7) ) ;
            break;
        }
        case GSA_SAT_8:
        {
            if (field (GSA_SAT_8) )
                currentGsa.sats[ 7 ] = getNumber (token (GSA_SAT_8) ) ;
            break;
        }
        case GSA_SAT_9:
        {
            if (field (GSA_SAT_9) )
                currentGsa.sats[ 8 ] = getNumber (token (GSA_SAT_9) ) ;
            break;
        }
        case GSA_SAT_10:
        {
            if (field (GSA_SAT_10) )
                currentGsa.sats[ 9 ] = getNumber (token (GSA_SAT_10) ) ;
            break;
        }
        case GSA_SAT_11:
        {
            if (field (GSA_SAT_11) )
                currentGsa.sats[ 10 ] = getNumber (token (GSA_SAT_11) ) ;
            break;
        }
        case GSA_SAT_12:
        {
            if (field (GSA_SAT_12) )
                currentGsa.sats[ 11 ] = getNumber (token (GSA_SAT_12) ) ;
            break;
        }
        case GSA_PDOP:
        {
            if (field (GSA_PDOP) )
                currentGsa.pdop = getNumberFloat (token (GSA_PDOP) ) ;
            break;
        }
        case GSA_HDOP:
        {
            if (field (GSA_HDOP) )
                currentGsa.hdop = getNumberFloat (token (GSA_HDOP) ) ;
            break;
        }
        case GSA_VDOP:
        {
            if (field (GSA_VDOP) )
                currentGsa.vdop = getNumberFloat (token (GSA_VDOP) ) ;
            break;
        }
        };
    }
    return;
}

static void processGSV (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;
    T_GPS_gsv *cur_sentence = &currentGsv[0];

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GSV_SENTENCE:
        {
            if (field (GSV_SENTENCE) )
            {
                uint8_t tmp_num = getNumber (token (GSV_SENTENCE) ) ;

                if (tmp_num <= 3 && tmp_num >= 1)
                    cur_sentence = &currentGsv[tmp_num - 1];
                else
                    return;
            }
            break;
        }
        case GSV_NUM_SATS:
        {
            if (field (GSV_NUM_SATS) )
                cur_sentence->numberOfSats = 
                getNumber (token (GSV_NUM_SATS)) ;
            break;
        }
        case GSV_SAT1_PRN:
        {
            if (field (GSV_SAT1_PRN))
                cur_sentence->satInfo[0].sattelitePrn = 
                getNumber (token (GSV_SAT1_PRN) ) ;
            break;
        }
        case GSV_ELEVATION1:
        {
            if (field (GSV_ELEVATION1) )
                cur_sentence->satInfo[0].elevation = 
                getNumber (token (GSV_ELEVATION1) ) ;
            break;
        }
        case GSV_AZIMUTH1:
        {
            if (field (GSV_AZIMUTH1) )
                cur_sentence->satInfo[0].azimuth = 
                getNumber (token (GSV_AZIMUTH1) ) ;
            break;
        }
        case GSV_SNR1:
        {
            if (field (GSV_SNR1) )
                cur_sentence->satInfo[0].azimuth = 
                getNumber (token (GSV_SNR1) ) ;
            break;
        }
        case GSV_SAT2_PRN:
        {
            if (field (GSV_SAT2_PRN))
                cur_sentence->satInfo[1].sattelitePrn = 
                getNumber (token (GSV_SAT2_PRN) ) ;
            break;
        }
        case GSV_ELEVATION2:
        {
            if (field (GSV_ELEVATION2) )
                cur_sentence->satInfo[1].elevation = 
                getNumber (token (GSV_ELEVATION2) ) ;
            break;
        }
        case GSV_AZIMUTH2:
        {
            if (field (GSV_AZIMUTH2) )
                cur_sentence->satInfo[1].azimuth = 
                getNumber (token (GSV_AZIMUTH2) ) ;
            break;
        }
        case GSV_SNR2:
        {
            if (field (GSV_SNR2) )
                cur_sentence->satInfo[1].azimuth = 
                getNumber (token (GSV_SNR2) ) ;
            break;
        }
        case GSV_SAT3_PRN:
        {
            if (field (GSV_SAT3_PRN))
                cur_sentence->satInfo[2].sattelitePrn = 
                getNumber (token (GSV_SAT3_PRN) ) ;
            break;
        }
        case GSV_ELEVATION3:
        {
            if (field (GSV_ELEVATION3) )
                cur_sentence->satInfo[2].elevation = 
                getNumber (token (GSV_ELEVATION3) ) ;
            break;
        }
        case GSV_AZIMUTH3:
        {
            if (field (GSV_AZIMUTH3) )
                cur_sentence->satInfo[2].azimuth = 
                getNumber (token (GSV_AZIMUTH3) ) ;
            break;
        }
        case GSV_SNR3:
        {
            if (field (GSV_SNR3) )
                cur_sentence->satInfo[2].azimuth = 
                getNumber (token (GSV_SNR3) ) ;
            break;
        }
        case GSV_SAT4_PRN:
        {
            if (field (GSV_SAT4_PRN))
                cur_sentence->satInfo[3].sattelitePrn = 
                getNumber (token (GSV_SAT4_PRN) ) ;
            break;
        }
        case GSV_ELEVATION4:
        {
            if (field (GSV_ELEVATION4) )
                cur_sentence->satInfo[3].elevation = 
                getNumber (token (GSV_ELEVATION4) ) ;
            break;
        }
        case GSV_AZIMUTH4:
        {
            if (field (GSV_AZIMUTH4) )
                cur_sentence->satInfo[3].azimuth = 
                getNumber (token (GSV_AZIMUTH4) ) ;
            break;
        }
        case GSV_SNR4:
        {
            if (field (GSV_SNR4) )
                cur_sentence->satInfo[3].azimuth = 
                getNumber (token (GSV_SNR4) ) ;
            break;
        }
        };
    }
    return;
}


static void processRMC (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case RMC_FIX:
        {
            if (field (RMC_FIX) )
            {
                currentRmc.fixTime = &currentFix;
                getTime (token (RMC_FIX) , currentRmc.fixTime) ;
            }
            break;
        }
        case RMC_STATUS:
        {
            if (field (RMC_STATUS) )
            {
                if (field (RMC_STATUS) == 'A')
                    currentRmc.status = GPS_RMC_ACTIVE;
                else if (field (RMC_STATUS) == 'V')
                    currentRmc.status = GPS_RMC_VOID;
                else
                    currentRmc.status = GPS_RMC_UKNOWN;
            }
            break;
        }
        case RMC_LAT:
        {
            if (field (RMC_LAT) )
            {
                currentRmc.latitude = &currentLatitude;
                getLocation (token (RMC_LAT),currentRmc.latitude,LOCATION_LAT);
            }
            break;
        }
        case RMC_LAT_AZMUTH:
        {
            if (field (RMC_LAT_AZMUTH) )
            {
                if (field (RMC_LAT_AZMUTH) == 'N')
                    currentRmc.latitude->azmuth = GPS_AZIMUTH_NORTH;
                else if (field (RMC_LAT_AZMUTH) == 'S')
                    currentRmc.latitude->azmuth = GPS_AZIMUTH_SOUTH;
                else
                    currentRmc.latitude->azmuth = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case RMC_LON:
        {
            if (field (RMC_LON) )
            {
                currentRmc.longitude = &currentLongitude;
                getLocation(token (RMC_LON),currentRmc.longitude,LOCATION_LON);
            }
            break;
        }
        case RMC_LON_AZMUTH:
        {
            if (field (RMC_LON_AZMUTH) )
            {
                if (field (RMC_LON_AZMUTH) == 'W')
                    currentRmc.longitude->azmuth = GPS_AZIMUTH_WEST;
                else if (field (RMC_LON_AZMUTH) == 'E')
                    currentRmc.longitude->azmuth = GPS_AZIMUTH_EAST;
                else
                    currentRmc.longitude->azmuth = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case RMC_SPEED:
        {
            if (field (RMC_SPEED) )
                currentRmc.speed = getNumberFloat (token (RMC_SPEED) ) ;
            break;
        }
        case RMC_TRACK:
        {
            if (field (RMC_TRACK) )
                currentRmc.track = getNumberFloat (token (RMC_TRACK) ) ;
            break;
        }
        case RMC_DATE:
        {
            if (field (RMC_DATE) )
            {
                currentRmc.date = &currentTime;
                getDate (token (RMC_DATE) , currentRmc.date) ;
            }
            break;
        }
        case RMC_MAG:
        {
            if (field (RMC_MAG) )
                currentRmc.magnetic.magneticVariation = 
                getNumberFloat (token (RMC_MAG) ) ;
            break;
        }
        case RMC_MAG_AZMUTH:
        {
            if (field (RMC_MAG_AZMUTH) )
            {
                if (field (RMC_MAG_AZMUTH) == 'N')
                    currentRmc.magnetic.azmuth = GPS_AZIMUTH_NORTH;
                else if (field (RMC_MAG_AZMUTH) == 'S')
                    currentRmc.magnetic.azmuth = GPS_AZIMUTH_SOUTH;
                else if (field (RMC_MAG_AZMUTH) == 'W')
                    currentRmc.magnetic.azmuth = GPS_AZIMUTH_WEST;
                else if (field (RMC_MAG_AZMUTH) == 'E')
                    currentRmc.magnetic.azmuth = GPS_AZIMUTH_EAST;
                else
                    currentRmc.magnetic.azmuth = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        };
    }
    return;
}

static void processVTG (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;
    
    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case VTG_TRACK:
        {
            if (field (VTG_TRACK) )
                currentVtg.track = getNumberFloat (token (VTG_TRACK) ) ;
            break;
        }
        case VTG_MAG_TRACK:
        {
            if (field (VTG_MAG_TRACK) )
                currentVtg.track = getNumberFloat (token (VTG_MAG_TRACK) ) ;
            break;
        }
        case VTG_SPEED_KNOTS:
        {
            if (field (VTG_SPEED_KNOTS) )
                currentVtg.track = getNumberFloat (token (VTG_SPEED_KNOTS) ) ;
            break;
        }
        case VTG_SPEED_KM:
        {
            if (field (VTG_SPEED_KM) )
                currentVtg.track = getNumberFloat (token (VTG_SPEED_KM) ) ;
            break;
        }
        };
    }
    return;
}

#ifdef _GPS_DTM
static void processDTM (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case DTM_LOCAL_DATUM:
        {
            // Local datum code
            if (field (DTM_LOCAL_DATUM) )
            {
                if (!strcmp (token (DTM_LOCAL_DATUM) , "W84") )
                    currentDtm.localDatum = GPS_DTM_WGS84;
                else if (!strcmp (token (DTM_LOCAL_DATUM) , "W72") )
                    currentDtm.localDatum = GPS_DTM_WGS72;
                else if (!strcmp (token (DTM_LOCAL_DATUM) , "S85") )
                    currentDtm.localDatum = GPS_DTM_SGS85;
                else if (!strcmp (token (DTM_LOCAL_DATUM) , "P90") )
                    currentDtm.localDatum = GPS_DTM_PE90;
                else if (!strcmp (token (DTM_LOCAL_DATUM) , "999") )
                    currentDtm.localDatum = GPS_DTM_USER_DEFINED;
                else if (!strcmp (token (DTM_LOCAL_DATUM) , "GPS_DTM_IHO") )
                    currentDtm.localDatum = GPS_DTM_IHO;
            }
            break;
        }
        case DTM_LOCAL_SUBCODE:
        {
            // Local datum sub-code
            if (field (DTM_LOCAL_SUBCODE) )
                memcpy (currentDtm.lsd, token (DTM_LOCAL_SUBCODE) , 1) ;
            break;
        }
        case DTM_LATITUDE_OFFSET:
        {
            // Offset in latitude in minutes
            if (field (DTM_LATITUDE_OFFSET) )
                currentDtm.latitude = 
                getNumberFloat (token (DTM_LATITUDE_OFFSET) ) ;
            break;
        }
        case DTM_LATITUDE_OFFSET_MARK:
        {
            // North South Indication
            if (field (DTM_LATITUDE_OFFSET_MARK) )
            {
                if (field (DTM_LATITUDE_OFFSET_MARK) == 'N')
                    currentDtm.latitudeOffsetDirection = GPS_AZIMUTH_NORTH;
                else if (field (DTM_LATITUDE_OFFSET_MARK) == 'S')
                    currentDtm.latitudeOffsetDirection = GPS_AZIMUTH_SOUTH;
                else
                    currentDtm.latitudeOffsetDirection = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case DTM_LONGITUDE_OFFSET:
        {
            if (field (DTM_LONGITUDE_OFFSET) )
                currentDtm.longitude = 
                getNumberFloat (token (DTM_LONGITUDE_OFFSET) ) ;
            break;
        }
        case DTM_LONGITUDE_OFFSET_MARK:
        {
            if (field (DTM_LONGITUDE_OFFSET_MARK) )
            {
                if (field (DTM_LONGITUDE_OFFSET_MARK) == 'E')
                    currentDtm.longitudeOffsetDirection = GPS_AZIMUTH_EAST;
                else if (field (DTM_LONGITUDE_OFFSET_MARK) == 'W')
                    currentDtm.longitudeOffsetDirection = GPS_AZIMUTH_WEST;
                else
                    currentDtm.longitudeOffsetDirection = GPS_AZIMUTH_UNKNOWN;
            }
            break;
        }
        case DTM_ALTITUDE_OFFSET:
        {
            if (field (DTM_ALTITUDE_OFFSET) != '\0')
                currentDtm.altitude = 
                getNumberFloat (token (DTM_ALTITUDE_OFFSET) ) ;
            break;
        }
        case DTM_DATUM:
        {
            // Local datum code
            if (field (DTM_DATUM) )
            {
                if (!strcmp (token (DTM_DATUM) , "W84") )
                    currentDtm.datum = GPS_DTM_WGS84;
                else if (!strcmp (token (DTM_DATUM) , "W72") )
                    currentDtm.datum = GPS_DTM_WGS72;
                else if (!strcmp (token (DTM_DATUM) , "S85") )
                    currentDtm.datum = GPS_DTM_SGS85;
                else if (!strcmp (token (DTM_DATUM) , "P90") )
                    currentDtm.datum = GPS_DTM_PE90;
                else if (!strcmp (token (DTM_DATUM) , "999") )
                    currentDtm.datum = GPS_DTM_USER_DEFINED;
                else if (!strcmp (token (DTM_DATUM) , "GPS_DTM_IHO") )
                    currentDtm.datum = GPS_DTM_IHO;
                else
                    currentDtm.datum = GPS_DTM_UNKNOWN;
            }
            break;
        }
        };
    }
    return;
}
#endif

#ifdef _GPS_GBS
static void processGBS (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;
    
    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GBS_UTC:
        {
            if (field (GBS_UTC) )
            {
                currentGbs.fixTime = &currentFix;
                getTime (token (GBS_UTC) , currentGbs.fixTime) ;
            }
            break;
        }
        case GBS_LAT_ERROR:
        {
            if (field (GBS_LAT_ERROR) )
                currentGbs.latitudeError = 
                getNumberFloat(token (GBS_LAT_ERROR));
            break;
        }
        case GBS_LON_ERROR:
        {
            if (field (GBS_LON_ERROR) )
                currentGbs.longitudeError = 
                getNumberFloat (token (GBS_LON_ERROR) ) ;
            break;
        }
        case GBS_ALT_ERROR:
        {
            if (field (GBS_ALT_ERROR) )
                currentGbs.altitudeError = 
                getNumberFloat (token (GBS_ALT_ERROR) ) ;
            break;
        }
        case GBS_FAILED_SAT_ID:
        {
            if (field (GBS_FAILED_SAT_ID) )
                currentGbs.satteliteID = 
                getNumber (token (GBS_FAILED_SAT_ID) ) ;
            break;
        }
        case GBS_PROB_MISS:
        {
            if (field (GBS_PROB_MISS) )
                currentGbs.probabilityOfMiss = 
                getNumberFloat (token (GBS_PROB_MISS) ) ;
            break;
        }
        case GBS_FAILED_EST:
        {
            if (field (GBS_FAILED_EST) )
                currentGbs.failedEstimation = 
                getNumberFloat (token (GBS_FAILED_EST) ) ;
            break;
        }
        case GBS_STD_DEVIATION:
        {
            if (field (GBS_STD_DEVIATION) )
                currentGbs.standardDeviation = 
                getNumberFloat (token (GBS_STD_DEVIATION) ) ;
            break;
        }
        };
    }
}
#endif

#ifdef _GPS_GPQ
static void processGPQ (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;

    if (fields->tokens[0][0] != '\0')
        strcpy (currentGpq.id, fields->tokens[0]) ;
    return;
}
#endif

#ifdef _GPS_GRS
static void processGRS (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GRS_UTC:
        {
            if (field (GRS_UTC) )
            {
                currentGrs.fixTime = &currentFix;
                getTime (token (GRS_UTC) , currentGrs.fixTime) ;
            }
            break;
        }
        case GRS_MODE:
        {
            if (field (GRS_MODE) )
                currentGrs.mode = getNumber (token (GRS_MODE) ) ;
            break;
        }
        case GRS_RANGE:
        {
            if (field (GRS_RANGE) )
                currentGrs.range = getNumberFloat (token (GRS_RANGE) ) ;
            break;
        }
        }
    }
    return;
}
#endif

#ifdef _GPS_GST
static void processGST (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case GST_UTC:
        {
            if (field (GST_UTC) )
            {
                currentGst.fixTime = &currentFix;
                getTime (token (GST_UTC) , currentGst.fixTime) ;
            }
            break;
        }
        case GST_RMS:
        {
            if (field (GST_RMS) )
                currentGst.rms = getNumberFloat (token (GST_RMS) ) ;
            break;
        }
        case GST_STD_MAJ:
        {
            if (field (GST_STD_MAJ) )
                currentGst.rms = getNumberFloat (token (GST_STD_MAJ) ) ;
            break;
        }
        case GST_STD_MIN:
        {
            if (field (GST_STD_MIN) )
                currentGst.rms = getNumberFloat (token (GST_STD_MIN) ) ;
            break;
        }
        case GST_ORIENTATION:
        {
            if (field (GST_ORIENTATION) )
                currentGst.rms = getNumberFloat (token (GST_ORIENTATION) ) ;
            break;
        }
        case GST_STD_LAT:
        {
            if (field (GST_STD_LAT) )
                currentGst.rms = getNumberFloat (token (GST_STD_LAT) ) ;
            break;
        }
        case GST_STD_LON:
        {
            if (field (GST_STD_LON) )
                currentGst.rms = getNumberFloat (token (GST_STD_LON) ) ;
            break;
        }
        case GST_STD_ALT:
        {
            if (field (GST_STD_ALT) )
                currentGst.rms = getNumberFloat (token (GST_STD_ALT) ) ;
            break;
        }
        };
    }
    return;
}
#endif

#ifdef _GPS_THS
static void processTHS (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;

    if (fields->tokens[ 0 ][ 0 ] != '\0')
        currentThs.heading = getNumberFloat (fields->tokens[ 0 ]) ;

    if (fields->tokens[ 1 ][ 0 ] != '\0')
    {
        if (fields->tokens[ 1 ][ 0 ] == 'A')
            currentThs.status = GPS_VEHICLE_AUTONOMOUS;
        else if (fields->tokens[ 1 ][ 0 ] == 'E')
            currentThs.status = GPS_VEHICLE_ESTIMATED;
        else if (fields->tokens[ 1 ][ 0 ] == 'M')
            currentThs.status = GPS_VEHICLE_MANUAL;
        else if (fields->tokens[ 1 ][ 0 ] == 'S')
            currentThs.status = GPS_VEHICLE_SIMULATOR;
        else if (fields->tokens[ 1 ][ 0 ] == 'V')
            currentThs.status = GPS_VEHICLE_NOT_VALID;
        else
            currentThs.status = GPS_VEHICLE_UKNOWN;
    }

    return;
}
#endif

#ifdef _GPS_TXT
static void processTXT (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;
    T_GPS_txt *tmptxt = &currentTxt[0];

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
            case TXT_TOTAL_PACKAGE:
            {
                if (field (TXT_TOTAL_PACKAGE) )
                    tmptxt->numberOfMessages = 
                    getNumber (token (TXT_TOTAL_PACKAGE) ) ;
                break;
            }
            case TXT_MESSAGE_NUM:
            {
                if (field (TXT_MESSAGE_NUM) )
                {
                    uint8_t tmpnum = getNumber (token (TXT_MESSAGE_NUM)) ;

                    if (tmpnum <= MAX_TXT_PACKAGES)
                    {
                        tmptxt = &currentTxt[ tmpnum -1 ];
                    }
                }
                break;
            }
            case TXT_TYPE:
            {
                if (field (TXT_TYPE) )
                    tmptxt->messageType = getNumber (token (TXT_TYPE) ) ;
                break;
            }
            case TXT_MESSGE:
            {
                if (field (TXT_MESSGE) )
                    strcpy (tmptxt->message, token (TXT_MESSGE) ) ;
                break;
            }
        };
    }

    return;
}
#endif

#ifdef _GPS_ZDA
static void processZDA (char *pSentence)
{
    T_GPS_fields *fields = parseFields (pSentence) ;
    uint16_t i;

    currentZda.time = &currentTime;

    for (i = 0; i < fields->num_of_fields; i++)
    {
        switch (i)
        {
        case ZDA_TIME:
        {
            if (field (ZDA_TIME) )
            {
                T_GPS_utcTime tmp_time;
                getTime (token (ZDA_TIME) , &tmp_time) ;
                currentZda.time->hh = tmp_time.hour;
                currentZda.time->mn = tmp_time.minute;
                currentZda.time->ss = tmp_time.second;
            }
            break;
        }
        case ZDA_DAY:
        {
            if (field (ZDA_DAY) )
                currentZda.time->md = getNumber (token (ZDA_DAY));
            break;
        }
        case ZDA_MONTH:
        {
            if (field (ZDA_MONTH) )
                currentZda.time->mo = getNumber (token (ZDA_MONTH));
            break;
        }
        case ZDA_YEAR:
        {
            if (field (ZDA_YEAR) )
                currentZda.time->yy = getNumber (token (ZDA_YEAR));
            break;
        }
        case ZDA_LOCAL_HOURS:
        {
            if (field (ZDA_LOCAL_HOURS) )
                currentZda.localHour = getNumber (token (ZDA_LOCAL_HOURS));
            break;
        }
        case ZDA_LOCAL_MINUTES:
        {
            if (field (ZDA_LOCAL_MINUTES) )
                currentZda.localMinute = getNumber (token (ZDA_LOCAL_MINUTES));
            break;
        }
        };
    }
    return;
}
#endif


static T_GPS_fields * parseFields (char *pSentence)
{
    static T_GPS_fields tmp_fields;
    char *p_sentence = pSentence;
    char *p_next = strchr (p_sentence, '*') ;

    tmp_fields.num_of_fields = 0;
    memset (&tmp_fields, 0, sizeof (T_GPS_fields) ) ;

    *p_next = '\0'; // Replace start of checksum with null
    /* Moves us to the first comma, which is just past the identifier */
    p_sentence = strchr (p_sentence, ',') ;

    do
    {
        p_sentence++;
        /* Gets the next comma, so we can calculate the number of bytes to copy */
        p_next = strchr (p_sentence, ',') ;

        if (p_next != 0)
            memcpy (tmp_fields.tokens[tmp_fields.num_of_fields++],
            p_sentence, p_next - p_sentence) ;
        else
            strcpy (tmp_fields.tokens[tmp_fields.num_of_fields++], p_sentence);

        p_sentence = p_next;
    }
    while (p_sentence != 0) ;

    return &tmp_fields;
}


static double getNumberFloat (char *pStr)
{
    uint16_t n;
    double num;
    char *tmp = pStr;

    if ( (n = strspn (tmp, "0") ) != 0 && tmp[n] != '\0')
        num = atof (&tmp[n]) ;
    else
        num = atof (tmp) ;

    return num;
}

static uint16_t getNumber (char *pStr)
{
    uint16_t n;
    uint16_t num;
    char *tmp = pStr;

    if ( (n = strspn (tmp, "0") ) != 0 && tmp[n] != '\0')
        num = atoi (&tmp[n]) ;
    else
        num = atoi (tmp) ;

    return num;
}

static void getTime (char *pStr, T_GPS_utcTime *pTime)
{
    char tmp[4] = {0};
    char *p_tmp = pStr;
    
    uint16_t i;
    uint16_t runcount;
    void *tmp_time =  (void*) pTime;

    if (strchr (pStr, '.') )
        runcount = 4;
    else
        runcount = 3;

    for (i = 0; i < runcount; i++)
    {
        if (*p_tmp == '.')
        {
            p_tmp++;
            strncpy (tmp, p_tmp, 3) ;
            tmp[3] = 0;
        }
        else
        {
            strncpy (tmp, p_tmp, 2) ;
            tmp[2] = 0;
        }

        * (uint8_t*) tmp_time = getNumber (tmp) ;

        p_tmp += 2;

         (uint8_t*) tmp_time++;
    }

    return;
}

static void getDate (char *pStr, T_GPS_time *pTime)
{
    char tmp[3] = {0};
    char *p_str = pStr;;

    strncpy (tmp, p_str, 2) ;
    pTime->md = getNumber (tmp) ;
    p_str += 2;
    strncpy (tmp, p_str, 2) ;
    pTime->mo = getNumber (tmp) ;
    p_str += 2;
    strncpy (tmp, p_str, 2) ;
    pTime->yy = 2000 + getNumber (tmp) ;
    
    return;
}

static void getLocation (char *pStr, T_GPS_location *pLocation, uint16_t type)
{
    if (pLocation != 0)
    {
        char tmp[10] = {0};
        char *p_tmp = pStr;

        if (type == LOCATION_LAT)
        {
            strncpy (tmp, p_tmp, 2) ;
            p_tmp += 2;
        }
        else
        {
            strncpy (tmp, p_tmp, 3) ;
            p_tmp += 3;
        }

        pLocation->degrees = getNumber (tmp) ;
        strcpy (tmp, p_tmp) ;
        pLocation->minutes = getNumberFloat (tmp) ;
    }

    return;
}

// Only needed on platforms other than mikroC
#ifdef ON_PC
static int xtoi (char *pHexstring)
{
    uint16_t i;
    i = 0;
    if ( (*pHexstring == '0') && (* (pHexstring + 1) == 'x'))
        pHexstring += 2;
    
    while (*pHexstring)
    {
        char c = toupper (*pHexstring++) ;

        if ((c < '0') ||  (c > 'F') || ( (c > '9') &&  (c < 'A')))
            break;

        c -= '0';

        if (c > 9)
            c -= 7;
        i =  (i << 4) + c;
    }

    return i;
}
#endif

// Check checksum of incoming sentences
static bool validateChecksum (char *pSentence)
{
    bool flagValid;
    flagValid = true;

    if (pSentence[ 0 ] != '$')
    {
        flagValid = false;
    }

    // if we are still good, test all bytes
    if (flagValid == true)
    {
        uint8_t position = 1;
        uint8_t chksum;
        uint8_t nmeaChk;
        char current_char;
        char hx[5] = "0x00";

        current_char = pSentence[position++]; // get first chr
        chksum = current_char;

        while ( (current_char != '*') &&  (position < BUFFER_MAX) )
        {
            current_char = pSentence[ position ]; // get next chr

            if (current_char != '*')
            {
                chksum = chksum ^ current_char;
            }

            position++;
        }

        // at this point we are either at * or at end of string
        #ifdef ON_PC
        hx[2] = pSentence[ position ];
        hx[3] = pSentence[ position + 1 ];
        hx[4] = '\0';
        #else
        hx[0] = pSentence[ position ];
        hx[1] = pSentence[ position + 1 ];
        hx[2] = '\0';
        #endif

        nmeaChk = xtoi (hx) ;


        if (chksum != nmeaChk)
        {
            flagValid = false;
        }

    }

    return flagValid;
}

// Router for incoming complete sentences
static void processSentence (char *pSentence)
{
#define MAX_COMPARE 6
    char *processSentence = pSentence;

    if (!validateChecksum (processSentence) )
        return;

    if (!strncmp (pSentence, "$GPGGA", MAX_COMPARE) ||
            !strncmp (pSentence, "$GNGGA", MAX_COMPARE) )
        processGGA (processSentence) ;
    else if (!strncmp (pSentence, "$GPGLL", MAX_COMPARE) ||
                 !strncmp (pSentence, "$GNGLL", MAX_COMPARE) )
        processGLL (processSentence) ;
    else if (!strncmp (pSentence, "$GPGSA", MAX_COMPARE) ||
                 !strncmp (pSentence, "$GNGSA", MAX_COMPARE) )
        processGSA (processSentence) ;
    else if (!strncmp (pSentence, "$GPGSV", MAX_COMPARE) ||
                 !strncmp (pSentence, "$GNGSV", MAX_COMPARE) )
        processGSV (processSentence) ;
    else if (!strncmp (pSentence, "$GPRMC", MAX_COMPARE) ||
                 !strncmp (pSentence, "$GNRMC", MAX_COMPARE) )
        processRMC (processSentence) ;
    else if (!strncmp (pSentence, "$GPVTG", MAX_COMPARE) ||
                 !strncmp (pSentence, "$GNVTG", MAX_COMPARE) )
        processVTG (processSentence) ;
#ifdef _GPS_DTM
    else if (!strncmp (pSentence, "$GPDTM", MAX_COMPARE) )
        processDTM (processSentence) ;
#endif
#ifdef _GPS_GBS
    else if (!strncmp (pSentence, "$GPGBS", MAX_COMPARE) )
        processGBS (processSentence) ;
#endif
#ifdef _GPS_GPQ
    else if (!strncmp (pSentence, "$GPGPQ", MAX_COMPARE) )
        processGPQ (processSentence) ;
#endif
#ifdef _GPS_GRS
    else if (!strncmp (pSentence, "$GPGRS", MAX_COMPARE) )
        processGRS (processSentence) ;
#endif
#ifdef _GPS_GST
    else if (!strncmp (pSentence, "$GPGST", MAX_COMPARE) )
        processGST (processSentence) ;
#endif
#ifdef _GPS_THS
    else if (!strncmp (pSentence, "$GPTHS", MAX_COMPARE) )
        processTHS (processSentence) ;
#endif
#ifdef _GPS_TXT
    else if (!strncmp (pSentence, "$GPTXT", MAX_COMPARE) )
        processTXT (processSentence) ;
#endif
#ifdef _GPS_ZDA
    else if (!strncmp (pSentence, "$GPZDA", MAX_COMPARE) )
        processZDA (processSentence) ;
#endif
    return;
}



/*                Public Function Definitions
 ******************************************************************************/
void GPS_put (char input)
{
    static bool sentence_flag;

    if ( (input != '\r' && input != '\n')  && bufferPosition < BUFFER_MAX)
    {
        bufferSentence[ bufferPosition++ ] = input;
    }
    else if (input == '\r')
    {
        sentence_flag = true;
    }
    else if (input == '\n' && sentence_flag)
    {
        bufferSentence[ bufferPosition ] = '\0';
        bufferPosition = 0;
        strcpyPrivate (processBuffer, bufferSentence) ;
        sentence_flag = false;
        processFlag = true;
    }
    else
    {
        bufferPosition = 0; /* invalid something or other */
    }
}

void GPS_parse()
{
    if (processFlag)
    {
        processSentence (processBuffer) ;
        processFlag = false;
    }
    return;
}

void GPS_init()
{
    currentLatitude.degrees = 0;
    currentLatitude.minutes = 0;
    currentLatitude.azmuth = 0;
    currentLongitude.degrees = 0;
    currentLongitude.minutes = 0;
    currentLongitude.azmuth = 0;
    
    currentTime.ss = 0;
    currentTime.mn = 0;
    currentTime.hh = 0;
    currentTime.md = 0;
    currentTime.wd = 0;
    currentTime.mo = 0;
    currentTime.yy = 0;
    currentFix.hour = 0;
    currentFix.second = 0;
    currentFix.minute = 0;
    currentFix.ms = 0;
    
    
    currentGga.fix = 0;
    currentGga.numberOfSats = 0;
    currentGga.horizontalDilution = 0;
    currentGga.altitude = 0;
    currentGga.height = 0;
    currentGga.lastUpdate = 0;
    currentGga.stationId = 0;
    
    currentGll.active = 0;
    
    currentGsa.mode = 0;
    currentGsa.fix = 0;
    memset(currentGsa.sats, 0, 0);
    currentGsa.pdop = 0;
    currentGsa.hdop = 0;
    currentGsa.vdop = 0;

    memset(currentGsv, 0, 0);

    currentRmc.status = 0;
    currentRmc.speed = 0;
    currentRmc.track = 0;
    currentRmc.magnetic.magneticVariation = 0;
    currentRmc.magnetic.azmuth = 0;
    currentRmc.mode = 0;

    currentVtg.track = 0;
    currentVtg.magneticTrack = 0;
    currentVtg.speedKnots = 0;
    currentVtg.speedKm = 0;

#ifdef _GPS_DTM
    currentDtm.localDatum = 0;
    memset(currentDtm.lsd, 0, 0);
    currentDtm.latitude = 0;
    currentDtm.latitudeOffsetDirection = 0;
    currentDtm.longitude = 0;
    currentDtm.longitudeOffsetDirection = 0;
    currentDtm.altitude = 0;
    currentDtm.datum = 0;
#endif
#ifdef _GPS_GBS
    currentGbs.latitudeError = 0;
    currentGbs.longitudeError = 0;
    currentGbs.altitudeError = 0;
    currentGbs.satteliteID = 0;
    currentGbs.probabilityOfMiss = 0;
    currentGbs.failedEstimation = 0;
    currentGbs.standardDeviation = 0;
#endif
#ifdef _GPS_GPQ
    memset(currentGpq.id, 0, 0);
#endif
#ifdef _GPS_GRS
    currentGrs.mode = 0;
    currentGrs.range = 0;
#endif
#ifdef _GPS_GST
    currentGst.rms = 0;
    currentGst.standardDeviationMajor = 0;
    currentGst.standardDeviationMinor = 0;
    currentGst.orientation = 0;
    currentGst.standardDeviationLatitude = 0;
    currentGst.standardDeviationLongitude = 0;
    currentGst.standardDeviationAltitude = 0;
#endif
#ifdef _GPS_THS
    currentThs.heading = 0;
    currentThs.status = 0;
#endif
}

/*
 * Converts longitude or latitude from Degrees, Minutes format to
 * Degrees, Decimal degrees format, which is also commonly used,
 * and is convenient for displaying coordinates as one number.
 */
double GPS_convertToDecimalDegrees  (uint8_t degrees, double minutes)
{
    return degrees + 0.0166666*minutes;
}

/***************** Common ***************/

T_GPS_location * GPS_getLongitude()
{
    return &currentLongitude;
}

T_GPS_location * GPS_getLatitude()
{
    return &currentLatitude;
}

T_GPS_time * GPS_getTime()
{
    return &currentTime;
}

T_GPS_utcTime * GPS_getFix()
{
    return &currentFix;
}

/****************** GGA ******************/
T_GPS_fix GPS_getGgaFixQuality()
{
    return currentGga.fix;
}

uint8_t GPS_getGgaSatCount()
{
    return currentGga.numberOfSats;
}

float GPS_getGgaHorizontalDilution()
{
    return currentGga.horizontalDilution;
}

double GPS_getGgaAltitude()
{
    return currentGga.altitude;
}

double GPS_getGgaMsl()
{
    return currentGga.height;
}

uint16_t GPS_getGgaLastUpdateDGPS()
{
    return currentGga.lastUpdate;
}

uint16_t GPS_getGgaStationID()
{
    return currentGga.stationId;
}

/***************** GLL ******************/
T_GPS_loran GPS_getGllActive()
{
    return currentGll.active;
}

/***************** GSA ******************/
T_GPS_gsaMode GPS_getGsaMode()
{
    return currentGsa.mode;
}

T_GPS_gsaMode GPS_getGsaFixType()
{
    return currentGsa.fix;
}

uint8_t *GPS_getGsaSatPrns()
{
    return currentGsa.sats;
}

float GPS_getGsaPrecisionDilution()
{
    return currentGsa.pdop;
}

float GPS_getGsaHorizontalDilution()
{
    return currentGsa.hdop;
}

float GPS_getGsaVerticalDilution()
{
    return currentGsa.vdop;
}

/***************** GSV *****************/
uint8_t GPS_getGsvSatCount()
{
    return currentGsv[0].numberOfSats;
}

T_GPS_gsvSattelites *GPS_getGsvSats()
{
    T_GPS_gsvSattelites returnValues [12];

    returnValues [0] = currentGsv[0].satInfo[0];
    returnValues [1] = currentGsv[0].satInfo[1];
    returnValues [2] = currentGsv[0].satInfo[2];
    returnValues [3] = currentGsv[0].satInfo[3];
    
    returnValues [4] = currentGsv[1].satInfo[0];
    returnValues [5] = currentGsv[1].satInfo[1];
    returnValues [6] = currentGsv[1].satInfo[2];
    returnValues [7] = currentGsv[1].satInfo[3];
    
    returnValues [8] = currentGsv[2].satInfo[0];
    returnValues [9] = currentGsv[2].satInfo[1];
    returnValues [10] = currentGsv[2].satInfo[2];
    returnValues [11] = currentGsv[2].satInfo[3];
    
    return returnValues;
}


/***************** RMC *****************/
T_GPS_status GPS_getRmcStatus()
{
    return currentRmc.status;
}

double GPS_getRmcSpeed()
{
    return currentRmc.speed;
}

double GPS_getRmcTrack()
{
    return currentRmc.track;
}

double GPS_getRmcMagneticVariation()
{
    return currentRmc.magnetic.magneticVariation;
}

T_GPS_azimuth GPS_getRmcDirection()
{
    return currentRmc.magnetic.azmuth;
}

T_GPS_status GPS_getRmcMode()
{
    return currentRmc.mode;
}

/**************** VTG *****************/
double GPS_getVtgTrack()
{
    return currentVtg.track;
}

double GPS_getVtgMagneticTrack()
{
    return currentVtg.magneticTrack;
}

double GPS_getVtgSpeedKnots()
{
    return currentVtg.speedKnots;
}

double GPS_getVtgSpeedKmh()
{
    return currentVtg.speedKm;
}

#ifdef _GPS_DTM
T_GPS_datumCode GPS_getDtmLocal()
{
    return currentDtm.localDatum;
}

char *GPS_getDtmLocalOffset()
{
    return currentDtm.lsd;
}

double GPS_getDtmLatitudeOffset()
{
    return currentDtm.latitude;
}

T_GPS_azimuth GPS_getDtmLatitudeOffsetDirection()
{
    return currentDtm.latitudeOffsetDirection;
}

double GPS_getDtmLongitudeOffset()
{
    return currentDtm.longitude;
}

T_GPS_azimuth GPS_getDtmLongitudeOffsetDirection()
{
    return currentDtm.longitudeOffsetDirection;
}

double GPS_getDtmAltitudeOffset()
{
    return currentDtm.altitude;
}

T_GPS_datumCode GPS_getDtmDatum()
{
    return currentDtm.datum;
}
#endif


#ifdef _GPS_GBS
float GPS_getGbsLatitudeError()
{
    return currentGbs.latitudeError;
}

float GPS_getGbsLongitudeError()
{
    return currentGbs.longitudeError;
}

float GPS_getGbsAltitudeError()
{
    return currentGbs.altitudeError;
}

uint8_t GPS_getGbsSateliteId()
{
    return currentGbs.satteliteID;
}

float GPS_getGbsMissProbability()
{
    return currentGbs.probabilityOfMiss;
}

double GPS_getGbsFailedEstimation()
{
    return currentGbs.failedEstimation;
}

float GPS_getGbsStandardDeviation()
{
    return currentGbs.standardDeviation;
}
#endif

#ifdef _GPS_GPQ
char *GPS_getGpqMessage()
{
    return currentGpq.id;
}

#endif

#ifdef _GPS_GRS
uint8_t GPS_getGrsMode()
{
    return currentGrs.mode;
}

float GPS_getGrsRange()
{
    return currentGrs.range;
}
#endif

#ifdef _GPS_GST
float GPS_getGstRms()
{
    return currentGst.rms;
}

float GPS_getGstStandardDeviationMajor()
{
    return currentGst.standardDeviationMajor;
}

float GPS_getGstStandardDeviationMinor()
{
    return currentGst.standardDeviationMinor;
}

float GPS_getGstOrientation()
{
    return currentGst.orientation;
}

float GPS_getGstStandardDeviationLatitude()
{
    return currentGst.standardDeviationLatitude;
}

float GPS_getGstStandardDeviationLongitude()
{
    return currentGst.standardDeviationLongitude;
}

float GPS_getGstStandardDeviationAltitude()
{
    return currentGst.standardDeviationAltitude;
}
#endif

#ifdef _GPS_THS
double GPS_getThsHeading()
{
    return currentThs.heading;
}

T_GPS_vehicleStatus GPS_getThsStatus()
{
    return currentThs.status;
}

#endif

#ifdef _GPS_TXT
// TODO
#endif

#ifdef _GPS_ZDA
// TODO
#endif

/*------------------------------------------------------------------------------

  __GPS_parser.c

  Copyright (c) 2011-2017 MikroElektronika.  All right reserved.

    This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.

------------------------------------------------------------------------------*/