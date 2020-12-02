#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen("liczby.txt", "rw");
    int tab[] = {2,4,6,3,7,2,5};
    if (fp == NULL)
    {
        printf("plik niedostepny\n");
        exit(1);
    }
    int i = 0;
    float suma=0,a;
    for(i = 0; i< 10; ++i){
        fprintf(fp, "%d ", tab[i]);
    }

    while (fscanf(fp, "%lf", &a) == 1){
        suma+=1;
        i++;
    }
    printf("%f", suma/i);
    fclose(fp);
    return 0;

    const char prefix[] = "pp";
    for(int i = 0; i < argc; ++i){
        char newname[100];
        strcpy(newname, prefix);
        strcat(newname, argv[i]);
        rename(argv[i], newname);
    }
    return 0;

    const char badword[] = "pies";
    const char filename[] = "data.txt";
    FILE *fp = fopen(filename, "r");
    if ( fp == NULL){
        printf("ERROR\n");
        exit(1);
    }

    char a[100];
    while (fscanf(fp, "%s", &a) == 1){
        if(!strcmp(a, badword)){
            printf("Bad word found.\n");
            fclose(fp);
            remove(filename);
            exit(0);
        }
     }
    fclose(fp);
    return 0;*/
}
