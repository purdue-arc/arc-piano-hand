import json
import serial
import time

#step, alter, octave, duration

#step: note name, alter: bass or treble clef, octave: octave (1-8), duration: length

port = "COM7" 
#Change this

step_finger = {"C": 4, "G": 3, "A": 2, "B": 1}

ser = serial.Serial("COM7")
ser.baudrate = 9600
ser.bytesize = 8        # check which port was really used
time.sleep(2)

def send_serial(json_list):
    
    for json_item in json_list:
        json_values = list(json_item.values())
        json_values[0] = step_finger[json_values[0]]
        
        message = ", ".join(f"{json_values[i]}" for i in range(4))

        ser.write(message.encode())
        print(str(ser.readline()))
        

        #finger number (important), alter (unimportant), octave (unimportant), length (important)

def main():
    with open("hotcrossmasked.json", "r") as file:
        json_list = json.load(file)
    
    send_serial(json_list)
    

if __name__ == "__main__":
    main()