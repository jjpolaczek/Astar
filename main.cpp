#include <cstdlib>

#include "Display.h"
#include "Maze.h"
#include "findWayAstar.h"

int main(int argc, char* argv[])
{
    int mazeSize = 15;
    int startPoint = 5;
    int endPoint = 7;
    switch(argc)
    {
    case 4:
        endPoint = atoi(argv[3]); 
    case 3:
         startPoint = atoi(argv[2]);
    case 2:
         mazeSize = atoi(argv[1]);
         break;
    default:
        break;
    }
    Maze maze(15);
	maze.generateMaze();
    Display display(&maze);
    display.Init();
    display.Draw();
    findWayAstar(maze.getNode(startPoint,startPoint),maze.getNode(endPoint,endPoint),display);
    while (!display.IsExit())
    {
        display.Draw();
    }
	return 0;
}
