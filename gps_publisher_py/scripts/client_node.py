import rospy
from std_msgs.msg import Int8
import socket
import time

host="192.168."
port=80
def talker():
    
    pub = rospy.Publisher('camera_data', Int8, queue_size=10)
    rospy.init_node('talker', anonymous=False)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        # while True:
            try:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                    hostname = socket.getfqdn()
                    HOST = socket.gethostbyname_ex(hostname)[2][1]
                    s.connect((host, port))
                    data = s.recv(1024)
                    ser.write(data)
                    out = list(data)
                    print(f"Received {out!r}")
                    rospy.loginfo(out)
                    pub.publish(int(data))
            except:
                # time.sleep(0.1)
                time.sleep(0.1)
        
    rate.sleep()

if _name_ == '_main_':
    #try:
        talker()