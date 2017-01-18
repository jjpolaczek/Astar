#include "AlghoritmWraper.h"



	AlghoritmWraper::AlghoritmWraper(Node* startNode, Node* goalNode, Display display)
	{
		this->goalNode = goalNode;
		this->display = display;
		aStar = new AStar(startNode, goalNode);
		startNode->setColor(Node::BLUE);
		goalNode->setColor(Node::BLUE);
	}
	
	void AlghoritmWraper::steppedSymulation()
	{
		while(aStar.step() != goalNode)
		{
			aStar.getCurentNode->setColor(Node::RED);
			//waitForNextStep();
		}
		drawPassedRoute();
	}
	
	void AlghoritmWraper::continousSymulation()
	{
		while(aStar.step() != goalNode)
		{
			aStar.getCurentNode->setColor(Node::RED);	
		}
		drawPassedRoute();
	}
	
	void AlghoritmWraper::drawPassedRoute()	//funkcja odtwarzająca i rysująca na planszy znalezioną drogę
	{
		std::vector<Node*> path = AStar::reconstructPath(aStar.getCameFrom(),aStar.getCurrentNode());
		for( auto i = path.begin(); i != path.end(); i++ )
			(*i)->setColor(Node::BLUE);
		display.Draw();
	}
