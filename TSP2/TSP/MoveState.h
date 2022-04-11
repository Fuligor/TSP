#pragma once
#include <memory>

#include "Move.h"
#include "SearchState.h"

class MoveState
{
	std::shared_ptr <SearchState> _state;
	distance _cost;
	bool _direction;
	Move _move;
public:
	MoveState();
	MoveState(std::shared_ptr <SearchState> state, Move move);

	bool isOutdated();
	bool isInvalidated();
	distance getCost() const;
	void makeMove();
	std::string getName() const;

	bool operator < (const MoveState& other) const;
};

