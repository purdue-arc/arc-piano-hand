isWhite = {
        0 : True,
        1 : False,
        2 : True,
        3 : False,
        4 : True,
        5 : True,
        6 : False,
        7 : True,
        8 : False,
        9 : True,
        10 : False,
        11 : True
}

def distanceInWhiteKeys(referenceKeyNumber, keyNumberToCalculate):
    # MIDI note number 0 = C octave -2 if 60 if C octave 3
    # Adjust to common range
    while(referenceKeyNumber > 12):
        referenceKeyNumber -= 12
        keyNumberToCalculate -= 12

    # Count number of octaves difference
    octaves = int(keyNumberToCalculate - referenceKeyNumber) / 12
    octAdjustKeyNumber = keyNumberToCalculate - 12*octaves

    numWhiteKeys = 0
    tempKeyNumber = referenceKeyNumber

    while(tempKeyNumber != keyNumberToCalculate):
        tempKeyNumber += 1
        if(isWhite(tempKeyNumber % 12)):
            numWhiteKeys += 1
    
    if keyNumberToCalculate % 12 != referenceKeyNumber % 12:
        numWhiteKeys += 0.5

    return numWhiteKeys

def whiteKeysUp(referenceKeyNumber, differenceInWhiteKeys):
    differenceInWhiteKeys = round(differenceInWhiteKeys)

    numWhiteKeys = 0

    tempKeyNumber = referenceKeyNumber

    while(numWhiteKeys < differenceInWhiteKeys):
        tempKeyNumber += 1
        if(isWhite(tempKeyNumber % 12)):
            numWhiteKeys += 1
    
    while(numWhiteKeys > differenceInWhiteKeys):
        tempKeyNumber -= 1
        if(isWhite(tempKeyNumber % 12)):
            numWhiteKeys -= 1

    return numWhiteKeys

class Finger:
    name = ""
    min_note = 0
    max_note = 0
    currentlyPlaying = False
    noteCurrentlyPlaying = -1

    def __init__(self, min_note, max_note):
        self.min_note = min_note
        self.max_note = max_note

    def __init__(self, min_note):
        self.min_note = min_note
        self.max_note = whiteKeysUp(min_note, 3)

    def setName(self, name):
        self.name = name

    def isPlaying(self):
        return self.currentlyPlaying

    def getNoteCurrentlyPlaying(self):
        if(self.currentlyPlaying):
            return self.noteCurrentlyPlaying
        else:
            return -1

    def noteOn(self, noteCurrentlyPlaying):
        self.currentlyPlaying = True
        self.noteCurrentlyPlaying = noteCurrentlyPlaying

    def noteOff(self):
        self.currentlyPlaying = False

    def isNoteValid(self, note):
        return note >= self.min_note and note <= self.max_note

    def updateNoteValues(self, shift):
        min_note += shift
        max_note += shift

class Hand:
    fingers = {}
    centerNote = 0

    def __init___(self, fingers, centerNote):
        self.fingers = fingers
        self.centerNote = centerNote

    def fingersThatCanPlayNote(self, note):
        fingersThatCanPlayNote = {}

        for finger in self.fingers:
            if (not finger.isPlaying) and finger.isNoteValid(note):
                fingersThatCanPlayNote.add(finger)
        
        return fingersThatCanPlayNote

    def canPlayNote(self, note):
        return len(self.fingersThatCanPlayNote) > 0

    def closestFinger(listOfFingers, note): # Assume that all fingers can play said note, or method is being used differently
        min_distance = 200 # Just needs to be larger than possible range of MIDI values
        min_dist_finger = None
        
        for finger in listOfFingers:
            if distanceInWhiteKeys((finger.min_note + finger.max_note) / 2, note) < min_distance:
                min_distance = distanceInWhiteKeys((finger.min_note + finger.max_note) / 2, note)
                min_dist_finger = finger
        
        if min_dist_finger == None:
            raise Exception("No fingers passed to closestFinger() call")
        
        return min_dist_finger

    def allocateFinger(self, note):
        closestFinger = None
        try:
            closestFinger = closestFinger(self.fingersThatCanPlayNote(note), note)
            self.fingers[self.fingers.index(closestFinger)].noteOn(note)
        except:
            raise Exception("Need to move hand or add more fingers") # Will change later
    
    def noteOff(self, note):
        for finger in self.fingers:
            if finger.getNoteCurrentlyPlaying == note:
                finger.noteOff()

        
            

    

