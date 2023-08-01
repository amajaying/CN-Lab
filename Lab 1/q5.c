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

    printf("\nExtracted byte from LSB of the number = %d\n", *(c+0));
    printf("Extracted byte from 2nd LSB of the number = %d\n\n", *(c+1));

    int converted = (int)*(c+3) | (int) *(c+2)<<8 | (int) *(c+1)<<16 | (int) *(c+0);

    if(*(c+0)>*(c+1)){
        printf("The representation is: Little Endian\n\n");
    }
    else{
        printf("The representation is: Big Endian\n\n");
    }
    
    for(int i=3; i>=0; i--){
        printf("digit in the %d byte=%d\n", 3-i+1, *(c+i));
    }



}
