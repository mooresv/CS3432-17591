/* getbits: get n bits from position p */
unsigned int getbits(unsigned int x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}
