#!/usr/bin/env python3
import rospy
from ros_basics.msg import iotSensor

def iotSensor_callback(sensor_mesage):
    
    rospy.loginfo(sensor_mesage)
    
rospy.init_node("iot_sub_node",anonymous=True)
rospy.Subscriber("iot_sensor",iotSensor,iotSensor_callback)
rospy.spin()