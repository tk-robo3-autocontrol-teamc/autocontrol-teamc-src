#include <stdio.h>
#include "fnc.h"

int main(int argc, char **argv)
{
    double d1, d2, d3;
    double a = 1.2, b = 3.4, c = 2.7;

    d1 = avg(a, b);
    d2 = avg(b, c);
    d3 = avg(c, a);

    printf("d1=%f, d2= %f, d3=%f\n", d1, d2, d3);

    return 0;
}