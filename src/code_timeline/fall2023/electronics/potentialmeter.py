import serial
import time    
import re
def main():
    ser = serial.Serial('COM3', 9600, timeout=1)
    
    speed = 255 
    delay = 1
    reversed = 0

    pattern = r'\d+'

    while(True):
        ser.write(bytes("p", 'utf-8'))
        line = ser.readline()
        line = str(line)

        item = re.findall(pattern, line)
        print(item)
        # print(line.strip().decode('utf-8'))
        
        time.sleep(1)
    

if __name__ == "__main__":
    main()
