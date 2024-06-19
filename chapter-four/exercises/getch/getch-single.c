char buf;  /* buffer for ungetch */

int getch(void) /* get a (possibly pushed back) character */
{
    char c;

    if (buf != 0)
        c = buf;
    else
        c = getchar();
    buf = 0;
    return c;
}

void ungetch(int c)
{
    if (buf != 0)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}

