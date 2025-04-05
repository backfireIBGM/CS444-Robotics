
#ifndef UTILS_H
#define UTILS_H
using namespace std;
void vectorPrint(float* u , int rows);
void vectorScale(float* u, int rows, float alpha , float* v);
double vectorDotProduct(float* array1, float* array2, int n);
void vectorScaling(float* array1, int n, float scalar);
void vectorSubtract(float* array1, int n, float* array2, float* array3);
double vectorNorm(float* array1, int n);

#endif