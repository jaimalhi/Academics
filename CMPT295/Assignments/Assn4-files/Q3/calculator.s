# add a header comment block

	.globl	compareValues 
	.globl	plus
	.globl	minus
	.globl	mul


compareValues: # Description: compares x and y, sets return value to 0 if x >= y, or 1 if y > x
    # x -> %edi, y -> %esi, return value -> %eax
	xorl	%eax, %eax  #set %eax (return value) to 0
	cmpl	%esi, %edi  #compare x : y
	setl	%al         #set %eax to 0 or 1what 
	ret                 #set* info on Pg.203

plus: # Description: Performs integer addition
# Requirement:
# - you cannot use add* instruction
# - you cannot use a loop

# x -> %edi, y -> %esi, return value -> %eax
# Put your code here
    leal (%rdi,%rsi,1), %eax #use leal to perform x + y * 1, storing result in %eax,
    ret                      #using %rdi and %rsi to match calling convention for x86
    

minus: # Description: Performs integer subtraction
# Requirement:
# - you cannot use sub* instruction
# - you cannot use a loop

# x -> %edi, y -> %esi, return value -> %eax
# Put your code here
    negl %esi                 #negate y (turn into a negative)
    leal (%rdi,%rsi,1), %eax  #use leal to perform x + (-y) * 1, storing result in %eax,
    ret                       #using %rdi and %rsi to match calling convention for x86


mul: # Description: Performs integer multiplication - when both operands are non-negative!
# You can assume that both operands are non-negative.
# Requirements:
# - you cannot use imul* instruction 
#   (or any kind of instruction that multiplies such as mul)
# - you must use a loop

# x -> %edi, y -> %esi, return value -> %eax
# algorithm:
# - set return value to zero (in case of mult by 0)
# - jump to false condition (endloop)
# - within endloop, if y > 0, enter loop
# - within loop add x to return value
# - repeat cycle until y <= 0 and return %eax

# Put your code here
    xorl %eax, %eax   #zero out %eax (return value)
    jmp endloop       #unconditional jump
loop:
    addl %edi, %eax   #add x to %eax
    decl %esi         #decrement y
endloop:
    testl %esi, %esi  #compare y with 0
    jg loop           #jump to loop if y > 0
    ret            