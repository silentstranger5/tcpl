#include <stdio.h>

#define FALSE 0
#define TRUE  1

void comment(void);
void quote(char c);

int main(void)
{
    int brace, brack, c, match, paren;

    match = TRUE;
    brace = brack = paren = 0;
    while ((c = getchar()) != EOF && match == TRUE) {
        if (c == '{')
            ++brace;
        else if (c == '}')
            --brace;
        else if (c == '[')
            ++brack;
        else if (c == ']')
            --brack;
        else if (c == '(')
            ++paren;
        else if (c == ')')
            --paren;
        else if (c == '/')
            comment();
        else if (c == '\'')
            quote(c);
        else if (c == '"')
            quote(c);
        if (brace < 0) {
            printf("unmatched enclosing brace\n");
            match = FALSE;
        } else if (brack < 0) {
            printf("unmatched enclosing bracket\n");
            match = FALSE;
        } else if (paren < 0) {
            printf("unmatched enclosing parenthesis\n");
            match = FALSE;
        }
    }
    if (match == TRUE) {
        if (brace > 0)
            printf("unmatched open brace\n");
        else if (brack > 0)
            printf("unmatched open bracket\n");
        else if (paren > 0)
            printf("unmatched open parenthesis\n");
        else
            printf("all match\n");
    }
    return 0;
}

void comment(void)
{
    int c, d;

    if ((c = getchar()) != '*')
        return;

    else {
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
    char d;

    while ((d = getchar()) != c)
        if (d == '\\')
            getchar();
}

