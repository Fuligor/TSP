#pragma once
#include <memory>

#include "SearchState.h"

struct InnerEdgeSwap
{
	static void makeMove(std::shared_ptr <SearchState> state, int node[]);
	static distance calculateCost(std::shared_ptr<SearchState> state, int node[]);
	static bool getDirection(std::shared_ptr<SearchState> state, int node[]);
	static bool isClose(std::shared_ptr<SearchState> state, int cycle, int pos1, int pos2);
	static bool isInvalid(std::shared_ptr<SearchState> state, int node[]);
};

