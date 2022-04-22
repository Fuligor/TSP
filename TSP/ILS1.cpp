#include "ILS1.h"
#include "Move.h"
#include "SearchState.h"
#include <chrono>
#include <iostream>


std::shared_ptr<Move>& ILS1::selectRandomMove()
{
	size_t index = _gen() % _moves.size();

	return _moves[index];
}

std::string ILS1::getName()
{
	return "ILS1 ";
}

void ILS1::calculate(int startingNode)
{
	int n = 15;
	_baseAlgorithm->calculate(startingNode);
	auto state = std::make_shared <SearchState>(_graph, _baseAlgorithm->getResult(), n);
	_result = state->getResult();
	auto start = std::chrono::high_resolution_clock::now();
	_moves.clear();
	for (auto i : _movementManagers) {
		i->generateMoves(state, _moves);
		//i->generateCanditatesMoves(state, _moves, n);
	}
	while (true)
	{
		while (true) {
			//std::cout << 1;

			auto& move = selectMove();

			if (stopCondition(move)) {
				break;
			}

			move->makeMove();

		}
		//std::cout << 2;
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		if (_result->getLength(_graph) > state->getResult()->getLength(_graph))
		{
			_result = state->getResult();
		}
		if (duration.count() >= _workTime)
		{
			
			break;
		}
		for (int i = 0; i < 20; i++)
		{
			auto& move = selectRandomMove();
			move->makeMove();
		}
		
	}
	



}
