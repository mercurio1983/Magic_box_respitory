#include "image.h"
#include "gpu_bayer.h"
#include <iostream>
#include <cv.h>

// includes CUDA Runtime
#include <cuda.h>
#include <cuda_runtime.h>

// includes Opencv Runtime
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/gpu/gpu.hpp>
#include <highgui.h>

using namespace cv;

void save_image(int w,int h,unsigned char* i1,char* input_filename){
	
	
	Mat img1(h,w,CV_8UC3,i1); //set frame to Mat format 
	//IplImage * Image1= cvCreateImage(cvSize(480,640),IPL_DEPTH_8U,3); 
	//IplImage *Image1= &img1;
	//IplImage Image1 = img1.operator IplImage();
	cvtColor(img1, img1, CV_RGB2BGR); //re doing the frame from BGR to RGB
	//printf("%s\n", input_filename);
	imwrite(input_filename, img1); //save the image
	//imwrite("Image_rgb.jpg", img1); //save the image
	//cvReleaseImage( &img1 ); //deleted image
	
	
	// Get the frame
	//Mat img;
	//img.data = i1;
    //img.rows = 640;
    //img.cols = 480;
    
 	//cvSaveImage("Image.jpg",Image1); // A JPG FILE IS BEING SAVED
                                    // OF 6KB , BUT IT IS BLACK
    //cvReleaseImage( &Image1 ); //deleted image                                
	//IplImage * Image1= cvCreateImage(cvSize(480,640),IPL_DEPTH_8U,3); 
	//Mat img2(964,1292*2,CV_8UC3,i1);
	//imwrite("Image_raw8.jpg", img1);
		
}



