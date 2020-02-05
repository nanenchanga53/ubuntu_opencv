#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("images/1.jpg", 0);		// 명암도 영상 읽기
	CV_Assert(!image.empty());									// 영상파일 예외처리

	Mat Result;
	Mat Result2;
	Mat Result3;
	threshold(image, Result, 100, 255, THRESH_BINARY);
	threshold(image, Result2, 150, 255, THRESH_BINARY);

	//bitwise_and(Result, Result2, Result3);
	Result3 = Result - Result2;
	imshow("image", image);
	imshow("Result", Result);
	imshow("Result2", Result3);

	waitKey();
	return 0;
}
