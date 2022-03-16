objs = ../../lib/CPP2C_2.o ../../lib/test_CPP2C_2.o
flags = -c -fabi-version=98 -pedantic-errors -Wall -Wextra -g

CPP2C_2.out: ../../lib/ $(objs)
	g++ $(objs) -o CPP2C_2.out
../../lib/test_CPP2C_2.o: test_CPP2C_2.cpp CPP2C_2.hpp
	g++ $(flags) test_CPP2C_2.cpp -o ../../lib/test_CPP2C_2.o
../../lib/CPP2C_2.o: CPP2C_2.cpp CPP2C_2.hpp
	g++ $(flags) CPP2C_2.cpp -o ../../lib/CPP2C_2.o
../../lib/: 
	nkdir ../../lib

clean:
	rm ../../lib/test_CPP2C_2.o ../../lib/CPP2C_2.o CPP2C_2.out
run: CPP2C_2.out
	./CPP2C_2.out
vlg: CPP2C_2.out
	valgrind --leak-check=yes --track-origins=yes ./CPP2C_2.out

