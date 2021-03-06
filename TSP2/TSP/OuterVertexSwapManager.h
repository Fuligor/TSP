#pragma once
#include "MovementManager.h"
class OuterVertexSwapManager :
	public MovementManager
{
public:
	// Odziedziczono za pośrednictwem elementu MovementManager
	virtual std::string getName() override;
	virtual void generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves) override;
};

