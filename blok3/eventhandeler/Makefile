CC = g++
CFLAGS = -Wall
PROG = eventhandeler
OBJ = event.o main.o scheduler.o

all: eventhandeler

$(PROG): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
