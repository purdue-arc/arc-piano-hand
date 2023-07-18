#include "pianoHandNamespace.h"
#include <fstream>
using namespace pianoHandNamespace;
// https://stackoverflow.com/questions/23603735/attempting-to-reference-a-deleted-function
void indent(std::ofstream& outfile, int indentLevel) {
    char *x = new char(2 * indentLevel + 1);
    for (int i = 0; i < 2 * indentLevel; i++) {
        x[i] = ' ';
    }
    x[2 * indentLevel] = '\0';
    outfile << x;
    return;
}
void newObject(std::ofstream& outfile, char *name, int *indentLevel) {
    indent(outfile, *indentLevel);
    outfile << "\"" << name << "\": {\n";
    (*indentLevel)++;
}
void newObject(std::ofstream& outfile, int name, int *indentLevel) {
    indent(outfile, *indentLevel);
    outfile << "\"" << name << "\": {\n";
    (*indentLevel)++;
}
void doneObject(std::ofstream& outfile, int *indentLevel) {
    indent(outfile, *indentLevel);
    outfile << "}";
    (*indentLevel)--;
}
void writeJSONtagToFile(std::ofstream& outfile, char *key, char *value, int *indentLevel) {
    indent(outfile, *indentLevel);
    outfile << "\"" << key << "\": " << value << ",\n";
}
void writeJSONtagToFile(std::ofstream& outfile, char *key, int value, int *indentLevel) {
    indent(outfile, *indentLevel);
    outfile << "\"" << key << "\": " << value << ",\n";
}

int writeLLtoFile(char *path, LinkedList *l) {
    std::ofstream outfile;
    outfile.open(path);
    int indentLevel = 1;
    outfile << "{\n";
    int i = 0;
    while (l != NULL) {
        Node n = l->n;
        newObject(outfile, "fs", &indentLevel);
        writeJSONtagToFile(outfile, "order", i, &indentLevel);
        for (auto f : n.getFingerState().getFingers()) {
            newObject(outfile, f.getID(), &indentLevel);
            writeJSONtagToFile(outfile, "midi_note_value", f.getNoteCurrentlyBeingPlayed().get_midi_note_value(), &indentLevel);
            writeJSONtagToFile(outfile, "velocity", f.getNoteCurrentlyBeingPlayed().get_velocity(), &indentLevel);
            doneObject(outfile, &indentLevel);
        }
        doneObject(outfile, &indentLevel);
        i++;
    }
    doneObject(outfile, &indentLevel);
    outfile.close();
}