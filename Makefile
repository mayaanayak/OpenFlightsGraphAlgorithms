#Executable Name
EXENAME = final_project
TEST = test
DIJKSTRA = dijkstra

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = parseDat.o main.o makeGraph.o dijkstra.o

# PageRank.o airport_graph.o Flight.o Djikstras.o BFS.o Landmark.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include test/make/make.mk
include make/make.mk

# Define Makefile Rules
.PHONY: all test clean output_msg testdijkstra

project : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

dijkstra: dijkstra.cpp tests/testdijkstra.cpp
	$(LD) tests/testdijkstra.cpp dijkstra.cpp $(LDFLAGS) -o dijkstra

test: output_msg parseDat.cpp main.cpp dijkstra.cpp
	$(LD) parseDat.cpp main.cpp dijkstra.cpp$(LDFLAGS) -o test_output

test: output_msg catch/catchmain.cpp tests/tests.cpp parseDat.cpp tests/testdijkstra.cpp dijkstra.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp parseDat.cpp tests/testdijkstra.cpp dijkstra.cpp $(LDFLAGS) -o test_output

test: output_msg parseDat.cpp main.cpp makeGraph.cpp dijkstra.cpp
	$(LD) parseDat.cpp main.cpp makeGraph.cpp dijkstra.cpp $(LDFLAGS) -o test_output

clean:
	-rm -f *.o $(EXENAME) test
