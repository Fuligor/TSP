#pragma once

#include <memory>
#include <vector>

#include "Graph.h"
#include "Result.h"

struct SearchState
{
private:
	std::vector <int> reference[2];
	distance reference_distance;
	int candidates_count;

public:
	std::shared_ptr <Graph> graph;
	std::vector <int> cycle[2];
	int** closests;

	SearchState(std::shared_ptr <Graph> graph, std::shared_ptr <Result> result, int n = -1);
	~SearchState();

	void update(std::shared_ptr <Result> result);

	void verify();
	void verify(std::shared_ptr <Result> result);

	std::shared_ptr <Result> getResult() const;

	distance getLength(std::vector <int> cycle[]) const;
};

