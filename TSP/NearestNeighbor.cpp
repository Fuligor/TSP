#include "NearestNeighbor.h"

#include "Result.h"

std::pair<distance, std::forward_list<int>::iterator> NearestNeighbor::calculateCostToCycle(int node, int cycle)
{
	distance minCost = std::numeric_limits<distance>::max();
	std::forward_list<int>::iterator positionInCycle;

	for (auto it = _result->cycle[cycle].begin(); it != _result->cycle[cycle].end(); ++it)
	{
		distance temp = (*_graph.get())[node][*it];

		if (temp < minCost)
		{
			minCost = temp;
			positionInCycle = it;
		}
	}

	return std::pair <distance, std::forward_list<int>::iterator>(minCost, positionInCycle);
}

std::string NearestNeighbor::getName()
{
	return "Nearest Neighbor";
}