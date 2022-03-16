objs = ../../lib/factory.o ../../lib/test_factory.o
flags = -c  -pedantic-errors -Wall -Wextra -g -I ../../include/

factory.out: ../../lib/ $(objs)
	g++ $(objs) -o factory.out
../../lib/test_factory.o: test_factory.cpp factory.hpp
	g++ $(flags) test_factory.cpp -o ../../lib/test_factory.o
../../lib/factory.o: factory.cpp factory.hpp
	g++ $(flags) factory.cpp -o ../../lib/factory.o 
../../lib/: 
	nkdir ../../lib

clean:
	rm ../../lib/test_factory.o ../../lib/factory.o factory.out
run: factory.out
	./factory.out
vlg: factory.out
	valgrind --leak-check=yes --track-origins=yes ./factory.out

