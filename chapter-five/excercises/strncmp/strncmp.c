/* strncmp:  compare first n characters of t to s */
int strncmp(int n, char *s, char *t)
{
    while (n-- > 0 && *s++ == *t++)
        ;
    return *s - *t;
}

