import mido as m
import time as t

mid = m.MidiFile('test.mid')
with m.open_output('USB MIDI Interface') as outport:
    for msg in mid:
        type(msg)

        # Send message

        # After sending message, wait with python

