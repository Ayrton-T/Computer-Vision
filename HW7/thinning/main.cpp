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

void yokoi(vector<vector<int>> &ans){
	int table[66][66];
	for(int i = 0 ; i < 66 ; i++){
		for(int j = 0 ; j < 66 ; j++){
			table[i][j] = 0;
		}
	}
	for(int i = 1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			table[i][j] = ans[i-1][j-1];
		}
	}
	char b,c,d,e;
	for(int i=1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			if( table[i][j] == 1 ){
				b = h( table[i][j] , table[i][j+1] , table[i-1][j+1] , table[i-1][j] );
				c = h( table[i][j] , table[i-1][j] , table[i-1][j-1] , table[i][j-1] );
				d = h( table[i][j] , table[i][j-1] , table[i+1][j-1] , table[i+1][j] );
				e = h( table[i][j] , table[i+1][j] , table[i+1][j+1] , table[i][j+1] );
				ans[i-1][j-1] = f( b , c , d , e );
			}
		}
	}
	return ;
}

void PRO(vector<vector<int>> &ans){
	int table[66][66];
	for(int i = 0 ; i < 66 ; i++){
		for(int j = 0 ; j < 66 ; j++){
			table[i][j] = 0;
		}
	}
	for(int i = 1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			table[i][j] = ans[i-1][j-1];
		}
	}

	for(int i = 1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			if(table[i][j] == 0) ans[i-1][j-1] = 0;
			else if(table[i][j] == 1){
				if(table[i+1][j] == 1 || table[i-1][j] == 1 || table[i][j+1] == 1 || table[i][j-1] == 1)
					ans[i-1][j-1] = 1;
				else ans[i-1][j-1] = 2;
			}
			else ans[i-1][j-1] = 2;
		}
	}
	return ;
}

void CSO(vector<vector<int>> &ans){
	int table[66][66];
	for(int i = 0 ; i < 66 ; i++){
		for(int j = 0 ; j < 66 ; j++){
			table[i][j] = 0;
		}
	}
	for(int i = 1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			table[i][j] = ans[i-1][j-1];
		}
	}
	for(int i = 1 ; i < 65 ; i++){
		for(int j = 1 ; j < 65 ; j++){
			if(table[i][j] != 0) table[i][j] = 1;
		}
	}
	char b,c,d,e;
	for(int i = 0 ; i < 64 ; i++){
		for(int j = 0 ; j < 64 ; j++){
			if(ans[i][j] == 1){
				b = h( table[i+1][j+1] , table[i+1][j+2] , table[i][j+2] , table[i][j+1] );
				c = h( table[i+1][j+1] , table[i][j+1] , table[i][j] , table[i+1][j] );
				d = h( table[i+1][j+1] , table[i+1][j] , table[i+2][j] , table[i+2][j+1] );
				e = h( table[i+1][j+1] , table[i+2][j+1] , table[i+2][j+2] , table[i+1][j+2] );
				
				int cnt = 0;
				if( b == 'q' ) cnt+=1;
				if( c == 'q' ) cnt+=1;
				if( d == 'q' ) cnt+=1;
				if( e == 'q' ) cnt+=1;

				if( cnt == 1 ){
					ans[i][j] = 0;
					table[i+1][j+1] = 0;
				}
			}
			if(ans[i][j] != 0) ans[i][j] = 1;
		}
	}
	return ;
}


int main(){
	Mat lena = imread("lena.bmp", CV_8UC1);
	Mat img = lena.clone();

	int down[66][66];
	vector<vector<int>> ans(64,vector<int>(64,0));

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
			if (down[i][j] >= 128) {
				down[i][j] = 1;
				ans[i-1][j-1] = 0;
			}
			else {
				ans[i-1][j-1] = 0;
				down[i][j] = 0;
			}
		}
	}

	for(int i = 0 ; i < 64 ; i++){
		for(int j = 0 ; j < 64 ; j++){
			ans[i][j] = down[i+1][j+1];
		}
	}
///yokoi


	yokoi(ans);
	PRO(ans);
	CSO(ans);

	bool change = 1;
	while(change){
		change = 0;
		int temp[64][64];
		for(int i = 0 ; i < 64 ; i++){
			for(int j = 0 ; j < 64 ; j++){
				temp[i][j] = ans[i][j];
			}
		}
		yokoi(ans);
		PRO(ans);
		CSO(ans);

		for(int i = 0 ; i < 64 ; i++){
			for(int j = 0 ; j < 64 ; j++){
				if(temp[i][j] != ans[i][j]){
					change = 1;
					break;
				}
			}
			if(change == 1) break;
		}
	}

	Mat lena_thinning(64, 64, CV_8UC1, Scalar(0));

	for(int i = 0 ; i < 64 ; i++){
		for(int j = 0 ; j < 64 ; j++){
			if(ans[i][j] == 1) lena_thinning.at<uchar>(i ,j) = 255;
			else lena_thinning.at<uchar>(i,j) = 0;
		}
	}


	imshow("lena_thinning", lena_thinning);
	imwrite("lena_thinning.jpg", lena_thinning);
	waitKey(0);
	return 0;
}