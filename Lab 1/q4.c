#include <stdio.h>
struct pkt
{
    char ch1;
    char ch2[2];
    char ch3;
};
int main()
{
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);
    printf("%d\n", n);
    struct pkt p;
    p.ch1 = n & 0xFF;
    p.ch2[0] = n >> 8 & 0xFF;
    p.ch2[1] = n >> 16 & 0xFF;
    p.ch3 = n >> 24 & 0xFF;
    printf("1st Byte is %d \n", p.ch1);
    printf("2nd Byte is %d \n", p.ch2[0]);
    printf("3rd Byte is %d \n", p.ch2[1]);
    printf("4th Byte is %d \n", p.ch3);
    int num = (int)p.ch1 | (int)p.ch2[0] << 8 | p.ch2[1] << 16 | p.ch3 << 24;
    printf("The original number is %d", n);
    return 0;
}
