#include "GreedyCycle.h"

#include "Result.h"

std::pair<distance, std::forward_list<int>::iterator> GreedyCycle::calculateCostToCycle(int node, int cycle)
{
	distance minCost = std::numeric_limits<distance>::max();
	std::forward_list<int>::iterator positionInCycle;

	for (auto it = _result->cycle[cycle].begin(); it != _result->cycle[cycle].end(); ++it)
	{
		auto next = it;
		++next;

		if(next == _result->cycle[cycle].end())
		{
			next = _result->cycle[cycle].begin();
		}

		distance temp = (*_graph.get())[node][*it] + (*_graph.get())[node][*next] - (*_graph.get())[*it][*next];

		if (temp < minCost)
		{
			minCost = temp;
			positionInCycle = it;
		}
	}

	return std::pair <distance, std::forward_list<int>::iterator>(minCost, positionInCycle);
}

GreedyCycle::GreedyCycle(size_t candidates_count)
	:GreedyAlgorithm(candidates_count)
{
}

std::string GreedyCycle::getName()
{
    return "Greedy Cycle";
}