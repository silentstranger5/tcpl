#include <stdio.h>

int power(int base, int n);

/* test power function */
int main(void)
{
    int i;

    for (i = 0; i < 10; i++)
        printf("%d %d\n", i, power(2, i));
    return 0;
}

/* power:  raise base to n-th power; n >= 0; version 2 */
int power(int base, int n)
{
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;
    return p;
}

