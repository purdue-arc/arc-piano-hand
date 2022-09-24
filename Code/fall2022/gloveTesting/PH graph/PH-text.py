#write if statements to save certain measurements to a text file
import serial
ser = serial.Serial('COM4', 9800, timeout=1)
with open('Arduino_Outputs', 'w') as f:
    while True:
        a = ser.readline()
        print(a)
        a = str(a)
        f.write(a)