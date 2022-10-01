# Write if statements to save certain measurements to a text file
import serial
import File_formatting as ff
import matplotlib.pyplot as plt
import matplotlib.animation as animation

foundR  = False
# plt.ion()
raw_readings = []
converted_readings = [] 
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
# line1, = ax.plot(x, y)
ser = serial.Serial('COM8', 9800, timeout=1)
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
            ff.make_graph(2,converted_readings,ax)