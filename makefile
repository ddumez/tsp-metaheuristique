CC = g++
SOURCES = ./Distancier/Distancier.cpp ./code_fourni.cpp ./3-opt/3opt.cpp ./vnd.cpp ./vns.cpp
CFLAGS = -Wall -g
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
	rm ./3-opt/*.o
	rm ./Distancier/*.o
