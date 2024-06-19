#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 100       /* max #lines to be stored */
#define DEFLINES 10        /* default #lines to be stored */

void readlines(char *lineptr[], int *fline, int *nlines);
void writelines(char *lineptr[], int fline, int nlines);

char *lineptr[MAXLINES];

/* tail:  print last n lines */
int main(int argc, char *argv[])
{
    int i, fline, nlines;

    if (argc == 1)
        nlines = DEFLINES;
    else if (argc == 2 && **++argv == '-')
        nlines = atoi(++*argv);
    else
        printf("Usage: tail -n\n");
    if (nlines < 1 || nlines > MAXLINES)
        nlines = DEFLINES;
    for (i = 0; i < MAXLINES; i++)
        lineptr[i] = NULL;
    readlines(lineptr, &fline, &nlines);
    writelines(lineptr, fline, nlines);
    return 0;
}

#define MAXLEN 1000   /* max length of any input line */

int getline(char *, int);
char *alloc(int);

/* readlines:  read input lines */
void readlines(char *lineptr[], int *fline, int *nlines)
{
    int len, nline;
    char *p, line[MAXLEN];

    nline = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nline > MAXLINES)
            nline = 0;
        p = alloc(len);
        line[len - 1] = '\0'; /* delete newline */
        strcpy(p, line);
        lineptr[nline++] = p;
    }
    if (*nlines > nline)
        *nlines = nline;
    *fline = nline - *nlines;
    if (*fline < 0)
        *fline += *nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int fline, int nlines)
{
    int i;

    for (i = fline; nlines-- > 0; i = (i + 1) % MAXLINES)
        printf("%s\n", lineptr[i]);
}

/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

char *alloc(int n)  /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp < n) /* it fits */
        allocp = allocbuf;
    allocp += n;
    return allocp - n; /* old p */
}

