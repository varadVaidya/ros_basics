from std_msgs.msg import String

import rospy

pub = rospy.Publisher('chatter',String,queue_size= 10)
rospy.init_node('talker',anonymous= True)
rate = rospy.Rate(1)

i = 0

while not rospy.is_shutdown():
    hello_string = "hello world %s "%i
    rospy.loginfo(hello_string)
    pub.publish(hello_string)
    rate.sleep()
    i = i + 1