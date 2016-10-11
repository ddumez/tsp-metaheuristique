CC = g++
SOURCES = ./RGSC/RGSC.cpp ./Distancier/Distancier.cpp ./code_fourni.cpp ./3-opt/3opt.cpp
CFLAGS = -Wall -g
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./RGSC/*.o
	rm ./Distancier/*.o
	rm ./*.o
