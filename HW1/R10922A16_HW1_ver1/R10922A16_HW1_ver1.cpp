#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

Mat img;
Mat lena;
int x;
int y;
int x_half;
int y_half;

void upside_down() {

	for (int i = 0; i < x_half; i++)
		for (int j = 0; j < y; j++)
			swap(img.at<char>(i, j) ,img.at<char>(x - i - 1, j));

}

void right_side_left() {

	for (int i = 0; i < x; i++)
		for (int j = 0; j < y_half; j++)
			swap(img.at<char>(i, j) ,img.at<char>(i, y - j - 1));

}

void diagonally_flip(){
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			img.at<char>(i,j)=lena.at<char>(j,i);
		}
	}
}


int main() {

	lena = imread("lena.bmp", CV_8UC1);
	img = lena.clone();

	x = lena.rows;
	y = lena.cols;

	x_half = x / 2;
	y_half = y / 2;


	upside_down();


	imshow("upside_down.png", img);
	imwrite("upside_down.png", img);
	waitKey(0);

	img = lena.clone();

	right_side_left();

	imshow("right_side_left.png", img);
	imwrite("right_side_left.png", img);
	waitKey(0);

	img = lena.clone();

	diagonally_flip();

	imshow("diagonally_flip.png", img);
	imwrite("diagonally_flip.png", img);
	waitKey(0);




	return 0;
}