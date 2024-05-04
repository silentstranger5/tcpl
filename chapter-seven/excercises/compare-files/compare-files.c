#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    void filecomp(FILE *, FILE *);

    if (argc != 3) {
	printf("Usage: compare-files file1 file2\n");
	exit(1);
    } else if ((fp1 = fopen(*++argv, "r")) == NULL) {
	printf("Failed to open file %s\n", *argv);
	exit(2);
    } else if ((fp2 = fopen(*++argv, "r")) == NULL) {
	printf("Failed to open file %s\n", *argv);
	exit(2);
    } else {
	filecomp(fp1, fp2);
	fclose(fp1);
	fclose(fp2);
        exit(0);
    }
}

#define MAXLINE 1000

void filecomp(FILE *fp1, FILE *fp2)
{
    char line1[MAXLINE], line2[MAXLINE];
    char *lp1, *lp2;

    do {
	lp1 = fgets(line1, MAXLINE, fp1);
	lp2 = fgets(line2, MAXLINE, fp2);
	if (lp1 == line1 && lp2 == line2) {
	    if (strcmp(line1, line2) != 0) {
		printf("%s%s", line1, line2);
		lp1 = lp2 = NULL;
	    }
	} else if (lp1 != line1 && lp2 == line2)
	    printf("EOF\n%s", line2);
	else if (lp1 == line1 && lp2 != line2)
	    printf("%sEOF\n", line1);
    } while (lp1 == line1 && lp2 == line2);
}
