CC = g++
CFLAGS = -I/usr/local/include -Wall -I../include
LDFLAGS= -L/usr/local/lib -lportaudio
OBJ = audio_io.o main.o amplifier.o tremolo.o distortion.o delay.o STFT.o biquad.o

all: audiofx

audiofx: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(LDFLAGS) -lpthread

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
