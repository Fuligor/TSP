#include "RandomCycle.h"

#include <algorithm>
#include <random>
#include <vector>

#include <iostream>

#include "Result.h"

std::string RandomCycle::getName()
{
	return "Random Cycle";
}

void RandomCycle::calculate(int startingNode)
{
	_result = std::make_shared <Result>();

	std::mt19937_64 gen(0);
	std::vector <int> nodes;

	for (int i = 0; i < _graph->getSize(); ++i)
	{
		if (i != startingNode)
		{
			nodes.push_back(i);
		}
	}

	std::shuffle(nodes.begin(), nodes.end(), gen);

	for (int i = 0; i < _graph->getSize() - 1; ++i)
	{
		_result->cycle[(i + 1) / (_graph->getSize() / 2)].push_front(nodes[i]);
	}

	_result->cycle[0].push_front(startingNode);
}
