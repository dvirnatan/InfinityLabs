objs = ../../lib/SharedPtr.o ../../lib/test_SharedPtr.o
flags = -c -fabi-version=98 -pedantic-errors -Wall -Wextra -g

SharedPtr.out: ../../lib/ $(objs)
	g++ $(objs) -o SharedPtr.out
../../lib/test_SharedPtr.o: test_SharedPtr.cpp SharedPtr.hpp
	g++ $(flags) test_SharedPtr.cpp -o ../../lib/test_SharedPtr.o
../../lib/SharedPtr.o: SharedPtr.cpp SharedPtr.hpp
	g++ $(flags) SharedPtr.cpp -o ../../lib/SharedPtr.o
../../lib/: 
	nkdir ../../lib

clean:
	rm ../../lib/test_SharedPtr.o ../../lib/SharedPtr.o SharedPtr.out
run: SharedPtr.out
	./SharedPtr.out
vlg: SharedPtr.out
	valgrind --leak-check=yes --track-origins=yes ./SharedPtr.out

