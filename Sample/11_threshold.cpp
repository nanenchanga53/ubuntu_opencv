#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("images/1.jpg", 0);		// 명암도 영상 읽기
	CV_Assert(!image.empty());									// 영상파일 예외처리

	Mat Result;
	threshold(image, Result, 100, 255, THRESH_BINARY);

	imshow("image", image);
	imshow("Result", Result);

	waitKey();
	return 0;
}
