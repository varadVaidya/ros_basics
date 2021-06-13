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

void rotateBot(double angular_speed, double relative_angle, bool clockwise) {


    geometry_msgs::Twist vel_msg;

    if (clockwise){
        vel_msg.angular.z = -abs(angular_speed);
    }
    else{
        vel_msg.angular.z = abs(angular_speed);
    }

    double current_angle = 0.0;
    double t0 = ros::Time::now().toSec();
    ros::Rate loop_rate(10);

    do{
        vel_publisher.publish(vel_msg);
        double t1 = ros::Time::now().toSec();
        
        current_angle = angular_speed * (t1 -t0);

        ros::spinOnce();
        loop_rate.sleep();

    }while(current_angle<relative_angle);

    vel_msg.angular.z = 0;
    vel_publisher.publish(vel_msg);
}

void goToGoal(turtlesim::Pose goalPose ,double distance_tolerance){

    geometry_msgs::Twist vel_msg;

    ros::Rate loop_rate(100);

    double K_linear = 0.5;
    double K_angular = 4;


    while(true){

        
        double goalDistance = sqrt( pow((turtlesim_pose.x - goalPose.x),2) + pow((turtlesim_pose.y - goalPose.y),2) );
        double angleGoal = atan2((goalPose.y - turtlesim_pose.y),(goalPose.x - turtlesim_pose.x));

        double linearSpeed = K_linear*goalDistance;
        double angularSpeed = K_angular*(angleGoal - turtlesim_pose.theta);

        vel_msg.linear.x = linearSpeed;
        vel_msg.angular.z = angularSpeed;
        vel_publisher.publish(vel_msg);

        ros::spinOnce();
        loop_rate.sleep();

        if(goalDistance<distance_tolerance){
            break;
        }


    }

    vel_msg.linear.x = 0.0;
    vel_msg.angular.z =0.0;
}
int main(int argc, char **argv){

    ros::init(argc, argv,"straight_Line");
    ros::NodeHandle n;

    double speed,distance;

    vel_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
    pose_subscriber = n.subscribe("/turtle1/pose",10,poseCallback);
    //movebot(1,5,true);
    //rotateBot(10,90,true);

    turtlesim::Pose goalPose;
    goalPose.x = 4.0;
    goalPose.y = 2.0;
    goalPose.theta = 0.0;

    goToGoal(goalPose,0.01);
    
    ros::Rate loop_rate(0.5);
    ros::spin();
    
    return 0;
    




}