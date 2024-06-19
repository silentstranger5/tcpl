#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct tnode {        /* the tree node: */
    char *word;           /* pointer to the text */
    int match;            /* number of occurrences */
    struct tnode *left;   /* left child */
    struct tnode *right;  /* right child */
};

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *, int, int *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main(int argc, char *argv[])
{
    int found = 0, num;
    struct tnode *root;
    char word[MAXWORD];
    
    num = (--argc && **++argv == '-') ? atoi(++*argv) : 6;
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
	if (isalpha(word[0]) && strlen(word) >= num)
	    root = addtree(root, word, num, &found);
	found = 0;
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int num, int *found)
{
    int cond, compare(char *, struct tnode *, int, int *);

    if (p == NULL) {	/* a new word has arrived */
	p = talloc();	/* make a new node */
	p->word = strdup(w);
	p->match = *found;
	p->left = p->right = NULL;
    } else if ((cond = compare(w, p, num, found)) < 0)
	p->left = addtree(p->left, w, num, found);	/* repeated word */
    else if (cond > 0)	    /* greater than into right subtree */
	p->right = addtree(p->right, w, num, found);
    return p;
}

/* compare:  compare words and update p->match */
int compare(char *s, struct tnode *p, int num, int *found)
{
    int i;
    char *t = p->word;

    for (i = 0; *s == *t; i++, s++, t++)
	if (*s == '\0')
	    return 0;
    if (i >= num) {	/* identical in first num chars ? */
	p->match = 1;
	*found = 1;
    }
    return *s - *t;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
	treeprint(p->left);
	if (p->match == 1)
	    printf("%s\n", p->word);
	treeprint(p->right);
    }
}

#include <stdlib.h>

/* talloc:  make a node */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)	/* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);  /* +1 for '\0' */
    if (p != NULL)
	strcpy(p, s);
    return p;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
	;
    if (c != EOF)
	*w++ = c;
    if (!isalpha(c)) {
	*w = '\0';
	return c;
    }
    for ( ; --lim > 0; w++)
	if (!isalnum(*w = getch())) {
	    ungetch(*w);
	    break;
	}
    *w = '\0';
    return word[0];
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

