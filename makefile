CC = gpp
SOURCES = ./grille.hpp ./incomplet.cpp ./complet.cpp ./grille.cpp ./variable.cpp ./carre.cpp
CFLAGS = -Wall -O3
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
