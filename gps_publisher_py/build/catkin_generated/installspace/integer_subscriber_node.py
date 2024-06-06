import rospy
from std_msgs.msg import Int8
from std_msgs.msg import Int16
from std_msgs.msg import ByteMultiArray
from std_msgs.msg import String
import serial
import time
import struct

start =bytes([0x7A])
end =bytes([0x78])
forward=bytes([0x1])
back=bytes([0x2])
right=bytes([0x3])
left=bytes([0x4])
stop=bytes([0x5])
speed=bytes([0x96])
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
    bytes_val = received_integer.to_bytes(2, 'big')
    #bytes_val = bytes(received_integer)
    
    speed=serial.to_bytes(bytes_val[1])
    #print(speed)
    string = b''
    string += struct.pack('!B',bytes_val[1])
    print(string)
    ser = serial.Serial('/dev/ttyACM0', 115200)
    if bytes_val[0]==1:
        # inp = ser.readline()
        # ser.close()
        ser.write(start)
        ser.write(forward)
        ser.write(string)
        ser.write(end)
        # ser.close()
        print(bytes_val[1])
        print("forward")
    elif bytes_val[0]==2:
        # inp = ser.readline()
        ser.write(start)
        ser.write(back)
        ser.write(string)
        ser.write(end)
        # ser.close()
        print("back")
        #bytes_val[0]=0
    elif bytes_val[0]==3:
        ser.write(start)
        ser.write(right)
        ser.write(string)
        ser.write(end)
        # ser.close()
        print("right")
        #bytes_val[0]=0
    elif bytes_val[0]==4:
        ser.write(start)
        ser.write(left)
        ser.write(string)
        ser.write(end)
        # ser.close()
        print("left")
        #bytes_val[0]=0
    elif bytes_val[0]==5:
        ser.write(start)
        ser.write(stop)
        ser.write(string)
        ser.write(end)
        # ser.close()
        print("stop")
        #bytes_val[0]=0



    
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
    rospy.Subscriber("integer_topic", Int16, callback)
    
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



