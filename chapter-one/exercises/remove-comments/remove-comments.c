#include <stdio.h>

void comment(void);
void quote(char c);

int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '/')
            comment();
        else if (c == '\'' || c == '"')
            quote(c);
        else
            putchar(c);
    }
    return 0;
}

void comment(void)
{
    int c, d;

    if ((c = getchar()) != '*') {
        putchar('/');
        putchar(c);
    } else {
        c = getchar();
        d = getchar();
        while (c != '*' || d != '/') {
            c = d;
            d = getchar();
        } 
    }
}

void quote(char c)
{
    int d;

    putchar(c);
    while ((d = getchar()) != c) {
        putchar(d);
        if (d == '\\')
            putchar(getchar());
    }
    putchar(d);
}

