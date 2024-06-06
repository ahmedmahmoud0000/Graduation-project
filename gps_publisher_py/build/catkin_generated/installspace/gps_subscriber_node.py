import rospy
from std_msgs.msg import String
from std_msgs.msg import Int32

def callback_action(action):

  print(f"Action: {action.data}")
  #print(f"Distance: {distance.data}")

def callback_distance(distance):

  print(f"Distance: {distance.data}")

def gps_subscriber():
  # Initialize the node with a name
  rospy.init_node('gps_subscriber_node', anonymous=True)

  # Create subscribers for the topics
  sub_action = rospy.Subscriber('gps_action', String, callback_action)
  sub_distance = rospy.Subscriber('gps_distance', Int32, callback_distance)

  # Keep the node running to receive data
  rospy.spin()

if __name__ == '__main__':
  try:
    gps_subscriber()
  except rospy.ROSInterruptException:
    pass

