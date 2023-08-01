#include<stdio.h>

int main(){
	int n;
    printf("Enter the number: ");
	scanf("%d", &n);

	char *c;
	c= (char *) &n;
	for(int i=0; i<4; i++){
		printf("digit in the %d byte=%d\n", i+1, *(c+i));
	}
	return 0;
}

