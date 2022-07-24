from gpiozero import Servo
import time import sleep

pinky_servo = Servo(1)
ring_servo = Servo(2)
middle_servo = Servo(3)
pointer_servo = Servo(4)
thumb_servo = Servo(5)
wrist_servo = Servo(6)

wrist_offset_angle = 0
default_wrist_angle = wrist_servo.mid()
press_key_angle = 30 / 180 # 30 of 180 degrees 

pinky_angle = pinky_servo.mid()
ring_angle = ring_servo.mid()
middle_angle = middle_servo.mid()
pointer_angle = pointer_servo.mid()
thumb_angle = thumb_servo.mid()

keys = ["C3", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "C4"]

def set_finger_joints():
    thumb_servo.value = thumb_angle
    pointer_servo.value = pointer_angle
    middle_servo.value = middle_angle
    ring_servo.value = ring_angle
    pinky_servo.value = pinky_angle

def reset_finger_joints():
    pinky_angle = pinky_servo.mid()
    ring_angle = ring_servo.mid()
    middle_angle = middle_servo.mid()
    pointer_angle = pointer_servo.mid()
    thumb_angle = thumb_servo.mid()
    set_finger_joints()
    sleep(0.25)

def move_servos():
    set_finger_joints()
    wrist_servo.value = default_wrist_angle + wrist_offset_angle
    sleep(0.3)

def set_angle(key):
    if key == "C3" :
        wrist_offset_angle = 0 / 180
        thumbAngle = press_key_angle
    elif key == "C#" :
        wrist_offset_angle = 15 / 180
        pointerAngle = press_key_angle
    elif key == "D" :
        wrist_offset_angle = 7 / 180
        pointerAngle = press_key_angle
    elif key == "D#" :
        wrist_offset_angle = 0 / 180
        pointerAngle = press_key_angle
    elif key == "E" :
        wrist_offset_angle = 3 / 180
        middleAngle = press_key_angle
    elif key == "F" :
        wrist_offset_angle = 0 / 180
        middleAngle = press_key_angle
    elif key == "F#" :
        wrist_offset_angle = -5 / 180
        middleAngle = press_key_angle
    elif key == "G" :
        wrist_offset_angle = 0 / 180
        ringAngle = press_key_angle
    elif key == "G#" :
        wrist_offset_angle = -3 / 180
        ringAngle = press_key_angle
    elif key == "A" :
        wrist_offset_angle = 0 / 180
        pinkyAngle = press_key_angle
    elif key == "A#" :
        wrist_offset_angle = -5 / 180
        pinkyAngle = press_key_angle
    elif key == "B" :
        wrist_offset_angle = -8 / 180
        pinkyAngle = press_key_angle
    elif key == "C4" :
        wrist_offset_angle = -12 / 180
        pinkyAngle = press_key_angle

def play_key(key):
    set_angle(key)
    move_servos()
    reset_finger_joints()
