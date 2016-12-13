#include <cstdio>
#include <vector>
#include <map>

#include "Display.h"
#include "Maze.h"
#include "findWayAstar.h"


std::vector<Node*> findWayAstar(Node* startNode, Node* goalNode, Display display)
{
	std::vector<Node*> closedSet;	//zbiór odwiedzonych
	std::vector<Node*> openSet;		//zbiór otkrytych nieodwiedzonych
	std::map<Node*,Node*> cameFrom;
	
	Node* currentNode;
	
	openSet.push_back(startNode);
	startNode->setPriority(abs(startNode->getX()-goalNode->getX())+abs(startNode->getY()-goalNode->getY()));	//przypisz przewidywaną długość drogi przechodzącej przez dany punkt
	startNode->setPassedRoute(0);	//przypisz przebytą drogę
	while(openSet.size()>0)
	{
		currentNode = openSet[0];
		for( auto i = openSet.begin(); i != openSet.end(); i++ )//weź najlepszy ze zbioru odkrytych nieodwiedzonych
		{
			if(currentNode->getPriority()>(*i)->getPriority())
				currentNode = *i;
			printf("Wybierz kolejny node %d : %d\n",currentNode->getX(),currentNode->getY());
		}
		display.Draw();	//Rysuj stan planszy
		printf("Dupa\n");
		if(currentNode == goalNode)	// Jeśli dotarliśmy do celu zwróć przebytą drogę
			return reconstructPath(cameFrom,currentNode);
		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
		closedSet.push_back(currentNode);
		for (int i = 0; i < 4; i++)	//Dodaj sąsiadów do zbioru odkrytych
		{
			if (std::find(closedSet.begin(), closedSet.end(),currentNode->next[i])!=closedSet.end())
				continue;
			//tentativeGScore = gGcore+1;
			if (!(std::find(openSet.begin(), openSet.end(),currentNode->next[i])!=openSet.end()) && currentNode->next[i] != nullptr)
			{
				openSet.push_back(currentNode->next[i]);
				currentNode->next[i]->setPriority((abs(currentNode->next[i]->getX()-goalNode->getX())+abs(currentNode->next[i]->getY()-goalNode->getY())) + currentNode->getPassedRoute());	//przypisz przewidywaną długość drogi przechodzącej przez dany punkt
				currentNode->next[i]->setPassedRoute(currentNode->getPassedRoute()+1);	//przypisz przebytą drogę
				printf("Dodaj sąsiada %d : %d\n",currentNode->getX(),currentNode->getY());
			}
			cameFrom[currentNode->next[i]]=currentNode;
		}
	}

}

std::vector<Node*> reconstructPath(std::map<Node*,Node*> cameFrom, Node* currentNode)
{
	if (cameFrom.find(currentNode)!=cameFrom.end())
	{
		std::vector<Node*> p = reconstructPath(cameFrom,cameFrom[currentNode]);
		p.push_back(currentNode);
		return p;
	} 
	std::vector<Node*> p;
		return p;
}
