#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
import math
import time

x,y,yaw = 0,0,1
def posCallback(pose_message):
    
    global x
    global y, yaw
    
    x = pose_message.x
    y = pose_message.y
    yaw = pose_message.theta
    

def move(velocity_publisher,speed,distance,is_forward):
    
    vel_message = Twist()
    

    global x,y
    print("x value:",x)    
    x0 = x
    y0 = y
    if is_forward:
        vel_message.linear.x = abs(speed)
    else:
        vel_message.linear.x = -abs(speed)
        
    distance_moved = 0.0
    
    loop_rate = rospy.Rate(20)
    
    while True:
        
        rospy.loginfo("Turtle move:")
        velocity_publisher.publish(vel_message)
        loop_rate.sleep()
        
        distance_moved = abs(
            math.sqrt(
                (x-x0)**2 + (y-y0)**2
            )
        )
        print("distance moved",distance_moved)
        
        if not distance_moved<distance:
            rospy.loginfo("reached")
            break
        
    vel_message.linear.x = 0
    velocity_publisher.publish(vel_message)

def rotatebot(velocity_publisher,angular_speed_degree,relative_angle_degree,clockwise):
    
    vel_message = Twist()
    
    angular_speed = math.radians(abs(angular_speed_degree))
    
    if clockwise:
        vel_message.angular.z = -abs(angular_speed)
    else:
        vel_message.angular.z = abs(angular_speed)
    
    loop_rate = rospy.Rate(10)
    
    t0 = rospy.Time.now().to_sec()
    
    while True:
        
        rospy.loginfo("Rotate")
        velocity_publisher.publish(vel_message)
        
        t1 = rospy.Time.now().to_sec()
        
        current_angle_degree = (t1-t0) * angular_speed_degree
        loop_rate.sleep()
        
        if (current_angle_degree>relative_angle_degree):
            rospy.loginfo("reached")
            break
    
    vel_message.angular.z = 0
    velocity_publisher.publish(vel_message)

def goToGoal(velocity_publisher,xgoal,ygoal):
    
    global x,y,yaw
    vel_message = Twist()
    loop_rate = rospy.Rate(100)
    while True:
        K_linear,K_angular, = 0.5,4
        distance = abs(math.sqrt(
            (xgoal-x) **2 + (ygoal - y)**2
        ))
        angleGoal = math.atan2(
            (ygoal-y),(xgoal-x)
        )
        loop_rate.sleep()
        angular_speed = (angleGoal - yaw) * K_angular
        
        linear_speed = distance*K_linear
        
        vel_message.linear.x = linear_speed
        vel_message.angular.z = angular_speed
        velocity_publisher.publish(vel_message)
        
        if (distance<0.001):
            break
        
if __name__ == '__main__':
    
    try:
        
        rospy.init_node('turtlesim_motion_pose',anonymous = True)
        
        vel_topic = "/turtle1/cmd_vel"
        velocity_publisher = rospy.Publisher(vel_topic,Twist,queue_size=20)
        
        position_topic = "/turtle1/pose"
        postionTopic = rospy.Subscriber(position_topic,Pose,posCallback)
        
        time.sleep(2)
        #move(velocity_publisher,1,5,is_forward = True)
        #rotatebot(velocity_publisher,10,90,True)
        goToGoal(velocity_publisher,2,2)
    except rospy.ROSInterruptException:
        rospy.loginfo("node terminated.")
    
        
        