import serial
import json
import time

with serial.Serial('COM3', 19200, timeout=None) as ser:  # location, baudrate, timeout
    x = {
        "fingers": {
            0: "A",
            1: None,
            2: "B",
            3: "C"
        },
        "move": False
    }

    j = json.dumps(x)

    while True:
        ser.write(j.encode('utf-8'))
        print("Arduino:", end="\n\n")
        print(ser.readline().decode('utf-8'), end="")
        print(ser.readline().decode('utf-8'), end="")
        print("-------------------------------------------------")
        time.sleep(0.1)

    # x = ser.read()          # read one byte
    # s = ser.read(10)        # read up to ten bytes (timeout), or whatever's in the buffer
    # line = ser.readline()   # read a '\n' terminated line
    # print(ser.name)         # check which port was really used
    # print(ser.is_open)      # check if the port is open
    # ser.write(b'hello')     # write a string
    # ser.close()             # close port
    # print(ser.is_open)      # verify the port is closed
