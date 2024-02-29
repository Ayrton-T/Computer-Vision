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

int pic[522][522] = {0};
int temp[514][514] = {0};

int main(){
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int x = img.rows;
	int y = img.cols;

	int mask[11][11] = {-1, -3, -4, -6, -7, -8, -7, -6, -4, -3, -1,
               			-3, -5, -8,-11,-13,-13,-13,-11, -8, -5, -3,
               			-4, -8,-12,-16,-17,-17,-17,-16,-12, -8, -4,
               			-6,-11,-16,-16,  0, 15,  0,-16,-16,-11, -6,
               			-7,-13,-17,  0, 85,160, 85,  0,-17,-13, -7,
               			-8,-13,-17, 15,160,283,160, 15,-17,-13, -8,
               			-7,-13,-17,  0, 85,160, 85,  0,-17,-13, -7,
               			-6,-11,-16,-16,  0, 15,  0,-16,-16,-11, -6,
               			-4, -8,-12,-16,-17,-17,-17,-16,-12, -8, -4,
               			-3, -5, -8,-11,-13,-13,-13,-11, -8, -5, -3,
               			-1, -3, -4, -6, -7, -8, -7, -6, -4, -3, -1};

	int threshold = 1;


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			pic[i+5][j+5] = img.at<uchar>(i, j);
		}
	}
	for(int i = 0 ; i < x ; i++){
		pic[i+5][4] = pic[i+5][5];
		pic[i+5][3] = pic[i+5][5];
		pic[i+5][2] = pic[i+5][5];
		pic[i+5][1] = pic[i+5][5];
		pic[i+5][0] = pic[i+5][5];
		pic[i+5][517] = pic[i+5][516];
		pic[i+5][518] = pic[i+5][516];
		pic[i+5][519] = pic[i+5][516];
		pic[i+5][520] = pic[i+5][516];
		pic[i+5][521] = pic[i+5][516];
		pic[4][i+5] = pic[5][i+5];
		pic[3][i+5] = pic[5][i+5];
		pic[2][i+5] = pic[5][i+5];
		pic[1][i+5] = pic[5][i+5];
		pic[0][i+5] = pic[5][i+5];
		pic[517][i+5] = pic[516][i+5];
		pic[518][i+5] = pic[516][i+5];
		pic[519][i+5] = pic[516][i+5];
		pic[520][i+5] = pic[516][i+5];
		pic[521][i+5] = pic[516][i+5];
	}
	for(int i = 0 ; i < 5 ; i++){
		for(int j = 0 ; j < 5 ; j++){
			pic[i][j] = pic[5][5];
			pic[517+i][517+j] = pic[516][516];
			pic[517+i][j] = pic[516][5];
			pic[i][517+j] = pic[5][516];
		}
	}



	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			int temp0 = 0;
			for(int a = -5 ; a < 6 ; a++){
				for(int b = -5 ; b < 6 ; b++){
					temp0 += pic[i + 5 + a][j + 5 + b] * mask[a+5][b+5];
				}
			}
			if (temp0 >= threshold) temp[i+1][j+1] = 1;
			else if (temp0 <= -threshold) temp[i+1][j+1] = -1;
			else temp[i+1][j+1] = 0;
		}
	}


	for(int i = 0 ; i < x ; i++){
		temp[0][i+1] = temp[1][i+1];
		temp[i+1][0] = temp[i+1][1];
		temp[513][i+1] = temp[512][i+1];
		temp[i+1][513] = temp[i+1][512];
	}

	Mat lena_Difference_of_Gaussian(512, 512, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			bool flag = 0;
			if(temp[i+1][j+1] == 1){
				for(int a = -1 ; a < 2; a++){
					for(int b = -1 ; b < 2 ; b++){
						if(temp[i+1+a][j+1+b] == -1){
							lena_Difference_of_Gaussian.at<uchar>(i,j) = 0;
							flag = 1;
							break;
						}
					}
					if(flag == 1) break;
					if(flag == 0) lena_Difference_of_Gaussian.at<uchar>(i,j) = 255;
				}
			}
			else lena_Difference_of_Gaussian.at<uchar>(i,j) = 255;
		}
	}


	imshow("lena_Difference_of_Gaussian", lena_Difference_of_Gaussian);
	imwrite("lena_Difference_of_Gaussian.jpg", lena_Difference_of_Gaussian);
	waitKey(0);
	return 0;
}