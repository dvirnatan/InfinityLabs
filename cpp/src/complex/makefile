CC = g++
CFLAGS=-fabi-version=98 -pedantic-errors -Wall -Wextra -g

complex : test_complex.o complex.o 
	$(CC) complex.cpp test_complex.cpp

test_complex.o : test_complex.cpp complex.hpp
	$(CC) -c test_complex.cpp

complex.o : complex.cpp complex.hpp
	$(CC) -c complex.cpp

clean:
	rm complex.o test_complex.o


