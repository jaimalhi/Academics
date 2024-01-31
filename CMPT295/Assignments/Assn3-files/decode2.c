/* 
 * Filename: decode2.c
 *
 * Description: 
 *
 * Author: Jai M + Nyls P
 * Student number: 301457742 + 301461940
 */
 
#include <stdio.h>

//function declarations
int decode2(long x, long y, long z);

int main() {
    int ret = decode2(3,4,5);
    printf("%d\n", ret);

    return 0;
}

//code was simplfied (from assembly) to reduce amount of variables used/updated
int decode2(long x, long y, long z){
    long t1 = y - z;
    long t2 = x * t1;
    //temp3 = 0 or -1, if temp = -1 then temp2 is complemented, else temp2 doesnt change
    long t3 = (t1 << 63) >> 63;
    return t3 ^ t2;
}

/* Assembly Code from Textbook
#x -> %rdi, y -> %rsi, z -> %rdx
#return value stored in %rax
decode2:
    subq %rdx, %rsi   # Subtraction: t1 = y - z (t1 -> %rsi)
    imulq %rsi, %rdi  # Multiplication: t2 = x * t1 (t2 -> %rdi)
    movq %rsi, %rax   # Moving: t3 = t1 (t3 -> %rax, t1 -> %rsi)
    salq $63, %rax    # Arith Shift Left: t3 << 63 (t3 -> %rax)
    sarq $63, %rax    # Arith Shift Right: t3 >> 63 (t3 -> %rax)
    xorq %rdi, %rax   # Exclusive or: t3 ^ t2 (t3 -> %rax, t2 -> %rdi)
    ret
*/