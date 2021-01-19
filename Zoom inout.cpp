
#include <iostream>
#include <iostream>
#include <tchar.h>
#include <cstdlib>
#include <cmath>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

Mat img2, img1;
int a = 1;
const int zoom_slider_max = 30;

void zoom_trackbar(int, void*)
{
    img2 = Mat::zeros(img1.rows * a, img1.cols * a, CV_8UC3); 
    for (int i = 0; i < img1.cols; i++) 
    {
        for (int k = 0; k < img1.rows; k++)
        {
           
            Vec3b color1 = img1.at<Vec3b>(Point(i, k));
            for (int x = 0; x < a; x++) /
            {
                for (int b = 0; b < a; b++)
                {
                    Vec3b color2 = img2.at<Vec3b>(Point(i, k));
                    color2.val[0] = color1.val[0];
                    color2.val[1] = color1.val[1];
                    color2.val[2] = color1.val[2];

                    img2.at<Vec3b>(Point(i * a + x, k * a + b)) = color2;

                }
            }
        }
    }
    imshow("Scaled Image", img2);
    cout << "Goruntu yakinlastirma/uzaklastirma faktoru= " << a << endl;
}
int main()
{
    img1 = imread("C:\\Users\\DK\\Desktop\\cicek.png");
    if (!img1.data) { printf("img1 yuklenirken hata olustu \n"); }

    namedWindow("Scaled Image", WINDOW_AUTOSIZE);
    createTrackbar("Magnify", "Scaled Image", &a, zoom_slider_max, zoom_trackbar);
    zoom_trackbar(a, 0);

    imwrite("C:\\Users\\DK\\Desktop\\zoomed.png", img2);

    namedWindow("Orjinal Görüntü", WINDOW_AUTOSIZE);
    imshow("Orjinal Görüntü", img1);

    waitKey(0);
    return 0;
}