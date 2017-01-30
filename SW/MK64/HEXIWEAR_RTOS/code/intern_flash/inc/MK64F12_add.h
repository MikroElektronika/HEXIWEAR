#ifndef HG_MK64F12_ADD
#define HG_MK64F12_ADD

/** SCB - Peripheral register structure */
typedef struct SCB_MemMap {
  uint8_t RESERVED_0[8];
  uint32_t ACTLR;                                  /**< Auxiliary Control Register,, offset: 0x8 */
  uint8_t RESERVED_1[3316];
  uint32_t CPUID;                                  /**< CPUID Base Register, offset: 0xD00 */
  uint32_t ICSR;                                   /**< Interrupt Control and State Register, offset: 0xD04 */
  uint32_t VTOR;                                   /**< Vector Table Offset Register, offset: 0xD08 */
  uint32_t AIRCR;                                  /**< Application Interrupt and Reset Control Register, offset: 0xD0C */
  uint32_t SCR;                                    /**< System Control Register, offset: 0xD10 */
  uint32_t CCR;                                    /**< Configuration and Control Register, offset: 0xD14 */
  uint32_t SHPR1;                                  /**< System Handler Priority Register 1, offset: 0xD18 */
  uint32_t SHPR2;                                  /**< System Handler Priority Register 2, offset: 0xD1C */
  uint32_t SHPR3;                                  /**< System Handler Priority Register 3, offset: 0xD20 */
  uint32_t SHCSR;                                  /**< System Handler Control and State Register, offset: 0xD24 */
  uint32_t CFSR;                                   /**< Configurable Fault Status Registers, offset: 0xD28 */
  uint32_t HFSR;                                   /**< HardFault Status register, offset: 0xD2C */
  uint32_t DFSR;                                   /**< Debug Fault Status Register, offset: 0xD30 */
  uint32_t MMFAR;                                  /**< MemManage Address Register, offset: 0xD34 */
  uint32_t BFAR;                                   /**< BusFault Address Register, offset: 0xD38 */
  uint32_t AFSR;                                   /**< Auxiliary Fault Status Register, offset: 0xD3C */
} volatile *SCB_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


 /** SCB - Register accessors */
#define SCB_ACTLR_REG(base)                      ((base)->ACTLR)
#define SCB_CPUID_REG(base)                      ((base)->CPUID)
#define SCB_ICSR_REG(base)                       ((base)->ICSR)
#define SCB_VTOR_REG(base)                       ((base)->VTOR)
#define SCB_AIRCR_REG(base)                      ((base)->AIRCR)
#define SCB_SCR_REG(base)                        ((base)->SCR)
#define SCB_CCR_REG(base)                        ((base)->CCR)
#define SCB_SHPR1_REG(base)                      ((base)->SHPR1)
#define SCB_SHPR2_REG(base)                      ((base)->SHPR2)
#define SCB_SHPR3_REG(base)                      ((base)->SHPR3)
#define SCB_SHCSR_REG(base)                      ((base)->SHCSR)
#define SCB_CFSR_REG(base)                       ((base)->CFSR)
#define SCB_HFSR_REG(base)                       ((base)->HFSR)
#define SCB_DFSR_REG(base)                       ((base)->DFSR)
#define SCB_MMFAR_REG(base)                      ((base)->MMFAR)
#define SCB_BFAR_REG(base)                       ((base)->BFAR)
#define SCB_AFSR_REG(base)                       ((base)->AFSR)

/*!
 * @}
 */  /** end of group SCB_Register_Accessor_Macros */


/* ----------------------------------------------------------------------------
   -- SCB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Masks SCB Register Masks
 * @{
 */

 /** ACTLR Bit Fields */
#define SCB_ACTLR_DISMCYCINT_MASK                0x1u
#define SCB_ACTLR_DISMCYCINT_SHIFT               0
#define SCB_ACTLR_DISDEFWBUF_MASK                0x2u
#define SCB_ACTLR_DISDEFWBUF_SHIFT               1
#define SCB_ACTLR_DISFOLD_MASK                   0x4u
#define SCB_ACTLR_DISFOLD_SHIFT                  2
 /** CPUID Bit Fields */
#define SCB_CPUID_REVISION_MASK                  0xFu
#define SCB_CPUID_REVISION_SHIFT                 0
#define SCB_CPUID_REVISION(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_REVISION_SHIFT))&SCB_CPUID_REVISION_MASK)
#define SCB_CPUID_PARTNO_MASK                    0xFFF0u
#define SCB_CPUID_PARTNO_SHIFT                   4
#define SCB_CPUID_PARTNO(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_PARTNO_SHIFT))&SCB_CPUID_PARTNO_MASK)
#define SCB_CPUID_VARIANT_MASK                   0xF00000u
#define SCB_CPUID_VARIANT_SHIFT                  20
#define SCB_CPUID_VARIANT(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_VARIANT_SHIFT))&SCB_CPUID_VARIANT_MASK)
#define SCB_CPUID_IMPLEMENTER_MASK               0xFF000000u
#define SCB_CPUID_IMPLEMENTER_SHIFT              24
#define SCB_CPUID_IMPLEMENTER(x)                 (((uint32_t)(((uint32_t)(x))<<SCB_CPUID_IMPLEMENTER_SHIFT))&SCB_CPUID_IMPLEMENTER_MASK)
 /** ICSR Bit Fields */
#define SCB_ICSR_VECTACTIVE_MASK                 0x1FFu
#define SCB_ICSR_VECTACTIVE_SHIFT                0
#define SCB_ICSR_VECTACTIVE(x)                   (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTACTIVE_SHIFT))&SCB_ICSR_VECTACTIVE_MASK)
#define SCB_ICSR_RETTOBASE_MASK                  0x800u
#define SCB_ICSR_RETTOBASE_SHIFT                 11
#define SCB_ICSR_VECTPENDING_MASK                0x3F000u
#define SCB_ICSR_VECTPENDING_SHIFT               12
#define SCB_ICSR_VECTPENDING(x)                  (((uint32_t)(((uint32_t)(x))<<SCB_ICSR_VECTPENDING_SHIFT))&SCB_ICSR_VECTPENDING_MASK)
#define SCB_ICSR_ISRPENDING_MASK                 0x400000u
#define SCB_ICSR_ISRPENDING_SHIFT                22
#define SCB_ICSR_ISRPREEMPT_MASK                 0x800000u
#define SCB_ICSR_ISRPREEMPT_SHIFT                23
#define SCB_ICSR_PENDSTCLR_MASK                  0x2000000u
#define SCB_ICSR_PENDSTCLR_SHIFT                 25
#define SCB_ICSR_PENDSTSET_MASK                  0x4000000u
#define SCB_ICSR_PENDSTSET_SHIFT                 26
#define SCB_ICSR_PENDSVCLR_MASK                  0x8000000u
#define SCB_ICSR_PENDSVCLR_SHIFT                 27
#define SCB_ICSR_PENDSVSET_MASK                  0x10000000u
#define SCB_ICSR_PENDSVSET_SHIFT                 28
#define SCB_ICSR_NMIPENDSET_MASK                 0x80000000u
#define SCB_ICSR_NMIPENDSET_SHIFT                31
 /** VTOR Bit Fields */
#define SCB_VTOR_TBLOFF_MASK                     0xFFFFFF80u
#define SCB_VTOR_TBLOFF_SHIFT                    7
#define SCB_VTOR_TBLOFF(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_VTOR_TBLOFF_SHIFT))&SCB_VTOR_TBLOFF_MASK)
 /** AIRCR Bit Fields */
#define SCB_AIRCR_VECTRESET_MASK                 0x1u
#define SCB_AIRCR_VECTRESET_SHIFT                0
#define SCB_AIRCR_VECTCLRACTIVE_MASK             0x2u
#define SCB_AIRCR_VECTCLRACTIVE_SHIFT            1
#define SCB_AIRCR_SYSRESETREQ_MASK               0x4u
#define SCB_AIRCR_SYSRESETREQ_SHIFT              2
#define SCB_AIRCR_PRIGROUP_MASK                  0x700u
#define SCB_AIRCR_PRIGROUP_SHIFT                 8
#define SCB_AIRCR_PRIGROUP(x)                    (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_PRIGROUP_SHIFT))&SCB_AIRCR_PRIGROUP_MASK)
#define SCB_AIRCR_ENDIANNESS_MASK                0x8000u
#define SCB_AIRCR_ENDIANNESS_SHIFT               15
#define SCB_AIRCR_VECTKEY_MASK                   0xFFFF0000u
#define SCB_AIRCR_VECTKEY_SHIFT                  16
#define SCB_AIRCR_VECTKEY(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AIRCR_VECTKEY_SHIFT))&SCB_AIRCR_VECTKEY_MASK)
 /** SCR Bit Fields */
#define SCB_SCR_SLEEPONEXIT_MASK                 0x2u
#define SCB_SCR_SLEEPONEXIT_SHIFT                1
#define SCB_SCR_SLEEPDEEP_MASK                   0x4u
#define SCB_SCR_SLEEPDEEP_SHIFT                  2
#define SCB_SCR_SEVONPEND_MASK                   0x10u
#define SCB_SCR_SEVONPEND_SHIFT                  4
 /** CCR Bit Fields */
#define SCB_CCR_NONBASETHRDENA_MASK              0x1u
#define SCB_CCR_NONBASETHRDENA_SHIFT             0
#define SCB_CCR_USERSETMPEND_MASK                0x2u
#define SCB_CCR_USERSETMPEND_SHIFT               1
#define SCB_CCR_UNALIGN_TRP_MASK                 0x8u
#define SCB_CCR_UNALIGN_TRP_SHIFT                3
#define SCB_CCR_DIV_0_TRP_MASK                   0x10u
#define SCB_CCR_DIV_0_TRP_SHIFT                  4
#define SCB_CCR_BFHFNMIGN_MASK                   0x100u
#define SCB_CCR_BFHFNMIGN_SHIFT                  8
#define SCB_CCR_STKALIGN_MASK                    0x200u
#define SCB_CCR_STKALIGN_SHIFT                   9
 /** SHPR1 Bit Fields */
#define SCB_SHPR1_PRI_4_MASK                     0xFFu
#define SCB_SHPR1_PRI_4_SHIFT                    0
#define SCB_SHPR1_PRI_4(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_SHPR1_PRI_4_SHIFT))&SCB_SHPR1_PRI_4_MASK)
#define SCB_SHPR1_PRI_5_MASK                     0xFF00u
#define SCB_SHPR1_PRI_5_SHIFT                    8
#define SCB_SHPR1_PRI_5(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_SHPR1_PRI_5_SHIFT))&SCB_SHPR1_PRI_5_MASK)
#define SCB_SHPR1_PRI_6_MASK                     0xFF0000u
#define SCB_SHPR1_PRI_6_SHIFT                    16
#define SCB_SHPR1_PRI_6(x)                       (((uint32_t)(((uint32_t)(x))<<SCB_SHPR1_PRI_6_SHIFT))&SCB_SHPR1_PRI_6_MASK)
 /** SHPR2 Bit Fields */
#define SCB_SHPR2_PRI_11_MASK                    0xFF000000u
#define SCB_SHPR2_PRI_11_SHIFT                   24
#define SCB_SHPR2_PRI_11(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR2_PRI_11_SHIFT))&SCB_SHPR2_PRI_11_MASK)
 /** SHPR3 Bit Fields */
#define SCB_SHPR3_PRI_14_MASK                    0xFF0000u
#define SCB_SHPR3_PRI_14_SHIFT                   16
#define SCB_SHPR3_PRI_14(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_14_SHIFT))&SCB_SHPR3_PRI_14_MASK)
#define SCB_SHPR3_PRI_15_MASK                    0xFF000000u
#define SCB_SHPR3_PRI_15_SHIFT                   24
#define SCB_SHPR3_PRI_15(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_SHPR3_PRI_15_SHIFT))&SCB_SHPR3_PRI_15_MASK)
 /** SHCSR Bit Fields */
#define SCB_SHCSR_MEMFAULTACT_MASK               0x1u
#define SCB_SHCSR_MEMFAULTACT_SHIFT              0
#define SCB_SHCSR_BUSFAULTACT_MASK               0x2u
#define SCB_SHCSR_BUSFAULTACT_SHIFT              1
#define SCB_SHCSR_USGFAULTACT_MASK               0x8u
#define SCB_SHCSR_USGFAULTACT_SHIFT              3
#define SCB_SHCSR_SVCALLACT_MASK                 0x80u
#define SCB_SHCSR_SVCALLACT_SHIFT                7
#define SCB_SHCSR_MONITORACT_MASK                0x100u
#define SCB_SHCSR_MONITORACT_SHIFT               8
#define SCB_SHCSR_PENDSVACT_MASK                 0x400u
#define SCB_SHCSR_PENDSVACT_SHIFT                10
#define SCB_SHCSR_SYSTICKACT_MASK                0x800u
#define SCB_SHCSR_SYSTICKACT_SHIFT               11
#define SCB_SHCSR_USGFAULTPENDED_MASK            0x1000u
#define SCB_SHCSR_USGFAULTPENDED_SHIFT           12
#define SCB_SHCSR_MEMFAULTPENDED_MASK            0x2000u
#define SCB_SHCSR_MEMFAULTPENDED_SHIFT           13
#define SCB_SHCSR_BUSFAULTPENDED_MASK            0x4000u
#define SCB_SHCSR_BUSFAULTPENDED_SHIFT           14
#define SCB_SHCSR_SVCALLPENDED_MASK              0x8000u
#define SCB_SHCSR_SVCALLPENDED_SHIFT             15
#define SCB_SHCSR_MEMFAULTENA_MASK               0x10000u
#define SCB_SHCSR_MEMFAULTENA_SHIFT              16
#define SCB_SHCSR_BUSFAULTENA_MASK               0x20000u
#define SCB_SHCSR_BUSFAULTENA_SHIFT              17
#define SCB_SHCSR_USGFAULTENA_MASK               0x40000u
#define SCB_SHCSR_USGFAULTENA_SHIFT              18
 /** CFSR Bit Fields */
#define SCB_CFSR_IACCVIOL_MASK                   0x1u
#define SCB_CFSR_IACCVIOL_SHIFT                  0
#define SCB_CFSR_DACCVIOL_MASK                   0x2u
#define SCB_CFSR_DACCVIOL_SHIFT                  1
#define SCB_CFSR_MUNSTKERR_MASK                  0x8u
#define SCB_CFSR_MUNSTKERR_SHIFT                 3
#define SCB_CFSR_MSTKERR_MASK                    0x10u
#define SCB_CFSR_MSTKERR_SHIFT                   4
#define SCB_CFSR_MLSPERR_MASK                    0x20u
#define SCB_CFSR_MLSPERR_SHIFT                   5
#define SCB_CFSR_MMARVALID_MASK                  0x80u
#define SCB_CFSR_MMARVALID_SHIFT                 7
#define SCB_CFSR_IBUSERR_MASK                    0x100u
#define SCB_CFSR_IBUSERR_SHIFT                   8
#define SCB_CFSR_PRECISERR_MASK                  0x200u
#define SCB_CFSR_PRECISERR_SHIFT                 9
#define SCB_CFSR_IMPRECISERR_MASK                0x400u
#define SCB_CFSR_IMPRECISERR_SHIFT               10
#define SCB_CFSR_UNSTKERR_MASK                   0x800u
#define SCB_CFSR_UNSTKERR_SHIFT                  11
#define SCB_CFSR_STKERR_MASK                     0x1000u
#define SCB_CFSR_STKERR_SHIFT                    12
#define SCB_CFSR_LSPERR_MASK                     0x2000u
#define SCB_CFSR_LSPERR_SHIFT                    13
#define SCB_CFSR_BFARVALID_MASK                  0x8000u
#define SCB_CFSR_BFARVALID_SHIFT                 15
#define SCB_CFSR_UNDEFINSTR_MASK                 0x10000u
#define SCB_CFSR_UNDEFINSTR_SHIFT                16
#define SCB_CFSR_INVSTATE_MASK                   0x20000u
#define SCB_CFSR_INVSTATE_SHIFT                  17
#define SCB_CFSR_INVPC_MASK                      0x40000u
#define SCB_CFSR_INVPC_SHIFT                     18
#define SCB_CFSR_NOCP_MASK                       0x80000u
#define SCB_CFSR_NOCP_SHIFT                      19
#define SCB_CFSR_UNALIGNED_MASK                  0x1000000u
#define SCB_CFSR_UNALIGNED_SHIFT                 24
#define SCB_CFSR_DIVBYZERO_MASK                  0x2000000u
#define SCB_CFSR_DIVBYZERO_SHIFT                 25
 /** HFSR Bit Fields */
#define SCB_HFSR_VECTTBL_MASK                    0x2u
#define SCB_HFSR_VECTTBL_SHIFT                   1
#define SCB_HFSR_FORCED_MASK                     0x40000000u
#define SCB_HFSR_FORCED_SHIFT                    30
#define SCB_HFSR_DEBUGEVT_MASK                   0x80000000u
#define SCB_HFSR_DEBUGEVT_SHIFT                  31
 /** DFSR Bit Fields */
#define SCB_DFSR_HALTED_MASK                     0x1u
#define SCB_DFSR_HALTED_SHIFT                    0
#define SCB_DFSR_BKPT_MASK                       0x2u
#define SCB_DFSR_BKPT_SHIFT                      1
#define SCB_DFSR_DWTTRAP_MASK                    0x4u
#define SCB_DFSR_DWTTRAP_SHIFT                   2
#define SCB_DFSR_VCATCH_MASK                     0x8u
#define SCB_DFSR_VCATCH_SHIFT                    3
#define SCB_DFSR_EXTERNAL_MASK                   0x10u
#define SCB_DFSR_EXTERNAL_SHIFT                  4
 /** MMFAR Bit Fields */
#define SCB_MMFAR_ADDRESS_MASK                   0xFFFFFFFFu
#define SCB_MMFAR_ADDRESS_SHIFT                  0
#define SCB_MMFAR_ADDRESS(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_MMFAR_ADDRESS_SHIFT))&SCB_MMFAR_ADDRESS_MASK)
 /** BFAR Bit Fields */
#define SCB_BFAR_ADDRESS_MASK                    0xFFFFFFFFu
#define SCB_BFAR_ADDRESS_SHIFT                   0
#define SCB_BFAR_ADDRESS(x)                      (((uint32_t)(((uint32_t)(x))<<SCB_BFAR_ADDRESS_SHIFT))&SCB_BFAR_ADDRESS_MASK)
 /** AFSR Bit Fields */
#define SCB_AFSR_AUXFAULT_MASK                   0xFFFFFFFFu
#define SCB_AFSR_AUXFAULT_SHIFT                  0
#define SCB_AFSR_AUXFAULT(x)                     (((uint32_t)(((uint32_t)(x))<<SCB_AFSR_AUXFAULT_SHIFT))&SCB_AFSR_AUXFAULT_MASK)

/*!
 * @}
 */  /** end of group SCB_Register_Masks */


 /** SCB - Peripheral instance base addresses */
/** Peripheral SystemControl base pointer */
#define SystemControl_BASE_PTR                   ((SCB_MemMapPtr)0xE000E000u)
/** Array initializer of SCB peripheral base pointers */
#define SCB_BASE_PTRS                            { SystemControl_BASE_PTR }

/* ----------------------------------------------------------------------------
   -- SCB - Register accessor macros
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCB_Register_Accessor_Macros SCB - Register accessor macros
 * @{
 */


 /** SCB - Register instance definitions */
 /** SystemControl */
#define SCB_ACTLR                                SCB_ACTLR_REG(SystemControl_BASE_PTR)
#define SCB_CPUID                                SCB_CPUID_REG(SystemControl_BASE_PTR)
#define SCB_ICSR                                 SCB_ICSR_REG(SystemControl_BASE_PTR)
#define SCB_VTOR                                 SCB_VTOR_REG(SystemControl_BASE_PTR)
#define SCB_AIRCR                                SCB_AIRCR_REG(SystemControl_BASE_PTR)
#define SCB_SCR                                  SCB_SCR_REG(SystemControl_BASE_PTR)
#define SCB_CCR                                  SCB_CCR_REG(SystemControl_BASE_PTR)
#define SCB_SHPR1                                SCB_SHPR1_REG(SystemControl_BASE_PTR)
#define SCB_SHPR2                                SCB_SHPR2_REG(SystemControl_BASE_PTR)
#define SCB_SHPR3                                SCB_SHPR3_REG(SystemControl_BASE_PTR)
#define SCB_SHCSR                                SCB_SHCSR_REG(SystemControl_BASE_PTR)
#define SCB_CFSR                                 SCB_CFSR_REG(SystemControl_BASE_PTR)
#define SCB_HFSR                                 SCB_HFSR_REG(SystemControl_BASE_PTR)
#define SCB_DFSR                                 SCB_DFSR_REG(SystemControl_BASE_PTR)
#define SCB_MMFAR                                SCB_MMFAR_REG(SystemControl_BASE_PTR)
#define SCB_BFAR                                 SCB_BFAR_REG(SystemControl_BASE_PTR)
#define SCB_AFSR                                 SCB_AFSR_REG(SystemControl_BASE_PTR)

/*!
 * @}
 */  /** end of group SCB_Register_Accessor_Macros */


/*!
 * @}
 */  /** end of group SCB_Peripheral */

#endif
