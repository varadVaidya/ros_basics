#!/usr/bin/env python3
import rospy
from ros_basics.msg import iotSensor
import random

publisher = rospy.Publisher('iot_sensor',iotSensor,queue_size=10)

rospy.init_node('iot_sensor_pub',anonymous = True)

rate = rospy.Rate(1)

i = 0

while not rospy.is_shutdown():
    
    sensor = iotSensor()
    sensor.id = 1
    sensor.name = "TEST_SENSOR"
    sensor.temperature = 24.33 + random.random()*2
    sensor.humidity = 33.41 + random.random()*2
    
    rospy.loginfo("\n")
    rospy.loginfo(sensor)
    
    publisher.publish(sensor)
    
    rate.sleep()
    i += 1
