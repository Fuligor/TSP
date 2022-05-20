#pragma once
#include <unordered_set>
#include <queue>
#include <random>
#include <vector>

#include "GeneticState.h"

class Population
{
	typedef std::vector <std::shared_ptr <GeneticState>> vectorType;
	typedef std::pair <distance, size_t> queueType;
protected:
	struct Compare
	{
		bool operator()(const queueType& a, const queueType& b)
		{
			return a.first < b.first;
		}
	};

	std::shared_ptr <Graph> _graph;
	size_t _population_size;
	vectorType _vector;
	std::mt19937_64 _gen;
	std::priority_queue <queueType, std::vector<queueType>, Compare> _queue;
	std::unordered_set <distance> _unique;
	std::vector <int> _indices;
public:
	Population(std::shared_ptr <Graph> graph, size_t population_size);

	void add(std::shared_ptr <GeneticState> state);
	std::shared_ptr <Result> getBest();

	typedef std::pair<std::shared_ptr <GeneticState>, std::shared_ptr<GeneticState>> parents;
	parents getParents();
};