#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);
int remove_trail(char line[]);

/* print input line with removed trail blanks and tabs */
int main(void)
{
    int len;            /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = getline(line, MAXLINE)) > 0) 
        if (remove_trail(line) > 0)
            printf("%s", line);
    
    return 0;
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

/* remove_trail:  remove trailing blanks and tabs from line */
int remove_trail(char s[])
{
    int i;

    for (i = 0; s[i] != '\n'; ++i)
        ;
    --i;
    while (s[i] == ' ' || s[i] == '\t')
        --i;
    if (i >= 0) {
        ++i;
        s[i] = '\n';
        ++i;
        s[i] = '\0';
    }
    return i;
}

