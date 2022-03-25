#include "OuterVertexSwap.h"

#include "SearchState.h"

OuterVertexSwap::OuterVertexSwap(std::shared_ptr <SearchState> state, int pos1, int pos2) :
	Move(state), _pos{ pos1, pos2 }
{
}

void OuterVertexSwap::makeMove()
{
	std::swap(_state->cycle[0][_pos[0]], _state->cycle[1][_pos[1]]);
}

distance OuterVertexSwap::calculateCost()
{
	distance result = 0;

	for (int i = 0; i < 2; ++i) {
		int other_cycle = (i + 1) % 2;
		int first = _state->cycle[i][_pos[i]];
		int other = _state->cycle[other_cycle][_pos[other_cycle]];

		for (int j = _pos[i] - 1; j <= _pos[i] + 1; j += 2) {
			int index = (j + _state->cycle[i].size()) % _state->cycle[i].size();
			int second = _state->cycle[i][index];

			result += (*_state->graph.get())[other][second] - (*_state->graph.get())[first][second];
		}
	}

	return result;
}

std::string OuterVertexSwap::getName()
{
	return "Outer Vertex " + std::to_string(_pos[0]) + " " + std::to_string(_pos[1]);
}
