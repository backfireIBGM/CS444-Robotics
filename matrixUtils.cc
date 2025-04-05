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
//Print matrix function
void matrixPrint(float* matrix, int rows, int cols) {
printf("number of rows and cols,%d %d \n", rows, cols);
for (int row = 0; row < rows; row++) {
for (int col = 0; col < cols; col++) {
printf("%6.5f ",matrix[row*cols + col]);
}
printf("\n");
}
printf("\n");
}
// Matrix Product Function
void matrixProduct(float* a, int rows_a, int cols_a, float* b, int rows_b, int
cols_b, float* c){
int index = 0;
int rows = rows_a;
int cols = cols_b;
if(cols_a == rows_b){
for(int row = 0; row < rows; row++){
for(int col = 0; col < cols; col++){
index = row*cols + col;
c[index] = 0.0;
for(int k = 0; k < cols_a; k++){
c[index]=c[index]+a[row*cols_a + k]*b[col+k*cols_b];
}
}
}
}else{
printf("Can't multiply. Dimensions incorrect \n");
exit(0);
}
}
// MATRIX VECTOR MULTIPLICATION FUNCTION
void matrixTimesVector(float* a, int rows, int cols, float* v, int rows_v, float*
w){
if(cols==rows_v){
for( int row = 0; row < rows; row++){
w[row]=0.0;
for( int col = 0;col < cols;col++){
w[row]=w[row]+a[row*cols+col]*v[col];
}
}
}else{
printf(" dimensions don't match \n");
exit(0);
}
}
// MATRIX TRANSPOST FUNCTION
void matrixTranspose(float* a, int rows, int cols, float* aTranspose){
for( int row = 0; row < rows; row++){
for( int col = 0;col < cols;col++){
aTranspose[col*rows+row] = a[row*cols+col];
}
}
}
// MATRIX COLUMN EXTRACTION FUNCTION
void matrixExtractCol(float*a, int rows, int cols, int col, float* column){
int index;
for(int row=0;row<rows;row++){
index = col + row*cols;
column[row] = a[index];
}
}
// 	MATRIX BACK SUBSTITUTION FUNCTION
void matrixBackSubstitution(float* R, int rows, int cols, float* d, float* p){
//solve Rp=d for an uppertriangular matrix R
// using back substitution
for (int j = cols-1; j > -1; j--){
p[j]=d[j];
for(int k = j+1; k < cols; k++){
p[j]= p[j] - R[j*cols + k]*p[k];
}
p[j]=p[j]/R[j*cols+j];
}
}
// MATRIX UPPER TRIANGULAR
void matrixUpperTriangularInverse(float* A, int rows, int cols, float* invA){
// This code computes the inverse of a non-singular upper triangular 3x3 matrix.
if(rows !=3 || cols !=3){
printf(" Only 3x3 full rank upper triangle matricies can be inverted with this code\n");
exit(0);
}
for(int row = 0; row < rows; row++){
for(int col= 0;col < cols; col++){
invA[ row*cols + col] = 0.0;
}
}
invA[0*cols+0]=1.0/A[0*cols+0];
invA[1*cols+1]=1.0/A[1*cols+1];
invA[2*cols+2]=1.0/A[2*cols+2];
invA[0*cols+1]=-A[0*cols+1]*invA[1*cols+1]/A[0*cols+0];
invA[1*cols+2]=-A[1*cols+2]*invA[2*cols+2]/A[1*cols+1];
invA[0*cols+2]=-( A[0*cols+1]*invA[1*cols+2] + A[0*cols+2]*invA[2*cols+2]
)/A[0*cols+0];
}
void matrixQR(float* matrixA, int n, int m, float* q, float* r) {
    // matrixA is of size n x m
    // q is of size n x n (resulting orthogonal matrix Q)
    // r is of size n x m (resulting upper triangular matrix R)
    cout << "Testing QR Decomposition" << endl;
    // Initialize q and r matrices
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            r[i * m + j] = matrixA[i * m + j];  // Copy A into R
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            q[i * n + j] = 0.0f;  // Initialize Q with zeros
        }
    }

    for (int i = 0; i < m; ++i) {
        // First compute the norm of the current column of A (for orthogonalization)
        float norm = 0.0f;
        for (int j = 0; j < n; ++j) {
            norm += r[j * m + i] * r[j * m + i];
        }
        norm = sqrtf(norm);

        // Set the i-th column of Q
        for (int j = 0; j < n; ++j) {
            q[j * n + i] = r[j * m + i] / norm;
        }

        // Orthogonalize the rest of the columns of R
        for (int j = i + 1; j < m; ++j) {
            float dotProduct = 0.0f;
            for (int k = 0; k < n; ++k) {
                dotProduct += r[k * m + i] * r[k * m + j];
            }

            // Subtract the projection of the i-th column of R from the j-th column of R
            for (int k = 0; k < n; ++k) {
                r[k * m + j] -= dotProduct * q[k * n + i];
            }
        }
    }

    // Now, the R matrix is upper triangular, and Q is orthogonal.
}
void matrixInternalCameraParameters(float* p,int rows,int cols,float* k){
float pSub[9];
float r[9];
float rInv[9];
float q[9];
float qT[9];
float b[9];
// extract a 3x3 sub matrix of p
for (int row=0; row < rows; row++){
for (int col=0; col<cols-1;col++){
pSub[row*(cols-1)+col]=p[row*cols+col];
}
}

printf("3x3 submatrix of p\n");
matrixPrint(pSub,3,3);
// find the inverse of pSub with QR decomposition
// Its inverse is B=RInv*QTranspose
matrixQR(pSub,3,3,q,r);
matrixTranspose(q,3,3,qT);
matrixUpperTriangularInverse(r,3,3,rInv);
matrixProduct(rInv,3,3,qT,3,3,b);
int rows_k = rows;
int cols_k = rows_k;
int rows_r = rows;
int cols_r = rows_r;
//diagonals of calibration matirx
k[0*cols_k +0] = 1/r[0*cols_r+0];
k[1*cols_k +1] = 1/r[1*cols_r+1];
k[2*cols_k +2] = 1.0;
// off diagonals of the calibration matrix
k[0*cols_k +2] = -r[0*cols_r +2]/r[0*cols_r+0];
k[1*cols_k +2] = -r[1*cols_r +2]/r[1*cols_r+1];
}
