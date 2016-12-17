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
        color(0),
        gCost(0),
        totalCost(0),
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
	void setColor(int color){this->color = color;}
    void setPriority(int priority){ this->priority = priority; this->totalCost = priority; this->color = GREEN;}
	void setPassedRoute(int passedRoute){ this->passedRoute = passedRoute;this->gCost = passedRoute; }
	int getPriority(){ return this->priority; }
	int getPassedRoute(){ return this->passedRoute; }
	int getX(){ return this->x; }
	int getY(){ return this->y; }
	bool isDisconnected() { return next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr;}

    //parameters for node display//
    //Note: Text will draw only if color != NONE//
    int color;
    int gCost; // odległość od startu

    int totalCost; // odległość od startu + funkcja heurystyczna
};
#endif
