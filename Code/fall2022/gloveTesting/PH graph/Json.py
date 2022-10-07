import serial
import json

x = {
     "notes": ['A', 'B', 'C']
}

j = json.dumps(x)
print(j)

with serial.Serial(port = 'COM6',baudrate= 9600, timeout=1) as ser: # location, baudrate, timeout
     x = {
          "notes": 12391230,
          "aaa":213
     }

     j = json.dumps(x)
     print(j)

     #ser.open()
     ser.write(j.encode('utf-8'))