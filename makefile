CXX = g++
SOURCES = ./grille.cpp ./incomplet.cpp ./complet.cpp ./variable.cpp ./carre.cpp
CPPFLAGS = -Wall -O3
CXXFLAGS := -std=c++11
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
