#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import LaserScan

def scan_callback(msg: LaserScan):

#     if msg.ranges[0] < 1:
#          rospy.loginfo("front : Danger")
#     else :
#          rospy.loginfo(" front : Safee")
# for msg.ranges in (0,90)
#      {
#           rospy.loginfo("(" +str(msg.ranges)+ ")")
#      }
         
#     if msg.ranges[360] < 1:
#          rospy.loginfo("behind : Dangeer")
#     else :
#          rospy.loginfo("behind : Safee")
#          rospy.loginfo("(" +str(msg.ranges[360])+ ")")
#     if msg.ranges[180] < 1:
#          rospy.loginfo("Left : Dangeer")
#     else :
#          rospy.loginfo("Left : Safee")
#          rospy.loginfo("(" +str(msg.ranges[180])+ ")")
#     if msg.ranges[90] < 1:
#          rospy.loginfo("right : Dangeer")

#     else :

#          rospy.loginfo("right :Safee")2
#          rospy.loginfo("(" +str(msg.ranges[90])+ ")")




if __name__ == '__main__':

 rospy.init_node("rplidar_data")

 sub=rospy.Subscriber("/scan", LaserScan, callback=scan_callback)

 rospy.loginfo("Node has started")

 rospy.spin()

