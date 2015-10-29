CC = g++
CFLAGS = -I/usr/local/include -Wall -I../include
LDFLAGS= -L/usr/local/lib -lsndfile

OBJ= main.o beattracking.o sndfile_io.o

all: beatTracker

beatTracker: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(LDFLAGS)

.cpp.o:
	$(CC) $< -c $(CFLAGS)

clean:
	rm -f *.o
