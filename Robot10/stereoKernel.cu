#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>
#include <limits.h>

__global__ void stereoKernel(unsigned char* left, unsigned char* right, unsigned char* depth,
                             double maxDistance, int rows, int cols){

// compute the row and col of the pixel to be processed
int col = blockIdx.x*blockDim.x + threadIdx.x;
int row = blockIdx.y*blockDim.y + threadIdx.y;

// put your stereo matching code here
// This code should only be for one pixel
// See the video I posted on acceleration stereo on the GPU

int L  = 9;
int w = (L - 1) / 2;
int ssd = 0;
int max_ssd = INT_MAX;
int diff = 0;
int disparity = 0;
int max_disp = 61;
int baseline = 60;
int focal_length = 700;
int max_distance = 5000;
int distance = 0;

for(int k = 0; k < max_disp; k++){
ssd = 0;
 for (int i = -w; i <= w; i++){
     for (int j = -w; j <= w; j++) {
     diff = left[(row+i)*cols+(col+j)] - right[(row+i)*cols+(col+j-k)];
     ssd += diff*diff;
     } 
 }
if (ssd < max_ssd){
  max_ssd = ssd;
  disparity = k;
}
}

//depth[row*cols+col] = (unsigned int)((disparity * 255) / max_disp);

if (disparity > 0) {
distance = (baseline * focal_length) / disparity;
  if(distance < max_distance)
    depth[row*cols+col] = (unsigned int)((distance * 255 ) / max_distance);
  else 
    depth[row*cols+col] = 255; 
}

else
  depth[row*cols+col] = 255;
}
