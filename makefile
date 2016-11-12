CC = gpp
SOURCES = ./grille.cpp ./incomplet.cpp
CFLAGS = -Wall -O3
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
