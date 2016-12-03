CXX = g++
SOURCES = ./2-opt/2opt.cpp ./3-opt/3opt.cpp ./Distancier/Distancier.cpp ./Path-Relinking/PathRel.cpp ./RGSC/RGSC.cpp ./vnd/vnd.cpp ./vns/vns.cpp code_fourni.cpp
CPPFLAGS = -Wall -g
.PHONY = clean

all: main

main: $(SOURCES:.cpp=.o)

clean: 
	rm ./*.o
	rm ./2-opt/*.o
	rm ./3-opt/*.o
	rm ./Distancier/*.o
	rm ./Path-Relinking/*.o
	rm ./RGSC/*.o
	rm ./vnd/*.o
	rm ./vns/*.o
