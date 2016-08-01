CC = g++
CFLAGS = -Wall
OBJ = dft_complex.o
PROG = dft_complex

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
