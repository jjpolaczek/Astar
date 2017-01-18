#pragma once
#include <cstdio>
#include <vector>
#include <map>

#include "Display.h"
#include "Maze.h"
#include "AStar.h"

class AlghoritmWraper
{
	private:
		AStar aStar;
		Node* goalNode;
		void drawPassedRoute()	//funkcja odtwarzająca i rysująca na planszy znalezioną drogę
	public:
		AlghoritmWraper(Node* startNode, Node* goalNode);
		void steppedSymulation();	//symulacja krokowa
		void continousSymulation();	//symulacja ciągła
};