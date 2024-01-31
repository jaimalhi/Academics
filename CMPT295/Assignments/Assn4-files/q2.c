/*
 * Filename: q2.c
 * Purpose: convert assembly to c code
 * Author: Jai Malhi
*/

#include <stdio.h>

long func(long x, int n);

int main( ){
    long ret = func(5,1);
    printf("%d\n",ret);
    return 0;
}

// a. Which registers hold program values x, n, result and mask?
// b. What is the initial value of result and of mask?
// c. What is the test condition for mask?
// d. How is mask updated?
// e. How is result updated?

long func(long x, int n){
    long result = 0;
    long mask;

    for(mask = 1 ; mask != 0 ; mask = mask << n){
        if(x & mask){
            result |= mask;
        }
    }

    // for (mask = 1;mask != 0;mask = mask << n){
    //     result |= mask;
    // }
    // return result;
}

/* #long func(long x, int n)
# x -> %rdi; n -> %esi; result -> %eax, %rax; mask -> %edx, %rdx 
func:
  movl  %esi, %ecx
  movl  $1,   %edx
  movl  $0,   %eax
  jmp   cond
loop:
  movq  %rdi, %r8
  andq  %rdx, %r8
  orq   %r8,  %rax
  salq  %cl,  %rdx    # shift left the value stored in %rdx by an amount 
                      # dictated by the value stored in %cl - see Note below
cond:
  testq %rdx, %rdx
  jne   loop       
  ret #ret %rdx
*/