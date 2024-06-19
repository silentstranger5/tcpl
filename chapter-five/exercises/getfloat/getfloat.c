#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat:  get next float from input into *pf */
int getfloat(double *pf)
{
    int c, sign;
    double power;

    while (isspace(c = getch()))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' &&
         c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pf = 0; isdigit(c); c = getch())
        *pf = 10.0 * *pf + (c - '0');
    if (c == '.')
        c = getch();
    for (power = 1.0; isdigit(c); c = getch()) {
        *pf = 10.0 * *pf + (c - '0');
        power *= 10.0;
    }
    *pf *= sign / power;
    if (c != EOF)
        ungetch(c);
    return c;
}

