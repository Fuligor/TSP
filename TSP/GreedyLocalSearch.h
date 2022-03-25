#pragma once
#include "LocalSearch.h"
class GreedyLocalSearch :
	public LocalSearch
{
public:
	template <typename... Args>
	GreedyLocalSearch(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);

	// Odziedziczono za poœrednictwem elementu LocalSearch
	virtual std::string getName() override;
	virtual std::shared_ptr <Move>& selectMove() override;
};

template<typename ...Args>
inline GreedyLocalSearch::GreedyLocalSearch(std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args):
	LocalSearch(baseAlgorithm, args...)
{
}
