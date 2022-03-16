objs = ../../lib/thread_pool.o ../../lib/test_thread_pool.o
flags = -c -std=c++11 -pedantic-errors -Wall -Wextra -g -I ../waitable_queue -lboost_system -lboost_timer -lboost_chrono -lboost_thread -pthread
thread_pool.out: ../../lib/ $(objs) 
	g++ $(objs) -o thread_pool.out -lboost_system -lboost_timer -lboost_chrono -lboost_thread -pthread
../../lib/test_thread_pool.o: test_thread_pool.cpp thread_pool.hpp
	g++ $(flags) test_thread_pool.cpp -o ../../lib/test_thread_pool.o
../../lib/thread_pool.o: thread_pool.cpp thread_pool.hpp
	g++ $(flags) thread_pool.cpp -o ../../lib/thread_pool.o
../../lib/: 
	mkdir ../../lib

clean:
	rm ../../lib/test_thread_pool.o ../../lib/thread_pool.o thread_pool.out
run: thread_pool.out
	./thread_pool.out
vlg: thread_pool.out
	valgrind --leak-check=yes --track-origins=yes ./thread_pool.out

