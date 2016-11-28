#include "Node.h"

class Graph
{
private:
	Node** nodes; //array of nodes
	int width; //is equal to height
public:
	Graph(int n) : width{n};
	~Graph();
	Node* getNode(int x, int y);
	void generateLabirynth();	//uses a Depth-First Search method to generate the connections
	 

}
