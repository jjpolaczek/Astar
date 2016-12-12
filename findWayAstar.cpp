#include <vector>

#include "Maze.h"

std::Vector<Node*> findWayAstar(Maze maze, Node* startNode, Node* goalNode)
{
	std::vector<Node*> closedSet;
	std::vector<Node*> openSet;
	std::map<Node*,Node*> cameFrom;
	
	Node* currentNode;
	int curentRouteLength;
	int prioryty; //currentROuteLength + heurisistic
	openSet.pushBack(startNode);
	startNode.setPriority(abs(startNode.getX()-goalNode.getX())+abs(startNode.getY()-goalNode.getY()));
	startNode.setPassedRoute(0);
	while(openSet.size()>0)
	{
		currentNode = openSet.begin();
		for( Node*::iterator i = openSet.begin(); i != openSet.end(); i++ )
		{
			if(currentNode.getPriority()>i.getPriority())
    		currentNode = i;
		}
		if(currentNode == goalNode)
			return reconstructPath(cameFrom);
		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
		closedSet.push_back(currentNode);
		for (int i = 0; i < 4; i++)
		{
			if (std::find(closedSet.begin(), closedSet.end(),currentNode->next[i])!=closedSet.end())
				continue;
			//tentativeGScore = gGcore+1;
			if (std::find(openSet.begin(), openSet.end(),currentNode->next[i])!=openSet.end())
			{
				openSet.pushBack(currentNode->next[i]);
				currentNode->next[i].setPriority((abs(currentNode->next[i].getX()-goalNode.getX())+abs(currentNode->next[i].getY()-goalNode.getY()))+currentNode.getPassedRoute());
				currentNode->next[i].setPassedRoute(currentNode.getPassedRouteLength());
			}
			cameFrom[currentNode->next[i]]=currentNode;
		}
		

}

std::vector reconstructPath(std::map<Node*,Node*> cameFrom, Node* current)
{
	if cameFrom[current_node] is set
	{
		std::vector<Node*> p = reconstructPath(came_from,came_from[current_node]);
		p.push_back(current_node);
		return p;
	} 
	else
		return null;
}