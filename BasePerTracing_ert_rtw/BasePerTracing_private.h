/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BasePerTracing_private.h
 *
 * Code generated for Simulink model 'BasePerTracing'.
 *
 * Model version                  : 6.0
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu May 21 11:45:18 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef BasePerTracing_private_h_
#define BasePerTracing_private_h_
#include "rtwtypes.h"
#include "BasePerTracing.h"
#include "BasePerTracing_types.h"

void config_QEP_eQEP1(uint32_T pcmaximumvalue, uint32_T pcInitialvalue, uint32_T
                      unittimerperiod, uint32_T comparevalue, uint16_T
                      watchdogtimer, uint16_T qdecctl, uint16_T qepctl, uint16_T
                      qposctl, uint16_T qcapctl, uint16_T qeint);

#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFFFU) ) || ( SCHAR_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */
void InitAdcC (void);
void config_ADCC_SOC0 (void);
void InitAdcA (void);
void config_ADCA_SOC1 (void);
void InitAdcB (void);
void config_ADCB_SOC0 (void);
void config_ADCA_SOC0 (void);
void config_ADCA_SOC2 (void);
void config_ADCC_SOC3 (void);
extern uint16_T MW_adcCInitFlag;
extern uint16_T MW_adcAInitFlag;
extern uint16_T MW_adcBInitFlag;
void isr_int1pie1_task_fcn(void);
void isr_int9pie1_task_fcn(void);
extern void configureGPIOExtInterrupt(void);
extern real_T look1_binlc(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
extern void BasePe_MATLABFunction1_Init(DW_MATLABFunction1_BasePerTra_T *localDW);
extern void BaseP_MATLABFunction1_Reset(DW_MATLABFunction1_BasePerTra_T *localDW);
extern void BasePerTrac_MATLABFunction1(real_T rtu_in, real_T rtu_Kp, real_T
  rtu_Ti, real_T rtu_Ts, real32_T rtu_Enable, real_T rtu_EnableCheckSat, real_T
  rtu_HiSat, real_T rtu_LowSat, B_MATLABFunction1_BasePerTrac_T *localB,
  DW_MATLABFunction1_BasePerTra_T *localDW);
extern void BasePer_CurrentControl_Init(void);
extern void BasePe_CurrentControl_Reset(void);

#pragma CODE_SECTION (BaseP_CurrentControl_Enable, "ramfuncs")

extern void BaseP_CurrentControl_Enable(void);

#pragma CODE_SECTION (BasePe_CurrentControl_Const, "ramfuncs")

extern void BasePe_CurrentControl_Const(void);

#pragma CODE_SECTION (BasePerTraci_CurrentControl, "ramfuncs")

extern void BasePerTraci_CurrentControl(void);
void isr_int1pie1_task_fcn(void);

#endif                                 /* BasePerTracing_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
