// File: dspi_hal.h

// Declarations of main functionalities in the DSPI HAL module.

#ifndef _dspi_hal_h_
#define _dspi_hal_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// MCR Bit Fields
#define SPI_MCR_HALT_MASK                        0x1u
#define SPI_MCR_HALT_SHIFT                       0
#define SPI_MCR_HALT_WIDTH                       1
#define SPI_MCR_HALT(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_MCR_HALT_SHIFT))&SPI_MCR_HALT_MASK)
#define SPI_MCR_SMPL_PT_MASK                     0x300u
#define SPI_MCR_SMPL_PT_SHIFT                    8
#define SPI_MCR_SMPL_PT_WIDTH                    2
#define SPI_MCR_SMPL_PT(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_MCR_SMPL_PT_SHIFT))&SPI_MCR_SMPL_PT_MASK)
#define SPI_MCR_CLR_RXF_MASK                     0x400u
#define SPI_MCR_CLR_RXF_SHIFT                    10
#define SPI_MCR_CLR_RXF_WIDTH                    1
#define SPI_MCR_CLR_RXF(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_MCR_CLR_RXF_SHIFT))&SPI_MCR_CLR_RXF_MASK)
#define SPI_MCR_CLR_TXF_MASK                     0x800u
#define SPI_MCR_CLR_TXF_SHIFT                    11
#define SPI_MCR_CLR_TXF_WIDTH                    1
#define SPI_MCR_CLR_TXF(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_MCR_CLR_TXF_SHIFT))&SPI_MCR_CLR_TXF_MASK)
#define SPI_MCR_DIS_RXF_MASK                     0x1000u
#define SPI_MCR_DIS_RXF_SHIFT                    12
#define SPI_MCR_DIS_RXF_WIDTH                    1
#define SPI_MCR_DIS_RXF(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_MCR_DIS_RXF_SHIFT))&SPI_MCR_DIS_RXF_MASK)
#define SPI_MCR_DIS_TXF_MASK                     0x2000u
#define SPI_MCR_DIS_TXF_SHIFT                    13
#define SPI_MCR_DIS_TXF_WIDTH                    1
#define SPI_MCR_DIS_TXF(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_MCR_DIS_TXF_SHIFT))&SPI_MCR_DIS_TXF_MASK)
#define SPI_MCR_MDIS_MASK                        0x4000u
#define SPI_MCR_MDIS_SHIFT                       14
#define SPI_MCR_MDIS_WIDTH                       1
#define SPI_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_MCR_MDIS_SHIFT))&SPI_MCR_MDIS_MASK)
#define SPI_MCR_DOZE_MASK                        0x8000u
#define SPI_MCR_DOZE_SHIFT                       15
#define SPI_MCR_DOZE_WIDTH                       1
#define SPI_MCR_DOZE(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_MCR_DOZE_SHIFT))&SPI_MCR_DOZE_MASK)
#define SPI_MCR_PCSIS_MASK                       0x3F0000u
#define SPI_MCR_PCSIS_SHIFT                      16
#define SPI_MCR_PCSIS_WIDTH                      6
#define SPI_MCR_PCSIS(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_MCR_PCSIS_SHIFT))&SPI_MCR_PCSIS_MASK)
#define SPI_MCR_ROOE_MASK                        0x1000000u
#define SPI_MCR_ROOE_SHIFT                       24
#define SPI_MCR_ROOE_WIDTH                       1
#define SPI_MCR_ROOE(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_MCR_ROOE_SHIFT))&SPI_MCR_ROOE_MASK)
#define SPI_MCR_PCSSE_MASK                       0x2000000u
#define SPI_MCR_PCSSE_SHIFT                      25
#define SPI_MCR_PCSSE_WIDTH                      1
#define SPI_MCR_PCSSE(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_MCR_PCSSE_SHIFT))&SPI_MCR_PCSSE_MASK)
#define SPI_MCR_MTFE_MASK                        0x4000000u
#define SPI_MCR_MTFE_SHIFT                       26
#define SPI_MCR_MTFE_WIDTH                       1
#define SPI_MCR_MTFE(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_MCR_MTFE_SHIFT))&SPI_MCR_MTFE_MASK)
#define SPI_MCR_FRZ_MASK                         0x8000000u
#define SPI_MCR_FRZ_SHIFT                        27
#define SPI_MCR_FRZ_WIDTH                        1
#define SPI_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_MCR_FRZ_SHIFT))&SPI_MCR_FRZ_MASK)
#define SPI_MCR_DCONF_MASK                       0x30000000u
#define SPI_MCR_DCONF_SHIFT                      28
#define SPI_MCR_DCONF_WIDTH                      2
#define SPI_MCR_DCONF(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_MCR_DCONF_SHIFT))&SPI_MCR_DCONF_MASK)
#define SPI_MCR_CONT_SCKE_MASK                   0x40000000u
#define SPI_MCR_CONT_SCKE_SHIFT                  30
#define SPI_MCR_CONT_SCKE_WIDTH                  1
#define SPI_MCR_CONT_SCKE(x)                     (((uint32_t)(((uint32_t)(x))<<SPI_MCR_CONT_SCKE_SHIFT))&SPI_MCR_CONT_SCKE_MASK)
#define SPI_MCR_MSTR_MASK                        0x80000000u
#define SPI_MCR_MSTR_SHIFT                       31
#define SPI_MCR_MSTR_WIDTH                       1
#define SPI_MCR_MSTR(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_MCR_MSTR_SHIFT))&SPI_MCR_MSTR_MASK)
// TCR Bit Fields
#define SPI_TCR_SPI_TCNT_MASK                    0xFFFF0000u
#define SPI_TCR_SPI_TCNT_SHIFT                   16
#define SPI_TCR_SPI_TCNT_WIDTH                   16
#define SPI_TCR_SPI_TCNT(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_TCR_SPI_TCNT_SHIFT))&SPI_TCR_SPI_TCNT_MASK)
// CTAR Bit Fields
#define SPI_CTAR_BR_MASK                         0xFu
#define SPI_CTAR_BR_SHIFT                        0
#define SPI_CTAR_BR_WIDTH                        4
#define SPI_CTAR_BR(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_BR_SHIFT))&SPI_CTAR_BR_MASK)
#define SPI_CTAR_DT_MASK                         0xF0u
#define SPI_CTAR_DT_SHIFT                        4
#define SPI_CTAR_DT_WIDTH                        4
#define SPI_CTAR_DT(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_DT_SHIFT))&SPI_CTAR_DT_MASK)
#define SPI_CTAR_ASC_MASK                        0xF00u
#define SPI_CTAR_ASC_SHIFT                       8
#define SPI_CTAR_ASC_WIDTH                       4
#define SPI_CTAR_ASC(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_ASC_SHIFT))&SPI_CTAR_ASC_MASK)
#define SPI_CTAR_CSSCK_MASK                      0xF000u
#define SPI_CTAR_CSSCK_SHIFT                     12
#define SPI_CTAR_CSSCK_WIDTH                     4
#define SPI_CTAR_CSSCK(x)                        (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_CSSCK_SHIFT))&SPI_CTAR_CSSCK_MASK)
#define SPI_CTAR_PBR_MASK                        0x30000u
#define SPI_CTAR_PBR_SHIFT                       16
#define SPI_CTAR_PBR_WIDTH                       2
#define SPI_CTAR_PBR(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_PBR_SHIFT))&SPI_CTAR_PBR_MASK)
#define SPI_CTAR_PDT_MASK                        0xC0000u
#define SPI_CTAR_PDT_SHIFT                       18
#define SPI_CTAR_PDT_WIDTH                       2
#define SPI_CTAR_PDT(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_PDT_SHIFT))&SPI_CTAR_PDT_MASK)
#define SPI_CTAR_PASC_MASK                       0x300000u
#define SPI_CTAR_PASC_SHIFT                      20
#define SPI_CTAR_PASC_WIDTH                      2
#define SPI_CTAR_PASC(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_PASC_SHIFT))&SPI_CTAR_PASC_MASK)
#define SPI_CTAR_PCSSCK_MASK                     0xC00000u
#define SPI_CTAR_PCSSCK_SHIFT                    22
#define SPI_CTAR_PCSSCK_WIDTH                    2
#define SPI_CTAR_PCSSCK(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_PCSSCK_SHIFT))&SPI_CTAR_PCSSCK_MASK)
#define SPI_CTAR_LSBFE_MASK                      0x1000000u
#define SPI_CTAR_LSBFE_SHIFT                     24
#define SPI_CTAR_LSBFE_WIDTH                     1
#define SPI_CTAR_LSBFE(x)                        (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_LSBFE_SHIFT))&SPI_CTAR_LSBFE_MASK)
#define SPI_CTAR_CPHA_MASK                       0x2000000u
#define SPI_CTAR_CPHA_SHIFT                      25
#define SPI_CTAR_CPHA_WIDTH                      1
#define SPI_CTAR_CPHA(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_CPHA_SHIFT))&SPI_CTAR_CPHA_MASK)
#define SPI_CTAR_CPOL_MASK                       0x4000000u
#define SPI_CTAR_CPOL_SHIFT                      26
#define SPI_CTAR_CPOL_WIDTH                      1
#define SPI_CTAR_CPOL(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_CPOL_SHIFT))&SPI_CTAR_CPOL_MASK)
#define SPI_CTAR_FMSZ_MASK                       0x78000000u
#define SPI_CTAR_FMSZ_SHIFT                      27
#define SPI_CTAR_FMSZ_WIDTH                      4
#define SPI_CTAR_FMSZ(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_FMSZ_SHIFT))&SPI_CTAR_FMSZ_MASK)
#define SPI_CTAR_DBR_MASK                        0x80000000u
#define SPI_CTAR_DBR_SHIFT                       31
#define SPI_CTAR_DBR_WIDTH                       1
#define SPI_CTAR_DBR(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_DBR_SHIFT))&SPI_CTAR_DBR_MASK)
// CTAR_SLAVE Bit Fields
#define SPI_CTAR_SLAVE_CPHA_MASK                 0x2000000u
#define SPI_CTAR_SLAVE_CPHA_SHIFT                25
#define SPI_CTAR_SLAVE_CPHA_WIDTH                1
#define SPI_CTAR_SLAVE_CPHA(x)                   (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_SLAVE_CPHA_SHIFT))&SPI_CTAR_SLAVE_CPHA_MASK)
#define SPI_CTAR_SLAVE_CPOL_MASK                 0x4000000u
#define SPI_CTAR_SLAVE_CPOL_SHIFT                26
#define SPI_CTAR_SLAVE_CPOL_WIDTH                1
#define SPI_CTAR_SLAVE_CPOL(x)                   (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_SLAVE_CPOL_SHIFT))&SPI_CTAR_SLAVE_CPOL_MASK)
#define SPI_CTAR_SLAVE_FMSZ_MASK                 0xF8000000u
#define SPI_CTAR_SLAVE_FMSZ_SHIFT                27
#define SPI_CTAR_SLAVE_FMSZ_WIDTH                5
#define SPI_CTAR_SLAVE_FMSZ(x)                   (((uint32_t)(((uint32_t)(x))<<SPI_CTAR_SLAVE_FMSZ_SHIFT))&SPI_CTAR_SLAVE_FMSZ_MASK)
// SR Bit Fields
#define SPI_SR_POPNXTPTR_MASK                    0xFu
#define SPI_SR_POPNXTPTR_SHIFT                   0
#define SPI_SR_POPNXTPTR_WIDTH                   4
#define SPI_SR_POPNXTPTR(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_SR_POPNXTPTR_SHIFT))&SPI_SR_POPNXTPTR_MASK)
#define SPI_SR_RXCTR_MASK                        0xF0u
#define SPI_SR_RXCTR_SHIFT                       4
#define SPI_SR_RXCTR_WIDTH                       4
#define SPI_SR_RXCTR(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_SR_RXCTR_SHIFT))&SPI_SR_RXCTR_MASK)
#define SPI_SR_TXNXTPTR_MASK                     0xF00u
#define SPI_SR_TXNXTPTR_SHIFT                    8
#define SPI_SR_TXNXTPTR_WIDTH                    4
#define SPI_SR_TXNXTPTR(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_SR_TXNXTPTR_SHIFT))&SPI_SR_TXNXTPTR_MASK)
#define SPI_SR_TXCTR_MASK                        0xF000u
#define SPI_SR_TXCTR_SHIFT                       12
#define SPI_SR_TXCTR_WIDTH                       4
#define SPI_SR_TXCTR(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_SR_TXCTR_SHIFT))&SPI_SR_TXCTR_MASK)
#define SPI_SR_RFDF_MASK                         0x20000u
#define SPI_SR_RFDF_SHIFT                        17
#define SPI_SR_RFDF_WIDTH                        1
#define SPI_SR_RFDF(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_SR_RFDF_SHIFT))&SPI_SR_RFDF_MASK)
#define SPI_SR_RFOF_MASK                         0x80000u
#define SPI_SR_RFOF_SHIFT                        19
#define SPI_SR_RFOF_WIDTH                        1
#define SPI_SR_RFOF(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_SR_RFOF_SHIFT))&SPI_SR_RFOF_MASK)
#define SPI_SR_TFFF_MASK                         0x2000000u
#define SPI_SR_TFFF_SHIFT                        25
#define SPI_SR_TFFF_WIDTH                        1
#define SPI_SR_TFFF(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_SR_TFFF_SHIFT))&SPI_SR_TFFF_MASK)
#define SPI_SR_TFUF_MASK                         0x8000000u
#define SPI_SR_TFUF_SHIFT                        27
#define SPI_SR_TFUF_WIDTH                        1
#define SPI_SR_TFUF(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_SR_TFUF_SHIFT))&SPI_SR_TFUF_MASK)
#define SPI_SR_EOQF_MASK                         0x10000000u
#define SPI_SR_EOQF_SHIFT                        28
#define SPI_SR_EOQF_WIDTH                        1
#define SPI_SR_EOQF(x)                           (((uint32_t)(((uint32_t)(x))<<SPI_SR_EOQF_SHIFT))&SPI_SR_EOQF_MASK)
#define SPI_SR_TXRXS_MASK                        0x40000000u
#define SPI_SR_TXRXS_SHIFT                       30
#define SPI_SR_TXRXS_WIDTH                       1
#define SPI_SR_TXRXS(x)                          (((uint32_t)(((uint32_t)(x))<<SPI_SR_TXRXS_SHIFT))&SPI_SR_TXRXS_MASK)
#define SPI_SR_TCF_MASK                          0x80000000u
#define SPI_SR_TCF_SHIFT                         31
#define SPI_SR_TCF_WIDTH                         1
#define SPI_SR_TCF(x)                            (((uint32_t)(((uint32_t)(x))<<SPI_SR_TCF_SHIFT))&SPI_SR_TCF_MASK)
// RSER Bit Fields
#define SPI_RSER_RFDF_DIRS_MASK                  0x10000u
#define SPI_RSER_RFDF_DIRS_SHIFT                 16
#define SPI_RSER_RFDF_DIRS_WIDTH                 1
#define SPI_RSER_RFDF_DIRS(x)                    (((uint32_t)(((uint32_t)(x))<<SPI_RSER_RFDF_DIRS_SHIFT))&SPI_RSER_RFDF_DIRS_MASK)
#define SPI_RSER_RFDF_RE_MASK                    0x20000u
#define SPI_RSER_RFDF_RE_SHIFT                   17
#define SPI_RSER_RFDF_RE_WIDTH                   1
#define SPI_RSER_RFDF_RE(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RSER_RFDF_RE_SHIFT))&SPI_RSER_RFDF_RE_MASK)
#define SPI_RSER_RFOF_RE_MASK                    0x80000u
#define SPI_RSER_RFOF_RE_SHIFT                   19
#define SPI_RSER_RFOF_RE_WIDTH                   1
#define SPI_RSER_RFOF_RE(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RSER_RFOF_RE_SHIFT))&SPI_RSER_RFOF_RE_MASK)
#define SPI_RSER_TFFF_DIRS_MASK                  0x1000000u
#define SPI_RSER_TFFF_DIRS_SHIFT                 24
#define SPI_RSER_TFFF_DIRS_WIDTH                 1
#define SPI_RSER_TFFF_DIRS(x)                    (((uint32_t)(((uint32_t)(x))<<SPI_RSER_TFFF_DIRS_SHIFT))&SPI_RSER_TFFF_DIRS_MASK)
#define SPI_RSER_TFFF_RE_MASK                    0x2000000u
#define SPI_RSER_TFFF_RE_SHIFT                   25
#define SPI_RSER_TFFF_RE_WIDTH                   1
#define SPI_RSER_TFFF_RE(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RSER_TFFF_RE_SHIFT))&SPI_RSER_TFFF_RE_MASK)
#define SPI_RSER_TFUF_RE_MASK                    0x8000000u
#define SPI_RSER_TFUF_RE_SHIFT                   27
#define SPI_RSER_TFUF_RE_WIDTH                   1
#define SPI_RSER_TFUF_RE(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RSER_TFUF_RE_SHIFT))&SPI_RSER_TFUF_RE_MASK)
#define SPI_RSER_EOQF_RE_MASK                    0x10000000u
#define SPI_RSER_EOQF_RE_SHIFT                   28
#define SPI_RSER_EOQF_RE_WIDTH                   1
#define SPI_RSER_EOQF_RE(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RSER_EOQF_RE_SHIFT))&SPI_RSER_EOQF_RE_MASK)
#define SPI_RSER_TCF_RE_MASK                     0x80000000u
#define SPI_RSER_TCF_RE_SHIFT                    31
#define SPI_RSER_TCF_RE_WIDTH                    1
#define SPI_RSER_TCF_RE(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_RSER_TCF_RE_SHIFT))&SPI_RSER_TCF_RE_MASK)
// PUSHR Bit Fields
#define SPI_PUSHR_TXDATA_MASK                    0xFFFFu
#define SPI_PUSHR_TXDATA_SHIFT                   0
#define SPI_PUSHR_TXDATA_WIDTH                   16
#define SPI_PUSHR_TXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_TXDATA_SHIFT))&SPI_PUSHR_TXDATA_MASK)
#define SPI_PUSHR_PCS_MASK                       0x3F0000u
#define SPI_PUSHR_PCS_SHIFT                      16
#define SPI_PUSHR_PCS_WIDTH                      6
#define SPI_PUSHR_PCS(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_PCS_SHIFT))&SPI_PUSHR_PCS_MASK)
#define SPI_PUSHR_CTCNT_MASK                     0x4000000u
#define SPI_PUSHR_CTCNT_SHIFT                    26
#define SPI_PUSHR_CTCNT_WIDTH                    1
#define SPI_PUSHR_CTCNT(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_CTCNT_SHIFT))&SPI_PUSHR_CTCNT_MASK)
#define SPI_PUSHR_EOQ_MASK                       0x8000000u
#define SPI_PUSHR_EOQ_SHIFT                      27
#define SPI_PUSHR_EOQ_WIDTH                      1
#define SPI_PUSHR_EOQ(x)                         (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_EOQ_SHIFT))&SPI_PUSHR_EOQ_MASK)
#define SPI_PUSHR_CTAS_MASK                      0x70000000u
#define SPI_PUSHR_CTAS_SHIFT                     28
#define SPI_PUSHR_CTAS_WIDTH                     3
#define SPI_PUSHR_CTAS(x)                        (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_CTAS_SHIFT))&SPI_PUSHR_CTAS_MASK)
#define SPI_PUSHR_CONT_MASK                      0x80000000u
#define SPI_PUSHR_CONT_SHIFT                     31
#define SPI_PUSHR_CONT_WIDTH                     1
#define SPI_PUSHR_CONT(x)                        (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_CONT_SHIFT))&SPI_PUSHR_CONT_MASK)
// PUSHR_SLAVE Bit Fields
#define SPI_PUSHR_SLAVE_TXDATA_MASK              0xFFFFFFFFu
#define SPI_PUSHR_SLAVE_TXDATA_SHIFT             0
#define SPI_PUSHR_SLAVE_TXDATA_WIDTH             32
#define SPI_PUSHR_SLAVE_TXDATA(x)                (((uint32_t)(((uint32_t)(x))<<SPI_PUSHR_SLAVE_TXDATA_SHIFT))&SPI_PUSHR_SLAVE_TXDATA_MASK)
// POPR Bit Fields
#define SPI_POPR_RXDATA_MASK                     0xFFFFFFFFu
#define SPI_POPR_RXDATA_SHIFT                    0
#define SPI_POPR_RXDATA_WIDTH                    32
#define SPI_POPR_RXDATA(x)                       (((uint32_t)(((uint32_t)(x))<<SPI_POPR_RXDATA_SHIFT))&SPI_POPR_RXDATA_MASK)
// TXFR0 Bit Fields
#define SPI_TXFR0_TXDATA_MASK                    0xFFFFu
#define SPI_TXFR0_TXDATA_SHIFT                   0
#define SPI_TXFR0_TXDATA_WIDTH                   16
#define SPI_TXFR0_TXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_TXFR0_TXDATA_SHIFT))&SPI_TXFR0_TXDATA_MASK)
#define SPI_TXFR0_TXCMD_TXDATA_MASK              0xFFFF0000u
#define SPI_TXFR0_TXCMD_TXDATA_SHIFT             16
#define SPI_TXFR0_TXCMD_TXDATA_WIDTH             16
#define SPI_TXFR0_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x))<<SPI_TXFR0_TXCMD_TXDATA_SHIFT))&SPI_TXFR0_TXCMD_TXDATA_MASK)
// TXFR1 Bit Fields
#define SPI_TXFR1_TXDATA_MASK                    0xFFFFu
#define SPI_TXFR1_TXDATA_SHIFT                   0
#define SPI_TXFR1_TXDATA_WIDTH                   16
#define SPI_TXFR1_TXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_TXFR1_TXDATA_SHIFT))&SPI_TXFR1_TXDATA_MASK)
#define SPI_TXFR1_TXCMD_TXDATA_MASK              0xFFFF0000u
#define SPI_TXFR1_TXCMD_TXDATA_SHIFT             16
#define SPI_TXFR1_TXCMD_TXDATA_WIDTH             16
#define SPI_TXFR1_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x))<<SPI_TXFR1_TXCMD_TXDATA_SHIFT))&SPI_TXFR1_TXCMD_TXDATA_MASK)
// TXFR2 Bit Fields
#define SPI_TXFR2_TXDATA_MASK                    0xFFFFu
#define SPI_TXFR2_TXDATA_SHIFT                   0
#define SPI_TXFR2_TXDATA_WIDTH                   16
#define SPI_TXFR2_TXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_TXFR2_TXDATA_SHIFT))&SPI_TXFR2_TXDATA_MASK)
#define SPI_TXFR2_TXCMD_TXDATA_MASK              0xFFFF0000u
#define SPI_TXFR2_TXCMD_TXDATA_SHIFT             16
#define SPI_TXFR2_TXCMD_TXDATA_WIDTH             16
#define SPI_TXFR2_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x))<<SPI_TXFR2_TXCMD_TXDATA_SHIFT))&SPI_TXFR2_TXCMD_TXDATA_MASK)
// TXFR3 Bit Fields
#define SPI_TXFR3_TXDATA_MASK                    0xFFFFu
#define SPI_TXFR3_TXDATA_SHIFT                   0
#define SPI_TXFR3_TXDATA_WIDTH                   16
#define SPI_TXFR3_TXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_TXFR3_TXDATA_SHIFT))&SPI_TXFR3_TXDATA_MASK)
#define SPI_TXFR3_TXCMD_TXDATA_MASK              0xFFFF0000u
#define SPI_TXFR3_TXCMD_TXDATA_SHIFT             16
#define SPI_TXFR3_TXCMD_TXDATA_WIDTH             16
#define SPI_TXFR3_TXCMD_TXDATA(x)                (((uint32_t)(((uint32_t)(x))<<SPI_TXFR3_TXCMD_TXDATA_SHIFT))&SPI_TXFR3_TXCMD_TXDATA_MASK)
// RXFR0 Bit Fields
#define SPI_RXFR0_RXDATA_MASK                    0xFFFFFFFFu
#define SPI_RXFR0_RXDATA_SHIFT                   0
#define SPI_RXFR0_RXDATA_WIDTH                   32
#define SPI_RXFR0_RXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RXFR0_RXDATA_SHIFT))&SPI_RXFR0_RXDATA_MASK)
// RXFR1 Bit Fields
#define SPI_RXFR1_RXDATA_MASK                    0xFFFFFFFFu
#define SPI_RXFR1_RXDATA_SHIFT                   0
#define SPI_RXFR1_RXDATA_WIDTH                   32
#define SPI_RXFR1_RXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RXFR1_RXDATA_SHIFT))&SPI_RXFR1_RXDATA_MASK)
// RXFR2 Bit Fields
#define SPI_RXFR2_RXDATA_MASK                    0xFFFFFFFFu
#define SPI_RXFR2_RXDATA_SHIFT                   0
#define SPI_RXFR2_RXDATA_WIDTH                   32
#define SPI_RXFR2_RXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RXFR2_RXDATA_SHIFT))&SPI_RXFR2_RXDATA_MASK)
// RXFR3 Bit Fields
#define SPI_RXFR3_RXDATA_MASK                    0xFFFFFFFFu
#define SPI_RXFR3_RXDATA_SHIFT                   0
#define SPI_RXFR3_RXDATA_WIDTH                   32
#define SPI_RXFR3_RXDATA(x)                      (((uint32_t)(((uint32_t)(x))<<SPI_RXFR3_RXDATA_SHIFT))&SPI_RXFR3_RXDATA_MASK)

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// Error codes for the DSPI driver.
typedef enum _dspi_status
{
    kStatus_DSPI_Success = 0,
    // DSPI Slave Tx Under run error
    kStatus_DSPI_SlaveTxUnderrun,
    // DSPI Slave Rx Overrun error
    kStatus_DSPI_SlaveRxOverrun,
    // DSPI transfer timed out
    kStatus_DSPI_Timeout,
    // DSPI instance is already busy performing a transfer.
    kStatus_DSPI_Busy,
    // Attempt to abort a transfer when no transfer was in progress
    kStatus_DSPI_NoTransferInProgress,
    // Bits-per-frame value not valid
    kStatus_DSPI_InvalidBitCount,
    // DSPI instance number does not match current count
    kStatus_DSPI_InvalidInstanceNumber,
    // DSPI out-of-range error
    kStatus_DSPI_OutOfRange,
    // DSPI invalid parameter error
    kStatus_DSPI_InvalidParameter,
    // DSPI driver does not initialize, not ready
    kStatus_DSPI_NonInit,
    // DSPI driver has initialized, cannot re-initialize
    kStatus_DSPI_Initialized,
    // DSPI driver could not request DMA channel(s)
    kStatus_DSPI_DMAChannelInvalid,
    // DSPI driver error
    kStatus_DSPI_Error,
    // DSPI Edma driver STCD unaligned to 32byte error
    kStatus_DSPI_EdmaStcdUnaligned32Error
} dspi_status_t;

// DSPI master or slave configuration
typedef enum _dspi_master_slave_mode {
    kDspiMaster = 1,     // DSPI peripheral operates in master mode
    kDspiSlave = 0       // DSPI peripheral operates in slave mode
} dspi_master_slave_mode_t;

// DSPI clock polarity configuration for a given CTAR
typedef enum _dspi_clock_polarity {
    kDspiClockPolarity_ActiveHigh = 0,   // Active-high DSPI clock (idles low)
    kDspiClockPolarity_ActiveLow = 1     // Active-low DSPI clock (idles high)
} dspi_clock_polarity_t;

// DSPI clock phase configuration for a given CTAR
typedef enum _dspi_clock_phase {
    // Data is captured on the leading edge of the SCK
    // and changed on the following edge.
    kDspiClockPhase_FirstEdge = 0,
    // Data is changed on the leading edge of the SCK
    // and captured on the following edge.
    kDspiClockPhase_SecondEdge = 1
} dspi_clock_phase_t;

// DSPI data shifter direction options for a given CTAR
typedef enum _dspi_shift_direction {
    kDspiMsbFirst = 0,   // Data transfers start with most significant bit.
    kDspiLsbFirst = 1    // Data transfers start with least significant bit.
} dspi_shift_direction_t;

// DSPI Clock and Transfer Attributes Register (CTAR) selection
typedef enum _dspi_ctar_selection {
    // CTAR0 selection option for master or slave mode
    kDspiCtar0 = 0,
    // CTAR1 selection option for master mode only
    kDspiCtar1 = 1
} dspi_ctar_selection_t;

// DSPI Peripheral Chip Select (PCS) Polarity configuration.
typedef enum _dspi_pcs_polarity_config {
    // PCS Active High (idles low)
    kDspiPcs_ActiveHigh = 0,
    // PCS Active Low (idles high)
    kDspiPcs_ActiveLow  = 1
} dspi_pcs_polarity_config_t;

// DSPI Peripheral Chip Select (PCS) configuration (which PCS to configure)
typedef enum _dspi_which_pcs_config {
    // PCS[0]
    kDspiPcs0 = 1 << 0,
    // PCS[1]
    kDspiPcs1 = 1 << 1,
    // PCS[2]
    kDspiPcs2 = 1 << 2,
    // PCS[3]
    kDspiPcs3 = 1 << 3,
    // PCS[4]
    kDspiPcs4 = 1 << 4,
    // PCS[5]
    kDspiPcs5 = 1 << 5
} dspi_which_pcs_config_t;

// DSPI Sample Point:
// Controls when the DSPI master samples SIN in Modified Transfer Format.
// This field is valid only when CPHA bit in CTAR register is 0.
typedef enum _dspi_master_sample_point {
    // 0 system clocks between SCK edge and SIN sample
    kDspiSckToSin_0Clock = 0,
    // 1 system clock between SCK edge and SIN sample
    kDspiSckToSin_1Clock = 1,
    // 2 system clocks between SCK edge and SIN sample
    kDspiSckToSin_2Clock = 2
} dspi_master_sample_point_t;

// DSPI Tx FIFO Fill and Rx FIFO Drain DMA or Interrupt configuration
typedef enum _dspi_dma_or_int_mode {
    kDspiGenerateIntReq = 0, // Desired flag generates an Interrupt request
    kDspiGenerateDmaReq = 1  // Desired flag generates a DMA request
} dspi_dma_or_int_mode_t;

// DSPI status flags and interrupt request enable
typedef enum _dspi_status_and_interrupt_request {
    // TCF status/interrupt enable
    kDspiTxComplete = SPI_RSER_TCF_RE_SHIFT,
    // TXRXS status only, no interrupt
    kDspiTxAndRxStatus = SPI_SR_TXRXS_SHIFT,
    // EOQF status/interrupt enable
    kDspiEndOfQueue = SPI_RSER_EOQF_RE_SHIFT,
    // TFUF status/interrupt enable
    kDspiTxFifoUnderflow = SPI_RSER_TFUF_RE_SHIFT,
    // TFFF status/interrupt enable
    kDspiTxFifoFillRequest = SPI_RSER_TFFF_RE_SHIFT,
    // RFOF status/interrupt enable
    kDspiRxFifoOverflow = SPI_RSER_RFOF_RE_SHIFT,
    // RFDF status/interrupt enable
    kDspiRxFifoDrainRequest = SPI_RSER_RFDF_RE_SHIFT
} dspi_status_and_interrupt_request_t;

// DSPI delay type selection
typedef enum _dspi_delay_type {
    // PCS-to-SCK delay
    kDspiPcsToSck = 1,
    // Last SCK edge to PCS delay
    kDspiLastSckToPcs = 2,
    // Delay between transfers
    kDspiAfterTransfer = 3,
} dspi_delay_type_t;

// DSPI data format settings configuration structure
typedef struct DspiDataFormatConfig {
    // Bits per frame, minimum 4, maximum 16
    uint32_t bitsPerFrame;
    // Active high or low clock polarity
    dspi_clock_polarity_t clkPolarity;
    // Clock phase setting to change and capture data
    dspi_clock_phase_t clkPhase;
    // MSB or LSB data shift direction. This setting relevant
    // only in master mode and can be ignored in slave  mode.
    dspi_shift_direction_t direction;
} dspi_data_format_config_t;

// DSPI baud rate divisors settings configuration structure.
typedef struct DspiBaudRateDivisors {
    bool doubleBaudRate;          // Double Baud rate parameter setting
    uint32_t prescaleDivisor;     // Baud Rate Pre-scaler parameter setting
    uint32_t baudRateDivisor;     // Baud Rate scaler parameter setting
} dspi_baud_rate_divisors_t;

// DSPI command and data configuration structure
typedef struct DspiCommandDataConfig {
    // Option to enable the continuous assertion of chip select
    // between transfers
    bool isChipSelectContinuous;
    // The desired Clock and Transfer Attributes Register (CTAR) to use for CTAS
    dspi_ctar_selection_t whichCtar;
    // The desired PCS signal to use for the data transfer
    dspi_which_pcs_config_t whichPcs;
    // Signals that the current transfer is the last in the queue
    bool isEndOfQueue;
    // Clears SPI_TCNT field; cleared before transmission starts
    bool clearTransferCount;
} dspi_command_config_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Defines constant value arrays
// for the baud rate pre-scalar and scalar divider values.
static const uint32_t s_baudratePrescaler[] = { 2, 3, 5, 7 };
static const uint32_t s_baudrateScaler[] = { 2, 4, 6, 8, 16, 32, 64, 128, 256,
    512, 1024, 2048, 4096, 8192, 16384, 32768 };

static const uint32_t s_delayPrescaler[] = { 1, 3, 5, 7 };
static const uint32_t s_delayScaler[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512,
    1024, 2048, 4096, 8192, 16384, 32768, 65536 };

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Configuration

// Restores the DSPI to reset the configuration.
void DSPI_HAL_Init( uint32_t* base );

// Enables the DSPI peripheral and sets the MCR MDIS to 0.
void DSPI_HAL_Enable( uint32_t* base );

// Disables the DSPI peripheral, sets MCR MDIS to 1.
void DSPI_HAL_Disable( uint32_t* base );

// Sets the DSPI baud rate in bits per second.
uint32_t DSPI_HAL_SetBaudRate( uint32_t* base, dspi_ctar_selection_t whichCtar,
    uint32_t bitsPerSec, uint32_t sourceClockInHz );
    
// Configures the baud rate divisors manually.
void DSPI_HAL_SetBaudDivisors( uint32_t* base, dspi_ctar_selection_t whichCtar,
    const dspi_baud_rate_divisors_t * divisors );
    
// Configures the DSPI for master or slave.
void DSPI_HAL_SetMasterSlaveMode(
    uint32_t* base, dspi_master_slave_mode_t mode );
    
// Returns whether the DSPI module is in master mode.
bool DSPI_HAL_IsMaster( uint32_t* base );

// Configures the DSPI for the continuous SCK operation.
void DSPI_HAL_SetContinuousSckCmd( uint32_t* base, bool enable );

// Configures the DSPI peripheral chip select strobe enable.
// Configures the PCS[5] to be the active-low PCS Strobe output.
void DSPI_HAL_SetPcsStrobeCmd( uint32_t* base, bool enable );

// Configures the DSPI received FIFO overflow overwrite enable.
void DSPI_HAL_SetRxFifoOverwriteCmd( uint32_t* base, bool enable );

// Configures the DSPI peripheral chip select polarity.
void DSPI_HAL_SetPcsPolarityMode( uint32_t* base, dspi_which_pcs_config_t pcs,
    dspi_pcs_polarity_config_t activeLowOrHigh );

// Enables (or disables) the DSPI FIFOs.
void DSPI_HAL_SetFifoCmd(
    uint32_t* base, bool enableTxFifo, bool enableRxFifo );
    
// Flushes the DSPI FIFOs.
void DSPI_HAL_SetFlushFifoCmd( uint32_t* base,
    bool enableFlushTxFifo, bool enableFlushRxFifo );
    
// Configures the time when the DSPI master samples SIN
// in the Modified Transfer Format.
void DSPI_HAL_SetDatainSamplepointMode( uint32_t* base,
    dspi_master_sample_point_t samplePnt );
    
// Starts the DSPI transfers, clears HALT bit in MCR.
void DSPI_HAL_StartTransfer( uint32_t* base );

// Stops (halts) DSPI transfers, sets HALT bit in MCR.
void DSPI_HAL_StopTransfer( uint32_t* base );

// Configures the data format for a particular CTAR.
dspi_status_t DSPI_HAL_SetDataFormat( uint32_t* base,
    dspi_ctar_selection_t whichCtar, const dspi_data_format_config_t * config );
    
// Manually configures the delay prescaler and scaler for a particular CTAR.
void DSPI_HAL_SetDelay( uint32_t* base, dspi_ctar_selection_t whichCtar,
    uint32_t prescaler, uint32_t scaler, dspi_delay_type_t whichDelay );
    
// Calculates the delay prescaler and scaler
// based on the desired delay input in nanoseconds.
uint32_t DSPI_HAL_CalculateDelay( uint32_t* base,
    dspi_ctar_selection_t whichCtar, dspi_delay_type_t whichDelay,
    uint32_t sourceClockInHz, uint32_t delayInNanoSec );

// Gets the DSPI master PUSHR data register address for DMA operation.
uint32_t DSPI_HAL_GetMasterPushrRegAddr( uint32_t* base );

// Gets the DSPI slave PUSHR data register address for DMA operation.
uint32_t DSPI_HAL_GetSlavePushrRegAddr( uint32_t* base );

// Gets the DSPI POPR data register address for DMA operation.
uint32_t DSPI_HAL_GetPoprRegAddr( uint32_t* base );

// Interrupts

// Configures the DSPI Tx FIFO fill request
// to generate DMA or interrupt requests.
void DSPI_HAL_SetTxFifoFillDmaIntMode( uint32_t* base,
    dspi_dma_or_int_mode_t mode, bool enable );
    
// Configures the DSPI Rx FIFO drain request
// to generate DMA or interrupt requests.
void DSPI_HAL_SetRxFifoDrainDmaIntMode( uint32_t* base,
    dspi_dma_or_int_mode_t mode, bool enable );

// Configures the DSPI interrupts.
void DSPI_HAL_SetIntMode( uint32_t* base,
    dspi_status_and_interrupt_request_t interruptSrc, bool enable );

// Gets DSPI interrupt configuration,
// returns if interrupt request is enabled or disabled.
bool DSPI_HAL_GetIntMode( uint32_t * base,
    dspi_status_and_interrupt_request_t interruptSrc );
    
// Status

// Gets the DSPI status flag state.
bool DSPI_HAL_GetStatusFlag( uint32_t* base,
    dspi_status_and_interrupt_request_t statusFlag );

// Clears the DSPI status flag.
void DSPI_HAL_ClearStatusFlag( uint32_t* base,
    dspi_status_and_interrupt_request_t statusFlag );

// Data transfer

// Reads data from the data buffer.
uint32_t DSPI_HAL_ReadData( uint32_t* base );

// Writes data into the data buffer, slave mode.
void DSPI_HAL_WriteDataSlavemode( uint32_t* base, uint32_t _data );

// Writes data into the data buffer, slave mode
// and waits till data was transmitted and return.
void DSPI_HAL_WriteDataSlavemodeBlocking( uint32_t* base, uint32_t _data );

// Writes data into the data buffer, master mode.
void DSPI_HAL_WriteDataMastermode( uint32_t* base,
    dspi_command_config_t* command, uint16_t _data );

// Writes data into the data buffer, master mode
// and waits till complete to return.
void DSPI_HAL_WriteDataMastermodeBlocking( uint32_t* base,
    dspi_command_config_t* command, uint16_t _data );

// Writes a 32-bit data word (16-bit command appended with 16-bit data)
// into the data buffer, master mode.
void DSPI_HAL_WriteCmdDataMastermode( uint32_t* base, uint32_t _data );

// Writes a 32-bit data word (16-bit command appended with 16-bit data)
// into the data buffer, master mode and waits till complete to return.
void DSPI_HAL_WriteCmdDataMastermodeBlocking( uint32_t* base, uint32_t _data );

// Gets the transfer count.
uint32_t DSPI_HAL_GetTransferCount( uint32_t* base );

// Pre-sets the transfer count.
void DSPI_HAL_PresetTransferCount( uint32_t* base, uint16_t presetValue );

// Returns the DSPI command word formatted to the PUSHR data register bit field.
uint32_t DSPI_HAL_GetFormattedCommand( uint32_t* base,
    dspi_command_config_t* command );

#endif