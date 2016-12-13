#include "Maze.h"
#include <stack>
#include <random>
#include <chrono>
#include <iostream>

//create a graph
Maze::Maze(int n) : _width(n)
{
    _nodes = new Node*[n];
    for(int i = 0; i < n; ++i)
        _nodes[i] = new Node[n];

    for(int i = 0; i < n; ++i)
	for(int j = 0; j < n; ++j)
		_nodes[i][j].setXY(i, j);

    //clear();
	//for maze generator to work everything must be walled first
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

/*
* This method clears all walls from the maze. 
*/
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
/*
* This method generates the maze using iterative depth-first search with a stack.
* It relies on the maze being full of walls at the beginning.
*/
void Maze::generateMaze()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand0 generator(seed);


	struct State //current state of the node
	{
		Side order[4]; //randomized order of directions
		int x;
		int y;
		int iter = 0;		//iterator on order
		State(int x_, int y_, std::minstd_rand0* generator): iter(0), x(x_), y(y_) { randomizeOrder(this->order, generator); };
	};

	std::stack<State*> stack;
	State* currentState = new State(0, 0, &generator); //first the first state
	stack.push(currentState);

	while(!stack.empty())
	{
		/* 
		*  look at the top one
		*  go through order[] with iter once if you can
		*  if you succeed with going further with that iter, create, push and update the new state
		*  otherwise, iterate with iter (loop) until you have to pop
		*/
		currentState = stack.top();
		while(currentState->iter < 4)
		{
			Side chosenSide = currentState->order[currentState->iter];
			Side oppositeSide;
			int x = currentState->x;
			int y = currentState->y;
			int newX, newY;
			++(currentState->iter); //advance the iterator for the current value
			if(isValidSide(chosenSide, x, y)) //can go theoretically
			{
				switch(chosenSide) //set new values
				{
					case Left:
						newX = x-1;
						newY = y;
						oppositeSide = Right;
						break;
					case Up:
						newX = x;
						newY = y-1;
						oppositeSide = Down;
						break;
					case Right:
						newX = x+1;
						newY = y;
						oppositeSide = Left;
						break;
					case Down:
						newX = x;
						newY = y+1;
						oppositeSide = Up;
						break;
				}
				if(_nodes[newX][newY].isDisconnected()) //is not connected to any node = maze can be expanded to that point
				{
					//first: connect the two
					_nodes[x][y].next[chosenSide] = &(_nodes[newX][newY]);
					_nodes[newX][newY].next[oppositeSide] = &(_nodes[x][y]);
					//second: create new state and push it on stack
					State* newState = new State(newX, newY, &generator);
					currentState = newState; //...set the new currentstate (top of the stack)
					stack.push(newState);
				}

			}

		} // end while(iter<4)

		//we have gone with iteraror further than possible, so we pop the most top element and delete it; it will be updated on next loop iteration	
		stack.pop();
		delete currentState; //clean that state as it won't be reused

	}// end while(!stack.isEmpty())
}

/*
* The (rather simple) order shuffler
*/
void Maze::randomizeOrder(Side* sides, std::minstd_rand0* generator)
{
	//init w/ some order
	sides[0] = Up;
	sides[1] = Down;
	sides[2] = Left;
	sides[3] = Right;

	 
	for(int i = 0; i < 3; ++i)
	{
		int j =(*generator)() % 4; //shuffle a bit
		Side temp = sides[i];
		sides[i] = sides[j];
		sides[j] = temp;
	}
}
/*
* Checks if from the cell given at x, y it's possible to go the given direction (side)
*/
bool Maze::isValidSide(Side side, int x, int y)
{
	if(x > 0 && x < _width-1 && y > 0 && y < _width-1)
		return true;
	switch(side)
	{
		case Left:
			return (x != 0); 
		case Up:
			return (y != 0); //if it's at the top, can't go down
		case Right:
			return (x != _width-1); //and if it's most right, it can't go any more as well
		case Down:
			return (y != _width-1); //if it's at the bottom, can't go up any more
	}
	return false; //how did we get there?

}
