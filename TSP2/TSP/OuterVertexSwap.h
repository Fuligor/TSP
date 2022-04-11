#pragma once
#include <memory>

#include "SearchState.h"

struct OuterVertexSwap
{
	static void makeMove(std::shared_ptr <SearchState> state, int node[]);
	static distance calculateCost(std::shared_ptr<SearchState> state, int node[]);
	static bool getDirection(std::shared_ptr<SearchState> state, int node[]);

	static bool isInvalid(std::shared_ptr<SearchState> state, int node[]);
};

