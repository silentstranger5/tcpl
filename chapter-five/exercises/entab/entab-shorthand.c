#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define TABINC  8

enum boolean {NO, YES};

int main(int argc, char *argv[])
{
    void settab(int, char *[], char *);
    void entab(char *);
    char tab[MAXLINE];

    settab(argc, argv, tab);
    entab(tab);

    return 0;
}

void settab(int argc, char *argv[], char *tab)
{
    int inc, pos;
    char *arg, *tp;

    for (tp = tab; tp - tab < MAXLINE; tp++)
        *tp = NO;
    if (argc == 1)
        for (tp = tab + TABINC; tp - tab < MAXLINE; tp += TABINC)
            *tp = YES;
    else if (argc == 3) {
        pos = atoi(*++argv + 1);
        inc = atoi(*++argv + 1);
        for (tp = tab + pos; tp - tab < MAXLINE; tp += inc)
            *tp = YES;
    }
    else
        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE)
                *(tab + pos) = YES;
        }
}

void entab(char *tab)
{
    int c, nb, nt, pos;
    int istabpos(int, char *);

    nb = nt = 0;
    for (pos = 1; (c = getchar()) != EOF; ++pos) {
        if (c == ' ') {
            if (istabpos(pos, tab) == NO)
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
                while (istabpos(pos, tab) != YES)
                    ++pos;
        }
    }
}

int istabpos(int pos, char *tab)
{
    if (pos > MAXLINE)
        return YES;
    else
        return *(tab + pos);
}

