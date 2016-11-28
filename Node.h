#ifndef NODE_H
#define NODE_H

enum {
    Left,
    Up,
    Right,
    Down
}Side;

class Node
{
    public:
    Node():
        next{nullptr,nullptr,nullptr,nullptr}
    {

    }
    Node *next[4];
};
#endif
