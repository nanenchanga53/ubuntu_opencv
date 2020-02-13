#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <iostream>
//이미지 차이점
int main()
{	
	cv::Mat img_color = cv::imread("images/green.jpg", CV_LOAD_IMAGE_COLOR);
	cv::Mat img_color2 = cv::imread("images/red.jpg", CV_LOAD_IMAGE_COLOR);

	cv::Mat img_absdiff;
	
	cv::absdiff(img_color, img_color2, img_absdiff);
	
	cv::imshow("src1", img_color);
	cv::imshow("src2", img_color2);
	
	cv::imshow("diff", img_absdiff);	

	cv::waitKey(0);

	return 0;
}

