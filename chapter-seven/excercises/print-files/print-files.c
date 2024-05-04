#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINE	100	/* maximum size of one line */
#define MAXPAGE	66	/* maximum # lines on one page */

/* print:  print files - each new one on a new page */
int main(int argc, char *argv[])
{
    FILE *fp;
    char *prog = *argv;
    void fileprint(FILE *, char *);

    if (argc == 1)
	fileprint(stdin, "stdin");
    else
	while (--argc > 0) {
	    if ((fp = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr, "%s: can't open %s\n", prog, *argv);
		exit(1);
	    } else {
		fileprint(fp, *argv);
		fclose(fp);
	    }
	}
    exit(0);
}

/* fileprint:  print file */
void fileprint(FILE *fp, char *fname)
{
    int lineno, pageno = 1;
    char line[MAXLINE];
    int heading(char *, int);

    lineno = heading(fname, pageno++);
    while (fgets(line, MAXLINE, fp) != NULL) {
	if (lineno == 1) {
	    fputc('\f', stdout);
	    lineno = heading(fname, pageno);
	}
	fputs(line, stdout);
	if (++lineno > MAXPAGE)
	    lineno = 1;
    }
    while (++lineno < MAXPAGE)
	fputc('\n', stdout);
    fputc('\f', stdout);
}

/* heading:  put heading */
int heading(char *fname, int pageno)
{
    int lineno = 3;
    time_t ltime;
    char s[30];

    time(&ltime);
    strftime(s, 30, "%b %d %R %Y", localtime(&ltime));
    fprintf(stdout, "\n\n");
    fprintf(stdout, "%s\t%s\tPage %d", s, fname, pageno);
    while (lineno++ < 6)
	fprintf(stdout, "\n");
    return lineno;
}
