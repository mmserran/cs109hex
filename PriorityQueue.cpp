//============================================================================
// Name        : PriorityQueue.cpp
// Author      : Mark Anthony Serrano
// Copyright   : please cite
// Description : CS109 Homework 4 - Priority Queue Class Implementation
//============================================================================

#include <sstream>		// std::ostringstream oss
#include <cstdlib>		// rand()
#include <ctime>		// Seed to rand()
#include <limits>		// std::numeric_limits<int>::max()
#include <iomanip> 		// std::setw()
#include <cmath>		// round()
#include <algorithm>	// std::swap()
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "Graph.h"
#include "PriorityQueue.h"

using namespace std;


//============================================================================
// Priority Queue Class Definition (Min Binary Heap)

//=== Helper Functions ===================
int PriorityQueue::parent(Node i)	{ return (i.arrayPos-1)/2; }
int PriorityQueue::left(Node i)		{ return i.arrayPos*2 + 1; }
int PriorityQueue::right(Node i)	{ return i.arrayPos*2 + 2; }
void PriorityQueue::swap(Node i, Node j) {
	int temp = j.arrayPos;
	heap[j.arrayPos].arrayPos = i.arrayPos;
	heap[i.arrayPos].arrayPos = temp;

	std::swap(heap[i.arrayPos], heap[j.arrayPos]);
	return;
}
int PriorityQueue::minChild(Node id) {
	if (left(id) > heap.size() || right(id) > heap.size())
		return -1;
	if (heap[left(id)].distance < heap[right(id)].distance)
		return heap[left(id)].arrayPos;
	else
		return heap[right(id)].arrayPos;
}

//=== Manipulation Functions =============
// add_with_priority().. Adds the element v to the priority queue
void PriorityQueue::add_with_priority(pair<int,int> v, double dist) {
	Node temp;

	temp.id = v;
	temp.distance = dist;
	temp.arrayPos = heap.size();
	heap.push_back(temp);

	// Percolate up in O(log(n)) time
	Node id = temp;
	if (heap.size() > 1)
		while (heap[parent(id)].distance > id.distance) {
			swap(heap[parent(id)], heap[id.arrayPos]);
			id = heap[parent(id)];
		}

	//cout << toString();			// THIS IS HIM D:<
	return;
}
// decrease_priority().. Modifies the priority of a node v
void PriorityQueue::decrease_priority(pair<int,int> v, double altDist) {
	Node id;
	// Search for node in heap in O(n) time
	for (int i=0; i<heap.size(); ++i)
		if (heap[i].id == v) {
			heap[i].distance = altDist;
			id = heap[i];
			break;
		}
	// Percolate up in O(log(n)) time
	if (heap.size() > 1) {
		while (heap[parent(id)].distance > id.distance) {
			swap(heap[parent(id)], heap[id.arrayPos]);

			id = heap[parent(id)];
		}
	}
	return;
}
// extract_min().. Return and remove node with lowest distance
pair<int,int> PriorityQueue::extract_min() {
	Node result = heap.front();		// extract the min node
	heap.front() = heap.back();		// copy back node to front node
	heap.front().arrayPos = 0;
	heap.pop_back();				// delete the back node

	// Percolate down in O(log(n)) time
	Node parent = heap.front();
	Node child = heap[minChild(parent)];

	while (parent.distance > child.distance) {
		swap(heap[parent.arrayPos], heap[child.arrayPos]);

		parent = child;
		if ( minChild(parent)==-1 )
			break;
		else
			child = heap[minChild(parent)];
	}
	return result.id;
}

//=== Access Functions ===================
// toString().. Does not modify anything in the class
const string PriorityQueue::toString() const {
	std::ostringstream oss;
	oss.precision(3);


	// Print priority queue data
	for( unsigned int i=0; i <heap.size(); ++i ) {
		oss << heap[i].id.first << heap[i].id.second
			<< "(" << heap[i].distance
			<< setw(3);

	}

	oss << "\n";
	return oss.str();
}
