def distanceInWhiteKeys(referenceKeyNumber, keyNumberToCalculate):
    # MIDI note number 0 = C octave -2 if 60 if C octave 3
    # Adjust to common range
    while(referenceKeyNumber > 12):
        referenceKeyNumber -= 12
        keyNumberToCalculate -= 12

    # Count number of octaves difference
    octaves = int(keyNumberToCalculate - referenceKeyNumber) / 12
    octAdjustKeyNumber = keyNumberToCalculate - 12*octaves

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

    numWhiteKeys = 0
    tempKeyNumber = referenceKeyNumber

    while(tempKeyNumber != keyNumberToCalculate):
        tempKeyNumber += 1
        if(isWhite(tempKeyNumber % 12)):
            numWhiteKeys += 1
    
    if keyNumberToCalculate % 12 != referenceKeyNumber % 12:
        numWhiteKeys += 0.5

    return numWhiteKeys




def 

def state_update():
    