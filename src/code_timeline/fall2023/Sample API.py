from flask import Flask    
import mido as mi
import music21 as m21
import json
import random
from markupsafe import escape

app = Flask(__name__)

def note_to_midi(note):
    note_map = {'C0': 12,'C#0': 13,'D0': 14,'D#0': 15,'E0': 16,'F0': 17,'F#0': 18,'G': 19,'G#0': 20,'A': 21,'A#0': 22,'B': 23,'C1': 24,}
    return note_map.get(note, -1)  

index = 0
notes_lines = ['<h1> Piano Hand API using Flask.API </h1>','<h2> Notes: </h2>']
attributes = {'On_Off': 'note_on', 'Channel':0}
times = [random.randint(5,20) for j in range(14)]

#cont = True
for i in 'GGGAAABBAAAGGG':
    attributes['Note'] = note_to_midi(i)
    attributes['Time'] = times[index]
    index += 1
    notes_lines.append(json.dumps(attributes))

"""while (cont):
    current_note = input("Enter note and time, separated by a space (Type STOP to stop): ")
    if (current_note == "STOP"):
        cont = False
        break
    items = current_note.split(" ")
    attributes['Note'] = items[0]
    attributes['Time'] = items[-1]
    notes_lines.append(json.dumps(attributes))
"""

@app.route('/')
def home():
    return ("<h1>Purdue Piano API, navigate to Notes</h1>")

@app.route('/notes')
def index():
    html = ''
    for note_line in notes_lines:
        html += '<p> {0} <p>'.format(note_line)
    return (html)
    
if __name__=='__main__':
   app.run("")