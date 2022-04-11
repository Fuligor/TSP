#pragma once
#include <forward_list>
#include <memory>

#include "Graph.h"

struct Result
{
	std::forward_list <int> cycle[2];

	distance getLength(std::shared_ptr <Graph> graph);
};
