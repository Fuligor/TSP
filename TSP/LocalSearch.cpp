#include "LocalSearch.h"

#include <iostream>

#include "Move.h"
#include "SearchState.h"

void LocalSearch::construct(std::shared_ptr<MovementManager> movement)
{
	_movementManagers.push_back(movement);
}

void LocalSearch::setGraph(std::shared_ptr<Graph> graph)
{
	AbstractAlgorithm::setGraph(graph);
	_baseAlgorithm->setGraph(graph);
}

std::string LocalSearch::getName()
{
	std::string result = _baseAlgorithm->getName() + " ";

	for (auto i : _movementManagers) {
		result += i->getName() + " ";
	}

	return result;
}

void LocalSearch::calculate(int startingNode)
{
	int n = 10;
	_baseAlgorithm->calculate(startingNode);
	auto state = std::make_shared <SearchState>(_graph, _baseAlgorithm->getResult(), n);

	

	

	while (true) {
		_moves.clear();
		for (auto i : _movementManagers) {
			//i->generateMoves(state, _moves);
			i->generateCanditatesMoves(state, _moves, n);
		}
		auto& move = selectMove();

		if (stopCondition(move)) {
			break;
		}

		move->makeMove();
	}

	_result = state->getResult();
}

bool LocalSearch::stopCondition(std::shared_ptr <Move>& move) {
	return move->calculateCost() >= 0;
}