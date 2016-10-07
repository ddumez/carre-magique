CC = gpp
SOURCES = ./grille.hpp ./incomplet.cpp ./complet.cpp ./grille.cpp ./variable.cpp ./carre.cpp
CFLAGS = -Wall -O3
LDLIBS = -lpthread
.PHONY = clean

all: main

main: $(SOURCES:.c=.o)

clean: 
	rm ./*.o
