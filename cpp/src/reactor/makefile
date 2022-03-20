objs = ../../lib/reactor.o ../../lib/test_reactor.o
flags = -c -std=c++11 -pedantic-errors -Wall -Wextra -g

reactor.out: ../../lib/ $(objs)
	g++ $(objs) -o reactor.out
../../lib/test_reactor.o: test_reactor.cpp reactor.hpp
	g++ $(flags) test_reactor.cpp -o ../../lib/test_reactor.o
../../lib/reactor.o: reactor.cpp reactor.hpp
	g++ $(flags) reactor.cpp -o ../../lib/reactor.o
../../lib/: 
	mkdir ../../lib

clean:
	rm ../../lib/test_reactor.o ../../lib/reactor.o reactor.out
run: reactor.out
	./reactor.out
vlg: reactor.out
	valgrind --leak-check=yes --track-origins=yes ./reactor.out

