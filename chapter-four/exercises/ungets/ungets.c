/* ungets:  push back s onto the input */
void ungets(char s[])
{
    int len = strlen(s);
    void ungetch(int);

    while (len > 0)
        ungetch(s[--len]);
}

