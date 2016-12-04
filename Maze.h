#ifndef MAZE_H
#define MAZE_H

#include "Node.h"
#include <stdexcept>
#include <random>
#include <chrono>


// Coordinate system:
//  O------->
//  |      x
//  |
//  |y
//  V
class Maze
{
private:
    Node** _nodes; //array of nodes
    int _width; //is equal to height

	bool isValidSide(Side side, int x, int y);
	static void randomizeOrder(Side* sides, std::minstd_rand0*);
public:

    Maze(int n);
    ~Maze();
	Node* getNode(int x, int y);
    int getSize()
    {
        return _width;
    }
    void clear();

	void generateMaze();	//uses a Depth-First Search method to generate the connections
	 

};
#endif
