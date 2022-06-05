#include "GreedyAlgorithm.h"

#include "Result.h"

#include <algorithm>
#include <iostream>
#include <vector>

struct InsertCandidate
{
	distance cost;
	std::forward_list<int>::iterator position;
	int node;
};

bool operator < (const InsertCandidate& a, const InsertCandidate& b)
{
	return a.cost < b.cost;
}

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
	std::vector <InsertCandidate> candidates;

	for (auto i : _free_nodes)
	{
		auto temp = calculateCostToCycle(i, cycle);

		if (candidates.size() >= _candidates_count) {
			if (temp.first < candidates.front().cost) {
				std::pop_heap(candidates.begin(), candidates.end());
				candidates.pop_back();
			}
			else {
				continue;
			}
		}

		candidates.push_back({
				temp.first,
				temp.second,
				i
			});
		std::push_heap(candidates.begin(), candidates.end());
	}

	int index = _gen() % candidates.size();

	InsertCandidate choosenCandidate = candidates[index];

	addToCycle(choosenCandidate.node, cycle, choosenCandidate.position);
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

GreedyAlgorithm::GreedyAlgorithm(size_t candidates_count)
	:_candidates_count(candidates_count)
{
}

void GreedyAlgorithm::setCandidates(size_t candidates_count)
{
	_candidates_count = candidates_count;
}

void GreedyAlgorithm::calculate(int startingNode)
{
	_gen.seed(startingNode);

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
		delete[] toAdd;
	}
	
	while(!_free_nodes.empty()) {
		int size0 = std::distance(_result->cycle[0].begin(), _result->cycle[0].end());
		int size1 = std::distance(_result->cycle[1].begin(), _result->cycle[1].end());
		int actualCycle = size0 > size1;

		addBestNodeToCycle(actualCycle);
	}
}
