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
    Node():
        next{nullptr,nullptr,nullptr,nullptr}
    {

    }
    Node *next[4];
	bool isDisconnected() {return !(next[0] || next[1] || next[2] || next[3]);}
};
#endif
