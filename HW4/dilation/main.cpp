#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int pic[512][512];
int dia[512][512]={0};

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
			else pic[i][j] = 0;
		}
	}
/////dilation
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j ++){
			if(pic[i][j] == 1){
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

	Mat lena_dilation = img.clone();
	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			lena_dilation.at<uchar>( i ,j ) = dia[i][j];
		}
	}


	imshow("lena_dilation", lena_dilation);
	imwrite("lena_dilation.jpg", lena_dilation);
	waitKey(0);
	return 0;
}