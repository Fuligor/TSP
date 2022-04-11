#pragma once
#include "AbstractAlgorithm.h"

#include <memory>
#include <queue>

#include "MoveState.h"

class LocalSearchWithMemory:
	public AbstractAlgorithm
{
protected:
	std::shared_ptr <AbstractAlgorithm> _baseAlgorithm;
	std::priority_queue <MoveState> _goodMoves;
	std::shared_ptr <SearchState> _state;
	bool _ended;
public:
	LocalSearchWithMemory(std::shared_ptr <AbstractAlgorithm> baseAlgorithm);

	virtual void setGraph(std::shared_ptr <Graph> graph) override;
	virtual std::string getName() override;
	virtual void calculate(int startingNode) override;
protected:
	virtual MoveState selectMove();
};
