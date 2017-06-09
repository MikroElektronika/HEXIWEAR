// File: edma_hal.c

// Definitions of main functionalities in the eDMA HAL module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "edma_hal.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

// CR Bit Fields
#define DMA_CR_EDBG_MASK                         0x2u
#define DMA_CR_EDBG_SHIFT                        1
#define DMA_CR_EDBG_WIDTH                        1
#define DMA_CR_EDBG(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_CR_EDBG_SHIFT))&DMA_CR_EDBG_MASK)
#define DMA_CR_ERCA_MASK                         0x4u
#define DMA_CR_ERCA_SHIFT                        2
#define DMA_CR_ERCA_WIDTH                        1
#define DMA_CR_ERCA(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_CR_ERCA_SHIFT))&DMA_CR_ERCA_MASK)
#define DMA_CR_HOE_MASK                          0x10u
#define DMA_CR_HOE_SHIFT                         4
#define DMA_CR_HOE_WIDTH                         1
#define DMA_CR_HOE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_CR_HOE_SHIFT))&DMA_CR_HOE_MASK)
#define DMA_CR_HALT_MASK                         0x20u
#define DMA_CR_HALT_SHIFT                        5
#define DMA_CR_HALT_WIDTH                        1
#define DMA_CR_HALT(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_CR_HALT_SHIFT))&DMA_CR_HALT_MASK)
#define DMA_CR_CLM_MASK                          0x40u
#define DMA_CR_CLM_SHIFT                         6
#define DMA_CR_CLM_WIDTH                         1
#define DMA_CR_CLM(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_CR_CLM_SHIFT))&DMA_CR_CLM_MASK)
#define DMA_CR_EMLM_MASK                         0x80u
#define DMA_CR_EMLM_SHIFT                        7
#define DMA_CR_EMLM_WIDTH                        1
#define DMA_CR_EMLM(x)                           (((uint32_t)(((uint32_t)(x))<<DMA_CR_EMLM_SHIFT))&DMA_CR_EMLM_MASK)
#define DMA_CR_ECX_MASK                          0x10000u
#define DMA_CR_ECX_SHIFT                         16
#define DMA_CR_ECX_WIDTH                         1
#define DMA_CR_ECX(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_CR_ECX_SHIFT))&DMA_CR_ECX_MASK)
#define DMA_CR_CX_MASK                           0x20000u
#define DMA_CR_CX_SHIFT                          17
#define DMA_CR_CX_WIDTH                          1
#define DMA_CR_CX(x)                             (((uint32_t)(((uint32_t)(x))<<DMA_CR_CX_SHIFT))&DMA_CR_CX_MASK)
// ES Bit Fields
#define DMA_ES_DBE_MASK                          0x1u
#define DMA_ES_DBE_SHIFT                         0
#define DMA_ES_DBE_WIDTH                         1
#define DMA_ES_DBE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_DBE_SHIFT))&DMA_ES_DBE_MASK)
#define DMA_ES_SBE_MASK                          0x2u
#define DMA_ES_SBE_SHIFT                         1
#define DMA_ES_SBE_WIDTH                         1
#define DMA_ES_SBE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_SBE_SHIFT))&DMA_ES_SBE_MASK)
#define DMA_ES_SGE_MASK                          0x4u
#define DMA_ES_SGE_SHIFT                         2
#define DMA_ES_SGE_WIDTH                         1
#define DMA_ES_SGE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_SGE_SHIFT))&DMA_ES_SGE_MASK)
#define DMA_ES_NCE_MASK                          0x8u
#define DMA_ES_NCE_SHIFT                         3
#define DMA_ES_NCE_WIDTH                         1
#define DMA_ES_NCE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_NCE_SHIFT))&DMA_ES_NCE_MASK)
#define DMA_ES_DOE_MASK                          0x10u
#define DMA_ES_DOE_SHIFT                         4
#define DMA_ES_DOE_WIDTH                         1
#define DMA_ES_DOE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_DOE_SHIFT))&DMA_ES_DOE_MASK)
#define DMA_ES_DAE_MASK                          0x20u
#define DMA_ES_DAE_SHIFT                         5
#define DMA_ES_DAE_WIDTH                         1
#define DMA_ES_DAE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_DAE_SHIFT))&DMA_ES_DAE_MASK)
#define DMA_ES_SOE_MASK                          0x40u
#define DMA_ES_SOE_SHIFT                         6
#define DMA_ES_SOE_WIDTH                         1
#define DMA_ES_SOE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_SOE_SHIFT))&DMA_ES_SOE_MASK)
#define DMA_ES_SAE_MASK                          0x80u
#define DMA_ES_SAE_SHIFT                         7
#define DMA_ES_SAE_WIDTH                         1
#define DMA_ES_SAE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_SAE_SHIFT))&DMA_ES_SAE_MASK)
#define DMA_ES_ERRCHN_MASK                       0xF00u
#define DMA_ES_ERRCHN_SHIFT                      8
#define DMA_ES_ERRCHN_WIDTH                      4
#define DMA_ES_ERRCHN(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ES_ERRCHN_SHIFT))&DMA_ES_ERRCHN_MASK)
#define DMA_ES_CPE_MASK                          0x4000u
#define DMA_ES_CPE_SHIFT                         14
#define DMA_ES_CPE_WIDTH                         1
#define DMA_ES_CPE(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_CPE_SHIFT))&DMA_ES_CPE_MASK)
#define DMA_ES_ECX_MASK                          0x10000u
#define DMA_ES_ECX_SHIFT                         16
#define DMA_ES_ECX_WIDTH                         1
#define DMA_ES_ECX(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_ECX_SHIFT))&DMA_ES_ECX_MASK)
#define DMA_ES_VLD_MASK                          0x80000000u
#define DMA_ES_VLD_SHIFT                         31
#define DMA_ES_VLD_WIDTH                         1
#define DMA_ES_VLD(x)                            (((uint32_t)(((uint32_t)(x))<<DMA_ES_VLD_SHIFT))&DMA_ES_VLD_MASK)
// ERQ Bit Fields
#define DMA_ERQ_ERQ0_MASK                        0x1u
#define DMA_ERQ_ERQ0_SHIFT                       0
#define DMA_ERQ_ERQ0_WIDTH                       1
#define DMA_ERQ_ERQ0(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ0_SHIFT))&DMA_ERQ_ERQ0_MASK)
#define DMA_ERQ_ERQ1_MASK                        0x2u
#define DMA_ERQ_ERQ1_SHIFT                       1
#define DMA_ERQ_ERQ1_WIDTH                       1
#define DMA_ERQ_ERQ1(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ1_SHIFT))&DMA_ERQ_ERQ1_MASK)
#define DMA_ERQ_ERQ2_MASK                        0x4u
#define DMA_ERQ_ERQ2_SHIFT                       2
#define DMA_ERQ_ERQ2_WIDTH                       1
#define DMA_ERQ_ERQ2(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ2_SHIFT))&DMA_ERQ_ERQ2_MASK)
#define DMA_ERQ_ERQ3_MASK                        0x8u
#define DMA_ERQ_ERQ3_SHIFT                       3
#define DMA_ERQ_ERQ3_WIDTH                       1
#define DMA_ERQ_ERQ3(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ3_SHIFT))&DMA_ERQ_ERQ3_MASK)
#define DMA_ERQ_ERQ4_MASK                        0x10u
#define DMA_ERQ_ERQ4_SHIFT                       4
#define DMA_ERQ_ERQ4_WIDTH                       1
#define DMA_ERQ_ERQ4(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ4_SHIFT))&DMA_ERQ_ERQ4_MASK)
#define DMA_ERQ_ERQ5_MASK                        0x20u
#define DMA_ERQ_ERQ5_SHIFT                       5
#define DMA_ERQ_ERQ5_WIDTH                       1
#define DMA_ERQ_ERQ5(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ5_SHIFT))&DMA_ERQ_ERQ5_MASK)
#define DMA_ERQ_ERQ6_MASK                        0x40u
#define DMA_ERQ_ERQ6_SHIFT                       6
#define DMA_ERQ_ERQ6_WIDTH                       1
#define DMA_ERQ_ERQ6(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ6_SHIFT))&DMA_ERQ_ERQ6_MASK)
#define DMA_ERQ_ERQ7_MASK                        0x80u
#define DMA_ERQ_ERQ7_SHIFT                       7
#define DMA_ERQ_ERQ7_WIDTH                       1
#define DMA_ERQ_ERQ7(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ7_SHIFT))&DMA_ERQ_ERQ7_MASK)
#define DMA_ERQ_ERQ8_MASK                        0x100u
#define DMA_ERQ_ERQ8_SHIFT                       8
#define DMA_ERQ_ERQ8_WIDTH                       1
#define DMA_ERQ_ERQ8(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ8_SHIFT))&DMA_ERQ_ERQ8_MASK)
#define DMA_ERQ_ERQ9_MASK                        0x200u
#define DMA_ERQ_ERQ9_SHIFT                       9
#define DMA_ERQ_ERQ9_WIDTH                       1
#define DMA_ERQ_ERQ9(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ9_SHIFT))&DMA_ERQ_ERQ9_MASK)
#define DMA_ERQ_ERQ10_MASK                       0x400u
#define DMA_ERQ_ERQ10_SHIFT                      10
#define DMA_ERQ_ERQ10_WIDTH                      1
#define DMA_ERQ_ERQ10(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ10_SHIFT))&DMA_ERQ_ERQ10_MASK)
#define DMA_ERQ_ERQ11_MASK                       0x800u
#define DMA_ERQ_ERQ11_SHIFT                      11
#define DMA_ERQ_ERQ11_WIDTH                      1
#define DMA_ERQ_ERQ11(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ11_SHIFT))&DMA_ERQ_ERQ11_MASK)
#define DMA_ERQ_ERQ12_MASK                       0x1000u
#define DMA_ERQ_ERQ12_SHIFT                      12
#define DMA_ERQ_ERQ12_WIDTH                      1
#define DMA_ERQ_ERQ12(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ12_SHIFT))&DMA_ERQ_ERQ12_MASK)
#define DMA_ERQ_ERQ13_MASK                       0x2000u
#define DMA_ERQ_ERQ13_SHIFT                      13
#define DMA_ERQ_ERQ13_WIDTH                      1
#define DMA_ERQ_ERQ13(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ13_SHIFT))&DMA_ERQ_ERQ13_MASK)
#define DMA_ERQ_ERQ14_MASK                       0x4000u
#define DMA_ERQ_ERQ14_SHIFT                      14
#define DMA_ERQ_ERQ14_WIDTH                      1
#define DMA_ERQ_ERQ14(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ14_SHIFT))&DMA_ERQ_ERQ14_MASK)
#define DMA_ERQ_ERQ15_MASK                       0x8000u
#define DMA_ERQ_ERQ15_SHIFT                      15
#define DMA_ERQ_ERQ15_WIDTH                      1
#define DMA_ERQ_ERQ15(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERQ_ERQ15_SHIFT))&DMA_ERQ_ERQ15_MASK)
// EEI Bit Fields
#define DMA_EEI_EEI0_MASK                        0x1u
#define DMA_EEI_EEI0_SHIFT                       0
#define DMA_EEI_EEI0_WIDTH                       1
#define DMA_EEI_EEI0(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI0_SHIFT))&DMA_EEI_EEI0_MASK)
#define DMA_EEI_EEI1_MASK                        0x2u
#define DMA_EEI_EEI1_SHIFT                       1
#define DMA_EEI_EEI1_WIDTH                       1
#define DMA_EEI_EEI1(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI1_SHIFT))&DMA_EEI_EEI1_MASK)
#define DMA_EEI_EEI2_MASK                        0x4u
#define DMA_EEI_EEI2_SHIFT                       2
#define DMA_EEI_EEI2_WIDTH                       1
#define DMA_EEI_EEI2(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI2_SHIFT))&DMA_EEI_EEI2_MASK)
#define DMA_EEI_EEI3_MASK                        0x8u
#define DMA_EEI_EEI3_SHIFT                       3
#define DMA_EEI_EEI3_WIDTH                       1
#define DMA_EEI_EEI3(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI3_SHIFT))&DMA_EEI_EEI3_MASK)
#define DMA_EEI_EEI4_MASK                        0x10u
#define DMA_EEI_EEI4_SHIFT                       4
#define DMA_EEI_EEI4_WIDTH                       1
#define DMA_EEI_EEI4(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI4_SHIFT))&DMA_EEI_EEI4_MASK)
#define DMA_EEI_EEI5_MASK                        0x20u
#define DMA_EEI_EEI5_SHIFT                       5
#define DMA_EEI_EEI5_WIDTH                       1
#define DMA_EEI_EEI5(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI5_SHIFT))&DMA_EEI_EEI5_MASK)
#define DMA_EEI_EEI6_MASK                        0x40u
#define DMA_EEI_EEI6_SHIFT                       6
#define DMA_EEI_EEI6_WIDTH                       1
#define DMA_EEI_EEI6(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI6_SHIFT))&DMA_EEI_EEI6_MASK)
#define DMA_EEI_EEI7_MASK                        0x80u
#define DMA_EEI_EEI7_SHIFT                       7
#define DMA_EEI_EEI7_WIDTH                       1
#define DMA_EEI_EEI7(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI7_SHIFT))&DMA_EEI_EEI7_MASK)
#define DMA_EEI_EEI8_MASK                        0x100u
#define DMA_EEI_EEI8_SHIFT                       8
#define DMA_EEI_EEI8_WIDTH                       1
#define DMA_EEI_EEI8(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI8_SHIFT))&DMA_EEI_EEI8_MASK)
#define DMA_EEI_EEI9_MASK                        0x200u
#define DMA_EEI_EEI9_SHIFT                       9
#define DMA_EEI_EEI9_WIDTH                       1
#define DMA_EEI_EEI9(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI9_SHIFT))&DMA_EEI_EEI9_MASK)
#define DMA_EEI_EEI10_MASK                       0x400u
#define DMA_EEI_EEI10_SHIFT                      10
#define DMA_EEI_EEI10_WIDTH                      1
#define DMA_EEI_EEI10(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI10_SHIFT))&DMA_EEI_EEI10_MASK)
#define DMA_EEI_EEI11_MASK                       0x800u
#define DMA_EEI_EEI11_SHIFT                      11
#define DMA_EEI_EEI11_WIDTH                      1
#define DMA_EEI_EEI11(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI11_SHIFT))&DMA_EEI_EEI11_MASK)
#define DMA_EEI_EEI12_MASK                       0x1000u
#define DMA_EEI_EEI12_SHIFT                      12
#define DMA_EEI_EEI12_WIDTH                      1
#define DMA_EEI_EEI12(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI12_SHIFT))&DMA_EEI_EEI12_MASK)
#define DMA_EEI_EEI13_MASK                       0x2000u
#define DMA_EEI_EEI13_SHIFT                      13
#define DMA_EEI_EEI13_WIDTH                      1
#define DMA_EEI_EEI13(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI13_SHIFT))&DMA_EEI_EEI13_MASK)
#define DMA_EEI_EEI14_MASK                       0x4000u
#define DMA_EEI_EEI14_SHIFT                      14
#define DMA_EEI_EEI14_WIDTH                      1
#define DMA_EEI_EEI14(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI14_SHIFT))&DMA_EEI_EEI14_MASK)
#define DMA_EEI_EEI15_MASK                       0x8000u
#define DMA_EEI_EEI15_SHIFT                      15
#define DMA_EEI_EEI15_WIDTH                      1
#define DMA_EEI_EEI15(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_EEI_EEI15_SHIFT))&DMA_EEI_EEI15_MASK)
// CEEI Bit Fields
#define DMA_CEEI_CEEI_MASK                       0xFu
#define DMA_CEEI_CEEI_SHIFT                      0
#define DMA_CEEI_CEEI_WIDTH                      4
#define DMA_CEEI_CEEI(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CEEI_CEEI_SHIFT))&DMA_CEEI_CEEI_MASK)
#define DMA_CEEI_CAEE_MASK                       0x40u
#define DMA_CEEI_CAEE_SHIFT                      6
#define DMA_CEEI_CAEE_WIDTH                      1
#define DMA_CEEI_CAEE(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CEEI_CAEE_SHIFT))&DMA_CEEI_CAEE_MASK)
#define DMA_CEEI_NOP_MASK                        0x80u
#define DMA_CEEI_NOP_SHIFT                       7
#define DMA_CEEI_NOP_WIDTH                       1
#define DMA_CEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_CEEI_NOP_SHIFT))&DMA_CEEI_NOP_MASK)
// SEEI Bit Fields
#define DMA_SEEI_SEEI_MASK                       0xFu
#define DMA_SEEI_SEEI_SHIFT                      0
#define DMA_SEEI_SEEI_WIDTH                      4
#define DMA_SEEI_SEEI(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_SEEI_SEEI_SHIFT))&DMA_SEEI_SEEI_MASK)
#define DMA_SEEI_SAEE_MASK                       0x40u
#define DMA_SEEI_SAEE_SHIFT                      6
#define DMA_SEEI_SAEE_WIDTH                      1
#define DMA_SEEI_SAEE(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_SEEI_SAEE_SHIFT))&DMA_SEEI_SAEE_MASK)
#define DMA_SEEI_NOP_MASK                        0x80u
#define DMA_SEEI_NOP_SHIFT                       7
#define DMA_SEEI_NOP_WIDTH                       1
#define DMA_SEEI_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_SEEI_NOP_SHIFT))&DMA_SEEI_NOP_MASK)
// CERQ Bit Fields
#define DMA_CERQ_CERQ_MASK                       0xFu
#define DMA_CERQ_CERQ_SHIFT                      0
#define DMA_CERQ_CERQ_WIDTH                      4
#define DMA_CERQ_CERQ(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CERQ_CERQ_SHIFT))&DMA_CERQ_CERQ_MASK)
#define DMA_CERQ_CAER_MASK                       0x40u
#define DMA_CERQ_CAER_SHIFT                      6
#define DMA_CERQ_CAER_WIDTH                      1
#define DMA_CERQ_CAER(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CERQ_CAER_SHIFT))&DMA_CERQ_CAER_MASK)
#define DMA_CERQ_NOP_MASK                        0x80u
#define DMA_CERQ_NOP_SHIFT                       7
#define DMA_CERQ_NOP_WIDTH                       1
#define DMA_CERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_CERQ_NOP_SHIFT))&DMA_CERQ_NOP_MASK)
// SERQ Bit Fields
#define DMA_SERQ_SERQ_MASK                       0xFu
#define DMA_SERQ_SERQ_SHIFT                      0
#define DMA_SERQ_SERQ_WIDTH                      4
#define DMA_SERQ_SERQ(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_SERQ_SERQ_SHIFT))&DMA_SERQ_SERQ_MASK)
#define DMA_SERQ_SAER_MASK                       0x40u
#define DMA_SERQ_SAER_SHIFT                      6
#define DMA_SERQ_SAER_WIDTH                      1
#define DMA_SERQ_SAER(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_SERQ_SAER_SHIFT))&DMA_SERQ_SAER_MASK)
#define DMA_SERQ_NOP_MASK                        0x80u
#define DMA_SERQ_NOP_SHIFT                       7
#define DMA_SERQ_NOP_WIDTH                       1
#define DMA_SERQ_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_SERQ_NOP_SHIFT))&DMA_SERQ_NOP_MASK)
// CDNE Bit Fields
#define DMA_CDNE_CDNE_MASK                       0xFu
#define DMA_CDNE_CDNE_SHIFT                      0
#define DMA_CDNE_CDNE_WIDTH                      4
#define DMA_CDNE_CDNE(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CDNE_CDNE_SHIFT))&DMA_CDNE_CDNE_MASK)
#define DMA_CDNE_CADN_MASK                       0x40u
#define DMA_CDNE_CADN_SHIFT                      6
#define DMA_CDNE_CADN_WIDTH                      1
#define DMA_CDNE_CADN(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CDNE_CADN_SHIFT))&DMA_CDNE_CADN_MASK)
#define DMA_CDNE_NOP_MASK                        0x80u
#define DMA_CDNE_NOP_SHIFT                       7
#define DMA_CDNE_NOP_WIDTH                       1
#define DMA_CDNE_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_CDNE_NOP_SHIFT))&DMA_CDNE_NOP_MASK)
// SSRT Bit Fields
#define DMA_SSRT_SSRT_MASK                       0xFu
#define DMA_SSRT_SSRT_SHIFT                      0
#define DMA_SSRT_SSRT_WIDTH                      4
#define DMA_SSRT_SSRT(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_SSRT_SSRT_SHIFT))&DMA_SSRT_SSRT_MASK)
#define DMA_SSRT_SAST_MASK                       0x40u
#define DMA_SSRT_SAST_SHIFT                      6
#define DMA_SSRT_SAST_WIDTH                      1
#define DMA_SSRT_SAST(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_SSRT_SAST_SHIFT))&DMA_SSRT_SAST_MASK)
#define DMA_SSRT_NOP_MASK                        0x80u
#define DMA_SSRT_NOP_SHIFT                       7
#define DMA_SSRT_NOP_WIDTH                       1
#define DMA_SSRT_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_SSRT_NOP_SHIFT))&DMA_SSRT_NOP_MASK)
// CERR Bit Fields
#define DMA_CERR_CERR_MASK                       0xFu
#define DMA_CERR_CERR_SHIFT                      0
#define DMA_CERR_CERR_WIDTH                      4
#define DMA_CERR_CERR(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CERR_CERR_SHIFT))&DMA_CERR_CERR_MASK)
#define DMA_CERR_CAEI_MASK                       0x40u
#define DMA_CERR_CAEI_SHIFT                      6
#define DMA_CERR_CAEI_WIDTH                      1
#define DMA_CERR_CAEI(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CERR_CAEI_SHIFT))&DMA_CERR_CAEI_MASK)
#define DMA_CERR_NOP_MASK                        0x80u
#define DMA_CERR_NOP_SHIFT                       7
#define DMA_CERR_NOP_WIDTH                       1
#define DMA_CERR_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_CERR_NOP_SHIFT))&DMA_CERR_NOP_MASK)
// CINT Bit Fields
#define DMA_CINT_CINT_MASK                       0xFu
#define DMA_CINT_CINT_SHIFT                      0
#define DMA_CINT_CINT_WIDTH                      4
#define DMA_CINT_CINT(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CINT_CINT_SHIFT))&DMA_CINT_CINT_MASK)
#define DMA_CINT_CAIR_MASK                       0x40u
#define DMA_CINT_CAIR_SHIFT                      6
#define DMA_CINT_CAIR_WIDTH                      1
#define DMA_CINT_CAIR(x)                         (((uint8_t)(((uint8_t)(x))<<DMA_CINT_CAIR_SHIFT))&DMA_CINT_CAIR_MASK)
#define DMA_CINT_NOP_MASK                        0x80u
#define DMA_CINT_NOP_SHIFT                       7
#define DMA_CINT_NOP_WIDTH                       1
#define DMA_CINT_NOP(x)                          (((uint8_t)(((uint8_t)(x))<<DMA_CINT_NOP_SHIFT))&DMA_CINT_NOP_MASK)
// INT Bit Fields
#define DMA_INT_INT0_MASK                        0x1u
#define DMA_INT_INT0_SHIFT                       0
#define DMA_INT_INT0_WIDTH                       1
#define DMA_INT_INT0(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT0_SHIFT))&DMA_INT_INT0_MASK)
#define DMA_INT_INT1_MASK                        0x2u
#define DMA_INT_INT1_SHIFT                       1
#define DMA_INT_INT1_WIDTH                       1
#define DMA_INT_INT1(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT1_SHIFT))&DMA_INT_INT1_MASK)
#define DMA_INT_INT2_MASK                        0x4u
#define DMA_INT_INT2_SHIFT                       2
#define DMA_INT_INT2_WIDTH                       1
#define DMA_INT_INT2(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT2_SHIFT))&DMA_INT_INT2_MASK)
#define DMA_INT_INT3_MASK                        0x8u
#define DMA_INT_INT3_SHIFT                       3
#define DMA_INT_INT3_WIDTH                       1
#define DMA_INT_INT3(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT3_SHIFT))&DMA_INT_INT3_MASK)
#define DMA_INT_INT4_MASK                        0x10u
#define DMA_INT_INT4_SHIFT                       4
#define DMA_INT_INT4_WIDTH                       1
#define DMA_INT_INT4(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT4_SHIFT))&DMA_INT_INT4_MASK)
#define DMA_INT_INT5_MASK                        0x20u
#define DMA_INT_INT5_SHIFT                       5
#define DMA_INT_INT5_WIDTH                       1
#define DMA_INT_INT5(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT5_SHIFT))&DMA_INT_INT5_MASK)
#define DMA_INT_INT6_MASK                        0x40u
#define DMA_INT_INT6_SHIFT                       6
#define DMA_INT_INT6_WIDTH                       1
#define DMA_INT_INT6(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT6_SHIFT))&DMA_INT_INT6_MASK)
#define DMA_INT_INT7_MASK                        0x80u
#define DMA_INT_INT7_SHIFT                       7
#define DMA_INT_INT7_WIDTH                       1
#define DMA_INT_INT7(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT7_SHIFT))&DMA_INT_INT7_MASK)
#define DMA_INT_INT8_MASK                        0x100u
#define DMA_INT_INT8_SHIFT                       8
#define DMA_INT_INT8_WIDTH                       1
#define DMA_INT_INT8(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT8_SHIFT))&DMA_INT_INT8_MASK)
#define DMA_INT_INT9_MASK                        0x200u
#define DMA_INT_INT9_SHIFT                       9
#define DMA_INT_INT9_WIDTH                       1
#define DMA_INT_INT9(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT9_SHIFT))&DMA_INT_INT9_MASK)
#define DMA_INT_INT10_MASK                       0x400u
#define DMA_INT_INT10_SHIFT                      10
#define DMA_INT_INT10_WIDTH                      1
#define DMA_INT_INT10(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT10_SHIFT))&DMA_INT_INT10_MASK)
#define DMA_INT_INT11_MASK                       0x800u
#define DMA_INT_INT11_SHIFT                      11
#define DMA_INT_INT11_WIDTH                      1
#define DMA_INT_INT11(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT11_SHIFT))&DMA_INT_INT11_MASK)
#define DMA_INT_INT12_MASK                       0x1000u
#define DMA_INT_INT12_SHIFT                      12
#define DMA_INT_INT12_WIDTH                      1
#define DMA_INT_INT12(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT12_SHIFT))&DMA_INT_INT12_MASK)
#define DMA_INT_INT13_MASK                       0x2000u
#define DMA_INT_INT13_SHIFT                      13
#define DMA_INT_INT13_WIDTH                      1
#define DMA_INT_INT13(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT13_SHIFT))&DMA_INT_INT13_MASK)
#define DMA_INT_INT14_MASK                       0x4000u
#define DMA_INT_INT14_SHIFT                      14
#define DMA_INT_INT14_WIDTH                      1
#define DMA_INT_INT14(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT14_SHIFT))&DMA_INT_INT14_MASK)
#define DMA_INT_INT15_MASK                       0x8000u
#define DMA_INT_INT15_SHIFT                      15
#define DMA_INT_INT15_WIDTH                      1
#define DMA_INT_INT15(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_INT_INT15_SHIFT))&DMA_INT_INT15_MASK)
// ERR Bit Fields
#define DMA_ERR_ERR0_MASK                        0x1u
#define DMA_ERR_ERR0_SHIFT                       0
#define DMA_ERR_ERR0_WIDTH                       1
#define DMA_ERR_ERR0(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR0_SHIFT))&DMA_ERR_ERR0_MASK)
#define DMA_ERR_ERR1_MASK                        0x2u
#define DMA_ERR_ERR1_SHIFT                       1
#define DMA_ERR_ERR1_WIDTH                       1
#define DMA_ERR_ERR1(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR1_SHIFT))&DMA_ERR_ERR1_MASK)
#define DMA_ERR_ERR2_MASK                        0x4u
#define DMA_ERR_ERR2_SHIFT                       2
#define DMA_ERR_ERR2_WIDTH                       1
#define DMA_ERR_ERR2(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR2_SHIFT))&DMA_ERR_ERR2_MASK)
#define DMA_ERR_ERR3_MASK                        0x8u
#define DMA_ERR_ERR3_SHIFT                       3
#define DMA_ERR_ERR3_WIDTH                       1
#define DMA_ERR_ERR3(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR3_SHIFT))&DMA_ERR_ERR3_MASK)
#define DMA_ERR_ERR4_MASK                        0x10u
#define DMA_ERR_ERR4_SHIFT                       4
#define DMA_ERR_ERR4_WIDTH                       1
#define DMA_ERR_ERR4(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR4_SHIFT))&DMA_ERR_ERR4_MASK)
#define DMA_ERR_ERR5_MASK                        0x20u
#define DMA_ERR_ERR5_SHIFT                       5
#define DMA_ERR_ERR5_WIDTH                       1
#define DMA_ERR_ERR5(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR5_SHIFT))&DMA_ERR_ERR5_MASK)
#define DMA_ERR_ERR6_MASK                        0x40u
#define DMA_ERR_ERR6_SHIFT                       6
#define DMA_ERR_ERR6_WIDTH                       1
#define DMA_ERR_ERR6(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR6_SHIFT))&DMA_ERR_ERR6_MASK)
#define DMA_ERR_ERR7_MASK                        0x80u
#define DMA_ERR_ERR7_SHIFT                       7
#define DMA_ERR_ERR7_WIDTH                       1
#define DMA_ERR_ERR7(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR7_SHIFT))&DMA_ERR_ERR7_MASK)
#define DMA_ERR_ERR8_MASK                        0x100u
#define DMA_ERR_ERR8_SHIFT                       8
#define DMA_ERR_ERR8_WIDTH                       1
#define DMA_ERR_ERR8(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR8_SHIFT))&DMA_ERR_ERR8_MASK)
#define DMA_ERR_ERR9_MASK                        0x200u
#define DMA_ERR_ERR9_SHIFT                       9
#define DMA_ERR_ERR9_WIDTH                       1
#define DMA_ERR_ERR9(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR9_SHIFT))&DMA_ERR_ERR9_MASK)
#define DMA_ERR_ERR10_MASK                       0x400u
#define DMA_ERR_ERR10_SHIFT                      10
#define DMA_ERR_ERR10_WIDTH                      1
#define DMA_ERR_ERR10(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR10_SHIFT))&DMA_ERR_ERR10_MASK)
#define DMA_ERR_ERR11_MASK                       0x800u
#define DMA_ERR_ERR11_SHIFT                      11
#define DMA_ERR_ERR11_WIDTH                      1
#define DMA_ERR_ERR11(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR11_SHIFT))&DMA_ERR_ERR11_MASK)
#define DMA_ERR_ERR12_MASK                       0x1000u
#define DMA_ERR_ERR12_SHIFT                      12
#define DMA_ERR_ERR12_WIDTH                      1
#define DMA_ERR_ERR12(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR12_SHIFT))&DMA_ERR_ERR12_MASK)
#define DMA_ERR_ERR13_MASK                       0x2000u
#define DMA_ERR_ERR13_SHIFT                      13
#define DMA_ERR_ERR13_WIDTH                      1
#define DMA_ERR_ERR13(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR13_SHIFT))&DMA_ERR_ERR13_MASK)
#define DMA_ERR_ERR14_MASK                       0x4000u
#define DMA_ERR_ERR14_SHIFT                      14
#define DMA_ERR_ERR14_WIDTH                      1
#define DMA_ERR_ERR14(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR14_SHIFT))&DMA_ERR_ERR14_MASK)
#define DMA_ERR_ERR15_MASK                       0x8000u
#define DMA_ERR_ERR15_SHIFT                      15
#define DMA_ERR_ERR15_WIDTH                      1
#define DMA_ERR_ERR15(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_ERR_ERR15_SHIFT))&DMA_ERR_ERR15_MASK)
// HRS Bit Fields
#define DMA_HRS_HRS0_MASK                        0x1u
#define DMA_HRS_HRS0_SHIFT                       0
#define DMA_HRS_HRS0_WIDTH                       1
#define DMA_HRS_HRS0(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS0_SHIFT))&DMA_HRS_HRS0_MASK)
#define DMA_HRS_HRS1_MASK                        0x2u
#define DMA_HRS_HRS1_SHIFT                       1
#define DMA_HRS_HRS1_WIDTH                       1
#define DMA_HRS_HRS1(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS1_SHIFT))&DMA_HRS_HRS1_MASK)
#define DMA_HRS_HRS2_MASK                        0x4u
#define DMA_HRS_HRS2_SHIFT                       2
#define DMA_HRS_HRS2_WIDTH                       1
#define DMA_HRS_HRS2(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS2_SHIFT))&DMA_HRS_HRS2_MASK)
#define DMA_HRS_HRS3_MASK                        0x8u
#define DMA_HRS_HRS3_SHIFT                       3
#define DMA_HRS_HRS3_WIDTH                       1
#define DMA_HRS_HRS3(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS3_SHIFT))&DMA_HRS_HRS3_MASK)
#define DMA_HRS_HRS4_MASK                        0x10u
#define DMA_HRS_HRS4_SHIFT                       4
#define DMA_HRS_HRS4_WIDTH                       1
#define DMA_HRS_HRS4(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS4_SHIFT))&DMA_HRS_HRS4_MASK)
#define DMA_HRS_HRS5_MASK                        0x20u
#define DMA_HRS_HRS5_SHIFT                       5
#define DMA_HRS_HRS5_WIDTH                       1
#define DMA_HRS_HRS5(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS5_SHIFT))&DMA_HRS_HRS5_MASK)
#define DMA_HRS_HRS6_MASK                        0x40u
#define DMA_HRS_HRS6_SHIFT                       6
#define DMA_HRS_HRS6_WIDTH                       1
#define DMA_HRS_HRS6(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS6_SHIFT))&DMA_HRS_HRS6_MASK)
#define DMA_HRS_HRS7_MASK                        0x80u
#define DMA_HRS_HRS7_SHIFT                       7
#define DMA_HRS_HRS7_WIDTH                       1
#define DMA_HRS_HRS7(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS7_SHIFT))&DMA_HRS_HRS7_MASK)
#define DMA_HRS_HRS8_MASK                        0x100u
#define DMA_HRS_HRS8_SHIFT                       8
#define DMA_HRS_HRS8_WIDTH                       1
#define DMA_HRS_HRS8(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS8_SHIFT))&DMA_HRS_HRS8_MASK)
#define DMA_HRS_HRS9_MASK                        0x200u
#define DMA_HRS_HRS9_SHIFT                       9
#define DMA_HRS_HRS9_WIDTH                       1
#define DMA_HRS_HRS9(x)                          (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS9_SHIFT))&DMA_HRS_HRS9_MASK)
#define DMA_HRS_HRS10_MASK                       0x400u
#define DMA_HRS_HRS10_SHIFT                      10
#define DMA_HRS_HRS10_WIDTH                      1
#define DMA_HRS_HRS10(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS10_SHIFT))&DMA_HRS_HRS10_MASK)
#define DMA_HRS_HRS11_MASK                       0x800u
#define DMA_HRS_HRS11_SHIFT                      11
#define DMA_HRS_HRS11_WIDTH                      1
#define DMA_HRS_HRS11(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS11_SHIFT))&DMA_HRS_HRS11_MASK)
#define DMA_HRS_HRS12_MASK                       0x1000u
#define DMA_HRS_HRS12_SHIFT                      12
#define DMA_HRS_HRS12_WIDTH                      1
#define DMA_HRS_HRS12(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS12_SHIFT))&DMA_HRS_HRS12_MASK)
#define DMA_HRS_HRS13_MASK                       0x2000u
#define DMA_HRS_HRS13_SHIFT                      13
#define DMA_HRS_HRS13_WIDTH                      1
#define DMA_HRS_HRS13(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS13_SHIFT))&DMA_HRS_HRS13_MASK)
#define DMA_HRS_HRS14_MASK                       0x4000u
#define DMA_HRS_HRS14_SHIFT                      14
#define DMA_HRS_HRS14_WIDTH                      1
#define DMA_HRS_HRS14(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS14_SHIFT))&DMA_HRS_HRS14_MASK)
#define DMA_HRS_HRS15_MASK                       0x8000u
#define DMA_HRS_HRS15_SHIFT                      15
#define DMA_HRS_HRS15_WIDTH                      1
#define DMA_HRS_HRS15(x)                         (((uint32_t)(((uint32_t)(x))<<DMA_HRS_HRS15_SHIFT))&DMA_HRS_HRS15_MASK)
// DCHPRI3 Bit Fields
#define DMA_DCHPRI3_CHPRI_MASK                   0xFu
#define DMA_DCHPRI3_CHPRI_SHIFT                  0
#define DMA_DCHPRI3_CHPRI_WIDTH                  4
#define DMA_DCHPRI3_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI3_CHPRI_SHIFT))&DMA_DCHPRI3_CHPRI_MASK)
#define DMA_DCHPRI3_DPA_MASK                     0x40u
#define DMA_DCHPRI3_DPA_SHIFT                    6
#define DMA_DCHPRI3_DPA_WIDTH                    1
#define DMA_DCHPRI3_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI3_DPA_SHIFT))&DMA_DCHPRI3_DPA_MASK)
#define DMA_DCHPRI3_ECP_MASK                     0x80u
#define DMA_DCHPRI3_ECP_SHIFT                    7
#define DMA_DCHPRI3_ECP_WIDTH                    1
#define DMA_DCHPRI3_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI3_ECP_SHIFT))&DMA_DCHPRI3_ECP_MASK)
// DCHPRI2 Bit Fields
#define DMA_DCHPRI2_CHPRI_MASK                   0xFu
#define DMA_DCHPRI2_CHPRI_SHIFT                  0
#define DMA_DCHPRI2_CHPRI_WIDTH                  4
#define DMA_DCHPRI2_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI2_CHPRI_SHIFT))&DMA_DCHPRI2_CHPRI_MASK)
#define DMA_DCHPRI2_DPA_MASK                     0x40u
#define DMA_DCHPRI2_DPA_SHIFT                    6
#define DMA_DCHPRI2_DPA_WIDTH                    1
#define DMA_DCHPRI2_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI2_DPA_SHIFT))&DMA_DCHPRI2_DPA_MASK)
#define DMA_DCHPRI2_ECP_MASK                     0x80u
#define DMA_DCHPRI2_ECP_SHIFT                    7
#define DMA_DCHPRI2_ECP_WIDTH                    1
#define DMA_DCHPRI2_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI2_ECP_SHIFT))&DMA_DCHPRI2_ECP_MASK)
// DCHPRI1 Bit Fields
#define DMA_DCHPRI1_CHPRI_MASK                   0xFu
#define DMA_DCHPRI1_CHPRI_SHIFT                  0
#define DMA_DCHPRI1_CHPRI_WIDTH                  4
#define DMA_DCHPRI1_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI1_CHPRI_SHIFT))&DMA_DCHPRI1_CHPRI_MASK)
#define DMA_DCHPRI1_DPA_MASK                     0x40u
#define DMA_DCHPRI1_DPA_SHIFT                    6
#define DMA_DCHPRI1_DPA_WIDTH                    1
#define DMA_DCHPRI1_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI1_DPA_SHIFT))&DMA_DCHPRI1_DPA_MASK)
#define DMA_DCHPRI1_ECP_MASK                     0x80u
#define DMA_DCHPRI1_ECP_SHIFT                    7
#define DMA_DCHPRI1_ECP_WIDTH                    1
#define DMA_DCHPRI1_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI1_ECP_SHIFT))&DMA_DCHPRI1_ECP_MASK)
// DCHPRI0 Bit Fields
#define DMA_DCHPRI0_CHPRI_MASK                   0xFu
#define DMA_DCHPRI0_CHPRI_SHIFT                  0
#define DMA_DCHPRI0_CHPRI_WIDTH                  4
#define DMA_DCHPRI0_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI0_CHPRI_SHIFT))&DMA_DCHPRI0_CHPRI_MASK)
#define DMA_DCHPRI0_DPA_MASK                     0x40u
#define DMA_DCHPRI0_DPA_SHIFT                    6
#define DMA_DCHPRI0_DPA_WIDTH                    1
#define DMA_DCHPRI0_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI0_DPA_SHIFT))&DMA_DCHPRI0_DPA_MASK)
#define DMA_DCHPRI0_ECP_MASK                     0x80u
#define DMA_DCHPRI0_ECP_SHIFT                    7
#define DMA_DCHPRI0_ECP_WIDTH                    1
#define DMA_DCHPRI0_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI0_ECP_SHIFT))&DMA_DCHPRI0_ECP_MASK)
// DCHPRI7 Bit Fields
#define DMA_DCHPRI7_CHPRI_MASK                   0xFu
#define DMA_DCHPRI7_CHPRI_SHIFT                  0
#define DMA_DCHPRI7_CHPRI_WIDTH                  4
#define DMA_DCHPRI7_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI7_CHPRI_SHIFT))&DMA_DCHPRI7_CHPRI_MASK)
#define DMA_DCHPRI7_DPA_MASK                     0x40u
#define DMA_DCHPRI7_DPA_SHIFT                    6
#define DMA_DCHPRI7_DPA_WIDTH                    1
#define DMA_DCHPRI7_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI7_DPA_SHIFT))&DMA_DCHPRI7_DPA_MASK)
#define DMA_DCHPRI7_ECP_MASK                     0x80u
#define DMA_DCHPRI7_ECP_SHIFT                    7
#define DMA_DCHPRI7_ECP_WIDTH                    1
#define DMA_DCHPRI7_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI7_ECP_SHIFT))&DMA_DCHPRI7_ECP_MASK)
// DCHPRI6 Bit Fields
#define DMA_DCHPRI6_CHPRI_MASK                   0xFu
#define DMA_DCHPRI6_CHPRI_SHIFT                  0
#define DMA_DCHPRI6_CHPRI_WIDTH                  4
#define DMA_DCHPRI6_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI6_CHPRI_SHIFT))&DMA_DCHPRI6_CHPRI_MASK)
#define DMA_DCHPRI6_DPA_MASK                     0x40u
#define DMA_DCHPRI6_DPA_SHIFT                    6
#define DMA_DCHPRI6_DPA_WIDTH                    1
#define DMA_DCHPRI6_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI6_DPA_SHIFT))&DMA_DCHPRI6_DPA_MASK)
#define DMA_DCHPRI6_ECP_MASK                     0x80u
#define DMA_DCHPRI6_ECP_SHIFT                    7
#define DMA_DCHPRI6_ECP_WIDTH                    1
#define DMA_DCHPRI6_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI6_ECP_SHIFT))&DMA_DCHPRI6_ECP_MASK)
// DCHPRI5 Bit Fields
#define DMA_DCHPRI5_CHPRI_MASK                   0xFu
#define DMA_DCHPRI5_CHPRI_SHIFT                  0
#define DMA_DCHPRI5_CHPRI_WIDTH                  4
#define DMA_DCHPRI5_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI5_CHPRI_SHIFT))&DMA_DCHPRI5_CHPRI_MASK)
#define DMA_DCHPRI5_DPA_MASK                     0x40u
#define DMA_DCHPRI5_DPA_SHIFT                    6
#define DMA_DCHPRI5_DPA_WIDTH                    1
#define DMA_DCHPRI5_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI5_DPA_SHIFT))&DMA_DCHPRI5_DPA_MASK)
#define DMA_DCHPRI5_ECP_MASK                     0x80u
#define DMA_DCHPRI5_ECP_SHIFT                    7
#define DMA_DCHPRI5_ECP_WIDTH                    1
#define DMA_DCHPRI5_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI5_ECP_SHIFT))&DMA_DCHPRI5_ECP_MASK)
// DCHPRI4 Bit Fields
#define DMA_DCHPRI4_CHPRI_MASK                   0xFu
#define DMA_DCHPRI4_CHPRI_SHIFT                  0
#define DMA_DCHPRI4_CHPRI_WIDTH                  4
#define DMA_DCHPRI4_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI4_CHPRI_SHIFT))&DMA_DCHPRI4_CHPRI_MASK)
#define DMA_DCHPRI4_DPA_MASK                     0x40u
#define DMA_DCHPRI4_DPA_SHIFT                    6
#define DMA_DCHPRI4_DPA_WIDTH                    1
#define DMA_DCHPRI4_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI4_DPA_SHIFT))&DMA_DCHPRI4_DPA_MASK)
#define DMA_DCHPRI4_ECP_MASK                     0x80u
#define DMA_DCHPRI4_ECP_SHIFT                    7
#define DMA_DCHPRI4_ECP_WIDTH                    1
#define DMA_DCHPRI4_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI4_ECP_SHIFT))&DMA_DCHPRI4_ECP_MASK)
// DCHPRI11 Bit Fields
#define DMA_DCHPRI11_CHPRI_MASK                  0xFu
#define DMA_DCHPRI11_CHPRI_SHIFT                 0
#define DMA_DCHPRI11_CHPRI_WIDTH                 4
#define DMA_DCHPRI11_CHPRI(x)                    (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI11_CHPRI_SHIFT))&DMA_DCHPRI11_CHPRI_MASK)
#define DMA_DCHPRI11_DPA_MASK                    0x40u
#define DMA_DCHPRI11_DPA_SHIFT                   6
#define DMA_DCHPRI11_DPA_WIDTH                   1
#define DMA_DCHPRI11_DPA(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI11_DPA_SHIFT))&DMA_DCHPRI11_DPA_MASK)
#define DMA_DCHPRI11_ECP_MASK                    0x80u
#define DMA_DCHPRI11_ECP_SHIFT                   7
#define DMA_DCHPRI11_ECP_WIDTH                   1
#define DMA_DCHPRI11_ECP(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI11_ECP_SHIFT))&DMA_DCHPRI11_ECP_MASK)
// DCHPRI10 Bit Fields
#define DMA_DCHPRI10_CHPRI_MASK                  0xFu
#define DMA_DCHPRI10_CHPRI_SHIFT                 0
#define DMA_DCHPRI10_CHPRI_WIDTH                 4
#define DMA_DCHPRI10_CHPRI(x)                    (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI10_CHPRI_SHIFT))&DMA_DCHPRI10_CHPRI_MASK)
#define DMA_DCHPRI10_DPA_MASK                    0x40u
#define DMA_DCHPRI10_DPA_SHIFT                   6
#define DMA_DCHPRI10_DPA_WIDTH                   1
#define DMA_DCHPRI10_DPA(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI10_DPA_SHIFT))&DMA_DCHPRI10_DPA_MASK)
#define DMA_DCHPRI10_ECP_MASK                    0x80u
#define DMA_DCHPRI10_ECP_SHIFT                   7
#define DMA_DCHPRI10_ECP_WIDTH                   1
#define DMA_DCHPRI10_ECP(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI10_ECP_SHIFT))&DMA_DCHPRI10_ECP_MASK)
// DCHPRI9 Bit Fields
#define DMA_DCHPRI9_CHPRI_MASK                   0xFu
#define DMA_DCHPRI9_CHPRI_SHIFT                  0
#define DMA_DCHPRI9_CHPRI_WIDTH                  4
#define DMA_DCHPRI9_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI9_CHPRI_SHIFT))&DMA_DCHPRI9_CHPRI_MASK)
#define DMA_DCHPRI9_DPA_MASK                     0x40u
#define DMA_DCHPRI9_DPA_SHIFT                    6
#define DMA_DCHPRI9_DPA_WIDTH                    1
#define DMA_DCHPRI9_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI9_DPA_SHIFT))&DMA_DCHPRI9_DPA_MASK)
#define DMA_DCHPRI9_ECP_MASK                     0x80u
#define DMA_DCHPRI9_ECP_SHIFT                    7
#define DMA_DCHPRI9_ECP_WIDTH                    1
#define DMA_DCHPRI9_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI9_ECP_SHIFT))&DMA_DCHPRI9_ECP_MASK)
// DCHPRI8 Bit Fields
#define DMA_DCHPRI8_CHPRI_MASK                   0xFu
#define DMA_DCHPRI8_CHPRI_SHIFT                  0
#define DMA_DCHPRI8_CHPRI_WIDTH                  4
#define DMA_DCHPRI8_CHPRI(x)                     (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI8_CHPRI_SHIFT))&DMA_DCHPRI8_CHPRI_MASK)
#define DMA_DCHPRI8_DPA_MASK                     0x40u
#define DMA_DCHPRI8_DPA_SHIFT                    6
#define DMA_DCHPRI8_DPA_WIDTH                    1
#define DMA_DCHPRI8_DPA(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI8_DPA_SHIFT))&DMA_DCHPRI8_DPA_MASK)
#define DMA_DCHPRI8_ECP_MASK                     0x80u
#define DMA_DCHPRI8_ECP_SHIFT                    7
#define DMA_DCHPRI8_ECP_WIDTH                    1
#define DMA_DCHPRI8_ECP(x)                       (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI8_ECP_SHIFT))&DMA_DCHPRI8_ECP_MASK)
// DCHPRI15 Bit Fields
#define DMA_DCHPRI15_CHPRI_MASK                  0xFu
#define DMA_DCHPRI15_CHPRI_SHIFT                 0
#define DMA_DCHPRI15_CHPRI_WIDTH                 4
#define DMA_DCHPRI15_CHPRI(x)                    (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI15_CHPRI_SHIFT))&DMA_DCHPRI15_CHPRI_MASK)
#define DMA_DCHPRI15_DPA_MASK                    0x40u
#define DMA_DCHPRI15_DPA_SHIFT                   6
#define DMA_DCHPRI15_DPA_WIDTH                   1
#define DMA_DCHPRI15_DPA(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI15_DPA_SHIFT))&DMA_DCHPRI15_DPA_MASK)
#define DMA_DCHPRI15_ECP_MASK                    0x80u
#define DMA_DCHPRI15_ECP_SHIFT                   7
#define DMA_DCHPRI15_ECP_WIDTH                   1
#define DMA_DCHPRI15_ECP(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI15_ECP_SHIFT))&DMA_DCHPRI15_ECP_MASK)
// DCHPRI14 Bit Fields
#define DMA_DCHPRI14_CHPRI_MASK                  0xFu
#define DMA_DCHPRI14_CHPRI_SHIFT                 0
#define DMA_DCHPRI14_CHPRI_WIDTH                 4
#define DMA_DCHPRI14_CHPRI(x)                    (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI14_CHPRI_SHIFT))&DMA_DCHPRI14_CHPRI_MASK)
#define DMA_DCHPRI14_DPA_MASK                    0x40u
#define DMA_DCHPRI14_DPA_SHIFT                   6
#define DMA_DCHPRI14_DPA_WIDTH                   1
#define DMA_DCHPRI14_DPA(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI14_DPA_SHIFT))&DMA_DCHPRI14_DPA_MASK)
#define DMA_DCHPRI14_ECP_MASK                    0x80u
#define DMA_DCHPRI14_ECP_SHIFT                   7
#define DMA_DCHPRI14_ECP_WIDTH                   1
#define DMA_DCHPRI14_ECP(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI14_ECP_SHIFT))&DMA_DCHPRI14_ECP_MASK)
// DCHPRI13 Bit Fields
#define DMA_DCHPRI13_CHPRI_MASK                  0xFu
#define DMA_DCHPRI13_CHPRI_SHIFT                 0
#define DMA_DCHPRI13_CHPRI_WIDTH                 4
#define DMA_DCHPRI13_CHPRI(x)                    (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI13_CHPRI_SHIFT))&DMA_DCHPRI13_CHPRI_MASK)
#define DMA_DCHPRI13_DPA_MASK                    0x40u
#define DMA_DCHPRI13_DPA_SHIFT                   6
#define DMA_DCHPRI13_DPA_WIDTH                   1
#define DMA_DCHPRI13_DPA(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI13_DPA_SHIFT))&DMA_DCHPRI13_DPA_MASK)
#define DMA_DCHPRI13_ECP_MASK                    0x80u
#define DMA_DCHPRI13_ECP_SHIFT                   7
#define DMA_DCHPRI13_ECP_WIDTH                   1
#define DMA_DCHPRI13_ECP(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI13_ECP_SHIFT))&DMA_DCHPRI13_ECP_MASK)
// DCHPRI12 Bit Fields
#define DMA_DCHPRI12_CHPRI_MASK                  0xFu
#define DMA_DCHPRI12_CHPRI_SHIFT                 0
#define DMA_DCHPRI12_CHPRI_WIDTH                 4
#define DMA_DCHPRI12_CHPRI(x)                    (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI12_CHPRI_SHIFT))&DMA_DCHPRI12_CHPRI_MASK)
#define DMA_DCHPRI12_DPA_MASK                    0x40u
#define DMA_DCHPRI12_DPA_SHIFT                   6
#define DMA_DCHPRI12_DPA_WIDTH                   1
#define DMA_DCHPRI12_DPA(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI12_DPA_SHIFT))&DMA_DCHPRI12_DPA_MASK)
#define DMA_DCHPRI12_ECP_MASK                    0x80u
#define DMA_DCHPRI12_ECP_SHIFT                   7
#define DMA_DCHPRI12_ECP_WIDTH                   1
#define DMA_DCHPRI12_ECP(x)                      (((uint8_t)(((uint8_t)(x))<<DMA_DCHPRI12_ECP_SHIFT))&DMA_DCHPRI12_ECP_MASK)
// SADDR Bit Fields
#define DMA_SADDR_SADDR_MASK                     0xFFFFFFFFu
#define DMA_SADDR_SADDR_SHIFT                    0
#define DMA_SADDR_SADDR_WIDTH                    32
#define DMA_SADDR_SADDR(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_SADDR_SADDR_SHIFT))&DMA_SADDR_SADDR_MASK)
// SOFF Bit Fields
#define DMA_SOFF_SOFF_MASK                       0xFFFFu
#define DMA_SOFF_SOFF_SHIFT                      0
#define DMA_SOFF_SOFF_WIDTH                      16
#define DMA_SOFF_SOFF(x)                         (((uint16_t)(((uint16_t)(x))<<DMA_SOFF_SOFF_SHIFT))&DMA_SOFF_SOFF_MASK)
// ATTR Bit Fields
#define DMA_ATTR_DSIZE_MASK                      0x7u
#define DMA_ATTR_DSIZE_SHIFT                     0
#define DMA_ATTR_DSIZE_WIDTH                     3
#define DMA_ATTR_DSIZE(x)                        (((uint16_t)(((uint16_t)(x))<<DMA_ATTR_DSIZE_SHIFT))&DMA_ATTR_DSIZE_MASK)
#define DMA_ATTR_DMOD_MASK                       0xF8u
#define DMA_ATTR_DMOD_SHIFT                      3
#define DMA_ATTR_DMOD_WIDTH                      5
#define DMA_ATTR_DMOD(x)                         (((uint16_t)(((uint16_t)(x))<<DMA_ATTR_DMOD_SHIFT))&DMA_ATTR_DMOD_MASK)
#define DMA_ATTR_SSIZE_MASK                      0x700u
#define DMA_ATTR_SSIZE_SHIFT                     8
#define DMA_ATTR_SSIZE_WIDTH                     3
#define DMA_ATTR_SSIZE(x)                        (((uint16_t)(((uint16_t)(x))<<DMA_ATTR_SSIZE_SHIFT))&DMA_ATTR_SSIZE_MASK)
#define DMA_ATTR_SMOD_MASK                       0xF800u
#define DMA_ATTR_SMOD_SHIFT                      11
#define DMA_ATTR_SMOD_WIDTH                      5
#define DMA_ATTR_SMOD(x)                         (((uint16_t)(((uint16_t)(x))<<DMA_ATTR_SMOD_SHIFT))&DMA_ATTR_SMOD_MASK)
// NBYTES_MLNO Bit Fields
#define DMA_NBYTES_MLNO_NBYTES_MASK              0xFFFFFFFFu
#define DMA_NBYTES_MLNO_NBYTES_SHIFT             0
#define DMA_NBYTES_MLNO_NBYTES_WIDTH             32
#define DMA_NBYTES_MLNO_NBYTES(x)                (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLNO_NBYTES_SHIFT))&DMA_NBYTES_MLNO_NBYTES_MASK)
// NBYTES_MLOFFNO Bit Fields
#define DMA_NBYTES_MLOFFNO_NBYTES_MASK           0x3FFFFFFFu
#define DMA_NBYTES_MLOFFNO_NBYTES_SHIFT          0
#define DMA_NBYTES_MLOFFNO_NBYTES_WIDTH          30
#define DMA_NBYTES_MLOFFNO_NBYTES(x)             (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFNO_NBYTES_SHIFT))&DMA_NBYTES_MLOFFNO_NBYTES_MASK)
#define DMA_NBYTES_MLOFFNO_DMLOE_MASK            0x40000000u
#define DMA_NBYTES_MLOFFNO_DMLOE_SHIFT           30
#define DMA_NBYTES_MLOFFNO_DMLOE_WIDTH           1
#define DMA_NBYTES_MLOFFNO_DMLOE(x)              (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFNO_DMLOE_SHIFT))&DMA_NBYTES_MLOFFNO_DMLOE_MASK)
#define DMA_NBYTES_MLOFFNO_SMLOE_MASK            0x80000000u
#define DMA_NBYTES_MLOFFNO_SMLOE_SHIFT           31
#define DMA_NBYTES_MLOFFNO_SMLOE_WIDTH           1
#define DMA_NBYTES_MLOFFNO_SMLOE(x)              (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFNO_SMLOE_SHIFT))&DMA_NBYTES_MLOFFNO_SMLOE_MASK)
// NBYTES_MLOFFYES Bit Fields
#define DMA_NBYTES_MLOFFYES_NBYTES_MASK          0x3FFu
#define DMA_NBYTES_MLOFFYES_NBYTES_SHIFT         0
#define DMA_NBYTES_MLOFFYES_NBYTES_WIDTH         10
#define DMA_NBYTES_MLOFFYES_NBYTES(x)            (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFYES_NBYTES_SHIFT))&DMA_NBYTES_MLOFFYES_NBYTES_MASK)
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK           0x3FFFFC00u
#define DMA_NBYTES_MLOFFYES_MLOFF_SHIFT          10
#define DMA_NBYTES_MLOFFYES_MLOFF_WIDTH          20
#define DMA_NBYTES_MLOFFYES_MLOFF(x)             (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFYES_MLOFF_SHIFT))&DMA_NBYTES_MLOFFYES_MLOFF_MASK)
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK           0x40000000u
#define DMA_NBYTES_MLOFFYES_DMLOE_SHIFT          30
#define DMA_NBYTES_MLOFFYES_DMLOE_WIDTH          1
#define DMA_NBYTES_MLOFFYES_DMLOE(x)             (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFYES_DMLOE_SHIFT))&DMA_NBYTES_MLOFFYES_DMLOE_MASK)
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK           0x80000000u
#define DMA_NBYTES_MLOFFYES_SMLOE_SHIFT          31
#define DMA_NBYTES_MLOFFYES_SMLOE_WIDTH          1
#define DMA_NBYTES_MLOFFYES_SMLOE(x)             (((uint32_t)(((uint32_t)(x))<<DMA_NBYTES_MLOFFYES_SMLOE_SHIFT))&DMA_NBYTES_MLOFFYES_SMLOE_MASK)
// SLAST Bit Fields
#define DMA_SLAST_SLAST_MASK                     0xFFFFFFFFu
#define DMA_SLAST_SLAST_SHIFT                    0
#define DMA_SLAST_SLAST_WIDTH                    32
#define DMA_SLAST_SLAST(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_SLAST_SLAST_SHIFT))&DMA_SLAST_SLAST_MASK)
//  DADDR Bit Fields
#define DMA_DADDR_DADDR_MASK                     0xFFFFFFFFu
#define DMA_DADDR_DADDR_SHIFT                    0
#define DMA_DADDR_DADDR_WIDTH                    32
#define DMA_DADDR_DADDR(x)                       (((uint32_t)(((uint32_t)(x))<<DMA_DADDR_DADDR_SHIFT))&DMA_DADDR_DADDR_MASK)
// DOFF Bit Fields
#define DMA_DOFF_DOFF_MASK                       0xFFFFu
#define DMA_DOFF_DOFF_SHIFT                      0
#define DMA_DOFF_DOFF_WIDTH                      16
#define DMA_DOFF_DOFF(x)                         (((uint16_t)(((uint16_t)(x))<<DMA_DOFF_DOFF_SHIFT))&DMA_DOFF_DOFF_MASK)
// CITER_ELINKNO Bit Fields
#define DMA_CITER_ELINKNO_CITER_MASK             0x7FFFu
#define DMA_CITER_ELINKNO_CITER_SHIFT            0
#define DMA_CITER_ELINKNO_CITER_WIDTH            15
#define DMA_CITER_ELINKNO_CITER(x)               (((uint16_t)(((uint16_t)(x))<<DMA_CITER_ELINKNO_CITER_SHIFT))&DMA_CITER_ELINKNO_CITER_MASK)
#define DMA_CITER_ELINKNO_ELINK_MASK             0x8000u
#define DMA_CITER_ELINKNO_ELINK_SHIFT            15
#define DMA_CITER_ELINKNO_ELINK_WIDTH            1
#define DMA_CITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x))<<DMA_CITER_ELINKNO_ELINK_SHIFT))&DMA_CITER_ELINKNO_ELINK_MASK)
// CITER_ELINKYES Bit Fields
#define DMA_CITER_ELINKYES_CITER_MASK            0x1FFu
#define DMA_CITER_ELINKYES_CITER_SHIFT           0
#define DMA_CITER_ELINKYES_CITER_WIDTH           9
#define DMA_CITER_ELINKYES_CITER(x)              (((uint16_t)(((uint16_t)(x))<<DMA_CITER_ELINKYES_CITER_SHIFT))&DMA_CITER_ELINKYES_CITER_MASK)
#define DMA_CITER_ELINKYES_LINKCH_MASK           0x1E00u
#define DMA_CITER_ELINKYES_LINKCH_SHIFT          9
#define DMA_CITER_ELINKYES_LINKCH_WIDTH          4
#define DMA_CITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x))<<DMA_CITER_ELINKYES_LINKCH_SHIFT))&DMA_CITER_ELINKYES_LINKCH_MASK)
#define DMA_CITER_ELINKYES_ELINK_MASK            0x8000u
#define DMA_CITER_ELINKYES_ELINK_SHIFT           15
#define DMA_CITER_ELINKYES_ELINK_WIDTH           1
#define DMA_CITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x))<<DMA_CITER_ELINKYES_ELINK_SHIFT))&DMA_CITER_ELINKYES_ELINK_MASK)
// DLAST_SGA Bit Fields
#define DMA_DLAST_SGA_DLASTSGA_MASK              0xFFFFFFFFu
#define DMA_DLAST_SGA_DLASTSGA_SHIFT             0
#define DMA_DLAST_SGA_DLASTSGA_WIDTH             32
#define DMA_DLAST_SGA_DLASTSGA(x)                (((uint32_t)(((uint32_t)(x))<<DMA_DLAST_SGA_DLASTSGA_SHIFT))&DMA_DLAST_SGA_DLASTSGA_MASK)
// CSR Bit Fields
#define DMA_CSR_START_MASK                       0x1u
#define DMA_CSR_START_SHIFT                      0
#define DMA_CSR_START_WIDTH                      1
#define DMA_CSR_START(x)                         (((uint16_t)(((uint16_t)(x))<<DMA_CSR_START_SHIFT))&DMA_CSR_START_MASK)
#define DMA_CSR_INTMAJOR_MASK                    0x2u
#define DMA_CSR_INTMAJOR_SHIFT                   1
#define DMA_CSR_INTMAJOR_WIDTH                   1
#define DMA_CSR_INTMAJOR(x)                      (((uint16_t)(((uint16_t)(x))<<DMA_CSR_INTMAJOR_SHIFT))&DMA_CSR_INTMAJOR_MASK)
#define DMA_CSR_INTHALF_MASK                     0x4u
#define DMA_CSR_INTHALF_SHIFT                    2
#define DMA_CSR_INTHALF_WIDTH                    1
#define DMA_CSR_INTHALF(x)                       (((uint16_t)(((uint16_t)(x))<<DMA_CSR_INTHALF_SHIFT))&DMA_CSR_INTHALF_MASK)
#define DMA_CSR_DREQ_MASK                        0x8u
#define DMA_CSR_DREQ_SHIFT                       3
#define DMA_CSR_DREQ_WIDTH                       1
#define DMA_CSR_DREQ(x)                          (((uint16_t)(((uint16_t)(x))<<DMA_CSR_DREQ_SHIFT))&DMA_CSR_DREQ_MASK)
#define DMA_CSR_ESG_MASK                         0x10u
#define DMA_CSR_ESG_SHIFT                        4
#define DMA_CSR_ESG_WIDTH                        1
#define DMA_CSR_ESG(x)                           (((uint16_t)(((uint16_t)(x))<<DMA_CSR_ESG_SHIFT))&DMA_CSR_ESG_MASK)
#define DMA_CSR_MAJORELINK_MASK                  0x20u
#define DMA_CSR_MAJORELINK_SHIFT                 5
#define DMA_CSR_MAJORELINK_WIDTH                 1
#define DMA_CSR_MAJORELINK(x)                    (((uint16_t)(((uint16_t)(x))<<DMA_CSR_MAJORELINK_SHIFT))&DMA_CSR_MAJORELINK_MASK)
#define DMA_CSR_ACTIVE_MASK                      0x40u
#define DMA_CSR_ACTIVE_SHIFT                     6
#define DMA_CSR_ACTIVE_WIDTH                     1
#define DMA_CSR_ACTIVE(x)                        (((uint16_t)(((uint16_t)(x))<<DMA_CSR_ACTIVE_SHIFT))&DMA_CSR_ACTIVE_MASK)
#define DMA_CSR_DONE_MASK                        0x80u
#define DMA_CSR_DONE_SHIFT                       7
#define DMA_CSR_DONE_WIDTH                       1
#define DMA_CSR_DONE(x)                          (((uint16_t)(((uint16_t)(x))<<DMA_CSR_DONE_SHIFT))&DMA_CSR_DONE_MASK)
#define DMA_CSR_MAJORLINKCH_MASK                 0xF00u
#define DMA_CSR_MAJORLINKCH_SHIFT                8
#define DMA_CSR_MAJORLINKCH_WIDTH                4
#define DMA_CSR_MAJORLINKCH(x)                   (((uint16_t)(((uint16_t)(x))<<DMA_CSR_MAJORLINKCH_SHIFT))&DMA_CSR_MAJORLINKCH_MASK)
#define DMA_CSR_BWC_MASK                         0xC000u
#define DMA_CSR_BWC_SHIFT                        14
#define DMA_CSR_BWC_WIDTH                        2
#define DMA_CSR_BWC(x)                           (((uint16_t)(((uint16_t)(x))<<DMA_CSR_BWC_SHIFT))&DMA_CSR_BWC_MASK)
// BITER_ELINKNO Bit Fields
#define DMA_BITER_ELINKNO_BITER_MASK             0x7FFFu
#define DMA_BITER_ELINKNO_BITER_SHIFT            0
#define DMA_BITER_ELINKNO_BITER_WIDTH            15
#define DMA_BITER_ELINKNO_BITER(x)               (((uint16_t)(((uint16_t)(x))<<DMA_BITER_ELINKNO_BITER_SHIFT))&DMA_BITER_ELINKNO_BITER_MASK)
#define DMA_BITER_ELINKNO_ELINK_MASK             0x8000u
#define DMA_BITER_ELINKNO_ELINK_SHIFT            15
#define DMA_BITER_ELINKNO_ELINK_WIDTH            1
#define DMA_BITER_ELINKNO_ELINK(x)               (((uint16_t)(((uint16_t)(x))<<DMA_BITER_ELINKNO_ELINK_SHIFT))&DMA_BITER_ELINKNO_ELINK_MASK)
// BITER_ELINKYES Bit Fields
#define DMA_BITER_ELINKYES_BITER_MASK            0x1FFu
#define DMA_BITER_ELINKYES_BITER_SHIFT           0
#define DMA_BITER_ELINKYES_BITER_WIDTH           9
#define DMA_BITER_ELINKYES_BITER(x)              (((uint16_t)(((uint16_t)(x))<<DMA_BITER_ELINKYES_BITER_SHIFT))&DMA_BITER_ELINKYES_BITER_MASK)
#define DMA_BITER_ELINKYES_LINKCH_MASK           0x1E00u
#define DMA_BITER_ELINKYES_LINKCH_SHIFT          9
#define DMA_BITER_ELINKYES_LINKCH_WIDTH          4
#define DMA_BITER_ELINKYES_LINKCH(x)             (((uint16_t)(((uint16_t)(x))<<DMA_BITER_ELINKYES_LINKCH_SHIFT))&DMA_BITER_ELINKYES_LINKCH_MASK)
#define DMA_BITER_ELINKYES_ELINK_MASK            0x8000u
#define DMA_BITER_ELINKYES_ELINK_SHIFT           15
#define DMA_BITER_ELINKYES_ELINK_WIDTH           1
#define DMA_BITER_ELINKYES_ELINK(x)              (((uint16_t)(((uint16_t)(x))<<DMA_BITER_ELINKYES_ELINK_SHIFT))&DMA_BITER_ELINKYES_ELINK_MASK)

// offsets
#define DMA_CR_OFFSET                             0x00
#define DMA_ES_OFFSET                             0x04
#define DMA_ERQ_OFFSET                            0x0C
#define DMA_EEI_OFFSET                            0x14
#define DMA_CEEI_OFFSET                           0x18
#define DMA_SEEI_OFFSET                           0x19
#define DMA_CERQ_OFFSET                           0x1A
#define DMA_SERQ_OFFSET                           0x1B
#define DMA_CDNE_OFFSET                           0x1C
#define DMA_SSRT_OFFSET                           0x1D
#define DMA_CERR_OFFSET                           0x1E
#define DMA_CINT_OFFSET                           0x1F
#define DMA_INT_OFFSET                            0x24
#define DMA_ERR_OFFSET                            0x2C
#define DMA_HRS_OFFSET                            0x34

#define DMA_DCHPRIn_OFFSET( channel )                                          \
    ( 0x100 + ( ( channel & ~0x03U ) | ( 3 - ( channel & 0x03U ) ) ) )
    
#define DMA_TCDn_SADDR_OFFSET( channel )           ( 0x1000 + 32 * channel )
#define DMA_TCDn_SOFF_OFFSET( channel )            ( 0x1004 + 32 * channel )
#define DMA_TCDn_ATTR_OFFSET( channel )            ( 0x1006 + 32 * channel )
#define DMA_TCDn_NBYTES_MLNO_OFFSET( channel )     ( 0x1008 + 32 * channel )
#define DMA_TCDn_NBYTES_MLOFFNO_OFFSET( channel )  ( 0x1008 + 32 * channel )
#define DMA_TCDn_NBYTES_MLOFFYES_OFFSET( channel ) ( 0x1008 + 32 * channel )
#define DMA_TCDn_SLAST_OFFSET( channel )           ( 0x100C + 32 * channel )
#define DMA_TCDn_DADDR_OFFSET( channel )           ( 0x1010 + 32 * channel )
#define DMA_TCDn_DOFF_OFFSET( channel )            ( 0x1014 + 32 * channel )
#define DMA_TCDn_CITER_ELINKYES_OFFSET( channel )  ( 0x1016 + 32 * channel )
#define DMA_TCDn_CITER_ELINKNO_OFFSET( channel )   ( 0x1016 + 32 * channel )
#define DMA_TCDn_DLASTSGA_OFFSET( channel )        ( 0x1018 + 32 * channel )
#define DMA_TCDn_CSR_OFFSET( channel )             ( 0x101C + 32 * channel )
#define DMA_TCDn_BITER_ELINKYES_OFFSET( channel )  ( 0x101E + 32 * channel )
#define DMA_TCDn_BITER_ELINKNO_OFFSET( channel )   ( 0x101E + 32 * channel )

#define DMAx_CR( base )                                                        \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_CR_OFFSET ) )

#define DMAx_CRbits( base )                                                    \
    ( ( typeDMA_CRBITS* )DMAx_CR( base ) )

#define DMAx_ES( base )                                                        \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_ES_OFFSET ) )

#define DMAx_ESbits( base )                                                    \
    ( ( typeDMA_ESBITS* )DMAx_ES( base ) )

#define DMAx_ERQ( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_ERQ_OFFSET ) )

#define DMAx_ERQbits( base )                                                   \
    ( ( typeDMA_ERQBITS* )DMAx_ERQ( base ) )

#define DMAx_EEI( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_EEI_OFFSET ) )

#define DMAx_EEIbits( base )                                                   \
    ( ( typeDMA_EEIBITS* )DMAx_EEI( base ) )

#define DMAx_CEEI( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_CEEI_OFFSET ) )

#define DMAx_CEEIbits( base )                                                  \
    ( ( typeDMA_CEEIBITS* )DMAx_CEEI( base ) )

#define DMAx_SEEI( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_SEEI_OFFSET ) )

#define DMAx_SEEIbits( base )                                                  \
    ( ( typeDMA_SEEIBITS* )DMAx_SEEI( base ) )

#define DMAx_CERQ( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_CERQ_OFFSET ) )

#define DMAx_CERQbits( base )                                                  \
    ( ( typeDMA_CERQBITS* )DMAx_CERQ( base ) )

#define DMAx_SERQ( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_SERQ_OFFSET ) )

#define DMAx_SERQbits( base )                                                  \
    ( ( typeDMA_SERQBITS* )DMAx_SERQ( base ) )

#define DMAx_CDNE( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_CDNE_OFFSET ) )

#define DMAx_CDNEbits( base )                                                  \
    ( ( typeDMA_CDNEBITS* )DMAx_CDNE( base ) )

#define DMAx_SSRT( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_SSRT_OFFSET ) )

#define DMAx_SSRTbits( base )                                                  \
    ( ( typeDMA_SSRTBITS* )DMAx_SSRT( base ) )

#define DMAx_CERR( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_CERR_OFFSET ) )

#define DMAx_CERRbits( base )                                                  \
    ( ( typeDMA_CERRBITS* )DMAx_CERR( base ) )

#define DMAx_CINT( base )                                                      \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_CINT_OFFSET ) )

#define DMAx_CINTbits( base )                                                  \
    ( ( typeDMA_CINTBITS* )DMAx_CINT( base ) )

#define DMAx_INT( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_INT_OFFSET ) )

#define DMAx_INTbits( base )                                                   \
    ( ( typeDMA_INTBITS* )DMAx_INT( base ) )

#define DMAx_ERR( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_ERR_OFFSET ) )

#define DMAx_ERRbits( base )                                                   \
    ( ( typeDMA_ERRBITS* )DMAx_ERR( base ) )

#define DMAx_HRS( base )                                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_HRS_OFFSET ) )

#define DMAx_HRSbits( base )                                                   \
    ( ( typeDMA_HRSBITS* )DMAx_HRS( base ) )

#define DMAx_DCHPRIn( base, channel )                                          \
    ( ( uint8_t* )( ( uint8_t* )base + DMA_DCHPRIn_OFFSET( channel ) ) )

#define DMAx_DCHPRInbits( base, channel )                                      \
    ( ( typeDMA_DCHPRInBITS* )DMAx_DCHPRIn( base, channel ) )

#define DMAx_TCDn_SADDR( base, channel )                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_TCDn_SADDR_OFFSET( channel ) ) )

#define DMAx_TCDn_SADDRbits( base, channel )                                   \
    ( ( typeDMA_TCDn_SADDRBITS* )DMAx_TCDn_SADDR( base, channel ) )
    
#define DMAx_TCDn_SOFF( base, channel )                                        \
    ( ( uint16_t* )( ( uint8_t* )base + DMA_TCDn_SOFF_OFFSET( channel ) ) )

#define DMAx_TCDn_SOFFbits( base, channel )                                    \
    ( ( typeDMA_TCDn_SOFFBITS* )DMAx_TCDn_SOFF( base, channel ) )

#define DMAx_TCDn_ATTR( base, channel )                                        \
    ( ( uint16_t* )( ( uint8_t* )base + DMA_TCDn_ATTR_OFFSET( channel ) ) )

#define DMAx_TCDn_ATTRbits( base, channel )                                    \
    ( ( typeDMA_TCDn_ATTRBITS* )DMAx_TCDn_ATTR( base, channel ) )

#define DMAx_TCDn_NBYTES_MLNO( base, channel )                                 \
    ( ( uint32_t* )                                                            \
        ( ( uint8_t* )base + DMA_TCDn_NBYTES_MLNO_OFFSET( channel ) ) )

#define DMAx_TCDn_NBYTES_MLNObits( base, channel )                             \
    ( ( typeDMA_TCDn_NBYTES_MLNOBITS* )DMAx_TCDn_NBYTES_MLNO( base, channel ) )

#define DMAx_TCDn_NBYTES_MLOFFNO( base, channel )                              \
    ( ( uint32_t* )                                                            \
        ( ( uint8_t* )base + DMA_TCDn_NBYTES_MLOFFNO_OFFSET( channel ) ) )

#define DMAx_TCDn_NBYTES_MLOFFNObits( base, channel )                          \
    ( ( typeDMA_TCDn_NBYTES_MLOFFNOBITS* )                                     \
        DMAx_TCDn_NBYTES_MLOFFNO( base, channel ) )

#define DMAx_TCDn_NBYTES_MLOFFYES( base, channel )                             \
    ( ( uint32_t* )                                                            \
        ( ( uint8_t* )base + DMA_TCDn_NBYTES_MLOFFYES_OFFSET( channel ) ) )

#define DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )                         \
    ( ( typeDMA_TCDn_NBYTES_MLOFFYESBITS* )                                    \
        DMAx_TCDn_NBYTES_MLOFFYES( base, channel ) )

#define DMAx_TCDn_SLAST( base, channel )                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_TCDn_SLAST_OFFSET( channel ) ) )

#define DMAx_TCDn_SLASTbits( base, channel )                                   \
    ( ( typeDMA_TCDn_SLASTBITS* )DMAx_TCDn_SLAST( base, channel ) )

#define DMAx_TCDn_DADDR( base, channel )                                       \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_TCDn_DADDR_OFFSET( channel ) ) )

#define DMAx_TCDn_DADDRbits( base, channel )                                   \
    ( ( typeDMA_TCDn_DADDRBITS* )DMAx_TCDn_DADDR( base, channel ) )

#define DMAx_TCDn_DOFF( base, channel )                                        \
    ( ( uint16_t* )( ( uint8_t* )base + DMA_TCDn_DOFF_OFFSET( channel ) ) )

#define DMAx_TCDn_DOFFbits( base, channel )                                    \
    ( ( typeDMA_TCDn_DOFFBITS* )DMAx_TCDn_DOFF( base, channel ) )

#define DMAx_TCDn_CITER_ELINKYES( base, channel )                              \
    ( ( uint16_t* )                                                            \
        ( ( uint8_t* )base + DMA_TCDn_CITER_ELINKYES_OFFSET( channel ) ) )

#define DMAx_TCDn_CITER_ELINKYESbits( base, channel )                          \
    ( ( typeDMA_TCDn_CITER_ELINKYESBITS* )                                     \
        DMAx_TCDn_CITER_ELINKYES( base, channel ) )

#define DMAx_TCDn_CITER_ELINKNO( base, channel )                               \
    ( ( uint16_t* )                                                           \
        ( ( uint8_t* )base + DMA_TCDn_CITER_ELINKNO_OFFSET( channel ) ) )

#define DMAx_TCDn_CITER_ELINKNObits( base, channel )                           \
    ( ( typeDMA_TCDn_CITER_ELINKNOBITS* )                                      \
        DMAx_TCDn_CITER_ELINKNO( base, channel ) )

#define DMAx_TCDn_DLASTSGA( base, channel )                                    \
    ( ( uint32_t* )( ( uint8_t* )base + DMA_TCDn_DLASTSGA_OFFSET( channel ) ) )

#define DMAx_TCDn_DLASTSGAbits( base, channel )                                \
    ( ( typeDMA_TCDn_DLASTSGABITS* )DMAx_TCDn_DLASTSGA( base, channel ) )

#define DMAx_TCDn_CSR( base, channel )                                         \
    ( ( uint16_t* )( ( uint8_t* )base + DMA_TCDn_CSR_OFFSET( channel ) ) )

#define DMAx_TCDn_CSRbits( base, channel )                                     \
    ( ( typeDMA_TCDn_CSRBITS* )DMAx_TCDn_CSR( base, channel ) )

#define DMAx_TCDn_BITER_ELINKYES( base, channel )                              \
    ( ( uint16_t* )                                                            \
        ( ( uint8_t* )base + DMA_TCDn_BITER_ELINKYES_OFFSET( channel ) ) )

#define DMAx_TCDn_BITER_ELINKYESbits( base, channel )                          \
    ( ( typeDMA_TCDn_BITER_ELINKYESBITS* )                                     \
        DMAx_TCDn_BITER_ELINKYES( base, channel ) )

#define DMAx_TCDn_BITER_ELINKNO( base, channel )                               \
    ( ( uint16_t* )                                                            \
        ( ( uint8_t* )base + DMA_TCDn_BITER_ELINKNO_OFFSET( channel ) ) )

#define DMAx_TCDn_BITER_ELINKNObits( base, channel )                           \
    ( ( typeDMA_TCDn_BITER_ELINKNOBITS* )                                      \
        DMAx_TCDn_BITER_ELINKNO( base, channel ) )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef struct tagDMA_CRBITS {
    unsigned : 1;
    unsigned EDBG : 1;
    unsigned ERCA : 1;
    unsigned : 1;
    unsigned HOE : 1;
    unsigned HALT : 1;
    unsigned CLM : 1;
    unsigned EMLM : 1;
    unsigned : 8;
    unsigned ECX : 1;
    unsigned CX : 1;
    unsigned : 14;
} typeDMA_CRBITS;

typedef struct tagDMA_ESBITS {
    unsigned DBE : 1;
    unsigned SBE : 1;
    unsigned SGE : 1;
    unsigned NCE : 1;
    unsigned DOE : 1;
    unsigned DAE : 1;
    unsigned SOE : 1;
    unsigned SAE : 1;
    unsigned ERRCHN : 4;
    unsigned : 2;
    unsigned CPE : 1;
    unsigned : 1;
    unsigned ECX : 1;
    unsigned : 14;
    unsigned VLD : 1;
} typeDMA_ESBITS;

typedef struct tagDMA_ERQBITS {
    unsigned ERQ0 : 1;
    unsigned ERQ1 : 1;
    unsigned ERQ2 : 1;
    unsigned ERQ3 : 1;
    unsigned ERQ4 : 1;
    unsigned ERQ5 : 1;
    unsigned ERQ6 : 1;
    unsigned ERQ7 : 1;
    unsigned ERQ8 : 1;
    unsigned ERQ9 : 1;
    unsigned ERQ10 : 1;
    unsigned ERQ11 : 1;
    unsigned ERQ12 : 1;
    unsigned ERQ13 : 1;
    unsigned ERQ14 : 1;
    unsigned ERQ15 : 1;
    unsigned : 16;
} typeDMA_ERQBITS;

typedef struct tagDMA_EEIBITS {
    unsigned EEI0 : 1;
    unsigned EEI1 : 1;
    unsigned EEI2 : 1;
    unsigned EEI3 : 1;
    unsigned EEI4 : 1;
    unsigned EEI5 : 1;
    unsigned EEI6 : 1;
    unsigned EEI7 : 1;
    unsigned EEI8 : 1;
    unsigned EEI9 : 1;
    unsigned EEI10 : 1;
    unsigned EEI11 : 1;
    unsigned EEI12 : 1;
    unsigned EEI13 : 1;
    unsigned EEI14 : 1;
    unsigned EEI15 : 1;
    unsigned : 16;
} typeDMA_EEIBITS;

typedef struct tagDMA_CEEIBITS {
    unsigned CEEI : 4;
    unsigned : 2;
    unsigned CAEE : 1;
    unsigned NOP : 1;
} typeDMA_CEEIBITS;

typedef struct tagDMA_SEEIBITS {
    unsigned SEEI : 4;
    unsigned : 2;
    unsigned SAEE : 1;
    unsigned NOP : 1;
} typeDMA_SEEIBITS;

typedef struct tagDMA_CERQBITS {
    unsigned CERQ : 4;
    unsigned : 2;
    unsigned CAER : 1;
    unsigned NOP : 1;
} typeDMA_CERQBITS;

typedef struct tagDMA_SERQBITS {
    unsigned SERQ : 4;
    unsigned : 2;
    unsigned SAER : 1;
    unsigned NOP : 1;
} typeDMA_SERQBITS;

typedef struct tagDMA_CDNEBITS {
    unsigned CDNE : 4;
    unsigned : 2;
    unsigned CADN : 1;
    unsigned NOP : 1;
} typeDMA_CDNEBITS;

typedef struct tagDMA_SSRTBITS {
    unsigned SSRT : 4;
    unsigned : 2;
    unsigned SAST : 1;
    unsigned NOP : 1;
} typeDMA_SSRTBITS;

typedef struct tagDMA_CERRBITS {
    unsigned CERR : 4;
    unsigned : 2;
    unsigned CAEI : 1;
    unsigned NOP : 1;
} typeDMA_CERRBITS;

typedef struct tagDMA_CINTBITS {
    unsigned CINT : 4;
    unsigned : 2;
    unsigned CAIR : 1;
    unsigned NOP : 1;
} typeDMA_CINTBITS;

typedef struct tagDMA_INTBITS {
    unsigned INT0 : 1;
    unsigned INT1 : 1;
    unsigned INT2 : 1;
    unsigned INT3 : 1;
    unsigned INT4 : 1;
    unsigned INT5 : 1;
    unsigned INT6 : 1;
    unsigned INT7 : 1;
    unsigned INT8_ : 1;
    unsigned INT9 : 1;
    unsigned INT10 : 1;
    unsigned INT11 : 1;
    unsigned INT12 : 1;
    unsigned INT13 : 1;
    unsigned INT14 : 1;
    unsigned INT15 : 1;
    unsigned : 16;
} typeDMA_INTBITS;

typedef struct tagDMA_ERRBITS {
    unsigned ERR0 : 1;
    unsigned ERR1 : 1;
    unsigned ERR2 : 1;
    unsigned ERR3 : 1;
    unsigned ERR4 : 1;
    unsigned ERR5 : 1;
    unsigned ERR6 : 1;
    unsigned ERR7 : 1;
    unsigned ERR8 : 1;
    unsigned ERR9 : 1;
    unsigned ERR10 : 1;
    unsigned ERR11 : 1;
    unsigned ERR12 : 1;
    unsigned ERR13 : 1;
    unsigned ERR14 : 1;
    unsigned ERR15 : 1;
    unsigned : 16;
} typeDMA_ERRBITS;

typedef struct tagDMA_HRSBITS {
    unsigned HRS0 : 1;
    unsigned HRS1 : 1;
    unsigned HRS2 : 1;
    unsigned HRS3 : 1;
    unsigned HRS4 : 1;
    unsigned HRS5 : 1;
    unsigned HRS6 : 1;
    unsigned HRS7 : 1;
    unsigned HRS8 : 1;
    unsigned HRS9 : 1;
    unsigned HRS10 : 1;
    unsigned HRS11 : 1;
    unsigned HRS12 : 1;
    unsigned HRS13 : 1;
    unsigned HRS14 : 1;
    unsigned HRS15 : 1;
    unsigned : 16;
} typeDMA_HRSBITS;

typedef struct tagDMA_DCHPRInBITS {
    unsigned CHPRI : 4;
    unsigned : 2;
    unsigned DPA : 1;
    unsigned ECP : 1;
} typeDMA_DCHPRInBITS;

typedef struct tagDMA_TCDn_SADDRBITS {
    unsigned SADDR : 32;
} typeDMA_TCDn_SADDRBITS;

typedef struct tagDMA_TCDn_SOFFBITS {
    unsigned SOFF : 16;
} typeDMA_TCDn_SOFFBITS;

typedef struct tagDMA_TCDn_ATTRBITS {
    unsigned DSIZE : 3;
    unsigned DMOD : 5;
    unsigned SSIZE : 3;
    unsigned SMOD : 5;
} typeDMA_TCDn_ATTRBITS;

typedef struct tagDMA_TCDn_NBYTES_MLNOBITS {
    unsigned NBYTES : 32;
} typeDMA_TCDn_NBYTES_MLNOBITS;

typedef struct tagDMA_TCDn_NBYTES_MLOFFNOBITS {
    unsigned NBYTES : 30;
    unsigned DMLOE : 1;
    unsigned SMLOE : 1;
} typeDMA_TCDn_NBYTES_MLOFFNOBITS;

typedef struct tagDMA_TCDn_NBYTES_MLOFFYESBITS {
    unsigned NBYTES : 10;
    unsigned MLOFF : 20;
    unsigned DMLOE : 1;
    unsigned SMLOE : 1;
} typeDMA_TCDn_NBYTES_MLOFFYESBITS;

typedef struct tagDMA_TCDn_SLASTBITS {
    unsigned SLAST : 32;
} typeDMA_TCDn_SLASTBITS;

typedef struct tagDMA_TCDn_DADDRBITS {
    unsigned DADDR : 32;
} typeDMA_TCDn_DADDRBITS;

typedef struct tagDMA_TCDn_DOFFBITS {
    unsigned DOFF : 16;
} typeDMA_TCDn_DOFFBITS;

typedef struct tagDMA_TCDn_CITER_ELINKYESBITS {
    unsigned CITER : 9;
    unsigned LINKCH : 4;
    unsigned : 2;
    unsigned ELINK : 1;
} typeDMA_TCDn_CITER_ELINKYESBITS;

typedef struct tagDMA_TCDn_CITER_ELINKNOBITS {
    unsigned CITER : 15;
    unsigned ELINK : 1;
} typeDMA_TCDn_CITER_ELINKNOBITS;

typedef struct tagDMA_TCDn_DLASTSGABITS {
    unsigned DLASTSGA : 32;
} typeDMA_TCDn_DLASTSGABITS;

typedef struct tagDMA_TCDn_CSRBITS {
    unsigned START : 1;
    unsigned INTMAJOR : 1;
    unsigned INTHALF : 1;
    unsigned DREQ : 1;
    unsigned ESG : 1;
    unsigned MAJORELINK : 1;
    unsigned ACTIVE : 1;
    unsigned DONE : 1;
    unsigned MAJORLINKCH : 4;
    unsigned : 2;
    unsigned BWC : 2;
} typeDMA_TCDn_CSRBITS;

typedef struct tagDMA_TCDn_BITER_ELINKYESBITS {
    unsigned BITER : 9;
    unsigned LINKCH : 4;
    unsigned : 2;
    unsigned ELINK : 1;
} typeDMA_TCDn_BITER_ELINKYESBITS;

typedef struct tagDMA_TCDn_BITER_ELINKNOBITS {
    unsigned BITER : 15;
    unsigned ELINK : 1;
} typeDMA_TCDn_BITER_ELINKNOBITS;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Gets the begin major iteration count
// according to minor loop channel link setting.
uint32_t EDMA_HAL_HTCDGetBeginMajorCount( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return 0;

    if( DMAx_TCDn_BITER_ELINKNObits( base, channel )->ELINK )
    {
        return DMAx_TCDn_BITER_ELINKYESbits( base, channel )->BITER;
    }
    else
    {
        return DMAx_TCDn_BITER_ELINKNObits( base, channel )->BITER;;
    }
}

// Gets the current major iteration count
// according to minor loop channel link setting.
uint32_t EDMA_HAL_HTCDGetCurrentMajorCount( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return 0;

    if( DMAx_TCDn_BITER_ELINKNObits( base, channel )->ELINK )
    {
        return DMAx_TCDn_CITER_ELINKYESbits( base, channel )->CITER;
    }
    else
    {
        return DMAx_TCDn_CITER_ELINKNObits( base, channel )->CITER;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// eDMA HAL driver module level operation

// Initializes eDMA module to known state.
void EDMA_HAL_Init( uint32_t* base )
{
    uint32_t i;

    // Clear the bit of CR register
    DMAx_CRbits( base )->CLM = 0;
    DMAx_CRbits( base )->CX = 0;
    DMAx_CRbits( base )->ECX = 0;
    DMAx_CRbits( base )->EDBG = 0;
    DMAx_CRbits( base )->EMLM = 0;
    DMAx_CRbits( base )->ERCA = 0;
    
    for( i = 0; i < FSL_FEATURE_EDMA_MODULE_CHANNEL; i++ )
    {
        EDMA_HAL_HTCDClearReg( base, i );
    }
}

// Cancels the remaining data transfer.
void EDMA_HAL_CancelTransfer( uint32_t* base )
{
    DMAx_CRbits( base )->CX = 1;
    while( DMAx_CRbits( base )->CX == 1 ) {}
}

// Cancels the remaining data transfer and treats it as an error condition.
void EDMA_HAL_ErrorCancelTransfer( uint32_t* base )
{
    DMAx_CRbits( base )->ECX = 1;
    while( DMAx_CRbits( base )->ECX == 1 ) {}
}

// Halts/Un-halts the DMA Operations.
void EDMA_HAL_SetHaltCmd( uint32_t* base, bool halt )
{
    DMAx_CRbits( base )->HALT = halt;
}

// Halts or does not halt the eDMA module when an error occurs.
void EDMA_HAL_SetHaltOnErrorCmd( uint32_t* base, bool haltOnError )
{
    DMAx_CRbits( base )->HOE = haltOnError;
}

// Enables/Disables the eDMA DEBUG mode.
void EDMA_HAL_SetDebugCmd( uint32_t* base, bool enable )
{
    DMAx_CRbits( base )->EDBG = enable;
}

// eDMA HAL driver channel priority and arbitration configuration.

// Sets the preempt and preemption feature for the eDMA channel.
void EDMA_HAL_SetChannelPreemptMode( uint32_t* base,
    uint32_t channel, bool preempt, bool preemption )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    DMAx_DCHPRInbits( base, channel )->DPA = preempt;
    DMAx_DCHPRInbits( base, channel )->ECP = preemption;
}

// Sets the eDMA channel priority.
void EDMA_HAL_SetChannelPriority( uint32_t* base,
    uint32_t channel, edma_channel_priority_t priority )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    DMAx_DCHPRInbits( base, channel )->CHPRI = priority;
}

// Sets the channel arbitration algorithm.
void EDMA_HAL_SetChannelArbitrationMode( uint32_t* base,
    edma_channel_arbitration_t channelArbitration )
{
    DMAx_CRbits( base )->ERCA = channelArbitration;
}

// eDMA HAL driver configuration and operation.

// Enables/Disables the minor loop mapping.
void EDMA_HAL_SetMinorLoopMappingCmd( uint32_t* base, bool enable )
{
    DMAx_CRbits( base )->EMLM = enable;
}

// Enables or disables the continuous transfer mode.
void EDMA_HAL_SetContinuousLinkCmd( uint32_t* base, bool continuous )
{
    DMAx_CRbits( base )->CLM = continuous;
}

// Gets the error status of the eDMA module.
edma_error_status_all_t EDMA_HAL_GetErrorStatus( uint32_t* base )
{
    edma_error_status_all_t status;
    uint32_t val = *DMAx_ES( base );
    
    status.destinationBusError =
        ( bool )( ( val & DMA_ES_DBE_MASK ) >> DMA_ES_DBE_SHIFT );
    status.sourceBusError =
        ( bool )( ( val & DMA_ES_SBE_MASK ) >> DMA_ES_SBE_SHIFT );
    status.scatterOrGatherConfigurationError =
        ( bool )( ( val & DMA_ES_SGE_MASK ) >> DMA_ES_SGE_SHIFT );
    status.nbyteOrCiterConfigurationError =
        ( bool )( ( val & DMA_ES_NCE_MASK ) >> DMA_ES_NCE_SHIFT );
    status.destinationOffsetError =
        ( bool )( ( val & DMA_ES_DOE_MASK ) >> DMA_ES_DOE_SHIFT );
    status.destinationAddressError =
        ( bool )( ( val & DMA_ES_DAE_MASK ) >> DMA_ES_DAE_SHIFT );
    status.sourceOffsetError =
        ( bool )( ( val & DMA_ES_SOE_MASK ) >> DMA_ES_SOE_SHIFT );
    status.sourceAddressError =
        ( bool )( ( val & DMA_ES_SAE_MASK ) >> DMA_ES_SAE_SHIFT );
    status.errorChannel =
        ( uint8_t )( ( val & DMA_ES_ERRCHN_MASK ) >> DMA_ES_ERRCHN_SHIFT );
    status.channelPriorityError =
        ( bool )( ( val & DMA_ES_CPE_MASK ) >> DMA_ES_CPE_SHIFT );
    status.transferCancelledError =
        ( bool )( ( val & DMA_ES_ECX_MASK ) >> DMA_ES_ECX_SHIFT );
    status.orOfAllError =
        ( bool )( ( val & DMA_ES_VLD_MASK ) >> DMA_ES_VLD_SHIFT );
        
    return status;
}

// Enables/Disables the error interrupt for channels.
void EDMA_HAL_SetErrorIntCmd( uint32_t* base,
    bool enable, edma_channel_indicator_t channel )
{
    if( enable )
    {
        *DMAx_SEEI( base ) = channel;
    }
    else
    {
        *DMAx_CEEI( base ) = channel;
    }
}

// Gets the eDMA error interrupt status.
uint32_t EDMA_HAL_GetErrorIntStatusFlag( uint32_t* base )
{
    return *DMAx_ERR( base );
}

// Clears the error interrupt status for the eDMA channel or channels.
void EDMA_HAL_ClearErrorIntStatusFlag( uint32_t* base,
    edma_channel_indicator_t channel )
{
    *DMAx_CERR( base ) = channel;
}

// Enables/Disables the DMA request for the channel or all channels.
void EDMA_HAL_SetDmaRequestCmd( uint32_t* base,
    edma_channel_indicator_t channel, bool enable )
{
    if( enable )
    {
        *DMAx_SERQ( base ) = channel;
    }
    else
    {
        *DMAx_CERQ( base ) = channel;
    }
}

// Gets the eDMA channel DMA request status.
bool EDMA_HAL_GetDmaRequestStatusFlag( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return false;
    
    return ( ( uint32_t )*DMAx_HRS( base ) >> channel ) & 0x1U;
}

// Clears the done status for a channel or all channels.
void EDMA_HAL_ClearDoneStatusFlag( uint32_t* base,
    edma_channel_indicator_t channel )
{
    *DMAx_CDNE( base ) = channel;
}

// Triggers the eDMA channel.
void EDMA_HAL_TriggerChannelStart( uint32_t* base,
    edma_channel_indicator_t channel )
{
    *DMAx_SSRT( base ) = channel;
}

// Gets the eDMA channel interrupt request status.
bool EDMA_HAL_GetIntStatusFlag( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return false;
    
    return ( ( uint32_t )*DMAx_INT( base ) >> channel ) & 0x1U;
}

// Clears the interrupt status for the eDMA channel or all channels.
void EDMA_HAL_ClearIntStatusFlag( uint32_t* base,
    edma_channel_indicator_t channel )
{
    *DMAx_CINT( base ) = channel;
}

// Clears all registers to 0 for the hardware TCD.
void EDMA_HAL_HTCDClearReg( uint32_t* base, uint32_t channel )
{
    *DMAx_TCDn_SADDR( base, channel ) = 0;
    *DMAx_TCDn_SOFF( base, channel ) = 0;
    *DMAx_TCDn_ATTR( base, channel ) = 0;
    *DMAx_TCDn_NBYTES_MLNO( base, channel ) = 0;
    *DMAx_TCDn_SLAST( base, channel ) = 0;
    *DMAx_TCDn_DADDR( base, channel ) = 0;
    *DMAx_TCDn_DOFF( base, channel ) = 0;
    *DMAx_TCDn_CITER_ELINKNO( base, channel ) = 0;
    *DMAx_TCDn_DLASTSGA( base, channel ) = 0;
    *DMAx_TCDn_CSR( base, channel ) = 0;
    *DMAx_TCDn_BITER_ELINKNO( base, channel ) = 0;
}

// Configures the source address for the hardware TCD.
void EDMA_HAL_HTCDSetSrcAddr( uint32_t* base,
    uint32_t channel, uint32_t address )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    *DMAx_TCDn_SADDR( base, channel ) = address;
}

// Configures the source address signed offset for the hardware TCD.
void EDMA_HAL_HTCDSetSrcOffset( uint32_t* base,
    uint32_t channel, int16_t offset )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    *DMAx_TCDn_SOFF( base, channel ) = offset;
}

// Configures the transfer attribute for the eDMA channel.
void EDMA_HAL_HTCDSetAttribute( uint32_t* base, uint32_t channel,
    edma_modulo_t srcModulo, edma_modulo_t destModulo,
    edma_transfer_size_t srcTransferSize,
    edma_transfer_size_t destTransferSize )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    *DMAx_TCDn_ATTR( base, channel ) = DMA_ATTR_SMOD( srcModulo ) |
                                       DMA_ATTR_DMOD( destModulo ) |
                                       DMA_ATTR_SSIZE( srcTransferSize ) |
                                       DMA_ATTR_DSIZE( destTransferSize );
}

// Configures the nbytes for the eDMA channel.
void EDMA_HAL_HTCDSetNbytes( uint32_t* base,
    uint32_t channel, uint32_t nbytes )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    if( DMAx_CRbits( base )->EMLM != 0 )
    {
        if( !( DMAx_TCDn_NBYTES_MLOFFNObits( base, channel )->SMLOE ||
               DMAx_TCDn_NBYTES_MLOFFNObits( base, channel )->DMLOE ) )
        {
              DMAx_TCDn_NBYTES_MLOFFNObits( base, channel )->NBYTES = nbytes;
        }
        else
        {
              DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->NBYTES = nbytes;
        }
    }
    else
    {
          DMAx_TCDn_NBYTES_MLNObits( base, channel )->NBYTES = nbytes;
    }
}

// Gets the nbytes configuration data for the hardware TCD.
uint32_t EDMA_HAL_HTCDGetNbytes( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return 0;

    if( DMAx_CRbits( base )->EMLM != 0 )
    {
        if( ( DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->SMLOE ||
              DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->DMLOE ) )
        {
            return DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->NBYTES;
        }
        else
        {
            return DMAx_TCDn_NBYTES_MLOFFNObits( base, channel )->NBYTES;
        }
    }
    else
    {
        return DMAx_TCDn_NBYTES_MLNObits( base, channel )->NBYTES;
    }
}

// Configures the minor loop offset for the hardware TCD.
void EDMA_HAL_HTCDSetMinorLoopOffset( uint32_t* base,
    uint32_t channel, edma_minorloop_offset_config_t *config )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    if( ( config->enableSrcMinorloop ) || ( config->enableDestMinorloop ) )
    {
        DMAx_CRbits( base )->EMLM = true;
        DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->SMLOE =
            config->enableSrcMinorloop;
        DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->DMLOE =
            config->enableDestMinorloop;
        DMAx_TCDn_NBYTES_MLOFFYESbits( base, channel )->MLOFF =
            config->offset;
    }
}

// Configures the last source address adjustment for the hardware TCD.
void EDMA_HAL_HTCDSetSrcLastAdjust( uint32_t* base,
    uint32_t channel, int32_t size )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    *DMAx_TCDn_SLAST( base, channel ) = size;
}

// Configures the destination address for the hardware TCD.
void EDMA_HAL_HTCDSetDestAddr( uint32_t* base,
    uint32_t channel, uint32_t address )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    *DMAx_TCDn_DADDR( base, channel ) = address;
}

// Configures the destination address signed offset for the hardware TCD.
void EDMA_HAL_HTCDSetDestOffset( uint32_t* base,
    uint32_t channel, int16_t offset )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    *DMAx_TCDn_DOFF( base, channel ) = offset;
}

// Configures the last source address adjustment.
void EDMA_HAL_HTCDSetDestLastAdjust( uint32_t* base,
    uint32_t channel, uint32_t adjust )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    *DMAx_TCDn_DLASTSGA( base, channel ) = adjust;
}

// Configures the memory address for the next transfer TCD for the hardware TCD.
void EDMA_HAL_HTCDSetScatterGatherLink( uint32_t* base,
    uint32_t channel, edma_software_tcd_t *stcd )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    DMAx_TCDn_CSRbits( base, channel )->ESG = true;
    *DMAx_TCDn_DLASTSGA( base, channel ) = ( uint32_t )stcd;
}

// Configures the bandwidth for the hardware TCD.
void EDMA_HAL_HTCDSetBandwidth( uint32_t* base,
    uint32_t channel, edma_bandwidth_config_t bandwidth )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    DMAx_TCDn_CSRbits( base, channel )->BWC = bandwidth;
    
}

// Configures the major channel link the hardware TCD.
void EDMA_HAL_HTCDSetChannelMajorLink( uint32_t* base,
    uint32_t channel, uint32_t majorChannel, bool enable )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    DMAx_TCDn_CSRbits( base, channel )->MAJORLINKCH = majorChannel;
    DMAx_TCDn_CSRbits( base, channel )->MAJORELINK = enable;
}

// Enables/Disables the scatter/gather feature for the hardware TCD.
void EDMA_HAL_HTCDSetScatterGatherCmd( uint32_t* base,
    uint32_t channel, bool enable )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    DMAx_TCDn_CSRbits( base, channel )->ESG = enable;
}

// Disables/Enables the DMA request
// after the major loop completes for the hardware TCD.
void EDMA_HAL_HTCDSetDisableDmaRequestAfterTCDDoneCmd( uint32_t* base,
    uint32_t channel, bool disable )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    DMAx_TCDn_CSRbits( base, channel )->DREQ = disable;
}

// Enables/Disables the half complete interrupt for the hardware TCD.
void EDMA_HAL_HTCDSetHalfCompleteIntCmd( uint32_t* base,
    uint32_t channel, bool enable )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    DMAx_TCDn_CSRbits( base, channel )->INTHALF = enable;
}

// Enables/Disables the interrupt
// after the major loop completes for the hardware TCD.
void EDMA_HAL_HTCDSetIntCmd( uint32_t* base, uint32_t channel, bool enable )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    DMAx_TCDn_CSRbits( base, channel )->INTMAJOR = enable;
}

// Triggers the start bits for the hardware TCD.
void EDMA_HAL_HTCDTriggerChannelStart( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;

    DMAx_TCDn_CSRbits( base, channel )->START = true;
}

// Checks whether the channel is running for the hardware TCD.
bool EDMA_HAL_HTCDGetChannelActiveStatus( uint32_t* base, uint32_t channel )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return false;

    return DMAx_TCDn_CSRbits( base, channel )->ACTIVE;
}

// Sets the channel minor link for the hardware TCD.
void EDMA_HAL_HTCDSetChannelMinorLink( uint32_t* base,
    uint32_t channel, uint32_t linkChannel, bool enable )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    if( enable )
    {
        DMAx_TCDn_BITER_ELINKYESbits( base, channel )->ELINK = enable;
        DMAx_TCDn_BITER_ELINKYESbits( base, channel )->LINKCH = linkChannel;
        DMAx_TCDn_CITER_ELINKYESbits( base, channel )->ELINK = enable;
        DMAx_TCDn_CITER_ELINKYESbits( base, channel )->LINKCH = linkChannel;
    }
    else
    {
        DMAx_TCDn_BITER_ELINKNObits( base, channel )->ELINK = enable;
        DMAx_TCDn_CITER_ELINKNObits( base, channel )->ELINK = enable;
    }
}

// Sets the major iteration count according to minor loop channel link setting.
void EDMA_HAL_HTCDSetMajorCount( uint32_t* base,
    uint32_t channel, uint32_t count )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    
    if( DMAx_TCDn_BITER_ELINKNObits( base, channel )->ELINK )
    {
        DMAx_TCDn_BITER_ELINKYESbits( base, channel )->BITER = count;
        DMAx_TCDn_CITER_ELINKYESbits( base, channel )->CITER = count;
    }
    else
    {
        DMAx_TCDn_BITER_ELINKNObits( base, channel )->BITER = count;
        DMAx_TCDn_CITER_ELINKNObits( base, channel )->CITER = count;
    }
}

// Gets the number of bytes already transferred for the hardware TCD.
uint32_t EDMA_HAL_HTCDGetFinishedBytes( uint32_t* base, uint32_t channel )
{
    uint32_t nbytes;
    uint32_t begin_majorcount;
    uint32_t current_majorcount;

    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return 0;
    
    nbytes = EDMA_HAL_HTCDGetNbytes( base, channel );
    begin_majorcount = EDMA_HAL_HTCDGetBeginMajorCount( base, channel );
    current_majorcount = EDMA_HAL_HTCDGetCurrentMajorCount( base, channel );

    return ( ( begin_majorcount - current_majorcount ) * nbytes );
}

// Gets the number of bytes haven't transferred for the hardware TCD.
uint32_t EDMA_HAL_HTCDGetUnfinishedBytes( uint32_t* base, uint32_t channel )
{
    uint32_t nbytes;

    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return 0;
    
    nbytes = EDMA_HAL_HTCDGetNbytes( base, channel );

    if( DMAx_TCDn_BITER_ELINKNObits( base, channel )->ELINK )
    {
        return DMAx_TCDn_CITER_ELINKYESbits( base, channel )->CITER * nbytes;
    }
    else
    {
        return DMAx_TCDn_CITER_ELINKNObits( base, channel )->CITER * nbytes;
    }
}

// Gets the channel done status.
bool EDMA_HAL_HTCDGetDoneStatusFlag( uint32_t* base, uint32_t channel )
{
    return DMAx_TCDn_CSRbits( base, channel )->DONE;
}

// EDMA HAL driver software TCD configuration functions.

// Configures the source address for the software TCD.
void EDMA_HAL_STCDSetSrcAddr( edma_software_tcd_t *stcd, uint32_t address )
{
    if( !stcd ) return;
    
    stcd->SADDR = DMA_SADDR_SADDR( address );
}

// Configures the source address signed offset for the software TCD.
void EDMA_HAL_STCDSetSrcOffset( edma_software_tcd_t *stcd, int16_t offset )
{
    if( !stcd ) return;
    
    stcd->SOFF = DMA_SOFF_SOFF( offset );
}

// Configures the transfer attribute for software TCD.
void EDMA_HAL_STCDSetAttribute( edma_software_tcd_t *stcd,
    edma_modulo_t srcModulo, edma_modulo_t destModulo,
    edma_transfer_size_t srcTransferSize,
    edma_transfer_size_t destTransferSize )
{
    if( !stcd ) return;
    
    stcd->ATTR = DMA_ATTR_SMOD( srcModulo ) |
                 DMA_ATTR_DMOD( destModulo ) |
                 DMA_ATTR_SSIZE( srcTransferSize ) |
                 DMA_ATTR_DSIZE( destTransferSize );
}

// Configures the nbytes for software TCD.
void EDMA_HAL_STCDSetNbytes( uint32_t* base,
    edma_software_tcd_t *stcd, uint32_t nbytes )
{
    if( !stcd ) return;
    
    if( DMAx_CRbits( base )->EMLM )
    {
        if( stcd->NBYTES | ( DMA_NBYTES_MLOFFNO_SMLOE_MASK |
            DMA_NBYTES_MLOFFNO_DMLOE_MASK ) )
        {
            stcd->NBYTES = ( stcd->NBYTES & ~DMA_NBYTES_MLOFFYES_NBYTES_MASK ) |
                           DMA_NBYTES_MLOFFYES_NBYTES( nbytes );
        }
        else
        {
            stcd->NBYTES = ( stcd->NBYTES & ~DMA_NBYTES_MLOFFNO_NBYTES_MASK ) |
                           DMA_NBYTES_MLOFFNO_NBYTES( nbytes );
        }
    }
    else
    {
        stcd->NBYTES = ( stcd->NBYTES & ~DMA_NBYTES_MLNO_NBYTES_MASK ) |
                       DMA_NBYTES_MLNO_NBYTES( nbytes );
    }
}

// Configures the minorloop offset for the software TCD.
void EDMA_HAL_STCDSetMinorLoopOffset( uint32_t* base,
    edma_software_tcd_t *stcd, edma_minorloop_offset_config_t *config )
{
    if( !stcd ) return;
        
    stcd->NBYTES = ( stcd->NBYTES &
        ~( DMA_NBYTES_MLOFFYES_SMLOE_MASK | DMA_NBYTES_MLOFFYES_DMLOE_MASK ) ) |
        ( ( ( uint32_t ) config->enableSrcMinorloop <<
            DMA_NBYTES_MLOFFYES_SMLOE_SHIFT ) |
        ( ( uint32_t )config->enableDestMinorloop <<
            DMA_NBYTES_MLOFFYES_DMLOE_SHIFT ) );

    if( ( config->enableSrcMinorloop == true ) ||
        ( config->enableDestMinorloop == true ) )
    {
        DMAx_CRbits( base )->EMLM = true;
        stcd->NBYTES = ( stcd->NBYTES & ~DMA_NBYTES_MLOFFYES_MLOFF_MASK ) |
                       DMA_NBYTES_MLOFFYES_MLOFF( config->offset );
    }
}

// Configures the last source address adjustment for the software TCD.
void EDMA_HAL_STCDSetSrcLastAdjust( edma_software_tcd_t *stcd, int32_t size )
{
    if( !stcd ) return;
    
    stcd->SLAST = ( stcd->SLAST & ~DMA_SLAST_SLAST_MASK ) |
                  DMA_SLAST_SLAST( size );
}

// Configures the destination address for the software TCD.
void EDMA_HAL_STCDSetDestAddr( edma_software_tcd_t *stcd, uint32_t address )
{
    if( !stcd ) return;
    
    stcd->DADDR = DMA_DADDR_DADDR( address );
}

// Configures the destination address signed offset for the software TCD.
void EDMA_HAL_STCDSetDestOffset( edma_software_tcd_t *stcd, int16_t offset )
{
    if( !stcd ) return;
    
    stcd->DOFF = DMA_DOFF_DOFF( offset );
}

// Configures the last source address adjustment.
void EDMA_HAL_STCDSetDestLastAdjust(
    edma_software_tcd_t *stcd, uint32_t adjust )
{
    if( !stcd ) return;
    
    stcd->DLAST_SGA = DMA_DLAST_SGA_DLASTSGA( adjust );
}

// Configures the memory address for the next transfer TCD for the software TCD.
void EDMA_HAL_STCDSetScatterGatherLink(
    edma_software_tcd_t *stcd, edma_software_tcd_t *nextStcd )
{
    if( !stcd ) return;
    if( !nextStcd ) return;
    
    EDMA_HAL_STCDSetScatterGatherCmd( stcd, true );
    stcd->DLAST_SGA = DMA_DLAST_SGA_DLASTSGA( ( uint32_t )nextStcd );
}

// Configures the bandwidth for the software TCD.
void EDMA_HAL_STCDSetBandwidth(
    edma_software_tcd_t *stcd, edma_bandwidth_config_t bandwidth )
{
    if( !stcd ) return;
    
    stcd->CSR = ( stcd->CSR & ~DMA_CSR_BWC_MASK ) | DMA_CSR_BWC( bandwidth );
}

// Configures the major channel link the software TCD.
void EDMA_HAL_STCDSetChannelMajorLink(
    edma_software_tcd_t *stcd, uint32_t majorChannel, bool enable )
{
    if( !stcd ) return;
    
    stcd->CSR = ( stcd->CSR & ~DMA_CSR_MAJORLINKCH_MASK ) |
                DMA_CSR_MAJORLINKCH( majorChannel );
    stcd->CSR = ( stcd->CSR & ~DMA_CSR_MAJORELINK_MASK ) |
                ( ( uint32_t )enable << DMA_CSR_MAJORELINK_SHIFT );

}

// Enables/Disables the scatter/gather feature for the software TCD.
void EDMA_HAL_STCDSetScatterGatherCmd( edma_software_tcd_t *stcd, bool enable )
{
    if( !stcd ) return;

    stcd->CSR = ( stcd->CSR & ~DMA_CSR_ESG_MASK ) |
                ( ( uint32_t )enable << DMA_CSR_ESG_SHIFT );
}

// Disables/Enables the DMA request
// after the major loop completes for the software TCD.
void EDMA_HAL_STCDSetDisableDmaRequestAfterTCDDoneCmd(
    edma_software_tcd_t *stcd, bool disable )
{
    if( !stcd ) return;
    
    stcd->CSR = ( stcd->CSR & ~DMA_CSR_DREQ_MASK ) |
                ( ( uint32_t )disable << DMA_CSR_DREQ_SHIFT );
}

// Enables/Disables the half complete interrupt for the software TCD.
void EDMA_HAL_STCDSetHalfCompleteIntCmd(
    edma_software_tcd_t *stcd, bool enable )
{
    if( !stcd ) return;
    
    stcd->CSR = ( stcd->CSR & ~DMA_CSR_INTHALF_MASK ) |
                ( ( uint32_t )enable << DMA_CSR_INTHALF_SHIFT );
}

// Enables/Disables the interrupt
// after the major loop completes for the software TCD.
void EDMA_HAL_STCDSetIntCmd( edma_software_tcd_t *stcd, bool enable )
{
    if( !stcd ) return;
    
    stcd->CSR = ( stcd->CSR & ~DMA_CSR_INTMAJOR_MASK ) |
                ( ( uint32_t )enable << DMA_CSR_INTMAJOR_SHIFT );
}

// Triggers the start bits for the software TCD.
void EDMA_HAL_STCDTriggerChannelStart( edma_software_tcd_t *stcd )
{
    if( !stcd ) return;
    
    stcd->CSR |= DMA_CSR_START_MASK;
}

// Set Channel minor link for software TCD.
void EDMA_HAL_STCDSetChannelMinorLink(
    edma_software_tcd_t *stcd, uint32_t linkChannel, bool enable )
{
    if( !stcd ) return;
    
    if( enable )
    {
        stcd->BITER = ( stcd->BITER & ~DMA_BITER_ELINKYES_ELINK_MASK ) |
                      ( ( uint32_t )enable << DMA_BITER_ELINKYES_ELINK_SHIFT );
        stcd->BITER = ( stcd->BITER & ~DMA_BITER_ELINKYES_LINKCH_MASK ) |
                      DMA_BITER_ELINKYES_LINKCH( linkChannel );
        stcd->CITER = ( stcd->CITER & ~DMA_CITER_ELINKYES_ELINK_MASK ) |
                      ( ( uint32_t )enable << DMA_CITER_ELINKYES_ELINK_SHIFT );
        stcd->CITER = ( stcd->CITER & ~DMA_CITER_ELINKYES_LINKCH_MASK ) |
                      DMA_CITER_ELINKYES_LINKCH( linkChannel );
    }
    else
    {
        stcd->BITER = ( stcd->BITER & ~DMA_BITER_ELINKNO_ELINK_MASK ) |
                      ( ( uint32_t )enable << DMA_BITER_ELINKNO_ELINK_SHIFT );
        stcd->CITER = ( stcd->CITER & ~DMA_CITER_ELINKNO_ELINK_MASK ) |
                      ( ( uint32_t )enable << DMA_CITER_ELINKNO_ELINK_SHIFT );
    }
}

// Sets the major iteration count according to minor loop channel link setting.
void EDMA_HAL_STCDSetMajorCount( edma_software_tcd_t *stcd, uint32_t count )
{
    if( !stcd ) return;

    if( stcd->BITER & DMA_BITER_ELINKNO_ELINK_MASK )
    {
        stcd->BITER = ( stcd->BITER & ~DMA_BITER_ELINKYES_BITER_MASK ) |
                      DMA_BITER_ELINKYES_BITER( count );
        stcd->CITER = ( stcd->CITER & ~DMA_CITER_ELINKYES_CITER_MASK ) |
                      DMA_CITER_ELINKYES_CITER( count );
    }
    else
    {
        stcd->BITER = ( stcd->BITER & ~DMA_BITER_ELINKNO_BITER_MASK ) |
                      DMA_BITER_ELINKNO_BITER( count );
        stcd->CITER = ( stcd->CITER & ~DMA_CITER_ELINKNO_CITER_MASK ) |
                      DMA_CITER_ELINKNO_CITER( count );
    }
}

// Copy the software TCD configuration to the hardware TCD.
void EDMA_HAL_PushSTCDToHTCD( uint32_t* base,
    uint32_t channel, edma_software_tcd_t *stcd )
{
    if( !( channel < FSL_FEATURE_EDMA_MODULE_CHANNEL ) ) return;
    if( !stcd ) return;
    
    *DMAx_TCDn_SADDR( base, channel ) = stcd->SADDR;
    *DMAx_TCDn_SOFF( base, channel ) = stcd->SOFF;
    *DMAx_TCDn_ATTR( base, channel ) = stcd->ATTR;
    *DMAx_TCDn_NBYTES_MLNO( base, channel ) = stcd->NBYTES;
    *DMAx_TCDn_SLAST( base, channel ) = stcd->SLAST;
    *DMAx_TCDn_DADDR( base, channel ) = stcd->DADDR;
    *DMAx_TCDn_DOFF( base, channel ) = stcd->DOFF;
    *DMAx_TCDn_CITER_ELINKYES( base, channel ) = stcd->CITER;
    *DMAx_TCDn_DLASTSGA( base, channel ) = stcd->DLAST_SGA;
    *DMAx_TCDn_CSR( base, channel ) = stcd->CSR;
    *DMAx_TCDn_BITER_ELINKYES( base, channel ) = stcd->BITER;
}

// Set the basic transfer for software TCD.
edma_status_t EDMA_HAL_STCDSetBasicTransfer( uint32_t* base,
    edma_software_tcd_t *stcd, edma_transfer_config_t *config,
    bool enableInt, bool disableDmaRequest )
{
    if( !stcd ) return;

    EDMA_HAL_STCDSetSrcAddr( stcd, config->srcAddr );
    EDMA_HAL_STCDSetDestAddr( stcd, config->destAddr );

    EDMA_HAL_STCDSetSrcOffset( stcd, config->srcOffset );
    EDMA_HAL_STCDSetDestOffset( stcd, config->destOffset );

    EDMA_HAL_STCDSetAttribute( stcd, config->srcModulo, config->destModulo,
        config->srcTransferSize, config->destTransferSize );

    EDMA_HAL_STCDSetSrcLastAdjust( stcd, config->srcLastAddrAdjust );
    EDMA_HAL_STCDSetDestLastAdjust( stcd, config->destLastAddrAdjust );
    EDMA_HAL_STCDSetNbytes( base, stcd, config->minorLoopCount );
    EDMA_HAL_STCDSetMajorCount( stcd, config->majorLoopCount );

    EDMA_HAL_STCDSetIntCmd( stcd, enableInt );
    EDMA_HAL_STCDSetDisableDmaRequestAfterTCDDoneCmd( stcd, disableDmaRequest );
    
    return kStatus_EDMA_Success;
}