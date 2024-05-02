BIN      = main.exe

all: main.cpp algorithms 
	g++ -std=c++11 -O3 -o main main.cpp bfs.o gbfs.o gbfsnode.o astarnode.o bfsnode.o node.o astar.o astar15.o idfs.o idastar.o

algorithms:
	g++ -std=c++11 -O3 -c ./astar.cpp
	g++ -std=c++11 -O3 -c ./astar15.cpp
	g++ -std=c++11 -O3 -c ./bfs.cpp
	g++ -std=c++11 -O3 -c ./gbfs.cpp
	g++ -std=c++11 -O3 -c ./idfs.cpp
	g++ -std=c++11 -O3 -c ./idastar.cpp
	g++ -std=c++11 -O3 -c ./astarnode.cpp
	g++ -std=c++11 -O3 -c ./gbfsnode.cpp
	g++ -std=c++11 -O3 -c ./node.cpp
	g++ -std=c++11 -O3 -c ./bfsnode.cpp
	
clean:
	rm -f *.o
	rm -f main
	rm -f *.csv
