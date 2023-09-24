import serial
import time    
import re


def main():
    port = 'COM3'
    rate = 9600
    timeout = 1
    speed = 255 
    delay = 1
    reversed = 0


    ser = serial.Serial(port, rate, timeout=timeout)    
    pattern = r'\d+'

    while(True):
        ser.write(bytes("p", 'utf-8'))
        line = ser.readline().decode('utf-8').strip()

        item = re.findall(pattern, line)
        
        if item:
            for certain_item in item:
                print(int(certain_item))

        time.sleep(1)
    

if __name__ == "__main__":
    main()
