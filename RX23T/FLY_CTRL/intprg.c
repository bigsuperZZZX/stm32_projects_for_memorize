/************************************************************************
*
* Device     : RX/RX200/RX23T
*
* File Name  : intprg.c
*
* Abstract   : Interrupt Program.
*
* History    : 0.5  (2014-11-07)  [Hardware Manual Revision : 0.50]
*            : 1.0  (2015-04-23)  [Hardware Manual Revision : 1.00]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright(C) 2015 (2014) Renesas Electronics Corporation.
*
************************************************************************/
#include <machine.h>
#include "vect.h"

#pragma section IntPRG

// Exception(Supervisor Instruction)
void Excep_SuperVisorInst(void){/* brk(); */}

// Exception(Access Instruction)
void Excep_AccessInst(void){/* brk(); */}

// Exception(Undefined Instruction)
void Excep_UndefinedInst(void){/* brk(); */}

// Exception(Floating Point)
void Excep_FloatingPoint(void){/* brk(); */}

// NMI
void NonMaskableInterrupt(void){/* brk(); */}

// Dummy
void Dummy(void){/* brk(); */}

// BRK
void Excep_BRK(void){ wait(); }

// BSC BUSERR
void Excep_BSC_BUSERR(void){/* brk(); */}

// FCU FRDYI
void Excep_FCU_FRDYI(void){/* brk(); */}

// ICU SWINT
void Excep_ICU_SWINT(void){/* brk(); */}

// CMT0 CMI0
void Excep_CMT0_CMI0(void){/* brk(); */}

// CMT1 CMI1
void Excep_CMT1_CMI1(void){/* brk(); */}

// CMT2 CMI2
void Excep_CMT2_CMI2(void){/* brk(); */}

// CMT3 CMI3
void Excep_CMT3_CMI3(void){/* brk(); */}

// CAC FERRF
void Excep_CAC_FERRF(void){/* brk(); */}

// CAC MENDF
void Excep_CAC_MENDF(void){/* brk(); */}

// CAC OVFF
void Excep_CAC_OVFF(void){/* brk(); */}

// RSPI0 SPEI0
void Excep_RSPI0_SPEI0(void){/* brk(); */}

// RSPI0 SPRI0
void Excep_RSPI0_SPRI0(void){/* brk(); */}

// RSPI0 SPTI0
void Excep_RSPI0_SPTI0(void){/* brk(); */}

// RSPI0 SPII0
void Excep_RSPI0_SPII0(void){/* brk(); */}

// DOC DOPCF
void Excep_DOC_DOPCF(void){/* brk(); */}

// ICU IRQ0
void Excep_ICU_IRQ0(void){/* brk(); */}

// ICU IRQ1
void Excep_ICU_IRQ1(void){/* brk(); */}

// ICU IRQ2
void Excep_ICU_IRQ2(void){/* brk(); */}

// ICU IRQ3
void Excep_ICU_IRQ3(void){/* brk(); */}

// ICU IRQ4
void Excep_ICU_IRQ4(void){/* brk(); */}

// ICU IRQ5
void Excep_ICU_IRQ5(void){/* brk(); */}

// LVD LVD1
void Excep_LVD_LVD1(void){/* brk(); */}

// LVD LVD2
void Excep_LVD_LVD2(void){/* brk(); */}

// S12AD S12ADI
void Excep_S12AD_S12ADI(void){/* brk(); */}

// S12AD GBADI
void Excep_S12AD_GBADI(void){/* brk(); */}

// CMPC0 CMPC0
void Excep_CMPC0_CMPC0(void){/* brk(); */}

// CMPC1 CMPC1
void Excep_CMPC1_CMPC1(void){/* brk(); */}

// CMPC2 CMPC2
void Excep_CMPC2_CMPC2(void){/* brk(); */}

// MTU0 TGIA0
void Excep_MTU0_TGIA0(void){/* brk(); */}

// MTU0 TGIB0
void Excep_MTU0_TGIB0(void){/* brk(); */}

// MTU0 TGIC0
void Excep_MTU0_TGIC0(void){/* brk(); */}

// MTU0 TGID0
void Excep_MTU0_TGID0(void){/* brk(); */}

// MTU0 TCIV0
void Excep_MTU0_TCIV0(void){/* brk(); */}

// MTU0 TGIE0
void Excep_MTU0_TGIE0(void){/* brk(); */}

// MTU0 TGIF0
void Excep_MTU0_TGIF0(void){/* brk(); */}

// MTU1 TGIA1
void Excep_MTU1_TGIA1(void){/* brk(); */}

// MTU1 TGIB1
void Excep_MTU1_TGIB1(void){/* brk(); */}

// MTU1 TCIV1
void Excep_MTU1_TCIV1(void){/* brk(); */}

// MTU1 TCIU1
void Excep_MTU1_TCIU1(void){/* brk(); */}

// MTU2 TGIA2
void Excep_MTU2_TGIA2(void){/* brk(); */}

// MTU2 TGIB2
void Excep_MTU2_TGIB2(void){/* brk(); */}

// MTU2 TCIV2
void Excep_MTU2_TCIV2(void){/* brk(); */}

// MTU2 TCIU2
void Excep_MTU2_TCIU2(void){/* brk(); */}

// MTU3 TGIA3
void Excep_MTU3_TGIA3(void){/* brk(); */}

// MTU3 TGIB3
void Excep_MTU3_TGIB3(void){/* brk(); */}

// MTU3 TGIC3
void Excep_MTU3_TGIC3(void){/* brk(); */}

// MTU3 TGID3
void Excep_MTU3_TGID3(void){/* brk(); */}

// MTU3 TCIV3
void Excep_MTU3_TCIV3(void){/* brk(); */}

// MTU4 TGIA4
void Excep_MTU4_TGIA4(void){/* brk(); */}

// MTU4 TGIB4
void Excep_MTU4_TGIB4(void){/* brk(); */}

// MTU4 TGIC4
void Excep_MTU4_TGIC4(void){/* brk(); */}

// MTU4 TGID4
void Excep_MTU4_TGID4(void){/* brk(); */}

// MTU4 TCIV4
void Excep_MTU4_TCIV4(void){/* brk(); */}

// MTU5 TGIU5
void Excep_MTU5_TGIU5(void){/* brk(); */}

// MTU5 TGIV5
void Excep_MTU5_TGIV5(void){/* brk(); */}

// MTU5 TGIW5
void Excep_MTU5_TGIW5(void){/* brk(); */}

// POE OEI1
void Excep_POE_OEI1(void){/* brk(); */}

// POE OEI3
void Excep_POE_OEI3(void){/* brk(); */}

// POE OEI4
void Excep_POE_OEI4(void){/* brk(); */}

// TMR0 CMIA0
void Excep_TMR0_CMIA0(void){/* brk(); */}

// TMR0 CMIB0
void Excep_TMR0_CMIB0(void){/* brk(); */}

// TMR0 OVI0
void Excep_TMR0_OVI0(void){/* brk(); */}

// TMR1 CMIA1
void Excep_TMR1_CMIA1(void){/* brk(); */}

// TMR1 CMIB1
void Excep_TMR1_CMIB1(void){/* brk(); */}

// TMR1 OVI1
void Excep_TMR1_OVI1(void){/* brk(); */}

// TMR2 CMIA2
void Excep_TMR2_CMIA2(void){/* brk(); */}

// TMR2 CMIB2
void Excep_TMR2_CMIB2(void){/* brk(); */}

// TMR2 OVI2
void Excep_TMR2_OVI2(void){/* brk(); */}

// TMR3 CMIA3
void Excep_TMR3_CMIA3(void){/* brk(); */}

// TMR3 CMIB3
void Excep_TMR3_CMIB3(void){/* brk(); */}

// TMR3 OVI3
void Excep_TMR3_OVI3(void){/* brk(); */}

// SCI1 ERI1
void Excep_SCI1_ERI1(void){/* brk(); */}

// SCI1 RXI1
void Excep_SCI1_RXI1(void){/* brk(); */}

// SCI1 TXI1
void Excep_SCI1_TXI1(void){/* brk(); */}

// SCI1 TEI1
void Excep_SCI1_TEI1(void){/* brk(); */}

// SCI5 ERI5
void Excep_SCI5_ERI5(void){/* brk(); */}

// SCI5 RXI5
void Excep_SCI5_RXI5(void){/* brk(); */}

// SCI5 TXI5
void Excep_SCI5_TXI5(void){/* brk(); */}

// SCI5 TEI5
void Excep_SCI5_TEI5(void){/* brk(); */}

// RIIC0 EEI0
void Excep_RIIC0_EEI0(void){/* brk(); */}

// RIIC0 RXI0
void Excep_RIIC0_RXI0(void){/* brk(); */}

// RIIC0 TXI0
void Excep_RIIC0_TXI0(void){/* brk(); */}

// RIIC0 TEI0
void Excep_RIIC0_TEI0(void){/* brk(); */}

