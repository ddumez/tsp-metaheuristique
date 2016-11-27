CC = g++
SOURCES = ./Distancier/Distancier.cpp ./code_fourni.cpp ./RGSC/RGSC.cpp ./3-opt/3opt.cpp ./vnd.cpp ./vns.cpp ./Path-Relinking/PathRel.cpp
CFLAGS = -Wall -O3
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
	rm ./3-opt/*.o
	rm ./Distancier/*.o
