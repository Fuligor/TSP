#pragma once
#include <memory>
#include <string>
#include <vector>

class Move;
struct SearchState;

class MovementManager
{
public:
	virtual std::string getName() = 0;
	virtual void generateMoves(std::shared_ptr <SearchState> state, std::vector <std::shared_ptr <Move>>& moves) = 0;
};