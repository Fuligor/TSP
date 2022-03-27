#include "SteepLocalSearch.h"

#include "Move.h"

std::string SteepLocalSearch::getName()
{
	return "Steep " + LocalSearch::getName();
}

std::shared_ptr <Move>& SteepLocalSearch::selectMove()
{
	distance bestCost = 0;
	std::shared_ptr <Move>& bestMove = _moves[0];

	for (auto& move : _moves) {
		distance cost = move->calculateCost();

		if (cost < bestCost) {
			bestCost = cost;
			bestMove = move;
		}
	}

	return bestMove;
}
