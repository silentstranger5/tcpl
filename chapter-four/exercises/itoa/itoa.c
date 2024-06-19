/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    static int i = 0;

    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    if (n / 10)
        itoa(n / 10, s);
    else
        s[i] = '\0';
    s[i++] = n % 10 + '0';
}

