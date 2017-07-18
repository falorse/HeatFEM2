#makefile

CC = g++
CCOPENMP = g++ -fopenmp

CFLAGS = -O3 -Wall

TARGETS = femMain

OBJS = femMain.o Node.o TriElem.o Driver.o Logger.o

all: clean logDir femMain

femMain: $(OBJS)

femMain.o: femMain.cpp
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

logDir:
	mkdir logFiles

clean:
	rm -f *.o
	rm -r logFiles
