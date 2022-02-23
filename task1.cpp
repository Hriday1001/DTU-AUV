#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int hmin =0,smin=0,vmin=0,hmax=179,smax=255,vmax=255;
int main(){
    String path = "/home/vampweeknd/AUVopencv/images/image1.jpg";
    Mat img = imread(path);
    Mat imgHSV,mask;
    cvtColor(img , imgHSV , CV_BGR2HSV);
    namedWindow("Trackbars",(640,250));
    createTrackbar("Hue min" , "Trackbars" , &hmin , 179);
    createTrackbar("Hue max" , "Trackbars" , &hmax , 179);
    createTrackbar("Sat min" , "Trackbars" , &smin , 255);
    createTrackbar("Sat max" , "Trackbars" , &smax , 255);
    createTrackbar("Val min" , "Trackbars" , &vmin , 255);
    createTrackbar("Val max" , "Trackbars" , &vmax , 255);
    
    while (true)
    {
    Scalar lower(hmin,smin,vmin);
    Scalar upper(hmax,smax,vmax);
    inRange(imgHSV,lower,upper,mask);
    imshow("Image" , img);
    imshow("HSVImage" , imgHSV);
    imshow("MaskImage" , mask);
    waitKey(1);
    }
    return 0;
}