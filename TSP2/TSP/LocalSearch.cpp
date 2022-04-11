#include "LocalSearch.h"

#include <iostream>

#include "Move.h"
#include "SearchState.h"

LocalSearchWithMemory::LocalSearchWithMemory(std::shared_ptr<AbstractAlgorithm> baseAlgorithm)
	:_baseAlgorithm(baseAlgorithm)
{
}

void LocalSearchWithMemory::setGraph(std::shared_ptr<Graph> graph)
{
	AbstractAlgorithm::setGraph(graph);
	_baseAlgorithm->setGraph(graph);
}

std::string LocalSearchWithMemory::getName()
{
	return "Local Search with Memory ";
}

void LocalSearchWithMemory::calculate(int startingNode)
{
	_baseAlgorithm->calculate(startingNode);
	_state = std::make_shared <SearchState>(_graph, _baseAlgorithm->getResult());

	_state->genereteBeginningMoves();

	while (true) {
		auto move = selectMove();

		if (_ended) {
			break;
		}

		//std::cout << move.getCost() << " " << move.getName() << std::endl;

		move.makeMove();
	}

	while (!_goodMoves.empty())
	{
		_goodMoves.pop();
	}

	_result = _state->getResult();
	_state.reset();
}

MoveState LocalSearchWithMemory::selectMove()
{
	for (auto i : _state->movesToCalculate)
	{
		auto move = MoveState(_state, i);

		if (move.getCost() < 0)
		{
			_goodMoves.push(move);
		}
	}

	_state->movesToCalculate.clear();

	_ended = true;
	if (_goodMoves.empty())
	{
		return MoveState();
	}
	auto result = _goodMoves.top();

	std::list <MoveState> movesToAdd;

	while (!_goodMoves.empty())
	{
		result = _goodMoves.top();
		_goodMoves.pop();

		if (result.isOutdated())
		{
			continue;
		}

		if (result.isInvalidated())
		{
			movesToAdd.push_back(result);

			continue;
		}

		_ended = false;

		break;
	}

	for (auto& i : movesToAdd)
	{
		_goodMoves.push(i);
	}

	return result;
}