//============================================================================
// Name        : 109hw4.cpp
// Author      : Mark Anthony Serrano
// Copyright   : Copyright Ira Pohl
// Description : CS109 Homework 4 - Hexboard main program
//============================================================================

#include <iostream>
#include <vector>
#include "Graph.h"
#include "PriorityQueue.h"

//============================================================================
// Hexboard test

int main() {

	// Create Graph test objects
	int size = 11;
	Graph hexboard(size, 0.7, 200.);

	int sum = 0;
	PriorityQueue allNodes;
	for( int i=0; i<size; ++i ) {
		for( int j=0; j<size; ++j ) {
			// add cell ij with random weight
			allNodes.add_with_priority(make_pair(i, j), 90.0*rand()/RAND_MAX);
			sum++;
		}
	}

	while (!allNodes.isEmpty()) {
		pair<int,int> u = allNodes.extract_min();
		hexboard.nextTurn(u.first, u.second);
	}
	cout << hexboard;

	StatusType winner = hexboard.verifyWinner();
	if (winner!=NONE) {
		if (winner==RED)
			cout << "RED WINS!" << endl;
		else
			cout << "BLUE WINS!" << endl;
	} else
		cout << "ERROR: now nobody wins" << endl;
	return 0;
}
