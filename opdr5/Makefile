CC = g++
CFLAGS = -Wall

dir = exec
OBJ = main.o sinewave.o

all: dir main clean

dir:
	mkdir -p ${dir}

main: $(OBJ)
	$(CC) -o ${dir}/$@ $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
