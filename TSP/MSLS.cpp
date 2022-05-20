#include "MSLS.h"

#include <algorithm>
#include <random>
#include "Result.h"

std::string MSLS::getName()
{
	return "MSLS ";
}

void MSLS::calculate(int startingNode)
{
	std::mt19937_64 gen(startingNode);
	std::vector <int> nodes;
	std::shared_ptr <Result> result;
	for (int i = 0; i < _graph->getSize(); ++i)
	{
		nodes.push_back(i);
	}

	std::shuffle(nodes.begin(), nodes.end(), gen);
	LocalSearch::calculate(nodes[0]);
	result = _result;
	for (int i = 1; i < 100; i++)
	{
		LocalSearch::calculate(nodes[i]);
		if (result->getLength(_graph) > _result->getLength(_graph))
		{
			result = _result;
		}
	}
	_result = result;
}
