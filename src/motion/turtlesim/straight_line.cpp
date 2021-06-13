#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <sstream>

using namespace std;

ros::Publisher vel_publisher;
ros::Subscriber pose_subscriber;
turtlesim::Pose turtlesim_pose;


void poseCallback(const turtlesim::Pose::ConstPtr & pose_message){
	turtlesim_pose.x=pose_message->x;
	turtlesim_pose.y=pose_message->y;
	turtlesim_pose.theta=pose_message->theta;
}


void movebot( double speed , double distance ,bool isForward){

    geometry_msgs::Twist vel_msgs;

    if (isForward){
        vel_msgs.linear.x = abs(speed);
    }
    else{
        vel_msgs.linear.x = -abs(speed);
    }

    double t0 = ros::Time::now().toSec();
    double current_distance = 0.0;

    ros::Rate loop_rate(100);

    do{
        vel_publisher.publish(vel_msgs);
        double t1 = ros::Time::now().toSec();

        current_distance = speed * (t1 - t0);
        ros::spinOnce();
        loop_rate.sleep();
    }

    while(current_distance<distance);

    vel_msgs.linear.x = 0;
    vel_publisher.publish(vel_msgs);
}

int main(int argc, char **argv){

    ros::init(argc, argv,"straight_Line");
    ros::NodeHandle n;

    double speed,distance;

    vel_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
    pose_subscriber = n.subscribe("/turtle1/pose",10,poseCallback);
    movebot(1,5,true);
   
    ros::Rate loop_rate(0.5);
    ros::spin();
    
    return 0;
    




}