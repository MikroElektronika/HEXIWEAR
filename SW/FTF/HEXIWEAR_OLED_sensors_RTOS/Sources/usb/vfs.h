#ifndef	_VFS_H_
#define	_VFS_H_

#define	__packed	__attribute__((__packed__))

#define WANTED_SIZE_IN_KB  		(8*1024)

//------------------------------------------------------------------- CONSTANTS
#define WANTED_SIZE_IN_BYTES        ((WANTED_SIZE_IN_KB + 16 + 8)*1024)
#define WANTED_SECTORS_PER_CLUSTER  (8)

//#define FLASH_PROGRAM_PAGE_SIZE         (512)
#define MBR_BYTES_PER_SECTOR            (512)

//--------------------------------------------------------------------- DERIVED

#define MBR_NUM_NEEDED_SECTORS  (WANTED_SIZE_IN_BYTES / MBR_BYTES_PER_SECTOR)
#define MBR_NUM_NEEDED_CLUSTERS (MBR_NUM_NEEDED_SECTORS / WANTED_SECTORS_PER_CLUSTER)

/* Need 3 sectors/FAT for every 1024 clusters */
#define MBR_SECTORS_PER_FAT     (3*((MBR_NUM_NEEDED_CLUSTERS + 1023)/1024))

/* Macro to help fill the two FAT tables with the empty sectors without
   adding a lot of test #ifs inside the sectors[] declaration below */
#if (MBR_SECTORS_PER_FAT == 1)
#   define EMPTY_FAT_SECTORS
#elif (MBR_SECTORS_PER_FAT == 2)
#   define EMPTY_FAT_SECTORS  {fat2,0},
#elif (MBR_SECTORS_PER_FAT == 3)
#   define EMPTY_FAT_SECTORS  {fat2,0},{fat2,0},
#elif (MBR_SECTORS_PER_FAT == 6)
#   define EMPTY_FAT_SECTORS  {fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},
#elif (MBR_SECTORS_PER_FAT == 9)
#   define EMPTY_FAT_SECTORS  {fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},
#elif (MBR_SECTORS_PER_FAT == 12)
#   define EMPTY_FAT_SECTORS  {fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},{fat2,0},
#else
#   error "Unsupported number of sectors per FAT table"
#endif

#define DIRENTS_PER_SECTOR  (MBR_BYTES_PER_SECTOR / sizeof(FatDirectoryEntry_t))

#define SECTORS_ROOT_IDX        (1 + mbr.num_fats*MBR_SECTORS_PER_FAT)
#define SECTORS_FIRST_FILE_IDX  (SECTORS_ROOT_IDX + 2)
#define SECTORS_SYSTEM_VOLUME_INFORMATION (SECTORS_FIRST_FILE_IDX  + WANTED_SECTORS_PER_CLUSTER)
#define SECTORS_INDEXER_VOLUME_GUID       (SECTORS_SYSTEM_VOLUME_INFORMATION + WANTED_SECTORS_PER_CLUSTER)
#define SECTORS_MBED_HTML_IDX   (SECTORS_INDEXER_VOLUME_GUID + WANTED_SECTORS_PER_CLUSTER)
#define SECTORS_ERROR_FILE_IDX  (SECTORS_MBED_HTML_IDX + WANTED_SECTORS_PER_CLUSTER)

//---------------------------------------------------------------- VERIFICATION

/* Sanity check */
#if (MBR_NUM_NEEDED_CLUSTERS > 4084)
  /* Limited by 12 bit cluster addresses, i.e. 2^12 but only 0x002..0xff5 can be used */
#   error Too many needed clusters, increase WANTED_SECTORS_PER_CLUSTER
#endif

#if ((WANTED_SECTORS_PER_CLUSTER * MBR_BYTES_PER_SECTOR) > 32768)
#   error Cluster size too large, must be <= 32KB
#endif

//-------------------------------------------------------------------- TYPEDEFS

 typedef struct __packed{
    uint8_t boot_sector[11];

    /* DOS 2.0 BPB - Bios Parameter Block, 13 bytes */
    uint16_t bytes_per_sector;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_logical_sectors;
    uint8_t  num_fats;
    uint16_t max_root_dir_entries;
    uint16_t total_logical_sectors;            /* If num is too large for 16 bits, set to 0 and use big_sectors_on_drive */
    uint8_t  media_descriptor;
    uint16_t logical_sectors_per_fat;          /* Need 3 sectors/FAT for every 1024 clusters */

    /* DOS 3.31 BPB - Bios Parameter Block, 12 bytes */
    uint16_t physical_sectors_per_track;
    uint16_t heads;
    uint32_t hidden_sectors;
    uint32_t big_sectors_on_drive;             /* Use if total_logical_sectors=0, needed for large number of sectors */

    /* Extended BIOS Parameter Block, 26 bytes */
    uint8_t  physical_drive_number;
    uint8_t  not_used;
    uint8_t  boot_record_signature;
    uint32_t volume_id;
    char     volume_label[11];
    char     file_system_type[8];

    /* bootstrap data in bytes 62-509 */
    uint8_t  bootstrap[448];

    /* Mandatory value at bytes 510-511, must be 0xaa55 */
    uint16_t signature;
} mbr_t;

typedef enum {
    BIN_FILE,
    PAR_FILE,
    DOW_FILE,
    CRD_FILE,
    SPI_FILE,
    UNSUP_FILE, /* Valid extension, but not supported */
    SKIP_FILE,  /* Unknown extension, typically Long File Name entries */
} FILE_TYPE;

typedef struct {
    FILE_TYPE type;
    char extension[3];
    uint32_t flash_offset;
} FILE_TYPE_MAPPING;

typedef struct __packed FatDirectoryEntry {
    uint8_t filename[11];
    uint8_t attributes;
    uint8_t reserved;
    uint8_t creation_time_ms;
    uint16_t creation_time;
    uint16_t creation_date;
    uint16_t accessed_date;
    uint16_t first_cluster_high_16;
    uint16_t modification_time;
    uint16_t modification_date;
    uint16_t first_cluster_low_16;
    uint32_t filesize;
} FatDirectoryEntry_t;

//------------------------------------------------------------------------- END

uint32_t BlockBuf[1024/4];

typedef struct sector {
    const uint8_t * sect;
    unsigned int length;
} SECTOR;

#define MEDIA_DESCRIPTOR        (0xF0)

void usbd_msc_init(void);
void usbd_msc_read_sect (uint32_t block, uint8_t *buf, uint32_t num_of_blocks);
void usbd_msc_write_sect (uint32_t block, uint8_t *buf, uint32_t num_of_blocks);

#endif
