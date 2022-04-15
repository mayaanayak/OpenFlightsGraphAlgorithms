#Executable Name
EXENAME = final_project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = parseDat.o main.o makeGraph.o

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
.PHONY: all test clean output_msg

project : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

<<<<<<< HEAD
<<<<<<< HEAD
test: output_msg parseDat.cpp main.cpp
	$(LD) parseDat.cpp main.cpp $(LDFLAGS) -o test_output
=======
test: output_msg catch/catchmain.cpp tests/tests.cpp parseDat.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp parseDat.cpp $(LDFLAGS) -o test_output
>>>>>>> 6d43924604136715cdbd5b4172525e90383e039e
=======
test: output_msg parseDat.cpp main.cpp makeGraph.cpp
	$(LD) parseDat.cpp main.cpp makeGraph.cpp $(LDFLAGS) -o test_output
>>>>>>> c430e94ca731ae883c2db3b3fedf6243e7bbbb81

clean:
	-rm -f *.o $(EXENAME) test
