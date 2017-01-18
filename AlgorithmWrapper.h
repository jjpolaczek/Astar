#pragma once
#include <cstdio>
#include <vector>
#include <map>

#include "Display.h"
#include "Maze.h"
#include "AStar.h"

class AlgorithmWrapper
{
	public:
		AlgorithmWrapper(Node* startNode, Node* goalNode, Display* display);
		void steppedSimulation();	//symulacja krokowa
		void continousSimulation();	//symulacja ciągła
    private:
        void drawPassedRoute();	//funkcja odtwarzająca i rysująca na planszy znalezioną drogę
        AStar* aStar;
        Node* goalNode;
        Display* display;
};
