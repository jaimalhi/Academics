	.globl sumPlus
# int sumPlus(int *A, int N);
# A in rdi, N in esi
sumPlus:
	xorl	%eax, %eax
	testl	%esi, %esi
	jle		done
	xorl	%edx, %edx
	shl     $2, %rsi
loop:
	movl	(%rdi,%rdx), %ecx
	testl	%ecx, %ecx
	jle	    endif
	addl	%ecx, %eax
endif:
	addq	$4, %rdx
	cmpq	%rsi, %rdx
	jne		loop
done:
	ret
