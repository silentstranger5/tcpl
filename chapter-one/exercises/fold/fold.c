#include <stdio.h>

#define MAXCOL 80
#define TABINC 8

char line[MAXCOL];

int expand(int pos);
int fnblank(int pos);
int newpos(int pos);
void printl(int pos);

int main(void)
{
    int c, pos;

    pos = 0;
    while ((c = getchar()) != EOF) {
        line[pos] = c;
        if (c == '\t')
            pos = expand(pos);
        else if (c == '\n') {
            printl(pos);
            pos = 0;
        } else if (++pos >= MAXCOL) {
            pos = fnblank(pos);
            printl(pos);
            pos = newpos(pos);
        }
    }
    return 0;
}

int expand(int pos)
{
    line[pos] = ' ';

    for (++pos; pos < MAXCOL && pos % TABINC != 0; ++pos)
        line[pos] = ' ';
    if (pos < MAXCOL)
        return pos;
    else {
        printl(pos);
        pos = 0;
        return pos;
    }
}

int fnblank(int pos)
{
    while (pos > 0 && line[pos] == ' ')
        --pos;
    if (pos == 0)
        return MAXCOL;
    else
        return pos + 1;
}

int newpos(int pos)
{
    int i, j;

    if (pos <= 0 || pos >= MAXCOL)
        return 0;
    else {
        i = 0;
        for (j = pos; j < MAXCOL; ++j) {
            line[i] = line[j];
            ++i;
        }
        return i;
    }
}

void printl(int pos)
{
    int i;

    for (i = 0; i < pos; ++i)
        putchar(line[i]);
    if (pos > 0)
        putchar('\n');
}

