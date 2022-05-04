#Executable Name
EXENAME = final_project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = parseDat.o main.o makeGraph.o iddfs.o dijkstra.o DFS.o 

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include cs225/make/cs225.mk

# Define Makefile Rules
.PHONY: all test clean

project : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

test: parseDat.o makeGraph.o iddfs.o dijkstra.o DFS.o tests/tests.o
	$(LD) parseDat.o makeGraph.o iddfs.o dijkstra.o DFS.o tests/tests.o $(LDFLAGS) -o test_output

main:  parseDat.o makeGraph.o iddfs.o dijkstra.o DFS.o main.o
	$(LD) parseDat.o makeGraph.o iddfs.o dijkstra.o DFS.o main.o $(LDFLAGS) -o main_output

# test: output_msg parseDat.cpp main.cpp makeGraph.cpp iddfs.cpp dijkstra.cpp tests/tests.cpp
# 	$(LD) parseDat.cpp main.cpp makeGraph.cpp iddfs.cpp dijkstra.cpp tests/tests.cpp $(LDFLAGS) -o test_output

clean:
	-rm -f *.o $(EXENAME) test
