#pragma once

std::vector<Node*> reconstructPath(std::map<Node*,Node*> cameFrom, Node* currentNode);

void findWayAstar(Node* startNode, Node* goalNode, Display display);
