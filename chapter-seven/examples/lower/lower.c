#include <ctype.h>
#include <stdio.h>

int main(void)	/* lower:  convert input to lower case */
{
    int c;

    while ((c = getchar()) != EOF)
	putchar(tolower(c));
    return 0;
}
