//============================================================================
// Name        : Graph.h
// Author      : Mark Anthony Serrano
// Copyright   : please cite
// Description : CS109 Homework 4 - Header file for Graph Class
//============================================================================

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>

using namespace std;

// Red bridges NS, Blue bridges WE
enum StatusType { RED, BLUE, NONE };

//============================================================================
// Graph Class Declaration (undirected)
// 		This graph maintains the invariant that only same-colored cells are
// 		on each other's adjacency lists in terms of connectivity.
//		Therefore any path's color can be revealed by anyone of its cells.

class Graph {
private:
	// Cell struct will be the adjacency list element
	struct Cell {
		int i;
		int j;
		vector< pair<int,int> > connectedCells;

		// Since there can be only one winner, only one path will have
		// 	both of these booleans true
		bool connectedToStartNode = false;
		bool connectedToEndNode = false;
		StatusType state;
	};
	static bool rand_flg;					// bool checking if rand() was seeded

	static int turn;						// Max n*n turns
	static StatusType currentPlayer;		// Who's turn is it?
	vector< vector<Cell> >g1;				// The graph object

	int size;					// Number of nodes
	vector<double> dist;		// Distances at each node
	vector<int> prev;			// Previous node in path

	//=== Helper Functions ===================
	// probability().. Return a random double
	inline double probability();
	// update(i, j, startReq, endReq).. updates the req status of cell ij
	void update(int i, int j, bool startReq, bool endReq);
	// initRand().. Checks if rand() has been seeded
	inline void initRand();
	// Operator Overload
	friend ostream& operator<<(ostream& os, const Graph& obj);
public:
	// === Constructor =======================
	Graph(int s, double density, double range) {

		// Resize graph
		this->size = s;
		g1.resize(size);

		dist.resize(size);
		prev.resize(size);

		// Random graph procedure
		init(density, range);
	}
	//=== Manipulation Functions =============
	// init().. Initializes the graph with random data
	void init(double density, double range);
	// addEdge(i, j, weight).. Adds a new edge between nodes i and j
	// 						   with the specified weight. Default w=1.0
	void addEdge(int uX, int uY, int vX, int vY, double weight=1.0);
	// nextTurn().. advances a turn
	void nextTurn(int i, int j);
	// changeState(i, j, updatedState).. updates cell ij to its new state
	void changeState(int i, int j, StatusType updatedState);
	//=== Access Functions ===================
	// getAdjList(i, j).. returns a list of all cells adjacent to ij
	vector< pair<int,int> > getAdjList(int i, int j);
	// verifyWinner().. checks if a winner exists
	StatusType verifyWinner();
	// toString().. Returns a string representing the graph
	const string toString() const;
};


#endif /* GRAPH_H_ */
