#include <ctype.h>
#include <stdio.h>

#define MAXCHAR 256    /* maximum number of characters */

int main(void)
{
    int c, i;
    int fc[MAXCHAR];
    
    for (i = 0; i < MAXCHAR; i++)
        fc[i] = 0;

    while ((c = getchar()) != EOF)
        ++fc[c];

    for (i = 0; i < MAXCHAR; i++) {
        if (fc[i] > 0) {
            if (isprint(i))
                printf("%3d %3c\t", i, i);
            else
                printf("%3d %3c\t", i, ' ');
            while (fc[i] > 0) {
                putchar('*');
                --fc[i];
            }
            putchar('\n');
        }
    }
    return 0;
}

