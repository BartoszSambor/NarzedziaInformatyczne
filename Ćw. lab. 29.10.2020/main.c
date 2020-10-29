#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void zadanie1(int argc, char* argv[]){
    for(int i = 0; i < argc; ++i){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
}

void zadanie2(int argc, char* argv[]){
    if( argc < 2){
        printf("Error in %s", argv[0]);
        abort();
    }
}

int zadanie3(int arg){
    return arg*arg*arg;
}

void zadanie4(char* a, char* b){
    printf("%s %s", a, b);
}

void zadanie5(char* a, char* b){
    static int counter = 0;
    printf("%s %s %d \n", a, b, ++counter);
}

int zadanie6(int b){
    int result = 1;
    for(int i = 1; i <= b; ++i){
        result *= i;
    }
    return result;
}

void zadanie7(int a){
    a *=2;
    printf("%d\n", a);
}

void zadanie8(int size, int tab[]){
    for(int i = 0; i < size; ++i){
            printf("Element number%d: %d\n", i, tab[i]);
    }
    for(int i = 0; i < size; ++i){
            tab[i] = 0;
    }
}

int main(int argc, char* argv[])
{
    zadanie1(argc, argv);

    zadanie2(argc, argv);

    printf("%d",zadanie3(4));

    zadanie4("[WARNING]", "Brak dostêpu");

    zadanie5("[WARNING]", "Brak dostêpu");
    zadanie5("[WARNING]", "Brak dostêpu");
    zadanie5("[WARNING]", "Brak dostêpu");

    printf("%d", zadanie6(10));

    int var = 10;
    zadanie7(var);
    printf("%d", var);


    int tab[] = {1,2,3,4,5,6,7};

    zadanie8(sizeof(tab)/sizeof(tab[0]), tab);
    for(int i = 0; i < sizeof(tab)/sizeof(tab[0]); ++i){
             printf("Element number%d: %d\n", i, tab[i]);
    }

    return 0;
}
