CC = g++
LIBS = -lsndfile
CFLAGS = -Wall

all: normalizer

normalizer: normalizer.cpp
	$(CC) -c $@.cpp -o $@.o ${CFLAGS}
	$(CC) -o $@ $@.o ${CFLAGS} ${LIBS}

clean:
	rm -f *.o
