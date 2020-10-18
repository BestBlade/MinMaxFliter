#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

Mat minmaxfliter(Mat img, Size temp) {
	if (temp.height % 2 == 0 || temp.width % 2 == 0) {
		cerr << "error template size" << endl;
	}
	int row_center = temp.height / 2;
	int col_center = temp.width / 2;
	int length = temp.height * temp.width - 1;

	Mat res = img.clone();
	//Mat res(img.rows, img.cols, img.type());

	for (int x = row_center; x < img.rows - row_center; x++) {
		for (int y = col_center; y < img.cols - col_center; y++) {
			if (res.channels() == 1) {
				vector<uchar> minmax_val;
				for (int i = 0; i < temp.height; i++) {
					for (int j = 0; j < temp.width; j++) {
						if (i == row_center && j == col_center) {
							continue;
						}
						minmax_val.push_back(img.at<uchar>(x + i - row_center, y + j - col_center));
					}
				}

				sort(minmax_val.begin(), minmax_val.end());
				if (img.at<uchar>(x, y) < minmax_val[0]) {
					res.at<uchar>(x, y) = minmax_val[0];
				}
				else if (img.at<uchar>(x, y) > minmax_val[length - 1]) {
					res.at<uchar>(x, y) = minmax_val[length - 1];
				}
				//else {
				//	res.at<uchar>(x, y) = img.at<uchar>(x, y);
				//}
			}
			else {
				//空间换时间
				vector<uchar> minmax_val_r;
				vector<uchar> minmax_val_g;
				vector<uchar> minmax_val_b;
				for (int i = 0; i < temp.height; i++) {
					for (int j = 0; j < temp.width; j++) {
						if (i == row_center && j == col_center) {
							continue;
						}
						minmax_val_r.push_back(img.at<Vec3b>(x + i - row_center, y + j - col_center)[2]);
						minmax_val_g.push_back(img.at<Vec3b>(x + i - row_center, y + j - col_center)[1]);
						minmax_val_b.push_back(img.at<Vec3b>(x + i - row_center, y + j - col_center)[0]);
					}
				}
				sort(minmax_val_r.begin(), minmax_val_r.end());
				sort(minmax_val_g.begin(), minmax_val_g.end());
				sort(minmax_val_b.begin(), minmax_val_b.end());

				if (img.at<Vec3b>(x, y)[2] < minmax_val_r[0]) {
					res.at<Vec3b>(x, y)[2] = minmax_val_r[0];
				}
				else if (img.at<Vec3b>(x, y)[2] > minmax_val_r[length - 1]) {
					res.at<Vec3b>(x, y)[2] = minmax_val_r[length - 1];
				}
				//else {
				//	res.at<Vec3b>(x, y)[2] = img.at<Vec3b>(x, y)[2];
				//}

				if (img.at<Vec3b>(x, y)[1] < minmax_val_g[0]) {
					res.at<Vec3b>(x, y)[1] = minmax_val_g[0];
				}
				else if (img.at<Vec3b>(x, y)[1] > minmax_val_g[length - 1]) {
					res.at<Vec3b>(x, y)[1] = minmax_val_g[length - 1];
				}
				//else {
				//	res.at<Vec3b>(x, y)[1] = img.at<Vec3b>(x, y)[1];
				//}

				if (img.at<Vec3b>(x, y)[0] < minmax_val_b[0]) {
					res.at<Vec3b>(x, y)[0] = minmax_val_b[0];
				}
				else if (img.at<Vec3b>(x, y)[0] > minmax_val_b[length - 1]) {
					res.at<Vec3b>(x, y)[0] = minmax_val_b[length - 1];
				}
				//else {
				//	res.at<Vec3b>(x, y)[0] = img.at<Vec3b>(x, y)[0];
				//}
			}
		}
	}
	return res;
}

int main() {
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.jpg",0);

	Size temp(3, 3);

	//

	//
	Mat res = minmaxfliter(img, temp);

	imshow("原图", img);
	imshow("3x3滤波结果图", res);

	waitKey(0);

	return 0;
}