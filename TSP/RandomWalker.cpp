#include "RandomWalker.h"

#include <iostream>

#include "Move.h"
#include "SearchState.h"

std::string RandomWalker::getName()
{
	return "Random Walker " + LocalSearch::getName();
}

void RandomWalker::calculate(int startingNode)
{
	_start = std::chrono::high_resolution_clock::now();

	_baseAlgorithm->calculate(startingNode);
	_result = _baseAlgorithm->getResult();
	distance _minDelta = 0;
	distance _actualDelta = 0;
	auto state = std::make_shared <SearchState>(_graph, _result, 10);

	_moves.clear();

	for (auto i : _movementManagers)
	{
		i->generateMoves(state, _moves);
	}

	while (true)
	{
		auto& move = selectMove();

		if (stopCondition(move))
		{
			break;
		}

		_actualDelta += move->calculateCost();

		move->makeMove();

		if (_actualDelta < _minDelta)
		{
			_minDelta = _actualDelta;
			_result = state->getResult();
		}
	}
}

bool RandomWalker::stopCondition(std::shared_ptr<Move>& move)
{
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - _start;
	return duration.count() >= _workTime;
}

std::shared_ptr<Move>& RandomWalker::selectMove()
{
	size_t index = _gen() % _moves.size();

	return _moves[index];
}
