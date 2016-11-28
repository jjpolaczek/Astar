#include "Maze.h"

//create a graph
Maze::Maze(int n) : _width(n)
{
    _nodes = new Node*[n];
    for(int i = 0; i < n; ++i)
        _nodes[i] = new Node[n];
    clear();
}

//clean up
Maze::~Maze()
{
    for(int i = 0; i < _width; ++i)
        delete _nodes[i];
    delete[] _nodes;
}

Node* Maze::getNode(int x, int y)
{
    if(x >= _width || y >= _width)
           throw std::out_of_range("Invalid coordinates");
    return &_nodes[x][y];
}

void Maze::clear()
{
    for(int i = 0; i < _width; ++i)
    {
        for(int j = 0; j < _width; ++j)
        {
            //Left - right walls//
            if(i != 0)
                _nodes[i][j].next[Left] = &_nodes[i - 1][j];
            else
                _nodes[i][j].next[Left] = nullptr;

            if(i != _width - 1)
                _nodes[i][j].next[Right] = &_nodes[i + 1][j];
            else
                _nodes[i][j].next[Right] = nullptr;
            //Up down walls//
            if(j != 0)
                _nodes[i][j].next[Up] = &_nodes[i][j - 1];
            else
                _nodes[i][j].next[Up] = nullptr;

            if(j != _width - 1)
                _nodes[i][j].next[Down] = &_nodes[i][j + 1];
            else
                _nodes[i][j].next[Down] = nullptr;


        }
    }
}

void Maze::generateLabirynth()
{
//todo fill out later
}
