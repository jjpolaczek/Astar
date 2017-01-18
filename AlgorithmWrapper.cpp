#include "AlgorithmWrapper.h"



	AlgorithmWrapper::AlgorithmWrapper(Node* startNode, Node* goalNode, Display* display)
	{
		this->goalNode = goalNode;
		this->display = display;
		aStar = new AStar(startNode, goalNode);
		startNode->setColor(Node::BLUE);
		goalNode->setColor(Node::BLUE);
	}
	
	void AlgorithmWrapper::steppedSimulation()
	{
		bool autoStep = true;
		Display::Input input;
		while(aStar->step() != goalNode)
		{
			aStar->getCurrentNode()->setColor(Node::RED);
			//pentla oczekuje na kolejny krok w algorytmie
		if(autoStep != true)
        {
			while(!display->IsExit())
                {
                    input = display->PollEvent();
                    if(input == Display::STEP)
                        break;
                    else if(input == Display::AUTO)
                    {
                        autoStep = !autoStep;
                        break;
                    }

                }
		}
		}
		drawPassedRoute();
	}
	
	void AlgorithmWrapper::continousSimulation()
	{
		while(aStar->step() != goalNode)
		{
			aStar->getCurrentNode()->setColor(Node::RED);	
		}
		drawPassedRoute();
	}
	
	void AlgorithmWrapper::drawPassedRoute()	//funkcja odtwarzająca i rysująca na planszy znalezioną drogę
	{
		std::vector<Node*> path = aStar->reconstructPath(aStar->getCameFrom(), aStar->getCurrentNode());
		for( auto i = path.begin(); i != path.end(); i++ )
			(*i)->setColor(Node::BLUE);
		display->Draw();
	}
