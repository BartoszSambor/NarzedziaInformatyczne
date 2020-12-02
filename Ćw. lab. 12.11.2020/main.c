#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zadanie1(){
    printf("%s\n", __TIME__);
    printf("%s\n", __DATE__);
    printf("%s\n", __func__);
    printf("%s\n", __FILE__);
}

int** zadanie2(int i, int j){
    int** tab = malloc(sizeof(int*)*i);
    for(int k = 0; k < j; ++k){
        tab[k] = malloc(sizeof(int)*(**tab));
    }
    tab[1][1] = 2;
    printf("%d\n", tab[1][1]);
    zwalnianie(tab, i);
}

void zwalnianie(int** tab, int size){
    for(int i = 0; i < size; ++i){
        free(tab[i]);
    }
    free(tab);
}

void suma(int** a, int** b, int x, int y){
    int** w[x][y];
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < y; ++j){
            w[i][j] = a[i][j] + b[i][j];
        }
    }
   // printf("%d", w[1][1]);
    return w;
}

char* zadanie3(char** tab){

}

char* zadanie4(char* wyrazy[], int size){
    char zdanie[100] = {};
    for(int i = 0; i < size; ++i){
        strcat(zdanie, wyrazy[i]);
        strcat(zdanie, " ");
    }
    return zdanie;
}

int main()
{
    zadanie1();
    zadanie2(3,3);

    int b[][2] = {{1,3},{4,5}};
    int a[][2] = {{1,3},{4,5}};
    int** s = suma(a,b, 2, 2);
    printf("%d", s[1][1]);

    char *wyrazy[] = {"Ala","ma","kota"};
    char* k = zadanie4(wyrazy, 3);
    printf("%s", k);


    return 0;
}
