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
	if (_result == nullptr)
	{
		initCalculations(startingNode);
	}
	else
	{
		bool* toAdd = new bool[_graph->getSize()];
		for (int i = 0; i < _graph->getSize(); i++)
		{
			toAdd[i] = true;
		}
		for (int i = 0; i < 2; i++)
		{
			for (auto j : _result->cycle[i])
			{
				toAdd[j] = false;
			}
		}
		_free_nodes.clear();
		for (int i = 0; i < _graph->getSize(); i++)
		{
			if (toAdd[i])
			{
				_free_nodes.push_front(i);
			}
		}
	}
	
	while(!_free_nodes.empty()) {
		int size0 = std::distance(_result->cycle[0].begin(), _result->cycle[0].end());
		int size1 = std::distance(_result->cycle[1].begin(), _result->cycle[1].end());
		int actualCycle = size0 > size1;

		addBestNodeToCycle(actualCycle);
	}
}
