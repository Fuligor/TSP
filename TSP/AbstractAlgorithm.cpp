#include "AbstractAlgorithm.h"

#include "Result.h"

int AbstractAlgorithm::getStartingNodes(int startingNode)
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

void AbstractAlgorithm::addBestNodeToCycle(int cycle)
{
	distance minCost = std::numeric_limits<distance>::max();
	int bestNode = -1;
	std::list<int>::iterator positionInCycle;

	for (auto i : _free_nodes)
	{
		std::pair <distance, std::list<int>::iterator> temp = calculateCostToCycle(i, cycle);

		if (temp.first < minCost)
		{
			minCost = temp.first;
			positionInCycle = temp.second;
			bestNode = i;
		}
	}

	addToCycle(bestNode, cycle, positionInCycle);
}

std::pair <distance, std::list<int>::iterator> AbstractAlgorithm::calculateCostToCycle(int node, int cycle)
{
	distance minCost = std::numeric_limits<distance>::max();
	std::list<int>::iterator positionInCycle;

	for (std::list<int>::iterator it = _result->cycle[cycle].begin(); it != _result->cycle[cycle].end(); ++it)
	{
		distance temp = calculateCost(node, it);

		if (temp < minCost)
		{
			minCost = temp;
			positionInCycle = it;
		}
	}

	return std::pair <distance, std::list<int>::iterator>(minCost, positionInCycle);
}

void AbstractAlgorithm::addToCycle(int node, int cycle)
{
	addToCycle(node, cycle, _result->cycle[cycle].begin());
}

void AbstractAlgorithm::addToCycle(int node, int cycle, std::list<int>::iterator pos)
{
	_free_nodes.remove(node);
	_result->cycle[cycle].insert(pos, node);
}

void AbstractAlgorithm::initCalculations(int startingNode)
{
	_result = std::make_shared <Result>();

	for (int i = 0; i < _graph->getSize(); ++i)
	{
		_free_nodes.push_back(i);
	}

	addToCycle(startingNode, 0);
	addToCycle(getStartingNodes(startingNode), 1);
}

void AbstractAlgorithm::setGraph(std::shared_ptr<Graph> graph)
{
	_graph = graph;
}

void AbstractAlgorithm::calculate(int startingNode)
{
	initCalculations(startingNode);

	int i = 0;

	while(!_free_nodes.empty()) {
		addBestNodeToCycle(i++ % 2);
	}
}

std::shared_ptr<Result> AbstractAlgorithm::getResult()
{
	return _result;
}
