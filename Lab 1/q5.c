// Write a C program to check whether the Host machine is in Little Endian or Big Endian. Enter a number, print the content of each byte location, and Convert the Endianness of the same i.e. Little to Big Endian, and vice-versa.
#include<stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);
    printf("%d\n", n);
    char *c;
    c= (char *) &n;
    for(int i=0; i<4; i++){
        printf("digit in the %d byte=%d\n", i+1, *(c+i));
    }

    printf("Extracted byte from LSB of the number = %d\n", *(c+0));
    printf("Extracted byte from 2nd LSB of the number = %d\n", *(c+1));



}