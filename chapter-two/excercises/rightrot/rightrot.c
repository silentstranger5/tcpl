/* rightrot:  rotate x by n positions */
unsigned rightrot(unsigned x, int n)
{
    int wordlen(void);

    while (n-- > 0)
        x = x >> 1 | (x & 1) << (wordlen() - 1);
    return x;
}

/* wordlen:  computes word length of machine */
int wordlen(void)
{
    int i;
    unsigned v = (unsigned) ~0;

    for (i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}

