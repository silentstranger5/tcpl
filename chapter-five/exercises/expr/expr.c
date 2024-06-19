#include <stdio.h>
#include <stdlib.h>   /* for atof() */

void push(double);
double pop(void);

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
    char *type;
    double op2; 

    while (--argc > 0) {
        switch (*(type = *++argv)) {
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisior\n");
            break;
        default:
            if (*type >= '0' && *type <= '9')
                push(atof(type));
            else
                printf("error: unknown command %s\n", type);
            break;
        }
    }
    printf("\t%.8g\n", pop());
    return 0;
}

#define MAXVAL 100    /* maximum depth of val stack */

double val[MAXVAL];   /* value stack */
double *sp = val;

/* push:  push f onto value stack */
void push(double f)
{
    if (sp - val < MAXVAL)
        *sp++ = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > val)
        return *--sp;
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

