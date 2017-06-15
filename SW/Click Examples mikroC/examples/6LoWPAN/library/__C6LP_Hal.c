/**
 * @file                        hal_6LoWPAN.c
 * @brief                       HAL for 6LoWPAN C click board
 *
/******************************************************************************/

/*******************************************************************************
********************************************************************************
* Includes
********************************************************************************
*******************************************************************************/

#include "__C6LP_Hal.h"
#include "__C6LP_Driver.h"

/*******************************************************************************
********************************************************************************
* Preprocessor Constants
********************************************************************************
*******************************************************************************/

#define BLOCK_SIZE  255

#define RSSI_OFFSET               76
#define RSSI_OFFSET_LNA_HIGHGAIN  ( RSSI_OFFSET + 3 )
#define RSSI_OFFSET_LNA_LOWGAIN   ( RSSI_OFFSET + 14 )

/*******************************************************************************
********************************************************************************
* Preprocessor Macros
********************************************************************************
*******************************************************************************/

/* SPI access macros */
#define CC2520_SPI_BEGIN() C6LP_SPI_CS = 0
#define CC2520_SPI_END()   C6LP_SPI_CS = 1

/* dummy macros when not using CC2591 */
#define HAL_PA_LNA_RX_LGM()
#define HAL_PA_LNA_RX_HGM()

/* TX power constants */
#define HAL_RF_TXPOWER_MIN_4_DBM   0
#define HAL_RF_TXPOWER_0_DBM       1
#define HAL_RF_TXPOWER_4_DBM       2

/*******************************************************************************
********************************************************************************
* Typedefs
********************************************************************************
*******************************************************************************/

typedef union
{
    uint16_t w;
    struct
    {
        uint8_t b0;
        uint8_t b1;
    }
    b;
}
T_C6LP_eWord;

typedef union
{
    uint32_t dw;
    struct
    {
        uint8_t b0;
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
    }
    b;
}
T_C6LP_eDword;

typedef struct
{
    uint8_t reg;
    uint8_t val;
}
T_C6LP_regVal;

/*******************************************************************************
********************************************************************************
* Memory Declarations
********************************************************************************
*******************************************************************************/

// Recommended register settings which differ from the data sheet
static T_C6LP_regVal regval[]= {
    // Tuning settings
    CC2520_TXPOWER,     0xF7,       // Max TX output power
    CC2520_CCACTRL0,    0xF8,       // CCA treshold -80dBm

    // Recommended RX settings
    CC2520_MDMCTRL0,    0x85,
    CC2520_MDMCTRL1,    0x14,
    CC2520_RXCTRL,      0x3F,
    CC2520_FSCTRL,      0x5A,
    CC2520_FSCAL1,      0x03,
    CC2520_AGCCTRL1,    0x11,
    CC2520_ADCTEST0,    0x10,
    CC2520_ADCTEST1,    0x0E,
    CC2520_ADCTEST2,    0x03,

    // Configuration for applications using halRfInit()
    CC2520_FRMCTRL0,    0x60,               // Auto-ack
    CC2520_EXTCLOCK,    0x00,
    CC2520_GPIOCTRL0,   CC2520_GPIO_RSSI_VALID, //CC2520_GPIO_SAMPLED_CCA,
    CC2520_GPIOCTRL1,   1 + CC2520_EXC_RX_FRM_DONE,
    CC2520_GPIOCTRL2,   CC2520_GPIO_RSSI_VALID,
    CC2520_GPIOCTRL3,   CC2520_GPIO_SFD,
    CC2520_GPIOCTRL4,   CC2520_GPIO_SNIFFER_DATA,
    CC2520_GPIOCTRL5,   CC2520_GPIO_SNIFFER_CLK,

    // Terminate array
    0,                  0x00
};

static uint8_t rssiOffset = RSSI_OFFSET;

/*******************************************************************************
********************************************************************************
* Private Function Prototypes
********************************************************************************
*******************************************************************************/

// Instruction prototypes
uint8_t  CC2520_SNOP(void);
uint8_t  CC2520_SIBUFEX(void);
uint8_t  CC2520_SSAMPLECCA(void);
uint8_t  CC2520_SXOSCON(void);
uint8_t  CC2520_STXCAL(void);
uint8_t  CC2520_SRXON(void);
uint8_t  CC2520_STXON(void);
uint8_t  CC2520_STXONCCA(void);
uint8_t  CC2520_SRFOFF(void);
uint8_t  CC2520_SXOSCOFF(void);
uint8_t  CC2520_SFLUSHRX(void);
uint8_t  CC2520_SFLUSHTX(void);
uint8_t  CC2520_SACK(void);
uint8_t  CC2520_SACKPEND(void);
uint8_t  CC2520_SNACK(void);
uint8_t  CC2520_SRXMASKBITSET(void);
uint8_t  CC2520_SRXMASKBITCLR(void);
uint8_t  CC2520_IBUFLD(uint8_t i);
uint8_t  CC2520_SRES(void);
uint8_t  CC2520_MEMRD(uint16_t addr, uint16_t count, uint8_t  *pData);
uint8_t  CC2520_MEMRD8(uint16_t addr);
uint16_t CC2520_MEMRD16(uint16_t addr);
uint32_t CC2520_MEMRD24(uint16_t addr);
uint8_t  CC2520_MEMWR(uint16_t addr, uint16_t count, uint8_t  *pData);
uint8_t  CC2520_MEMWR8(uint16_t addr, uint8_t value);
uint8_t  CC2520_MEMWR16(uint16_t addr, uint16_t value);
uint8_t  CC2520_MEMWR24(uint16_t addr, uint32_t value);
uint8_t  CC2520_RXBUFCP_BEGIN(uint16_t addr, uint8_t *pCurrCount);
uint8_t  CC2520_RXBUFCP_END(uint16_t addr, uint8_t count, uint8_t  *pData);
uint8_t  CC2520_RXBUF(uint8_t count, uint8_t  *pData);
uint8_t  CC2520_RXBUF8(void);
uint16_t CC2520_RXBUF16(void);
uint8_t  CC2520_RXBUFMOV(
    uint8_t pri, uint16_t addr, uint8_t count, uint8_t *pCurrCount);
uint8_t  CC2520_TXBUF(uint8_t count, uint8_t  *pData);
void     CC2520_TXBUF8(uint8_t _data);
void     CC2520_TXBUF16(uint16_t _data);
uint8_t  CC2520_TXBUFCP(
    uint8_t pri, uint16_t addr, uint8_t count, uint8_t *pCurrCount);
uint8_t  CC2520_RANDOM(uint8_t count, uint8_t  *pData);
uint8_t  CC2520_RANDOM8(void);
uint16_t CC2520_RANDOM16(void);
uint8_t  CC2520_RXMASKOR(uint16_t orMask);
uint8_t  CC2520_RXMASKAND(uint16_t andMask);
uint8_t  CC2520_MEMCP(
    uint8_t pri, uint16_t count, uint16_t src, uint16_t dest);
uint8_t  CC2520_MEMCPR(
    uint8_t pri, uint16_t count, uint16_t src, uint16_t dest);
uint8_t  CC2520_MEMXCP(
    uint8_t pri, uint16_t count, uint16_t src, uint16_t dest);
uint8_t  CC2520_MEMXWR(uint16_t addr, uint16_t count, uint8_t  *pData);
uint8_t  CC2520_BSET(uint8_t bitAddr);
uint8_t  CC2520_BCLR(uint8_t bitAddr);
uint8_t  CC2520_CTR(uint8_t pri, uint8_t k, uint8_t c, uint8_t n,
    uint16_t src, uint16_t dest);
uint8_t  CC2520_UCTR(uint8_t pri, uint8_t k, uint8_t c, uint8_t n,
    uint16_t src, uint16_t dest);
uint8_t  CC2520_CBCMAC(uint8_t pri, uint8_t k, uint8_t c,
    uint16_t src, uint16_t dest, uint8_t m);
uint8_t  CC2520_UCBCMAC(uint8_t pri, uint8_t k, uint8_t c,
    uint16_t src, uint8_t m);
uint8_t  CC2520_CCM(uint8_t pri, uint8_t k, uint8_t c, uint8_t n,
    uint16_t src, uint16_t dest, uint8_t f, uint8_t m);
uint8_t  CC2520_UCCM(uint8_t pri, uint8_t k, uint8_t c, uint8_t n,
    uint16_t src, uint16_t dest, uint8_t f, uint8_t m);
uint8_t  CC2520_ECB(
    uint8_t pri, uint8_t k, uint8_t c, uint16_t src, uint16_t dest);
uint8_t  CC2520_ECBO(uint8_t pri, uint8_t k, uint8_t c, uint16_t addr);
uint8_t  CC2520_ECBX(
    uint8_t pri, uint8_t k, uint8_t c, uint16_t src, uint16_t dest);
uint8_t  CC2520_ECBXO(uint8_t pri, uint8_t k, uint8_t c, uint16_t addr);
uint8_t  CC2520_INC(uint8_t pri, uint8_t c, uint16_t addr);
uint8_t  CC2520_ABORT(uint8_t c);
uint8_t  CC2520_REGRD(uint8_t addr, uint8_t count, uint8_t  *pValues);
uint8_t  CC2520_REGRD8(uint8_t addr);
uint16_t CC2520_REGRD16(uint8_t addr);
uint32_t CC2520_REGRD24(uint8_t addr);
uint8_t  CC2520_REGWR(uint8_t addr, uint8_t count, uint8_t  *pValues);
void     CC2520_REGWR8(uint8_t addr, uint8_t value);
void     CC2520_REGWR16(uint8_t addr, uint16_t value);
void     CC2520_REGWR24(uint8_t addr, uint32_t value);
uint8_t  CC2520_INS_STROBE(uint8_t strobe);

static void CC2520_INS_RD_ARRAY(uint16_t count, uint8_t *pData);
static uint8_t CC2520_INS_MEMCP_COMMON(uint8_t instr, uint8_t pri,
    uint16_t count, uint16_t src, uint16_t dest);

static uint8_t CC2520_SPI_TXRX(uint8_t x);

static uint8_t gotException(uint8_t index);
static uint8_t waitException(uint8_t exc, uint16_t timeOut);
static void clearException(uint32_t dwMap);

static uint8_t halRfWaitRadioReady(void);
static uint8_t halRfGetStatusByte(void);

/*******************************************************************************
********************************************************************************
* Private Functions
********************************************************************************
*******************************************************************************/

void CC2520_INS_WR_ARRAY(uint16_t count, uint8_t *pData)
{
    while (count--)
    {
        C6LP_spiRxTx(*pData);
        pData++;
    }
}

uint8_t CC2520_INS_STROBE(uint8_t strobe)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(strobe);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_SNOP(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SNOP);
}

uint8_t CC2520_SIBUFEX(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SIBUFEX);
}

uint8_t CC2520_SSAMPLECCA(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SSAMPLECCA);
}

uint8_t CC2520_SXOSCON(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SXOSCON);
}

uint8_t CC2520_STXCAL(void)
{
    return CC2520_INS_STROBE(CC2520_INS_STXCAL);
}

uint8_t CC2520_SRXON(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SRXON);
}

uint8_t CC2520_STXON(void)
{
    return CC2520_INS_STROBE(CC2520_INS_STXON);
}

uint8_t CC2520_STXONCCA(void)
{
    return CC2520_INS_STROBE(CC2520_INS_STXONCCA);
}

uint8_t CC2520_SRFOFF(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SRFOFF);
}

uint8_t CC2520_SXOSCOFF(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SXOSCOFF);
}

uint8_t CC2520_SFLUSHRX(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SFLUSHRX);
}

uint8_t CC2520_SFLUSHTX(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SFLUSHTX);
}

uint8_t CC2520_SACK(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SACK);
}

uint8_t CC2520_SACKPEND(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SACKPEND);
}

uint8_t CC2520_SNACK(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SNACK);
}

uint8_t CC2520_SRXMASKBITSET(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SRXMASKBITSET);
}

uint8_t CC2520_SRXMASKBITCLR(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SRXMASKBITCLR);
}

uint8_t CC2520_IBUFLD(uint8_t i)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_IBUFLD);
    C6LP_spiRxTx(i);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_SRES(void)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_SRES);
    C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_MEMRD(uint16_t addr, uint16_t count, uint8_t *pData)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_MEMRD | (addr >> 8));
    C6LP_spiRxTx(addr);
    CC2520_INS_RD_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_MEMRD8(uint16_t addr)
{
    uint8_t value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_MEMRD | (addr >> 8));
    C6LP_spiRxTx(addr);
    value = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value;
}

uint16_t CC2520_MEMRD16(uint16_t addr)
{
    T_C6LP_eWord value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_MEMRD | (addr >> 8));
    C6LP_spiRxTx(addr);
    value.b.b0 = C6LP_spiRxTx(0x00);
    value.b.b1 = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value.w;
}

uint32_t CC2520_MEMRD24(uint16_t addr)
{
    T_C6LP_eDword value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_MEMRD | (addr >> 8));
    C6LP_spiRxTx(addr);
    value.b.b0 = C6LP_spiRxTx(0x00);
    value.b.b1 = C6LP_spiRxTx(0x00);
    value.b.b2 = C6LP_spiRxTx(0x00);
    value.b.b3 = 0x00;
    CC2520_SPI_END();
    return value.dw;
}

uint8_t CC2520_MEMWR(uint16_t addr, uint16_t count, uint8_t *pData)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_MEMWR | (addr >> 8));
    C6LP_spiRxTx(addr);
    CC2520_INS_WR_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_MEMWR8(uint16_t addr, uint8_t value)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_MEMWR | (addr >> 8));
    C6LP_spiRxTx(addr);
    C6LP_spiRxTx(value);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_MEMWR16(uint16_t addr, uint16_t value)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_MEMWR | (addr >> 8));
    C6LP_spiRxTx(addr);
    C6LP_spiRxTx(value);
    C6LP_spiRxTx(value >> 8);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_MEMWR24(uint16_t addr, uint32_t value)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_MEMWR | (addr >> 8));
    C6LP_spiRxTx(addr);
    C6LP_spiRxTx(value);
    C6LP_spiRxTx(value >> 8);
    C6LP_spiRxTx(value >> 16);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_RXBUF(uint8_t count, uint8_t  *pData)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_RXBUF);
    CC2520_INS_RD_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_RXBUF8(void)
{
    uint8_t value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_RXBUF);
    value = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value;
}

uint16_t CC2520_RXBUF16(void)
{
    T_C6LP_eWord value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_RXBUF);
    value.b.b0 = C6LP_spiRxTx(0x00);
    value.b.b1 = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value.w;
}

uint8_t CC2520_RXBUFCP_BEGIN(uint16_t addr, uint8_t *pCurrCount)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_RXBUFCP);
    if (pCurrCount)
    {
        *pCurrCount = C6LP_spiRxTx(addr >> 8);
    }
    else
    {
        C6LP_spiRxTx(addr >> 8);
    }
    return s;
}

uint8_t CC2520_RXBUFCP_END(uint16_t addr, uint8_t count, uint8_t  *pData)
{
    uint8_t s;
    s = C6LP_spiRxTx(addr);
    CC2520_INS_RD_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_RXBUFMOV(uint8_t pri, uint16_t addr, uint8_t count,
    uint8_t *pCurrCount)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_RXBUFMOV | pri);
    if (pCurrCount)
    {
        *pCurrCount = C6LP_spiRxTx(count);
    }
    else
    {
        C6LP_spiRxTx(count);
    }
    C6LP_spiRxTx(addr >> 8);
    C6LP_spiRxTx(addr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_TXBUF(uint8_t count, uint8_t  *pData)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_TXBUF);
    CC2520_INS_WR_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

void CC2520_TXBUF8(uint8_t _data)
{
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_TXBUF);
    C6LP_spiRxTx(_data);
    CC2520_SPI_END();
}

void CC2520_TXBUF16(uint16_t _data)
{
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_TXBUF);
    C6LP_spiRxTx(_data);
    C6LP_spiRxTx(_data >> 8);
    CC2520_SPI_END();
}

uint8_t CC2520_TXBUFCP(uint8_t pri, uint16_t addr, uint8_t count,
    uint8_t *pCurrCount)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_TXBUFCP | pri);
    if (pCurrCount)
    {
        *pCurrCount = C6LP_spiRxTx(count);
    }
    else
    {
        C6LP_spiRxTx(count);
    }
    C6LP_spiRxTx(addr >> 8);
    C6LP_spiRxTx(addr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_RANDOM(uint8_t count, uint8_t *pData)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_RANDOM);
    C6LP_spiRxTx(0x00);
    CC2520_INS_RD_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_RANDOM8(void)
{
    uint8_t value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_RANDOM);
    C6LP_spiRxTx(0x00);
    value = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value;
}

uint16_t CC2520_RANDOM16(void)
{
    T_C6LP_eWord value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_RANDOM);
    C6LP_spiRxTx(0x00);
    value.b.b0 = C6LP_spiRxTx(0x00);
    value.b.b1 = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value.w;
}

uint8_t CC2520_RXMASKOR(uint16_t orMask)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_RXMASKOR);
    C6LP_spiRxTx(orMask >> 8);
    C6LP_spiRxTx(orMask);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_RXMASKAND(uint16_t andMask)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_RXMASKAND);
    C6LP_spiRxTx(andMask >> 8);
    C6LP_spiRxTx(andMask);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_MEMCP(uint8_t pri, uint16_t count, uint16_t src, uint16_t dest)
{
    return CC2520_INS_MEMCP_COMMON(CC2520_INS_MEMCP, pri, count, src, dest);
}

uint8_t CC2520_MEMCPR(uint8_t pri, uint16_t count, uint16_t src, uint16_t dest)
{
    return CC2520_INS_MEMCP_COMMON(CC2520_INS_MEMCPR, pri, count, src, dest);
}

uint8_t CC2520_MEMXCP(uint8_t pri, uint16_t count, uint16_t src, uint16_t dest)
{
    return CC2520_INS_MEMCP_COMMON(CC2520_INS_MEMXCP, pri, count, src, dest);
}

uint8_t CC2520_MEMXWR(uint16_t addr, uint16_t count, uint8_t  *pData)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_MEMXWR);
    C6LP_spiRxTx(addr >> 8);
    C6LP_spiRxTx(addr);
    CC2520_INS_WR_ARRAY(count, pData);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_BSET(uint8_t bitAddr)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_BSET);
    C6LP_spiRxTx(bitAddr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_BCLR(uint8_t bitAddr)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_BCLR);
    C6LP_spiRxTx(bitAddr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_CTR(uint8_t pri, uint8_t k, uint8_t c, uint8_t n,
    uint16_t src, uint16_t dest)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_CTR | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx(c);
    C6LP_spiRxTx(n);
    C6LP_spiRxTx(((src >> 8) << 4) | (dest >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_UCTR(uint8_t pri, uint8_t k, uint8_t c, uint8_t n,
    uint16_t src, uint16_t dest)
{
    return CC2520_CTR(pri, k, c, n, src, dest);
}

uint8_t CC2520_CBCMAC(uint8_t pri, uint8_t k, uint8_t c,
    uint16_t src, uint16_t dest, uint8_t m)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_CBCMAC | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx(c);
    C6LP_spiRxTx(((src >> 8) << 4) | (dest >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest);
    C6LP_spiRxTx(m);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_UCBCMAC(uint8_t pri, uint8_t k, uint8_t c,
    uint16_t src, uint8_t m)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_UCBCMAC | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx(c);
    C6LP_spiRxTx(src >> 8);
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(m);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_CCM(uint8_t pri, uint8_t k, uint8_t c, uint8_t n, uint16_t src,
    uint16_t dest, uint8_t f, uint8_t m)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_CCM | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx(c);
    C6LP_spiRxTx(n);
    C6LP_spiRxTx(((src >> 8) << 4) | (dest >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest);
    C6LP_spiRxTx(f);
    C6LP_spiRxTx(m);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_UCCM(uint8_t pri, uint8_t k, uint8_t c, uint8_t n, uint16_t src,
    uint16_t dest, uint8_t f, uint8_t m)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_UCCM | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx(c);
    C6LP_spiRxTx(n);
    C6LP_spiRxTx(((src >> 8) << 4) | (dest >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest);
    C6LP_spiRxTx(f);
    C6LP_spiRxTx(m);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_ECB(uint8_t pri, uint8_t k, uint8_t c,
    uint16_t src, uint16_t dest)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_ECB | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx((c << 4) | (src >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest >> 8);
    C6LP_spiRxTx(dest);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_ECBO(uint8_t pri, uint8_t k, uint8_t c, uint16_t addr)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_ECBO | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx((c << 4) | (addr >> 8));
    C6LP_spiRxTx(addr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_ECBX(uint8_t pri, uint8_t k, uint8_t c, uint16_t src, uint16_t dest)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_ECBX | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx((c << 4) | (src >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest >> 8);
    C6LP_spiRxTx(dest);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_ECBXO(uint8_t pri, uint8_t k, uint8_t c, uint16_t addr)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_ECBXO | pri);
    C6LP_spiRxTx(k);
    C6LP_spiRxTx((c << 4) | (addr >> 8));
    C6LP_spiRxTx(addr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_INC(uint8_t pri, uint8_t c, uint16_t addr)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_INC | pri);
    C6LP_spiRxTx((c << 4) | (addr >> 8));
    C6LP_spiRxTx(addr);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_ABORT(uint8_t c)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_ABORT);
    C6LP_spiRxTx(c);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_REGRD(uint8_t addr, uint8_t count, uint8_t  *pValues)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_REGRD | addr);
    CC2520_INS_RD_ARRAY(count, pValues);
    CC2520_SPI_END();
    return s;
}

uint8_t CC2520_REGRD8(uint8_t addr)
{
    uint8_t value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_REGRD | addr);
    value = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value;
}

uint16_t CC2520_REGRD16(uint8_t addr)
{
    T_C6LP_eWord value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_REGRD | addr);
    value.b.b0 = C6LP_spiRxTx(0x00);
    value.b.b1 = C6LP_spiRxTx(0x00);
    CC2520_SPI_END();
    return value.w;
}

uint32_t CC2520_REGRD24(uint8_t addr)
{
    T_C6LP_eDword value;
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_REGRD | addr);
    value.b.b0 = C6LP_spiRxTx(0x00);
    value.b.b1 = C6LP_spiRxTx(0x00);
    value.b.b2 = C6LP_spiRxTx(0x00);
    value.b.b3 = 0x00;
    CC2520_SPI_END();
    return value.dw;
}

uint8_t CC2520_REGWR(uint8_t addr, uint8_t count, uint8_t  *pValues)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(CC2520_INS_REGWR | addr);
    CC2520_INS_WR_ARRAY(count, pValues);
    CC2520_SPI_END();
    return s;
}

void CC2520_REGWR8(uint8_t addr, uint8_t value)
{
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_REGWR | addr);
    C6LP_spiRxTx(value);
    CC2520_SPI_END();
    return;
}

void CC2520_REGWR16(uint8_t addr, uint16_t value)
{
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_REGWR | addr);
    C6LP_spiRxTx(value);
    C6LP_spiRxTx(value >> 8);
    CC2520_SPI_END();
}

void CC2520_REGWR24(uint8_t addr, uint32_t value)
{
    CC2520_SPI_BEGIN();
    C6LP_spiRxTx(CC2520_INS_REGWR | addr);
    C6LP_spiRxTx(value);
    C6LP_spiRxTx(value >> 8);
    C6LP_spiRxTx(value >> 16);
    CC2520_SPI_END();
}

static void CC2520_INS_RD_ARRAY(uint16_t count, uint8_t *pData)
{
    while (count--)
    {
        *pData = C6LP_spiRxTx(0x00);
        pData++;
    }
}

static uint8_t CC2520_INS_MEMCP_COMMON(uint8_t instr, uint8_t pri,
    uint16_t count, uint16_t src, uint16_t dest)
{
    uint8_t s;
    CC2520_SPI_BEGIN();
    s = C6LP_spiRxTx(instr | pri);
    C6LP_spiRxTx(count);
    C6LP_spiRxTx(((src >> 8) << 4) | (dest >> 8));
    C6LP_spiRxTx(src);
    C6LP_spiRxTx(dest);
    CC2520_SPI_END();
    return s;
}

static uint8_t gotException(uint8_t index)
{
    uint8_t exceptions = CC2520_REGRD8(CC2520_EXCFLAG0 + (index >> 3));
    if (exceptions & (1 << (index & 0x07)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static uint8_t waitException(uint8_t exc, uint16_t timeOut)
{
    while (--timeOut > 0)
    {
        if (gotException(exc))
            break;
        Delay_us(10);
    }
    return timeOut > 0;
}

static void clearException(uint32_t dwMap)
{
    CC2520_REGWR24(CC2520_EXCFLAG0, ~dwMap);
}

static uint8_t halRfWaitRadioReady(void)
{
    uint8_t i;

    // Wait for XOSC stable to be announced on the MISO pin
    i= 100;
    C6LP_SPI_CS = 0;
    while ((i > 0) && !C6LP_SPI_MISO)
    {
        Delay_us(10);
        --i;
    }
    C6LP_SPI_CS = 1;

    return (i > 0) ? SUCCESS : FAILED;
}

static uint8_t halRfGetStatusByte(void)
{
    return CC2520_INS_STROBE(CC2520_INS_SNOP);
}

/*******************************************************************************
********************************************************************************
* Public Functions
********************************************************************************
*******************************************************************************/

uint8_t C6LP_halInit(void)
{
    T_C6LP_regVal* p;
    uint8_t val;

    // Make sure to pull the CC2520 RESETn and VREG_EN pins low
    C6LP_RESET = 0;
    C6LP_SPI_CS = 1;
    C6LP_VREG_EN = 0;
    Delay_us(1100);
        
    // Enable the voltage regulator and wait for it (CC2520 power-up)
    C6LP_VREG_EN = 1;
    Delay_us(CC2520_VREG_MAX_STARTUP_TIME);

    // Release reset
    C6LP_RESET = 1;

    // Wait for XOSC stable to be announced on the MISO pin
    if (halRfWaitRadioReady() != 0)
        return FAILED;

    // Write non-default register values
    p = regval;
    while (p->reg != 0)
    {
        CC2520_MEMWR8(p->reg, p->val);
        p++;
    }

    // Verify a register
    val = CC2520_MEMRD8(CC2520_MDMCTRL0);

    return (val == 0x85) ? SUCCESS : FAILED;
}

uint8_t C6LP_halGetChipId(void)
{
    return (CC2520_MEMRD8(CC2520_CHIPID));
}

uint8_t C6LP_halGetChipVer(void)
{
    return (CC2520_MEMRD8(CC2520_VERSION));
}

uint8_t C6LP_halGetRandomByte(void)
{
    return CC2520_RANDOM8();
}

uint8_t C6LP_halGetRssiOffset(void)
{
    return rssiOffset;
}

void C6LP_halSetChannel(uint8_t channel)
{
    CC2520_REGWR8(CC2520_FREQCTRL, MIN_CHANNEL +
        ((channel - MIN_CHANNEL) * CHANNEL_SPACING));
}

void C6LP_halSetShortAddr(uint16_t shortAddr)
{
    CC2520_MEMWR16(CC2520_RAM_SHORTADDR, shortAddr);
}

void C6LP_halSetPanId(uint16_t panId)
{
    CC2520_MEMWR16(CC2520_RAM_PANID, panId);
}

uint8_t C6LP_halSetTxPower(uint8_t power)
{
    uint8_t n;

    switch (power)
    {
        case HAL_RF_TXPOWER_MIN_4_DBM:
            n = CC2520_TXPOWER_MIN_4_DBM;
            break;
        case HAL_RF_TXPOWER_0_DBM:
            n = CC2520_TXPOWER_0_DBM; 
            break;
        case HAL_RF_TXPOWER_4_DBM:
            n = CC2520_TXPOWER_4_DBM;
            break;
        default:
            return FAILED;
    }
    CC2520_REGWR8(CC2520_TXPOWER, n);
    return SUCCESS;
}

void C6LP_halWriteTxBuf(uint8_t* pData, uint8_t length)
{
    // Copy packet to TX FIFO
    CC2520_TXBUF(length, pData);
}

void C6LP_halReadRxBuf(uint8_t* pData, uint8_t length)
{
    CC2520_RXBUF(length, pData);
}

uint8_t C6LP_halReadMemory(uint16_t addr, uint8_t* pData, uint8_t length)
{
    if (addr >= CC2520_MEMORY_SIZE)
        length = 0;
    else if (addr + length > CC2520_MEMORY_SIZE)
        length = CC2520_MEMORY_SIZE - addr;

    CC2520_MEMRD(addr, length, pData);
    return length;
}

uint8_t C6LP_halWriteMemory(uint16_t addr, uint8_t* pData, uint8_t length)
{
    return 0;
}

uint8_t C6LP_halTransmit(void)
{
    uint16_t timeout = 2500; // 2500 x 20us = 50ms
    uint8_t status = 0;

    // Wait for RSSI to become valid
    while (!C6LP_GPIO0);

    // Reuse GPIO0 for TX_FRM_DONE exception
    C6LP_halDisableInterrupts();
    CC2520_CFG_GPIO_OUT(0, CC2520_GPIO_SAMPLED_CCA);
    C6LP_halEnableInterrupts();

    // Wait for the transmission to begin before exiting
    // (makes sure that this function cannot be called a second time,
    // and thereby cancelling the first transmission).
    while (--timeout > 0)
    {
        C6LP_halDisableInterrupts();
        CC2520_INS_STROBE(CC2520_INS_STXONCCA);
        C6LP_halEnableInterrupts();
        if (C6LP_GPIO0)
            break;
        Delay_us(20);
    }
    
    if (timeout == 0)
    {
        status = FAILED;
        CC2520_INS_STROBE(CC2520_INS_SFLUSHTX);
    }
    else
    {
        C6LP_halDisableInterrupts();
        CC2520_CFG_GPIO_OUT(0, 1 + CC2520_EXC_TX_FRM_DONE);
        C6LP_halEnableInterrupts();
    
        status = SUCCESS;
        // Wait for TX_FRM_DONE exception
        while (!C6LP_GPIO0);
        C6LP_halDisableInterrupts();
        CC2520_CLEAR_EXC(CC2520_EXC_TX_FRM_DONE);
        C6LP_halEnableInterrupts();
    }

    // Reconfigure GPIO0
    C6LP_halDisableInterrupts();
    CC2520_CFG_GPIO_OUT(0, CC2520_GPIO_RSSI_VALID);
    C6LP_halEnableInterrupts();
    return status;
}

void C6LP_halReceiveOn(void)
{
    CC2520_INS_STROBE(CC2520_INS_SRXON);
}

void C6LP_halReceiveOff(void)
{
    CC2520_INS_STROBE(CC2520_INS_SRFOFF);
}

void C6LP_halDisableRxInterrupt(void)
{
    // Clear the exception
    CLEAR_EXC_RX_FRM_DONE();
}

void C6LP_halEnableRxInterrupt(void)
{

}

void C6LP_halRxInterruptConfig(void)
{
    // Clear the exception
    CLEAR_EXC_RX_FRM_DONE();
}

void C6LP_halWaitTransceiverReady(void)
{
    C6LP_halDisableInterrupts();
    CC2520_CFG_GPIO_OUT(0, CC2520_GPIO_TX_ACTIVE);
    C6LP_halEnableInterrupts();

    while (C6LP_GPIO0);
    
    C6LP_halDisableInterrupts();
    CC2520_CFG_GPIO_OUT(0, CC2520_GPIO_RSSI_VALID);
    C6LP_halEnableInterrupts();
}

/**
* @brief Global interrupt disable.
*
* @return none
*
* Function disables interrupts globally.
*/
void C6LP_halDisableInterrupts(void)
{
    DisableInterrupts();
}

/**
* @brief Global interrupt enable.
*
* @return none
*
* Function enables interrupts globally.
*/
void C6LP_halEnableInterrupts(void)
{
    EnableInterrupts();
}