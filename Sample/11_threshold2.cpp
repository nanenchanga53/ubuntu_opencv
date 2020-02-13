#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
        Mat image = imread("images/green.jpg", 0);		// 명암도 영상 읽기
	CV_Assert(!image.empty());									// 영상파일 예외처리

        Rect rect(150,50,200,100);
        Mat ROI = image(rect);


	Mat Result;
	Mat Result2;
        Mat Result3;
        Mat ResultRoi;
        threshold(image, Result, 100, 255, THRESH_BINARY);
        threshold(image, Result2, 200, 255, THRESH_BINARY);
        threshold(ROI, ResultRoi, 160, 255, THRESH_BINARY);
        Mat ResultOtu;
        int rtn = threshold(image, ResultOtu, 150, 255, THRESH_OTSU);

        cout << "otsu : " << rtn << endl;

        Mat Result_mapping,Result_mapping2;

        bitwise_and(image,Result, Result_mapping);
        bitwise_and(ROI,ResultRoi, Result_mapping2);
	Result3 = Result - Result2;
	imshow("image", image);
	imshow("Result", Result);
	imshow("Result2", Result3);
        imshow("ResultOtu",ResultOtu);
        imshow("Result_bitwise",Result_mapping);
        imshow("ResultROI",ResultRoi);
        imshow("ROI",ROI);
        imshow("ROIMapping",Result_mapping2);
	waitKey();
	return 0;
}
