"""my_finger_controller controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot
import time
#import keyboard
 
if __name__ == "__main__":
    # create the Robot instance.
    robot = Robot()
    
    # get the time step of the current world.
    timestep = int(robot.getBasicTimeStep())
    
    print("14")
    #timeStep = 64
    max_speed = 0.5
        
    finger1Motor = robot.getDevice("finger_1")
    finger2Motor = robot.getDevice("finger_2")
    finger3Motor = robot.getDevice("finger_3")
    finger4Motor = robot.getDevice("finger_4")
    
    #Thinking we might need to use a function like this
    finger1Motor.setPosition(float(0))
    finger2Motor.setPosition(float(0))
    finger3Motor.setPosition(float(0))
    finger4Motor.setPosition(float(0))   
    
    finger1Motor.setVelocity(max_speed)
    finger2Motor.setVelocity(max_speed)
    finger3Motor.setVelocity(max_speed)
    finger4Motor.setVelocity(max_speed)
    
    start_time = time.time()
    
    
    while robot.step(timestep) < 32:
        end_time = time.time()
        elapsed_time = end_time - start_time
        
        if (elapsed_time > 0.0):
            finger1Motor.setPosition(1.34)
            
        if (elapsed_time > 1.0):
            finger2Motor.setPosition(1.34)   
            
        if (elapsed_time > 2.0):
            finger3Motor.setPosition(1.34)   
        
        if (elapsed_time > 3.0):
            finger4Motor.setPosition(1.34)  
        
        print(elapsed_time)
        print("in while")

 

# Enter here exit cleanup code.
