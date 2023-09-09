#pragma once
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <format>
#include <string>
#include <string_view>
#include <assert.h>

namespace pianoHandNamespace
{
	const int MIN_NOTE_VALUE = 0;
	const int MAX_NOTE_VALUE = 127;

	const int OK = -1;
	const int NOTE_ERROR = -2;
	const int SIZE_ERROR = -3;
	const int NOT_ENOUGH_LAYERS = -4;

	// An object class containing a note value as well as some helper methods
	class Note
	{
	public:
		// Object methods
		Note(int midi_note_value);
		Note(int midi_note_value, int velocity);
		int get_midi_note_value();
		bool equals(Note n);
		int get_velocity();

	private:
		int midi_note_value;
		int velocity;
	};

	// An object class representing a finger
	class Finger
	{
	public:
		Finger(int id);
		Finger(int id, Note n);
		int getID();
		Note getNoteCurrentlyBeingPlayed();
		bool isNoteBeingPlayed();
		void setNoteCurrentlyBeingPlayed(Note note);
		void removeNoteBeingPlayed();

	private:
		int id;
		Note noteCurrentlyPlaying = NULL;
	};
	// Do we need add'l variables for this class to make multiple types of fingers?

	// An object class representing a finger state
	class FingerState
	{
	public:
		FingerState();
		FingerState(int capacity);
		void free();
		Finger *get(int idx);
		int getSize();
		int getCapacity();
		int add(Finger *f);
		void remove(Finger *f);
		Finger **getFingers();
		Note get_note(Finger *f);
		bool exists(Finger *f);

	private:
		int size;
		int capacity;
		Finger **state;
	};

	// An object class representing a hand
	class Hand : public FingerState
	{
	public:
		Hand(int size);
		void free();

	private:
		int size;
		Finger **fingers;
		int rotation;
		int position;
	};

	// An object class representing a trellis node
	class Node
	{
	public:
		Node();
		Node(FingerState *fs_ptr);
		Node(double weight, FingerState *fs_ptr);
		double getWeight();
		void setWeight(double weight);
		FingerState *getFingerState();

	private:
		double weight;
		FingerState *fs_ptr;
	};

	// An object class representing a trellis layer
	class Layer
	{
	public:
		Layer();
		int add(Node *node);
		int remove(Node *node);
		std::vector<Node *> getNodes();

	private:
		std::vector<Node *> nodes;
	};

	// An object class representing a trellis
	class Trellis
	{
	public:
		Trellis(int n_layers);
		void free();
		int get_n_layers();
		Layer *get_layer(int n);

	private:
		int n_layers;
		Layer **layers;
	};

	// A class containing cost functions for analyzing finger states
	class costFunctions
	{
	public:
		static double stretch(Finger *f1, Finger *f2);
		static double vertical_cost(FingerState *fs_ptr);
		static double horizontal_cost(FingerState *fs_ptr);
		static double finger_range_cost_hand(FingerState *fs_ptr);
		static double aggregate_cost(FingerState *fs_curr, FingerState *fs_next);
	};
}