#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	MAXLINE	1000	/* maximum input line length */

/* find:  print lines that match pattern from 1st argument */
int main(int argc, char *argv[])
{
    char pattern[MAXLINE];
    int c, except = 0, number = 0;
    FILE *fp;
    void fpat(FILE *, char *, char *, int, int);

    while (--argc > 0 && **++argv == '-')
	while (c = *++*argv)
	    switch(c) {
	    case 'x':
		except = 1;
		break;
	    case 'n':
		number = 1;
		break;
	    default:
		printf("find: illegal option %c\n", c);
		argc = 0;
		break;
	    }
    if (argc >= 1)
	strcpy(pattern, *argv);
    else {
	printf("Usage: find [-x] [-n] pattern [file ...]\n");
	exit(1);
    }
    if (argc == 1)
	fpat(stdin, "stdin", pattern, except, number);
    else
	while (--argc > 0)
	    if ((fp = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "find: can't open %s\n",
			*argv);
		exit(1);
	    } else {
		fpat(fp, *argv, pattern, except, number);
		fclose(fp);
	    }
    exit(0);
}

/* fpat:  find pattern */
void fpat(FILE *fp, char *fname, char *pattern,
	  int except, int number)
{
    char line[MAXLINE];
    int lineno = 0;

    while (fgets(line, MAXLINE, fp) != NULL) {
	lineno++;
	if ((strstr(line, pattern) != NULL) != except) {
	    printf("%s\t", fname);
	    if (number)
		printf("%d:", lineno);
	    printf("%s", line);
	}
    }
}
