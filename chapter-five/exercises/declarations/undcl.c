#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int nexttoken(void);
int tokentype;		  /* type of last token */
char token[MAXTOKEN];	  /* last token string */
char name[MAXTOKEN];	  /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];		  /* output string */
int prevtoken;

/* undcl:  convert word description to declaration */
int main(void)
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
	strcpy(out, token);
	while ((type = gettoken()) != '\n')
	    if (type == PARENS || type == BRACKETS)
		strcat(out, token);
	    else if (type == '*') {
		if ((type = nexttoken()) == PARENS ||
		    type == BRACKETS)
		    sprintf(temp, "(*%s)", out);
		else
		    sprintf(temp, "*%s", out);
		strcpy(out, temp);
	    } else if (type == NAME) {
		sprintf(temp, "%s %s", token, out);
		strcpy(out, temp);
	    } else
		printf("invalid input at %s\n", token);
	printf("%s\n", out);
    }
    return 0;
}

int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prevtoken == YES) {
	prevtoken = NO;
	return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
	;
    if (c == '(') {
	if ((c = getch()) == ')') {
	    strcpy(token, "()");
	    return tokentype = PARENS;
	} else {
	    ungetch(c);
	    return tokentype = '(';
	}
    } else if (c == '[') {
	for (*p++ = c; (*p++ = getch()) != ']'; )
	    ;
	*p = '\0';
	return tokentype = BRACKETS;
    } else if (isalpha(c)) {
	for (*p++ = c; isalnum(c = getch()); )
	    *p++ = c;
	*p = '\0';
	ungetch(c);
	return tokentype = NAME;
    } else
	    return tokentype = c;
}

int nexttoken(void)
{
    int type;

    type = gettoken();
    prevtoken = YES;
    return type;
}

#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

