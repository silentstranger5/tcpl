#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

#define NUMERIC 1
#define REVERSE 2
#define FOLD    4
#define DIRECT  8
int option = 0;

int pos1 = 0, pos2 = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);

void my_qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int numcmp(char *, char *);
int charcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;
    int c, rc = 0;

    while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')) {
	if (c == '-' && !isdigit(*(*argv + 1))) {
            while (c = *++*argv)
                switch (c) {
                case 'n':
                    option |= NUMERIC;
                    break;
                case 'r':
                    option |= REVERSE;
                    break;
                case 'f':
                    option |= FOLD;
                    break;
    	    case 'd':
    		option |= DIRECT;
    		break;
            default:
                printf("error: illegal option %c\n", c);
                argc = 1;
                break;
            }
	}
	else if (c == '-')
	    pos1 = atoi(*argv + 1);
	else if ((pos2 = atoi(*argv + 1)) < 0)
	    printf("error\n");
    }
    if (argc || pos1 > pos2) {
        printf("Usage: sort -fdnr -pos1 +pos2\n");
        rc = 1;
    } else
        if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
            if (option & NUMERIC)
                my_qsort((void **) lineptr, 0, nlines - 1,
                (int (*)(void *, void *)) numcmp);
            else
                my_qsort((void **) lineptr, 0, nlines - 1,
                (int (*)(void *, void *)) charcmp);
            writelines(lineptr, nlines, option & REVERSE);
        } else {
            printf("input too big to sort\n");
            rc = 1;
        }
    return rc;
}

#define MAXLEN 1000   /* max length of any input line */

int getline(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines, int reverse)
{
    if (reverse)
        while (nlines-- > 0)
            printf("%s\n", *(lineptr + nlines));
    else
        while (nlines-- > 0)
            printf("%s\n", *lineptr++);
}

/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

char *alloc(int n)  /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else      /* not enough room */
        return 0;
}

/* my_qsort:  sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)   /* do nothing if array contains */
        return;          /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last - 1, comp);
    my_qsort(v, last + 1, right, comp);
}

#include <stdlib.h>

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    char t1[MAXLEN], t2[MAXLEN];
    void substr(char *s1, char *s2);

    substr(t1, s1);
    substr(t2, s2);
    v1 = atof(t1);
    v2 = atof(t2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

#include <ctype.h>

/* charcmp:  return <0 if s1<s2, 0 if s1=s2, >0 if s1>s2 */
int charcmp(char *s1, char *s2)
{
    int fold = option & FOLD;
    int dir  = option & DIRECT;
    extern int pos1, pos2;
    char s, t, *t1, *t2;

    t1 = s1 + pos1;
    t2 = s2 + pos1;
    do {
	if (dir) {
	    while (!isalnum(*t1) && *t1 != ' ' && *t1 != '\0')
		t1++;
	    while (!isalnum(*t2) && *t2 != ' ' && *t2 != '\0')
		t2++;
	}
	s = (fold) ? tolower(*t1) : *t1;
	t1++;
	t = (fold) ? tolower(*t2) : *t2;
	t2++;
	if (s == '\0' && s == t)
	    return 0;
    } while (s == t && (t1 - s1) < pos2 && (t2 - s2) < pos2);
    return s - t;
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* substr: get a substring */
void substr(char *s1, char *s2)
{
    int i;
    extern int pos1, pos2;

    if (!pos2 || pos2 > strlen(s2))
	pos2 = strlen(s2);
    for (i = pos1; i < pos2; i++)
	*s1++ = *(s2 + i);
    *s1 = '\0';
}

