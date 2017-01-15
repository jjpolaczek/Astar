class FunctionCaller
{
	AStar aStar;
	Node* goalNode;
	public FunctionCaller(Node* startNode, Node* goalNode)
	{
		this->goalNode = goalNode;
		aStar = new AStar(startNode, goalNode);
		startNode->setColor(Node::BLUE);
		goalNode->setColor(Node::BLUE);
	}
	
	void steppedSymulation()
	{
		while(aStar.step() != goalNode)
		{
			aStar.getCurentNode->setColor(Node::RED);
			//waitForNextStep();
		}
		drawPassedRoute();
	}
	
	void continousSymulation()
	{
		while(aStar.step() != goalNode)
		{
			aStar.getCurentNode->setColor(Node::RED);	
		}
		drawPassedRoute();
	}
	
	void drawPassedRoute()	//funkcja odtwarzająca i rysująca na planszy znalezioną drogę
	{
		std::vector<Node*> path = reconstructPath(aStar.getCameFrom(),aStar.getCurrentNode());
		for( auto i = path.begin(); i != path.end(); i++ )
			(*i)->setColor(Node::BLUE);
		display.Draw();
	}
	
}