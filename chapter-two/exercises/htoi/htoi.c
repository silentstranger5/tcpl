/* htoi:  convert s to integer */
int htoi(char s[])
{
    int i, val;

    i = val = 0;
    if (s[i] == '0') {
        ++i;
        if (s[i] == 'x' || s[i] == 'X')
            ++i;
    }

    while (s[i] != '\0') {
        if (s[i] >= '0' && s[i] <= '9')
            val = 16 * val + (s[i] - '0');
        else if (s[i] >= 'a' && s[i] <= 'f')
            val = 16 * val + (10 + s[i] - 'a');
        else if (s[i] >= 'A' && s[i] <= 'F')
            val = 16 * val + (10 + s[i] - 'A');
        else {
            printf("error: unknown symbol %c\n", s[i]);
            return 0;
        }
        ++i;
    }
    return val;
}

