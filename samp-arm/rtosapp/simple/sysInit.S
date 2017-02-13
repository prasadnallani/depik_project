
.text
.global	sysInit
sysInit:
	ldr	sp, =0x400000	@locating stack pointer to 4MB
	bl	usrInit
        nop
        nop
	swi

.global	raiseSWI
raiseSWI:
	swi #2000

