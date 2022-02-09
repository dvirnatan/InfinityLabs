CC = g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g

shapes : test_shapes.o shapes.o 
	$(CC) $(CFLAGS) shapes.cpp test_shapes.cpp

test_shapes.o: test_shapes.cpp shapes.hpp
	$(CC) $(CFLAGS) -c test_shapes.cpp

shapes.o : shapes.cpp shapes.hpp
	$(CC) $(CFLAGS) -c shapes.cpp

clean:
	rm shapes.o test_shapes.o


