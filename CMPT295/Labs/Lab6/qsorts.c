/* 
 * Filename: qsorts.c
 *
 * Description: The functions we are benchmarking in this Lab 6:
 *              - Quick Sort using the Hoare partitioning algorithm
 *              (qSort1(...) and partitionH(...))
 *              - Quick Sort using the Lomuto partitioning algorithm
 *              (qSort2(...) and partitionL(...))
 *
 * Auhtor:
 * Modification date: March 2023
 */
 
int partitionH(int *A, int n);
int partitionL(int *A, int n);

// Hoare Partition
void qSort1(int *A, int n) {
    int q;
    if (n <= 1) return;
    q = partitionH(A, n);
    qSort1(A, q + 1);
    qSort1(A + q + 1, n - q - 1);
}  

// Lomuto Partition
void qSort2(int *A, int n) {
    int q;
    if (n <= 1) return;
    q = partitionL(A, n);
    qSort2(A, q);
    qSort2(A + q + 1, n - q - 1);
} 

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
} 

// Hoare Partition
int partitionH(int *A, int n) {
    int x = A[0];
    int i = -1;
    int j = n;
    while (1) {
        while (A[--j] > x);
        while (A[++i] < x);
        if (i < j) swap(A+i, A+j); else return j;
    } 
}  

// Lomuto Partition
int partitionL(int *A, int n) {
    int x = A[--n];
    int i = 0;
    int j;
    for (j = 0; j < n; j++) 
        if (A[j] <= x) 
            swap(A + i++, A+j);
    swap(A+i, A+n);
    return i;
}  


