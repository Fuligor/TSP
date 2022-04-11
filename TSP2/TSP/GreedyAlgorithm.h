#pragma once
#include "AbstractAlgorithm.h"

#include <limits>
#include <forward_list>

#include "Graph.h"

class GreedyAlgorithm
	:public AbstractAlgorithm
{
protected:
	std::forward_list <int> _free_nodes;

	int getStartingNodes(int startingNode);
	void addBestNodeToCycle(int cycle);
	virtual std::pair <distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) = 0;
	void addToCycle(int node, int cycle);
	void addToCycle(int node, int cycle, std::forward_list<int>::iterator pos);
	void initCalculations(int startingNode);
public:
	virtual void calculate(int startingNode);
};

