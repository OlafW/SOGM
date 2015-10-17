CC = g++
LDFLAGS= -L/usr/local/lib -lportaudio -lsndfile

OBJ= main.o beattracking.o sndfile_io.o

all: beatTracker

beatTracker: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

.cpp.o:
	$(CC) $< -c

clean:
	rm -f *.o
