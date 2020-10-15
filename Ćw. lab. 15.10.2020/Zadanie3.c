#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);
    float d = ((b*b)-(4*a*c));
    d = sqrt(d);
    float x1,x2;
    x1 = ((-b-d)/(2*a));
    x2 = ((-b+d)/(2*a));
    printf("%f %f",x1,x2);

    return 0;
}
