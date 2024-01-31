# add a header comment block

	.globl	compareValues 
	.globl	plus
	.globl	minus
	.globl	mul


compareValues: # Description: compares x and y, sets return value to 0 if x >= y, or 1 if y > x
    # x -> %edi, y -> %esi, return value -> %eax
	xorl	%eax, %eax  # set %eax (return value) to 0
	cmpl	%esi, %edi  # compare x : y
	setl	%al         # set %eax to 0 or 1
	ret                 # set* info on Pg.203

plus: # Description: Performs integer addition
# Requirement:
# - you cannot use add* instruction
# - you cannot use a loop

# x -> %edi, y -> %esi, return value -> %eax
# Put your code here
    leal (%rdi,%rsi,1), %eax # use leal to perform x + y * 1, storing result in %eax,
    ret                      # using %rdi and %rsi to match calling convention for x86
    

minus: # Description: Performs integer subtraction
# Requirement:
# - you cannot use sub* instruction
# - you cannot use a loop

# x -> %edi, y -> %esi, return value -> %eax
# Put your code here
    negl %esi                 #  negate y (turn into a negative)
    leal (%rdi,%rsi,1), %eax  # use leal to perform x + (-y) * 1, storing result in %eax,
    ret                       # using %rdi and %rsi to match calling convention for x86


mul: # performs integer multiplication - when both operands are non-negative!
# x in %edi, y in %esi, return value in %eax
# Requirements:
# - cannot use imul* instruction
# - you must use recursion (no loop) and the stack

# Put your Code here
    pushq %rbp           # save base pointer
    movq %rsp, %rbp      # set current stack pointer

    xorl %eax, %eax      # Initialize the return value to 0
    cmpl $0, %esi        # Check if y is 0
    je end               # If y is 0, jump to the end

    movl %edi, %eax      # Load x into the return value
    decl %esi            # Decrement y by 1
    call mul             # Call the function recursively
    addl %edi, %eax      # Add x to the return value

end:
    popq %rbp            # restore original base pointer
    ret

