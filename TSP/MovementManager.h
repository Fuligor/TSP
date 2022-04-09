#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Graph.h"

class Move;
struct SearchState;

class MovementManager
{
public:
	virtual std::string getName() = 0;
	virtual void generateMoves(std::shared_ptr <SearchState> state, std::vector <std::shared_ptr <Move>>& moves) = 0;
	virtual void generateCanditatesMoves(std::shared_ptr <SearchState> state, std::vector <std::shared_ptr <Move>>& moves, int n) = 0;
	//int* getClosest(int n, unsigned int node, std::shared_ptr <Graph> graph);

};