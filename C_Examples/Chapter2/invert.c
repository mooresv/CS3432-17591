unsigned int invert(unsigned int x, int p, int n)
{
    return(x ^ ((~(~0<<n)) << p+1-n));
}
