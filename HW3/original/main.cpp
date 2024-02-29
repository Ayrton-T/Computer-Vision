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

	int pixel_count[256];

	for(int i=0;i<256;i++){
		pixel_count[i]=0;
	}

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			pixel_count[img.at<uchar>(i,j)]++;			///count the number of every single pixel
		}
	}

	int max_count = 0;
	for (int i = 0; i < 256; i++)
		if (pixel_count[i] > max_count)
			max_count = pixel_count[i];

	Mat histogram(512, 512, CV_8UC1, Scalar(0));		///宣告一個新圖來製作histogram

	double scale=512.0 / max_count;						///use this scale to print


	///i*2 不*2會全部擠在左邊 然後不連印兩行的話 看起來有點稀疏
	
	for (int i = 0; i < 256;i++) {
		int draw_pixel_count = (int)floor(pixel_count[i]*scale);
		for (int j = 0; j < draw_pixel_count;j++) {
			histogram.at<uchar>(512 - j - 1, i * 2) = 255;
			histogram.at<uchar>(512 - j - 1, i * 2 + 1) = 255;
		}
	}


	imshow("histogram", histogram);
	imwrite("histgram.jpg", histogram);
	waitKey(0);
	return 0;
}