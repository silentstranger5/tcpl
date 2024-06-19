/* invert:  set n bits of x from position p inverted */
unsigned invert(unsigned x, int n, int p)
{
    return x ^ (~(~0 << n) << (p + 1 - n));
}
