import serial
import json
# import time

with serial.Serial(port='/dev/ttyUSB0', baudrate=19200, timeout=1) as ser:  # location, baudrate, timeout
    # Create python dictionary representing message to be sent
    x = {
        "notes": ['A', 'B', 'C']
    }

    # Convert dictionary object to JSON
    j = json.dumps(x)
    print(j)

    # Open serial communication port and write JSON object as bytes
    ser.open()
    ser.write(j.encode('utf-8'))

    # x = ser.read()          # read one byte
    # s = ser.read(10)        # read up to ten bytes (timeout), or whatever's in the buffer
    # line = ser.readline()   # read a '\n' terminated line
    # print(ser.name)         # check which port was really used
    # print(ser.is_open)      # check if the port is open
    # ser.write(b'hello')     # write a string
    # ser.close()             # close port
    # print(ser.is_open)      # verify the port is closed

# # Alternatively configure serial later
# with serial.Serial() as ser:
#     ser.baudrate = 19200
#     ser.port = '/dev/ttyUSB0'
#     ser.timeout = 1
#     ser.open()
