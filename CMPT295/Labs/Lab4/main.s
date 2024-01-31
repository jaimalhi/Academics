	.file	"main.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Original values are: x=%d, y=%d.\n"`
	.align 8
.LC1:
	.string	"Final values are: x=%d, y=%d.\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$9, %ecx
	movl	$6, %edx
	movl	$1, %edi
	leaq	.LC0(%rip), %rsi
	subq	$64, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	leaq	16(%rsp), %rbp
	movl	$6, 8(%rsp)
	movl	$9, 12(%rsp)
	call	__printf_chk@PLT
	leaq	12(%rsp), %rdx
	leaq	8(%rsp), %rsi
	movq	%rbp, %rdi
	call	proc1@PLT # Here
	movl	12(%rsp), %ecx
	movl	8(%rsp), %edx
	xorl	%eax, %eax
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	call	__printf_chk@PLT
	movq	%rbp, %rdi
	call	puts@PLT
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L5
	addq	$64, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
