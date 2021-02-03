#include <stdio.h>

void jumpForward(char **p, int **m) {
    if(**m == 0){
        while(**p != ']'){
            (*p)++;
        }
    }
}

void jumpBackward(char **p){
    while(**p != '['){
        (*p)--;
    }
    (*p)--;
}

int main(int argc, char** argv) {
    if(argc != 2){
        printf("One argument required: patch to brainfuck code.\n");
        return 1;
    }

    int memory[1000];
    for(int i = 0; i < 1000; ++i){
        memory[i] = 0;
    }

    char program[1000];
    FILE *f = fopen(argv[1], "r");
    int k = 0;
    char c;
    c = fgetc(f);
    while(c != EOF){
        program[k] = c;
        c = fgetc(f);
        k++;
    }
    fclose(f);

    int* m = memory;
    char* p = program;

    while(*p != '\0'){
        switch(*p){
            case '+':
                (*m)++;
                break;
            case '-':
                (*m)--;
                break;
            case '>':
                m++;
                break;
            case '<':
                m--;
                break;
            case '.':
                putchar(*m);
                break;
            case ',':
                *m = getchar();
                break;
            case '[':
                jumpForward(&p, &m);
                break;
            case ']':
                jumpBackward(&p);
                break;
        }
        p++;
    }
    return 0;
}
