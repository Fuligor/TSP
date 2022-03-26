#pragma once
#include "LocalSearch.h"

#include <random>

class GreedyLocalSearch :
	public LocalSearch
{
	std::mt19937_64 _gen;
public:
	template <typename... Args>
	GreedyLocalSearch(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);

	// Odziedziczono za poœrednictwem elementu LocalSearch
	virtual std::string getName() override;

protected:
	virtual std::shared_ptr <Move>& selectMove() override;
};

template<typename ...Args>
inline GreedyLocalSearch::GreedyLocalSearch(std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args):
	LocalSearch(baseAlgorithm, args...), _gen(0)
{
}
