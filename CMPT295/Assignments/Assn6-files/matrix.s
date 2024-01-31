# =============================================================
# Filename: matrix.s
# Description: x86-64 for the purpose of rotating a matrix 90 deg clockwise
# - transpose: find the transpose for a NxN matrix
# - reverseColumns: reverse the columns for a NxN matrix
# Date: March 10, 2023
# Name: Jai Malhi & Nyls Poonoosamy
# =============================================================

    .globl    copy
# ***** Version 2 *****
copy:
# A in %rdi, C in %rsi, N in %edx

# Using A and C as pointers

# This function is not a "caller", i.e., it does not call functions. 
# It is a leaf function (a callee). 
# Hence it does not have the responsibility of saving "caller-saved" registers 
# such as %rax, %rdi, %rsi, %rdx, %rcx, %r8 and %r9.
# This signifies that it can use these registers without 
# first saving their content if it needs to use registers.

# Set up registers
    xorl %eax, %eax            # set %eax to 0
    xorl %ecx, %ecx            # i = 0 (row index i is in %ecx)

# For each row
rowLoop:
    xorl %r8d, %r8d            # j = 0 (column index j in %r8d)
    cmpl %edx, %ecx            # while i < N (i - N < 0)
    jge doneWithRows

# For each cell of this row
colLoop:
    cmpl %edx, %r8d            # while j < N (j - N < 0)
    jge doneWithCells

# Copy the element A points to (%rdi) to the cell C points to (%rsi)
    movb (%rdi), %r9b          # temp = element A points to
    movb %r9b, (%rsi)          # cell C points to = temp

# Update A and C so they now point to their next element 
    incq %rdi
    incq %rsi

    incl %r8d                  # j++ (column index in %r8d)
    jmp colLoop                # go to next cell

# Go to next row
doneWithCells:
    incl %ecx                  # i++ (row index in %ecx)
    jmp rowLoop                # go to next row

doneWithRows:                  # bye! bye!
    ret


# #################### #
	.globl	transpose
# Transpose a square matrix
# N (size of matrix) -> %rsi / %esi
# row -> %eax
# col -> %ecx
transpose:
    # Set up loop counters
    xorl %eax, %eax       # row = 0

.outer_loop:
    cmpl %esi, %eax      # compare row with n
    jge .end_outer_loop  # exit outer loop if row >= n

    # Reset inner loop counter
    movl %eax, %ecx      # col = row

.inner_loop:
    cmpl %esi, %ecx      # compare col with n
    jge .end_inner_loop  # exit inner loop if col >= n

    # Compute indices for arr[row][col] 
    movl %eax, %edx      # edx = row
    imull %esi, %edx     # edx *= n
    addl %ecx, %edx      # edx += col
    movb (%rdi,%rdx), %r8b # compute address of arr[row][col]
    
    # Compute indices for arr[col][row]
    movl %ecx, %edx      # edx = col
    imull %esi, %edx     # edx *= n
    addl %eax, %edx      # edx += row
    movb (%rdi,%rdx), %r9b # compute address of arr[col][row]

    # put [row][col] into [col][row]
    movb %r8b, (%rdi,%rdx,1)

    # Compute indices for arr[row][col] again
    movl %eax, %edx      # edx = row
    imull %esi, %edx     # edx *= n
    addl %ecx, %edx      # edx += col
    movb %r9b, (%rdi,%rdx,1) # compute address of arr[row][col]
    
    incl %ecx            # col++
    jmp .inner_loop

.end_inner_loop:
    incl %eax            # row++
    jmp .outer_loop      # jump back to outer loop

.end_outer_loop:
    ret               

# #################### #
	.globl	reverseColumns
# N -> %esi   (was %ecx)
# row -> %eax (was %edx)
# col -> %ecx (was %ebx)
reverseColumns:
    # set up loop counters
    movl %esi, %r11d         # r11d = n
    shrl $1, %r11d           # divide n by 2 (n/2 loop control)
    xorl %ecx, %ecx         # initialize col to 0

.col_loop: 
    cmpl %r11d, %ecx         # compare col to n/2
    jge .end_col_loop       # if col >= n/2 

    # Reset inner loop counter
    xorl %eax, %eax         # row = 0

.row_loop:
    cmpl %esi, %eax  # compare row to n
    jge .end_row_loop       # if row >= n

    # Compute indices for arr[row][col] 
    movl %eax, %edx      # edx = row
    imull %esi, %edx     # edx *= n
    addl %ecx, %edx      # edx += col
    movb (%rdi,%rdx), %r8b # compute address of arr[row][col]

    # Compute indices for arr[row][n-col-1]
    movl %eax, %edx      # edx = row
    imull %esi, %edx     # edx *= n

    movl %esi, %r10d     # r10d = n
    subl %ecx, %r10d      # r10d = n-col
    subl $1, %r10d        # r10d = col-1

    addl %r10d, %edx      # edx += col
    movb (%rdi,%rdx), %r9b # compute address of arr[row][n-col-1]

    # put [row][col] into [row][n-col-1]
    movb %r8b, (%rdi,%rdx,1)

    # Compute indices for arr[row][col] again
    movl %eax, %edx      # edx = row
    imull %esi, %edx     # edx *= n
    addl %ecx, %edx      # edx += col
    movb %r9b, (%rdi,%rdx,1) # compute address of arr[row][col]

    incl %eax               # row++
    jmp .row_loop           # jump to row_loop

.end_row_loop:
    incl %ecx               # col++
    jmp .col_loop           # jump to col_loop

.end_col_loop:
    ret 
