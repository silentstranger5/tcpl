#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
	switch(type) {
	case NUMBER:
	    push(atof(s));
	    break;
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
		printf("error: zero divisor\n");
	    break;
	case '\n':
	    printf("\t%.8g\n", pop());
	    break;
	default:
	    printf("error: unknown command %c\n", type);
	    break;
	}
    }
    return 0;
}

#define MAXVAL	100	/* maximum depth of val stack */

double val[MAXVAL];	/* value stack */
double *sp = val;	/* next free stack position */

/* push:  push f onto value stack */
void push(double f)
{
    if (sp < val + MAXVAL)
	*sp++ = f;
    else
	printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
    if (sp >= val)
	return *--sp;
    else {
	sp = val;
	printf("error: stack empty\n");
	return 0.0;
    }
}

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
    char c, rc;
    float f;

    while ((rc = scanf("%c", &c)) != EOF)
	if ((*s = c) != ' ' && c != '\t')
	    break;
    *(s + 1) = '\0';
    if (rc == EOF)
	return EOF;
    else if (!isdigit(c) && c != '.')
	return c;
    ungetc(c, stdin);
    scanf("%f", &f);
    sprintf(s, "%f", f);
    return NUMBER;
}
