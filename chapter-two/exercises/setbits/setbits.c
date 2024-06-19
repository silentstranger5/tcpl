/* setbits:  set n bits of x that begins at p to rigtmost n bits of y */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return x & ~(~(~0 << n) << (p + 1 - n)) |
        (y & ~(~0 << n)) << (p + 1 - n);
}

