#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int invert(unsigned int, int, int);
extern unsigned int setbits(unsigned int, int, int, unsigned int);
extern unsigned int getbits(unsigned int, int, int);
extern unsigned int rightrot(unsigned int, int);

void showbits( unsigned int x )
{
    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

int main()
{
        unsigned int x, y, a;
        int p;
        int n;

        printf("This program gets n bits from position p in number x\n");
//        printf("This program inverts the n bits that begin at position p in x\n");
//        printf("This program rotates x right by n bit positions\n");
        printf("This program then sets the n bits that begin at position p in x to the rightmost n bits of y\n");
        printf("Enter value of x in hexadecimal: ");
        scanf("%x", &x);
        printf("x in binary: ");
        showbits(x);
        printf("\n");
        printf("Enter value of y in hexadecimal: ");
        scanf("%x", &y);
        printf("y in binary: ");
        showbits(y);
        printf("\n");
        printf("Enter value of p in decimal: ");
        scanf("%d", &p);
        printf("Enter value of n in decimal: ");
        scanf("%d", &n);
	a = getbits(x, p, n);
	printf("\ngetbits(x%08x, %d, %d): x%08x\n", x, p, n, a);
        printf("binary: ");
        showbits(a);
        printf("\n");
/*	a = invert(x, p, n);
	printf("invert(x%08x, %d, %d): x%08x\n", x, p, n, a);
        printf("binary: ");
        showbits(a);
        printf("\n");
	a = rightrot(x, n);
	printf("rightrot(x%08x, %d): x%08x\n", x, n, a);
        printf("binary: ");
        showbits(a);
        printf("\n");
*/
        a = setbits(x, p, n, y);
        printf("setbits(x%08x, %d, %d, x%08x); x%08x\n", x, p, n, y, a);
        printf("binary: ");
        showbits(a);
        printf("\n");
}
