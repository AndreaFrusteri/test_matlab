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
 * C/C++ source code generated on : Thu May 21 10:20:22 2026
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
#include <stddef.h>
#include <string.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
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
  uint64_T Gain5;                      /* '<S5>/Gain5' */
  real_T Switch;                       /* '<S3>/Switch' */
  real_T Sum;                          /* '<S5>/Sum' */
  real_T ConversioneADCinVOLT_;        /* '<S5>/ConversioneADC in VOLT_' */
  real_T Gain3;                        /* '<S5>/Gain3' */
  real_T DataTypeConversion1;          /* '<S7>/Data Type Conversion1' */
  real_T ErroreSpeed;                  /* '<S2>/Sum1' */
  real_T Sum2;                         /* '<S2>/Sum2' */
  real_T Gain2;                        /* '<S2>/Gain2' */
  real_T Sum_a;                        /* '<S2>/Sum' */
  real_T Add1;                         /* '<S10>/Add1' */
  real_T Add3;                         /* '<S10>/Add3' */
  real_T Gain1;                        /* '<S2>/Gain1' */
  real_T DataTypeConversion3;          /* '<S5>/Data Type Conversion3' */
  real_T ThetaMis;                     /* '<S7>/MATLAB Function1' */
  real_T OmegaMis;                     /* '<S7>/MATLAB Function1' */
  real_T OmegaMisRPM;                  /* '<S7>/MATLAB Function1' */
  real_T DeltaCounter;                 /* '<S7>/MATLAB Function1' */
  real_T out;                          /* '<S7>/MATLAB Function' */
  real_T out_a;                        /* '<S5>/MATLAB Function' */
  uint32_T BytePack[2];                /* '<S18>/Byte Pack' */
  uint32_T SCI_Tx_Data[3];             /* '<S16>/Merge' */
  uint32_T SCI_Tx_Iteration;           /* '<S16>/Merge1' */
  uint32_T IndexVector;                /* '<S17>/Index Vector' */
  uint32_T Add;                        /* '<S17>/Add' */
  uint32_T Data[2];                    /* '<S20>/Data' */
  uint32_T Data_f[2];                  /* '<S21>/Data' */
  uint32_T Data_fw[2];                 /* '<S22>/Data' */
  uint32_T ConversioneADCinVOLT;       /* '<S5>/ConversioneADC in VOLT' */
  real32_T DataTypeConversion;         /* '<S3>/Data Type Conversion' */
  real32_T SCIReceive[2];              /* '<S28>/SCI Receive' */
  real32_T CastToSingle;               /* '<S4>/Cast To Single' */
  real32_T DataTypeConversion_a;       /* '<S2>/Data Type Conversion' */
  real32_T DataStoreRead;              /* '<S2>/Data Store Read' */
  real32_T rpmtors;                    /* '<S2>/rpm to r//s' */
  real32_T eQEP;                       /* '<S7>/eQEP' */
  real32_T Divide;                     /* '<S10>/Divide' */
  real32_T Saturation;                 /* '<S10>/Saturation' */
  real32_T Gain4;                      /* '<S10>/Gain4' */
  real32_T Gain6;                      /* '<S10>/Gain6' */
  real32_T Gain2_a;                    /* '<S10>/Gain2' */
  real32_T Gain1_k;                    /* '<S10>/Gain1' */
  real32_T CastToSingle2;              /* '<S6>/Cast To Single2' */
  real32_T CastToSingle3;              /* '<S6>/Cast To Single3' */
  real32_T CastToSingle4;              /* '<S6>/Cast To Single4' */
  real32_T CastToSingle5;              /* '<S6>/Cast To Single5' */
  real32_T CastToSingle6;              /* '<S6>/Cast To Single6' */
  real32_T CastToSingle_b[9];          /* '<S6>/Cast To Single' */
  real32_T Selector[2];                /* '<S6>/Selector' */
  uint16_T DataTypeConversion2;        /* '<S29>/Data Type Conversion2' */
  uint16_T BitwiseOperator;            /* '<S27>/Bitwise Operator' */
  uint16_T BitwiseOperator1;           /* '<S27>/Bitwise Operator1' */
  uint16_T ShiftArithmetic1;           /* '<S27>/Shift Arithmetic1' */
  uint16_T IsenA;                      /* '<S5>/IsenA' */
  uint16_T Vdc;                        /* '<S5>/Vdc' */
  uint16_T Output;                     /* '<S19>/Output' */
  uint16_T DataStoreRead_j;            /* '<S6>/Data Store Read' */
  uint16_T MultiportSwitch[2];         /* '<S6>/Multiport Switch' */
  uint16_T FixPtSum1;                  /* '<S23>/FixPt Sum1' */
  uint16_T FixPtSwitch;                /* '<S24>/FixPt Switch' */
  uint16_T IsenB;                      /* '<S5>/IsenB' */
  uint16_T IsenC;                      /* '<S5>/IsenC' */
  uint16_T VsenA;                      /* '<S5>/VsenA' */
  uint16_T VsenB;                      /* '<S5>/VsenB' */
  int16_T WhileIterator;               /* '<S17>/While Iterator' */
  boolean_T PWM_En;                    /* '<S3>/Enable1' */
  boolean_T DataTypeConversion3_f;     /* '<S27>/Data Type Conversion3' */
  boolean_T PWM_En_g;                  /* '<S2>/Enable1' */
  B_MATLABFunction1_BasePerTrac_T sf_MATLABFunction2;/* '<S2>/MATLAB Function2' */
  B_MATLABFunction1_BasePerTrac_T sf_MATLABFunction1_n;/* '<S2>/MATLAB Function1' */
} B_BasePerTracing_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T IaOffset;                     /* '<Root>/Data Store Memory1' */
  real_T IbOffset;                     /* '<Root>/Data Store Memory2' */
  real_T Sum_DWORK1;                   /* '<S5>/Sum' */
  real_T CounterPrec;                  /* '<S7>/MATLAB Function1' */
  real_T OutPrecedente;                /* '<S7>/MATLAB Function' */
  real_T OutPrecedente_k;              /* '<S5>/MATLAB Function' */
  real32_T SpeedRef;                   /* '<Root>/Data Store Memory4' */
  real32_T Add1_DWORK1;                /* '<S10>/Add1' */
  int32_T DigitalOutput_FRAC_LEN;      /* '<S3>/Digital Output' */
  int32_T DigitalOutput1_FRAC_LEN;     /* '<S3>/Digital Output1' */
  int32_T ENABLE_FRAC_LEN;             /* '<S3>/ENABLE' */
  int32_T ENABLE1_FRAC_LEN;            /* '<S2>/ENABLE1' */
  uint32_T Add_DWORK1;                 /* '<S17>/Add' */
  uint16_T Output_DSTATE;              /* '<S19>/Output' */
  uint16_T Debug_signals;              /* '<Root>/Data Store Memory6' */
  boolean_T EnClosedLoop;              /* '<Root>/Data Store Memory3' */
  boolean_T Enable;                    /* '<Root>/Data Store Memory29' */
  DW_MATLABFunction1_BasePerTra_T sf_MATLABFunction2;/* '<S2>/MATLAB Function2' */
  DW_MATLABFunction1_BasePerTra_T sf_MATLABFunction1_n;/* '<S2>/MATLAB Function1' */
} DW_BasePerTracing_T;

/* Invariant block signals (default storage) */
typedef struct {
  const uint32_T Width;                /* '<S16>/Width' */
  const real32_T CastToSingle7;        /* '<S6>/Cast To Single7' */
  const real32_T CastToSingle8;        /* '<S6>/Cast To Single8' */
  const real32_T CastToSingle9;        /* '<S6>/Cast To Single9' */
} ConstB_BasePerTracing_T;

/* Real-time Model Data Structure */
struct tag_RTM_BasePerTracing_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_BasePerTracing_T BasePerTracing_B;

/* Block states (default storage) */
extern DW_BasePerTracing_T BasePerTracing_DW;
extern const ConstB_BasePerTracing_T BasePerTracing_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void BasePerTracing_initialize(void);
extern void BasePerTracing_step(void);
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
 * '<S4>'   : 'BasePerTracing/Serial Receive'
 * '<S5>'   : 'BasePerTracing/Current Control/AnalogReading'
 * '<S6>'   : 'BasePerTracing/Current Control/Debug_signals'
 * '<S7>'   : 'BasePerTracing/Current Control/ENCODER'
 * '<S8>'   : 'BasePerTracing/Current Control/MATLAB Function1'
 * '<S9>'   : 'BasePerTracing/Current Control/MATLAB Function2'
 * '<S10>'  : 'BasePerTracing/Current Control/PWM'
 * '<S11>'  : 'BasePerTracing/Current Control/SCI (Code Generation)'
 * '<S12>'  : 'BasePerTracing/Current Control/AnalogReading/MATLAB Function'
 * '<S13>'  : 'BasePerTracing/Current Control/ENCODER/MATLAB Function'
 * '<S14>'  : 'BasePerTracing/Current Control/ENCODER/MATLAB Function1'
 * '<S15>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Conditioning_Tx'
 * '<S16>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging'
 * '<S17>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/While Iterator Subsystem'
 * '<S18>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Conditioning_Tx/Data_Type_Float'
 * '<S19>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Counter Limited'
 * '<S20>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Data'
 * '<S21>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/End'
 * '<S22>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Start'
 * '<S23>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Counter Limited/Increment Real World'
 * '<S24>'  : 'BasePerTracing/Current Control/SCI (Code Generation)/Data_Logging/Counter Limited/Wrap To Zero'
 * '<S25>'  : 'BasePerTracing/Serial Receive/Code Generation'
 * '<S26>'  : 'BasePerTracing/Serial Receive/Data_Conditioning_Rx'
 * '<S27>'  : 'BasePerTracing/Serial Receive/unParse'
 * '<S28>'  : 'BasePerTracing/Serial Receive/Code Generation/Data_Type_Float'
 * '<S29>'  : 'BasePerTracing/Serial Receive/Data_Conditioning_Rx/Data_Type_Float'
 */
#endif                                 /* BasePerTracing_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
