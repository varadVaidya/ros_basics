#!/usr/bin/env python3

from ros_basics.srv import addTwoInts
from ros_basics.srv import addTwoIntsRequest
from ros_basics.srv import addTwoIntsResponse

import rospy
import sys

def add_two_ints_client(x,y):
    
    rospy.wait_for_service('add_two_ints')
    
    try:
        add_two_ints = rospy.ServiceProxy('add_two_ints',addTwoInts)
        response = add_two_ints(x,y)
        return response.sum
        
    except rospy.ServiceException:
        print("service call failed:")

def usage():
    return "%s [x y]"%sys.argv[0]
        
if __name__ == '__main__':
    
    if len(sys.argv)==3:
        
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    
    else:
        print("%s [x y] " %sys.argv[0])
        sys.exit(1)
    
    print("Requesting %s + %s" % (x, y))
    s = add_two_ints_client(x,y)
    print("%s + %s = %s" % (x,y,s))
    