#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<iostream>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


char h( int x0 ,int x1 , int x2 , int x3){
	if(x0 == x1){
		if(x0 == x2 && x0 == x3) return 'r';
		else return 'q';
	}
	return 's';
}

int f( char b ,char c ,char d ,char e ){
	if(b == 'r' && c == 'r' && d == 'r' && e == 'r') return 5;
	int cnt = 0;
	if(b == 'q') cnt++;
	if(c == 'q') cnt++;
	if(d == 'q') cnt++;
	if(e == 'q') cnt++;

	return cnt;
}

int down[66][66] = {0};
int ans[64][64] = {0};
int main(){
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int x = img.rows;
	int y = img.cols;
	int down_row = 1 , down_col = 1;

///down sampling fetch every 8*8 matrix topmost-left pixel 
	for (int i = 0; i < x; i+=8) {
		for (int j = 0; j < y; j+=8) {
			down[down_row][down_col] = img.at<uchar>(i, j);
			down_col += 1;
		}
		down_col = 1;
		down_row += 1;
	}
///build 0/1 array
	for (int i = 1; i < 65; i++) {
		for (int j = 1; j < 65; j++) {
			if (down[i][j] >= 128) down[i][j] = 1;
			else down[i][j] = 0;
		}
	}
///yokoi
	char b,c,d,e;
	for(int i=1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			if( down[i][j] == 1 ){
				b = h( down[i][j] , down[i][j+1] , down[i-1][j+1] , down[i-1][j] );
				c = h( down[i][j] , down[i-1][j] , down[i-1][j-1] , down[i][j-1] );
				d = h( down[i][j] , down[i][j-1] , down[i+1][j-1] , down[i+1][j] );
				e = h( down[i][j] , down[i+1][j] , down[i+1][j+1] , down[i][j+1] );
				ans[i-1][j-1] = f( b , c , d , e );
			}
		}
	}

///output a txt file
	ofstream newFile;
	newFile.open("hw6.txt");
	
	for(int i = 0 ; i < 64 ; i++){
		for(int j = 0 ; j < 64 ; j++){
			if(ans[i][j] == 0) newFile << ' ';
			else newFile << ans[i][j];
			if (j % 63 == 0 && j != 0) newFile << '\n';
		}
	}

	newFile.close();
	// imshow("lena_opening", lena_opening);
	// imwrite("lena_opening.jpg", lena_opening);
	// waitKey(0);
	return 0;
}