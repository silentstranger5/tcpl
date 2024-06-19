/* strindex:  return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    int i, j, k;
    char *u, *v, *bs = s;

    while (*s++) {
        for (u = s, v = t; *v && *u == *v; u++, v++)
            ;
        if (v > t && !*v)
            return s - bs;
    }
    return -1;
}

