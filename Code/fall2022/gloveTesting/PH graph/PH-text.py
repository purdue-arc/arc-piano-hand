# Write if statements to save certain measurements to a text file
import serial
import File_formatting as ff
foundR  = False
ser = serial.Serial('COM3', 9800, timeout=1)
with open('Arduino_Outputs', 'w') as f:
    while True:
        line = ser.readline()
        print(line)
        f.write(str(line))
        line = str(line)
        if(foundR ==True or line[2] == "R"):
            foundR = True
            ff.add_data(line)
            # ff.make_graph()