#pragma once
#include "InnerMove.h"

class InnerVertexSwap :
	public InnerMove
{
public:
	InnerVertexSwap(std::shared_ptr <SearchState> state, int cycle, int pos1, int pos2);

	// Odziedziczono za po�rednictwem elementu Move
	virtual void makeMove() override;
	virtual distance calculateCost() override;

	// Odziedziczono za po�rednictwem elementu InnerMove
	virtual std::string getName() override;
};

