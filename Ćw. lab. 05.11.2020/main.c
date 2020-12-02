#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct S1{
        bool b; //
        double d; //
        char c; //
        int i; //
};
struct S2{
        double d; //
        int i; //
        bool b; //
        char c; //
};


void zadanie2(int tab[], int size){
    int *copy[size+1];

    for(int i = 0; i < size; ++i){
        copy[i] = tab[i];
    }
    copy[size] = 0;

    for(int i = 0; i < size+1; ++i){
        printf("%d\n", copy[i]);
    }

}

void zadanie1(){
    int tab[10] = {1,2,3,4,5,6,7,8,9,10};
    int size = sizeof(tab) / sizeof(tab[0]);
    int *copy[size];

    for(int i = 0; i < size; ++i){
        copy[i] = tab[i];
    }

    for(int i = 0; i < size; ++i){
        printf("%d\n", copy[i]);
    }

}

void zadanie3(){
    size_t k = 10000000000LU;
    int *c = malloc(k);
    if (NULL == c){
        printf("%s", "Nie uda³o siê");
    }
    free(c);
}

static enum dni {pon, wt, sr, czw, pt, sob, ndz};


int main()
{
   zadanie1();

   int tab[10] = {1,2,3,4,5,6,7,8,9,10};
   zadanie2(tab, 10);

   struct S1 a;
   struct S2 b;
   printf("%d\n", sizeof(a));
   printf("%d\n", sizeof(b));

   zadanie3();






    return 0;
}
