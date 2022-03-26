#pragma once
#include "LocalSearch.h"

#include <chrono>
#include <random>

class RandomWalker :
	public LocalSearch
{
	std::mt19937_64 _gen;

	std::chrono::high_resolution_clock::time_point _start;
	double _workTime;
public:
	template <typename ...Args>
	RandomWalker(double workTime, std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);

	// Odziedziczono za poœrednictwem elementu LocalSearch
	virtual std::string getName() override;
	virtual void calculate(int startingNode) override;
protected:
	virtual bool stopCondition(std::shared_ptr <Move>& move) override;
private:
	virtual std::shared_ptr<Move>& selectMove() override;
};

template<typename ...Args>
inline RandomWalker::RandomWalker(double workTime, std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args)
	:LocalSearch(baseAlgorithm, args...), _workTime(workTime)
{
}
