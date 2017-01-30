//  Filename: main.cpp
//  CS510 Computer Vision Project1 - Hybrid Image Synthesis
//
//  Created by Shu-Ping Chu on 1/14/17.
//  Copyright (c) 2017 Shu-Ping Chu. All rights reserved.

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>


using namespace std;

// Using cvPyrDown() to create a new image that is half the width and height of the input image
IplImage* doPyrDown(IplImage* in) {
 // Best to make sure input image is divisible by two.
 //
 //assert( in->width%2 == 0 && in->height%2 == 0 );
 IplImage* out = cvCreateImage (cvSize( in->width/2, in->height/2 ), in->depth, in->nChannels);
 cvPyrDown( in, out );

 return( out );

}

int main(int argc, const char * argv[]) {
    // Structure IplImage: OpenCV uses this structure to handle all kinds of images: single-channel, 
    // 			   multichannel, integer-valued, fl oating-point-valued, et cetera
    // Load image from command line
    IplImage* horseIMG = cvLoadImage(argv[1]);
    IplImage* zebraIMG = cvLoadImage(argv[2]);

    // Get image weigh and heigh
    int horseIMG_H = horseIMG->height;
    int horseIMG_W = horseIMG->width;
    int zebraIMG_H = zebraIMG->height;
    int zebraIMG_W = zebraIMG->width;

    // Set paramater for horseIMG
    IplImage* apply_smoothLPF_horseIMG = cvCreateImage(cvSize(horseIMG_W, horseIMG_H), 8, 3);

    // Apply low pass filter for horseImage by using Gaussian filter
    cvSmooth(horseIMG, apply_smoothLPF_horseIMG, CV_GAUSSIAN, 33, 0, 8.65, 0);

    // Save smooth LPF image for horse
    IplImage* out_horseIMG = apply_smoothLPF_horseIMG;
    cvSaveImage("/home/shuping/CS510_Computer_vision/CS510_Computer_Vision_Project1/out_pic/horseLPF.jpg", out_horseIMG);
    
    // Set paramater for zebraIMG
    IplImage* channelRed = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* channelGreen = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* channelBlue = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* out_zebraIMG = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 3);

    // Spilt image zebraIMG into three channels R, G, B
    cvSplit(zebraIMG, channelRed, channelGreen, channelBlue, NULL);

    // Apply high pass filter for zebraImage by using Gaussian filter
    IplImage* apply_smoothLPF_zebraIMG_channelRed = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* apply_smoothLPF_zebraIMG_channelGreen = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* apply_smoothLPF_zebraIMG_channelBlue = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    cvSmooth(channelRed, apply_smoothLPF_zebraIMG_channelRed, CV_GAUSSIAN, 33, 0, 8.65, 0);
    cvSmooth(channelGreen, apply_smoothLPF_zebraIMG_channelGreen, CV_GAUSSIAN, 33, 0, 8.65, 0);
    cvSmooth(channelBlue, apply_smoothLPF_zebraIMG_channelBlue, CV_GAUSSIAN, 33, 0, 8.65, 0);

    // Apply subtract image into three channels R, G, B
    IplImage* subtractIMG_channelRed = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* subtractIMG_channelGreen = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    IplImage* subtractIMG_channelBlue = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 1);
    cvSub(channelRed, apply_smoothLPF_zebraIMG_channelRed, subtractIMG_channelRed, NULL);
    cvSub(channelGreen, apply_smoothLPF_zebraIMG_channelGreen, subtractIMG_channelGreen, NULL);
    cvSub(channelBlue, apply_smoothLPF_zebraIMG_channelBlue, subtractIMG_channelBlue, NULL);

    // Merge all three channels R,G, B into an outIMG
    cvMerge(subtractIMG_channelRed, subtractIMG_channelGreen, subtractIMG_channelBlue, NULL, out_zebraIMG);

    // Save smooth HPF image for zebra
    cvSaveImage("/home/shuping/CS510_Computer_vision/CS510_Computer_Vision_Project1/out_pic/zebraHPF.jpg", out_zebraIMG);

    // Combine with high pass filter image and low pass filter image
    IplImage* hybirdIMG = cvCreateImage(cvSize(horseIMG_W, horseIMG_H), 8, 3);
    cvAdd(out_horseIMG, out_zebraIMG, hybirdIMG, NULL);

    // Half size
    // IplImage* halfIMG = doPyrDown(hybirdIMG);

    // Save hybridIMG
    cvSaveImage("/home/shuping/CS510_Computer_vision/CS510_Computer_Vision_Project1/out_pic/hybird.jpg", hybirdIMG);
    

    //img = doPyrDown(img);
/*
    // Opens a window on the screen that can contain and display an image, CV_WINDOW_AUTOSIZE will set 
    // window size to as same as image size
    cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );

    // Window will be redrawn with the appropriate image and the window will resize 
    // itself as appropriate if it was created using the CV_WINDOW_AUTOSIZE fl ag
    cvShowImage( "Example1", apply_smoothLPF_hourseIMG );

    // Will asks the program to stop and wait for a keystroke in milliseconds, wait indefi nitely for a keypress
    cvWaitKey(0);

    // Free the allocated memory, set to null
    cvReleaseImage( &apply_smoothLPF_hourseIMG );

    // Destroy the window itself
    cvDestroyWindow( "Example1" );
*/

}

// command line: g++ -g main.cpp `pkg-config --cflags --libs opencv`
//               ./a.out VM.png










