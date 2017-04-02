CXX = g++
CXXFLAGS = -std=c++0x

PROG1 = Lab5SeanSolberg
PROGS = ${PROG3}

Lab5SeanSolberg: utils.o critter.o doodlebug.o ant.o main.o
	${CXX} -g utils.o critter.o doodlebug.o ant.o main.o -o Lab5SeanSolberg

utils.o: utils.cpp
	${CXX} -c utils.cpp

critter.o: critter.cpp
	${CXX} -c critter.cpp

doodlebug.o: doodlebug.cpp
	${CXX} -c doodlebug.cpp

ant.o: ant.cpp
	${CXX} -c ant.cpp

main.o: main.cpp
	${CXX} -c main.cpp

clean:
	rm -f Lab5SeanSolberg  *.o

