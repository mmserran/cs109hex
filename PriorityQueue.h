//============================================================================
// Name        : PriorityQueue.h
// Author      : Mark Anthony Serrano
// Copyright   : please cite
// Description : CS109 Homework 4 - Header file for Priority Queue Class
//============================================================================

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

using namespace std;

//============================================================================
// Priority Queue Class Declaration (Min Binary Heap)

class PriorityQueue {
private:
	// Node structs will be elements of the heap
	struct Node {
		pair<int,int> id;
		double distance;

		int arrayPos;
	};
	vector<Node> heap;
	int parent(Node i);
	int left(Node i);
	int right(Node i);
	void swap(Node i, Node j);
	int minChild(Node id);
public:
	PriorityQueue() {}
	bool isEmpty() { return heap.size() == 0; }
	// add_with_priority().. Adds the element v to the priority queue
	void add_with_priority(pair<int,int> v, double dist);
	// decrease_priority().. Modifies the priority of a node v
	void decrease_priority(pair<int,int> v, double altDist);
	// extract_min().. Return and remove node with lowest distance
	pair<int,int> extract_min();
	// toString().. Does not modify anything in the class
	const string toString() const;
};

#endif /* PRIORITYQUEUE_H_ */
