#pragma once
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

#include "Maze.h"

class AStar
{
	public:
		AStar(Node* startNode, Node* goalNode);	
		Node* step();
		std::vector<Node*> reconstructPath(std::map<Node*,Node*> cameFrom, Node* currentNode);	//funkcja odtwarzająca przebytą drogę
		Node* getCurrentNode();
		std::map<Node*,Node*> getCameFrom();
    private:
        std::vector<Node*> closedSet;	//zbiór odwiedzonych
        std::vector<Node*> openSet;		//zbiór otkrytych nieodwiedzonych
        std::map<Node*,Node*> cameFrom;
        Node* currentNode;
        Node* startNode;
        Node* goalNode;
};
