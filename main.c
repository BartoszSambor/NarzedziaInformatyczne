#include <stdio.h>
#include <math.h>


static int RandomNumbers[] = {87, 169, 59, 126, 149, 20, 47, 253, 67, 168, 17, 24, 202, 64, 247, 175, 218, 22,
                      198, 103, 201, 54, 26, 255, 28, 227, 157, 124, 252, 60, 156, 165, 213, 2, 96, 136,
                      154, 248, 192, 94, 233, 83, 113, 51, 142, 55, 215, 23, 171, 234, 1, 241, 68, 179,
                      245, 220, 145, 184, 35, 95, 7, 71, 44, 143, 222, 14, 110, 128, 164, 29, 38, 162,
                      40, 97, 185, 31, 137, 50, 65, 188, 116, 100, 84, 195, 238, 112, 88, 11, 173, 81,
                      63, 236, 129, 52, 3, 131, 106, 37, 151, 48, 178, 187, 39, 177, 114, 229, 190, 78,
                      144, 211, 121, 119, 172, 193, 101, 46, 135, 30, 42, 231, 86, 163, 57, 228, 45, 16,
                      196, 181, 212, 109, 250, 167, 73, 160, 15, 56, 125, 242, 199, 200, 21, 155, 225, 5,
                      251, 150, 10, 107, 18, 246, 219, 191, 244, 70, 13, 49, 221, 92, 122, 205, 4, 159, 166,
                      127, 120, 208, 74, 174, 210, 75, 176, 53, 161, 93, 132, 139, 85, 226, 180, 209, 104,
                      105, 194, 237, 152, 12, 90, 61, 117, 62, 19, 239, 153, 232, 189, 115, 141, 182, 217,
                      27, 36, 197, 66, 140, 89, 170, 77, 80, 118, 99, 69, 6, 243, 123, 254, 34, 214, 33,
                      130, 203, 158, 111, 207, 72, 148, 249, 240, 91, 204, 146, 108, 76, 25, 216, 206, 98,
                      224, 32, 0, 102, 9, 147, 134, 186, 41, 58, 183, 223, 43, 138, 8, 79, 230, 133, 82, 235};

int randomNumber(int x, int y, int seed){
    return (RandomNumbers[(x + RandomNumbers[y + seed])%256]);
}

float interpolate(float x, float y, float s){
    return (x + (y - x) * (s * s * (3 - 2 * s)));
}

float noise(float x, float y, int seed){
    seed %= 256;
    int xFloor = (int) x;
    int yFloor = (int) y;
    float xFraction = x - (float)xFloor;
    float yFraction = y - (float)yFloor;

    int corner00 = randomNumber(xFloor, yFloor, seed);
    int corner01 = randomNumber(xFloor, yFloor + 1, seed);
    int corner10 = randomNumber(xFloor + 1, yFloor, seed);
    int corner11 = randomNumber(xFloor + 1, yFloor + 1, seed);

    float y1Smooth = interpolate((float)corner00, (float)corner10, xFraction);
    float y2Smooth = interpolate((float)corner01, (float)corner11, xFraction);
    float xySmooth =  interpolate(y1Smooth, y2Smooth, yFraction);
    return xySmooth;
}

float noiseRecursive(int x, int y, float density, int depth, int seed){
    float result = 0;
    float value = 1.0f;
    for(int i = 0; i < depth; ++i){
        float xFloat = (float)x / density;
        float yFloat = (float)y / density;
        result += (noise(xFloat, yFloat, seed)-128) * value;
        density *= 2;
        value /= 2;
    }

    float m = 1.0f;
    if(depth > 1){
        float sum = 256 - (float)pow(2, 8 - depth);
        m = sum / 128.0f;
    }
    return (result/m)+128;
}

int main(void)
{
    const int SIZEX = 1024, SIZEY = 1024;
    int i, j;
    FILE *fp = fopen("out.ppm", "wb");
    fprintf(fp, "P6\n%d %d\n255\n", SIZEX, SIZEY);

    char buffer[1024][3];
    int index = 0;

    for (j = 0; j < SIZEY; ++j)
    {
        for (i = 0; i < SIZEX; ++i)
        {
            char value = (char) noiseRecursive(i, j, 56.65f, 3, 45);
            buffer[index][0] = value;
            buffer[index][1] = value;
            buffer[index][2] = value;
            index++;
        }
        (void) fwrite(buffer, 1024 * 3, 1, fp);
        index = 0;
    }
    fclose(fp);
    return 0;
}
