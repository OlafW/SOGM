CC = g++

all: pointers1 pointers2


pointers1: pointers1.o
	$(CC) -c $@.cpp
	$(CC) -o $@ $@.o

pointers2: pointers2.o
	$(CC) -c $@.cpp
	$(CC) -o $@ $@.o


clean:
	rm -f *.o
