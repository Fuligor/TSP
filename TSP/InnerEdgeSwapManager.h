#pragma once
#include "MovementManager.h"
class InnerEdgeSwapManager :
	public MovementManager
{
public:
	// Odziedziczono za poœrednictwem elementu MovementManager
	virtual std::string getName() override;
	virtual void generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves) override;
};

