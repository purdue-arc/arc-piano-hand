# Write if statements to save certain measurements to a text file
import serial
import File_formatting as ff
foundR  = False

raw_readings = []
converted_readings = []  
ser = serial.Serial('COM3', 9800, timeout=1)
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
            #print("output[1]:", output[1])
            # ff.make_graph()