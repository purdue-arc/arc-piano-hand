
# Note that this is specifically for MusicXML produced by OEMER (by BreezeWhite)
# OEMER has 64 notes in a measure
# OEMER produces chords through extra voices and not <chord>
class MusicXMLChecker:

    # Takes a file path and validates everything
    def __init__(self, file_path):
        self.file_path = file_path
        self.has_valid_npm = True
        self.has_valid_clefs = True
        self.has_no_chords = True
        self.revalidate()
    
    # <tag>n</tag>
    # Returns the n between two tags as a string
    def get_value(self, line, tag):
        return line.replace(f"<{tag}>", "").replace(f"</{tag}>", "")
    
    # This sets the file path, does not automatically revalidate
    def set_file_path(self, new_file_path):
        self.file_path = new_file_path

    # Does everything you want it to :D
    def set_file_path_and_revalidate(self, new_file_path):
        self.file_path = new_file_path
        self.revalidate
    
    # Validates everything in one run then stores the results
    def revalidate(self):
        with open(self.file_path, 'r') as file:
            cur_clef = ""
            in_clef = False
            inside_measure = False
            curMeasure = 0
            curNPM = 0
            for line in file:
                line = line.strip()
                if (self.has_valid_npm):
                    if "<measure" in line:
                        inside_measure = True
                        curMeasure += 1
                        curNPM = 0
                    elif "</measure>" in line:
                        inside_measure = False
                        if curNPM != 64:
                            self.has_valid_npm = False
                    elif inside_measure and "<duration>" in line:
                        value = self.get_value(line, "duration")
                        curNPM += int(value)
                
                if (self.has_no_chords):
                    if "<chord" in line:
                        self.has_no_chords = False
                    if "<voice" in line:
                        value = int(self.get_value(line, "voice"))
                        if value != 1:
                            self.has_no_chords = False

                if (self.has_valid_clefs):
                    if "<clef" in line:
                        in_clef = True
                    elif in_clef == True and "<sign>" in line:
                        temp = self.get_value(line, "sign")
                        if temp not in {"G", "F"}:
                            self.has_valid_clefs = False
                        elif cur_clef == "":
                            cur_clef = temp
                        elif cur_clef != temp:
                            self.has_valid_clefs = False
                    elif "</clef>" in line:
                        in_clef = False

    
    # Runs all Checks
    # Will print debug statements depending on which one is wrong
    def verifyAll(self) -> bool:
        if (not self.has_valid_npm):
            print("NPM is wrong")
            return False
        if ( not self.has_valid_clefs):
            print("Clefs is wrong")
            return False
        if (not self.has_no_chords):
            print("There are chords")
            return False

        return True
        
    

    # Below are methods that are no longer necessary, but still work

    # Checks if there are the correct beats in a measure
    # notes per measure
    def verifyNPM(self) -> bool:
        inside_measure = False
        curMeasure = 0
        curNPM = 0

        with open(self.file_path, 'r') as file:
            for line in file:
                line = line.strip()
                if "<measure" in line:
                    inside_measure = True
                    curMeasure += 1
                    curNPM = 0
                elif "</measure>" in line:
                    inside_measure = False
                    # print("curNPM is " + str(curNPM))
                    if curNPM != 64:
                        return False
                elif inside_measure and "<duration>" in line:
                    value = self.get_value(line, "duration")
                    curNPM += int(value)
        return True
    
    # Verifies the clef is consistent
    def verifyClefs(self) -> bool:
        cur_clef = ""
        in_clef = False
        with open(self.file_path, 'r') as file:
            for line in file:
                line = line.strip()
                if "<clef" in line:
                    in_clef = True
                elif in_clef == True and "<sign>" in line:
                    temp = self.get_value(line, "sign")
                    if temp not in {"G", "F"}:
                        return False
                    elif cur_clef == "":
                        cur_clef = temp
                    elif cur_clef != temp:
                        return False
                elif "</clef>" in line:
                    in_clef = False

        return True
    
    # verifies we have no chords (the hand can't physically play chords anyway)
    def verifyNoChords(self) -> bool:
        with open(self.file_path, 'r') as file:
            for line in file:
                line = line.strip()
                if "<chord" in line:
                    return False
                if "<voice" in line:
                    value = int(self.get_value(line, "voice"))
                    #print("value is " + str(value))
                    if value != 1:
                        return False
        return True
    

if __name__ == "__main__":
    xml_file = fr"C:\Users\Error\Desktop\OEMER\XML Files\ClefChangeTest.musicxml"
    checker = MusicXMLChecker(xml_file)
    ok = checker.verifyAll()
    print("✅ All checks passed!" if ok else "❌ One or more checks failed.")