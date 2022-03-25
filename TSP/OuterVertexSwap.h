#pragma once
#include "Move.h"
class OuterVertexSwap :
	public Move
{
	int _pos[2];
public:
	OuterVertexSwap(std::shared_ptr <SearchState> state, int pos1, int pos2);

	// Odziedziczono za poœrednictwem elementu Move
	virtual void makeMove() override;
	virtual distance calculateCost() override;

	// Odziedziczono za poœrednictwem elementu Move
	virtual std::string getName() override;
};

