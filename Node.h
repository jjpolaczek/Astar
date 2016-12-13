#ifndef NODE_H
#define NODE_H
#include <random>
enum Side {
    Left,
    Up,
    Right,
    Down
};

class Node
{
    public:
    enum Color
    {
        NONE,
        GREEN,
        RED,
        BLUE
    };

    Node():
        next{nullptr,nullptr,nullptr,nullptr},
        color(rand()%4),
        gCost(0),
        hCost(0),
		priority(0),
		passedRoute(0)
    {

    }
    Node *next[4];
	int passedRoute;
	int priority;
	int x;
	int y;

	void setXY(int x, int y){this->x = x; this->y = y;}
	void setPriority(int priority){ this->priority = priority; this->hCost = priority;}
	void setPassedRoute(int passedRoute){ this->passedRoute = passedRoute;this->gCost = passedRoute; }
	int getPriority(){ return this->priority; }
	int getPassedRoute(){ return this->passedRoute; }
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	bool isDisconnected() { return next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr;}

    //parameters for node display//
    //Note: Text will draw only if color != NONE//
    int color;
    int gCost; // move cost
    int hCost; // heuristics
};
#endif
