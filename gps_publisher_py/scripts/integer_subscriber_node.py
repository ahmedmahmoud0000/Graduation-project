import rospy
from std_msgs.msg import Int8
from std_msgs.msg import ByteMultiArray
from std_msgs.msg import String
import serial
import time
forward=bytes([0x1])
back=bytes([0x2])
right=bytes([0x3])
left=bytes([0x4])
stop=bytes([0x5])
global received_integer
received_integer=10
ser = serial.Serial('/dev/ttyACM0', 115200)

def callback(data):
    """
    This function is called whenever a new message is received on the subscribed topic.
    It retrieves the integer, opens the serial port, writes the data, and closes the port.
    """
    print("okkkkkk")
    
    received_integer = data.data
    print(received_integer)
    print(received_integer)
    
    ser = serial.Serial('/dev/ttyACM0', 115200)
    if received_integer==1:
        # inp = ser.readline()
        # ser.close()
        ser.write(forward)
        # ser.close()
        print("forward")
    elif received_integer==2:
        # inp = ser.readline()
        ser.write(back)
        # ser.close()
        print("back")
        received_integer=0
    elif received_integer==3:
        ser.write(right)
        # ser.close()
        print("right")
        received_integer=0
    elif received_integer==4:
        ser.write(left)
        # ser.close()
        print("left")
        received_integer=0
    elif received_integer==5:
        ser.write(stop)
        # ser.close()
        print("stop")
        received_integer=0



    
    # with serial.Serial('/dev/ttyUS', 9600) as ser:  # Open and automatically close port
    #     # Convert integer to bytes (if needed for your device)
    #     data_to_send = str(received_integer).encode()

    #     # Write data to serial port
    #     ser.write(data_to_send)


def main():
    # Initialize ROS node
    # received_integer=0
    pub = rospy.Publisher("encoder_data", String, queue_size=10)

    rospy.init_node('integer_subscriber_node')
    # time.sleep(2)
    # ser.write(forward)
    # ser.write(forward)
    print("okkkkkk")
    # time.sleep(2)
    # ser.write(stop)
    rospy.Subscriber("integer_topic", Int8, callback)
    # rospy.spin()
    rate = rospy.Rate(10)
    while not rospy.is_shutdown():
      # out_data=ser.readline()
      # ser.close()
      ser = serial.Serial('/dev/ttyACM0', 115200)
      out_data=ser.readline()
      msg = ByteMultiArray()
      msg.data = out_data
      decoded_string = out_data.decode("utf-8")
      pub.publish(decoded_string)
      
      # ser.close()
      print(out_data)
      rate.sleep()

    out_data=ser.readline()
    print(out_data)

   

if __name__ == '__main__':
    main()



