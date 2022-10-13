# Write if statements to save certain measurements to a text file
import serial
import File_formatting as ff
import matplotlib.pyplot as plt
import numpy as np
foundR  = False
raw_readings = []
#create a list of numbers from 1-20
converted_readings = []
for i in range(-1,19):
    converted_readings.append(110/20*i)
timelist = range(0, 20)
plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111)
line1, = ax.plot(timelist, converted_readings)
ff.make_graph(converted_readings[-20:],fig,line1)
ser = serial.Serial('COM6', 9800, timeout=1)
with open('Arduino_Outputs', 'w') as f:
    while True:
        line = ser.readline()
        f.write(str(line))
        line = str(line)
        print(line)
        if(foundR or line[2] == "R"):
            foundR = True
            output = ff.add_data(line)
            if output[0] == "c":
                converted_readings.append(output[1])
            elif output[0] == 'r':
                raw_readings.append(output[1])
            print("converted readings:", converted_readings)
            ff.make_graph(converted_readings[-20:],fig,line1)