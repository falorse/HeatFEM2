#makefile

CC = g++
CCOPENMP = g++ -fopenmp

CFLAGS = -g -Wall

TARGETS = femMain

OBJS = femMain.o Node.o TriElem.o Driver.o Logger.o

all: clean femMain

femMain: $(OBJS)

femMain.o: femMain.cpp
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

logDir:
	mkdir logFiles

clean:
	rm -f *.o
