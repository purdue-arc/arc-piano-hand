def main():
    """Write your mainline logic below this line (then delete this line)."""
    import serial
    import time
    ser = serial.Serial('COM10', 9800, timeout=1)
    speed = 255 
    delay = 1
    reversed = 0

    while(True):
        ser.write(bytes("p", 'utf-8'))
        time.sleep(2.2)
        line = ser.readline()
        line = str(line)

"""Do not change anything below this line."""
if __name__ == "__main__":
    main()
