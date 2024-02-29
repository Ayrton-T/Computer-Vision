#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int pic[512][512];
int ero[512][512]={0};

int main()
{
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();
////kernel
	int kernel[5][5]={0,1,1,1,0,
					  1,1,1,1,1,
					  1,1,1,1,1,
					  1,1,1,1,1,
					  0,1,1,1,0};

	int x = lena.rows;
	int y = lena.cols;
////build a 0/1 array
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if(img.at<uchar>(i,j) >= 128 ) pic[i][j] = 1;
			else ero[i][j] = 0;
		}
	}
/////erosion
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j ++){
			int temp = 0;
			for(int k = 0 ; k < 5 ; k++){
				for(int l = 0 ; l < 5 ; l++){
					temp = temp + kernel[k][l]*pic[i+k][j+l];
				}
			}
			if(temp == 21) ero[i+2][j+2] = 255;			///same as kernel then you can keep
		}
	}

	Mat lena_erosion = img.clone();
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			lena_erosion.at<uchar>( i ,j ) = ero[i][j];
		}
	}


	imshow("lena_erosion", lena_erosion);
	imwrite("lena_erosion.jpg", lena_erosion);
	waitKey(0);
	return 0;
}