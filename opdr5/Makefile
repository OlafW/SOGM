dir = exec

all: dir main clean

dir:
	mkdir -p ${dir}

main: main.o sinewave.o
	g++ -o ${dir}/$@ ${CFLAGS} main.o sinewave.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

sinewave.o: sinewave.cpp
	g++ -c sinewave.cpp -o sinewave.o

clean:
	rm -f *.o
