/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BasePerTracing.h
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

#ifndef BasePerTracing_h_
#define BasePerTracing_h_
#ifndef BasePerTracing_COMMON_INCLUDES_
#define BasePerTracing_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "string.h"
#include "DSP28xx_SciUtil.h"
#include "IQmathLib.h"
#endif                                 /* BasePerTracing_COMMON_INCLUDES_ */

#include "BasePerTracing_types.h"
#include <string.h>
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

extern void init_SCI(void);
extern void init_SCI_GPIO(void);
extern void config_ePWMSyncSource(void);
extern void config_ePWM_GPIO (void);
extern void config_ePWM_TBSync (void);
extern void config_ePWM_XBAR(void);

/* Block signals for system '<S2>/MATLAB Function1' */
typedef struct {
  real_T out;                          /* '<S2>/MATLAB Function1' */
} B_MATLABFunction1_BasePerTrac_T;

/* Block states (default storage) for system '<S2>/MATLAB Function1' */
typedef struct {
  real_T in_prev;                      /* '<S2>/MATLAB Function1' */
  real_T out_prev;                     /* '<S2>/MATLAB Function1' */
} DW_MATLABFunction1_BasePerTra_T;

/* Block signals (default storage) */
typedef struct {
  uint64_T Gain5;                      /* '<S8>/Gain5' */
  real_T DataTypeConversion;           /* '<S5>/Data Type Conversion' */
  real_T SampleTimeMath;               /* '<S5>/Sample Time Math' */
  real_T Lookup;                       /* '<S5>/Lookup' */
  real_T DataTypeConversion_m;         /* '<S6>/Data Type Conversion' */
  real_T SampleTimeMath_h;             /* '<S6>/Sample Time Math' */
  real_T Lookup_l;                     /* '<S6>/Lookup' */
  real_T Switch;                       /* '<S3>/Switch' */
  real_T RateTransition1;              /* '<Root>/Rate Transition1' */
  real_T RateTransition2;              /* '<Root>/Rate Transition2' */
  real_T Sum;                          /* '<S8>/Sum' */
  real_T ConversioneADCinVOLT_;        /* '<S8>/ConversioneADC in VOLT_' */
  real_T Gain3;                        /* '<S8>/Gain3' */
  real_T rpmtors1;                     /* '<S2>/rpm to r//s1' */
  real_T TSamp;                        /* '<S10>/TSamp' */
  real_T Uk1;                          /* '<S10>/UD' */
  real_T Diff;                         /* '<S10>/Diff' */
  real_T Gain;                         /* '<S2>/Gain' */
  real_T rpmtors;                      /* '<S2>/rpm to r//s' */
  real_T DataTypeConversion1;          /* '<S11>/Data Type Conversion1' */
  real_T ErroreSpeed;                  /* '<S2>/Sum1' */
  real_T Sum3;                         /* '<S2>/Sum3' */
  real_T Sum2;                         /* '<S2>/Sum2' */
  real_T Gain2;                        /* '<S2>/Gain2' */
  real_T Sum_a;                        /* '<S2>/Sum' */
  real_T Add1;                         /* '<S14>/Add1' */
  real_T Add3;                         /* '<S14>/Add3' */
  real_T Gain1;                        /* '<S2>/Gain1' */
  real_T DataTypeConversion3;          /* '<S8>/Data Type Conversion3' */
  real_T ThetaMis;                     /* '<S11>/MATLAB Function1' */
  real_T OmegaMis;                     /* '<S11>/MATLAB Function1' */
  real_T OmegaMisRPM;                  /* '<S11>/MATLAB Function1' */
  real_T DeltaCounter;                 /* '<S11>/MATLAB Function1' */
  real_T out;                          /* '<S11>/MATLAB Function' */
  real_T out_a;                        /* '<S8>/MATLAB Function' */
  uint32_T BytePack[2];                /* '<S22>/Byte Pack' */
  uint32_T SCI_Tx_Data[3];             /* '<S20>/Merge' */
  uint32_T SCI_Tx_Iteration;           /* '<S20>/Merge1' */
  uint32_T IndexVector;                /* '<S21>/Index Vector' */
  uint32_T Add;                        /* '<S21>/Add' */
  uint32_T Data[2];                    /* '<S24>/Data' */
  uint32_T Data_f[2];                  /* '<S25>/Data' */
  uint32_T Data_fw[2];                 /* '<S26>/Data' */
  uint32_T ConversioneADCinVOLT;       /* '<S8>/ConversioneADC in VOLT' */
  real32_T DataTypeConversion_k;       /* '<S3>/Data Type Conversion' */
  real32_T SCIReceive[2];              /* '<S41>/SCI Receive' */
  real32_T CastToSingle;               /* '<S7>/Cast To Single' */
  real32_T eQEP;                       /* '<S11>/eQEP' */
  real32_T DataTypeConversion_a;       /* '<S2>/Data Type Conversion' */
  real32_T Divide;                     /* '<S14>/Divide' */
  real32_T Saturation;                 /* '<S14>/Saturation' */
  real32_T Gain4;                      /* '<S14>/Gain4' */
  real32_T Gain6;                      /* '<S14>/Gain6' */
  real32_T Gain2_a;                    /* '<S14>/Gain2' */
  real32_T Gain1_k;                    /* '<S14>/Gain1' */
  real32_T CastToSingle1;              /* '<S9>/Cast To Single1' */
  real32_T CastToSingle2;              /* '<S9>/Cast To Single2' */
  real32_T CastToSingle3;              /* '<S9>/Cast To Single3' */
  real32_T CastToSingle4;              /* '<S9>/Cast To Single4' */
  real32_T CastToSingle5;              /* '<S9>/Cast To Single5' */
  real32_T CastToSingle6;              /* '<S9>/Cast To Single6' */
  real32_T CastToSingle_b[9];          /* '<S9>/Cast To Single' */
  real32_T Selector[2];                /* '<S9>/Selector' */
  real32_T DataStoreRead;              /* '<S2>/Data Store Read' */
  uint16_T Output;                     /* '<S32>/Output' */
  uint16_T Output_i;                   /* '<S35>/Output' */
  uint16_T FixPtSum1;                  /* '<S33>/FixPt Sum1' */
  uint16_T FixPtSwitch;                /* '<S34>/FixPt Switch' */
  uint16_T FixPtSum1_c;                /* '<S36>/FixPt Sum1' */
  uint16_T FixPtSwitch_o;              /* '<S37>/FixPt Switch' */
  uint16_T DataTypeConversion2;        /* '<S42>/Data Type Conversion2' */
  uint16_T BitwiseOperator;            /* '<S40>/Bitwise Operator' */
  uint16_T BitwiseOperator1;           /* '<S40>/Bitwise Operator1' */
  uint16_T ShiftArithmetic1;           /* '<S40>/Shift Arithmetic1' */
  uint16_T IsenA;                      /* '<S8>/IsenA' */
  uint16_T Vdc;                        /* '<S8>/Vdc' */
  uint16_T Output_m;                   /* '<S23>/Output' */
  uint16_T DataStoreRead_j;            /* '<S9>/Data Store Read' */
  uint16_T MultiportSwitch[2];         /* '<S9>/Multiport Switch' */
  uint16_T FixPtSum1_k;                /* '<S27>/FixPt Sum1' */
  uint16_T FixPtSwitch_l;              /* '<S28>/FixPt Switch' */
  uint16_T IsenB;                      /* '<S8>/IsenB' */
  uint16_T IsenC;                      /* '<S8>/IsenC' */
  uint16_T VsenA;                      /* '<S8>/VsenA' */
  uint16_T VsenB;                      /* '<S8>/VsenB' */
  int16_T WhileIterator;               /* '<S21>/While Iterator' */
  boolean_T PWM_En;                    /* '<S3>/Enable1' */
  boolean_T DataTypeConversion3_f;     /* '<S40>/Data Type Conversion3' */
  boolean_T PWM_En_g;                  /* '<S2>/Enable1' */
  B_MATLABFunction1_BasePerTrac_T sf_MATLABFunction2;/* '<S2>/MATLAB Function2' */
  B_MATLABFunction1_BasePerTrac_T sf_MATLABFunction1_n;/* '<S2>/MATLAB Function1' */
} B_BasePerTracing_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UD_DSTATE;                    /* '<S10>/UD' */
  real_T IaOffset;                     /* '<Root>/Data Store Memory1' */
  real_T IbOffset;                     /* '<Root>/Data Store Memory2' */
  volatile real_T RateTransition1_Buffer[2];/* '<Root>/Rate Transition1' */
  volatile real_T RateTransition2_Buffer[2];/* '<Root>/Rate Transition2' */
  real_T Sum_DWORK1;                   /* '<S8>/Sum' */
  real_T CounterPrec;                  /* '<S11>/MATLAB Function1' */
  real_T OutPrecedente;                /* '<S11>/MATLAB Function' */
  real_T OutPrecedente_k;              /* '<S8>/MATLAB Function' */
  real32_T SpeedRef;                   /* '<Root>/Data Store Memory4' */
  real32_T Add1_DWORK1;                /* '<S14>/Add1' */
  int32_T DigitalOutput1_FRAC_LEN;     /* '<S3>/Digital Output1' */
  int32_T ENABLE_FRAC_LEN;             /* '<S3>/ENABLE' */
  int32_T DigitalOutput_FRAC_LEN;      /* '<S3>/Digital Output' */
  uint32_T CurrentControl_ELAPS_T;     /* '<Root>/Current Control' */
  uint32_T CurrentControl_PREV_T;      /* '<Root>/Current Control' */
  uint32_T Add_DWORK1;                 /* '<S21>/Add' */
  uint16_T Output_DSTATE;              /* '<S32>/Output' */
  uint16_T Output_DSTATE_p;            /* '<S35>/Output' */
  uint16_T Output_DSTATE_h;            /* '<S23>/Output' */
  volatile int16_T RateTransition1_ActiveBufIdx;/* '<Root>/Rate Transition1' */
  volatile int16_T RateTransition2_ActiveBufIdx;/* '<Root>/Rate Transition2' */
  uint16_T Debug_signals;              /* '<Root>/Data Store Memory6' */
  boolean_T EnClosedLoop;              /* '<Root>/Data Store Memory3' */
  boolean_T Enable;                    /* '<Root>/Data Store Memory29' */
  boolean_T CurrentControl_RESET_ELAPS_T;/* '<Root>/Current Control' */
  DW_MATLABFunction1_BasePerTra_T sf_MATLABFunction2;/* '<S2>/MATLAB Function2' */
  DW_MATLABFunction1_BasePerTra_T sf_MATLABFunction1_n;/* '<S2>/MATLAB Function1' */
} DW_BasePerTracing_T;

/* Invariant block signals (default storage) */
typedef struct {
  const uint32_T Width;                /* '<S20>/Width' */
  const real32_T CastToSingle7;        /* '<S9>/Cast To Single7' */
  const real32_T CastToSingle8;        /* '<S9>/Cast To Single8' */
  const real32_T CastToSingle9;        /* '<S9>/Cast To Single9' */
} ConstB_BasePerTracing_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: OutValues
   * Referenced by: '<S5>/Lookup'
   */
  real_T Lookup_tableData[9];

  /* Pooled Parameter (Expression: TimeValues)
   * Referenced by:
   *   '<S5>/Lookup'
   *   '<S6>/Lookup'
   */
  real_T pooled6[9];

  /* Expression: OutValues
   * Referenced by: '<S6>/Lookup'
   */
  real_T Lookup_tableData_m[9];
} ConstP_BasePerTracing_T;

/* Real-time Model Data Structure */
struct tag_RTM_BasePerTracing_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint16_T rtmL2HLastBufWr;
    uint32_T rtmL2HDbBufClockTick[2];
    uint32_T clockTick2;
    struct {
      uint16_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals (default storage) */
extern B_BasePerTracing_T BasePerTracing_B;

/* Block states (default storage) */
extern DW_BasePerTracing_T BasePerTracing_DW;
extern const ConstB_BasePerTracing_T BasePerTracing_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_BasePerTracing_T BasePerTracing_ConstP;

/* External function called from main */
extern void BasePerTracing_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void BasePerTracing_initialize(void);
extern void BasePerTracing_step0(void);/* Sample time: [0.0001s, 0.0s] */
extern void BasePerTracing_step1(void);/* Sample time: [0.5s, 0.0s] */
extern void BasePerTracing_terminate(void);
extern volatile boolean_T runModel;

/* Real-time Model object */
extern RT_MODEL_BasePerTracing_T *const BasePerTracing_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'BasePerTracing'
 * '<S1>'   : 'BasePerTracing/Code generation'
 * '<S2>'   : 'BasePerTracing/Current Control'
 * '<S3>'   : 'BasePerTracing/Gestione LED//Enable'
 * '<S4>'   : 'BasePerTracing/Repeating Sequence Interpolated'
 * '<S5>'   : 'BasePerTracing/Repeating Sequence Interpolated1'
 * '<S6>'   : 'BasePerTracing/Repeating Sequence Interpolated2'
 * '<S7>'   : 'BasePerTracing/Serial Receive'
 * '<S8>'   : 'BasePerTracing/Current Control/AnalogReading'
 * '<S9>'   : 'BasePerTracing/Current Control/Debug_signals'
 * '<S10>'  : 'BasePerTracing/Current Control/Discrete Derivative'
 * '<S11>'  : 'BasePerTracing/Current Control/ENCODER'
 * '<S12>'  : 'BasePerTracing/Current Control/MATLAB Function1'
 * '<S13>'  : 'BasePerTracing/Current Control/MATLAB Function2'
 * '<S14>'  : 'BasePerTracing/Current Control/PWM'
 * '<S15>'  : 'BasePerTracing/Current Control/SCI (Code Generation)'
 * '<S16>'  : 'BasePerTracing/Current Control/AnalogReading/MATLAB Function'
 * '<S17>'  : 'BasePerTracing/Current Control/ENCODER/MATLAB Function'
 * '<S18>'  : 'BasePerTracing/Current Control/ENCODER/MATLAB Function1'
 * '<S19>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Conditioning_Tx'
 * '<S20>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging'
 * '<S21>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/While Iterator Subsystem'
 * '<S22>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Conditioning_Tx/Data_Type_Float'
 * '<S23>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Counter Limited'
 * '<S24>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Data'
 * '<S25>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/End'
 * '<S26>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Start'
 * '<S27>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Counter Limited/Increment Real World'
 * '<S28>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Counter Limited/Wrap To Zero'
 * '<S29>'  : 'BasePerTracing/Repeating Sequence Interpolated/LimitedCounter'
 * '<S30>'  : 'BasePerTracing/Repeating Sequence Interpolated/LimitedCounter/Increment Real World'
 * '<S31>'  : 'BasePerTracing/Repeating Sequence Interpolated/LimitedCounter/Wrap To Zero'
 * '<S32>'  : 'BasePerTracing/Repeating Sequence Interpolated1/LimitedCounter'
 * '<S33>'  : 'BasePerTracing/Repeating Sequence Interpolated1/LimitedCounter/Increment Real World'
 * '<S34>'  : 'BasePerTracing/Repeating Sequence Interpolated1/LimitedCounter/Wrap To Zero'
 * '<S35>'  : 'BasePerTracing/Repeating Sequence Interpolated2/LimitedCounter'
 * '<S36>'  : 'BasePerTracing/Repeating Sequence Interpolated2/LimitedCounter/Increment Real World'
 * '<S37>'  : 'BasePerTracing/Repeating Sequence Interpolated2/LimitedCounter/Wrap To Zero'
 * '<S38>'  : 'BasePerTracing/Serial Receive/Code Generation'
 * '<S39>'  : 'BasePerTracing/Serial Receive/Data_Conditioning_Rx'
 * '<S40>'  : 'BasePerTracing/Serial Receive/unParse'
 * '<S41>'  : 'BasePerTracing/Serial Receive/Code Generation/Data_Type_Float'
 * '<S42>'  : 'BasePerTracing/Serial Receive/Data_Conditioning_Rx/Data_Type_Float'
 */
#endif                                 /* BasePerTracing_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
