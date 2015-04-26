CC = g++
LIBS = -lsndfile
CFLAGS = -Wall
OBJS = audio_io.o main.o
PROG = audioIO

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ ${CFLAGS} $(OBJS) ${LIBS}

.ccp.o:
	$(CC) -c $< $(CFLAGS) ${LIBS}

clean:
	rm -f *.o
