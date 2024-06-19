#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */
#define LIMIT 80        /* limit of output line */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print input line longer than 80 characters */
int main(void)
{
    int len;            /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = getline(line, MAXLINE)) > 0)
        if (len > LIMIT)
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

