#include <stdio.h>

unsigned int rightrot(unsigned int x, int n)
{
    unsigned nbits = 8*sizeof(unsigned int);

    if (n == 0 || n == nbits)
        return(x);
    return(x >> n | (x << (nbits - n)));
}
