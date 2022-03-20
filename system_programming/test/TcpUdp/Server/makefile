gd=g++ -std=c++98 -pedantic-errors -Wall -Wextra -g -cpp

bin/server.out: lib/ bin/ lib/server.o lib/utils.o bin/udp_custom.out \
				bin/broadcast_custom.out bin/tcp_custom.out
	gcc lib/server.o lib/utils.o -o bin/server.out
bin/udp_custom.out: lib/udp_custom.o lib/utils.o
	gcc lib/udp_custom.o lib/utils.o -o bin/udp_custom.out
bin/broadcast_custom.out: lib/broadcast_custom.o lib/utils.o
	gcc lib/broadcast_custom.o lib/utils.o -o bin/broadcast_custom.out
bin/tcp_custom.out: lib/tcp_custom.o lib/utils.o
	gcc lib/tcp_custom.o lib/utils.o -o bin/tcp_custom.out
	
lib/server.o: server.cpp utils.hpp
	$(gd) server.cpp utils.cpp -o lib/server.o
lib/udp_custom.o: udp_custom.cpp utils.hpp
	$(gd) udp_custom.cpp -o lib/udp_custom.o
lib/broadcast_custom.o: broadcast_custom.cpp utils.hpp
	$(gd) broadcast_custom.cpp -o lib/broadcast_custom.o
lib/tcp_custom.o: tcp_custom.cpp utils.hpp
	$(gd) tcp_custom.cpp -o lib/tcp_custom.o
lib/utils.o: utils.cpp utils.hpp
	$(gd) utils.cpp -o lib/utils.o
	
lib/: 
	mkdir lib
bin/:
	mkdir bin
	
clean:
	rm -r lib/ bin/
