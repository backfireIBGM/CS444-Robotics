
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
  
  double vectorDotProduct(float* array1, float* array2, int n) {
      double result = 0.0;
      for (int i = 0; i < n; i++) {
          result += array1[i]*array2[i];
      }
      return result;
  }
  
  void vectorScaling(float* array1, int n, float scalar){
      float array2[] = {};
      cout << "Vector scaling function" << endl;
      for(int i = 0; i < n; i++) {
          array2[i] = scalar * array1[i];
          cout << array2[i] << endl;
      }
  }
  
  void vectorSubtract(float* array1, int n, float* array2, float* array3){
      cout << "Vector subtract function" << endl;
      for(int i=0; i<n; i++){
          array3[i]=array1[i]-array2[i];
          cout << array3[i] << endl;
          }
  }
  
  double vectorNorm(float* array1, int n){
      cout << "Vector norm function" << endl;
      double leng = 0.0;
      for(int i=0; i<n; i++){
          leng = leng + (pow(array1[i], 2));
      }
      return sqrt(leng);
  }