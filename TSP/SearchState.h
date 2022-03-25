#pragma once

#include <memory>
#include <vector>

#include "Graph.h"
#include "Result.h"

struct SearchState
{
	std::shared_ptr <Graph> graph;
	std::vector <int> cycle[2];

	SearchState(std::shared_ptr <Graph> graph, std::shared_ptr <Result> result);

	std::shared_ptr <Result> getResult() const;
};

