#include <stdio.h>
#include <stdlib.h>
#include "Noise.h"

char** getArray(int i, int j){ //dont work
    char** tab = malloc(sizeof(char*)*i);
    for(int k = 0; k < j; ++k){
        tab[k] = malloc(sizeof(char)*(**tab));
    }
    return tab;
}

int writeNoiseToFile(char filename[], int SIZEX, int SIZEY, int mode, float density, int depth, int seed){
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", SIZEX, SIZEY);
    char buffer[1024][3];
    //char** buffer = getArray(1024, 3);
    int index = 0;

    for (int y = 0; y < SIZEY; ++y)
    {
        for (int x = 0; x < SIZEX; ++x)
        {
            char value;
            if(mode == 0){
                value = (char) noiseComplexRecursive(x, y, density, depth, seed);
            } else{
                value = (char) noiseSimpleRecursive(x, y, density, depth, seed);
            }

            buffer[index][0] = value;
            buffer[index][1] = value;
            buffer[index][2] = value;
            index++;
        }
        fwrite(buffer, 1024 * 3, 1, fp);
        index = 0;
    }
    free(buffer);
    fclose(fp);
    return 0;
}

int main(int argc, char** argv)
{
    if(argc <= 1){
        writeNoiseToFile("out.ppm", 1024, 1024, 0, 45.34f, 2, 23);
    } else if(argc == 8){
        char* filename = argv[1];
        int sizeX = atoi(argv[2]);
        int sizeY = atoi(argv[3]);
        int mode = atoi(argv[4]);
        float density = atof(argv[5]);
        int depth = atoi(argv[6]);
        int seed = atoi(argv[7]);
        writeNoiseToFile(filename, sizeX, sizeY, mode, density, depth, seed);
    } else{
        return 2;
    }
}
