#include "Population.h"

#include <algorithm>
#include <iostream>


Population::Population(std::shared_ptr<Graph> graph, size_t population_size)
	:_graph(graph), _population_size(population_size)
{
}

void Population::add(std::shared_ptr<GeneticState> state)
{
	if(_unique.find(state->getLength(_graph)) != _unique.end())
	{
		return;
	}

	if (_vector.size() >= _population_size)
	{
		auto top = _queue.top();

		if(state->getLength(_graph) >= top.first)
		{
			return;
		}

		_queue.pop();
		_vector[top.second] = state;
		_queue.emplace(state->getLength(_graph), top.second);
		_unique.erase(top.first);
	}
	else
	{
		_indices.push_back(_indices.size());
		_queue.emplace(state->getLength(_graph), _vector.size());
		_vector.push_back(state);
	}
	
	_unique.insert(state->getLength(_graph));
}

std::shared_ptr<Result> Population::getBest()
{
	std::shared_ptr <Result> result = _vector.front();

	for(auto i: _vector)
	{
		if(result->getLength(_graph) > i->getLength(_graph))
		{
			result = i;
		}
	}

	return result;
}

Population::parents Population::getParents()
{
	std::shuffle(_indices.begin(), _indices.end(), _gen);

	return parents(_vector[_indices[0]], _vector[_indices[1]]);
}
