#include <Graph.h>

//create a graph
Graph::Graph(int n) : width{n}
{
	nodes = new Node*[n*n];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			nodes[i*n + j] = new Node(i, j);
}

//clean up
Graph::~Graph()
{
	for(int i = 0; i < width*width; ++i)
		delete nodes[i];
	delete[] nodes;
}

Node* Graph::getNode(int x, int y)
{
	return nodes[x*width + y];
}

void Graph::generateLabirynth()
{
//todo fill out later
}
