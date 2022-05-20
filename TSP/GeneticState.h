#pragma once
#include "Result.h"

#include <unordered_map>

#include "GreedyAlgorithm.h"

class GeneticState:
	public Result
{
protected:
	std::unordered_map <int, int> _edges;

	distance _distance = -1;
public:
	GeneticState(std::shared_ptr <Result> result);
	static std::shared_ptr <Result> crossover(const std::shared_ptr <GeneticState>& a, const std::shared_ptr <GeneticState>& b);

	distance getLength(std::shared_ptr <Graph> graph);

	bool containEdge(int a, int b) const;
	void insert(int a, int b, int iCycle, std::forward_list <int>::iterator& iterator);
};