all: release
debug:
	g++ main.cpp Display.cpp Maze.cpp findWayAstar.cpp -o app.o -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -g -O0
release:
	g++ main.cpp Display.cpp Maze.cpp findWayAstar.cpp -o app.o -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -O3
clean:
	rm *.o
