#include<stdio.h>

int main(){
	int n;
	scanf("%d", &n);

	char *c;
	c= (char *) &n;
	for(int i=0; i<4; i++){
		printf("%d no of byte is %d\n", i+1, *(c+i));
	}
	return 0;
}

