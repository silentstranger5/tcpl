#include <stdio.h>

/* replace each string of one or more blanks by a single blanks */
int main(void)
{
    int c, lc;

    lc = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (lc != ' ')
                putchar(c);
        }
        else
            putchar(c);
        lc = c;
    }
    return 0;
}

