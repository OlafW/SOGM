CC = g++
CFLAGS = -Wall
OBJ = dft.o
PROG = dft

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
