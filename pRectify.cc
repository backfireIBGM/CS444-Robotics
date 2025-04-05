#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
// Load left and right stereo images
    Mat leftImageColor  = imread("nvcamtest_11984_s00_00003.jpg");
    Mat rightImageColor = imread("nvcamtest_12058_s01_00003.jpg");

     cv::Mat leftImage,rightImage;
     cv::cvtColor(leftImageColor,leftImage, cv::COLOR_BGR2GRAY);
     cv::cvtColor(rightImageColor,rightImage, cv::COLOR_BGR2GRAY);

    imshow("left",leftImage);
    imshow("right",rightImage);

    if (leftImage.empty() || rightImage.empty()) {
        cout << "Error: Could not load stereo images!" << endl;
        return -1;
    }

 
// Camera parameters (intrinsic matrices)
       Mat cameraMatrix1 = (Mat_<double>(3,3) << 584.7110214378362, 0, 309.3584751309851,
                                                 0, 775.9928265718431, 201.2808235919595,
                                                  0,0,1);
        Mat cameraMatrix2 = (Mat_<double>(3,3) << 594.388935588237, 0, 320.4875022779982,
                                                  0, 789.9350531808199, 193.1161030497741,
                                                  0 ,0, 1);
  
        // Distortion coefficients
        Mat distCoeffs1 = (Mat_<double>(1, 5) << -0.1634478674188373, 1.13692367560844, -0.008013388948795832, -0.003440734640517225, -2.16937218407675);
        Mat distCoeffs2 = (Mat_<double>(1, 5) << -0.15831993845105781, 0.9545853146439264, -0.003136577286588905, -0.00450147348927946, -1.872148001614667);

//Rotation matrix R:
 Mat R = (Mat_<double>(3,3) << 0.9999249611524121, 0.001980748961238986, 0.01208919757054656,
                              -0.001974954295619306, 0.9999979291146271, -0.0004912453432377702,
                              -0.01209014556890748, 0.0004673328680807988, 0.9999268023111058);
//Translation vector T:
Mat T = (Mat_<double>(3,1) << -57.3178332594807,
                              -0.05226267397674714,
                              0.4095876280348906);
// Output rectification transforms, projection matrices, and disparity-to-depth mapping matrix
    Mat R1, R2, P1, P2, Q;
    
    // Compute rectification transforms
    stereoRectify(cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2, leftImage.size(), 
    R, T, R1, R2, P1, P2, Q, CALIB_ZERO_DISPARITY,-1,leftImage.size());
    
    // Compute undistortion and rectification maps
    Mat map1x, map1y, map2x, map2y;
    initUndistortRectifyMap(cameraMatrix1, distCoeffs1, R1, P1, leftImage.size(), CV_32FC1, map1x, map1y);
    initUndistortRectifyMap(cameraMatrix2, distCoeffs2, R2, P2, rightImage.size(), CV_32FC1, map2x, map2y);
    
    // Apply rectification
    Mat rectifiedLeft, rectifiedRight;
    remap(leftImage, rectifiedLeft, map1x, map1y, INTER_LINEAR);
    remap(rightImage, rectifiedRight, map2x, map2y, INTER_LINEAR);
    FileStorage fs("lookupTables.xml",FileStorage::WRITE);
    fs << "Map1x" << map1x;
    fs << "Map1y" << map1y;
    fs << "Map2x" << map2x;
    fs << "Map2y" << map2y;
    fs.release();
    
    // Display results
    imshow("Rectified Left Image", rectifiedLeft);
    imshow("Rectified Right Image", rectifiedRight);

   // Display original images
    imwrite("leftRectified.jpg", rectifiedLeft); 
    imwrite("rightRectified.jpg", rectifiedRight); 
    waitKey(0);
    return 0;
}

