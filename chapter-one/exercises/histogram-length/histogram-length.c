#include <stdio.h>

#define IN  0    /* inside a word */
#define OUT 1    /* outside a word */
#define MAXLEN 10    /* maximum length of word */

/* print horizontal histogram of the length of words in input */
int main(void)
{
    int c, i, nc, ovflow, state;
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
    
    for (i = 1; i < MAXLEN; ++i) {
        if (wl[i] > 0) {
            printf("%3d\t", i);
            while (wl[i] > 0) {
                putchar('*');
                --wl[i];
            }
            putchar('\n');
        }
    }
    if (ovflow > 0) {
        printf("%3d+\t", MAXLEN);
        while (ovflow > 0) {
            putchar('*');
            --ovflow;
        }
        putchar('\n');
    }
    return 0;
}

