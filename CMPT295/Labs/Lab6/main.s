	.file	"main.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"It took %ld microseconds to initialize the array with quicksort2.\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%edi, %edi
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	leaq	4+A(%rip), %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	leaq	-4(%r13), %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movl	$1, %ebx
	subq	$304, %rsp
	.cfi_def_cfa_offset 352
	movq	%fs:40, %rax
	movq	%rax, 296(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rbp
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movq	%rbp, %rsi
	xorl	%edi, %edi
	call	getrusage@PLT
	movl	$0, A(%rip)
	.p2align 4,,10
	.p2align 3
.L2:
	movl	%ebx, %eax
	addl	$1, %ebx
	addq	$4, %r13
	imulq	$1374389535, %rax, %rax
	shrq	$37, %rax
	movl	%eax, -4(%r13)
	call	rand@PLT
	movl	%eax, %r14d
	call	rand@PLT
	movslq	%r14d, %rdx
	imulq	$-2147418109, %rdx, %rdx
	movl	%eax, %ecx
	movl	%r14d, %eax
	sarl	$31, %eax
	shrq	$32, %rdx
	addl	%r14d, %edx
	sarl	$14, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$15, %eax
	subl	%edx, %eax
	movslq	%ecx, %rdx
	imulq	$-2147450879, %rdx, %rdx
	subl	%eax, %r14d
	movl	%ecx, %eax
	sarl	$31, %eax
	sall	$16, %r14d
	shrq	$32, %rdx
	addl	%ecx, %edx
	sarl	$15, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$16, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%r14d, %eax
	orl	%ecx, %eax
	cltd
	idivl	%ebx
	movl	-4(%r13), %eax
	movslq	%edx, %rdx
	movl	(%r12,%rdx,4), %ecx
	movl	%ecx, -4(%r13)
	movl	%eax, (%r12,%rdx,4)
	cmpl	$1000000, %ebx
	jne	.L2
	leaq	144(%rsp), %r13
	xorl	%edi, %edi
	movq	%r13, %rsi
	call	getrusage@PLT
	xorl	%edi, %edi
	movq	%rbp, %rsi
	call	getrusage@PLT
	movl	$1000000, %esi
	movq	%r12, %rdi
	call	qSort2@PLT
	xorl	%edi, %edi
	movq	%r13, %rsi
	call	getrusage@PLT
	movq	144(%rsp), %rdx
	subq	(%rsp), %rdx
	xorl	%eax, %eax
	imulq	$1000000, %rdx, %rdx
	leaq	.LC0(%rip), %rsi
	addq	152(%rsp), %rdx
	movl	$1, %edi
	subq	8(%rsp), %rdx
	call	__printf_chk@PLT
	movq	296(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L7
	addq	$304, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L7:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.globl	A
	.bss
	.align 32
	.type	A, @object
	.size	A, 4000000
A:
	.zero	4000000
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
