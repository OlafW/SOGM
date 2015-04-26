CC = g++
CFLAGS = -Wall
PROG = binaryTree
OBJ = node.o main.o noteEvent.o

all: binaryTree

$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
