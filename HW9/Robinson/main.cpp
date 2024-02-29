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
int temp[512][512] = {0};

int main(){
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int x = img.rows;
	int y = img.cols;

	int op0[3][3] = {-1, 0, 1,
					 -2, 0, 2,
					 -1, 0, 1 };

	int op1[3][3] = { 0, 1, 2,
					 -1, 0, 1,
					 -2,-1, 0 };

	int op2[3][3] = { 1, 2, 1,
					  0, 0, 0,
					 -1,-2,-1 };

	int op3[3][3] = { 2, 1, 0,
					  1, 0,-1,
					  0,-1,-2 };

	int op4[3][3] = { 1, 0,-1,
					  2, 0,-2,
					  1, 0,-1 };

	int op5[3][3] = { 0,-1,-2,
					  1, 0,-1,
					  2, 1, 0 };

	int op6[3][3] = {-1,-2,-1,
					  0, 0, 0,
					  1, 2, 1 };

	int op7[3][3] = {-2,-1, 0,
					 -1, 0, 1,
					  0, 1, 2 };



	int threshold = 43;


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			pic[i+1][j+1] = img.at<uchar>(i, j);
		}
	}

	for(int i = 0 ; i < x ; i++){
		pic[i+1][0] = pic[i+1][1];
		pic[i+1][515] = pic[i+1][514];
	}

	for(int j = 0 ; j < y ; j++){
		pic[0][j+1] = pic[1][j+1];
		pic[515][j+1] = pic[514][j+1];
	}


	pic[0][0] = pic[1][1];
	pic[515][515] = pic[514][514];
	pic[515][0] = pic[514][1];
	pic[0][515] = pic[1][514];


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			vector<int> list;
			int temp0 = 0;
			for(int a = 0 ; a < 3 ; a++){
				for(int b = 0 ; b < 3 ; b++){
					temp0 += pic[i + 1 + a][j + 1 + b] * op0[a][b];
				}
			}
			list.push_back(temp0);
			int temp1 = 0;
			for(int a = 0 ; a < 3 ; a++){
				for(int b = 0 ; b < 3 ; b++){
					temp1 += pic[i + 1 + a][j + 1 + b] * op1[a][b];
				}
			}
			list.push_back(temp1);
			int temp2 = 0;
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					temp2 += pic[i + 1 + a][j + 1 + b] * op2[a][b];
				}
			}
			list.push_back(temp2);
			int temp3 = 0;
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					temp3 += pic[i + 1 + a][j + 1 + b] * op3[a][b];
				}
			}
			list.push_back(temp3);
			int temp4 = 0;
			for(int a = 0 ; a < 3 ; a++){
				for(int b = 0 ; b < 3 ; b++){
					temp4 += pic[i + 1 + a][j + 1 + b] * op4[a][b];
				}
			}
			list.push_back(temp4);
			int temp5 = 0;
			for(int a = 0 ; a < 3 ; a++){
				for(int b = 0 ; b < 3 ; b++){
					temp5 += pic[i + 1 + a][j + 1 + b] * op5[a][b];
				}
			}
			list.push_back(temp5);
			int temp6 = 0;
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					temp6 += pic[i + 1 + a][j + 1 + b] * op6[a][b];
				}
			}
			list.push_back(temp6);
			int temp7 = 0;
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					temp7 += pic[i + 1 + a][j + 1 + b] * op7[a][b];
				}
			}
			list.push_back(temp7);
			

			temp[i][j] = *max_element(list.begin(), list.end());
			list.clear();
		}
	}

	Mat lena_Robinson(512, 512, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if(temp[i][j] >= threshold) lena_Robinson.at<uchar>(i,j) = 0;
			else lena_Robinson.at<uchar>(i,j) = 255;
		}
	}

	imshow("lena_Robinson", lena_Robinson);
	imwrite("lena_Robinson.jpg", lena_Robinson);
	waitKey(0);
	return 0;
}