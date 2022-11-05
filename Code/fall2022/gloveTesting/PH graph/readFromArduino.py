# Write if statements to save certain measurements to a text file
import serial
import manipulateData as ff
import matplotlib.pyplot as plt
import numpy as np
import re
#create a list of numbers from 1-20
num_fingers = 5 
fingerArray = [[],[],[],[],[]]

# Make starting array with values for scaling the graph
for i in range(num_fingers):
    for j in range(-1,19):
        fingerArray[i].append(110/20*j)
# Create basic graph

timelist = range(0, 20)
plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111)
# This needs to change when we add fingers
counter = ['v-','w-','x-','y-','z-']
lineArray = []
for i in range(num_fingers):
    lineArray[i], ax.plot(timelist, fingerArray[i], counter[i], label = "Finger %d" %(i + 1))
ff.make_graph(fingerArray, fig, lineArray)

#start reading data from arduino
foundDone = False
total_readings = 0
ser = serial.Serial('COM6', 9800, timeout=1)
with open('Arduino_Outputs', 'w') as f:
    while True:
        line = ser.readline()
        line = str(line)
        if(line.find("D") != -1 or foundDone):
            f.write(line)
            p = re.compile(r'([-]{0,1}[0-9]{0,2}\.[0-9]{0,2})')
            m = p.search(line)
            if m != None:
                total_readings += 1
                fingerVal = m.group(0)
                finger_index = total_readings % num_fingers
                fingerArray[finger_index].append(float(fingerVal))
                print("Finger " + (finger_index + 1))
                print(fingerVal)
            foundDone = True
            ff.make_graph(fingerArray, fig, lineArray)

            
        
        # if(foundR or line[2] == "D"):
        #     output = ff.add_data(line)
        #     index = total_readings % num_fingers
        #     converted_readings[index].append(output[1])
        #     total_readings += 1
        #     print("converted readings:", converted_readings)
        #     ff.make_graph(converted_readings[0][-20:], fig, line1, line2)
        #     if len(converted_readings[0]) == 40:
        #         print(ff.analyze_data(converted_readings[0]))