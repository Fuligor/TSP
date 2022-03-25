#pragma once
#include "Move.h"
class InnerMove :
	public Move
{
protected:
	int _cycle;
	int _pos[2];
public:
	InnerMove(std::shared_ptr <SearchState> state, int cycle, int pos1, int pos2);
};

