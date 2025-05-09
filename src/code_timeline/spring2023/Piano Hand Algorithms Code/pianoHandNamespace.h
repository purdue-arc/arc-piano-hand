#pragma once
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <format>
#include <string>
#include <string_view>
#include <assert.h>

namespace pianoHandNamespace {
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
		int get_midi_note_value();
		bool equals(Note n);
	private:
		int midi_note_value;
	};

	const Note NULL_NOTE = Note(-1);

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
		int size();
		int add(Finger f); // add error codes
		static FingerState null_state();
		std::vector<Finger> getFingers();
		std::vector<Note> getNotes();
		std::vector<Finger> get(Note n);
		Finger get_finger(Finger f);
		FingerState make_copy();
		Note get(Finger f);
		//assigns the finger to note in a finger state
		void assignFingerToNote(Finger f, Note n);
		//fingers available to play 
        std::vector<Finger> getRemainingFingers();
		//notes remaining to be played 
		std::vector<Note> getRemainingNotes(std::vector<Note> notesToPlay);
		// add more methods here
		int uniquifyFingerwise();
		int uniquifyNotewise();

	private:
		std::vector<Finger> state;
	};

	// An object class representing a hand
	class Hand
	{
	public:
		Hand(int size);
		Hand(Finger fingers[]);
		Hand(std::vector<Finger> fingers);
	private:
		std::vector<Finger> fingers;
		int rotation;
		int position;
	};

	// An object class representing a trellis node
	class Node
	{
	public:
		Node();
		Node(FingerState fs);
		Node(double weight, FingerState fs);
		double getWeight();
		void setWeight(double weight);
		FingerState getFingerState();
	private:
		double weight;
		FingerState fs;
	};

	// An object class representing a trellis edge
	class Edge
	{
	public:
		Edge(Node startNode, Node endNode);
		Edge(double weight, Node startNode, Node endNode);
		Edge(double weight, Node startNode, Node endNode, int startLayerIndex, int endLayerIndex);
		double getWeight();
		void setWeight(double weight);
		int getStartLayerIndex();
		int getEndLayerIndex();
		Node getStartNode();
		Node getEndNode();
		//string toString();

	private:
		double edgeWeight;
		Node startNode;
		Node endNode;
		int startLayerIndex;
		int endLayerIndex;
	};

	// An object class representing a trellis layer
	class Layer
	{
	public:
		Layer();
		int add(Node node);
		int remove(Node node);
		std::vector<Node> getNodes();
	private:
		std::vector<Node> nodes;
	};
	
	// An object class representing a trellis
	class Trellis
	{
	public:
		Trellis();
		int link_edges();
	private:
		std::vector<Layer> layers;
		std::vector<Edge> edges;

	};

	// A class containing cost functions for analyzing finger states
	class costFunctions
	{
	public: 
		static double vertical_cost(FingerState fs);
		static double horizontal_cost(FingerState fs);
		static double finger_range_cost_hand(FingerState fs);
		static double aggregate_cost(FingerState fs);
	};
}