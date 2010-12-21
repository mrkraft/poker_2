all: poker

poker: main.o
	g++ main.o -o poker
main.o: main.cpp
	g++ -c -o main.o main.cpp
.PHONY: clean

clean:
	rm -f main.o

valgrind:

	valgrind /media/win_c2/PROGGA/GIT/porer_linux/poker 1

run:

	/media/win_c2/PROGGA/GIT/porer_linux/poker 0 3 1000 10
 
