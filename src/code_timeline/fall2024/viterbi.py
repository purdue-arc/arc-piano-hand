from music21 import *
import matplotlib.pyplot as plt
import os
from collections import defaultdict


def parse_musicxml(file):
    """
    Parse a musicxml file and extract the relevant information
    NOTE:
    - step := letter of the note (ex. G, B, D, etc.)
    - octave := group of the note (ex. 0, 1, 2, etc.)
    - alter := flat (-1), normal (0), sharp (1)

    :param file: musicxml file
    :return: list of note info (type, pitch(es) -> [(step, octave, alter, midi)], duration)
    """
    score = converter.parse(file)

    note_info = []

    for music_element in score.recurse():
        # note
        if isinstance(music_element, note.Note):
            info = {
                'type': 'note',
                'pitch': [music_element.pitch.octave, music_element.pitch.step, music_element.pitch.alter],
                'duration': music_element.quarterLength,
            }
            note_info.append(info)

        # chord
        elif isinstance(music_element, chord.Chord):
            info = {
                'type': 'chord',
                'pitches': [[n.pitch.octave, n.pitch.step, n.pitch.alter, n.pitch.midi] for n in music_element.notes],
                'duration': music_element.quarterLength,
            }
            note_info.append(info)

    return note_info


def convert_to_time_steps(note_info):
    """

    :param note_info:
    :return: list of time steps (midi, duration)
    """
    time_steps = []

    for n in note_info:
        if n['type'] == 'chord':
            temp = []
            for note in n['pitches']:
                temp.append(note)
            time_steps.append(temp)
        else:
            time_steps.append(n['pitch'])
    return time_steps


def main():
    # TODO: path to hot cross buns
    music_file = ...
    note_info = parse_musicxml()
    time_steps = convert_to_time_steps(note_info)

    notePos = {'C': 0, 'D': 1, 'E': 2, 'F': 3, 'G': 4, 'A': 5, 'B': 6}

    notesToPlay = []

    for note in time_steps:
        temp = []
        temp.append(int(2 * (note[0] * 7 + notePos[note[1]] + 0.5 * (note[2]))))
        notesToPlay.append(temp)  # NEW
    # notesToPlay2 = [[1,2,3], [1,2], [6]]
    # notesToPlay = [[1,3], [1,2], [3,6], [1,2,3,4,5], [4,5], [8,9], [11], [2,3,4,5], [6,8]] #dataset of notes at each notesToPlay[i]

    # trellis graph
    possiblePositions = defaultdict(list)  # hashmap of all possible positions
    possiblePositions[-1].append(0)

    # values stored at each node of trellis graph goes here
    viterbiOutputs = defaultdict(list)
    # formatted to have one entry for each time period,
    # this entry is a list for every possible position we can call the data array,
    # each data point in this list holds three values: cost, number of moves, position of min cost upto that point
    # How do we go from this to find the actual position?
    # The time key and the index of the data in the data array indicates can be used in the possible positions dictionary to access the position:
    # Example, viterbiOutputs[time1][i] gives cost, number of moves, and position of min cost at the possible position possiblePositions[time1][i]
    viterbiOutputs[-1] = [[0, 0, 0]]

    # answer goes here after we backtrack
    finalSequence = [0] * len(notesToPlay)

    t = 0
    # we iterate over each individual section of time
    while t < (len(notesToPlay)):
        # for each time t, we identify each possible position x and store it in possible positions dictionary to create a trellis graph
        for x in range(notesToPlay[t][0] - 5 + (notesToPlay[t][-1] - notesToPlay[t][0] + 1), notesToPlay[t][0] + 1):
            possiblePositions[t].append(x)
        # i is the pointer in current layer, j is the pointer in the previous layer
        i = 0
        viterbiOutputs[t] = [0] * len(possiblePositions[t])
        while i < len(possiblePositions[t]):
            viterbiOutputs[t][i] = [9999, 0, 0]
            Min = False  # this is to indicate that we have reached the lowest possible value of 0
            j = 0
            prevLayerMin = 0
            while j < len(possiblePositions[t - 1]) and not Min:
                temp = viterbiOutputs[t][i][0]
                viterbiOutputs[t][i][0] = min(viterbiOutputs[t][i][0],
                                              abs(possiblePositions[t][i] - possiblePositions[t - 1][j]) +
                                              viterbiOutputs[t - 1][j][0])
                if viterbiOutputs[t][i][0] == viterbiOutputs[t - 1][j][0]:  # if the distance needed to travle is 0
                    viterbiOutputs[t][i][1] = viterbiOutputs[t - 1][j][1]
                    prevLayerMin = j
                    Min = True
                elif temp != viterbiOutputs[t][i][0]:  # if distance needed to travel decreases
                    viterbiOutputs[t][i][1] = viterbiOutputs[t - 1][j][1] + 1
                    prevLayerMin = j
                    j += 1
                else:  # if the distance needed to travel is higher than it currently is
                    j += 1
                viterbiOutputs[t][i][2] = prevLayerMin
            i += 1
        t += 1

    print('Possible positions: ', possiblePositions, '\n')
    print('viterbieOutputs: ', viterbiOutputs, '\n')

    # backtracking
    k = 0
    while k < len(viterbiOutputs[len(notesToPlay) - 1]):
        temp = 9999
        if viterbiOutputs[len(notesToPlay) - 1][k][0] < temp:
            temp = viterbiOutputs[len(notesToPlay) - 1][k][2]
        finalSequence[-1] = temp
        k += 1
    time = len(notesToPlay) - 1

    while time >= 0:
        if time > 0:
            finalSequence[time - 1] = viterbiOutputs[time][finalSequence[time]][2]
        finalSequence[time] = possiblePositions[time][finalSequence[time]]
        time -= 1

    finalSequence = [1 / 2 * x for x in finalSequence]

    print('finalSequence: ', finalSequence, '\n')


if __name__ == '__main__':
    main()
