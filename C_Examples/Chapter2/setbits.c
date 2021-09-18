/* setbits: return x with the n bits that begin at position p 
   set to the rightmost n bits of y */
unsigned setbits(unsigned int x, int p, int n, unsigned int y)
{
        return((x & ~(~(~0 << n) << p+1-n)) | ((~(~0 << n) & y) << p+1-n));
}

