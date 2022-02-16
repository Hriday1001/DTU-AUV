#include<ros/ros.h>
#include<random>
#include "std_msgs/Int8.h"
#include<stdlib.h>

int main(int argc, char **argv){
    ros::init(argc , argv , "talker");
    ros::NodeHandle nh;

    ros::Publisher rand_pub = nh.advertise<std_msgs::Int8>("rand",1000);
    ros::Rate loop_rate(10);
    while(ros::ok()){
        int value = rand()%3 + (-1) ;
        std_msgs::Int8 msg;
        msg.data = value;
        rand_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
