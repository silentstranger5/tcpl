/* strncat:  concatenate first n characters of t to the end of s */
void strncat(int n, char *s, char *t)
{
    while(*s)
        s++;
    while (*t && n-- > 0)
        *s++ = *t++;
    *s = '\0';
}

