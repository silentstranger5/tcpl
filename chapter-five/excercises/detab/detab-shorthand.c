#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC  8

enum boolean {NO, YES};

int main(int argc, char *argv[])
{
    void settab(int, char *[], char *);
    void detab(char *);
    char tab[MAXLINE];

    settab(argc, argv, tab);
    detab(tab);

    return 0;
}

void settab(int argc, char *argv[], char *tab)
{
    int i, inc, pos;
    char *arg, *tp;

    for (tp = tab; tp - tab < MAXLINE; tp++)
        *tp = NO;
    if (argc == 1)
        for (tp = tab + TABINC; tp - tab < MAXLINE; tp += TABINC)
            *tp = YES;
    else if (argc == 3) {
        pos = atoi(*++argv + 1);
        inc = atoi(*++argv + 1);
        for (i = 1; i <= MAXLINE; i++)
            if (i == pos) {
                tab[i] = YES;
                pos += inc;
            }
    }
    else
        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE)
                *(tab + pos) = YES;
        }
}

void detab(char *tab)
{
    int c, nb, pos, pc;
    int istabpos(int, char*);

    pos = 1;
    while ((c = getchar()) != EOF)
        if (c == '\t') {
            do
                putchar(' ');
            while (istabpos(pos++, tab) != YES);
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
}

int istabpos(int pos, char *tab)
{
    if (pos > MAXLINE)
        return YES;
    else
        return *(tab + pos);
}

