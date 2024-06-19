#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
void clear(void);

int gettoken(void);
int tokentype;		  /* type of last token */
char token[MAXTOKEN];	  /* last token string */
char name[MAXTOKEN];	  /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];		  /* output string */
int prevtoken;

int main(void)	/* convert declaration to words */
{
    while (gettoken() != EOF) {   /* 1st token on line */
	strcpy(datatype, token);  /* is the datatype */
	out[0] = '\0';
	dcl();      /* parse rest of line */
	if (tokentype != '\n') {
	    printf("syntax error\n");
	    prevtoken = YES;
	}
	printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl:  parse a declarator */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; )	/* count *'s */
	ns++;
    dirdcl();
    while (ns-- > 0)
	strcat(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
    int type;
    void parmdcl(void);
    
    if (tokentype == '(') {	     /* ( dcl ) */
	dcl();
	if (tokentype != ')') {
	    printf("error: missing )\n");
	    prevtoken = YES;
	}
    } else if (tokentype == NAME) {   /* variable name */
	if (name[0] == '\0')
            strcpy(name, token);
    } else
	prevtoken = YES;
    while ((type = gettoken()) == PARENS || type == BRACKETS
	|| type == '(')
	if (type == PARENS)
	    strcat(out, " function returning");
        else if (type == '(') {
	    strcat(out, " function expecting");
	    parmdcl();
	    strcat(out, " and returning");
	} else {
	    strcat(out, " array");
	    strcat(out, token);
	    strcat(out, " of");
	}
}

/* parmdcl:  parse a parameter declarator */
void parmdcl(void)
{
    void dclspec(void);

    do {
	dclspec();
    } while(tokentype == ',');
    if (tokentype != ')') {
	printf("missing ) in parameter declaration\n");
	prevtoken = YES;
    }
}

/* dclspec:  declaration specification */
void dclspec(void)
{
    char temp[MAXTOKEN];
    int typeext(void);

    temp[0] = '\0';
    gettoken();
    do {
	if (tokentype != NAME) {
	    prevtoken = YES;
	    dcl();
	} else if (typeext() == YES) {
	    strcat(temp, " ");
	    strcat(temp, token);
	    gettoken();
	} else {
	    printf("unknown type in parameter list\n");
	    prevtoken = YES;
	}
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',')
	strcat(out, ",");
}

/* typeext:  return YES if token is a
 *     type-specifier or type-qualifier */
int typeext(void)
{
    int i;
    static char *typeext[5] = {
	"char", "const", "int", "void", "volatile"
    };
    
    for (i = 0; i < 5; i++)
	if (strcmp(token, typeext[i]) == 0)
	    return YES;
    return NO;
}

int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prevtoken) {
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

