#include <ctype.h>

/* expand:  expand shorthand notation from s1 into s2 */
void expand(char s1[], char s2[])
{
    int c, i, j, k;

    for (i = j = 0; s1[i] != '\0'; i++)
        if (s1[i] == '-' && isalnum(s1[i - 1]) && isalnum(s1[i + 1]))
            for (k = 1; (c = s1[i - 1] + k) < s1[i + 1]; k++)
                s2[j++] = c;
        else
            s2[j++] = s1[i];
    s2[j] = '\0';
}

