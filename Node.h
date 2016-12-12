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
        gCost(rand()%100),
        hCost(rand()%100),
		priority(0),
		passedRoute(0)
    {

    }
    Node *next[4];
	int passedRoute;
	int priority;


	void setPriority(int priority){ this->priority = priority; }
	void setPassedRoute(int passedRoute){ this->passedRoute = passedRoute; }
	int getPriority(){ return this->priority; }
	int getPassedRoute(){ return this->passedRoute; }
	bool isDisconnected() { return next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr;}

    //parameters for node display//
    //Note: Text will draw only if color != NONE//
    int color;
    int gCost; // move cost
    int hCost; // heuristics
};
#endif
