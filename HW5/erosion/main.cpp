#include<cstdio>
#include<cstdlib>
#include<cmath>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int pic[512][512] = { 0 };
int ero[512][512] = { 0 };

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

	Mat lena_erosion = img.clone();

	for(int i = 0 ; i < x ; i++){
		for(int j = 0 ; j < y ; j++){
			pic[i][j] = img.at<uchar>(i, j);
			lena_erosion.at<uchar>(i, j) = 0;
		}
	}


/////erosion
	for (int i = 2; i < x-2; i++) {
		for (int j = 2; j < y-2; j++) {
			int temp = pic[i][j];
			for (int k = -2; k < 3; k++) {
				if (k + i >= 512) break;
				for (int l = -2; l < 3; l++) {
					if (j + l >= 512) break;
					///pick the smallest value min f(x-z) - k(z) but k(z) = 0 only pick min f(x-z)
					if (kernel[k + 2][l + 2] == 1 && pic[k + i][l + j] < temp) temp = pic[i + k][j + l];
				}
			}
			ero[i][j] = temp;
		}
	}




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