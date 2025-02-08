from machine import Pin, PWM
import time
import machine
import esp32
import time
from machine import Timer
import json
global songData
with open("config.json") as f:
    songData= json.load(f)

rtc = machine.RTC()
rtc.datetime((0,0,0,0,0,0,0,0))
stopStepperMotorTimer = Timer(2)
dir_pin = Pin(2, Pin.OUT)
step_pin = Pin(15, Pin.OUT)
step_pin_PWM = PWM(step_pin,freq=50)
dir_pin.value(1)     # high is CCW looking down on shaft
finger_pins = [16, 17, 18, 19, 22]
fingers = [PWM(Pin(pin), freq=50) for pin in finger_pins]

def set_servo_angle(servo, angle):
    duty_cycle = int((angle / 180) * 2**16)
    servo.duty_u16(duty_cycle)

def stopStepperMotor(timer):
    step_pin_PWM.duty_u16(0)

def moveStepperMotor(dir, steps):
    dir_pin.value(dir)
    stopStepperMotorTimer.init(period=steps*20, mode=Timer.ONE_SHOT, callback=stopStepperMotor)
    duty_cycle = int(0.5 * 2**16)
    step_pin_PWM.duty_u16(duty_cycle)

def checkHandPos(timer):
    currTime = rtc.datetime()
    currTimeInSeconds = currTime[5] + currTime[6]*60 + currTime[4]*3600
    currentTimestamp = currTimeInSeconds % len(songData)
    currentData = songData[currentTimestamp]
    handPosition = currentData.get("handPosition", 0)
    moveStepperMotor(1, handPosition)
    fingerStates = ["thumb", "index", "middle", "ring", "pinky"]
    for i, fingerState in enumerate(fingerStates):
        if i < len(fingers):
            angle = 90 if currentData.get(fingerState, "up") == "down" else 0
            set_servo_angle(fingers[i], angle)
def TestingExample():
    print("Moving stepper motor 100 steps forward")
    moveStepperMotor(1, 100)  # Move 100 steps forward
    time.sleep(2)  # Wait 2 seconds
    print("Moving stepper motor 100 steps backward")

    moveStepperMotor(0, 100)  # Move 100 steps backward
    time.sleep(2)
    
    print("Testing each servo")
    for servo in fingers:
        set_servo_angle(servo, 90) #Move servo to 90 degrees
    time.sleep(5)
    
    for servo in fingers:
        set_servo_angle(servo, 0) #Move servo to 0 degrees
    time.sleep(5)
    

checkHandPosition = Timer(1)
checkHandPosition.init(period=100, mode=Timer.PERIODIC, callback=checkHandPos)
while True:
    TestingExample()
    
    
    