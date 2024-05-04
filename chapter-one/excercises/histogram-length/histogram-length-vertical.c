#include <stdio.h>

#define IN  0    /* inside a word */
#define OUT 1    /* outside a word */
#define MAXLEN 10    /* maximum length of word */

/* print vertical histogram of the length of words in input */
int main(void)
{
    int c, i, j, max, nc, ovflow, state;
    int wl[MAXLEN];

    for (i = 0; i < MAXLEN; i++)
        wl[i] = 0;

    nc = ovflow = 0;
    state = OUT;
    while ((c = getchar()) != EOF) {
       if (c == ' ' || c == '\t' || c == '\n') {
           state = OUT;
           if (nc > 0)
               if (nc < MAXLEN)
                   ++wl[nc];
               else
                   ++ovflow;
           nc = 0;
       }
       else {
           if (state == OUT)
               state = IN;
           ++nc;
       }
    }

    max = 0;
    for (i = 1; i < MAXLEN; ++i)
        if (wl[i] > max)
            max = wl[i];

    for (i = max; i > 0; --i) {
        for (j = 1; j < MAXLEN; ++j)
            if (wl[j] >= i)
                printf(" * ");
            else if (wl[j] > 0)
                printf("   ");
        if (ovflow >= i)
            printf(" * ");
        putchar('\n');
    }

    for (i = 1; i < MAXLEN; ++i)
        if (wl[i] > 0)
            printf("%2d ", i);
    if (ovflow > 0)
        printf("%2d+", MAXLEN);
    putchar('\n');

   return 0;
}

