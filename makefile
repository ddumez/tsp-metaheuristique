CC = g++
SOURCES = ./RGSC/RGSC.cpp ./Distancier/Distancier.cpp ./code_fourni.cpp
CFLAGS = -Wall -g
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./RGSC/*.o
	rm ./Distancier/*.o
	rm ./*.o
