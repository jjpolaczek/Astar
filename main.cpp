#include "Display.h"

int main()
{
    MazeVisualizer maze(15);
    maze.Init();
    while (!maze.IsExit())
    {
        maze.Draw();
    }
	return 0;
}
