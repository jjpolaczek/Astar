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
	
	/*
	* Checks if it's possible to go that way
	* ie. if it's not a border node or if there's a wall
	*/
	bool isValidSide(Side side, int x, int y);
	/*
	* Shuffles the sides list.
	*/
	static void randomizeOrder(Side* sides, std::minstd_rand0*);
public:

    /*
    * Constructor. Creates a clean maze of given size.
    * Filling it with walls requires calling generateMaze().
    */
    Maze(int n);
    
    /*
    * Destructor. Cleans up the created mess.
    */
    ~Maze();
    
    /*
    * Returns a node at given coordinates.
    * Throws an exception if it's out of bonds.
    */
	Node* getNode(int x, int y);
	
	/*
	* Returns width/height of the maze.
	*/
    int getSize()
    {
        return _width;
    }
    
    /*
    * Removes walls from the maze.
    */
    void clear();
    
    /*
    * Uses a Depth-First Search method to generate the maze.
    * Requires a fully walled maze first.
    * Using DFS, it's ensured that the maze will have a path from any point to any point.
    */
	void generateMaze(); 

};
#endif
