#!/usr/bin/env python3

from ros_basics.srv import addTwoInts
from ros_basics.srv import addTwoIntsRequest
from ros_basics.srv import addTwoIntsResponse

import rospy
import time

def callbak_add_two_ints(req):
    
    print("Returning addition [%s + %s = %s]" %(req.a,req.b, (req.a+req.b)))
    
    time.sleep(5)
    return addTwoIntsResponse(req.a+req.b)

def intergerAdd():
    
    rospy.init_node('add_two_ints_server')
    
    service = rospy.Service('add_two_ints',addTwoInts,callbak_add_two_ints)
    print("ready to add ints")
    rospy.spin()
    
if __name__ == '__main__':
    intergerAdd()