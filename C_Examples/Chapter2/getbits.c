#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//extern char* itoa(int, char*, int);
 
unsigned getbits(unsigned, int, int);
void reverse(char s[]);
void itoa(int n, char s[]);

int main()
{
        unsigned x;
        int p;
        int n;
        char buffer[100];
        char outbuf[100];
        int width = 32;
        int len;

        printf("This program gets n bits from position p in number x\n");
        printf("Enter value of x in hexadecimal: ");
        scanf("%x", &x);
        itoa(x, buffer);
        len = strlen(buffer);
        if (len >= width)
            strcpy(outbuf, buffer); 
        else
            sprintf(outbuf, "%0*d%s", (int) (width - len), 0, buffer);
        printf("binary: %32s\n", outbuf);
        printf("Enter value of p in decimal: ");
        scanf("%d", &p);
        printf("Enter value of n in decimal: ");
        scanf("%d", &n);
	unsigned a = getbits(x, p, n);
	printf("getbits(%08x, %d, %d): x%x\n", x, p, n, a);
        itoa(a, buffer);
        width = n;
        len = strlen(buffer);
        if (len >= width)
            strcpy(outbuf, buffer); 
        else
            sprintf(outbuf, "%0*d%s", (int) (width - len), 0, buffer);
        printf("binary: %s\n", outbuf);
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  
