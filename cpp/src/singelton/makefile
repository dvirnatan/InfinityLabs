objs = ../../lib/singelton.o ../../lib/test_singelton.o
flags = -c -std=c++98 -pedantic-errors -Wall -Wextra -g

singelton.out: ../../lib/ $(objs)
	g++ $(objs) -o singelton.out
../../lib/test_singelton.o: test_singelton.cpp singelton.hpp
	g++ $(flags) test_singelton.cpp -o ../../lib/test_singelton.o
../../lib/singelton.o: singelton.cpp singelton.hpp
	g++ $(flags) singelton.cpp -o ../../lib/singelton.o
../../lib/: 
	nkdir ../../lib

clean:
	rm ../../lib/test_singelton.o ../../lib/singelton.o singelton.out
run: singelton.out
	./singelton.out
vlg: singelton.out
	valgrind --leak-check=yes --track-origins=yes ./singelton.out

