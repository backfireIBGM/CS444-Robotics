#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

void vectorPrint(float* u , int rows){
   for(int i=0;i<rows;i++){
    printf( "%7.1f \n",u[i]);
  }
  printf("\n");

}

void vectorScale(float* u, int rows, float alpha , float* v){
  for(int i=0; i<rows; i++){
    v[i]=alpha*u[i];
  }
}

 void matrixMult(float a, int rows_a, int cols_a, float* b, int rows_b, int cols_b, float* c) {

}

// index_b = col + cols_b * k
// iner-loop for k = 0 : rows_b, k++
// index_c = row * col_b + k
// c[index] = c[index] + a[index] + b[index]

if (cols_a == rows_b) {
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {

    }
  }
}

for (row = 0; rows_a; row++)
{
  for (col = 0; col < cols_b; cols++)
  {
    for (k = 0; k < cols_a; k++)
    {
      
    }
  }
}