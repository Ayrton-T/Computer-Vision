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

	int op0[5][5] = { 100, 100, 100, 100, 100,
					  100, 100, 100, 100, 100,
						0,   0,   0,   0,   0,
					 -100,-100,-100,-100,-100,
					 -100,-100,-100,-100,-100 };

	int op30[5][5] = { 100, 100, 100, 100, 100,
					   100, 100, 100,  78, -32,
					   100,  92,   0, -92,-100,
						32, -78,-100,-100,-100,
					  -100,-100,-100,-100,-100 };

	int op60[5][5] = { 100, 100, 100,  32,-100,
					   100, 100,  92, -78,-100,
					   100, 100,   0,-100,-100,
					   100,  78, -92,-100,-100,
					   100, -32,-100,-100,-100 };

	int opn90[5][5] = { -100,-100,   0, 100, 100,
						-100,-100,   0, 100, 100,
						-100,-100,   0, 100, 100,
						-100,-100,   0, 100, 100,
						-100,-100,   0, 100, 100 };

	int opn60[5][5] = { -100,  32, 100, 100, 100,
						-100, -78,  92, 100, 100,
						-100,-100,   0, 100, 100,
						-100,-100, -92,  78, 100,
						-100,-100,-100, -32, 100 };

	int opn30[5][5] = {  100, 100, 100, 100, 100,
						 -32,  78, 100, 100, 100,
						-100, -92,   0,  92, 100,
						-100,-100,-100, -78,  32,
						-100,-100,-100,-100,-100 };



	int threshold = 12500;


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			pic[i+2][j+2] = img.at<uchar>(i, j);
		}
	}

	for(int i = 0 ; i < x ; i++){
		pic[i+2][1] = pic[i+2][2];
		pic[i+2][0] = pic[i+2][1];
		pic[i+2][515] = pic[i+2][514];
		pic[i+2][516] = pic[i+2][515];
	}

	for(int j = 0 ; j < y ; j++){
		pic[1][j+2] = pic[2][j+2];
		pic[0][j+2] = pic[1][j+2];
		pic[515][j+2] = pic[514][j+2];
		pic[516][j+2] = pic[515][j+2];
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			pic[i][j] = pic[2][2];
			pic[515+i][515+j] = pic[514][514];
			pic[515+i][j] = pic[514][2];
			pic[i][515+j] = pic[2][514];
		}
	}

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			vector<int> list;
			int temp0 = 0;
			for(int a = 0 ; a < 5 ; a++){
				for(int b = 0 ; b < 5 ; b++){
					temp0 += pic[i + 1 + a][j + 1 + b] * op0[a][b];
				}
			}
			list.push_back(temp0);
			int temp1 = 0;
			for(int a = 0 ; a < 5 ; a++){
				for(int b = 0 ; b < 5 ; b++){
					temp1 += pic[i + 1 + a][j + 1 + b] * op30[a][b];
				}
			}
			list.push_back(temp1);
			int temp2 = 0;
			for (int a = 0; a < 5; a++) {
				for (int b = 0; b < 5; b++) {
					temp2 += pic[i + 1 + a][j + 1 + b] * op60[a][b];
				}
			}
			list.push_back(temp2);
			int temp3 = 0;
			for (int a = 0; a < 5; a++) {
				for (int b = 0; b < 5; b++) {
					temp3 += pic[i + 1 + a][j + 1 + b] * opn90[a][b];
				}
			}
			list.push_back(temp3);
			int temp4 = 0;
			for (int a = 0; a < 5; a++) {
				for (int b = 0; b < 5; b++) {
					temp4 += pic[i + 1 + a][j + 1 + b] * opn60[a][b];
				}
			}
			list.push_back(temp4);
			int temp5 = 0;
			for (int a = 0; a < 5; a++) {
				for (int b = 0; b < 5; b++) {
					temp5 += pic[i + 1 + a][j + 1 + b] * opn30[a][b];
				}
			}
			list.push_back(temp5);
			

			temp[i][j] = *max_element(list.begin(), list.end());
			list.clear();
		}
	}

	Mat lena_Nevatia_Babu(512, 512, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if(temp[i][j] >= threshold) lena_Nevatia_Babu.at<uchar>(i,j) = 0;
			else lena_Nevatia_Babu.at<uchar>(i,j) = 255;
		}
	}

	imshow("lena_Nevatia_Babu", lena_Nevatia_Babu);
	imwrite("lena_Nevatia_Babu.jpg", lena_Nevatia_Babu);
	waitKey(0);
	return 0;
}