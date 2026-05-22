#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "rtwtypes.h"
#include "BasePerTracing.h"
#include "BasePerTracing_private.h"

void config_ADCC_SOC0(void)
{
  EALLOW;
  AdccRegs.ADCSOC0CTL.bit.CHSEL = 4U;  /* Set SOC0 channel select to ADCIN4*/
  AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 11U;
  AdccRegs.ADCSOC0CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC0 S/H Window to 15.0 ADC Clock Cycles*/
  AdccRegs.ADCINTSOCSEL1.bit.SOC0 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdccRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdccRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correction Value*/
  AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
             /* Interrupt pulse generation occurs at the end of the conversion*/
  AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADCB_SOC0(void)
{
  EALLOW;
  AdcbRegs.ADCSOC0CTL.bit.CHSEL = 4U;  /* Set SOC0 channel select to ADCIN4*/
  AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 11U;
  AdcbRegs.ADCSOC0CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC0 S/H Window to 15.0 ADC Clock Cycles*/
  AdcbRegs.ADCINTSOCSEL1.bit.SOC0 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdcbRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcbRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correction Value*/
  AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
             /* Interrupt pulse generation occurs at the end of the conversion*/
  AdcbRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADCA_SOC0(void)
{
  EALLOW;
  AdcaRegs.ADCSOC0CTL.bit.CHSEL = 4U;  /* Set SOC0 channel select to ADCIN4*/
  AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 11U;
  AdcaRegs.ADCSOC0CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC0 S/H Window to 15.0 ADC Clock Cycles*/
  AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcaRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correction Value*/
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
             /* Interrupt pulse generation occurs at the end of the conversion*/
  AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADCA_SOC1(void)
{
  EALLOW;
  AdcaRegs.ADCSOC1CTL.bit.CHSEL = 5U;  /* Set SOC1 channel select to ADCIN5*/
  AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 11U;
  AdcaRegs.ADCSOC1CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC1 S/H Window to 15.0 ADC Clock Cycles*/
  AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1U;/* Enabled/Disable ADCINT1 interrupt*/
  AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 1U;/* Setup EOC1 to trigger ADCINT1*/
  AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1U;
                                     /* Enable/Disable ADCINT1 Continuous mode*/
  AdcaRegs.ADCINTSOCSEL1.bit.SOC1 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcaRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correction Value*/
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
             /* Interrupt pulse generation occurs at the end of the conversion*/
  AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADCA_SOC2(void)
{
  EALLOW;
  AdcaRegs.ADCSOC2CTL.bit.CHSEL = 15U; /* Set SOC2 channel select to ADCIN15*/
  AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 11U;
  AdcaRegs.ADCSOC2CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC2 S/H Window to 15.0 ADC Clock Cycles*/
  AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1U;/* Enabled/Disable ADCINT2 interrupt*/
  AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 2U;/* Setup EOC2 to trigger ADCINT2*/
  AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 1U;
                                     /* Enable/Disable ADCINT2 Continuous mode*/
  AdcaRegs.ADCINTSOCSEL1.bit.SOC2 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdcaRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdcaRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correction Value*/
  AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
             /* Interrupt pulse generation occurs at the end of the conversion*/
  AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void config_ADCC_SOC3(void)
{
  EALLOW;
  AdccRegs.ADCSOC3CTL.bit.CHSEL = 5U;  /* Set SOC3 channel select to ADCIN5*/
  AdccRegs.ADCSOC3CTL.bit.TRIGSEL = 11U;
  AdccRegs.ADCSOC3CTL.bit.ACQPS = (uint16_T)14.0;
                               /* Set SOC3 S/H Window to 15.0 ADC Clock Cycles*/
  AdccRegs.ADCINTSEL3N4.bit.INT3E = 1U;/* Enabled/Disable ADCINT3 interrupt*/
  AdccRegs.ADCINTSEL3N4.bit.INT3SEL = 3U;/* Setup EOC3 to trigger ADCINT3*/
  AdccRegs.ADCINTSEL3N4.bit.INT3CONT = 1U;
                                     /* Enable/Disable ADCINT3 Continuous mode*/
  AdccRegs.ADCINTSOCSEL1.bit.SOC3 = 0U;
                                   /* SOCx No ADCINT Interrupt Trigger Select.*/
  AdccRegs.ADCOFFTRIM.bit.OFFTRIM = (uint16_T)AdccRegs.ADCOFFTRIM.bit.OFFTRIM;/* Set Offset Error Correction Value*/
  AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1U;
             /* Interrupt pulse generation occurs at the end of the conversion*/
  AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0U;/* All in round robin mode SOC Priority*/
  EDIS;
}

void InitAdcA(void)
{
  EALLOW;
  CpuSysRegs.PCLKCR13.bit.ADC_A = 1U;
  AdcaRegs.ADCCTL2.bit.PRESCALE = 8U;
  AdcSetMode((uint16_T)ADC_ADCA, (uint16_T)ADC_RESOLUTION_12BIT,(uint16_T)
             ADC_SIGNALMODE_SINGLE);

  //power up the ADC
  AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1U;

  //delay for 1ms to allow ADC time to power up
  DELAY_US(1000);
  EDIS;
}

void InitAdcB(void)
{
  EALLOW;
  CpuSysRegs.PCLKCR13.bit.ADC_B = 1U;
  AdcbRegs.ADCCTL2.bit.PRESCALE = 8U;
  AdcSetMode((uint16_T)ADC_ADCB, (uint16_T)ADC_RESOLUTION_12BIT,(uint16_T)
             ADC_SIGNALMODE_SINGLE);

  //power up the ADC
  AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1U;

  //delay for 1ms to allow ADC time to power up
  DELAY_US(1000);
  EDIS;
}

void InitAdcC(void)
{
  EALLOW;
  CpuSysRegs.PCLKCR13.bit.ADC_C = 1U;
  AdccRegs.ADCCTL2.bit.PRESCALE = 8U;
  AdcSetMode((uint16_T)ADC_ADCC, (uint16_T)ADC_RESOLUTION_12BIT,(uint16_T)
             ADC_SIGNALMODE_SINGLE);

  //power up the ADC
  AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1U;

  //delay for 1ms to allow ADC time to power up
  DELAY_US(1000);
  EDIS;
}
