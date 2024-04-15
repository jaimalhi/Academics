#include <stdio.h>

int main(int argCount, char *argv[]) {  
    // char** args = char* argv[] (array of pointers)

    printf("Arguments (%d) with Arg 0: %s\n", argCount, argv[0]);
    for (int i = 1; i < argCount; i++) {
        printf("%s\n", argv[i]);
    }

    return 0;
}
