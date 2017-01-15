class AStar
{
	std::vector<Node*> closedSet;	//zbiór odwiedzonych
	std::vector<Node*> openSet;		//zbiór otkrytych nieodwiedzonych
	std::map<Node*,Node*> cameFrom;
	Node* currentNode;
	Node* startNode;
	Node* goalNode;
	public AStar(Node* startNode, Node* goalNode)
	{
		this->startNode = startNode;
		//this->goalNode = goalNode;
		openSet.push_back(startNode);
		startNode->setPriority(abs(startNode->getX()-goalNode->getX())+abs(startNode->getY()-goalNode->getY()));	//przypisz przewidywaną długość drogi przechodzącej przez dany punkt
		startNode->setPassedRoute(0);	//przypisz przebytą drogę
	}
		
	Node* step()
	{
		currentNode = openSet[0];
		for( auto i = openSet.begin(); i != openSet.end(); i++ )//weź najlepszy ze zbioru odkrytych nieodwiedzonych
		{
			if(currentNode->getPriority()>(*i)->getPriority())
			currentNode = *i;
		}

		openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
		closedSet.push_back(currentNode);
		for (int i = 0; i < 4; i++)	//Dodaj sąsiadów do zbioru odkrytych
		{
			if (std::find(closedSet.begin(), closedSet.end(),currentNode->next[i])!=closedSet.end())
				continue;

			if (!(std::find(openSet.begin(), openSet.end(),currentNode->next[i])!=openSet.end()) && currentNode->next[i])
			{
				openSet.push_back(currentNode->next[i]);
                currentNode->next[i]->setPriority((abs(currentNode->next[i]->getX()-goalNode->getX())+abs(currentNode->next[i]->getY()-goalNode->getY())) + (currentNode->getPassedRoute() + 1));	//przypisz przewidywaną długość drogi przechodzącej przez dany punkt
                currentNode->next[i]->setPassedRoute(currentNode->getPassedRoute()+1);	//przypisz przebytą drogę
			}
			cameFrom[currentNode->next[i]]=currentNode;
		}
		return currentNode;
	}

	std::vector<Node*> reconstructPath(std::map<Node*,Node*> cameFrom, Node* currentNode)	//funkcja odtwarzająca przebytą drogę
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
	
	Node* getCurrentNode()
	{
		return currentNode;
	}
	
	std::map<Node*,Node*> getCameFrom()
	{
		return cameFrom;
	}

}
