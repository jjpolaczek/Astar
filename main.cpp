#include <cstdlib>

#include "Display.h"
#include "Maze.h"
#include "findWayAstar.h"

int main(int argc, char* argv[])	// parametry wywołania: rozmiar planszy, wejście.x, wejście.y, wyjście.x, wyjście.y
{
    int mazeSize = 15;
    int startPointX = 5;
    int startPointY = 5;
    int endPointX = 10;
    int endPointY = 10;
    switch(argc)
    {
    case 6:
        endPointY = atoi(argv[5]);
    case 5:
        endPointX = atoi(argv[4]);
    case 4:
         startPointY = atoi(argv[3]); 
    case 3:
         startPointX = atoi(argv[2]);
    case 2:
         mazeSize = atoi(argv[1]);
         break;
    default:
        break;
    }
    Maze maze(mazeSize);
	maze.generateMaze();
    Display display(&maze);
    display.Init();
    display.Draw();
    findWayAstar(maze.getNode(startPointX,startPointY),maze.getNode(endPointX,endPointY),display);
    while (!display.IsExit())
    {
        display.Draw();
    }
	return 0;
}
