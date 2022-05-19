#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
int main(){
    String path = "/home/vampweeknd/AUVopencv/images/path1.jpg";
    Mat img = imread(path);
    Mat imgGray,imgBlur,imgCanny,imgDil;
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);
    Canny(imgBlur,imgCanny,50,100);
    // Probabilistic Line Transform (Hough line transform)
    vector<Vec4d> linesP; // will hold the results of the detection
    HoughLinesP(imgCanny, linesP, 1, CV_PI/180, 60, 50, 20 ); // runs the actual detection
    vector<double>slopes;
    vector<double>finalslopes;
    // Draw the lines
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4d l = linesP[i];
        //line( img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, LINE_AA);
        double slope = (l[3]-l[1])/(l[2]-l[0]);
        slopes.push_back(slope);
    }
    //four lines are detected for the four edges - so a pair of the lines will have identical slopes 
    for(int j =0;j<slopes.size();j++){
        for(int k =j+1;k<slopes.size();k++){
            if(abs(slopes[j]-slopes[k]) < 0.2){
                finalslopes.push_back(slopes[j]);
                //sort so that the negative slope is at 0th index
                sort(finalslopes.begin(),finalslopes.end());
            }
        }
    }
    double theta = -(atan(finalslopes[0])) * (180/CV_PI) + atan(finalslopes[1])*(180/CV_PI);
    double phi = (180-theta)/2;
    vector<Vec3f>circles;
    vector<Point> centersfinal;
    HoughCircles(imgBlur,circles,HOUGH_GRADIENT,1,60,200,15,0,20);
    for( size_t i = 0; i < circles.size(); i++ ) 
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle( img, center, 3, Scalar(0,255,255), -1);
        circle( img, center, radius, Scalar(0,0,255), 1 );
        centersfinal.push_back(center);
    }
    // ensuring that the lower centre is at 0th index
    if(centersfinal[0].y<centersfinal[1].y){
        swap(centersfinal[0],centersfinal[1]);
    }
    //considering the triangle to be isosceles and hence applying trignometric relations
    double dist1 = norm((centersfinal[1]-centersfinal[0]));
    double length = (dist1/2)/cos(phi*(CV_PI/180));
    int x1 = centersfinal[0].x + length*sin(phi*(CV_PI/180));
    int y1 = centersfinal[0].y - length*cos(phi*(CV_PI/180));
    circle(img,{x1,y1},3,Scalar(0,255,255),-1);
    circle(img,{x1,y1},13,Scalar(0,0,255),1);
    line(img,centersfinal[0],{x1,y1},Scalar(255,0,0));
    line(img,{x1,y1},centersfinal[1],Scalar(255,0,0));
    imshow("Image",img);
    waitKey(0);
    
}
