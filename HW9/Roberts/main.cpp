#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<iostream>
#include<vector>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int pic[514][514] = {0};
int temp[512][512] = {0};

int main(){
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int x = img.rows;
	int y = img.cols;

	int op1[2][2] = {-1,0,
					 0,1};
	int op2[2][2] = {0,-1,
					1,0};

	int threshold = 12;


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			pic[i+1][j+1] = img.at<uchar>(i, j);
		}
	}

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			int temp1 = 0;
			for(int a = 0 ; a < 2 ; a++){
				for(int b = 0 ; b < 2 ; b++){
					temp1 += pic[i + 1 + a][j + 1 + b] * op1[a][b];
				}
			}
			int temp2 = 0;
			for(int a = 0 ; a < 2 ; a++){
				for(int b = 0 ; b < 2 ; b++){
					temp2 += pic[i + 1 + a][j + 1 + b] * op2[a][b];
				}
			}
			temp[i][j] = round(sqrt(temp1*temp1 + temp2*temp2));
		}
	}

	Mat lena_Roberts(512, 512, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if(temp[i][j] >= threshold) lena_Roberts.at<uchar>(i,j) = 0;
			else lena_Roberts.at<uchar>(i,j) = 255;
		}
	}

	imshow("lena_Roberts", lena_Roberts);
	imwrite("lena_Roberts.jpg", lena_Roberts);
	waitKey(0);
	return 0;
}