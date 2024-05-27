import json
from serpapi import GoogleSearch
#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int32
import time
from serpapi import GoogleSearch

dis=[0] * 30
head=[0] * 30
last = 100
last2 =150
last3 = 90


params = {
 "api_key": "a049341aa06153faee8cdb4bb7c951de7c5c7d0fbd3a9f071900838897f9b3dc",
 "engine": "google_maps_directions",
 "q": "Coffee",
 "hl": "en",
 "start_addr": "Modern Academy For Engineering and Technology",
 "end_addr": "Modern University for Technology & Information, Faculty of Pharmacy",
 "gl": "eg",
 "travel_mode": "0",
 "distance_unit": "0"
}

def get_trips_data():
  search = GoogleSearch(params)
  data = search.get_dict()

  # returns JSON object as
  # a dictionary
  #data = json.loads(results)
  trips = data['directions']
  det=[0] * 3
  #dis=[0] * 30
  #head=[0] * 30
  dir=data['directions']
  trips=dir[0]#['trips']
  best_dir=trips['trips']
  trip_steps = []
  for index, i in enumerate(best_dir):
    det[int(index)]=i['details']
    of=0
  for index,y in enumerate(det):
    if y == 0:
      continue
    for dex,z in enumerate(y):
      dis[dex+of]=z['distance']
      head[dex+of]=z['action']
    of=of+dex+1
    #trip_steps.append({'action': step['action'], 'distance': step['distance']})
    #print[y]
  print("hello")

  for w,i in enumerate(dis):
    if head[w] ==0:
      continue
    print(head[w]," ",i)


def gps_publisher():
  pub_action = rospy.Publisher('gps_action', String, queue_size=10)
  pub_distance = rospy.Publisher('gps_distance', Int32, queue_size=10)
  rospy.init_node('gps_publisher_py', anonymous=False)
  rate = rospy.Rate(10) # 10hz

  while not rospy.is_shutdown():
    get_trips_data()#trips_data =
    # time.sleep(2)
    for w, i in enumerate(dis):
	    if head[w] ==0:
		     continue
      
	    pub_action.publish(head[w])
	    pub_distance.publish(i)
    # pub_action.publish("turn-right")
    # pub_distance.publish(last)
    # pub_action.publish("straight")
    # print("straight")
    # pub_distance.publish(last)
    # print(last)
    # pub_action.publish("turn-right")
    # print("turn-right")
    # pub_distance.publish(last2)
    # print(last2)
    # pub_action.publish("turn-left")
    # print("turn-left")
    # pub_distance.publish(last3)
    # print(last3)
    pub_action.publish("done")
	
  
    rate.sleep()
    break 
if __name__ == '__main__':
  try:
    gps_publisher()
  except rospy.ROSInterruptException:
    pass 
  
