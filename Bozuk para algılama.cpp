
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/types_c.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat img;
	img = imread("C:\\Users\\DK\\Desktop\\para.jpeg");

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	medianBlur(gray, gray, 5); 
	vector<Vec3f> daire;
	HoughCircles(gray, daire, HOUGH_GRADIENT, 1,
		gray.rows / 8,  
		100, 30, 1, 120 
	);


	struct sort_pred {
		bool operator()(const Vec3f& left, const Vec3f& right) {
			return left[2] < right[2];
		}
	};


	std::sort(daire.rbegin(), daire.rend(), sort_pred()); 
	
	float enbuyuk_yaricap = daire[0][2];
	float sayac = 0;
	float oran; //oran tanımlanır.



	for (int i = 0; i < daire.size(); i++)
	{
		Vec3i c = daire[i];
		Point merkez = Point(c[0], c[1]);
		circle(img, merkez, 1, Scalar(0, 255, 255), 3, LINE_AA);
		int yaricap = c[2];
		circle(img, merkez, yaricap, Scalar(255, 0, 255), 3, LINE_AA);
		oran = ((yaricap * yaricap) / (enbuyuk_yaricap * enbuyuk_yaricap));

		if (oran >= 0.75)
		{
			putText(img, "1 tl", Point(merkez.x - yaricap, merkez.y + yaricap + 15), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 255, 255), 0.4, CV_AA);
			sayac = sayac + 1;

		}
		else if ((oran >= 0.60) && (oran < .75))
		{
			putText(img, "50 kurus", Point(merkez.x - yaricap, merkez.y + yaricap + 15), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 255, 255), 0.4, CV_AA);
			sayac = sayac + .50;

		}
		else if ((oran >= 0.45) && (oran < .60))
		{
			putText(img, "25 kurus", Point(merkez.x - yaricap, merkez.y + yaricap + 15), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 255, 255), 0.4, CV_AA);
			sayac = sayac + .25;

		}
		else if ((oran >= 0.30) && (oran < .45))
		{
			putText(img, "10 kurus", Point(merkez.x - yaricap, merkez.y + yaricap + 15), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 255, 255), 0.4, CV_AA);
			sayac = sayac + .10;

		}

	}

	putText(img, "Toplam Para:" + to_string(sayac), Point(img.cols / 10, img.rows - img.rows / 10), FONT_HERSHEY_COMPLEX_SMALL, 0.7, Scalar(0, 255, 255), 0.6, CV_AA);


	namedWindow("Goruntu", 0);
	imshow("Goruntu", img);

	waitKey();

	return 0;
}





