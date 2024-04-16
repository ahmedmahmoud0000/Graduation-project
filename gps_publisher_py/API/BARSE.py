import json
from serpapi import GoogleSearch

params = {
  "api_key": "eeee61d95745136cdada2ae07cba559cb7f51ff6d863ba550d5fe7ff76d8d656",
  "engine": "google_maps_directions",
  "q": "Coffee",
  "hl": "en",
  "start_addr": "Modern Academy For Engineering and Technology",
  "end_addr": "Modern University for Technology & Information, Faculty of Pharmacy",
  "gl": "eg",
  "travel_mode": "0",
  "distance_unit": "0"
}

search = GoogleSearch(params)
data = search.get_dict()

# returns JSON object as
# a dictionary
#data = json.loads(results)
trips = data['directions']
det=[0] * 3
dis=[0] * 30
head=[0] * 30
dir=data['directions']
trips=dir[0]#['trips']
best_dir=trips['trips']

for index, i in enumerate(best_dir):
    det[int(index)]=i['details']
    of=0
for index,y in enumerate(det):
    if y == 0 :
        continue
    for dex,z in enumerate(y):
        dis[dex+of]=z['distance']
        head[dex+of]=z['action']
    of=of+dex+1
    #print[y]
print("hello")

for w,i in enumerate(dis):
    print(head[w]," ",i)