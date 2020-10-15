#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tab[] = {1,2,3};
    printf("%d\n",tab[3]);
    tab[4] = 323;
    printf("%d",tab[4]);
    scanf("%d",&tab[5]);
    return 0;
}
