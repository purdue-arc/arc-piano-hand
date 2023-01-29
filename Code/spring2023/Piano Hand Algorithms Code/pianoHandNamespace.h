#pragma once

namespace pianoHandNamespace {
	class Edge
	{
	public:

	private:
		double edgeWeight;
		Node startNode;
		Node endNode;
	};
	

	class Finger
	{
	public:
		Finger();
	};
	class FingeringState
	{
	public:
		FingeringState();
	};

	
	class Hand
	{
	public:
		Hand();
	};
	
	
	class Layer
	{
	public:
		Layer();
	private:
		Node nodes[];
	};
	
	
	class Node
	{
	public:
		Node();
	private:
		double weight;
		FingeringState fs;
	};
	
	
	class Note
	{
	private:
		int midi_note_value;
	public:
		Note(int midi_note_value);
		int get_midi_note_value();
	};
	
	
	class Trellis
	{
	public:
		Trellis();
	};

}