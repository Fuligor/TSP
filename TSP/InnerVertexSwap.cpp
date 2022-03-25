#include "InnerVertexSwap.h"

#include "SearchState.h"

#include <iostream>

InnerVertexSwap::InnerVertexSwap(std::shared_ptr <SearchState> state, int cycle, int pos1, int pos2):
	InnerMove(state, cycle, pos1, pos2)
{
}

void InnerVertexSwap::makeMove()
{
	std::swap(_state->cycle[_cycle][_pos[0]], _state->cycle[_cycle][_pos[1]]);
}

distance InnerVertexSwap::calculateCost()
{
	distance result = 0;

	for (int i = 0; i < 2; ++i) {
		int other_index = (i + 1) % 2;
		int first = _state->cycle[_cycle][_pos[i]];
		int other = _state->cycle[_cycle][_pos[other_index]];

		for (int j = _pos[i] - 1; j <= _pos[i] + 1; j += 2) {
			int index = (j + _state->cycle[_cycle].size()) % _state->cycle[_cycle].size();
			if (index != _pos[other_index]) {
				int second = _state->cycle[_cycle][index];
				result += (*_state->graph.get())[other][second] - (*_state->graph.get())[first][second];
			}
		}
	}

	return result;
}

std::string InnerVertexSwap::getName()
{
	return "Inner Vertex " + std::to_string(_cycle) + " " + std::to_string(_pos[0]) + " " + std::to_string(_pos[1]);
}
