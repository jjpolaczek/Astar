#ifndef MAZE_H
#define MAZE_H

#include "Node.h"
#include <stdexcept>

// Coordinate system:
//  O------->
//  |      x
//  |
//  |y
// \ /
class Maze
{
private:
    Node** _nodes; //array of nodes
    int _width; //is equal to height
public:

    Maze(int n);
    ~Maze();
	Node* getNode(int x, int y);
    int getSize()
    {
        return _width;
    }
    void clear();

	void generateLabirynth();	//uses a Depth-First Search method to generate the connections
	 

};
#endif
