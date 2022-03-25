#include "InnerMove.h"

InnerMove::InnerMove(std::shared_ptr<SearchState> state, int cycle, int pos1, int pos2):
	Move(state), _cycle(cycle), _pos{ pos1, pos2 }
{
	if (_pos[1] < _pos[0]) {
		std::swap(_pos[0], _pos[1]);
	}
}
