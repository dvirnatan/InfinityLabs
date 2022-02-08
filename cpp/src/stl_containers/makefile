CC = g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g

stl_containers : test_stl_containers.o stl_containers.o 
	$(CC) $(CFLAGS) stl_containers.cpp test_stl_containers.cpp

test_stl_containers.o: test_stl_containers.cpp stl_containers.hpp
	$(CC) $(CFLAGS) -c test_stl_containers.cpp

stl_containers.o : stl_containers.cpp stl_containers.hpp
	$(CC) $(CFLAGS) -c stl_containers.cpp

clean:
	rm stl_containers.o test_stl_containers.o


