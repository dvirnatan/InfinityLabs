string : test_string.o string.o 
	g++ string.cpp test_string.cpp

test_string.o : test_string.cpp string.hpp
	g++ -c test_string.cpp

string.o : string.cpp string.hpp
	g++ -c string.cpp

clean:
	rm string.o test_string.o


