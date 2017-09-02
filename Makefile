#makefile

CC = g++
CCOPENMP = g++ -fopenmp -O3

CFLAGS = -g -Wall

TARGETS = femMain

OBJS = femMain.o Node.o TriElem.o Driver.o Logger.o

all: clean femMain

femMain: $(OBJS)
	$(CCOPENMP) $(CFLAGS) -o $@ $(OBJS)

femMain.o: femMain.cpp
	$(CCOPENMP) $(CFLAGS) -c $<

%.o: %.cpp
	$(CCOPENMP) $(CFLAGS) -c $<

logDir:
	mkdir logFiles

clean:
	rm -f *.o
