#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

//IplImage* doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5);

using namespace std;

/*
// Using cvPyrDown() to create a new image that is half the width and height of the input image
IplImage* doPyrDown(IplImage* in, int filter = IPL_GAUSSIAN_5x5) {
 // Best to make sure input image is divisible by two.
 //
 //assert( in->width%2 == 0 && in->height%2 == 0 );

 IplImage* out = cvCreateImage ( 
 	cvSize( in->width/2, in->height/2 ),
 	in->depth,
 	in->nChannels
 );

 cvPyrDown( in, out );
 return( out );

}
*/

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

    // Set paramater & apply low pass filter for horseImage & zebraImage
    IplImage* apply_smoothLPF_horseIMG = cvCreateImage(cvSize(horseIMG_W, horseIMG_H), 8, 3);
    cvSmooth(horseIMG, apply_smoothLPF_horseIMG, CV_GAUSSIAN, 33, 0, 9.65, 0);
    IplImage* apply_smoothLPF_zebraIMG = cvCreateImage(cvSize(zebraIMG_W, zebraIMG_H), 8, 3);
    cvSmooth(zebraIMG, apply_smoothLPF_zebraIMG, CV_GAUSSIAN, 33, 0, 9.65, 0);

    // Save smooth LPF image for horse and zebra
    cvSaveImage("/home/shuping/CS510_Computer_vision/CS510_Computer_Vision_Project1/LowPassFilter/horseLPF.jpg", apply_smoothLPF_horseIMG);
    cvSaveImage("/home/shuping/CS510_Computer_vision/CS510_Computer_Vision_Project1/LowPassFilter/zebraLPF.jpg", apply_smoothLPF_zebraIMG);
    
    // Set paramater & apply high pass filter for horseImage & zebraImage

    // Combine two images (houre and zebra)
    //IplImage* hybird_image = cvCreateImage(cvSize(image_width, image_height), 8, 3);
    //cvAdd(result_1, result_2, hybird_image, NULL);

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










