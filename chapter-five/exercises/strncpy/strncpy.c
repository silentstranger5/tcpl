/* strncpy:  copy first n characters of t to s */
void strncpy(int n, char *s, char *t)
{
    while (*t && n-- > 0)
        *s++ = *t++;
    *s = '\0';
}

