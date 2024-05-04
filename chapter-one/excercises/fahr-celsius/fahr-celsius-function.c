#include <stdio.h>

#define   LOWER  0      /* lower limit of table */
#define   UPPER  300    /* upper limit */
#define   STEP   20     /* step size */

float celsius(int fahr);

/* print Fahrenheit-Celsius table */
int main(void)
{
    int fahr;
    for (fahr = LOWER; fahr <= UPPER; fahr += STEP)
        printf("%3d %6.1f\n", fahr, celsius(fahr));
    return 0;
}

/* celsius:  return celsius equivalent to given fahrenheit value */
float celsius(int fahr)
{
    return (5.0 / 9.0) * (fahr - 32);
}

