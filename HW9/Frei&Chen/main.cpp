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

	float op1[3][3] = {-1,-sqrt(2),-1,
					  0, 0, 0,
					  1  , sqrt(2), 1};
	float op2[3][3] = {-1    , 0, 1,
					 -sqrt(2), 0, sqrt(2),
					 -1      , 0, 1};

	int threshold = 30;


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			pic[i+1][j+1] = img.at<uchar>(i, j);
		}
	}

	for(int i = 0 ; i < x ; i++){
		pic[i+1][0] = pic[i+1][1];
		pic[i+1][514] = pic[i+1][513];
	}

	for(int j = 0 ; j < y ; j++){
		pic[0][j+1] = pic[1][j+1];
		pic[514][j+1] = pic[513][j+1];
	}

	pic[0][0] = pic[1][1];
	pic[514][0] = pic[513][1];
	pic[0][514] = pic[1][513];
	pic[514][514] = pic[513][513];

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			float temp1 = 0;
			for(int a = 0 ; a < 3 ; a++){
				for(int b = 0 ; b < 3 ; b++){
					temp1 += pic[i + 1 + a][j + 1 + b] * op1[a][b];
				}
			}
			float temp2 = 0;
			for(int a = 0 ; a < 3 ; a++){
				for(int b = 0 ; b < 3 ; b++){
					temp2 += pic[i + 1 + a][j + 1 + b] * op2[a][b];
				}
			}
			temp[i][j] = round(sqrt(temp1*temp1 + temp2*temp2));
		}
	}

	Mat lena_FreiandChen(512, 512, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if(temp[i][j] >= threshold) lena_FreiandChen.at<uchar>(i,j) = 0;
			else lena_FreiandChen.at<uchar>(i,j) = 255;
		}
	}

	imshow("lena_FreiandChen", lena_FreiandChen);
	imwrite("lena_FreiandChen.jpg", lena_FreiandChen);
	waitKey(0);
	return 0;
}