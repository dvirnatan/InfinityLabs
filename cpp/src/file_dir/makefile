CC = g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g

file_dir : test_file_dir.o file_dir.o 
	$(CC) $(CFLAGS) file_dir.cpp test_file_dir.cpp

test_file_dir.o: test_file_dir.cpp file_dir.hpp
	$(CC) $(CFLAGS) -c test_file_dir.cpp

file_dir.o : file_dir.cpp file_dir.hpp
	$(CC) $(CFLAGS) -c file_dir.cpp

clean:
	rm file_dir.o test_file_dir.o a.out


