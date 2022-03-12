#include "RegretHeuristics.h"

#include "Result.h"

#include <iostream>

std::pair<distance, std::forward_list<int>::iterator> RegretHeuristics::calculateCostToCycle(int node, int cycle)
{
	distance minCost = std::numeric_limits<distance>::max();
	distance secondCost = std::numeric_limits<distance>::max();
	std::forward_list<int>::iterator positionInCycle;

	for (auto it = _result->cycle[cycle].begin(); it != _result->cycle[cycle].end(); ++it)
	{
		auto next = it;
		++next;

		if (next == _result->cycle[cycle].end())
		{
			next = _result->cycle[cycle].begin();
		}

		distance temp = (*_graph.get())[node][*it] + (*_graph.get())[node][*next] - (*_graph.get())[*it][*next];

		if (temp < minCost)
		{
			secondCost = minCost;
			minCost = temp;
			positionInCycle = it;
		}
		else if(temp < secondCost) {
			secondCost = temp;
		}
	}

	distance cost = 1.8 * minCost - secondCost;

	return std::pair <distance, std::forward_list<int>::iterator>(cost, positionInCycle);
}

std::string RegretHeuristics::getName()
{
    return "Regret Heuristics";
}
