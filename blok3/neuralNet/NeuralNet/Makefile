CC = g++
CFLAGS = -Wall
PROG = ART
OBJ = art.o neuron.o main.o
DIR = output

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
