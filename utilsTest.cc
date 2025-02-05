#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <string>
#include <sstream>
#include "utils.h"

using namespace std;

int main(){

float u[] = {
	     1,
	     2,
	     3
           };

float v[] = {
             4,
             5,
             6 
           };


float c[] = {
  0, 0, 0, 0
  0, 0, 0, 0};

  int rows_c = 2;
  int cols_c 4;

 

  martrixMult(a, rows_a, cols_a, b, rows_b, cols_b, c);



// cols_a = rows_b


// [2 1] [1 2 3 4] = []
//  1 2   5 6 7 8



int rows = 3;
float alpha = 2.0;

vectorPrint(u, rows);

vectorScale(u,rows,alpha,v);
vectorPrint(v,rows);

}