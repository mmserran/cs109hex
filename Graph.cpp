//============================================================================
// Name        : Graph.cpp
// Author      : Mark Anthony Serrano
// Copyright   : please cite
// Description : CS109 Homework 4 - Graph Class Implementation
//============================================================================

#include <sstream>		// std::ostringstream oss
#include <cstdlib>		// rand()
#include <ctime>		// Seed to rand()
#include <limits>		// std::numeric_limits<int>::max()
#include <iomanip> 		// std::setw()
#include <cmath>		// round()
#include <algorithm>	// min_element
#include <utility>		// pair<T,T>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "Graph.h"
#include "PriorityQueue.h"


//============================================================================
// Graph Class Definition

bool Graph::rand_flg = false;			// Init the static class variable
int Graph::turn = 0;					// Initiate to Turn 0
StatusType Graph::currentPlayer = RED;	// Red player goes first


//=== Helper Functions ===================
inline double Graph::probability() {
	// return random double between 0 and 1
	return 1.0*rand()/RAND_MAX;
}
// update(i, j, startReq, endReq).. updates the req status of cell ij
void Graph::update(int i, int j, bool startReq, bool endReq) {

	bool stReq = (g1[i][j].connectedToStartNode || startReq);
	bool enReq = (g1[i][j].connectedToEndNode || endReq);

	if ( g1[i][j].connectedToStartNode==stReq
			&& g1[i][j].connectedToEndNode==enReq ) {
		return;
	} else {

		// Update cell ij
		g1[i][j].connectedToStartNode = stReq;
		g1[i][j].connectedToEndNode = enReq;

		// Perform a tree traversal and update each node
		vector< pair<int,int> > adjList = g1[i][j].connectedCells;
		for (auto u=adjList.begin(); u!=adjList.end(); ++u)
			update(u->first, u->second, stReq, enReq);
		return;
	}
}
inline void Graph::initRand() {
	// Initiate random seed if necessary
	if (!rand_flg) {
		srand(time(nullptr));
		this->rand_flg = true;
	}
}
ostream& operator<<(ostream& os, const Graph& obj){
	// Overload the printing operator
	os << obj.toString();
	return os;
}

//=== Manipulation Functions =============
// init().. Populates the graph with edges that replicates
//			the Hexboard connectivity. There are 4 cases.
void Graph::init(double density, double range) {
	// Start rand()
	initRand();

	for( int i=0; i<size; ++i ) {
		for( int j=0; j<size; ++j ) {
			Cell temp;
			temp.i = i;
			temp.j = j;
			temp.state = NONE;
			g1[i].push_back(temp);
		}
	}
	return;
}
// nextTurn().. advances a turn after current player makes their move
void Graph::nextTurn(int i, int j) {
	// Advance turn
	turn++;
	if (currentPlayer==RED)
		currentPlayer = BLUE;
	else
		currentPlayer = RED;
	changeState(i, j, currentPlayer);
	return;
}
// changeState(i, j, updatedState).. updates cell ij to its new state
void Graph::changeState(int i, int j, StatusType updatedState) {
	// Update the state
	g1[i][j].state = updatedState;

	// Case: Red state - N/S
	if (updatedState == RED) {
		if (j==0)
			update(i, j, true, false);
		if (j==size-1)
			update(i, j, false, true);
	}
	// Case: Blue state - W/E
	else {
		if (i==0)
			update(i, j, true, false);
		if (i==size-1)
			update(i, j, false, true);
	}

	// Get ij's adjacency list
	vector< pair<int,int> > adjList = getAdjList(i, j);

	// Let u be a neighbor in ij's adj list
	for( auto u=adjList.begin(); u!=adjList.end(); ++u ) {
		// add an edge if they share the same color
		StatusType neighborColor = g1[u->first][u->second].state;
		if ( neighborColor==updatedState ) {
			addEdge(u->first, u->second, i, j);
		}
	}
	return;
}
// addEdge()..	Adds an edge between nodes i and j using weight w
/* 				INVARIANT:	edges in this hexboard only connects
 *							two nodes of the same color
 *				This function assumes it will never have the case
 *				that: 		(uX, uY) == (vX, vY)
 */
void Graph::addEdge(int uX, int uY, int vX, int vY, double w) {
	g1[uX][uY].connectedCells.push_back(make_pair(vX, vY));
	g1[vX][vY].connectedCells.push_back(make_pair(uX, uY));

	bool uStart = g1[uX][uY].connectedToStartNode;
	bool vStart = g1[vX][vY].connectedToStartNode;
	bool uEnd 	= g1[uX][uY].connectedToEndNode;
	bool vEnd 	= g1[vX][vY].connectedToEndNode;


	// Update start node connectivity requirement
	if (uStart || vStart) {
		if (!uStart)
			update(uX, uY, vStart, (uEnd || vEnd));
		if (!vStart)
			update(vX, vY, uStart, (uEnd || vEnd));
	}
	// Update end node connectivity requirement
	if (uEnd || vEnd) {
		if (!uEnd)
			update(uX, uY, (uStart || vStart), vEnd);
		if (!vEnd)
			update(vX, vY, (uStart || vStart), uEnd);
	}

	return;
}

//=== Access Functions ===================
// getAdjList(i, j).. returns a list of all cells adjacent to ij
vector< pair<int,int> > Graph::getAdjList(int i, int j) {
	// As a hexagon, there are only 6 potential spots for edges to be made
	// Given a cell at (i, j), those positions are as follows:
	/* 		I.  ( i,  j-1)	  II.(i+1, j-1)
	 * 		III.(i-1, j  )	  IV.(i+1,  j )
	 * 		V.  (i-1, j+1)	  VI.( i,  j+1)
	 */
	vector< pair<int,int> > adjList;
	int n = size-1;		// account for 0 index numbering
	if ( j!=0 ) {
		adjList.push_back(make_pair( i,  j-1));		// case I.
		if ( i!=n )
			adjList.push_back(make_pair(i+1, j-1));	// case II.
	}
	if ( i!=0 ) {
		adjList.push_back(make_pair(i-1,  j ));		// case III.
		if ( j!=n )
			adjList.push_back(make_pair(i-1, j+1));	// case V.
	}
	if ( i!=n )
		adjList.push_back(make_pair(i+1, j));		// case IV.
	if ( j!=n )
		adjList.push_back(make_pair(i, j+1));		// case VI.

	return adjList;
}
// verifyWinner().. checks if a winner exists
StatusType Graph::verifyWinner() {
	for( int i=0; i<size; ++i ) {
		for( int j=0; j<size; ++j ) {
			if (g1[i][j].connectedToStartNode && g1[i][j].connectedToEndNode) {
				cout << "at cell " << i << j << endl;
				return g1[i][j].state;
			}
		}
	}
	return NONE;
}
// toString().. Does not modify anything in the class
const string Graph::toString() const {
	std::ostringstream oss;
	oss.precision(3);

	// Print the connectivity list for each cell
	for( int i=0; i<size; ++i) {
		for (int j=0; j<size; ++j) {
			vector< pair<int,int> > connectedList = g1[i][j].connectedCells;
			if (g1[i][j].state==RED)
				oss << "R ";
			else
				oss << "B ";
			oss << i << j << ": ";

			// ex. 0R1 would represent a cell that is Red,
			//			is not connected by some path to a start node,
			//			and is connected by some path to an end node.
			for (auto u=connectedList.begin(); u!=connectedList.end(); ++u){
				oss << "(";
				if (g1[i][j].connectedToStartNode)
					oss << "1";
				else
					oss << "0";

				if (g1[i][j].state == RED)
					oss << "R";
				else
					oss << "B";

				if (g1[i][j].connectedToEndNode)
					oss << "1";
				else
					oss << "0";
				oss << ":" << u->first << "" << u->second << ") ";
			}
			oss << endl;
		}
	}

	const string margin{"  "};

	oss << endl << "graph size " << size << endl << endl << margin;

	for( int i=0; i<size; ++i )
		// Print i header
		oss << setw(3) << i << " ";

	// the "________" top art
	oss << endl << " " << margin;
	oss << setfill('_') << setw(size*4) << "" << setfill(' ');

	for( int i=0; i<size; ++i ) {
		// Print j header
		oss << endl << setw(i+1) << i << margin << "\\";

		// Print graph data
		for( int j=0; j<size; ++j ) {
			StatusType current = g1[j][i].state;
			switch (current) {
				case RED:
					oss << " R";
					break;
				case BLUE:
					oss << " B";
					break;
				case NONE:
					oss << " _";
					break;
				default:
					cout << "error in Graph::toString()";
			}
			oss << " \\";
		}
	}
	oss << endl << endl;
	return oss.str();
}
