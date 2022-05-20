#include "ILS2.h"
#include "Move.h"
#include "SearchState.h"
#include "RegretHeuristics.h"
#include "GreedyCycle.h"
#include <chrono>
#include <iostream>

std::shared_ptr<Move>& ILS2::selectRandomMove()
{
    size_t index = _gen() % _moves.size();

    return _moves[index];
}

std::string ILS2::getName()
{
    if (_version == 1)
    {
        return "ILS2a "; //bez LocalSearch
    }
    return "ILS2b "; //z LocalSearch
}

void ILS2::calculate(int startingNode)
{
	std::shared_ptr<AbstractAlgorithm> repairAlgorithm = std::shared_ptr<AbstractAlgorithm> (new GreedyCycle());
	repairAlgorithm->setGraph(_graph);
	_baseAlgorithm->calculate(startingNode);
	auto state = std::make_shared <SearchState>(_graph, _baseAlgorithm->getResult());
	auto start = std::chrono::high_resolution_clock::now();
	_moves.clear();
	for (auto i : _movementManagers) {
		i->generateMoves(state, _moves);
	}

	std::vector <int> nodes;
	bool* toDelete = new bool[_graph->getSize()];
	for (int i = 0; i < _graph->getSize(); ++i)
	{
		toDelete[i] = false;
	}

	for (int i = 0; i < _graph->getSize() / 2; ++i)
	{
		nodes.push_back(i);
	}

	while (true)
	{
		if (_version == 2)
		{
			while (true) {

				auto& move = selectMove();

		if (stopCondition(move))
		{
					break;
				}

				move->makeMove();

			}
		}
		
	state->verify();

	while (true)
	{
		auto temp = std::make_shared<Result>();
		

		std::shuffle(nodes.begin(), nodes.end(), _gen);

		for (int i = 0; i < _graph->getSize() / 5; ++i)
		{
			toDelete[nodes[i]] = true;
		}

		for (int i = 0; i < 2; i++)
		{
			int index = 0;

			for (auto j : state->cycle[i])
			{
				if (!toDelete[index])
				{
					temp->cycle[i].push_front(j);
				}

				++index;
			}
		}
		repairAlgorithm->setResult(temp);
		repairAlgorithm->calculate(startingNode);

		for (int i = 0; i < _graph->getSize() / 5; ++i)
		{
			toDelete[nodes[i]] = false;
		}

		if (_version == 2)
		{
		state->update(repairAlgorithm->getResult());

			while (true)
			{

				auto& move = selectMove();

				if (stopCondition(move))
				{
					break;
				}

				move->makeMove();
			}

			state->verify();
		}
		else
		{
			state->verify(repairAlgorithm->getResult());
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		if (duration.count() >= _workTime)
		{
			break;
		}
	}

	_result = state->getResult();
}
