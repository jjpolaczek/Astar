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
    //Get mouse input of start and stop tiles//
    Display::Input input;
    int pointsToSet = 2;
    while(!display.IsExit() && pointsToSet != 0)
    {
        input = display.PollEvent();
        if(input == Display::POINT)
        {
            int resx , resy;
            display.GetLastClickedTile(resx, resy);
            maze.getNode(resx,resy)->setColor(Node::BLUE);
            display.Draw();
            if(pointsToSet == 2)
            {
                startPointX = resx;
                startPointY = resy;
            }
            if(pointsToSet == 1)
            {
                endPointX = resx;
                endPointY = resy;
            }
            --pointsToSet;
        }
    }

    //Display and perform A* search//
    findWayAstar(maze.getNode(startPointX,startPointY),maze.getNode(endPointX,endPointY),display);
    while (!display.IsExit())
    {
        display.PollEvent();
    }
	return 0;
}
