#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    static int lc;

    if (lc) {
        c = lc;
        lc = 0;
    } else
        c = getchar();
    while ((s[0] = c) == ' ' || c == '\t')
        c = getchar();
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;     /* not a number */
    i = 0;
    if (isdigit(c))   /* collect integer part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')     /* collect fraction part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lc = c;
    return NUMBER;
}

