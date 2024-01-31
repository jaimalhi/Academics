# objdump -d main.o -> object dump tool to view machine code

# Table 1
xorq 	%rax, %rax
xorl	%eax, %eax
movq	$0, %rax
movl	$0, %eax
subl	%eax, %eax
imull	$0, %eax
andl	$0, %eax

# Table 2
addl	$1, %eax
leal	1(%eax), %eax
incl	%eax
subl	$-1, %eax

# Table 3
addl	$8, %eax
leal	8(%eax), %eax

# Table 4
subq	$8, %rsp
movq	%rdi, (%rsp)
pushq	%rdi

# Table 5
movq	(%rsp), %rsi
addq	$8, %rsp
popq	%rsi