

#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;




void convolution(Mat GrayScaleimage, Mat img2, float Kernel[][3])
{
 
    float toplam; 
    for (int y = 1; y < GrayScaleimage.rows - 1; y++) {
        for (int x = 1; x < GrayScaleimage.cols - 1; x++) {
            toplam = 0.0;
            for (int k = -1; k <= 1; k++) {
                for (int j = -1; j <= 1; j++) {
                    toplam = toplam + Kernel[j + 1][k + 1] * GrayScaleimage.at<uchar>(y - j, x - k);
                }
            }
            img2.at<uchar>(y, x) = toplam;
        }
    }
}


int main()
{

    Mat src, img;
    src = imread("C:\\Users\\DK\\Desktop\\image.png");

 
    Mat GrayScaleimage(src.size(), CV_8UC1);
    int rows = src.rows;
    int cols = src.cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b intensity = src.at<Vec3b>(i, j);
            int blue = intensity.val[0];
            int green = intensity.val[1];
            int red = intensity.val[2];
            GrayScaleimage.at<uchar>(i, j) = blue * 0.0722 + green * 0.7152 + red * 0.2126;
        }
    }


    if (!GrayScaleimage.data)
    {
        return -1;
    }


    float Kernel[3][3] = {
                          {1 / 8.0, 1 / 8.0, 1 / 8.0},
                          {1 / 8.0, 1 / 8.0, 1 / 8.0},
                          {1 / 8.0, 1 / 8.0, 1 / 8.0}
    };

    img = GrayScaleimage.clone();
    for (int y = 0; y < GrayScaleimage.rows; y++)
        for (int x = 0; x < GrayScaleimage.cols; x++)
            img.at<uchar>(y, x) = 0.0;

    convolution(GrayScaleimage, img, Kernel);



    namedWindow("konvolusyon");
    imshow("konvolusyon", img);

    namedWindow("Gri olcekli goruntu");
    imshow("Gri olcekli goruntu", GrayScaleimage);

    waitKey();


    return 0;
}