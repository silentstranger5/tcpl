#include <stdio.h>

/* replace each escape sequence by visible representation */
int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        if (c == '\b')
            printf("\\b");
        if (c == '\\')
            printf("\\\\");
        if (c != '\t')
            if (c != '\b')
                if (c != '\\')
                    putchar(c);
    }
    return 0;
}

