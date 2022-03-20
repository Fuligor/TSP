#pragma once
#include <memory>

#include "Graph.h"

struct Result;

class Move
{
	std::shared_ptr <Graph> _graph;
	std::shared_ptr <Result> _result;
public:
	Move(std::shared_ptr <Graph> graph, std::shared_ptr <Result> initial_result);

	virtual void makeMove() = 0;
	virtual distance calculateCost() = 0;
};

