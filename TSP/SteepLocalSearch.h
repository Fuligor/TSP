#pragma once
#include "LocalSearch.h"

class SteepLocalSearch :
	public LocalSearch
{
public:
	template <typename... Args>
	SteepLocalSearch(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);
	
	// Odziedziczono za poœrednictwem elementu LocalSearch
	virtual std::string getName() override;

protected:
	virtual std::shared_ptr <Move>& selectMove() override;
};

template<typename ...Args>
inline SteepLocalSearch::SteepLocalSearch(std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args) :
	LocalSearch(baseAlgorithm, args...)
{
}

