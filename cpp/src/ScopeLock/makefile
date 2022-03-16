objs = ../../lib/ScopeLock.o ../../lib/test_ScopeLock.o
flags = -c -fabi-version=98 -pedantic-errors -Wall -Wextra -g

ScopeLock.out: ../../lib/ $(objs)
	g++ $(objs) -o ScopeLock.out
../../lib/test_ScopeLock.o: test_ScopeLock.cpp ScopeLock.hpp
	g++ $(flags) test_ScopeLock.cpp -o ../../lib/test_ScopeLock.o
../../lib/ScopeLock.o: ScopeLock.cpp ScopeLock.hpp
	g++ $(flags) ScopeLock.cpp -o ../../lib/ScopeLock.o
../../lib/: 
	nkdir ../../lib

clean:
	rm ../../lib/test_ScopeLock.o ../../lib/ScopeLock.o ScopeLock.out
run: ScopeLock.out
	./ScopeLock.out
vlg: ScopeLock.out
	valgrind --leak-check=yes --track-origins=yes ./ScopeLock.out

