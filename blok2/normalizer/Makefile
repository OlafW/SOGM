CC = g++
LIBS = -lsndfile
CFLAGS = -Wall

all: normalizer

normalizer: normalizer.o
	$(CC) -o $@ ${CFLAGS} $@.o ${LIBS}

.ccp.o:
	$(CC) -c $< $(CFLAGS) ${LIBS}

clean:
	rm -f *.o
