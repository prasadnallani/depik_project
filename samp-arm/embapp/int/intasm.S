
#include "board.h"

.text

.global vectors_start
.global vectors_end
	
vectors_start:

	ldr	pc, PREABRT
	ldr	pc, SOFT_INT
	ldr	pc, PREABRT
	ldr	pc, DATABRT
	ldr	pc, DPBOOT
	ldr	pc, IRQ
	ldr	pc, FIQ

SOFT_INT:	.word  vector_IRQ	
DATABRT:	.word  vector_IRQ	
PREABRT:	.word  vector_IRQ	
DPBOOT:		.word  vector_IRQ	
IRQ:		.word  vector_IRQ	
FIQ:		.word  vector_IRQ	

vectors_end:


vector_IRQ:	
  	SUB  	lr,lr,#4
  	stmfd   sp!, {r0-r12,r14}
  	bl      cmnIrqHandler
	ldmfd	sp!, {r0-r12,pc}^


.globl enableInt

enableInt:
        mrs r12, cpsr
        bic r12, r12, #0xC0
        msr cpsr, r12
        mov pc, lr
          

.globl disableInt
disableInt:
        mrs r12, cpsr
        orr r12, r12, #0xC0
        msr cpsr, r12
        mov pc, lr  

.globl getcpsr 
getcpsr:
        mrs r0, cpsr
        mov pc, lr  

