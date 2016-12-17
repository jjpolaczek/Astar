#pragma once
#include <cstdio>
#include <vector>
#include <map>

#include "Display.h"
#include "Maze.h"
std::vector<Node*> reconstructPath(std::map<Node*,Node*> cameFrom, Node* currentNode);

void findWayAstar(Node* startNode, Node* goalNode, Display display);