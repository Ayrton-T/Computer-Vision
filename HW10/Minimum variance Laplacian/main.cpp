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

int pic[516][516] = {0};
int temp[514][514] = {0};

int main(){
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int x = img.rows;
	int y = img.cols;

	int mask[3][3] = { 2,-1, 2,
					  -1,-4,-1,
					   2,-1, 2 };

	int threshold = 20;


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
			float temp0 = 0;
			for(int a = -1 ; a < 2 ; a++){
				for(int b = -1 ; b < 2 ; b++){
					temp0 += pic[i + 1 + a][j + 1 + b] * mask[a+1][b+1];
				}
			}
			if (temp0/3 >= threshold) temp[i+1][j+1] = 1;
			else if (temp0/3 <= -threshold) temp[i+1][j+1] = -1;
			else temp[i+1][j+1] = 0;
		}
	}

	for(int i = 0 ; i < x ; i++){
		temp[0][i+1] = temp[1][i+1];
		temp[i+1][0] = temp[i+1][1];
		temp[513][i+1] = temp[512][i+1];
		temp[i+1][513] = temp[i+1][512];
	}

	Mat lena_Minimum_variance_Laplacian(512, 512, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			bool flag = 0;
			if(temp[i+1][j+1] == 1){
				for(int a = -1 ; a < 2; a++){
					for(int b = -1 ; b < 2 ; b++){
						if(temp[i+1+a][j+1+b] == -1){
							lena_Minimum_variance_Laplacian.at<uchar>(i,j) = 0;
							flag = 1;
							break;
						}
					}
					if(flag == 1) break;
					if(flag == 0) lena_Minimum_variance_Laplacian.at<uchar>(i,j) = 255;
				}
			}
			else lena_Minimum_variance_Laplacian.at<uchar>(i,j) = 255;
		}
	}

	imshow("lena_Minimum_variance_Laplacian", lena_Minimum_variance_Laplacian);
	imwrite("lena_Minimum_variance_Laplacian.jpg", lena_Minimum_variance_Laplacian);
	waitKey(0);
	return 0;
}