
#include "board.h"

.section ".text"
.global   start
start:
 
	ldr	sp, =0x200000
	bl	app_main
	swi


