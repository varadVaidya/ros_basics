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



if __name__ == '__main__':
    
    try:
        
        rospy.init_node('turtlesim_motion_pose',anonymous = True)
        
        vel_topic = "/turtle1/cmd_vel"
        velocity_publisher = rospy.Publisher(vel_topic,Twist,queue_size=20)
        
        position_topic = "/turtle1/pose"
        postionTopic = rospy.Subscriber(position_topic,Pose,posCallback)
        
        time.sleep(2)
        move(velocity_publisher,1,5,is_forward = True)
    
    except rospy.ROSInterruptException:
        rospy.loginfo("node terminated.")
    
        
        