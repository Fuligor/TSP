#include "RandomWalker.h"

std::string RandomWalker::getName()
{
	return "Random Walker " + LocalSearch::getName();
}

void RandomWalker::calculate(int startingNode)
{
	_start = std::chrono::high_resolution_clock::now();

	LocalSearch::calculate(startingNode);
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
