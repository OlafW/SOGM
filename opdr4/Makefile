dir = exec

all: dir somfunc print_array max_array rot_array clean

dir:
	mkdir -p ${dir}

somfunc: somfunc.cpp
	g++ -c somfunc.cpp
	g++ -o ${dir}/$@ $@.o


print_array: print_array.cpp
	g++ -c print_array.cpp
	g++ -o ${dir}/$@ $@.o

max_array: max_array.cpp
		g++ -c max_array.cpp
		g++ -o ${dir}/$@ $@.o


rot_array: rot_array.cpp
		g++ -c rot_array.cpp
		g++ -o ${dir}/$@ $@.o


clean:
	rm -f *.o
