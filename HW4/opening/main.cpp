#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int pic[512][512];
int dia[512][512]={0};
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

	Mat lena_opening = img.clone();
////build a 0/1 array
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			if (img.at<uchar>(i, j) >= 128) { 
				pic[i][j] = 1; 
				lena_opening.at<uchar>(i, j) = 1;
			}
			else { 
				pic[i][j] = 0; 
				lena_opening.at<uchar>(i, j) = 0;
			}
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
			if(temp == 21) ero[i+2][j+2] = 1;
		}
	}


/////dilation
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j ++){
			if(ero[i][j] == 1){
				for(int k = -2 ; k < 3 ; k++){
					if(k+i >= 512) break;
					for(int l = -2 ; l < 3 ; l++){
						if(j+l >= 512) break;
						if( kernel[k+2][l+2] == 1) dia[i+k][j+l] = 255;
					}
				}
			}
		}
	}


	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			lena_opening.at<uchar>( i ,j ) = dia[i][j];
		}
	}


	imshow("lena_opening", lena_opening);
	imwrite("lena_opening.jpg", lena_opening);
	waitKey(0);
	return 0;
}