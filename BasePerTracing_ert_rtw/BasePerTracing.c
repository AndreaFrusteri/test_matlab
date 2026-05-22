/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BasePerTracing.c
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
#include "rtwtypes.h"
#include "BasePerTracing_private.h"
#include <string.h>

/* Block signals (default storage) */
B_BasePerTracing_T BasePerTracing_B;

/* Block states (default storage) */
DW_BasePerTracing_T BasePerTracing_DW;

/* Real-time model */
static RT_MODEL_BasePerTracing_T BasePerTracing_M_;
RT_MODEL_BasePerTracing_T *const BasePerTracing_M = &BasePerTracing_M_;
static void rate_monotonic_scheduler(void);

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcCInitFlag = 0;

#endif

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcAInitFlag = 0;

#endif

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcBInitFlag = 0;

#endif

real_T look1_binlc(real_T u0, const real_T bp0[], const real_T table[], uint32_T
                   maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex;
    while (iRght - iLeft > 1UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1UL;
    frac = 1.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1UL] - yL_0d0) * frac + yL_0d0;
}

/* Hardware Interrupt Block: '<S1>/C28x Hardware Interrupt' */
void isr_int1pie1_task_fcn(void)
{
  if (1 == runModel) {
    /* Call the system: <Root>/Current Control */
    {
      /* RateTransition: '<Root>/Rate Transition1' */
      BasePerTracing_B.RateTransition1 =
        BasePerTracing_DW.RateTransition1_Buffer[BasePerTracing_DW.RateTransition1_ActiveBufIdx];

      /* RateTransition: '<Root>/Rate Transition2' */
      BasePerTracing_B.RateTransition2 =
        BasePerTracing_DW.RateTransition2_Buffer[BasePerTracing_DW.RateTransition2_ActiveBufIdx];

      /* S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */
      BasePerTraci_CurrentControl();

      /* End of Outputs for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */
    }
  }
}

/* Hardware Interrupt Block: '<S1>/C28x Hardware Interrupt' */
void isr_int9pie1_task_fcn(void)
{
  if (1 == runModel) {
    /* Call the system: <Root>/Serial Receive */
    {
      /* S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */

      /* Output and update for function-call system: '<Root>/Serial Receive' */

      /* S-Function (c28xsci_rx): '<S41>/SCI Receive' */
      {
        int16_T i;
        int16_T errFlg = NOERROR;
        uint16_T isHeadReceived = 1U;

        //get data as uint16 in recBuff
        uint16_T recbuff[4];
        for (i = 0; i < 4; i++) {
          recbuff[i] = 0U;
        }

        errFlg = NOERROR;

        /* Receiving data: For uint32 and uint16, rcvBuff will contain uint16 data */
        if (isHeadReceived) {
          errFlg = scia_rcv(recbuff, 8, 4);
          asm(" NOP");
          if ((errFlg == NOERROR) || (errFlg == PARTIALDATA)) {
            memcpy( &BasePerTracing_B.SCIReceive[0], recbuff,4);
          }
        }
      }

      /* DataTypeConversion: '<S42>/Data Type Conversion2' */
      BasePerTracing_B.DataTypeConversion2 = (uint16_T)
        BasePerTracing_B.SCIReceive[1];

      /* S-Function (sfix_bitop): '<S40>/Bitwise Operator' */
      BasePerTracing_B.BitwiseOperator = BasePerTracing_B.DataTypeConversion2 &
        1U;

      /* DataTypeConversion: '<S40>/Data Type Conversion3' */
      BasePerTracing_B.DataTypeConversion3_f = (BasePerTracing_B.BitwiseOperator
        != 0U);

      /* DataStoreWrite: '<S7>/Data Store Write' */
      BasePerTracing_DW.Enable = BasePerTracing_B.DataTypeConversion3_f;

      /* DataTypeConversion: '<S7>/Cast To Single' */
      BasePerTracing_B.CastToSingle = BasePerTracing_B.SCIReceive[0];

      /* DataStoreWrite: '<S7>/Data Store Write1' */
      BasePerTracing_DW.SpeedRef = BasePerTracing_B.CastToSingle;

      /* S-Function (sfix_bitop): '<S40>/Bitwise Operator1' */
      BasePerTracing_B.BitwiseOperator1 = BasePerTracing_B.DataTypeConversion2 &
        240U;

      /* ArithShift: '<S40>/Shift Arithmetic1' incorporates:
       *  S-Function (sfix_bitop): '<S40>/Bitwise Operator1'
       */
      BasePerTracing_B.ShiftArithmetic1 = BasePerTracing_B.BitwiseOperator1 >>
        4U;

      /* DataStoreWrite: '<S7>/Data Store Write2' */
      BasePerTracing_DW.Debug_signals = BasePerTracing_B.ShiftArithmetic1;

      /* End of Outputs for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */
    }
  }
}

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void BasePerTracing_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(BasePerTracing_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (BasePerTracing_M->Timing.TaskCounters.TID[1])++;
  if ((BasePerTracing_M->Timing.TaskCounters.TID[1]) > 4999) {/* Sample time: [0.5s, 0.0s] */
    BasePerTracing_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/*
 * System initialize for atomic system:
 *    '<S2>/MATLAB Function1'
 *    '<S2>/MATLAB Function2'
 */
void BasePe_MATLABFunction1_Init(DW_MATLABFunction1_BasePerTra_T *localDW)
{
  localDW->out_prev = 0.0;
  localDW->in_prev = 0.0;
}

/*
 * System reset for atomic system:
 *    '<S2>/MATLAB Function1'
 *    '<S2>/MATLAB Function2'
 */
void BaseP_MATLABFunction1_Reset(DW_MATLABFunction1_BasePerTra_T *localDW)
{
  localDW->out_prev = 0.0;
  localDW->in_prev = 0.0;
}

/*
 * Output and update for atomic system:
 *    '<S2>/MATLAB Function1'
 *    '<S2>/MATLAB Function2'
 */
void BasePerTrac_MATLABFunction1(real_T rtu_in, real_T rtu_Kp, real_T rtu_Ti,
  real_T rtu_Ts, real32_T rtu_Enable, real_T rtu_EnableCheckSat, real_T
  rtu_HiSat, real_T rtu_LowSat, B_MATLABFunction1_BasePerTrac_T *localB,
  DW_MATLABFunction1_BasePerTra_T *localDW)
{
  real_T in;
  in = rtu_in;

  /* MATLAB Function 'Current Control/MATLAB Function1': '<S12>:1' */
  if (rtu_Enable == 1.0F) {
    /* '<S12>:1:13' */
    /* '<S12>:1:15' */
    localB->out = (rtu_Kp * rtu_Ts / (2.0 * rtu_Ti) * (rtu_in + localDW->in_prev)
                   + (rtu_in - localDW->in_prev) * rtu_Kp) + localDW->out_prev;
  } else {
    /* '<S12>:1:17' */
    localB->out = 0.0;

    /* '<S12>:1:18' */
    in = 0.0;
  }

  if (rtu_EnableCheckSat == 1.0) {
    /* '<S12>:1:21' */
    if (localB->out > rtu_HiSat) {
      /* '<S12>:1:23' */
      /* '<S12>:1:24' */
      localB->out = rtu_HiSat;
    } else if (localB->out < rtu_LowSat) {
      /* '<S12>:1:25' */
      /* '<S12>:1:26' */
      localB->out = rtu_LowSat;
    }
  }

  /* '<S12>:1:30' */
  localDW->out_prev = localB->out;

  /* '<S12>:1:31' */
  localDW->in_prev = in;
}

/* System initialize for function-call system: '<Root>/Current Control' */
void BasePer_CurrentControl_Init(void)
{
  /* Asynchronous task reads absolute time. Data (absolute time)
     transfers from low priority task (base rate) to high priority
     task (asynchronous rate). Double buffers are used to ensure
     data integrity.
     -- rtmL2HLastBufWr is the buffer index that is written last.
   */
  BasePerTracing_M->Timing.clockTick2 =
    BasePerTracing_M->Timing.rtmL2HDbBufClockTick
    [BasePerTracing_M->Timing.rtmL2HLastBufWr];

  /* Start for S-Function (c2802xpwm): '<S14>/PWM MOT C' incorporates:
   *  Constant: '<S14>/Constant6'
   */
  real32_T tbprdValue6 = (real32_T)EPwm6Regs.TBPRD;

  /*** Initialize ePWM6 modules ***/
  {
    /*  -- Time Base Control Register
       EPwm6Regs.TBCTL.bit.CTRMODE              = 2U;          -- Counter Mode
       EPwm6Regs.TBCTL.bit.SYNCOSEL             = 0U;          -- Sync Output Select

       EPwm6Regs.TBCTL.bit.PRDLD                = 0U;          -- Shadow select

       EPwm6Regs.TBCTL2.bit.PRDLDSYNC           = 0U;          -- Shadow select

       EPwm6Regs.TBCTL.bit.PHSEN                = 1U;          -- Phase Load Enable
       EPwm6Regs.TBCTL.bit.PHSDIR               = 1U;          -- Phase Direction Bit
       EPwm6Regs.TBCTL.bit.HSPCLKDIV            = 0U;          -- High Speed TBCLK Pre-scaler
       EPwm6Regs.TBCTL.bit.CLKDIV               = 0U;          -- Time Base Clock Pre-scaler
     */
    EPwm6Regs.TBCTL.all = (EPwm6Regs.TBCTL.all & ~0x3FFFU) | 0x2006U;
    EPwm6Regs.TBCTL2.all = (EPwm6Regs.TBCTL2.all & ~0xC000U) | 0x0U;

    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm6Regs.TBPRD = 10000U;          // Time Base Period Register

    /* -- Time-Base Phase Register
       EPwm6Regs.TBPHS.bit.TBPHS               = 0U;          -- Phase offset register
     */
    EPwm6Regs.TBPHS.all = (EPwm6Regs.TBPHS.all & ~0xFFFF0000U) | 0x0U;

    // Time Base Counter Register
    EPwm6Regs.TBCTR = 0x0000U;         /* Clear counter*/

    /*-- Setup Counter_Compare (CC) Submodule --*/
    /*	-- Counter Compare Control Register

       EPwm6Regs.CMPCTL.bit.LOADASYNC           = 0U;          -- Active Compare A Load SYNC Option
       EPwm6Regs.CMPCTL.bit.LOADBSYNC           = 0U;          -- Active Compare B Load SYNC Option
       EPwm6Regs.CMPCTL.bit.LOADAMODE           = 0U;          -- Active Compare A Load
       EPwm6Regs.CMPCTL.bit.LOADBMODE           = 0U;          -- Active Compare B Load
       EPwm6Regs.CMPCTL.bit.SHDWAMODE           = 0U;          -- Compare A Register Block Operating Mode
       EPwm6Regs.CMPCTL.bit.SHDWBMODE           = 0U;          -- Compare B Register Block Operating Mode
     */
    EPwm6Regs.CMPCTL.all = (EPwm6Regs.CMPCTL.all & ~0x3C5FU) | 0x0U;

    /* EPwm6Regs.CMPCTL2.bit.SHDWCMODE           = 0U;          -- Compare C Register Block Operating Mode
       EPwm6Regs.CMPCTL2.bit.SHDWDMODE           = 0U;          -- Compare D Register Block Operating Mode
       EPwm6Regs.CMPCTL2.bit.LOADCSYNC           = 0U;          -- Active Compare C Load SYNC Option
       EPwm6Regs.CMPCTL2.bit.LOADDSYNC           = 0U;          -- Active Compare D Load SYNC Option
       EPwm6Regs.CMPCTL2.bit.LOADCMODE           = 0U;          -- Active Compare C Load
       EPwm6Regs.CMPCTL2.bit.LOADDMODE           = 0U;          -- Active Compare D Load
     */
    EPwm6Regs.CMPCTL2.all = (EPwm6Regs.CMPCTL2.all & ~0x3C5FU) | 0x0U;
    EPwm6Regs.CMPA.bit.CMPA = 0U;      // Counter Compare A Register
    EPwm6Regs.CMPB.bit.CMPB = 2000U;   // Counter Compare B Register
    EPwm6Regs.CMPC = 32000U;           // Counter Compare C Register
    EPwm6Regs.CMPD = 32000U;           // Counter Compare D Register

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm6Regs.AQCTLA.all = 146U;
                               // Action Qualifier Control Register For Output A
    EPwm6Regs.AQCTLB.all = 2310U;
                               // Action Qualifier Control Register For Output B

    /*	-- Action Qualifier Software Force Register
       EPwm6Regs.AQSFRC.bit.RLDCSF              = 0U;          -- Reload from Shadow Options
     */
    EPwm6Regs.AQSFRC.all = (EPwm6Regs.AQSFRC.all & ~0xC0U) | 0x0U;

    /*	-- Action Qualifier Continuous S/W Force Register
       EPwm6Regs.AQCSFRC.bit.CSFA               = 0U;          -- Continuous Software Force on output A
       EPwm6Regs.AQCSFRC.bit.CSFB               = 0U;          -- Continuous Software Force on output B
     */
    EPwm6Regs.AQCSFRC.all = (EPwm6Regs.AQCSFRC.all & ~0xFU) | 0x0U;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    /*	-- Dead-Band Generator Control Register
       EPwm6Regs.DBCTL.bit.OUT_MODE             = 3U;          -- Dead Band Output Mode Control
       EPwm6Regs.DBCTL.bit.IN_MODE              = 0U;          -- Dead Band Input Select Mode Control
       EPwm6Regs.DBCTL.bit.POLSEL               = 2U;          -- Polarity Select Control
       EPwm6Regs.DBCTL.bit.HALFCYCLE            = 0U;          -- Half Cycle Clocking Enable
       EPwm6Regs.DBCTL.bit.SHDWDBREDMODE        = 0U;          -- DBRED shadow mode
       EPwm6Regs.DBCTL.bit.SHDWDBFEDMODE        = 0U;          -- DBFED shadow mode
       EPwm6Regs.DBCTL.bit.LOADREDMODE          = 4U;        -- DBRED load
       EPwm6Regs.DBCTL.bit.LOADFEDMODE          = 4U;        -- DBFED load
     */
    EPwm6Regs.DBCTL.all = (EPwm6Regs.DBCTL.all & ~0x8FFFU) | 0xBU;
    EPwm6Regs.DBRED.bit.DBRED = (uint16_T)(15.0);
                         // Dead-Band Generator Rising Edge Delay Count Register
    EPwm6Regs.DBFED.bit.DBFED = (uint16_T)(15.0);
                        // Dead-Band Generator Falling Edge Delay Count Register

    /*-- Setup Event-Trigger (ET) Submodule --*/
    /*	-- Event Trigger Selection and Pre-Scale Register
       EPwm6Regs.ETSEL.bit.SOCAEN               = 1U;          -- Start of Conversion A Enable
       EPwm6Regs.ETSEL.bit.SOCASELCMP           = 0U;
       EPwm6Regs.ETSEL.bit.SOCASEL              = 1U;          -- Start of Conversion A Select
       EPwm6Regs.ETPS.bit.SOCPSSEL              = 1U;          -- EPWM6SOC Period Select
       EPwm6Regs.ETSOCPS.bit.SOCAPRD2           = 1U;
       EPwm6Regs.ETSEL.bit.SOCBEN               = 0U;          -- Start of Conversion B Enable
       EPwm6Regs.ETSEL.bit.SOCBSELCMP           = 0U;
       EPwm6Regs.ETSEL.bit.SOCBSEL              = 1U;          -- Start of Conversion A Select
       EPwm6Regs.ETPS.bit.SOCPSSEL              = 1;          -- EPWM6SOCB Period Select
       EPwm6Regs.ETSOCPS.bit.SOCBPRD2           = 1U;
       EPwm6Regs.ETSEL.bit.INTEN                = 0U;          -- EPWM6INTn Enable
       EPwm6Regs.ETSEL.bit.INTSELCMP            = 0U;
       EPwm6Regs.ETSEL.bit.INTSEL               = 1U;          -- Start of Conversion A Select
       EPwm6Regs.ETPS.bit.INTPSSEL              = 1U;          // EPWM6INTn Period Select
       EPwm6Regs.ETINTPS.bit.INTPRD2            = 1U;
     */
    EPwm6Regs.ETSEL.all = (EPwm6Regs.ETSEL.all & ~0xFF7FU) | 0x1901U;
    EPwm6Regs.ETPS.all = (EPwm6Regs.ETPS.all & ~0x30U) | 0x30U;
    EPwm6Regs.ETSOCPS.all = (EPwm6Regs.ETSOCPS.all & ~0xF0FU) | 0x101U;
    EPwm6Regs.ETINTPS.all = (EPwm6Regs.ETINTPS.all & ~0xFU) | 0x1U;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    /*	-- PWM Chopper Control Register
       EPwm6Regs.PCCTL.bit.CHPEN                = 0U;          -- PWM chopping enable
       EPwm6Regs.PCCTL.bit.CHPFREQ              = 0U;          -- Chopping clock frequency
       EPwm6Regs.PCCTL.bit.OSHTWTH              = 0U;          -- One-shot pulse width
       EPwm6Regs.PCCTL.bit.CHPDUTY              = 0U;          -- Chopping clock Duty cycle
     */
    EPwm6Regs.PCCTL.all = (EPwm6Regs.PCCTL.all & ~0x7FFU) | 0x0U;

    /*-- Set up Trip-Zone (TZ) Submodule --*/
    EALLOW;
    EPwm6Regs.TZSEL.all = 0U;          // Trip Zone Select Register

    /*	-- Trip Zone Control Register
       EPwm6Regs.TZCTL.bit.TZA                  = 3U;          -- TZ1 to TZ6 Trip Action On EPWM6A
       EPwm6Regs.TZCTL.bit.TZB                  = 3U;          -- TZ1 to TZ6 Trip Action On EPWM6B
       EPwm6Regs.TZCTL.bit.DCAEVT1              = 3U;          -- EPWM6A action on DCAEVT1
       EPwm6Regs.TZCTL.bit.DCAEVT2              = 3U;          -- EPWM6A action on DCAEVT2
       EPwm6Regs.TZCTL.bit.DCBEVT1              = 3U;          -- EPWM6B action on DCBEVT1
       EPwm6Regs.TZCTL.bit.DCBEVT2              = 3U;          -- EPWM6B action on DCBEVT2
     */
    EPwm6Regs.TZCTL.all = (EPwm6Regs.TZCTL.all & ~0xFFFU) | 0xFFFU;

    /*	-- Trip Zone Enable Interrupt Register
       EPwm6Regs.TZEINT.bit.OST                 = 0U;          -- Trip Zones One Shot Int Enable
       EPwm6Regs.TZEINT.bit.CBC                 = 0U;          -- Trip Zones Cycle By Cycle Int Enable
       EPwm6Regs.TZEINT.bit.DCAEVT1             = 0U;          -- Digital Compare A Event 1 Int Enable
       EPwm6Regs.TZEINT.bit.DCAEVT2             = 0U;          -- Digital Compare A Event 2 Int Enable
       EPwm6Regs.TZEINT.bit.DCBEVT1             = 0U;          -- Digital Compare B Event 1 Int Enable
       EPwm6Regs.TZEINT.bit.DCBEVT2             = 0U;          -- Digital Compare B Event 2 Int Enable
     */
    EPwm6Regs.TZEINT.all = (EPwm6Regs.TZEINT.all & ~0x7EU) | 0x0U;

    /*	-- Digital Compare A Control Register
       EPwm6Regs.DCACTL.bit.EVT1SYNCE           = 0U;          -- DCAEVT1 SYNC Enable
       EPwm6Regs.DCACTL.bit.EVT1SOCE            = 1U;          -- DCAEVT1 SOC Enable
       EPwm6Regs.DCACTL.bit.EVT1FRCSYNCSEL      = 0U;          -- DCAEVT1 Force Sync Signal
       EPwm6Regs.DCACTL.bit.EVT1SRCSEL          = 0U;          -- DCAEVT1 Source Signal
       EPwm6Regs.DCACTL.bit.EVT2FRCSYNCSEL      = 0U;          -- DCAEVT2 Force Sync Signal
       EPwm6Regs.DCACTL.bit.EVT2SRCSEL          = 0U;          -- DCAEVT2 Source Signal
     */
    EPwm6Regs.DCACTL.all = (EPwm6Regs.DCACTL.all & ~0x30FU) | 0x4U;

    /*	-- Digital Compare B Control Register
       EPwm6Regs.DCBCTL.bit.EVT1SYNCE           = 0U;          -- DCBEVT1 SYNC Enable
       EPwm6Regs.DCBCTL.bit.EVT1SOCE            = 0U;          -- DCBEVT1 SOC Enable
       EPwm6Regs.DCBCTL.bit.EVT1FRCSYNCSEL      = 0U;          -- DCBEVT1 Force Sync Signal
       EPwm6Regs.DCBCTL.bit.EVT1SRCSEL          = 0U;          -- DCBEVT1 Source Signal
       EPwm6Regs.DCBCTL.bit.EVT2FRCSYNCSEL      = 0U;          -- DCBEVT2 Force Sync Signal
       EPwm6Regs.DCBCTL.bit.EVT2SRCSEL          = 0U;          -- DCBEVT2 Source Signal
     */
    EPwm6Regs.DCBCTL.all = (EPwm6Regs.DCBCTL.all & ~0x30FU) | 0x0U;

    /*	-- Digital Compare Trip Select Register
       EPwm6Regs.DCTRIPSEL.bit.DCAHCOMPSEL      = 0U;          -- Digital Compare A High COMP Input Select

       EPwm6Regs.DCTRIPSEL.bit.DCALCOMPSEL      = 1U;          -- Digital Compare A Low COMP Input Select
       EPwm6Regs.DCTRIPSEL.bit.DCBHCOMPSEL      = 0U;          -- Digital Compare B High COMP Input Select
       EPwm6Regs.DCTRIPSEL.bit.DCBLCOMPSEL      = 1U;          -- Digital Compare B Low COMP Input Select
     */
    EPwm6Regs.DCTRIPSEL.all = (EPwm6Regs.DCTRIPSEL.all & ~ 0xFFFFU) | 0x1010U;

    /*	-- Trip Zone Digital Comparator Select Register
       EPwm6Regs.TZDCSEL.bit.DCAEVT1            = 0U;          -- Digital Compare Output A Event 1
       EPwm6Regs.TZDCSEL.bit.DCAEVT2            = 0U;          -- Digital Compare Output A Event 2
       EPwm6Regs.TZDCSEL.bit.DCBEVT1            = 0U;          -- Digital Compare Output B Event 1
       EPwm6Regs.TZDCSEL.bit.DCBEVT2            = 0U;          -- Digital Compare Output B Event 2
     */
    EPwm6Regs.TZDCSEL.all = (EPwm6Regs.TZDCSEL.all & ~0xFFFU) | 0x0U;

    /*	-- Digital Compare Filter Control Register
       EPwm6Regs.DCFCTL.bit.BLANKE              = 0U;          -- Blanking Enable/Disable
       EPwm6Regs.DCFCTL.bit.PULSESEL            = 1U;          -- Pulse Select for Blanking & Capture Alignment
       EPwm6Regs.DCFCTL.bit.BLANKINV            = 0U;          -- Blanking Window Inversion
       EPwm6Regs.DCFCTL.bit.SRCSEL              = 0U;          -- Filter Block Signal Source Select
     */
    EPwm6Regs.DCFCTL.all = (EPwm6Regs.DCFCTL.all & ~0x3FU) | 0x10U;
    EPwm6Regs.DCFOFFSET = 0U;          // Digital Compare Filter Offset Register
    EPwm6Regs.DCFWINDOW = 0U;          // Digital Compare Filter Window Register

    /*	-- Digital Compare Capture Control Register
       EPwm6Regs.DCCAPCTL.bit.CAPE              = 0U;          -- Counter Capture Enable
     */
    EPwm6Regs.DCCAPCTL.all = (EPwm6Regs.DCCAPCTL.all & ~0x1U) | 0x0U;

    /*	-- HRPWM Configuration Register
       EPwm6Regs.HRCNFG.bit.SWAPAB              = 0U;          -- Swap EPWMA and EPWMB Outputs Bit
       EPwm6Regs.HRCNFG.bit.SELOUTB             = 0U;          -- EPWMB Output Selection Bit
     */
    EPwm6Regs.HRCNFG.all = (EPwm6Regs.HRCNFG.all & ~0xA0U) | 0x0U;

    /* Update the Link Registers with the link value for all the Compare values and TBPRD */
    /* No error is thrown if the ePWM register exists in the model or not */
    EPwm6Regs.EPWMXLINK.bit.TBPRDLINK = 5U;
    EPwm6Regs.EPWMXLINK.bit.CMPALINK = 5U;
    EPwm6Regs.EPWMXLINK.bit.CMPBLINK = 5U;
    EPwm6Regs.EPWMXLINK.bit.CMPCLINK = 5U;
    EPwm6Regs.EPWMXLINK.bit.CMPDLINK = 5U;

    /* SYNCPER - Peripheral synchronization output event
       EPwm6Regs.HRPCTL.bit.PWMSYNCSEL            = 0U;          -- EPWMSYNCPER selection
       EPwm6Regs.HRPCTL.bit.PWMSYNCSELX           = 0U;          --  EPWMSYNCPER selection
     */
    EPwm6Regs.HRPCTL.all = (EPwm6Regs.HRPCTL.all & ~0x72U) | 0x0U;
    EDIS;
  }

  /* Start for S-Function (c2802xadc): '<S8>/IsenA' */
  if (MW_adcCInitFlag == 0U) {
    InitAdcC();
    MW_adcCInitFlag = 1U;
  }

  config_ADCC_SOC0 ();

  /* Start for S-Function (c280xqep): '<S11>/eQEP' */
  config_QEP_eQEP1((uint32_T)8191U,(uint32_T)0U, (uint32_T)0, (uint32_T)0,
                   (uint16_T)0, (uint16_T)1024, (uint16_T)4232, (uint16_T)32768,
                   (uint16_T)119,(uint16_T)0);

  /* Start for S-Function (c2802xadc): '<S8>/Vdc' */
  if (MW_adcAInitFlag == 0U) {
    InitAdcA();
    MW_adcAInitFlag = 1U;
  }

  config_ADCA_SOC1 ();

  /* Start for S-Function (c2802xpwm): '<S14>/PWM MOT A' */
  real32_T tbprdValue4 = (real32_T)EPwm4Regs.TBPRD;

  /*** Initialize ePWM4 modules ***/
  {
    /*  -- Time Base Control Register
       EPwm4Regs.TBCTL.bit.CTRMODE              = 2U;          -- Counter Mode
       EPwm4Regs.TBCTL.bit.SYNCOSEL             = 1U;          -- Sync Output Select

       EPwm4Regs.TBCTL.bit.PRDLD                = 0U;          -- Shadow select

       EPwm4Regs.TBCTL2.bit.PRDLDSYNC           = 0U;          -- Shadow select

       EPwm4Regs.TBCTL.bit.PHSEN                = 0U;          -- Phase Load Enable
       EPwm4Regs.TBCTL.bit.PHSDIR               = 0U;          -- Phase Direction Bit
       EPwm4Regs.TBCTL.bit.HSPCLKDIV            = 0U;          -- High Speed TBCLK Pre-scaler
       EPwm4Regs.TBCTL.bit.CLKDIV               = 0U;          -- Time Base Clock Pre-scaler
     */
    EPwm4Regs.TBCTL.all = (EPwm4Regs.TBCTL.all & ~0x3FFFU) | 0x12U;
    EPwm4Regs.TBCTL2.all = (EPwm4Regs.TBCTL2.all & ~0xC000U) | 0x0U;

    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm4Regs.TBPRD = 10000U;          // Time Base Period Register

    /* -- Time-Base Phase Register
       EPwm4Regs.TBPHS.bit.TBPHS               = 0U;          -- Phase offset register
     */
    EPwm4Regs.TBPHS.all = (EPwm4Regs.TBPHS.all & ~0xFFFF0000U) | 0x0U;

    // Time Base Counter Register
    EPwm4Regs.TBCTR = 0x0000U;         /* Clear counter*/

    /*-- Setup Counter_Compare (CC) Submodule --*/
    /*	-- Counter Compare Control Register

       EPwm4Regs.CMPCTL.bit.LOADASYNC           = 0U;          -- Active Compare A Load SYNC Option
       EPwm4Regs.CMPCTL.bit.LOADBSYNC           = 0U;          -- Active Compare B Load SYNC Option
       EPwm4Regs.CMPCTL.bit.LOADAMODE           = 0U;          -- Active Compare A Load
       EPwm4Regs.CMPCTL.bit.LOADBMODE           = 0U;          -- Active Compare B Load
       EPwm4Regs.CMPCTL.bit.SHDWAMODE           = 0U;          -- Compare A Register Block Operating Mode
       EPwm4Regs.CMPCTL.bit.SHDWBMODE           = 0U;          -- Compare B Register Block Operating Mode
     */
    EPwm4Regs.CMPCTL.all = (EPwm4Regs.CMPCTL.all & ~0x3C5FU) | 0x0U;

    /* EPwm4Regs.CMPCTL2.bit.SHDWCMODE           = 0U;          -- Compare C Register Block Operating Mode
       EPwm4Regs.CMPCTL2.bit.SHDWDMODE           = 0U;          -- Compare D Register Block Operating Mode
       EPwm4Regs.CMPCTL2.bit.LOADCSYNC           = 0U;          -- Active Compare C Load SYNC Option
       EPwm4Regs.CMPCTL2.bit.LOADDSYNC           = 0U;          -- Active Compare D Load SYNC Option
       EPwm4Regs.CMPCTL2.bit.LOADCMODE           = 0U;          -- Active Compare C Load
       EPwm4Regs.CMPCTL2.bit.LOADDMODE           = 0U;          -- Active Compare D Load
     */
    EPwm4Regs.CMPCTL2.all = (EPwm4Regs.CMPCTL2.all & ~0x3C5FU) | 0x0U;
    EPwm4Regs.CMPA.bit.CMPA = 0U;      // Counter Compare A Register
    EPwm4Regs.CMPB.bit.CMPB = 2000U;   // Counter Compare B Register
    EPwm4Regs.CMPC = 32000U;           // Counter Compare C Register
    EPwm4Regs.CMPD = 32000U;           // Counter Compare D Register

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm4Regs.AQCTLA.all = 146U;
                               // Action Qualifier Control Register For Output A
    EPwm4Regs.AQCTLB.all = 2310U;
                               // Action Qualifier Control Register For Output B

    /*	-- Action Qualifier Software Force Register
       EPwm4Regs.AQSFRC.bit.RLDCSF              = 0U;          -- Reload from Shadow Options
     */
    EPwm4Regs.AQSFRC.all = (EPwm4Regs.AQSFRC.all & ~0xC0U) | 0x0U;

    /*	-- Action Qualifier Continuous S/W Force Register
       EPwm4Regs.AQCSFRC.bit.CSFA               = 0U;          -- Continuous Software Force on output A
       EPwm4Regs.AQCSFRC.bit.CSFB               = 0U;          -- Continuous Software Force on output B
     */
    EPwm4Regs.AQCSFRC.all = (EPwm4Regs.AQCSFRC.all & ~0xFU) | 0x0U;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    /*	-- Dead-Band Generator Control Register
       EPwm4Regs.DBCTL.bit.OUT_MODE             = 3U;          -- Dead Band Output Mode Control
       EPwm4Regs.DBCTL.bit.IN_MODE              = 0U;          -- Dead Band Input Select Mode Control
       EPwm4Regs.DBCTL.bit.POLSEL               = 2U;          -- Polarity Select Control
       EPwm4Regs.DBCTL.bit.HALFCYCLE            = 0U;          -- Half Cycle Clocking Enable
       EPwm4Regs.DBCTL.bit.SHDWDBREDMODE        = 0U;          -- DBRED shadow mode
       EPwm4Regs.DBCTL.bit.SHDWDBFEDMODE        = 0U;          -- DBFED shadow mode
       EPwm4Regs.DBCTL.bit.LOADREDMODE          = 4U;        -- DBRED load
       EPwm4Regs.DBCTL.bit.LOADFEDMODE          = 4U;        -- DBFED load
     */
    EPwm4Regs.DBCTL.all = (EPwm4Regs.DBCTL.all & ~0x8FFFU) | 0xBU;
    EPwm4Regs.DBRED.bit.DBRED = (uint16_T)(15.0);
                         // Dead-Band Generator Rising Edge Delay Count Register
    EPwm4Regs.DBFED.bit.DBFED = (uint16_T)(15.0);
                        // Dead-Band Generator Falling Edge Delay Count Register

    /*-- Setup Event-Trigger (ET) Submodule --*/
    /*	-- Event Trigger Selection and Pre-Scale Register
       EPwm4Regs.ETSEL.bit.SOCAEN               = 1U;          -- Start of Conversion A Enable
       EPwm4Regs.ETSEL.bit.SOCASELCMP           = 0U;
       EPwm4Regs.ETSEL.bit.SOCASEL              = 2U;          -- Start of Conversion A Select
       EPwm4Regs.ETPS.bit.SOCPSSEL              = 1U;          -- EPWM4SOC Period Select
       EPwm4Regs.ETSOCPS.bit.SOCAPRD2           = 1U;
       EPwm4Regs.ETSEL.bit.SOCBEN               = 0U;          -- Start of Conversion B Enable
       EPwm4Regs.ETSEL.bit.SOCBSELCMP           = 0U;
       EPwm4Regs.ETSEL.bit.SOCBSEL              = 1U;          -- Start of Conversion A Select
       EPwm4Regs.ETPS.bit.SOCPSSEL              = 1;          -- EPWM4SOCB Period Select
       EPwm4Regs.ETSOCPS.bit.SOCBPRD2           = 1U;
       EPwm4Regs.ETSEL.bit.INTEN                = 0U;          -- EPWM4INTn Enable
       EPwm4Regs.ETSEL.bit.INTSELCMP            = 0U;
       EPwm4Regs.ETSEL.bit.INTSEL               = 1U;          -- Start of Conversion A Select
       EPwm4Regs.ETPS.bit.INTPSSEL              = 1U;          // EPWM4INTn Period Select
       EPwm4Regs.ETINTPS.bit.INTPRD2            = 1U;
     */
    EPwm4Regs.ETSEL.all = (EPwm4Regs.ETSEL.all & ~0xFF7FU) | 0x1A01U;
    EPwm4Regs.ETPS.all = (EPwm4Regs.ETPS.all & ~0x30U) | 0x30U;
    EPwm4Regs.ETSOCPS.all = (EPwm4Regs.ETSOCPS.all & ~0xF0FU) | 0x101U;
    EPwm4Regs.ETINTPS.all = (EPwm4Regs.ETINTPS.all & ~0xFU) | 0x1U;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    /*	-- PWM Chopper Control Register
       EPwm4Regs.PCCTL.bit.CHPEN                = 0U;          -- PWM chopping enable
       EPwm4Regs.PCCTL.bit.CHPFREQ              = 0U;          -- Chopping clock frequency
       EPwm4Regs.PCCTL.bit.OSHTWTH              = 0U;          -- One-shot pulse width
       EPwm4Regs.PCCTL.bit.CHPDUTY              = 0U;          -- Chopping clock Duty cycle
     */
    EPwm4Regs.PCCTL.all = (EPwm4Regs.PCCTL.all & ~0x7FFU) | 0x0U;

    /*-- Set up Trip-Zone (TZ) Submodule --*/
    EALLOW;
    EPwm4Regs.TZSEL.all = 0U;          // Trip Zone Select Register

    /*	-- Trip Zone Control Register
       EPwm4Regs.TZCTL.bit.TZA                  = 3U;          -- TZ1 to TZ6 Trip Action On EPWM4A
       EPwm4Regs.TZCTL.bit.TZB                  = 3U;          -- TZ1 to TZ6 Trip Action On EPWM4B
       EPwm4Regs.TZCTL.bit.DCAEVT1              = 3U;          -- EPWM4A action on DCAEVT1
       EPwm4Regs.TZCTL.bit.DCAEVT2              = 3U;          -- EPWM4A action on DCAEVT2
       EPwm4Regs.TZCTL.bit.DCBEVT1              = 3U;          -- EPWM4B action on DCBEVT1
       EPwm4Regs.TZCTL.bit.DCBEVT2              = 3U;          -- EPWM4B action on DCBEVT2
     */
    EPwm4Regs.TZCTL.all = (EPwm4Regs.TZCTL.all & ~0xFFFU) | 0xFFFU;

    /*	-- Trip Zone Enable Interrupt Register
       EPwm4Regs.TZEINT.bit.OST                 = 0U;          -- Trip Zones One Shot Int Enable
       EPwm4Regs.TZEINT.bit.CBC                 = 0U;          -- Trip Zones Cycle By Cycle Int Enable
       EPwm4Regs.TZEINT.bit.DCAEVT1             = 0U;          -- Digital Compare A Event 1 Int Enable
       EPwm4Regs.TZEINT.bit.DCAEVT2             = 0U;          -- Digital Compare A Event 2 Int Enable
       EPwm4Regs.TZEINT.bit.DCBEVT1             = 0U;          -- Digital Compare B Event 1 Int Enable
       EPwm4Regs.TZEINT.bit.DCBEVT2             = 0U;          -- Digital Compare B Event 2 Int Enable
     */
    EPwm4Regs.TZEINT.all = (EPwm4Regs.TZEINT.all & ~0x7EU) | 0x0U;

    /*	-- Digital Compare A Control Register
       EPwm4Regs.DCACTL.bit.EVT1SYNCE           = 0U;          -- DCAEVT1 SYNC Enable
       EPwm4Regs.DCACTL.bit.EVT1SOCE            = 1U;          -- DCAEVT1 SOC Enable
       EPwm4Regs.DCACTL.bit.EVT1FRCSYNCSEL      = 0U;          -- DCAEVT1 Force Sync Signal
       EPwm4Regs.DCACTL.bit.EVT1SRCSEL          = 0U;          -- DCAEVT1 Source Signal
       EPwm4Regs.DCACTL.bit.EVT2FRCSYNCSEL      = 0U;          -- DCAEVT2 Force Sync Signal
       EPwm4Regs.DCACTL.bit.EVT2SRCSEL          = 0U;          -- DCAEVT2 Source Signal
     */
    EPwm4Regs.DCACTL.all = (EPwm4Regs.DCACTL.all & ~0x30FU) | 0x4U;

    /*	-- Digital Compare B Control Register
       EPwm4Regs.DCBCTL.bit.EVT1SYNCE           = 0U;          -- DCBEVT1 SYNC Enable
       EPwm4Regs.DCBCTL.bit.EVT1SOCE            = 0U;          -- DCBEVT1 SOC Enable
       EPwm4Regs.DCBCTL.bit.EVT1FRCSYNCSEL      = 0U;          -- DCBEVT1 Force Sync Signal
       EPwm4Regs.DCBCTL.bit.EVT1SRCSEL          = 0U;          -- DCBEVT1 Source Signal
       EPwm4Regs.DCBCTL.bit.EVT2FRCSYNCSEL      = 0U;          -- DCBEVT2 Force Sync Signal
       EPwm4Regs.DCBCTL.bit.EVT2SRCSEL          = 0U;          -- DCBEVT2 Source Signal
     */
    EPwm4Regs.DCBCTL.all = (EPwm4Regs.DCBCTL.all & ~0x30FU) | 0x0U;

    /*	-- Digital Compare Trip Select Register
       EPwm4Regs.DCTRIPSEL.bit.DCAHCOMPSEL      = 0U;          -- Digital Compare A High COMP Input Select

       EPwm4Regs.DCTRIPSEL.bit.DCALCOMPSEL      = 1U;          -- Digital Compare A Low COMP Input Select
       EPwm4Regs.DCTRIPSEL.bit.DCBHCOMPSEL      = 0U;          -- Digital Compare B High COMP Input Select
       EPwm4Regs.DCTRIPSEL.bit.DCBLCOMPSEL      = 1U;          -- Digital Compare B Low COMP Input Select
     */
    EPwm4Regs.DCTRIPSEL.all = (EPwm4Regs.DCTRIPSEL.all & ~ 0xFFFFU) | 0x1010U;

    /*	-- Trip Zone Digital Comparator Select Register
       EPwm4Regs.TZDCSEL.bit.DCAEVT1            = 0U;          -- Digital Compare Output A Event 1
       EPwm4Regs.TZDCSEL.bit.DCAEVT2            = 0U;          -- Digital Compare Output A Event 2
       EPwm4Regs.TZDCSEL.bit.DCBEVT1            = 0U;          -- Digital Compare Output B Event 1
       EPwm4Regs.TZDCSEL.bit.DCBEVT2            = 0U;          -- Digital Compare Output B Event 2
     */
    EPwm4Regs.TZDCSEL.all = (EPwm4Regs.TZDCSEL.all & ~0xFFFU) | 0x0U;

    /*	-- Digital Compare Filter Control Register
       EPwm4Regs.DCFCTL.bit.BLANKE              = 0U;          -- Blanking Enable/Disable
       EPwm4Regs.DCFCTL.bit.PULSESEL            = 1U;          -- Pulse Select for Blanking & Capture Alignment
       EPwm4Regs.DCFCTL.bit.BLANKINV            = 0U;          -- Blanking Window Inversion
       EPwm4Regs.DCFCTL.bit.SRCSEL              = 0U;          -- Filter Block Signal Source Select
     */
    EPwm4Regs.DCFCTL.all = (EPwm4Regs.DCFCTL.all & ~0x3FU) | 0x10U;
    EPwm4Regs.DCFOFFSET = 0U;          // Digital Compare Filter Offset Register
    EPwm4Regs.DCFWINDOW = 0U;          // Digital Compare Filter Window Register

    /*	-- Digital Compare Capture Control Register
       EPwm4Regs.DCCAPCTL.bit.CAPE              = 0U;          -- Counter Capture Enable
     */
    EPwm4Regs.DCCAPCTL.all = (EPwm4Regs.DCCAPCTL.all & ~0x1U) | 0x0U;

    /*	-- HRPWM Configuration Register
       EPwm4Regs.HRCNFG.bit.SWAPAB              = 0U;          -- Swap EPWMA and EPWMB Outputs Bit
       EPwm4Regs.HRCNFG.bit.SELOUTB             = 0U;          -- EPWMB Output Selection Bit
     */
    EPwm4Regs.HRCNFG.all = (EPwm4Regs.HRCNFG.all & ~0xA0U) | 0x0U;

    /* Update the Link Registers with the link value for all the Compare values and TBPRD */
    /* No error is thrown if the ePWM register exists in the model or not */
    EPwm4Regs.EPWMXLINK.bit.TBPRDLINK = 3U;
    EPwm4Regs.EPWMXLINK.bit.CMPALINK = 3U;
    EPwm4Regs.EPWMXLINK.bit.CMPBLINK = 3U;
    EPwm4Regs.EPWMXLINK.bit.CMPCLINK = 3U;
    EPwm4Regs.EPWMXLINK.bit.CMPDLINK = 3U;

    /* SYNCPER - Peripheral synchronization output event
       EPwm4Regs.HRPCTL.bit.PWMSYNCSEL            = 0U;          -- EPWMSYNCPER selection
       EPwm4Regs.HRPCTL.bit.PWMSYNCSELX           = 0U;          --  EPWMSYNCPER selection
     */
    EPwm4Regs.HRPCTL.all = (EPwm4Regs.HRPCTL.all & ~0x72U) | 0x0U;
    EDIS;
  }

  /* Start for S-Function (c2802xpwm): '<S14>/PWM MOT B' */
  real32_T tbprdValue5 = (real32_T)EPwm5Regs.TBPRD;

  /*** Initialize ePWM5 modules ***/
  {
    /*  -- Time Base Control Register
       EPwm5Regs.TBCTL.bit.CTRMODE              = 2U;          -- Counter Mode
       EPwm5Regs.TBCTL.bit.SYNCOSEL             = 0U;          -- Sync Output Select

       EPwm5Regs.TBCTL.bit.PRDLD                = 0U;          -- Shadow select

       EPwm5Regs.TBCTL2.bit.PRDLDSYNC           = 0U;          -- Shadow select

       EPwm5Regs.TBCTL.bit.PHSEN                = 1U;          -- Phase Load Enable
       EPwm5Regs.TBCTL.bit.PHSDIR               = 1U;          -- Phase Direction Bit
       EPwm5Regs.TBCTL.bit.HSPCLKDIV            = 0U;          -- High Speed TBCLK Pre-scaler
       EPwm5Regs.TBCTL.bit.CLKDIV               = 0U;          -- Time Base Clock Pre-scaler
     */
    EPwm5Regs.TBCTL.all = (EPwm5Regs.TBCTL.all & ~0x3FFFU) | 0x2006U;
    EPwm5Regs.TBCTL2.all = (EPwm5Regs.TBCTL2.all & ~0xC000U) | 0x0U;

    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm5Regs.TBPRD = 10000U;          // Time Base Period Register

    /* -- Time-Base Phase Register
       EPwm5Regs.TBPHS.bit.TBPHS               = 0U;          -- Phase offset register
     */
    EPwm5Regs.TBPHS.all = (EPwm5Regs.TBPHS.all & ~0xFFFF0000U) | 0x0U;

    // Time Base Counter Register
    EPwm5Regs.TBCTR = 0x0000U;         /* Clear counter*/

    /*-- Setup Counter_Compare (CC) Submodule --*/
    /*	-- Counter Compare Control Register

       EPwm5Regs.CMPCTL.bit.LOADASYNC           = 0U;          -- Active Compare A Load SYNC Option
       EPwm5Regs.CMPCTL.bit.LOADBSYNC           = 0U;          -- Active Compare B Load SYNC Option
       EPwm5Regs.CMPCTL.bit.LOADAMODE           = 0U;          -- Active Compare A Load
       EPwm5Regs.CMPCTL.bit.LOADBMODE           = 0U;          -- Active Compare B Load
       EPwm5Regs.CMPCTL.bit.SHDWAMODE           = 0U;          -- Compare A Register Block Operating Mode
       EPwm5Regs.CMPCTL.bit.SHDWBMODE           = 0U;          -- Compare B Register Block Operating Mode
     */
    EPwm5Regs.CMPCTL.all = (EPwm5Regs.CMPCTL.all & ~0x3C5FU) | 0x0U;

    /* EPwm5Regs.CMPCTL2.bit.SHDWCMODE           = 0U;          -- Compare C Register Block Operating Mode
       EPwm5Regs.CMPCTL2.bit.SHDWDMODE           = 0U;          -- Compare D Register Block Operating Mode
       EPwm5Regs.CMPCTL2.bit.LOADCSYNC           = 0U;          -- Active Compare C Load SYNC Option
       EPwm5Regs.CMPCTL2.bit.LOADDSYNC           = 0U;          -- Active Compare D Load SYNC Option
       EPwm5Regs.CMPCTL2.bit.LOADCMODE           = 0U;          -- Active Compare C Load
       EPwm5Regs.CMPCTL2.bit.LOADDMODE           = 0U;          -- Active Compare D Load
     */
    EPwm5Regs.CMPCTL2.all = (EPwm5Regs.CMPCTL2.all & ~0x3C5FU) | 0x0U;
    EPwm5Regs.CMPA.bit.CMPA = 0U;      // Counter Compare A Register
    EPwm5Regs.CMPB.bit.CMPB = 2000U;   // Counter Compare B Register
    EPwm5Regs.CMPC = 32000U;           // Counter Compare C Register
    EPwm5Regs.CMPD = 32000U;           // Counter Compare D Register

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm5Regs.AQCTLA.all = 146U;
                               // Action Qualifier Control Register For Output A
    EPwm5Regs.AQCTLB.all = 2310U;
                               // Action Qualifier Control Register For Output B

    /*	-- Action Qualifier Software Force Register
       EPwm5Regs.AQSFRC.bit.RLDCSF              = 0U;          -- Reload from Shadow Options
     */
    EPwm5Regs.AQSFRC.all = (EPwm5Regs.AQSFRC.all & ~0xC0U) | 0x0U;

    /*	-- Action Qualifier Continuous S/W Force Register
       EPwm5Regs.AQCSFRC.bit.CSFA               = 0U;          -- Continuous Software Force on output A
       EPwm5Regs.AQCSFRC.bit.CSFB               = 0U;          -- Continuous Software Force on output B
     */
    EPwm5Regs.AQCSFRC.all = (EPwm5Regs.AQCSFRC.all & ~0xFU) | 0x0U;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    /*	-- Dead-Band Generator Control Register
       EPwm5Regs.DBCTL.bit.OUT_MODE             = 3U;          -- Dead Band Output Mode Control
       EPwm5Regs.DBCTL.bit.IN_MODE              = 0U;          -- Dead Band Input Select Mode Control
       EPwm5Regs.DBCTL.bit.POLSEL               = 2U;          -- Polarity Select Control
       EPwm5Regs.DBCTL.bit.HALFCYCLE            = 0U;          -- Half Cycle Clocking Enable
       EPwm5Regs.DBCTL.bit.SHDWDBREDMODE        = 0U;          -- DBRED shadow mode
       EPwm5Regs.DBCTL.bit.SHDWDBFEDMODE        = 0U;          -- DBFED shadow mode
       EPwm5Regs.DBCTL.bit.LOADREDMODE          = 4U;        -- DBRED load
       EPwm5Regs.DBCTL.bit.LOADFEDMODE          = 4U;        -- DBFED load
     */
    EPwm5Regs.DBCTL.all = (EPwm5Regs.DBCTL.all & ~0x8FFFU) | 0xBU;
    EPwm5Regs.DBRED.bit.DBRED = (uint16_T)(15.0);
                         // Dead-Band Generator Rising Edge Delay Count Register
    EPwm5Regs.DBFED.bit.DBFED = (uint16_T)(15.0);
                        // Dead-Band Generator Falling Edge Delay Count Register

    /*-- Setup Event-Trigger (ET) Submodule --*/
    /*	-- Event Trigger Selection and Pre-Scale Register
       EPwm5Regs.ETSEL.bit.SOCAEN               = 1U;          -- Start of Conversion A Enable
       EPwm5Regs.ETSEL.bit.SOCASELCMP           = 0U;
       EPwm5Regs.ETSEL.bit.SOCASEL              = 1U;          -- Start of Conversion A Select
       EPwm5Regs.ETPS.bit.SOCPSSEL              = 1U;          -- EPWM5SOC Period Select
       EPwm5Regs.ETSOCPS.bit.SOCAPRD2           = 1U;
       EPwm5Regs.ETSEL.bit.SOCBEN               = 0U;          -- Start of Conversion B Enable
       EPwm5Regs.ETSEL.bit.SOCBSELCMP           = 0U;
       EPwm5Regs.ETSEL.bit.SOCBSEL              = 1U;          -- Start of Conversion A Select
       EPwm5Regs.ETPS.bit.SOCPSSEL              = 1;          -- EPWM5SOCB Period Select
       EPwm5Regs.ETSOCPS.bit.SOCBPRD2           = 1U;
       EPwm5Regs.ETSEL.bit.INTEN                = 0U;          -- EPWM5INTn Enable
       EPwm5Regs.ETSEL.bit.INTSELCMP            = 0U;
       EPwm5Regs.ETSEL.bit.INTSEL               = 1U;          -- Start of Conversion A Select
       EPwm5Regs.ETPS.bit.INTPSSEL              = 1U;          // EPWM5INTn Period Select
       EPwm5Regs.ETINTPS.bit.INTPRD2            = 1U;
     */
    EPwm5Regs.ETSEL.all = (EPwm5Regs.ETSEL.all & ~0xFF7FU) | 0x1901U;
    EPwm5Regs.ETPS.all = (EPwm5Regs.ETPS.all & ~0x30U) | 0x30U;
    EPwm5Regs.ETSOCPS.all = (EPwm5Regs.ETSOCPS.all & ~0xF0FU) | 0x101U;
    EPwm5Regs.ETINTPS.all = (EPwm5Regs.ETINTPS.all & ~0xFU) | 0x1U;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    /*	-- PWM Chopper Control Register
       EPwm5Regs.PCCTL.bit.CHPEN                = 0U;          -- PWM chopping enable
       EPwm5Regs.PCCTL.bit.CHPFREQ              = 0U;          -- Chopping clock frequency
       EPwm5Regs.PCCTL.bit.OSHTWTH              = 0U;          -- One-shot pulse width
       EPwm5Regs.PCCTL.bit.CHPDUTY              = 0U;          -- Chopping clock Duty cycle
     */
    EPwm5Regs.PCCTL.all = (EPwm5Regs.PCCTL.all & ~0x7FFU) | 0x0U;

    /*-- Set up Trip-Zone (TZ) Submodule --*/
    EALLOW;
    EPwm5Regs.TZSEL.all = 0U;          // Trip Zone Select Register

    /*	-- Trip Zone Control Register
       EPwm5Regs.TZCTL.bit.TZA                  = 3U;          -- TZ1 to TZ6 Trip Action On EPWM5A
       EPwm5Regs.TZCTL.bit.TZB                  = 3U;          -- TZ1 to TZ6 Trip Action On EPWM5B
       EPwm5Regs.TZCTL.bit.DCAEVT1              = 3U;          -- EPWM5A action on DCAEVT1
       EPwm5Regs.TZCTL.bit.DCAEVT2              = 3U;          -- EPWM5A action on DCAEVT2
       EPwm5Regs.TZCTL.bit.DCBEVT1              = 3U;          -- EPWM5B action on DCBEVT1
       EPwm5Regs.TZCTL.bit.DCBEVT2              = 3U;          -- EPWM5B action on DCBEVT2
     */
    EPwm5Regs.TZCTL.all = (EPwm5Regs.TZCTL.all & ~0xFFFU) | 0xFFFU;

    /*	-- Trip Zone Enable Interrupt Register
       EPwm5Regs.TZEINT.bit.OST                 = 0U;          -- Trip Zones One Shot Int Enable
       EPwm5Regs.TZEINT.bit.CBC                 = 0U;          -- Trip Zones Cycle By Cycle Int Enable
       EPwm5Regs.TZEINT.bit.DCAEVT1             = 0U;          -- Digital Compare A Event 1 Int Enable
       EPwm5Regs.TZEINT.bit.DCAEVT2             = 0U;          -- Digital Compare A Event 2 Int Enable
       EPwm5Regs.TZEINT.bit.DCBEVT1             = 0U;          -- Digital Compare B Event 1 Int Enable
       EPwm5Regs.TZEINT.bit.DCBEVT2             = 0U;          -- Digital Compare B Event 2 Int Enable
     */
    EPwm5Regs.TZEINT.all = (EPwm5Regs.TZEINT.all & ~0x7EU) | 0x0U;

    /*	-- Digital Compare A Control Register
       EPwm5Regs.DCACTL.bit.EVT1SYNCE           = 0U;          -- DCAEVT1 SYNC Enable
       EPwm5Regs.DCACTL.bit.EVT1SOCE            = 1U;          -- DCAEVT1 SOC Enable
       EPwm5Regs.DCACTL.bit.EVT1FRCSYNCSEL      = 0U;          -- DCAEVT1 Force Sync Signal
       EPwm5Regs.DCACTL.bit.EVT1SRCSEL          = 0U;          -- DCAEVT1 Source Signal
       EPwm5Regs.DCACTL.bit.EVT2FRCSYNCSEL      = 0U;          -- DCAEVT2 Force Sync Signal
       EPwm5Regs.DCACTL.bit.EVT2SRCSEL          = 0U;          -- DCAEVT2 Source Signal
     */
    EPwm5Regs.DCACTL.all = (EPwm5Regs.DCACTL.all & ~0x30FU) | 0x4U;

    /*	-- Digital Compare B Control Register
       EPwm5Regs.DCBCTL.bit.EVT1SYNCE           = 0U;          -- DCBEVT1 SYNC Enable
       EPwm5Regs.DCBCTL.bit.EVT1SOCE            = 0U;          -- DCBEVT1 SOC Enable
       EPwm5Regs.DCBCTL.bit.EVT1FRCSYNCSEL      = 0U;          -- DCBEVT1 Force Sync Signal
       EPwm5Regs.DCBCTL.bit.EVT1SRCSEL          = 0U;          -- DCBEVT1 Source Signal
       EPwm5Regs.DCBCTL.bit.EVT2FRCSYNCSEL      = 0U;          -- DCBEVT2 Force Sync Signal
       EPwm5Regs.DCBCTL.bit.EVT2SRCSEL          = 0U;          -- DCBEVT2 Source Signal
     */
    EPwm5Regs.DCBCTL.all = (EPwm5Regs.DCBCTL.all & ~0x30FU) | 0x0U;

    /*	-- Digital Compare Trip Select Register
       EPwm5Regs.DCTRIPSEL.bit.DCAHCOMPSEL      = 0U;          -- Digital Compare A High COMP Input Select

       EPwm5Regs.DCTRIPSEL.bit.DCALCOMPSEL      = 1U;          -- Digital Compare A Low COMP Input Select
       EPwm5Regs.DCTRIPSEL.bit.DCBHCOMPSEL      = 0U;          -- Digital Compare B High COMP Input Select
       EPwm5Regs.DCTRIPSEL.bit.DCBLCOMPSEL      = 1U;          -- Digital Compare B Low COMP Input Select
     */
    EPwm5Regs.DCTRIPSEL.all = (EPwm5Regs.DCTRIPSEL.all & ~ 0xFFFFU) | 0x1010U;

    /*	-- Trip Zone Digital Comparator Select Register
       EPwm5Regs.TZDCSEL.bit.DCAEVT1            = 0U;          -- Digital Compare Output A Event 1
       EPwm5Regs.TZDCSEL.bit.DCAEVT2            = 0U;          -- Digital Compare Output A Event 2
       EPwm5Regs.TZDCSEL.bit.DCBEVT1            = 0U;          -- Digital Compare Output B Event 1
       EPwm5Regs.TZDCSEL.bit.DCBEVT2            = 0U;          -- Digital Compare Output B Event 2
     */
    EPwm5Regs.TZDCSEL.all = (EPwm5Regs.TZDCSEL.all & ~0xFFFU) | 0x0U;

    /*	-- Digital Compare Filter Control Register
       EPwm5Regs.DCFCTL.bit.BLANKE              = 0U;          -- Blanking Enable/Disable
       EPwm5Regs.DCFCTL.bit.PULSESEL            = 1U;          -- Pulse Select for Blanking & Capture Alignment
       EPwm5Regs.DCFCTL.bit.BLANKINV            = 0U;          -- Blanking Window Inversion
       EPwm5Regs.DCFCTL.bit.SRCSEL              = 0U;          -- Filter Block Signal Source Select
     */
    EPwm5Regs.DCFCTL.all = (EPwm5Regs.DCFCTL.all & ~0x3FU) | 0x10U;
    EPwm5Regs.DCFOFFSET = 0U;          // Digital Compare Filter Offset Register
    EPwm5Regs.DCFWINDOW = 0U;          // Digital Compare Filter Window Register

    /*	-- Digital Compare Capture Control Register
       EPwm5Regs.DCCAPCTL.bit.CAPE              = 0U;          -- Counter Capture Enable
     */
    EPwm5Regs.DCCAPCTL.all = (EPwm5Regs.DCCAPCTL.all & ~0x1U) | 0x0U;

    /*	-- HRPWM Configuration Register
       EPwm5Regs.HRCNFG.bit.SWAPAB              = 0U;          -- Swap EPWMA and EPWMB Outputs Bit
       EPwm5Regs.HRCNFG.bit.SELOUTB             = 0U;          -- EPWMB Output Selection Bit
     */
    EPwm5Regs.HRCNFG.all = (EPwm5Regs.HRCNFG.all & ~0xA0U) | 0x0U;

    /* Update the Link Registers with the link value for all the Compare values and TBPRD */
    /* No error is thrown if the ePWM register exists in the model or not */
    EPwm5Regs.EPWMXLINK.bit.TBPRDLINK = 4U;
    EPwm5Regs.EPWMXLINK.bit.CMPALINK = 4U;
    EPwm5Regs.EPWMXLINK.bit.CMPBLINK = 4U;
    EPwm5Regs.EPWMXLINK.bit.CMPCLINK = 4U;
    EPwm5Regs.EPWMXLINK.bit.CMPDLINK = 4U;

    /* SYNCPER - Peripheral synchronization output event
       EPwm5Regs.HRPCTL.bit.PWMSYNCSEL            = 0U;          -- EPWMSYNCPER selection
       EPwm5Regs.HRPCTL.bit.PWMSYNCSELX           = 0U;          --  EPWMSYNCPER selection
     */
    EPwm5Regs.HRPCTL.all = (EPwm5Regs.HRPCTL.all & ~0x72U) | 0x0U;
    EDIS;
  }

  /* Start for S-Function (c2802xadc): '<S8>/IsenB' */
  if (MW_adcBInitFlag == 0U) {
    InitAdcB();
    MW_adcBInitFlag = 1U;
  }

  config_ADCB_SOC0 ();

  /* Start for S-Function (c2802xadc): '<S8>/IsenC' */
  if (MW_adcAInitFlag == 0U) {
    InitAdcA();
    MW_adcAInitFlag = 1U;
  }

  config_ADCA_SOC0 ();

  /* Start for S-Function (c2802xadc): '<S8>/VsenA' */
  if (MW_adcAInitFlag == 0U) {
    InitAdcA();
    MW_adcAInitFlag = 1U;
  }

  config_ADCA_SOC2 ();

  /* Start for S-Function (c2802xadc): '<S8>/VsenB' */
  if (MW_adcCInitFlag == 0U) {
    InitAdcC();
    MW_adcCInitFlag = 1U;
  }

  config_ADCC_SOC3 ();

  /* SystemInitialize for MATLAB Function: '<S8>/MATLAB Function' */
  BasePerTracing_DW.OutPrecedente_k = 0.0;

  /* SystemInitialize for MATLAB Function: '<S11>/MATLAB Function' */
  BasePerTracing_DW.OutPrecedente = 0.0;

  /* SystemInitialize for MATLAB Function: '<S11>/MATLAB Function1' */
  BasePerTracing_DW.CounterPrec = 0.0;

  /* SystemInitialize for MATLAB Function: '<S2>/MATLAB Function1' */
  BasePe_MATLABFunction1_Init(&BasePerTracing_DW.sf_MATLABFunction1_n);

  /* SystemInitialize for MATLAB Function: '<S2>/MATLAB Function2' */
  BasePe_MATLABFunction1_Init(&BasePerTracing_DW.sf_MATLABFunction2);
}

/* System reset for function-call system: '<Root>/Current Control' */
void BasePe_CurrentControl_Reset(void)
{
  /* Asynchronous task reads absolute time. Data (absolute time)
     transfers from low priority task (base rate) to high priority
     task (asynchronous rate). Double buffers are used to ensure
     data integrity.
     -- rtmL2HLastBufWr is the buffer index that is written last.
   */
  BasePerTracing_M->Timing.clockTick2 =
    BasePerTracing_M->Timing.rtmL2HDbBufClockTick
    [BasePerTracing_M->Timing.rtmL2HLastBufWr];

  /* SystemReset for MATLAB Function: '<S11>/MATLAB Function1' */
  BasePerTracing_DW.CounterPrec = 0.0;

  /* SystemReset for MATLAB Function: '<S11>/MATLAB Function' */
  BasePerTracing_DW.OutPrecedente = 0.0;

  /* SystemReset for MATLAB Function: '<S2>/MATLAB Function2' */
  BaseP_MATLABFunction1_Reset(&BasePerTracing_DW.sf_MATLABFunction2);

  /* SystemReset for MATLAB Function: '<S2>/MATLAB Function1' */
  BaseP_MATLABFunction1_Reset(&BasePerTracing_DW.sf_MATLABFunction1_n);

  /* SystemReset for MATLAB Function: '<S8>/MATLAB Function' */
  BasePerTracing_DW.OutPrecedente_k = 0.0;
}

/* Enable for function-call system: '<Root>/Current Control' */
#pragma CODE_SECTION (BaseP_CurrentControl_Enable, "ramfuncs")

void BaseP_CurrentControl_Enable(void)
{
  /* Asynchronous task reads absolute time. Data (absolute time)
     transfers from low priority task (base rate) to high priority
     task (asynchronous rate). Double buffers are used to ensure
     data integrity.
     -- rtmL2HLastBufWr is the buffer index that is written last.
   */
  BasePerTracing_M->Timing.clockTick2 =
    BasePerTracing_M->Timing.rtmL2HDbBufClockTick
    [BasePerTracing_M->Timing.rtmL2HLastBufWr];
  BasePerTracing_DW.CurrentControl_RESET_ELAPS_T = true;
}

/* Output and update for function-call system: '<Root>/Current Control' */
#pragma CODE_SECTION (BasePerTraci_CurrentControl, "ramfuncs")

void BasePerTraci_CurrentControl(void)
{
  real_T OmegaMis;
  real_T elapseTime;
  real32_T u0;
  uint32_T Data;
  int16_T s21_iter;

  /* Asynchronous task reads absolute time. Data (absolute time)
     transfers from low priority task (base rate) to high priority
     task (asynchronous rate). Double buffers are used to ensure
     data integrity.
     -- rtmL2HLastBufWr is the buffer index that is written last.
   */
  BasePerTracing_M->Timing.clockTick2 =
    BasePerTracing_M->Timing.rtmL2HDbBufClockTick
    [BasePerTracing_M->Timing.rtmL2HLastBufWr];
  if (BasePerTracing_DW.CurrentControl_RESET_ELAPS_T) {
    BasePerTracing_DW.CurrentControl_ELAPS_T = 0UL;
  } else {
    BasePerTracing_DW.CurrentControl_ELAPS_T =
      BasePerTracing_M->Timing.clockTick2 -
      BasePerTracing_DW.CurrentControl_PREV_T;
  }

  BasePerTracing_DW.CurrentControl_PREV_T = BasePerTracing_M->Timing.clockTick2;
  BasePerTracing_DW.CurrentControl_RESET_ELAPS_T = false;

  /* S-Function (c2802xadc): '<S8>/IsenA' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    BasePerTracing_B.IsenA = (AdccResultRegs.ADCRESULT0);
  }

  /* Sum: '<S8>/Sum' incorporates:
   *  Constant: '<S8>/OffsetADCINC4'
   */
  BasePerTracing_B.Sum = (real_T)BasePerTracing_B.IsenA - 2296.0;

  /* Gain: '<S8>/ConversioneADC in VOLT_' */
  BasePerTracing_B.ConversioneADCinVOLT_ = 0.0007326007326007326 *
    BasePerTracing_B.Sum;

  /* Gain: '<S8>/Gain3' */
  BasePerTracing_B.Gain3 = 14.285714285714286 *
    BasePerTracing_B.ConversioneADCinVOLT_;

  /* Gain: '<S2>/rpm to r//s1' */
  BasePerTracing_B.rpmtors1 = 0.10471975511965977 *
    BasePerTracing_B.RateTransition2;

  /* SampleTimeMath: '<S10>/TSamp'
   *
   * About '<S10>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  elapseTime = (real_T)BasePerTracing_DW.CurrentControl_ELAPS_T * 0.0001;

  /* SampleTimeMath: '<S10>/TSamp'
   *
   * About '<S10>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  BasePerTracing_B.TSamp = BasePerTracing_B.rpmtors1 / elapseTime;

  /* UnitDelay: '<S10>/UD' */
  BasePerTracing_B.Uk1 = BasePerTracing_DW.UD_DSTATE;

  /* Sum: '<S10>/Diff' */
  BasePerTracing_B.Diff = BasePerTracing_B.TSamp - BasePerTracing_B.Uk1;

  /* Gain: '<S2>/Gain' */
  BasePerTracing_B.Gain = 0.00066545454545454547 * BasePerTracing_B.Diff;

  /* Gain: '<S2>/rpm to r//s' */
  BasePerTracing_B.rpmtors = 0.10471975511965977 *
    BasePerTracing_B.RateTransition1;

  /* S-Function (c280xqep): '<S11>/eQEP' */
  {
    BasePerTracing_B.eQEP = EQep1Regs.QPOSCNT;/*eQEP Position Counter*/
  }

  /* DataTypeConversion: '<S11>/Data Type Conversion1' */
  BasePerTracing_B.DataTypeConversion1 = BasePerTracing_B.eQEP;

  /* MATLAB Function: '<S11>/MATLAB Function1' incorporates:
   *  Constant: '<S11>/Constant3'
   *  Constant: '<S11>/Constant7'
   */
  /* MATLAB Function 'Current Control/ENCODER/MATLAB Function1': '<S18>:1' */
  /* '<S18>:1:9' */
  elapseTime = BasePerTracing_B.DataTypeConversion1 -
    BasePerTracing_DW.CounterPrec;
  if (elapseTime > 4096.0) {
    /* '<S18>:1:11' */
    /* '<S18>:1:12' */
    elapseTime -= 8192.0;
  }

  if (elapseTime < -4096.0) {
    /* '<S18>:1:15' */
    /* '<S18>:1:16' */
    elapseTime += 8192.0;
  }

  /* '<S18>:1:20' */
  BasePerTracing_B.ThetaMis = BasePerTracing_B.DataTypeConversion1 *
    0.00076708403213033649;

  /* '<S18>:1:22' */
  /* '<S18>:1:24' */
  OmegaMis = elapseTime * 0.00076708403213033649 / 0.0001;

  /* '<S18>:1:25' */
  BasePerTracing_B.OmegaMisRPM = OmegaMis * 60.0 / 6.2831853071795862;

  /* '<S18>:1:27' */
  BasePerTracing_DW.CounterPrec = BasePerTracing_B.DataTypeConversion1;
  BasePerTracing_B.OmegaMis = OmegaMis;
  BasePerTracing_B.DeltaCounter = elapseTime;

  /* End of MATLAB Function: '<S11>/MATLAB Function1' */

  /* MATLAB Function: '<S11>/MATLAB Function' incorporates:
   *  Constant: '<S11>/Constant1'
   *  Constant: '<S11>/Constant2'
   */
  /* MATLAB Function 'Current Control/ENCODER/MATLAB Function': '<S17>:1' */
  /* '<S17>:1:9' */
  /* '<S17>:1:10' */
  /* '<S17>:1:12' */
  BasePerTracing_B.out = 0.0196078431372549 * BasePerTracing_B.OmegaMis +
    BasePerTracing_DW.OutPrecedente * 0.98039215686274506;

  /* '<S17>:1:14' */
  BasePerTracing_DW.OutPrecedente = BasePerTracing_B.out;

  /* Sum: '<S2>/Sum1' */
  BasePerTracing_B.ErroreSpeed = BasePerTracing_B.rpmtors - BasePerTracing_B.out;

  /* DataStoreRead: '<S2>/Enable1' */
  BasePerTracing_B.PWM_En_g = BasePerTracing_DW.Enable;

  /* DataTypeConversion: '<S2>/Data Type Conversion' */
  BasePerTracing_B.DataTypeConversion_a = BasePerTracing_B.PWM_En_g;

  /* MATLAB Function: '<S2>/MATLAB Function2' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant14'
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/EnableSaturation'
   */
  BasePerTrac_MATLABFunction1(BasePerTracing_B.ErroreSpeed, 0.066545454545454547,
    0.085, 0.0001, BasePerTracing_B.DataTypeConversion_a, 1.0, 6.0, -6.0,
    &BasePerTracing_B.sf_MATLABFunction2, &BasePerTracing_DW.sf_MATLABFunction2);

  /* Sum: '<S2>/Sum3' */
  BasePerTracing_B.Sum3 = BasePerTracing_B.Gain +
    BasePerTracing_B.sf_MATLABFunction2.out;

  /* Sum: '<S2>/Sum2' */
  BasePerTracing_B.Sum2 = BasePerTracing_B.Sum3 - BasePerTracing_B.Gain3;

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  Constant: '<S2>/Constant5'
   *  Constant: '<S2>/Constant6'
   *  Constant: '<S2>/Constant7'
   *  Constant: '<S2>/Constant8'
   *  Constant: '<S2>/Constant9'
   *  Constant: '<S2>/EnableSaturation'
   */
  BasePerTrac_MATLABFunction1(BasePerTracing_B.Sum2, 4.1000000000000005,
    0.00128125, 0.0001, BasePerTracing_B.DataTypeConversion_a, 1.0, 32.0, -32.0,
    &BasePerTracing_B.sf_MATLABFunction1_n,
    &BasePerTracing_DW.sf_MATLABFunction1_n);

  /* Gain: '<S2>/Gain2' */
  BasePerTracing_B.Gain2 = 0.11 * BasePerTracing_B.out;

  /* Sum: '<S2>/Sum' */
  BasePerTracing_B.Sum_a = BasePerTracing_B.sf_MATLABFunction1_n.out +
    BasePerTracing_B.Gain2;

  /* S-Function (c2802xadc): '<S8>/Vdc' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    BasePerTracing_B.Vdc = (AdcaResultRegs.ADCRESULT1);
  }

  /* Gain: '<S8>/ConversioneADC in VOLT' */
  BasePerTracing_B.ConversioneADCinVOLT = 49164UL * BasePerTracing_B.Vdc;

  /* Gain: '<S8>/Gain5' incorporates:
   *  Gain: '<S8>/ConversioneADC in VOLT'
   */
  BasePerTracing_B.Gain5 = 3603705651ULL * BasePerTracing_B.ConversioneADCinVOLT;

  /* Product: '<S14>/Divide' incorporates:
   *  Gain: '<S8>/Gain5'
   */
  BasePerTracing_B.Divide = (real32_T)(BasePerTracing_B.Sum_a / ((real_T)
    BasePerTracing_B.Gain5 * 5.5511151231257827E-17));

  /* Saturate: '<S14>/Saturation' */
  u0 = BasePerTracing_B.Divide;
  if (u0 > 0.95F) {
    /* Saturate: '<S14>/Saturation' */
    BasePerTracing_B.Saturation = 0.95F;
  } else if (u0 < -0.95F) {
    /* Saturate: '<S14>/Saturation' */
    BasePerTracing_B.Saturation = -0.95F;
  } else {
    /* Saturate: '<S14>/Saturation' */
    BasePerTracing_B.Saturation = u0;
  }

  /* End of Saturate: '<S14>/Saturation' */

  /* Sum: '<S14>/Add1' incorporates:
   *  Constant: '<S14>/Constant'
   */
  BasePerTracing_B.Add1 = BasePerTracing_B.Saturation + 1.0F;

  /* Gain: '<S14>/Gain4' */
  BasePerTracing_B.Gain4 = (real32_T)(0.5 * BasePerTracing_B.Add1);

  /* Gain: '<S14>/Gain6' */
  BasePerTracing_B.Gain6 = 100.0F * BasePerTracing_B.Gain4;

  /* S-Function (c2802xpwm): '<S14>/PWM MOT A' */
  uint16_T tbprdValue4Outputs = EPwm4Regs.TBPRD;

  /*-- Update CMPA value for ePWM4 --*/
  {
    EPwm4Regs.CMPA.bit.CMPA = (uint16_T)((uint32_T)EPwm4Regs.TBPRD *
      BasePerTracing_B.Gain6 * 0.01);
  }

  /* Sum: '<S14>/Add3' incorporates:
   *  Constant: '<S14>/Constant'
   */
  BasePerTracing_B.Add3 = 1.0F - BasePerTracing_B.Saturation;

  /* Gain: '<S14>/Gain2' */
  BasePerTracing_B.Gain2_a = (real32_T)(0.5 * BasePerTracing_B.Add3);

  /* Gain: '<S14>/Gain1' */
  BasePerTracing_B.Gain1_k = 100.0F * BasePerTracing_B.Gain2_a;

  /* S-Function (c2802xpwm): '<S14>/PWM MOT B' */
  uint16_T tbprdValue5Outputs = EPwm5Regs.TBPRD;

  /*-- Update CMPA value for ePWM5 --*/
  {
    EPwm5Regs.CMPA.bit.CMPA = (uint16_T)((uint32_T)EPwm5Regs.TBPRD *
      BasePerTracing_B.Gain1_k * 0.01);
  }

  /* UnitDelay: '<S23>/Output' */
  BasePerTracing_B.Output_m = BasePerTracing_DW.Output_DSTATE_h;

  /* DataTypeConversion: '<S9>/Cast To Single1' */
  BasePerTracing_B.CastToSingle1 = (real32_T)BasePerTracing_B.RateTransition1;

  /* Gain: '<S2>/Gain1' */
  BasePerTracing_B.Gain1 = 9.5492965855137211 * BasePerTracing_B.out;

  /* DataTypeConversion: '<S9>/Cast To Single2' */
  BasePerTracing_B.CastToSingle2 = (real32_T)BasePerTracing_B.Gain1;

  /* DataTypeConversion: '<S9>/Cast To Single3' */
  BasePerTracing_B.CastToSingle3 = (real32_T)BasePerTracing_B.Sum3;

  /* DataTypeConversion: '<S9>/Cast To Single4' */
  BasePerTracing_B.CastToSingle4 = (real32_T)BasePerTracing_B.Gain3;

  /* DataTypeConversion: '<S9>/Cast To Single5' */
  BasePerTracing_B.CastToSingle5 = (real32_T)BasePerTracing_B.Sum_a;

  /* DataTypeConversion: '<S9>/Cast To Single6' incorporates:
   *  Gain: '<S8>/Gain5'
   */
  BasePerTracing_B.CastToSingle6 = (real32_T)BasePerTracing_B.Gain5 *
    5.55111512E-17F;

  /* DataTypeConversion: '<S9>/Cast To Single' */
  BasePerTracing_B.CastToSingle_b[0] = BasePerTracing_B.CastToSingle1;
  BasePerTracing_B.CastToSingle_b[1] = BasePerTracing_B.CastToSingle2;
  BasePerTracing_B.CastToSingle_b[2] = BasePerTracing_B.CastToSingle3;
  BasePerTracing_B.CastToSingle_b[3] = BasePerTracing_B.CastToSingle4;
  BasePerTracing_B.CastToSingle_b[4] = BasePerTracing_B.CastToSingle5;
  BasePerTracing_B.CastToSingle_b[5] = BasePerTracing_B.CastToSingle6;
  BasePerTracing_B.CastToSingle_b[6] = BasePerTracing_ConstB.CastToSingle7;
  BasePerTracing_B.CastToSingle_b[7] = BasePerTracing_ConstB.CastToSingle8;
  BasePerTracing_B.CastToSingle_b[8] = BasePerTracing_ConstB.CastToSingle9;

  /* DataStoreRead: '<S9>/Data Store Read' */
  BasePerTracing_B.DataStoreRead_j = BasePerTracing_DW.Debug_signals;

  /* MultiPortSwitch: '<S9>/Multiport Switch' */
  switch (BasePerTracing_B.DataStoreRead_j) {
   case 1:
    /* MultiPortSwitch: '<S9>/Multiport Switch' incorporates:
     *  Constant: '<S9>/speed_control'
     */
    BasePerTracing_B.MultiportSwitch[0] = 1U;
    BasePerTracing_B.MultiportSwitch[1] = 2U;
    break;

   case 2:
    /* MultiPortSwitch: '<S9>/Multiport Switch' incorporates:
     *  Constant: '<S9>/current'
     */
    BasePerTracing_B.MultiportSwitch[0] = 3U;
    BasePerTracing_B.MultiportSwitch[1] = 4U;
    break;

   case 3:
    /* MultiPortSwitch: '<S9>/Multiport Switch' incorporates:
     *  Constant: '<S9>/voltage'
     */
    BasePerTracing_B.MultiportSwitch[0] = 6U;
    BasePerTracing_B.MultiportSwitch[1] = 5U;
    break;

   case 4:
    /* MultiPortSwitch: '<S9>/Multiport Switch' incorporates:
     *  Constant: '<S9>/dbgA'
     */
    BasePerTracing_B.MultiportSwitch[0] = 7U;
    BasePerTracing_B.MultiportSwitch[1] = 8U;
    break;

   default:
    /* MultiPortSwitch: '<S9>/Multiport Switch' incorporates:
     *  Constant: '<S9>/dbgB'
     */
    BasePerTracing_B.MultiportSwitch[0] = 8U;
    BasePerTracing_B.MultiportSwitch[1] = 9U;
    break;
  }

  /* End of MultiPortSwitch: '<S9>/Multiport Switch' */

  /* Selector: '<S9>/Selector' */
  BasePerTracing_B.Selector[0] = BasePerTracing_B.CastToSingle_b[(int16_T)
    BasePerTracing_B.MultiportSwitch[0] - 1];
  BasePerTracing_B.Selector[1] = BasePerTracing_B.CastToSingle_b[(int16_T)
    BasePerTracing_B.MultiportSwitch[1] - 1];

  /* S-Function (any2byte_svd): '<S22>/Byte Pack' */

  /* Pack: <S22>/Byte Pack */
  {
    uint32_T MW_outputPortOffset = 0U;
    uint16_T MW_inputPortWidth = 0U;

    /* Packed output data type - uint32_T */
    void* packData = &BasePerTracing_B.BytePack[0];

    /* Packing the values of Input 1 */
    /* Input data type - real32_T, size - 2 */
    {
      MW_inputPortWidth = (uint16_T)2 * sizeof(real32_T);
      memcpy((void *)&(((uint16_T *)packData)[MW_outputPortOffset]), (void*)
             &BasePerTracing_B.Selector[0], MW_inputPortWidth);
    }
  }

  /* If: '<S20>/If' */
  if (BasePerTracing_B.Output_m == 0U) {
    /* Outputs for IfAction SubSystem: '<S20>/Start' incorporates:
     *  ActionPort: '<S26>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  Constant: '<S26>/Start'
     *  SignalConversion generated from: '<S26>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[0] = 1397969747UL;

    /* SignalConversion generated from: '<S26>/Data' */
    Data = BasePerTracing_B.BytePack[0];

    /* End of Outputs for SubSystem: '<S20>/Start' */
    BasePerTracing_B.Data_fw[0] = Data;

    /* Outputs for IfAction SubSystem: '<S20>/Start' incorporates:
     *  ActionPort: '<S26>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  SignalConversion generated from: '<S26>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[1] = Data;

    /* SignalConversion generated from: '<S26>/Data' */
    Data = BasePerTracing_B.BytePack[1];

    /* End of Outputs for SubSystem: '<S20>/Start' */
    BasePerTracing_B.Data_fw[1] = Data;

    /* Outputs for IfAction SubSystem: '<S20>/Start' incorporates:
     *  ActionPort: '<S26>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  SignalConversion generated from: '<S26>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[2] = Data;

    /* Merge: '<S20>/Merge1' incorporates:
     *  Bias: '<S26>/Bias'
     */
    BasePerTracing_B.SCI_Tx_Iteration = BasePerTracing_ConstB.Width + 1UL;

    /* End of Outputs for SubSystem: '<S20>/Start' */
  } else if (BasePerTracing_B.Output_m == 599U) {
    /* Outputs for IfAction SubSystem: '<S20>/End' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    /* SignalConversion generated from: '<S25>/Data' */
    Data = BasePerTracing_B.BytePack[0];

    /* End of Outputs for SubSystem: '<S20>/End' */
    BasePerTracing_B.Data_f[0] = Data;

    /* Outputs for IfAction SubSystem: '<S20>/End' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  SignalConversion generated from: '<S25>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[0] = Data;

    /* SignalConversion generated from: '<S25>/Data' */
    Data = BasePerTracing_B.BytePack[1];

    /* End of Outputs for SubSystem: '<S20>/End' */
    BasePerTracing_B.Data_f[1] = Data;

    /* Outputs for IfAction SubSystem: '<S20>/End' incorporates:
     *  ActionPort: '<S25>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  Constant: '<S25>/End'
     *  SignalConversion generated from: '<S25>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[1] = Data;
    BasePerTracing_B.SCI_Tx_Data[2] = 1162167621UL;

    /* Merge: '<S20>/Merge1' incorporates:
     *  Bias: '<S25>/Bias'
     */
    BasePerTracing_B.SCI_Tx_Iteration = BasePerTracing_ConstB.Width + 1UL;

    /* End of Outputs for SubSystem: '<S20>/End' */
  } else {
    /* Outputs for IfAction SubSystem: '<S20>/Data' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    /* SignalConversion generated from: '<S24>/Data' */
    Data = BasePerTracing_B.BytePack[0];

    /* End of Outputs for SubSystem: '<S20>/Data' */
    BasePerTracing_B.Data[0] = Data;

    /* Outputs for IfAction SubSystem: '<S20>/Data' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  SignalConversion generated from: '<S24>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[0] = Data;

    /* SignalConversion generated from: '<S24>/Data' */
    Data = BasePerTracing_B.BytePack[1];

    /* End of Outputs for SubSystem: '<S20>/Data' */
    BasePerTracing_B.Data[1] = Data;

    /* Outputs for IfAction SubSystem: '<S20>/Data' incorporates:
     *  ActionPort: '<S24>/Action Port'
     */
    /* Merge: '<S20>/Merge' incorporates:
     *  Constant: '<S24>/Dummy'
     *  SignalConversion generated from: '<S24>/Data_out'
     */
    BasePerTracing_B.SCI_Tx_Data[1] = Data;
    BasePerTracing_B.SCI_Tx_Data[2] = 0UL;

    /* Merge: '<S20>/Merge1' incorporates:
     *  SignalConversion generated from: '<S24>/Data_width'
     */
    BasePerTracing_B.SCI_Tx_Iteration = BasePerTracing_ConstB.Width;

    /* End of Outputs for SubSystem: '<S20>/Data' */
  }

  /* End of If: '<S20>/If' */

  /* Outputs for Iterator SubSystem: '<S15>/While Iterator Subsystem' incorporates:
   *  WhileIterator: '<S21>/While Iterator'
   */
  s21_iter = 1;
  do {
    BasePerTracing_B.WhileIterator = s21_iter;
    BasePerTracing_B.IndexVector =
      BasePerTracing_B.SCI_Tx_Data[BasePerTracing_B.WhileIterator - 1];

    {
      if (checkSCITransmitInProgressA != 1U) {
        checkSCITransmitInProgressA = 1U;
        int16_T errFlgHeader = NOERROR;
        int16_T errFlgData = NOERROR;
        int16_T errFlgTail = NOERROR;
        errFlgData = scia_xmit((uchar_T*)&BasePerTracing_B.IndexVector, 4, 4);
        checkSCITransmitInProgressA = 0U;
      }
    }

    BasePerTracing_B.Add = BasePerTracing_B.SCI_Tx_Iteration - (uint32_T)
      BasePerTracing_B.WhileIterator;
    s21_iter++;
  } while (BasePerTracing_B.Add != 0UL);

  /* End of Outputs for SubSystem: '<S15>/While Iterator Subsystem' */

  /* Sum: '<S27>/FixPt Sum1' incorporates:
   *  Constant: '<S27>/FixPt Constant'
   */
  BasePerTracing_B.FixPtSum1_k = BasePerTracing_B.Output_m + 1U;

  /* Switch: '<S28>/FixPt Switch' */
  if (BasePerTracing_B.FixPtSum1_k > 599U) {
    /* Switch: '<S28>/FixPt Switch' incorporates:
     *  Constant: '<S28>/Constant'
     */
    BasePerTracing_B.FixPtSwitch_l = 0U;
  } else {
    /* Switch: '<S28>/FixPt Switch' */
    BasePerTracing_B.FixPtSwitch_l = BasePerTracing_B.FixPtSum1_k;
  }

  /* End of Switch: '<S28>/FixPt Switch' */

  /* DataTypeConversion: '<S8>/Data Type Conversion3' */
  BasePerTracing_B.DataTypeConversion3 = BasePerTracing_B.IsenA;

  /* MATLAB Function: '<S8>/MATLAB Function' incorporates:
   *  Constant: '<S8>/Constant5'
   *  Constant: '<S8>/Constant6'
   */
  /* MATLAB Function 'Current Control/AnalogReading/MATLAB Function': '<S16>:1' */
  /* '<S16>:1:10' */
  /* '<S16>:1:11' */
  /* '<S16>:1:13' */
  BasePerTracing_B.out_a = 9.9990000999900015E-5 *
    BasePerTracing_B.DataTypeConversion3 + BasePerTracing_DW.OutPrecedente_k *
    0.99990000999900008;

  /* '<S16>:1:15' */
  BasePerTracing_DW.OutPrecedente_k = BasePerTracing_B.out_a;

  /* S-Function (c2802xadc): '<S8>/IsenB' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    BasePerTracing_B.IsenB = (AdcbResultRegs.ADCRESULT0);
  }

  /* S-Function (c2802xadc): '<S8>/IsenC' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    BasePerTracing_B.IsenC = (AdcaResultRegs.ADCRESULT0);
  }

  /* S-Function (c2802xadc): '<S8>/VsenA' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    BasePerTracing_B.VsenA = (AdcaResultRegs.ADCRESULT2);
  }

  /* S-Function (c2802xadc): '<S8>/VsenB' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    BasePerTracing_B.VsenB = (AdccResultRegs.ADCRESULT3);
  }

  /* DataStoreRead: '<S2>/Data Store Read' */
  BasePerTracing_B.DataStoreRead = BasePerTracing_DW.SpeedRef;

  /* Update for UnitDelay: '<S10>/UD' */
  BasePerTracing_DW.UD_DSTATE = BasePerTracing_B.TSamp;

  /* Update for UnitDelay: '<S23>/Output' */
  BasePerTracing_DW.Output_DSTATE_h = BasePerTracing_B.FixPtSwitch_l;
}

/* ConstCode for function-call system: '<Root>/Current Control' */
#pragma CODE_SECTION (BasePe_CurrentControl_Const, "ramfuncs")

void BasePe_CurrentControl_Const(void)
{
  /* ConstCode for S-Function (c2802xpwm): '<S14>/PWM MOT C' incorporates:
   *  Constant: '<S14>/Constant6'
   */
  uint16_T tbprdValue6Outputs = EPwm6Regs.TBPRD;

  /*-- Update CMPA value for ePWM6 --*/
  {
    EPwm6Regs.CMPA.bit.CMPA = (uint16_T)((uint32_T)EPwm6Regs.TBPRD * 0.0 * 0.01);
  }
}

/* Model step function for TID0 */
void BasePerTracing_step0(void)        /* Sample time: [0.0001s, 0.0s] */
{
  {                                    /* Sample time: [0.0001s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* UnitDelay: '<S32>/Output' */
  BasePerTracing_B.Output = BasePerTracing_DW.Output_DSTATE;

  /* DataTypeConversion: '<S5>/Data Type Conversion' */
  BasePerTracing_B.DataTypeConversion = BasePerTracing_B.Output;

  /* SampleTimeMath: '<S5>/Sample Time Math'
   *
   * About '<S5>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  BasePerTracing_B.SampleTimeMath = BasePerTracing_B.DataTypeConversion * 0.0001;

  /* Lookup_n-D: '<S5>/Lookup' incorporates:
   *  SampleTimeMath: '<S5>/Sample Time Math'
   *
   * About '<S5>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  BasePerTracing_B.Lookup = look1_binlc(BasePerTracing_B.SampleTimeMath,
    BasePerTracing_ConstP.pooled6, BasePerTracing_ConstP.Lookup_tableData, 8UL);

  /* RateTransition: '<Root>/Rate Transition1' */
  BasePerTracing_DW.RateTransition1_Buffer[BasePerTracing_DW.RateTransition1_ActiveBufIdx
    == 0] = BasePerTracing_B.Lookup;
  BasePerTracing_DW.RateTransition1_ActiveBufIdx =
    (BasePerTracing_DW.RateTransition1_ActiveBufIdx == 0);

  /* UnitDelay: '<S35>/Output' */
  BasePerTracing_B.Output_i = BasePerTracing_DW.Output_DSTATE_p;

  /* DataTypeConversion: '<S6>/Data Type Conversion' */
  BasePerTracing_B.DataTypeConversion_m = BasePerTracing_B.Output_i;

  /* SampleTimeMath: '<S6>/Sample Time Math'
   *
   * About '<S6>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  BasePerTracing_B.SampleTimeMath_h = BasePerTracing_B.DataTypeConversion_m *
    0.0001;

  /* Lookup_n-D: '<S6>/Lookup' incorporates:
   *  SampleTimeMath: '<S6>/Sample Time Math'
   *
   * About '<S6>/Sample Time Math':
   *  y = u * K where K = ( w * Ts )
   *   */
  BasePerTracing_B.Lookup_l = look1_binlc(BasePerTracing_B.SampleTimeMath_h,
    BasePerTracing_ConstP.pooled6, BasePerTracing_ConstP.Lookup_tableData_m, 8UL);

  /* RateTransition: '<Root>/Rate Transition2' */
  BasePerTracing_DW.RateTransition2_Buffer[BasePerTracing_DW.RateTransition2_ActiveBufIdx
    == 0] = BasePerTracing_B.Lookup_l;
  BasePerTracing_DW.RateTransition2_ActiveBufIdx =
    (BasePerTracing_DW.RateTransition2_ActiveBufIdx == 0);

  /* Sum: '<S33>/FixPt Sum1' incorporates:
   *  Constant: '<S33>/FixPt Constant'
   */
  BasePerTracing_B.FixPtSum1 = BasePerTracing_B.Output + 1U;

  /* Switch: '<S34>/FixPt Switch' */
  if (BasePerTracing_B.FixPtSum1 > 4500U) {
    /* Switch: '<S34>/FixPt Switch' incorporates:
     *  Constant: '<S34>/Constant'
     */
    BasePerTracing_B.FixPtSwitch = 0U;
  } else {
    /* Switch: '<S34>/FixPt Switch' */
    BasePerTracing_B.FixPtSwitch = BasePerTracing_B.FixPtSum1;
  }

  /* End of Switch: '<S34>/FixPt Switch' */

  /* Sum: '<S36>/FixPt Sum1' incorporates:
   *  Constant: '<S36>/FixPt Constant'
   */
  BasePerTracing_B.FixPtSum1_c = BasePerTracing_B.Output_i + 1U;

  /* Switch: '<S37>/FixPt Switch' */
  if (BasePerTracing_B.FixPtSum1_c > 4500U) {
    /* Switch: '<S37>/FixPt Switch' incorporates:
     *  Constant: '<S37>/Constant'
     */
    BasePerTracing_B.FixPtSwitch_o = 0U;
  } else {
    /* Switch: '<S37>/FixPt Switch' */
    BasePerTracing_B.FixPtSwitch_o = BasePerTracing_B.FixPtSum1_c;
  }

  /* End of Switch: '<S37>/FixPt Switch' */

  /* DataStoreRead: '<S3>/Enable1' */
  BasePerTracing_B.PWM_En = BasePerTracing_DW.Enable;

  /* DataTypeConversion: '<S3>/Data Type Conversion' */
  BasePerTracing_B.DataTypeConversion_k = BasePerTracing_B.PWM_En;

  /* Switch: '<S3>/Switch' */
  BasePerTracing_B.Switch = !(BasePerTracing_B.DataTypeConversion_k > 0.0F);

  /* S-Function (c280xgpio_do): '<S3>/Digital Output1' */
  {
    if (BasePerTracing_B.Switch) {
      GpioDataRegs.GPBSET.bit.GPIO34 = 1U;
    } else {
      GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1U;
    }
  }

  /* S-Function (c280xgpio_do): '<S3>/ENABLE' */
  {
    if (BasePerTracing_B.DataTypeConversion_k) {
      GpioDataRegs.GPASET.bit.GPIO26 = 1U;
    } else {
      GpioDataRegs.GPACLEAR.bit.GPIO26 = 1U;
    }
  }

  /* Update for UnitDelay: '<S32>/Output' */
  BasePerTracing_DW.Output_DSTATE = BasePerTracing_B.FixPtSwitch;

  /* Update for UnitDelay: '<S35>/Output' */
  BasePerTracing_DW.Output_DSTATE_p = BasePerTracing_B.FixPtSwitch_o;

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.0001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  BasePerTracing_M->Timing.clockTick0++;

  {
    /* Base rate updates double buffers of absolute time for
       asynchronous task. Double buffers are used to ensure
       data integrity when asynchronous task reads absolute
       time.
       -- rtmL2HLastBufWr is the buffer index that is written last.
     */
    boolean_T bufIdx = !(BasePerTracing_M->Timing.rtmL2HLastBufWr != 0U);
    BasePerTracing_M->Timing.rtmL2HDbBufClockTick[bufIdx] =
      BasePerTracing_M->Timing.clockTick0;
    BasePerTracing_M->Timing.rtmL2HLastBufWr = bufIdx ? 1U : 0U;
  }
}

/* Model step function for TID1 */
void BasePerTracing_step1(void)        /* Sample time: [0.5s, 0.0s] */
{
  /* S-Function (c280xgpio_do): '<S3>/Digital Output' incorporates:
   *  Constant: '<S3>/Constant'
   */
  {
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = (uint16_T)((1.0) != 0);
  }
}

/* Model initialize function */
void BasePerTracing_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)BasePerTracing_M, 0,
                sizeof(RT_MODEL_BasePerTracing_T));

  /* block I/O */
  (void) memset(((void *) &BasePerTracing_B), 0,
                sizeof(B_BasePerTracing_T));

  {
    int16_T i;
    for (i = 0; i < 9; i++) {
      BasePerTracing_B.CastToSingle_b[i] = 0.0F;
    }

    BasePerTracing_B.DataTypeConversion = 0.0;
    BasePerTracing_B.SampleTimeMath = 0.0;
    BasePerTracing_B.Lookup = 0.0;
    BasePerTracing_B.DataTypeConversion_m = 0.0;
    BasePerTracing_B.SampleTimeMath_h = 0.0;
    BasePerTracing_B.Lookup_l = 0.0;
    BasePerTracing_B.Switch = 0.0;
    BasePerTracing_B.RateTransition1 = 0.0;
    BasePerTracing_B.RateTransition2 = 0.0;
    BasePerTracing_B.Sum = 0.0;
    BasePerTracing_B.ConversioneADCinVOLT_ = 0.0;
    BasePerTracing_B.Gain3 = 0.0;
    BasePerTracing_B.rpmtors1 = 0.0;
    BasePerTracing_B.TSamp = 0.0;
    BasePerTracing_B.Uk1 = 0.0;
    BasePerTracing_B.Diff = 0.0;
    BasePerTracing_B.Gain = 0.0;
    BasePerTracing_B.rpmtors = 0.0;
    BasePerTracing_B.DataTypeConversion1 = 0.0;
    BasePerTracing_B.ErroreSpeed = 0.0;
    BasePerTracing_B.Sum3 = 0.0;
    BasePerTracing_B.Sum2 = 0.0;
    BasePerTracing_B.Gain2 = 0.0;
    BasePerTracing_B.Sum_a = 0.0;
    BasePerTracing_B.Add1 = 0.0;
    BasePerTracing_B.Add3 = 0.0;
    BasePerTracing_B.Gain1 = 0.0;
    BasePerTracing_B.DataTypeConversion3 = 0.0;
    BasePerTracing_B.ThetaMis = 0.0;
    BasePerTracing_B.OmegaMis = 0.0;
    BasePerTracing_B.OmegaMisRPM = 0.0;
    BasePerTracing_B.DeltaCounter = 0.0;
    BasePerTracing_B.out = 0.0;
    BasePerTracing_B.out_a = 0.0;
    BasePerTracing_B.DataTypeConversion_k = 0.0F;
    BasePerTracing_B.SCIReceive[0] = 0.0F;
    BasePerTracing_B.SCIReceive[1] = 0.0F;
    BasePerTracing_B.CastToSingle = 0.0F;
    BasePerTracing_B.eQEP = 0.0F;
    BasePerTracing_B.DataTypeConversion_a = 0.0F;
    BasePerTracing_B.Divide = 0.0F;
    BasePerTracing_B.Saturation = 0.0F;
    BasePerTracing_B.Gain4 = 0.0F;
    BasePerTracing_B.Gain6 = 0.0F;
    BasePerTracing_B.Gain2_a = 0.0F;
    BasePerTracing_B.Gain1_k = 0.0F;
    BasePerTracing_B.CastToSingle1 = 0.0F;
    BasePerTracing_B.CastToSingle2 = 0.0F;
    BasePerTracing_B.CastToSingle3 = 0.0F;
    BasePerTracing_B.CastToSingle4 = 0.0F;
    BasePerTracing_B.CastToSingle5 = 0.0F;
    BasePerTracing_B.CastToSingle6 = 0.0F;
    BasePerTracing_B.Selector[0] = 0.0F;
    BasePerTracing_B.Selector[1] = 0.0F;
    BasePerTracing_B.DataStoreRead = 0.0F;
    BasePerTracing_B.sf_MATLABFunction2.out = 0.0;
    BasePerTracing_B.sf_MATLABFunction1_n.out = 0.0;
  }

  /* states (dwork) */
  (void) memset((void *)&BasePerTracing_DW, 0,
                sizeof(DW_BasePerTracing_T));
  BasePerTracing_DW.UD_DSTATE = 0.0;
  BasePerTracing_DW.IaOffset = 0.0;
  BasePerTracing_DW.IbOffset = 0.0;
  BasePerTracing_DW.RateTransition1_Buffer[0] = 0.0;
  BasePerTracing_DW.RateTransition1_Buffer[1] = 0.0;
  BasePerTracing_DW.RateTransition2_Buffer[0] = 0.0;
  BasePerTracing_DW.RateTransition2_Buffer[1] = 0.0;
  BasePerTracing_DW.Sum_DWORK1 = 0.0;
  BasePerTracing_DW.CounterPrec = 0.0;
  BasePerTracing_DW.OutPrecedente = 0.0;
  BasePerTracing_DW.OutPrecedente_k = 0.0;
  BasePerTracing_DW.SpeedRef = 0.0F;
  BasePerTracing_DW.Add1_DWORK1 = 0.0F;
  BasePerTracing_DW.sf_MATLABFunction2.in_prev = 0.0;
  BasePerTracing_DW.sf_MATLABFunction2.out_prev = 0.0;
  BasePerTracing_DW.sf_MATLABFunction1_n.in_prev = 0.0;
  BasePerTracing_DW.sf_MATLABFunction1_n.out_prev = 0.0;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory1' */
  BasePerTracing_DW.IaOffset = 2295.0;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory2' */
  BasePerTracing_DW.IbOffset = 2286.0;

  /* Start for S-Function (c280xgpio_do): '<S3>/Digital Output1' */
  EALLOW;
  GpioCtrlRegs.GPBMUX1.all &= 0xFFFFFFCFU;
  GpioCtrlRegs.GPBDIR.all |= 0x4U;
  EDIS;

  /* Start for S-Function (c280xgpio_do): '<S3>/ENABLE' */
  EALLOW;
  GpioCtrlRegs.GPAMUX2.all &= 0xFFCFFFFFU;
  GpioCtrlRegs.GPADIR.all |= 0x4000000U;
  EDIS;

  /* Start for S-Function (c280xgpio_do): '<S3>/Digital Output' */
  EALLOW;
  GpioCtrlRegs.GPAMUX2.all &= 0x3FFFFFFFU;
  GpioCtrlRegs.GPADIR.all |= 0x80000000U;
  EDIS;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory6' */
  BasePerTracing_DW.Debug_signals = 5U;

  /* SystemInitialize for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Current Control'
   */
  BasePer_CurrentControl_Init();

  /* SystemInitialize for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Serial Receive'
   */

  /* System initialize for function-call system: '<Root>/Serial Receive' */

  /* Start for S-Function (c28xsci_rx): '<S41>/SCI Receive' */

  /* Initialize out port */
  {
    BasePerTracing_B.SCIReceive[0] = (real32_T)0.0;
    BasePerTracing_B.SCIReceive[1] = (real32_T)0.0;
  }

  /*Configure Timer2 when blocking mode is enabled and Timeout is not inf*/
  {
    /* InitCpuTimers() - CPU Timers are also initialized in
     * MW_c28xx_board.c in the generated code.
     */
    CpuTimer2Regs.PRD.all = 0xFFFFFFFFU;/* max Period*/
    CpuTimer2Regs.TIM.all = 0xFFFFFFFFU;/* set Ctr*/
    CpuTimer2Regs.TPR.all = 0x00U;     /* no prescaler    */
    StartCpuTimer2();
  }

  /* End of SystemInitialize for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */

  /* Enable for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Current Control'
   */
  BaseP_CurrentControl_Enable();

  /* End of Enable for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */

  /* ConstCode for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' incorporates:
   *  SubSystem: '<Root>/Current Control'
   */
  BasePe_CurrentControl_Const();

  /* End of ConstCode for S-Function (c28xisr_c2000): '<S1>/C28x Hardware Interrupt' */
}

/* Model terminate function */
void BasePerTracing_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
