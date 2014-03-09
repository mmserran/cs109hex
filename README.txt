Mark Anthony Serrano (mmserran@ucsc.edu)
README file for CS 109 - Hw4

Notes:
	- Use "make clean" to remove object files, then "./" + tab + enter to run
	- Use "make spotless" to remove object files and executable
	- The program first prints the connectivity list for each cell 
		in the following format:	ij: (XRY:ab)
			where ints i, j, a, b < n
			and bool X denotes the existance of a path with a start node
			and bool Y denotes the existance of a path with an end node. 
	- It then prints out the hexboard, and who wins.
	  The winner is determined by the first cell with a path who has
	  reachability to both a start and end node.
	  	so for ex. 1R1 means Red won, while 1B1 means Blue won.
	- There is this strange bug concerning line 67 in PriorityQueue.cpp
		(and I suggest you try this with size = 4 on line 20 in 109hw4.cpp)
		When this line is commented out, a strange bug occurs. One spot in
		the hexboard appears to be unfilled, and in fact is in terms of
		the connectivity matrix. So to debug this, I decide to print out
		the priority queue to see where data is corrupted. But printing it
		out (line 67) makes the program work perfectly! I am stuck. C++ pls
	
What I learned:
	I learned that $@ is a macro for the file name of the target in a Makefile,
	and that $< is a macro for the name of the first dependency in a Makefile.