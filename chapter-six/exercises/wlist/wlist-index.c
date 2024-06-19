#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct linklist {
    int lnum;
    struct linklist *ptr;
};

struct tnode {        /* the tree node: */
    char *word;              /* pointer to the text */
    struct linklist *lines;  /* pointer to list of numbers */
    struct tnode *left;      /* left child */
    struct tnode *right;     /* right child */
};

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int noiseword(char *);

/* word frequency count */
int main(void)
{
    int linenum = 1;
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
	if (isalpha(word[0]) && noiseword(word) == 0)
	    root = addtree(root, word, linenum);
        else if (word[0] == '\n')
	    linenum++;
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
struct linklist *lalloc(void);
char *strdup(char *);

/* addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
    int cond;
    void addln(struct tnode *, int);

    if (p == NULL) {	/* a new word has arrived */
	p = talloc();	/* make a new node */
	p->lines = lalloc();
	p->lines->lnum = linenum;
	p->lines->ptr = NULL;
	p->word = strdup(w);
	p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
	addln(p, linenum);	/* repeated word */
    else if (cond < 0)	/* less than into left subtree */
	p->left = addtree(p->left, w, linenum);
    else	    /* greater than into right subtree */
	p->right = addtree(p->right, w, linenum);
    return p;
}

/* addln:  add line number to the linked list */
void addln (struct tnode *p, int linenum)
{
    struct linklist *temp;

    temp = p->lines;
    while (temp->ptr != NULL && temp->lnum != linenum)
	temp = temp->ptr;
    if (temp->lnum != linenum) {
	temp->ptr = lalloc();
	temp->ptr->lnum = linenum;
	temp->ptr->ptr = NULL;
    }
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
    struct linklist *temp;

    if (p != NULL) {
	treeprint(p->left);
	printf("%10s:", p->word);
	for (temp = p->lines; temp != NULL; temp = temp->ptr)
	    printf("%4d", temp->lnum);
	putchar('\n');
	treeprint(p->right);
    }
}

/* noiseword:  identify word as noise word */
int noiseword(char *word)
{
    static char *nw[] = {
	"a",
	"an",
	"and",
	"are",
	"in",
	"is",
	"of",
	"or",
	"that",
	"the",
	"this",
	"to"
    };
    int cond, mid;
    int low = 0;
    int high = sizeof(nw) / sizeof(char *) - 1;

    while (low <= high) {
	mid = (low + high) / 2;
	if ((cond = strcmp(word, nw[mid])) < 0)
	    high = mid - 1;
	else if (cond > 0)
	    low = mid + 1;
	else
	    return 1;
    }
    return 0;
}

#include <stdlib.h>

/* talloc:  make a node */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* lalloc:  make a node for linked list */
struct linklist *lalloc(void)
{
    return (struct linklist *) malloc(sizeof(struct linklist));
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

    while (isspace(c = getch()) && c != '\n')
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

