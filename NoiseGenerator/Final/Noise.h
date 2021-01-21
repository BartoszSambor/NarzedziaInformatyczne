#ifndef NOISEGENERATORFINAL_NOISE_H
#define NOISEGENERATORFINAL_NOISE_H


static int RandomNumbers[256]; //pre generated array of random heights
int randomNumber(int x, int y, int seed); //function that get coords and return pre generated random height

float interpolate(float x, float y, float s); //function with derivative equal to 0 for arguments 1 and 0
float dotScalar(int ix, int iy, float x, float y, int seed); //return scalar products of random vectors based on coords

float noiseSimple(float x, float y, int seed); //just noise function
float noiseSimpleRecursive(int x, int y, float density, int depth, int seed); //call noise functions a few time to get better results

float noiseComplex(float x, float y, int seed); //better but slower noise because sin() and cos() was used
float noiseComplexRecursive(int x, int y, float density, int depth, int seed); //call noise functions a few time to get better results


#endif //NOISEGENERATORFINAL_NOISE_H
