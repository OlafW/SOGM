CC = g++
PROG = iir
OBJS = iir.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)


.cpp.o:
	$(CC) -c $<


clean:
	rm -f *.o
