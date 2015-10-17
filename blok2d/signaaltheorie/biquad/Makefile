CC = g++
CFLAGS = -Wall
OBJS = biquad.o main.o io-aiff/rdaiff.o io-aiff/wraiff.o
PROG = biquad

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ ${CFLAGS} $(OBJS)

.ccp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
