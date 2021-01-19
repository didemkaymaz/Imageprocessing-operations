

#include <iostream>
#include <tchar.h>
#include <cstdlib>
#include <cmath>
#include <opencv2\opencv.hpp>
#include <stdint.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <stdio.h>


using namespace cv;
using namespace std;
typedef Vec<uchar, 3> Vec3b;
Mat RGBimg;
Mat img2;

int main(int argc, char** argv) {
	RGBimg = imread("C:\\Users\\DK\\Desktop\\istanbul.png");

	
	for (int i = 0; i < RGBimg.rows; i++) {
		for (int j = 0; j < RGBimg.cols; j++) {


			float blue = RGBimg.at<Vec3b>(i,j)[0];
			float green = RGBimg.at<Vec3b>(i, j)[1];
			float red = RGBimg.at<Vec3b>(i, j)[2];

			float hue;
			float sat;
			float V;
			float maxValue = max(max(red, green), blue); 
			float minValue = min(min(red, green), blue); 
			float delta = maxValue - minValue; 

			if (maxValue != 0)
			{
				sat = (delta * 255) / maxValue;
				if (delta != 0)
				{
					if (red == maxValue) {
						hue = 60 * (fmod(((green - blue) / delta), 6));
					}
					else if (green == maxValue) {
						hue = 120 + 60 * (((blue - red) / delta) + 2);
					}
					else {
						hue = 240 + 60 * (((red - green) / delta) + 4);
					}
					if (hue < 0) {
						hue = hue + 360;
					}
				}
				else {
					sat = 0;
					hue = 0;
				}
			}
			else {
				hue = 0;
				sat = 0;
			}
			float const ang0 = 0;
			float const ang255 = 255;
			RGBimg.at<Vec3b>(i, j)[0] = max(min(floor(maxValue), ang255), ang0);        
			RGBimg.at<Vec3b>(i, j)[1] = max(min(floor(sat), ang255), ang0);                 
			RGBimg.at<Vec3b>(i, j)[2] = max(min(floor(((hue * 255) / 360)), ang255), ang0); 



		}
	}
	
	namedWindow("HSV Image");
	imshow("HSV Image", RGBimg);
	/*namedWindow("RGB Image");
	imshow("RGB Image", img2);*/

	waitKey();
	return 0;
}
	

