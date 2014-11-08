CC = g++
CFLAGS = -Wall

OBJ=amplifier.o main.o

all: guitarfx

guitarfx: $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
