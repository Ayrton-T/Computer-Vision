#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int x = lena.rows;
	int y = lena.cols;


	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (img.at<uchar>(i, j) < 128) {
				img.at<uchar>(i, j) = 0;
			}
			else {
				img.at<uchar>(i, j) = 255;
			}
		}
	}


	imshow("Binarized", img);
	imwrite("Binarized.jpg", img);

	waitKey(0);
	return 0;
}