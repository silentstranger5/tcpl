#include <stdio.h>

#define TABINC 8

int main(void)
{
    int c, nb, nt, pos;

    nb = nt = 0;
    for (pos = 1; (c = getchar()) != EOF; ++pos) {
        if (c == ' ') {
            if (pos % TABINC != 0)
                ++nb;
            else {
                nb = 0;
                ++nt;
            }
        } else {
            while (nt > 0) {
                putchar('\t');
                --nt;
            }
            if (c == '\t')
                nb = 0;
            else
                while (nb > 0) {
                    putchar(' ');
                    --nb;
                }
            putchar(c);
            if (c == '\n')
                pos = 0;
            else if (c == '\t')
                pos = pos + (TABINC - (pos - 1) % TABINC) - 1;
        }
    }
    return 0;
}

