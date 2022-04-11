#include "GreedyAlgorithm.h"

#include "Result.h"

#include <iostream>

int GreedyAlgorithm::getStartingNodes(int startingNode)
{
	distance maxDistance = 0;
	int secondNode = -1;

	for (int i = 0; i < _graph->getSize(); ++i)
	{
		auto distance = (*_graph.get())[startingNode][i];

		if (distance > maxDistance)
		{
			maxDistance = distance;
			secondNode = i;
		}
	}

	return secondNode;
}

void GreedyAlgorithm::addBestNodeToCycle(int cycle)
{
	distance minCost = std::numeric_limits<distance>::max();
	int bestNode = -1;
	std::forward_list<int>::iterator positionInCycle = _result->cycle[cycle].before_begin();

	for (auto i : _free_nodes)
	{
		auto temp = calculateCostToCycle(i, cycle);

		if (temp.first <= minCost)
		{
			minCost = temp.first;
			positionInCycle = temp.second;
			bestNode = i;
		}
	}

	addToCycle(bestNode, cycle, positionInCycle);
}

void GreedyAlgorithm::addToCycle(int node, int cycle)
{
	addToCycle(node, cycle, _result->cycle[cycle].before_begin());
}

void GreedyAlgorithm::addToCycle(int node, int cycle, std::forward_list<int>::iterator pos)
{
	_free_nodes.remove(node);
	_result->cycle[cycle].insert_after(pos, node);
}

void GreedyAlgorithm::initCalculations(int startingNode)
{
	_result = std::make_shared <Result>();

	for (int i = 0; i < _graph->getSize(); ++i)
	{
		_free_nodes.push_front(i);
	}

	addToCycle(startingNode, 0);
	addToCycle(getStartingNodes(startingNode), 1);
}

void GreedyAlgorithm::calculate(int startingNode)
{
	initCalculations(startingNode);

	int i = 0;

	while(!_free_nodes.empty()) {
		addBestNodeToCycle(i++ % 2);
	}
}
