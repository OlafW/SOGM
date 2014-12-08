CC = g++
CFLAGS = -Wall
LDFLAGS= -L/usr/local/lib -lportaudio

OBJ=amplifier.o main.o tremolo.o reverser.o audio_io.o

all: guitarfx

guitarfx: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
