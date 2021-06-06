import rospy
from std_msgs.msg import String

rospy.init_node('listener',anonymous = True)
def chatter_callback(message):
    print("I heard %s",message.data)
    
    
rospy.Subscriber('chatter',String,chatter_callback)
## chatter callback is callback, which is a fucntion that is automatically executed when their is a new message is received by the subscriber



rospy.spin()
    
    
