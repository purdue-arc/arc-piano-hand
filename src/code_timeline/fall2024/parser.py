from music21 import *
import pypianoroll
import matplotlib.pyplot as plt
import os


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
                'pitch': (music_element.pitch.step,
                          music_element.pitch.octave,
                          music_element.pitch.alter,
                          music_element.pitch.midi),
                'duration': music_element.quarterLength,
            }
            note_info.append(info)

        # chord
        elif isinstance(music_element, chord.Chord):
            info = {
                'type': 'chord',
                'pitches': [(n.pitch.step,
                             n.pitch.octave,
                             n.pitch.alter,
                             n.pitch.midi)
                            for n in music_element.notes],
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
        time_step = []
        if n['type'] == 'chord':
            for m in n['pitches']:
                time_step.append((m[3], n['duration']))
            time_steps.append(time_step)
        else:
            time_step.append((n['pitch'][3], n['duration']))
            time_steps.append(time_step)

    return time_steps


def main():
    note_info = parse_musicxml(
        '/Users/tristan.brideweser/Desktop/Purdue/Extracirricular/ARC/src/code_timeline/fall2024/music_files/note_length_testing.musicxml')
    time_steps = convert_to_time_steps(note_info)
    print(note_info)
    print(time_steps)


if __name__ == '__main__':
    main()
