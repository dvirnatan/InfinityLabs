objs = ../../lib/logger.o ../../lib/test_logger.o ../../lib/thread_pool.o
flags = -c -std=c++11 -pedantic-errors -Wall -Wextra -g -I ../../include 
links = -lboost_thread -lboost_chrono -pthread

logger.out: ../../lib/ $(objs)
	g++ $(objs) $(links) -o logger.out
../../lib/test_logger.o: test_logger.cpp logger.hpp
	g++ $(flags) test_logger.cpp -o ../../lib/test_logger.o 
../../lib/logger.o: logger.cpp logger.hpp 
	g++ $(flags) logger.cpp -o ../../lib/logger.o 
../../lib/: 
	mkdir ../../lib

clean:
	rm ../../lib/test_logger.o ../../lib/logger.o logger.out
run: logger.out
	./logger.out
vlg: logger.out
	valgrind --leak-check=yes --track-origins=yes ./logger.out

