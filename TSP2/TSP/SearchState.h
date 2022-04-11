#pragma once

#include <memory>
#include <list>
#include <set>
#include <map>
#include <vector>

#include <tuple>

#include "Graph.h"
#include "Move.h"
#include "Result.h"

struct SearchState
{
	int* nodeToPosition;
	std::set <Move> movesToCalculate;
	std::shared_ptr <Graph> graph;
	std::vector <int> cycle[2];

	SearchState(std::shared_ptr <Graph> graph, std::shared_ptr <Result> result);
	~SearchState();

	std::shared_ptr <Result> getResult() const;

	void recalculateNode(int node);
	int getNodePosition(int node);
	int getNodeCycle(int node);

	void genereteBeginningMoves();
	void genereteMovesForNode(int node);
	void genereteMovesForDirection(int iCycle, int pos1, int pos2);
};

