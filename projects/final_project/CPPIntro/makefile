Ex11 : Ex11_driver.o Ex11.h libEx11.so
	g++ -L./ -Wl,-rpath=./ Ex11_driver.cpp -o Ex11.out -lEx11 


Ex11_driver.o : Ex11_driver.cpp Ex11.h
	g++ -c Ex11_driver.cpp

libEx11.so : Ex11.o
	g++ -shared Ex11.o  -o libEx11.so

Ex11.o : Ex11.cpp Ex11.h
	g++ -fpic -c Ex11.cpp

clean:
	rm Ex11_driver.o Ex11.o