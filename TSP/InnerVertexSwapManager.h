#pragma once
#include "MovementManager.h"

class InnerVertexSwapManager :
	public MovementManager
{
public:
	// Odziedziczono za pośrednictwem elementu MovementManager
	virtual std::string getName() override;
	virtual void generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves) override;
	virtual void generateCanditatesMoves(std::shared_ptr <SearchState> state, std::vector <std::shared_ptr <Move>>& moves, int n) override;
};

