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
    //vector<Point2f>centres(contours.size());
    //vector<float>radius(contours.size());
        
    
    for (int i = 0 ; i<contours.size();i++){
        int area = contourArea(contours[i]);
        float peri= arcLength(contours[i],true);
    //     float no2 = secondhighest(peri);
    //     cout<<peri<<endl;
        approxPolyDP(contours[i],conPoly[i],0.0002*peri,true);
        
        //cout<<area<<" "<<i<<endl;
        
        
        //
        if(area>70){
        
            drawContours(img,conPoly,i,Scalar(0,255,0),2);
            boundRect[i]= boundingRect(conPoly[i]);
            
            //rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0,0,255),2);
            /*
              int x1 = boundRect[0].x;
              int y1 = boundRect[0].y;
              int x2 = boundRect[1].x + boundRect[1].width;
              int y2 = boundRect[1].y + boundRect[1].height;*/
            int x1 = 0,y1=0;  
            if(boundRect[i].area()>326){  
            rectangle(img,boundRect[3].br(),boundRect[8].tl(),Scalar(0,0,255),1);
            int x1 = (boundRect[3].x + boundRect[8].x)/2;
            int y1 = boundRect[i].height/2 + boundRect[i].y;
            circle(img,{x1,y1},4,Scalar(0,0,255),5);
            
            }//  cout<<x1<<endl;
            //  cout<<y1<<endl;
            //  cout<<x2<<endl;
            //  cout<<y2<<endl;      
            //cout<<conPoly.size()<<endl;
            //cout<<boundRect[i].area()<<endl;
            cout<<x1<<" "<<y1;

        
        
        
        
       }
        // int boundary = (boundRect[i].width + boundRect[i].height)*2;
        
        // //cout<<boundary<<endl;
        // if(boundary==356){
        //     
                     
        //         
        //     int x = boundRect[i].x + (boundRect[i].width)/2;
        //     int y = boundRect[i].y + (boundRect[i].height)/2;
        //     circle(img,{x,y},4,Scalar(0,0,255),5);
        // }
        
        //minEnclosingCircle(conPoly[i],centres[i],radius[i]);
        //circle(img,centres[i],(int)radius[i],Scalar(0,0,255),4);
    }
    
    
}

int hmin=125,hmax=179,smin=0,smax=83,vmin=74,vmax=214;
int main(){
    String path = "/home/vampweeknd/AUVopencv/images/gate1.jpg";
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