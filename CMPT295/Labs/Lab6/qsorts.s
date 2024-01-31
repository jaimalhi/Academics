	.file	"qsorts.c"
	.text
	.p2align 4
	.globl	qSort1
	.type	qSort1, @function
qSort1:
.LFB0:
	.cfi_startproc
	endbr64
	cmpl	$1, %esi
	jle	.L11
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
.L2:
	movl	(%rbx), %edi
	leal	-1(%r12), %esi
	movl	$-1, %ecx
	movslq	%esi, %rsi
	movl	%edi, %edx
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%rbx,%rsi,4), %r8d
	leal	1(%rsi), %ebp
	movl	%esi, %r13d
	cmpl	%r8d, %edi
	jl	.L4
	addl	$1, %ecx
	movslq	%ecx, %rax
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L15:
	movl	(%rbx,%rax,4), %edx
.L6:
	movl	%eax, %ecx
	addq	$1, %rax
	cmpl	%edx, %edi
	jg	.L15
	cmpl	%esi, %ecx
	jge	.L7
	movslq	%ecx, %rax
	movl	%r8d, (%rbx,%rax,4)
	movl	%edx, (%rbx,%rsi,4)
	movl	4(%rbx,%rax,4), %edx
.L4:
	subq	$1, %rsi
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L7:
	subl	%r13d, %r12d
	movl	%ebp, %esi
	movq	%rbx, %rdi
	movslq	%ebp, %rbp
	call	qSort1
	subl	$1, %r12d
	leaq	(%rbx,%rbp,4), %rbx
	cmpl	$1, %r12d
	jg	.L2
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	ret
	.cfi_endproc
.LFE0:
	.size	qSort1, .-qSort1
	.p2align 4
	.globl	swap
	.type	swap, @function
swap:
.LFB2:
	.cfi_startproc
	endbr64
	movl	(%rdi), %eax
	movl	(%rsi), %edx
	movl	%edx, (%rdi)
	movl	%eax, (%rsi)
	ret
	.cfi_endproc
.LFE2:
	.size	swap, .-swap
	.p2align 4
	.globl	partitionH
	.type	partitionH, @function
partitionH:
.LFB3:
	.cfi_startproc
	endbr64
	movl	%esi, %r8d
	movl	(%rdi), %esi
	movl	$-1, %ecx
	subl	$1, %r8d
	movslq	%r8d, %r8
	movl	%esi, %edx
	.p2align 4,,10
	.p2align 3
.L18:
	movl	(%rdi,%r8,4), %r9d
	movl	%r8d, %r10d
	cmpl	%esi, %r9d
	jg	.L19
	addl	$1, %ecx
	movslq	%ecx, %rax
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L23:
	movl	(%rdi,%rax,4), %edx
.L21:
	movl	%eax, %ecx
	addq	$1, %rax
	cmpl	%edx, %esi
	jg	.L23
	cmpl	%r8d, %ecx
	jge	.L17
	movslq	%ecx, %rax
	movl	%r9d, (%rdi,%rax,4)
	movl	%edx, (%rdi,%r8,4)
	movl	4(%rdi,%rax,4), %edx
.L19:
	subq	$1, %r8
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L17:
	movl	%r10d, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	partitionH, .-partitionH
	.p2align 4
	.globl	partitionL
	.type	partitionL, @function
partitionL:
.LFB4:
	.cfi_startproc
	endbr64
	leal	-1(%rsi), %eax
	movq	%rdi, %rcx
	movslq	%eax, %rdx
	leaq	(%rdi,%rdx,4), %r11
	movl	(%r11), %edi
	testl	%eax, %eax
	jle	.L28
	leal	-2(%rsi), %edx
	movq	%rcx, %rax
	xorl	%r8d, %r8d
	leaq	4(%rcx,%rdx,4), %r9
	.p2align 4,,10
	.p2align 3
.L27:
	movl	(%rax), %edx
	cmpl	%edi, %edx
	jg	.L26
	movslq	%r8d, %rsi
	addl	$1, %r8d
	leaq	(%rcx,%rsi,4), %rsi
	movl	(%rsi), %r10d
	movl	%edx, (%rsi)
	movl	%r10d, (%rax)
.L26:
	addq	$4, %rax
	cmpq	%r9, %rax
	jne	.L27
	movslq	%r8d, %rax
	movl	(%r11), %edi
	leaq	(%rcx,%rax,4), %rcx
	movl	(%rcx), %eax
	movl	%edi, (%rcx)
	movl	%eax, (%r11)
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L28:
	movl	(%rcx), %eax
	xorl	%r8d, %r8d
	movl	%edi, (%rcx)
	movl	%eax, (%r11)
	movl	%r8d, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	partitionL, .-partitionL
	.p2align 4
	.globl	qSort2
	.type	qSort2, @function
qSort2:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$120, %rsp
	.cfi_def_cfa_offset 176
	movq	%rdi, 56(%rsp)
	movl	%esi, 64(%rsp)
	cmpl	$1, %esi
	jle	.L30
.L31:
	movq	56(%rsp), %rbx
	movl	64(%rsp), %esi
	movq	%rbx, %rdi
	call	partitionL
	movl	%eax, 80(%rsp)
	cmpl	$1, %eax
	jle	.L32
	movq	%rbx, 24(%rsp)
	movl	%eax, 20(%rsp)
.L47:
	movq	24(%rsp), %rbx
	movl	20(%rsp), %esi
	movq	%rbx, %rdi
	call	partitionL
	movl	%eax, 84(%rsp)
	cmpl	$1, %eax
	jle	.L33
	movq	%rbx, 32(%rsp)
	movl	%eax, 40(%rsp)
.L46:
	movq	32(%rsp), %rbx
	movl	40(%rsp), %esi
	movq	%rbx, %rdi
	call	partitionL
	movl	%eax, 88(%rsp)
	cmpl	$1, %eax
	jle	.L34
	movq	%rbx, 48(%rsp)
	movl	%eax, 44(%rsp)
.L45:
	movq	48(%rsp), %r15
	movl	44(%rsp), %esi
	movq	%r15, %rdi
	call	partitionL
	movl	%eax, 92(%rsp)
	movl	%eax, %r13d
	cmpl	$1, %eax
	jle	.L35
.L44:
	movl	%r13d, %esi
	movq	%r15, %rdi
	call	partitionL
	movl	%eax, %ebp
	cmpl	$1, %eax
	jle	.L36
	movl	%eax, 4(%rsp)
	movq	%r15, %r12
	movl	%eax, %r14d
	movl	%r13d, 16(%rsp)
	movq	%r15, 8(%rsp)
.L43:
	movl	%r14d, %esi
	movq	%r12, %rdi
	call	partitionL
	movl	%eax, %ebp
	cmpl	$1, %eax
	jle	.L37
	movl	%eax, (%rsp)
	movq	%r12, %r15
.L42:
	movl	(%rsp), %esi
	movq	%r15, %rdi
	call	partitionL
	movl	%eax, 96(%rsp)
	cmpl	$1, %eax
	jle	.L38
	movl	%ebp, 68(%rsp)
	movl	%eax, %ebp
	movq	%r12, 72(%rsp)
	movq	%r15, %r12
.L41:
	movl	%ebp, %esi
	movq	%r12, %rdi
	call	partitionL
	movl	%eax, %ebx
	cmpl	$1, %eax
	jle	.L39
	movq	%r12, %rdi
	movl	%ebp, %edx
	movq	%r12, %rcx
	movl	%eax, %r12d
	movq	%rdi, %rbp
.L40:
	movl	%ebx, %esi
	movq	%rbp, %rdi
	movq	%rcx, 104(%rsp)
	movl	%edx, 100(%rsp)
	call	partitionL
	movq	%rbp, %rdi
	movl	%eax, %esi
	movl	%eax, %r13d
	call	qSort2
	movl	%ebx, %eax
	movl	100(%rsp), %edx
	movq	104(%rsp), %rcx
	subl	%r13d, %eax
	leal	-1(%rax), %ebx
	movslq	%r13d, %rax
	cmpl	$1, %ebx
	leaq	4(%rbp,%rax,4), %rbp
	jg	.L40
	movl	%r12d, %ebx
	movl	%edx, %ebp
	movq	%rcx, %r12
.L39:
	movl	%ebp, %eax
	subl	%ebx, %eax
	leal	-1(%rax), %ebp
	movslq	%ebx, %rax
	leaq	4(%r12,%rax,4), %r12
	cmpl	$1, %ebp
	jg	.L41
	movl	68(%rsp), %ebp
	movq	72(%rsp), %r12
.L38:
	movl	(%rsp), %r13d
	movslq	96(%rsp), %rbx
	subl	%ebx, %r13d
	leaq	4(%r15,%rbx,4), %r15
	leal	-1(%r13), %eax
	movl	%eax, (%rsp)
	cmpl	$1, %eax
	jg	.L42
.L37:
	subl	%ebp, %r14d
	movslq	%ebp, %rax
	subl	$1, %r14d
	leaq	4(%r12,%rax,4), %r12
	cmpl	$1, %r14d
	jg	.L43
	movl	4(%rsp), %ebp
	movl	16(%rsp), %r13d
	movq	8(%rsp), %r15
.L36:
	subl	%ebp, %r13d
	movslq	%ebp, %rdx
	subl	$1, %r13d
	leaq	4(%r15,%rdx,4), %r15
	cmpl	$1, %r13d
	jg	.L44
.L35:
	movl	44(%rsp), %eax
	movl	92(%rsp), %edx
	movq	48(%rsp), %rsi
	subl	%edx, %eax
	leal	-1(%rax), %ecx
	movslq	%edx, %rax
	leaq	4(%rsi,%rax,4), %rax
	movl	%ecx, 44(%rsp)
	movq	%rax, 48(%rsp)
	cmpl	$1, %ecx
	jg	.L45
.L34:
	movl	88(%rsp), %edx
	movl	40(%rsp), %eax
	subl	%edx, %eax
	leal	-1(%rax), %ecx
	movslq	%edx, %rax
	movq	32(%rsp), %rdx
	movl	%ecx, 40(%rsp)
	leaq	4(%rdx,%rax,4), %rax
	movq	%rax, 32(%rsp)
	cmpl	$1, %ecx
	jg	.L46
.L33:
	movl	20(%rsp), %eax
	movl	84(%rsp), %edx
	movq	24(%rsp), %rcx
	subl	%edx, %eax
	leal	-1(%rax), %esi
	movslq	%edx, %rax
	leaq	4(%rcx,%rax,4), %rax
	movl	%esi, 20(%rsp)
	movq	%rax, 24(%rsp)
	cmpl	$1, %esi
	jg	.L47
.L32:
	movl	64(%rsp), %eax
	movl	80(%rsp), %ecx
	movq	56(%rsp), %rsi
	subl	%ecx, %eax
	leal	-1(%rax), %edi
	movslq	%ecx, %rax
	leaq	4(%rsi,%rax,4), %rax
	movl	%edi, 64(%rsp)
	movq	%rax, 56(%rsp)
	cmpl	$1, %edi
	jg	.L31
.L30:
	addq	$120, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	qSort2, .-qSort2
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
