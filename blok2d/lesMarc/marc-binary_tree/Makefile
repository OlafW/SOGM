CC = g++
CFLAGS = -g -Wall

all: bintree

bintree: bintree.o

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`

