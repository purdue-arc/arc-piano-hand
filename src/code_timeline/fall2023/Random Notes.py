import time
import serial
ser = serial.Serial('COM4', 9800, timeout=1)
speed = 255
delay = 1
reversed = 0

while(True):
    ser.write(bytes("{},0,{},{}".format(speed,str(int(delay) * 1000),0), 'utf-8'))
    time.sleep(2.2)
    # ser.write(bytes("{},1,{},{}".format(speed,str(int(delay) * 1000),0), 'utf-8'))
    # time.sleep(2.2)
    ser.write(bytes("{},2,{},{}".format(speed,str(int(delay) * 1000),1), 'utf-8'))
    time.sleep(2.2)