objs = ../../lib/waitable_queue.o ../../lib/test_waitable_queue.o
flags = -c std=c++11 -pedantic-errors -Wall -Wextra -g -lboost_timer -lboost_chrono -lboost_system -lboost_thread -lpthread

waitable_queue.out: ../../lib/ $(objs)
	g++ $(objs) -o waitable_queue.out -lboost_timer -lboost_chrono -lboost_system -lboost_thread -lpthread
../../lib/test_waitable_queue.o: test_waitable_queue.cpp waitable_queue.hpp
	g++ $(flags) test_waitable_queue.cpp -o ../../lib/test_waitable_queue.o
../../lib/waitable_queue.o: waitable_queue.cpp waitable_queue.hpp
	g++ $(flags) waitable_queue.cpp -o ../../lib/waitable_queue.o
../../lib/: 
	mkdir ../../lib

clean:
	rm ../../lib/test_waitable_queue.o ../../lib/waitable_queue.o waitable_queue.out
run: waitable_queue.out
	./waitable_queue.out
vlg: waitable_queue.out
	valgrind --leak-check=yes --track-origins=yes ./waitable_queue.out

