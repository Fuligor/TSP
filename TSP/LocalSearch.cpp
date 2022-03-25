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
	_baseAlgorithm->calculate(startingNode);
	auto state = std::make_shared <SearchState>(_graph, _baseAlgorithm->getResult());

	_moves.clear();

	for (auto i : _movementManagers) {
		i->generateMoves(state, _moves);
	}

	while (true) {
		auto& move = selectMove();

		if (move->calculateCost() >= 0) {
			break;
		}

		move->makeMove();
	}

	_result = state->getResult();
}