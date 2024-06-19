#include <stdio.h>

#define MAXLINE 1000

enum boolean {FALSE, TRUE};

int main()
{
    int c, i, loop;
    char s[MAXLINE];

    i = 0;
    loop = TRUE;
    while (loop) {
        if (i >= MAXLINE - 1)
            loop = FALSE;
        else if ((c = getchar()) == '\n')
            loop = FALSE;
        else if (c == EOF)
            loop = FALSE;
        else {
            s[i] = c;
            ++i;
        }
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    printf("%s", s);
    return 0;
}

