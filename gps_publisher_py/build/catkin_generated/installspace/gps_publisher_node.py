import tkinter as tk
from tkinter import messagebox
import threading
import json
from serpapi import GoogleSearch
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int32
import time

# Define global variables to store the addresses
start_addr = ""
end_addr = ""

dis = [0] * 30
head = [0] * 30

def get_trips_data(start_addr, end_addr):
    params = {
        "api_key": "a049341aa06153faee8cdb4bb7c951de7c5c7d0fbd3a9f071900838897f9b3dc",
        "engine": "google_maps_directions",
        "q": "Coffee",
        "hl": "en",
        "start_addr": start_addr,
        "end_addr": end_addr,
        "gl": "eg",
        "travel_mode": "0",
        "distance_unit": "0"
    }

    search = GoogleSearch(params)
    data = search.get_dict()
    trips = data['directions']
    det = [0] * 3
    dir = data['directions']
    trips = dir[0]
    best_dir = trips['trips']
    for index, i in enumerate(best_dir):
        det[int(index)] = i['details']
        of = 0
    for index, y in enumerate(det):
        if y == 0:
            continue
        for dex, z in enumerate(y):
            dis[dex + of] = z['distance']
            head[dex + of] = z['action']
        of = of + dex + 1
    print("hello")

    for w, i in enumerate(dis):
        if head[w] == 0:
            continue
        print(head[w], " ", i)

def gps_publisher():
    rospy.init_node('gps_publisher_py', anonymous=False)
    pub_action = rospy.Publisher('gps_action', String, queue_size=10)
    pub_distance = rospy.Publisher('gps_distance', Int32, queue_size=10)
    rate = rospy.Rate(10)  # 10hz

    while not rospy.is_shutdown():
        if start_addr and end_addr:
            get_trips_data(start_addr, end_addr)
            for w, i in enumerate(dis):
                if head[w] == 0:
                    continue
                i = i * 100
                pub_action.publish(head[w])
                pub_distance.publish(i)
            pub_action.publish("done")
            break
        rate.sleep()

def on_submit():
    global start_addr, end_addr
    start_addr = start_entry.get()
    end_addr = end_entry.get()
    if start_addr and end_addr:
        root.quit()  # Close the Tkinter window

def on_closing():
    try:
        rospy.signal_shutdown("GUI closed")
    except:
        pass
    root.quit()

# Create the Tkinter window
root = tk.Tk()
root.title("GPS Publisher")
root.geometry("400x200")
root.configure(bg="lightblue")

# Create and place the title label
title_label = tk.Label(root, text="Autonomous Delivery Vehicle", font=("Helvetica", 16, "bold"), bg="lightblue")
title_label.pack(pady=10)

# Create and place labels and entries for start and end addresses
frame = tk.Frame(root, bg="lightblue", padx=10, pady=10)
frame.pack(fill=tk.BOTH, expand=True)

tk.Label(frame, text="Start Address", bg="lightblue", font=("Helvetica", 12)).grid(row=0, column=0, pady=5)
start_entry = tk.Entry(frame, font=("Helvetica", 12))
start_entry.grid(row=0, column=1, pady=5, padx=10)

tk.Label(frame, text="End Address", bg="lightblue", font=("Helvetica", 12)).grid(row=1, column=0, pady=5)
end_entry = tk.Entry(frame, font=("Helvetica", 12))
end_entry.grid(row=1, column=1, pady=5, padx=10)

# Create and place the submit button with an edged border
submit_button = tk.Button(frame, text="Submit", command=on_submit, font=("Helvetica", 12), bg="green", fg="white",
                          relief="raised", borderwidth=4)
submit_button.grid(row=2, columnspan=2, pady=20)

# Set the window close event
root.protocol("WM_DELETE_WINDOW", on_closing)

# Run the Tkinter main loop
root.mainloop()

# After the Tkinter loop ends, start the ROS node
if start_addr and end_addr:
    try:
        gps_publisher()
    except rospy.ROSInterruptException:
        pass
