#include <stdio.h>
#include <stdlib.h>

void zadanie1(){
     for (int i =1;i<=10;i++){
        printf("%d\n",i);
    }
    return 0;
}

void zadanie2(){
    for (int i =10;i>=2;i-=2){
        printf("%d\n",i);
    }
    return 0;
}

void zadanie3(){
    int a[] = {1,2,54,34,2,656,4,12,21,21,212,4354,53,211,2,4343};
    int b = 0;
    for (int i=0;i<sizeof(a)/4;++i){
        if(a[i]==2){
            b = 1;
            break;
        }
    }

    b == 1 ? printf("Jest") : printf("Nie jest");
}

void zadanie4(){
    int a[] = {1,2,3,4,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int s = 6;
    int left = 0, right = sizeof(a)/sizeof(a[0]);
    int d;
    while (left<right)
    {
        if (a[(left+right)/2]>s){
            right = (left+right)/2;
        } else if(a[(left+right)/2]<s){
            left = (left+right)/2+1;
        } else if(a[(left+right)/2]==s){
            d = 1;
            break;
        }
    }
    d == 1 ? printf("Jest") : printf("Nie ma");
}

void zadanie5(){
    char a[] = "dsdstaldjkjktakjjwyrazestisdsds";
    char b[] = "wyraz";

    for(int i=0;i<=(sizeof(a)-sizeof(b));i++){

        int result = 1;
        for(int j=0;j<sizeof(b)-1;j++){
            if(a[i+j]!=b[j]){
                result = 0;
            }
        }

        if(result==1){
            printf("jest");
            break;
        }
    }
}

void zadanie6(){
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int b[] = {1,2,3,4,5,6,7,8,9,10};
    for (int i=0;i<10;i++){
        for (int j=0;j<10;j++){
            printf("%d ",a[i]*b[j]);
        }
        printf("\n");
    }

}


int main()
{
    return 0;
}
