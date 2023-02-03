#pragma once
#include <unordered_map>
#include <string>

namespace pianoHandNamespace {
	#define static int MIN_NOTE_VALUE = 0;
	#define static int MAX_NOTE_VALUE = 127;

	// An object class containing a note value as well as some helper methods
	class Note
	{
	public:
		// Constants

		// Object methods
		Note(int midi_note_value);
		int get_midi_note_value();
	private:
		int midi_note_value;
	};

	// An object class representing a finger
	class Finger
	{
	public:
		Finger();
		Note getNoteCurrentlyBeingPlayed();
		bool isNoteBeingPlayed();
		void setNoteCurrentlyBeingPlayed(Note note);
	private:
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
		std::vector<Finger> getFingers();
		std::vector<Note> getNotes();
		Finger get(Note n);
		Note get(Finger f);
		// add more methods here

	private:
		std::unordered_map<Finger, Note> state;
	};

	// An object class representing a hand
	class Hand
	{
	public:
		Hand(int size);
		Hand(Finger fingers[]);
	private:
		std::vector<Finger> fingers;
		int rotation;
		int position;
	};

	// An object class representing a trellis node
	class Node
	{
	public:
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
		Edge(double weight, Node startNode, Node endNode,int startLayerIndex, int endLayerIndex);
		double getWeight();
		void setWeight(double weight);
		int getStartLayerIndex();
		int getEndLayerIndex();
		Node getStartNode();
		Node getEndNode();
		char[] toString();
		minWeight(vector<Edge> te);

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

	private:
		std::vector<Node> nodes;
	};
	
	// An object class representing a trellis
	class Trellis
	{
	public:
		Trellis();
	private:
		std::vector<Layer> layers;
		std::vector<Edge> edges;
	};
}