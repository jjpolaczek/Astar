#ifndef NODE_H
#define NODE_H
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
        RED
    };

    Node():
        next{nullptr,nullptr,nullptr,nullptr},
        color(0),
        gCost(0),
        hCost(0)
    {

    }
    Node *next[4];
	bool isDisconnected() { return next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr;}
    //parameters for node display//
    //Note: Text will draw only if color != NONE//
    int color;
    int gCost; // move cost
    int hCost; // heuristics
};
#endif
