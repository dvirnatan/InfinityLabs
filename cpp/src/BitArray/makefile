objs = ../../lib/BitArray.o ../../lib/test_BitArray.o
flags = -c -fabi-version=98 -pedantic-errors -Wall -Wextra -g

BitArray.out: ../../lib/ $(objs)
	g++ $(objs) -o BitArray.out
../../lib/test_BitArray.o: test_BitArray.cpp BitArray.hpp
	g++ $(flags) test_BitArray.cpp -o ../../lib/test_BitArray.o
../../lib/BitArray.o: BitArray.cpp BitArray.hpp
	g++ $(flags) BitArray.cpp -o ../../lib/BitArray.o
../../lib/: 
	nkdir ../../lib

clean:
	rm ../../lib/test_BitArray.o ../../lib/BitArray.o BitArray.out
run: BitArray.out
	./BitArray.out
vlg: BitArray.out
	valgrind --leak-check=yes --track-origins=yes ./BitArray.out

