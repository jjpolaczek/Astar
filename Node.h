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
	bool isDisconnected() { return next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr;}
};
#endif
