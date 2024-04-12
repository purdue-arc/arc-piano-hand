import json
import serial
import time

#step, alter, octave, duration

#step: note name, alter: bass or treble clef, octave: octave (1-8), duration: length

port = "COM8" 
#Change this

rate = 9600
step_finger = {"C": 4, "G": 3, "A": 2, "B": 1}

def send_serial(json_list):
    ser = serial.Serial(port, rate)
    
    for json_item in json_list:
        json_values = list(json_item.values());
        json_values[0] = step_finger[json_values[0]]
        
        message = ", ".join(f"{json_values[i]}" for i in range(4))

        ser.write(message.encode())
        print(message + '\n' + str(ser.readline()))
        time.sleep(3)
        

        #finger number (important), alter (unimportant), octave (unimportant), length (important)

def main():
    with open("hotcrossmasked.json", "r") as file:
        json_list = json.load(file)
    
    send_serial(json_list)
    

if __name__ == "__main__":
    main()