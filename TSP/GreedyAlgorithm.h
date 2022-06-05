#pragma once
#include "AbstractAlgorithm.h"

#include <limits>
#include <forward_list>
#include <random>

#include "Graph.h"

class GreedyAlgorithm
	:public AbstractAlgorithm
{
protected:
	size_t _candidates_count;
	std::forward_list <int> _free_nodes;
	std::mt19937_64 _gen;

	int getStartingNodes(int startingNode);
	void addBestNodeToCycle(int cycle);
	virtual std::pair <distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) = 0;
	void addToCycle(int node, int cycle);
	void addToCycle(int node, int cycle, std::forward_list<int>::iterator pos);
	void initCalculations(int startingNode);
public:
	GreedyAlgorithm(size_t candidates_count);

	void setCandidates(size_t candidates_count = 1);

	virtual void calculate(int startingNode);
};

