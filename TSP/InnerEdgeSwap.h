#pragma once
#include "InnerMove.h"

class InnerEdgeSwap :
	public InnerMove
{
public:
	InnerEdgeSwap(std::shared_ptr <SearchState> state, int cycle, int pos1, int pos2);

	// Odziedziczono za pośrednictwem elementu Move
	virtual void makeMove() override;
	virtual distance calculateCost() override;

	// Odziedziczono za pośrednictwem elementu InnerMove
	virtual std::string getName() override;
};

