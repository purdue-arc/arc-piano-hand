def distanceInWhiteKeys(referenceKeyNumber, keyNumberToCalculate):
    while(referenceKeyNumber > 12):
        referenceKeyNumber -= 12
        keyNumberToCalculate -= 12
    octaves = int(keyNumberToCalculate - referenceKeyNumber) / 12
    octAdjustKeyNumber = keyNumberToCalculate - 12*octaves
    

def state_update()