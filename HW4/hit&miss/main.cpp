#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int pic1[512][512]={0};
int pic2[512][512]={0};
int img_J[512][512]={0};
int img_K[512][512]={0};

int main()
{
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();
////kernel
	int J_kernel[3][3]={0,0,0,
						1,1,0,
						0,1,0};
	int K_kernel[3][3]={0,1,1,
						0,0,1,
						0,0,0};

	int x = lena.rows;
	int y = lena.cols;

	Mat lena1 = img.clone();
	Mat lena2 = img.clone();
	Mat lena_HitMiss = img.clone();
////build a 0/1 array
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if (img.at<uchar>(i, j) >= 128) { 
				pic1[i][j] = 1;
				pic2[i][j] = 0;
			}
			else { 
				pic1[i][j] = 0;
				pic2[i][j] = 1;
			}
		}
	}


	for(int i = 0 ; i < x-2 ; i++){
		for(int j = 0 ; j < y-2 ; j++){
			int temp = 0;
			for(int k = 0 ; k < 3 ; k++){
				for(int l = 0 ; l < 3 ; l++){
					temp = temp + J_kernel[k][l]*pic1[i+k][j+l];
				}
			}
			if(temp == 3) img_J[i+1][j+1] = 1;
		}
	}
	for(int i = 0 ; i < x-2 ; i++){
		for(int j = 0 ; j < y-2 ; j++){
			int temp = 0;
			for(int k = 0 ; k < 3 ; k++){
				for(int l = 0 ; l < 3 ; l++){
					temp = temp + K_kernel[k][l]*pic2[i+k][j+l];
				}
			}
			if(temp == 3) img_K[i+1][j+1] = 1;
		}
	}


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if(img_J[i][j] == 1 && img_K[i][j] == 1) lena_HitMiss.at<uchar>( i ,j ) = 255;
			else lena_HitMiss.at<uchar>(i,j) = 0;
		}
	}


	imshow("lena_hit_and_miss", lena_HitMiss);
	imwrite("lena_hit_and_miss.jpg", lena_HitMiss);
	waitKey(0);
	return 0;
}