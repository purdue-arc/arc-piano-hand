
class Hand(object):
    def __init__(self):
        """
        A Hand has:
        - fingers (list)
        - thumb*
        """
        self.fingers = []
        # self.thumb = []

class Finger(object):
    def __init__(self):
        """
        A Finger has:
        - midi value (int)
        - playing (bool)
        """
        self.midi = None
        self.playing = False

# depedent on the progress of hardware/electronics
"""
class Thumb(object):
    def __init__(self):
"""

def main():
    num_fingers = 5
    hand = Hand()
    fingers = [Finger() for _ in range(0, num_fingers)]

    hand.fingers = fingers

    print(hand.fingers)

if __name__ == "__main__":
    main()