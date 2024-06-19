#include <stdarg.h>

/* minscanf:  minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
    va_list ap;	/* points to each unnamed arg in turn */
    char *p, *sval;
    int *ival;
    double *dval;

    va_start(ap, fmt);	/* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
	if (*p != '%') {
	    getchar();
	    continue;
	}
	switch (*++p) {
	case 'd':
	    ival = va_arg(ap, int *);
	    scanf("%d", ival);
	    break;
	case 'f':
	    dval = va_arg(ap, double *);
	    scanf("%lf", dval);
	    break;
	case 's':
	    sval = va_arg(ap, char *);
	    scanf("%s", sval);
	    break;
	default:
	    getchar();
	    break;
	}
    }
    va_end(ap);		/* clean up when done */
}
