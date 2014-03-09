# Mark Anthony Serrano (mmserran@ucsc.edu)
# Makefile for CS109 - Hw4
# Please feel free to reuse, cite me

VALGRIND   = valgrind --leak-check=full --show-reachable=yes

EXECUTABLE = 109hw4
HSOURCES   = Graph.h PriorityQueue.h
CSOURCES   = 109hw4.cpp Graph.cpp PriorityQueue.cpp

GCC        = g++
CFLAGS     = -c -std=c++11
ALLSRC     = ${CSOURCES}
OBJS       = ${ALLSRC:.cpp=.o}


#
# The first target is always ``all''
# We have it build the executable.
#
all : ${EXECUTABLE}

#
# Build the executable image from the object files.
#
${EXECUTABLE} : ${OBJS}
	${GCC} -o $@ ${OBJS} 

#
# Build an object file from a C++ source file.
#
%.o : %.cpp
	${GCC} ${CFLAGS} $<

#
# Utility functions.
#
# ``make memcheck''.. performs a valgrind memory check
memcheck:
	$(VALGRIND) ./$(EXECUTABLE)
# ``make clean''.. removes *.o files
clean:
	rm -f $(OBJS)
# ``make spotless''.. removes all *.o files and the executable
spotless:
	rm -f $(OBJS) $(EXECUTABLE)
