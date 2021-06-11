#include <ros/ros.h>
#include <ros_basics/addTwoInts.h>

bool add(ros_basics::addTwoInts::Request &request, ros_basics::addTwoInts::Response &response){

    response.sum = request.a + request.b;
    ROS_INFO("request x=%d , y=%d", request.a, request.b);
    ROS_INFO("sending response = %d", response.sum);

    return true;

}

int main(int argc, char **argv){

    ros::init(argc, argv , "add_two_ints_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertise("add_two_ints",add);

    ROS_INFO("Ready to add two ints");
    ros::spin();
    
    return 0;
}

