#include<cmath>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<fstream>
#include<stdio.h>
#include <stdlib.h>
#include <iomanip>


#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;


struct list{
	int label;
	int top;
	int left;
	int right;
	int down;
	int number;
};

int connected[514][514]={0};	//use more space to escape from those i=0 j=0 i=512 j=512 condition

int main()
{

	//load already binarized pic
	Mat binarized = imread("binarized.jpg", IMREAD_GRAYSCALE);
	Mat img = binarized.clone();

	int x = binarized.rows;
	int y = binarized.cols;


	//initialize to 0/1 array cuz i dont know why some pixels are not 0 or 255 ,and some of them are 2 3 4 254....
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (img.at<uchar>(i, j) < 128) {
				connected[i + 1][j + 1] = 0;
			}
			else {
				connected[i + 1][j + 1] = 1;
			}
		}
	}

	//assign tag
	int iter=1;

	for (int i = 1; i<=x; i++) {
		for(int j=1;j<=y;j++){
			
			if(connected[i][j]==1){
				connected[i][j] = iter;
				iter++;
			}
			else {
				connected[i][j] = 0;
			}
		}
	}


	int min_temp;
	bool change = true;
	iter = 0;
	while (change) {
		change = false;
		iter += 1;
	//	cout << iter << endl;
		//top-down 4-connected			 check itself top down left right			
		for (int i = 1; i <=x; i++) {
			for (int j = 1; j <= y; j++) {
				vector<int> templist;
				if (connected[i][j] != 0) {
					templist.push_back(connected[i][j]);
					if (connected[i-1][j]!=0) {					
						templist.push_back(connected[i-1][j]);
					}
					if (connected[i][j-1]!=0) {						
						templist.push_back(connected[i][j-1]);
					}
					if (connected[i+1][j]!=0) {						
						templist.push_back(connected[i+1][j]);
					}
					if (connected[i][j+1]!=0){
						templist.push_back(connected[i][j+1]);
					}
					//if min is not itself still need to loop
					if (!templist.empty()) {
						min_temp = *min_element(templist.begin(), templist.end());
						if (min_temp != connected[i][j]) {
							change = true;
							connected[i][j] = min_temp;
						}
					}
				}
				templist.clear();
				
			}
		
		}
		////bottom-up almost like top-down only direction is different
		for (int i = x; i > 0; i--) {
			for (int j = y; j > 0; j--) {
				vector<int> templist;
				if (connected[i][j] != 0) {
					templist.push_back(connected[i][j]);
					if (connected[i-1][j]!=0) {					
						templist.push_back(connected[i-1][j]);
					}
					if (connected[i][j-1]!=0) {						
						templist.push_back(connected[i][j-1]);
					}
					if (connected[i+1][j]!=0) {						
						templist.push_back(connected[i+1][j]);
					}
					if (connected[i][j+1]!=0){
						templist.push_back(connected[i][j+1]);
					}
					if (!templist.empty()) {
						min_temp = *min_element(templist.begin(), templist.end());
						if (min_temp != connected[i][j]) {
							change = true;
							connected[i][j] = min_temp;
						}
					}

				}
				templist.clear();
			}
		}
	}



	list temp;
	vector<list> list_with_label;
	bool find;

	//try to count the number of the same tag and find (top left down right) index

	for(int i=1;i<=x;i++){
		for(int j=1;j<=y;j++){
			if(connected[i][j]!=0){
				if(list_with_label.empty()){
					temp.label=connected[i][j];
					temp.top=i-1;
					temp.left=j-1;
					temp.down=i-1;
					temp.right=j-1;
					temp.number=1;
					list_with_label.push_back(temp);
				}
				else{
					find=false;
					for(int k=0;k<list_with_label.size();k++){
						if(list_with_label[k].label==connected[i][j]){
							find=true;
							if(list_with_label[k].top>i-1) list_with_label[k].top=i-1;
							if(list_with_label[k].left>j-1) list_with_label[k].left=j-1;
							if(list_with_label[k].down<i-1) list_with_label[k].down=i-1;
							if(list_with_label[k].right<j-1) list_with_label[k].right=j-1;

							list_with_label[k].number+=1;
							break;
						}
					}

					if(!find){
						temp.label=connected[i][j];
						temp.top=i-1;
						temp.left=j-1;
						temp.down=i-1;
						temp.right=j-1;
						temp.number=1;
						list_with_label.push_back(temp);
					}
				}
			}
		}
	}

	vector<list> for_draw;

	//int test = 0;
	//ignore those pixel tag are not exceed the amount of 500
	for(int i=0;i<list_with_label.size();i++){	
		if(list_with_label[i].number>=500){
			temp.label=list_with_label[i].label;
			temp.top=list_with_label[i].top;
			temp.left=list_with_label[i].left;
			temp.down=list_with_label[i].down;
			temp.right=list_with_label[i].right;
			temp.number=list_with_label[i].number;
			for_draw.push_back(temp);
		}
	}

	int t,l,d,r;
	//you need to transfer from grayscale to RGB
	//or your rectangle and line will only draw black or white line
	Mat imgRGB;
	cvtColor(img, imgRGB, COLOR_GRAY2RGB);

	//use the index you have to draw
	for(int i=0;i<for_draw.size();i++){
		t=for_draw[i].top;
		l=for_draw[i].left;
		d=for_draw[i].down;
		r=for_draw[i].right;

		rectangle(imgRGB, Point(l, t), Point(r, d),Scalar(255,0,0),1,8,0);
		line(imgRGB,Point((l + r) / 2,(t+d)/2-5),Point((l + r) / 2,(t+d)/2+5),Scalar(0,0,255),1);
		line(imgRGB,Point((l + r) / 2 - 5,(t+d)/2),Point((l + r) / 2 + 5,(t+d)/2),Scalar(0,0,255),1);
	}

	imshow("connected_components.jpg", imgRGB);
	imwrite("connected_components.jpg", imgRGB);
	waitKey(0);

	return 0;
}

