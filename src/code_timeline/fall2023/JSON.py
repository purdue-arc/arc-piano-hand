import json, serial

global temp_map
temp_map = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4}
#Constant mapping for notes

def playNote(note):
    serial.write(f"{temp_map[note['note']]}, {note['duration']}, {note['octave']}, {note['voice']}|")

def main():
    arduino = serial.Serial(port = 'COM4', baudrate = 115200, timeout = 0.1)
    #Open serial connection
    
    with open("Example_JSON.json", 'r') as file:
        data = json.load(file)
    #note, duration, octave, voice   

    for note in data:
        playNote(note)

if (__name__ == "__main__"):
    main()
