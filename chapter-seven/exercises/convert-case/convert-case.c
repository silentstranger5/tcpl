#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;

    if (strcmp(*argv + 2, "lower") == 0)
	while ((c = getchar()) != EOF)
	    putchar(tolower(c));
    else if (strcmp(*argv + 2, "upper") == 0)
	while ((c = getchar()) != EOF)
	    putchar(toupper(c));
    return 0;
}
