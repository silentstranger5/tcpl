#include <ctype.h>

/* atoi:  convert s to integer; version 2 */
int atoi(char *s)
{
    int i, n, sign;

    while (isspace(*s)) /* skip white space */
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '-' || *s == '+')  /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

