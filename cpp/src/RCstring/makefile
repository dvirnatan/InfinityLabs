CC = g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g

RCString : test_RCString.o RCString.o 
	$(CC) $(CFLAGS) RCString.cpp test_RCString.cpp

test_RCString.o: test_RCString.cpp RCString.hpp
	$(CC) $(CFLAGS) -c test_RCString.cpp

RCString.o : RCString.cpp RCString.hpp
	$(CC) $(CFLAGS) -c RCString.cpp

clean:
	rm RCString.o test_RCString.o


