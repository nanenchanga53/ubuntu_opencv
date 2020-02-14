#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
        Mat Imgproc = imread("images/red.jpg");
        Mat imgsplit[3]; // RGB -> C1 R, G, B

        split(Imgproc, imgsplit); //B(0), G(1), R(2)

        Mat red_find_res;
        threshold(imgsplit[2], red_find_res,
                200, 255, THRESH_BINARY);
        Mat green_find_res;
        threshold(imgsplit[1], green_find_res,
                  200, 255, THRESH_BINARY);
        Mat blue_find_res;
         threshold(imgsplit[0], blue_find_res,
                   200, 255, THRESH_BINARY);


         Mat last_find_res;
         last_find_res = red_find_res - green_find_res - blue_find_res;

         Mat result = Imgproc.clone();


        // Mat::zeros(last_find_res.rows, last_find_res.cols, CV_8UC3)


         vector<vector<Point> > contours;
         vector<Vec4i> hierarchy;
         findContours(last_find_res, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
         for(int i = 0; i<contours.size(); i++)
         {
             Scalar line( 0, 0, 255);
             drawContours(result, contours, i, line);
             RotatedRect rrect = minAreaRect(contours[i]);
             Rect boundingrect = rrect.boundingRect();

             if(boundingrect.width * 1.0
                 <= boundingrect.height
                 && (boundingrect.width * 1.0
                 >= boundingrect.height))             {
                rectangle(result, boundingrect, line);
             }
         }
         if(!result.empty())
         {
            imshow("result", result);
         }

        imshow("Imgproc",Imgproc);
        //imshow("red",Imgsplit[2]);
        //imshow("green",Imgsplit[1]);
        //imshow("blue",Imgsplit[0]);
        //imshow("th_r_200",red_find_res);
        //imshow("th_g_200",green_find_res);
        //imshow("th_b_200",blue_find_res);
        //imshow("last_find_res",last_find_res);
        //imshow("HSL",img_HLS);
        //imshow("HRes",Img_H_Red_res);
        //imshow("erode",erode_res);
       // imshow("dilate",dil_res);
        waitKey();


        return 0;
}
