#include "GreedyLocalSearch.h"

#include <algorithm>
#include <random>

#include "Move.h"

std::string GreedyLocalSearch::getName()
{
	return "Greedy Local Search " + LocalSearch::getName();
}

std::shared_ptr <Move>& GreedyLocalSearch::selectMove()
{
	std::mt19937_64 gen(0);

	std::shuffle(_moves.begin(), _moves.end(), gen);

	for (auto& move : _moves) {
		if (move->calculateCost() < 0) {
			return move;
		}
	}

	return _moves[0];
}
