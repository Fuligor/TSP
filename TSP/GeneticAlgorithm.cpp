#include "GeneticAlgorithm.h"

#include <algorithm>
#include <chrono>
#include <random>

#include "GeneticState.h"
#include "GreedyCycle.h"
#include "RegretHeuristics.h"
#include "Move.h"
#include "Population.h"
#include "SearchState.h"

std::string GeneticAlgorithm::getName()
{
    return "Genetic Algorithm " + std::to_string(_version);
}

void GeneticAlgorithm::calculate(int startingNode)
{
	std::mt19937_64 gen(startingNode);
	std::vector <int> nodes;
	std::shared_ptr <Result> result;
	auto repairAlgorithm = std::shared_ptr <GreedyAlgorithm>(new RegretHeuristics());
	repairAlgorithm->setGraph(_graph);
	size_t population_size = 20;
	Population population(_graph, population_size); 
	int is_static = 0;
	int mutation_prob = 5;

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < _graph->getSize(); ++i)
	{
		nodes.push_back(i);
	}

	std::shuffle(nodes.begin(), nodes.end(), gen);
	for (int i = 0; i < population_size; i++)
	{
		LocalSearch::calculate(nodes[i]);
		auto state = std::make_shared <GeneticState>(GeneticState(_result));
		population.add(state);
	}

	auto state = std::make_shared <SearchState>(_graph, _result);
	_moves.clear();
	for (auto i : _movementManagers)
	{
		i->generateMoves(state, _moves);
	}

	while (true)
	{
		auto parents = population.getParents();
		auto child = GeneticState::crossover(parents.first, parents.second);
		std::shared_ptr <GeneticState> childState;

		if (gen() % 100 < mutation_prob)
		{
			repairAlgorithm->setCandidates(20);
		}
		else
		{
			repairAlgorithm->setCandidates();
		}
		
		repairAlgorithm->setResult(child);
		repairAlgorithm->calculate(startingNode);

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

			childState = std::make_shared <GeneticState>(state->getResult());
		}
		else
		{
			childState = std::make_shared <GeneticState>(repairAlgorithm->getResult());
		}

		if (population.add(childState))
		{
			is_static++;
		}
		else
		{
			is_static = 0;
		}

		if (is_static < 5)
		{
			mutation_prob = 5;
		}
		else if (is_static > 100)
		{
			mutation_prob = 100;
		}
		else
		{
			mutation_prob = is_static;
		}

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		if (duration.count() >= _workTime)
		{
			break;
		}
	}

	_result = population.getBest();
}
