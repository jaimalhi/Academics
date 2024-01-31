/*
 * Filename: subprog.c
 *
 * Purpose: Lab 2
 * 
 * Last Modified: Jan. 2023
 *
 */
 
typedef unsigned short bit16;

char *mystery(bit16 x, char* str) {
    int i;
    for (i = 0; i < 16; i++) {
        str[i] = (char) ((x & 0x8000) >> 15) | 0x30;
        x = (x << 1) & 0xffff;
    }
    str[16] = '\0';
    return str;  
}