#include <stdio.h>
#include <stdlib.h>

int main()
{
    char w[4][100] = {"Ala","ma","kota","kot ma Alê"};
    int c;
    scanf("%d",&c);
    printf(w[c-1]);
    return 0;
}
