#include "Display.h"
#include "Maze.h"

int main()
{
    Maze maze(15);
    Display display(&maze);
    display.Init();
    while (!display.IsExit())
    {
        display.Draw();
    }
	return 0;
}
