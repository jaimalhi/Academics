	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%4d %4d %4d %4d"
	.text
	.p2align 4
	.globl	printMatrixByRow
	.type	printMatrixByRow, @function
printMatrixByRow:
.LFB24:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	jle	.L6
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	leaq	.LC0(%rip), %r14
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movslq	%esi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	.p2align 4,,10
	.p2align 3
.L3:
	movsbl	1(%rbx), %ecx
	movsbl	(%rbx), %edx
	movq	%r14, %rsi
	movl	$1, %edi
	movsbl	3(%rbx), %r9d
	movsbl	2(%rbx), %r8d
	xorl	%eax, %eax
	addl	$1, %ebp
	addq	%r13, %rbx
	call	__printf_chk@PLT
	movl	$10, %edi
	call	putchar@PLT
	cmpl	%ebp, %r12d
	jne	.L3
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 40
	movl	$10, %edi
	popq	%rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_restore 12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_restore 13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_restore 14
	.cfi_def_cfa_offset 8
	jmp	putchar@PLT
	.p2align 4,,10
	.p2align 3
.L6:
	movl	$10, %edi
	jmp	putchar@PLT
	.cfi_endproc
.LFE24:
	.size	printMatrixByRow, .-printMatrixByRow
	.section	.rodata.str1.1
.LC1:
	.string	"Matrix A: "
.LC2:
	.string	"Copy A to C"
.LC3:
	.string	"\nMatrix C: "
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC4:
	.string	"Rotating the matrix C by 90 degrees clockwise: "
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	$4, %esi
	leaq	A(%rip), %rdi
	call	printMatrixByRow
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movl	$4, %edx
	leaq	C(%rip), %rsi
	leaq	A(%rip), %rdi
	call	copy@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	$4, %esi
	leaq	C(%rip), %rdi
	call	printMatrixByRow
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	leaq	C(%rip), %rdx
	xorl	%r8d, %r8d
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L11:
	movq	%r8, %rax
	.p2align 4,,10
	.p2align 3
.L12:
	movzbl	(%rdx,%rax), %esi
	movzbl	(%rcx,%rax,4), %edi
	movb	%dil, (%rdx,%rax)
	movb	%sil, (%rcx,%rax,4)
	addq	$1, %rax
	cmpl	$4, %eax
	jne	.L12
	addq	$1, %r8
	addq	$4, %rdx
	addq	$1, %rcx
	cmpq	$4, %r8
	jne	.L11
	movzbl	C(%rip), %eax
	movzbl	3+C(%rip), %edx
	rolw	$8, 1+C(%rip)
	movl	$4, %esi
	rolw	$8, 5+C(%rip)
	leaq	C(%rip), %rdi
	movb	%dl, C(%rip)
	movzbl	7+C(%rip), %edx
	movb	%al, 3+C(%rip)
	movzbl	4+C(%rip), %eax
	movb	%dl, 4+C(%rip)
	movzbl	11+C(%rip), %edx
	movb	%al, 7+C(%rip)
	movzbl	8+C(%rip), %eax
	movb	%dl, 8+C(%rip)
	movzbl	15+C(%rip), %edx
	movb	%al, 11+C(%rip)
	movzbl	12+C(%rip), %eax
	rolw	$8, 9+C(%rip)
	movb	%dl, 12+C(%rip)
	movb	%al, 15+C(%rip)
	rolw	$8, 13+C(%rip)
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	printMatrixByRow
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.text
	.p2align 4
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB25:
	.cfi_startproc
	endbr64
	testl	%esi, %esi
	jle	.L23
	movslq	%esi, %r9
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %r11
	movq	%rdi, %rcx
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	leaq	1(%r9), %rbp
	leal	-1(%rsi), %ebx
	xorl	%r10d, %r10d
	.p2align 4,,10
	.p2align 3
.L19:
	movq	%r11, %rdx
	movq	%r10, %rax
	.p2align 4,,10
	.p2align 3
.L18:
	movzbl	(%rdx), %r8d
	movzbl	(%rcx,%rax), %edi
	movb	%r8b, (%rcx,%rax)
	addq	$1, %rax
	movb	%dil, (%rdx)
	addq	%r9, %rdx
	cmpl	%eax, %esi
	jg	.L18
	leaq	1(%r10), %rax
	addq	%rbp, %r11
	addq	%r9, %rcx
	cmpq	%rbx, %r10
	je	.L26
	movq	%rax, %r10
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L26:
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L23:
	.cfi_restore 3
	.cfi_restore 6
	ret
	.cfi_endproc
.LFE25:
	.size	transpose, .-transpose
	.p2align 4
	.globl	reverseColumns
	.type	reverseColumns, @function
reverseColumns:
.LFB26:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	%esi, %ebx
	shrl	$31, %ebx
	addl	%esi, %ebx
	sarl	%ebx
	cmpl	$1, %esi
	jle	.L27
	movq	%rdi, %rbp
	xorl	%r11d, %r11d
	leal	-1(%rsi), %r12d
	movslq	%esi, %rdi
	.p2align 4,,10
	.p2align 3
.L28:
	movl	%r12d, %r8d
	leaq	0(%rbp,%r11), %rax
	xorl	%edx, %edx
	subl	%r11d, %r8d
	movslq	%r8d, %r8
	.p2align 4,,10
	.p2align 3
.L30:
	movq	%rax, %rcx
	movzbl	(%rax), %r9d
	addl	$1, %edx
	subq	%r11, %rcx
	movzbl	(%rcx,%r8), %r10d
	movb	%r10b, (%rax)
	addq	%rdi, %rax
	movb	%r9b, (%rcx,%r8)
	cmpl	%edx, %esi
	jne	.L30
	addq	$1, %r11
	cmpl	%r11d, %ebx
	jg	.L28
.L27:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	reverseColumns, .-reverseColumns
	.comm	C,16,16
	.globl	A
	.data
	.align 16
	.type	A, @object
	.size	A, 16
A:
	.ascii	"\001\376\003\374"
	.ascii	"\373\006\371\b"
	.ascii	"\377\002\375\004"
	.ascii	"\005\372\007\370"
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
