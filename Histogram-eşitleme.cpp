
#include <iostream>
#include <tchar.h>
#include <cstdlib>
#include <cmath>
#include <opencv2\opencv.hpp>
#include <stdint.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "opencv2\imgcodecs.hpp"
using namespace cv;
using namespace std;

using std::cout;
using std::cin;
using std::endl;

using namespace cv;

void imhist(Mat GrayScaleimg, int histogram[])
{
   
    for (int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }

    for (int y = 0; y < GrayScaleimg.rows; y++)
        for (int x = 0; x < GrayScaleimg.cols; x++)
            histogram[(int)GrayScaleimg.at<uchar>(y, x)]++;

}

void kumulatif_hist(int histogram[], int kmltfhistogram[]) 
{
    kmltfhistogram[0] = histogram[0];

    for (int i = 1; i < 256; i++)
    {
        kmltfhistogram[i] = histogram[i] + kmltfhistogram[i - 1];
    }
}

void histScreen(int histogram[], const char* name) 
{
    int hist[256];
    for (int i = 0; i < 256; i++)
    {
        hist[i] = histogram[i];
    }
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / 256);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    int max = hist[0];
    for (int i = 1; i < 256; i++) {
        if (max < hist[i]) {
            max = hist[i];
        }
    }

    
    for (int i = 0; i < 256; i++) {
        hist[i] = ((double)hist[i] / max) * histImage.rows;
    }


    for (int i = 0; i < 256; i++)
    {
        line(histImage, Point(bin_w * (i), hist_h),
            Point(bin_w * (i), hist_h - hist[i]),
            Scalar(0, 0, 0), 1, 8, 0);
    }
    imshow(name, histImage);
}



int main()
{

   	Mat RGBimg;  

	RGBimg = imread("C:\\Users\\DK\\Desktop\\lena.jpg"); //görüntü nesneye atandı.

	Mat GrayScaleimage(RGBimg.size(), CV_8UC1);  

   
	int rows = RGBimg.rows;
	int cols = RGBimg.cols;

	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			Vec3b intensity = RGBimg.at<Vec3b>(i, j); 
			int blue = intensity.val[0]; 
			int green = intensity.val[1];
			int red = intensity.val[2];

			GrayScaleimage.at<uchar>(i, j) = blue * 0.0722 + green * 0.7152 + red * 0.2126; 
		}

	}


    int histogram[256];
    imhist(GrayScaleimage, histogram);

    int size = GrayScaleimage.rows * GrayScaleimage.cols;
    float alpha = 255.0 / size;

    float intnsty[256];
    for (int i = 0; i < 256; i++)
    {
        intnsty[i] = (double)histogram[i] / size;
    }

    int kumulatifhistogram[256];
    kumulatif_hist(histogram, kumulatifhistogram);

    int Hst[256];
    for (int i = 0; i < 256; i++)
    {
        Hst[i] = cvRound((double)kumulatifhistogram[i] * alpha);
    }


    float intnstyEq[256];
    for (int i = 0; i < 256; i++)
    {
        intnstyEq[i] = 0;
    }

    for (int i = 0; i < 256; i++)
    {
        intnstyEq[Hst[i]] += intnsty[i];
    }

    int final[256];
    for (int i = 0; i < 256; i++)
        final[i] = cvRound(intnstyEq[i] * 255);


    Mat yeni_img = GrayScaleimage.clone();

    for (int y = 0; y < GrayScaleimage.rows; y++)
        for (int x = 0; x < GrayScaleimage.cols; x++)
            yeni_img.at<uchar>(y, x) = saturate_cast<uchar>(Hst[GrayScaleimage.at<uchar>(y, x)]);

    // Orijinal Görüntü
    namedWindow("Original Image");
    imshow("Original Image", GrayScaleimage);

    // Orijinal Histogram
    histScreen(histogram, "Original Histogram");

    // Eşitlenmiş görüntü
    namedWindow("Equilized Image");
    imshow("Equilized Image", yeni_img);

    // Eşitlenmiş Histogram
    histScreen(final, "Equilized Histogram");

    waitKey();
    return 0;
}




