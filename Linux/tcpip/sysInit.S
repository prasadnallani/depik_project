	.file	"asmfun.c"
gcc2_compiled.:
___gnu_compiled_c:
.text

	.align 2
.globl sysInit
	.type	 sysInit,@function
sysInit:
        cli
        movl  $0, %ebp
	movl  $0x3ffff0, %esp
#ifdef WINDOWS
        movl  $_end, %eax
        movl  %eax, _bssEnd
        movl  $_edata, %eax
        movl  %eax, _bssStart
	call  _root
#else
        movl  $_end, %eax
        movl  %eax, bssEnd
        movl  $_edata, %eax
        movl  %eax, bssStart
	call  usrInit
#endif
        int   $3
L1:
	leave
	ret
Lfe1:
#ifdef WINDOWS
	.size	 _sysInit,Lfe1-_sysInit
#else
	.size	 sysInit,Lfe1-sysInit
#endif
	.align 2


