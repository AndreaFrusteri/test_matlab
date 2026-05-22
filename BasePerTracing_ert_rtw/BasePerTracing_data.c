/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BasePerTracing_data.c
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

#include "BasePerTracing.h"

/* Invariant block signals (default storage) */
const ConstB_BasePerTracing_T BasePerTracing_ConstB = {
  2U,                                  /* '<S20>/Width' */
  12.0F,                               /* '<S9>/Cast To Single7' */
  13.0F,                               /* '<S9>/Cast To Single8' */
  14.0F                                /* '<S9>/Cast To Single9' */
};

/* Constant parameters (default storage) */
const ConstP_BasePerTracing_T BasePerTracing_ConstP = {
  /* Expression: OutValues
   * Referenced by: '<S5>/Lookup'
   */
  { 0.0, 700.0, 700.0, 0.0, 0.0, 710.0, 710.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: TimeValues)
   * Referenced by:
   *   '<S5>/Lookup'
   *   '<S6>/Lookup'
   */
  { 0.0, 0.055, 0.1, 0.15, 0.25, 0.305, 0.35, 0.4, 0.45 },

  /* Expression: OutValues
   * Referenced by: '<S6>/Lookup'
   */
  { 0.0, 700.0, 700.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
