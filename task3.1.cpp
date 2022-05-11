#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;



void getContours(Mat imgDil , Mat img){
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    findContours(imgDil,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    vector<vector<Point>>conPoly(contours.size());
    vector<Rect>boundRect(contours.size());
    vector<Point2f>centres(contours.size());
    vector<float>radius(contours.size());
  
        
    
    for (int i = 0 ; i<contours.size();i++){
        float peri= arcLength(contours[i],true);
        int area = contourArea(contours[i]);
        approxPolyDP(contours[i],conPoly[i],0.01*peri,true);
        
            
            
        drawContours(img,conPoly,i,Scalar(0,255,0),2);
        cout<<conPoly[i]<<endl;
        //boundRect[i]= boundingRect(conPoly[i]);
            
        //rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,0,255),2);
            /*
              int x1 = boundRect[0].x;
              int y1 = boundRect[0].y;
              int x2 = boundRect[1].x + boundRect[1].width;
              int y2 = boundRect[1].y + boundRect[1].height;*/
            
            //rectangle(img,boundRect[j].br(),boundRect[j+1].tl(),Scalar(0,0,255),1);
            circle(img,{345,280},4,Scalar(0,0,255),4);
            circle(img,{327,127},4,Scalar(0,0,255),4);                
            circle(img,{369,197},4,Scalar(0,0,255),4);
            }
            

        
        
        
        
       }
        
    
        
    

  
    


int hmin=0,hmax=42,smin=21,smax=101,vmin=96,vmax=237;
int main(){
    String path = "/home/vampweeknd/AUVopencv/images/path1.jpg";
    Mat img = imread(path);
    Mat imgGray,imgBlur,imgCanny,imgDil;
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);
    Canny(imgBlur,imgCanny,50,100);
    Mat kernel = getStructuringElement(MORPH_RECT,Size(2,2));
    dilate(imgCanny,imgDil,kernel);
    Mat imgHSV,mask;
    cvtColor(img , imgHSV , CV_BGR2HSV);
    Scalar lower(hmin,smin,vmin);
    Scalar upper(hmax,smax,vmax);
    inRange(imgHSV,lower,upper,mask);

    getContours(mask,img);
    
   // putText(img,"Dark Green",cont);

    imshow("Image",img);
    imshow("mask",mask);
    // imshow("Gray Image",imgGray);
    // imshow("Blur Image",imgBlur);
    // imshow("Canny Image",imgCanny);
    // imshow("Dialated Image",imgDil);
    waitKey(0);
    
}