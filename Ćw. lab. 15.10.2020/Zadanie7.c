#include <stdio.h>
#include <stdlib.h>

int main()
{
    int s;
    char k;
    scanf("%d %c",&s,&k);
    if(k=='c'){
        printf("%d\n",s+273);
    }else if (k=='k'){
        printf("%d\n",s-273);
    } else {
        printf("B³¹d");
    }
    return 0;
}
