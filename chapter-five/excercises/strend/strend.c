/* strend:  return 1 if t occurs at the end of s, 0 otherwise */
int strend(char *s, char *t)
{
    char *bs = s, *bt = t;

    while(*s)
        s++;
    while(*t)
        t++;
    while(*s-- == *t--)
        if (s == bs || t == bt)
            break;
    if (*s == *t && t == bt && *s != '\0')
        return 1;
    else
        return 0;
}

