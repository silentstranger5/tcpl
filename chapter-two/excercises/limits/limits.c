#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("values from standard headers:\n");
    printf("integer types:\n");
    printf("signed types:\n");
    printf("signed\t\tchar\tmin:\t%d\n", SCHAR_MIN);
    printf("signed\t\tchar\tmax:\t%d\n", SCHAR_MAX);
    printf("signed\t\tshort\tmin:\t%d\n", SHRT_MIN);
    printf("signed\t\tshort\tmax:\t%d\n", SHRT_MAX);
    printf("signed\t\tint\tmin:\t%d\n", INT_MIN);
    printf("signed\t\tint\tmax:\t%d\n", INT_MAX);
    printf("signed\t\tlong\tmin:\t%ld\n", LONG_MIN);
    printf("signed\t\tlong\tmax:\t%ld\n", LONG_MAX);
    printf("unsigned types:\n");
    printf("unsigned\tchar\tmax:\t%d\n", UCHAR_MAX);
    printf("unsigned\tshort\tmax:\t%d\n", USHRT_MAX);
    printf("unsigned\tint\tmax:\t%u\n", UINT_MAX);
    printf("unsigned\tlong\tmax:\t%lu\n", ULONG_MAX);
    printf("floating-point types:\n");
    printf("single\tprecision\tmin:\t%f\n", -FLT_MAX);
    printf("single\tprecision\tmax:\t%f\n", FLT_MAX);
    printf("double\tprecision\tmin:\t%f\n", -DBL_MAX);
    printf("double\tprecision\tmax:\t%f\n", DBL_MAX);
    printf("long\tdouble\tmin:\t%Lf\n", -LDBL_MAX);
    printf("long\tdouble\tmax:\t%Lf\n", LDBL_MAX);
    printf("values by direct computation:\n");
    printf("integer types:\n");
    printf("signed types:\n");
    printf("signed\t\tchar\tmin:\t%d\n",
            -(char)((unsigned char) ~0 >> 1));
    printf("signed\t\tchar\tmax:\t%d\n",
            (char)((unsigned char) ~0 >> 1));
    printf("signed\t\tshort\tmin:\t%d\n",
            -(short)((unsigned short) ~0 >> 1));
    printf("signed\t\tshort\tmax:\t%d\n",
            (short)((unsigned short) ~0 >> 1));
    printf("signed\t\tint\tmin:\t%d\n", 
            -(int)((unsigned int) ~0 >> 1));
    printf("signed\t\tint\tmax:\t%d\n",
            (int)((unsigned int) ~0 >> 1));
    printf("signed\t\tlong\tmin:\t%ld\n",
            -(long)((unsigned long) ~0 >> 1));
    printf("signed\t\tlong\tmax:\t%ld\n",
            (long)((unsigned long) ~0 >> 1));
    printf("unsigned types:\n");
    printf("unsigned\tchar\tmax:\t%u\n", (unsigned char) ~0);
    printf("unsigned\tshort\tmax:\t%u\n", (unsigned short) ~0);
    printf("unsigned\tint\tmax:\t%u\n", (unsigned int) ~0);
    printf("unsigned\tlong\tmax:\t%lu\n", (unsigned long) ~0);

    return 0;
}

