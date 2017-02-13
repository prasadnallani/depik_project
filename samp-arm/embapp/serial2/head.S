
#include "board.h"

.section ".text"
.global   start
start:
 
	ldr	sp, =0x200000
	mrs     r1, cpsr          /* save cpsr in r1 */
	ldr	r2, =0xd2
        msr     cpsr, r2          /* set to irq mode */
	ldr	sp, =0x300000
        msr     cpsr, r1          /* Go back original mode the svc mode */
	bl	app_main
	swi


