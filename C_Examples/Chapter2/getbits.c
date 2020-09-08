#include <stdio.h>

unsigned getbits(unsigned, int, int);

int main()
{
        unsigned x;
        int p;
        int n;
        printf("This program gets n bits from position p in number x\n");
        printf("Enter value of x in hexadecimal:");
        scanf("%x", &x);
        printf("Enter value of p in decimal:");
        scanf("%d", &p);
        printf("Enter value of n in decimal:");
        scanf("%d", &n);
	unsigned a = getbits(x, p, n);
	printf("getbits(%4x, %d, %d): %x\n", x, p, n, a);
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

