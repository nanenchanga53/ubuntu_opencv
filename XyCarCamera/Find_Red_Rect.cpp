#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
     Mat cam_data;  // 카메라에서 받아온 영상 저장     
     VideoCapture cap(0); // 웹캡 연결 (video0)
     // 1fps로 설정     
     double fps = cap.set(CV_CAP_PROP_FPS, 1);
     cout << "fps :" << fps << endl;     
     if(!cap.isOpened()) {
         cerr << "error conn fail" << endl;
	 return -1;
     }
     while(1)
     {
         cap.read(cam_data);
         if(cam_data.empty()) {
            cerr << "cam_data empty" << endl;
            break;
         }

         Mat imgproc = cam_data.clone();
         Mat imgsplit[3]; // RGB -> C1 R, G, B
         
         split(imgproc, imgsplit); //B(0), G(1), R(2)

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





	 Mat result = imgproc.clone();


// Mat::zeros(last_find_res.rows, last_find_res.cols, CV_8UC3)


         vector<vector<Point> > contours;
         vector<vec4i> hierarchy;
         findContours(last_find_res, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);         
         for(int i = 0; i<contours.size(); i++)
         {
             Scalar line( 0, 0, 255);
             //drawContours(result, contours, i, line);
             RotatedRect rrect = minAreaRect(contours[i]);
             Rect boundingrect = rrect.boundingRect();

             if(boundingrect.width * 0.6
                 <= boundingrect.height
                 && (boundingrect.width * 0.8
                 >= boundingrect.height))             {
		rectangle(result, boundingrect, line);
             }
         }
         if(!result.empty())
         {
            imshow("result", result);
         }
       






         imshow("cam", cam_data);
         imshow("th_r_200", red_find_res);

         imshow("r", imgsplit[2]);
         imshow("g", imgsplit[1]);
         imshow("b", imgsplit[0]);

         imshow("last", last_find_res);

         if(waitKey(25) >= 0)
         {
             break;
         }
     }
     return 0;
}
