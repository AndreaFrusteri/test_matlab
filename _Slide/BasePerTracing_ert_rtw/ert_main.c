/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'BasePerTracing'.
 *
 * Model version                  : 6.0
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Thu May 21 10:20:22 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BasePerTracing.h"
#include "rtwtypes.h"
#include "MW_target_hardware_resources.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  enableTimer0Interrupt();
  BasePerTracing_step();

  /* Get model outputs here */
  disableTimer0Interrupt();
  OverrunFlag--;
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(void)
{
  float modelBaseRate = 0.5;
  float systemClock = 200;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;
  c2000_flash_init();
  init_board();

#if defined(MW_EXEC_PROFILER_ON) || (defined(MW_EXTMODE_RUNNING) && !defined(XCP_TIMESTAMP_BASED_ON_SIMULATION_TIME))

  hardwareTimer1Init();

#endif

  ;
  rtmSetErrorStatus(BasePerTracing_M, 0);
  BasePerTracing_initialize();
  globalInterruptDisable();
  configureTimer0(modelBaseRate, systemClock);
  runModel =
    rtmGetErrorStatus(BasePerTracing_M) == (NULL);
  enableTimer0Interrupt();
  enable_interrupts();
  config_ePWM_TBSync();
  globalInterruptEnable();
  while (runModel) {
    stopRequested = !(
                      rtmGetErrorStatus(BasePerTracing_M) == (NULL));
  }

  /* Terminate model */
  BasePerTracing_terminate();
  globalInterruptDisable();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
