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
			img.at<uchar>(i, j) = img.at<uchar>(i, j) / 3;			
		}
	}

/////use hw3-2 image(div3) to implement the algo
	int CDF[256]={0};
/////count  CDF
	for(int i = 0 ; i  < x ; i++){
		for(int j = 0 ; j < y ; j++){
			CDF[img.at<uchar>(i,j)]++;
		}
	}

	for(int i = 0 ; i  < 256 ; i++)
		CDF[i]+=CDF[i-1];
	
	int min,max;
	for(int i = 0 ; i < 256 ; i++){
		if(CDF[i]!=0){
			min = CDF[i];
			break;
		}
	}

/*	for (int i = 1; i < 256; i++) {
		if (CDF[i] > CDF[i-1]) {
			max = CDF[i];
		}
	}*/

	double s_k;
	Mat his_eq=img.clone();


	//(256-1) * round( (cdf(v) - cdfmin) / (M*N-cdfmin ) )
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			s_k = double(CDF[img.at<uchar>(i,j)] - min)/double(x*y - min);
			his_eq.at<uchar>(i,j) = floor(s_k*255);

		}
	}

	



	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			pixel_count[his_eq.at<uchar>(i,j)]++;			///count the number of every single pixel
		}
	}

	int max_count = 0;
	for (int i = 0; i < 256; i++)
		if (pixel_count[i] > max_count)
			max_count = pixel_count[i];


	Mat histogram(512, 512, CV_8UC1, Scalar(0));		///宣告一個新圖來製作histogram

	double scale=512.0 / max_count;						

	for (int i = 0; i < 256;i++) {
		int draw_pixel_count = (int)floor(pixel_count[i]*scale);
		for (int j = 0; j < draw_pixel_count;j++) {
			histogram.at<uchar>(512 - j - 1, i*2 ) = 255;
			histogram.at<uchar>(512 - j - 1, i * 2 + 1) = 255;
		}
	}

	imshow("lena", his_eq);
	imwrite("lena_eq.jpg", his_eq);
	imshow("histogram", histogram);
	imwrite("histgram_eq.jpg", histogram);
	waitKey(0);
	return 0;
}