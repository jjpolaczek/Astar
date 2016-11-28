#ifndef NODE_H
#define NODE_H


class Node
{
    public:
    Node():
        wLeft(0),
        wRight(0),
        wUp(0),
        wDown(0)
    {

    }

    bool wLeft,wRight,wUp,wDown;
};
#endif
