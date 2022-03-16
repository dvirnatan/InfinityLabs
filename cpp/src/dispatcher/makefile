objs = ../../lib/dispatcher.o ../../lib/test_dispatcher.o
flags = -c -std=c++11 -pedantic-errors -Wall -Wextra -g

dispatcher.out: ../../lib/ $(objs)
	g++ $(objs) -o dispatcher.out
../../lib/test_dispatcher.o: test_dispatcher.cpp dispatcher.hpp
	g++ $(flags) test_dispatcher.cpp -o ../../lib/test_dispatcher.o
../../lib/dispatcher.o: dispatcher.cpp dispatcher.hpp
	g++ $(flags) dispatcher.cpp -o ../../lib/dispatcher.o
../../lib/: 
	mkdir ../../lib

clean:
	rm ../../lib/test_dispatcher.o ../../lib/dispatcher.o dispatcher.out
run: dispatcher.out
	./dispatcher.out
vlg: dispatcher.out
	valgrind --leak-check=yes --track-origins=yes ./dispatcher.out

