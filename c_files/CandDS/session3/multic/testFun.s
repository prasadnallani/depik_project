	.file	"testFun.c"
	.text
.globl avearge
	.type	avearge, @function
avearge:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	movl	%eax, %ecx
	addl	16(%ebp), %ecx
	movl	$1431655766, %eax
	imull	%ecx
	sarl	$31, %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	avearge, .-avearge
	.section	.rodata
.LC0:
	.string	"%d"
	.text
.globl TestFunc
	.type	TestFunc, @function
TestFunc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$20, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	subl	$4, %esp
	pushl	-12(%ebp)
	pushl	-8(%ebp)
	pushl	-4(%ebp)
	call	average
	addl	$16, %esp
	movl	%eax, sum
	subl	$8, %esp
	pushl	sum
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	leave
	ret
	.size	TestFunc, .-TestFunc
	.comm	sum,4,4
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.2 20031022 (Red Hat Linux 3.3.2-1)"
