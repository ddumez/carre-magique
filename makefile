CC = gpp
SOURCES = ./grille.cpp ./incomplet.cpp ./complet.cpp ./variable.cpp ./carre.cpp
CFLAGS = -Wall -g
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
rm ./*.o
