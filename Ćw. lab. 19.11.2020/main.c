#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

struct Employee{
    char name[50];
    char surname[50];
    int age;
};

struct Employee* findEmployee(struct Employee empls[], char name[], int num){
    for(int i = 0; i < num; ++i){
        if(strcmp(empls[i].surname, name) == 0){
            return(&empls[i]);
        }
    }
    return NULL;
}



int main()
{
    struct Employee Janek = {"Jan","Kowalski",20};
    struct Employee Bartek = {"Bartosz","Nowak",19};
    struct Employee Kuba = {"Jakub","Dom",29};
    struct Employee Krzysiek = {"Krzysztof","Akasaa",59};

    struct Employee empls[4] = {Janek, Bartek, Kuba, Krzysiek};

    struct Employee *srh = findEmployee(empls, "Nowak", 4);
    printf("%s\n", srh->name);


    int z1 = 10;
    int z2 = 5;
    int* w1 = &z1;
    int* w2 = &z2;
    swap(w1,w2);
    printf("%d %d\n", z1,z2);

    /*
    int* l;
    const int b = 11;
    l = (int*)&b;
    printf("%d\n",*l);

    int** f;
    int* g;
    int h = 13;
    g = &h;
    f = &g;
    **f = 50;
    printf("%d\n", **f);*/

    /*mamy wskaŸnik do pocz¹tku i koñca tablicy oblicz ile elem:
      (od - do)  bez dzielenia przez rozmiar, bez *  */
    /* ró¿nice const* int w1 a const int* w1 a const* int* w1/*/

    /*void* t[10];
    void* t2 = t+10;
    printf("%d %d\n", t, t2);*/
    return 0;
}
