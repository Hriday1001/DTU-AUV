#include<ros/ros.h>
#include "std_msgs/Int8.h"
#include<iostream>
using namespace std;

void randCallback(const std_msgs::Int8& msg){
    if(msg.data == 0){
        ROS_INFO_STREAM("YES");
    }
    else {
        ROS_INFO_STREAM(" ");
    }
}

int main(int argc , char **argv ){
    ros::init(argc , argv , "listener");
    ros::NodeHandle nh;
    ros::Subscriber rand_sub = nh.subscribe("rand" , 1000 , &randCallback);
    ros::spin();
    return 0;
}