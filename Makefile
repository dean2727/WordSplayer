# Dean Orenstein
# CSCE 221 518
# Makefile for project 3
# An Aggie does not lie, cheat or steal or tolerate those who do.

CXX = g++
FLAGS = -Wall -c -std=c++11
OBJECTS = driver.o HashedSplays.o SplayTree.o Node.o Util.o
PROJ = Proj3

$(PROJ): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

driver.o: driver.cpp HashedSplays.h SplayTree.h Exceptions.h Node.h DS_EXCEPTIONS.h Util.h Exceptions.h
	$(CXX) $(FLAGS) -c $<

HashedSplays.o: HashedSplays.cpp HashedSplays.h SplayTree.h Exceptions.h Node.h DS_EXCEPTIONS.h Util.h Exceptions.h
	$(CXX) $(FLAGS) -c $<

SplayTree.o: SplayTree.cpp SplayTree.h Node.h DS_EXCEPTIONS.h Util.h
	$(CXX) $(FLAGS) -c $<

Node.o: Node.cpp Node.h Util.h
	$(CXX) $(FLAGS) -c $<

Util.o: Util.cpp Util.h
	$(CXX) $(FLAGS) -c $<


.PHONY: clean run valgrind

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./$(PROJ) $(DATA)

valgrind:
	valgrind --leak-check=full ./Proj3 $(DATA)