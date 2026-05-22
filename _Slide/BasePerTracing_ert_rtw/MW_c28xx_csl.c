#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "rtwtypes.h"
#include "BasePerTracing.h"
#include "BasePerTracing_private.h"

void enableExtInterrupt (void);
void configureGPIOExtInterrupt(void);

#include <stdint.h>

void disableWatchdog(void)
{
  int *WatchdogWDCR = (int *)(uintptr_t)0x7029;
  asm(" EALLOW ");
  *WatchdogWDCR = 0x0068;
  asm(" EDIS ");
}

interrupt void ADCA1_INT_isr(void)
{
  volatile unsigned int PIEIER1_stack_save = PieCtrlRegs.PIEIER1.all;
  volatile unsigned int PIEIER9_stack_save = PieCtrlRegs.PIEIER9.all;
  PieCtrlRegs.PIEIER1.all &= ~65;
                              /*disable group1 lower/equal priority interrupts*/
  PieCtrlRegs.PIEIER9.all &= ~1;
                              /*disable group9 lower/equal priority interrupts*/
  asm(" RPT #5 || NOP");               /*wait 5 cycles        */
  IFR &= ~257;    /*eventually disable lower/equal priority pending interrupts*/
  PieCtrlRegs.PIEACK.all = 257;
                   /*ACK to allow other interrupts from the same group to fire*/
  IER |= 1;
  EINT;                                /*global interrupt enable*/
  isr_int1pie1_task_fcn();
  DINT;
  /* disable global interrupts during context switch, CPU will enable global interrupts after exiting ISR    */
  PieCtrlRegs.PIEIER1.all = PIEIER1_stack_save;
                                   /*restore PIEIER register that was modified*/
  PieCtrlRegs.PIEIER9.all = PIEIER9_stack_save;
                                   /*restore PIEIER register that was modified*/
  EALLOW;
  AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
  EDIS;
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
                                     /* Acknowledge to receive more interrupts*/
}

interrupt void SCIA_RX_INT_isr(void)
{
  isr_int9pie1_task_fcn();
  EALLOW;
  SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
  EDIS;
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
                                     /* Acknowledge to receive more interrupts*/
}

void enable_interrupts()
{
  EALLOW;
  PieVectTable.ADCA1_INT = &ADCA1_INT_isr;/* Hook interrupt to the ISR*/
  EDIS;
  PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   /* Enable interrupt ADCA1_INT*/
  IER |= M_INT1;
  EALLOW;
  PieVectTable.SCIA_RX_INT = &SCIA_RX_INT_isr;/* Hook interrupt to the ISR*/
  EDIS;
  PieCtrlRegs.PIEIER9.bit.INTx1 = 1;   /* Enable interrupt SCIA_RX_INT*/
  IER |= M_INT9;

  /* Enable global Interrupts and higher priority real-time debug events:*/
  EINT;                                /* Enable Global interrupt INTM*/
  ERTM;                               /* Enable Global realtime interrupt DBGM*/
}

void init_SCI(void)
{
  /* initialize SCI & FIFO registers */
  EALLOW;

  /*
   * Initialize SCI_A with following parameters:
   *    BaudRate              : 12500000
   *    CharacterLengthBits   : 8
   *    EnableLoopBack        : 0
   *    NumberOfStopBits      : 1
   *    ParityMode            : None
   *    SuspensionMode        : Free_run
   */
  CpuSysRegs.PCLKCR7.bit.SCI_A = 1U;
  asm(" NOP");
  SciaRegs.SCICCR.bit.STOPBITS = 0U;
                    /*Number of stop bits. (0: One stop bit, 1: Two stop bits)*/
  SciaRegs.SCICCR.bit.PARITY = 0U;
                                 /*Parity mode (0: Odd parity, 1: Even parity)*/
  SciaRegs.SCICCR.bit.PARITYENA = 0U;  /*Enable Pary Mode */
  SciaRegs.SCICCR.bit.LOOPBKENA = 0U;  /*Loop Back enable*/
  SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0U;/*ADDR/IDLE Mode control*/
  SciaRegs.SCICCR.bit.SCICHAR = 7U;    /*Character length*/
  SciaRegs.SCICTL1.bit.RXERRINTENA = 0U;/*Disable receive error interrupt*/
  SciaRegs.SCICTL1.bit.SWRESET = 1U;   /*Software reset*/
  SciaRegs.SCICTL1.bit.TXENA = 1U;     /* SCI transmitter enable*/
  SciaRegs.SCICTL1.bit.RXENA = 1U;     /* SCI receiver enable*/
  SciaRegs.SCIHBAUD.bit.BAUD = 0U;
  SciaRegs.SCILBAUD.bit.BAUD = 1U;

  /*Free run, continue SCI operation regardless of suspend*/
  SciaRegs.SCIPRI.bit.FREESOFT = 3U;
  SciaRegs.SCIFFCT.bit.ABDCLR = 0U;
  SciaRegs.SCIFFCT.bit.CDC = 0U;
  SciaRegs.SCIFFTX.bit.SCIRST = 1U;    /* SCI reset rx/tx channels*/
  SciaRegs.SCIFFTX.bit.SCIFFENA = 1U;  /* SCI FIFO enhancements are enabled.*/
  SciaRegs.SCIFFTX.bit.TXFIFORESET = 1U;/* Re-enable transmit FIFO operation.*/
  SciaRegs.SCIFFRX.bit.RXFIFORESET = 1U;/* Re-enable receive FIFO operation.*/
  SciaRegs.SCIFFRX.bit.RXFFIENA = 1U;
  SciaRegs.SCIFFRX.bit.RXFFIL = 4U;
  SciaRegs.SCICTL1.bit.RXERRINTENA = 1U;
  /*Enable receive error interrupt by default if receive FIFO interrupt is enabled*/
  EDIS;
}

void init_SCI_GPIO(void)
{
  EALLOW;
  GpioCtrlRegs.GPBQSEL1.bit.GPIO43 = 3U;/*Asynch input GPIO43 SCIRXDA*/
  GpioCtrlRegs.GPBPUD.bit.GPIO43 = 0U; /*Enable pull-up for GPIO43*/
  GpioCtrlRegs.GPBGMUX1.bit.GPIO43 = 3U;
  GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3U;/*Configure GPIO43 as SCIRXDA*/
  GpioCtrlRegs.GPBPUD.bit.GPIO42 = 0U; /*Enable pull-up for GPIO42*/
  GpioCtrlRegs.GPBGMUX1.bit.GPIO42 = 3U;
  GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3U;/*Configure GPIO42 as SCITXDA*/
  EDIS;
}
