// Write a C program to swap the content of 2 variables entered through the command line using function and pointer.

#include<stdio.h>
#include <stdlib.h>
void swapping(int *a, int *b){
    int x;
    x = *a;
    *a = *b;
    *b = x;
}

int main(int args, char* argv[]){
    int a=atoi(argv[1]);
    int b=atoi(argv[2])
    swapping(&a, &b);
    printf("Swapped: %d, %d\n", a,b);
}