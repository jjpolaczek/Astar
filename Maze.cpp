#include "Maze.h"

//create a graph
Maze::Maze(int n) : _width(n)
{
    _nodes = new Node*[n*n];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
            _nodes[i*n + j] = new Node(/*i, j*/);
}

//clean up
Maze::~Maze()
{
    for(int i = 0; i < _width*_width; ++i)
        delete _nodes[i];
    delete[] _nodes;
}

Node* Maze::getNode(int x, int y)
{
    return _nodes[x*_width + y];
}

void Maze::generateLabirynth()
{
//todo fill out later
}
