#pragma once
#include <memory>

#include "Graph.h"

struct SearchState;

class Move
{
protected:
	std::shared_ptr <SearchState> _state;
public:
	Move(std::shared_ptr <SearchState> state);

	virtual void makeMove() = 0;
	virtual distance calculateCost() = 0;
	virtual std::string getName() = 0;
};

