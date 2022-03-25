#include "InnerEdgeSwap.h"

#include "SearchState.h"

InnerEdgeSwap::InnerEdgeSwap(std::shared_ptr<SearchState> state, int cycle, int pos1, int pos2) :
	InnerMove(state, cycle, pos1, pos2)
{
}

void InnerEdgeSwap::makeMove()
{
	int size = _state->cycle[_cycle].size();
	// int direction = (long long) _pos[1] - _pos[0] <= _state->cycle[_cycle].size() / 2 ? 1 : -1;

	for (int i = _pos[0] + 1, j = _pos[1]; i < j; i = (i + 1) % size, j = (j - 1 + size) % size) {
		std::swap(_state->cycle[_cycle][i], _state->cycle[_cycle][j]);
	}
}

distance InnerEdgeSwap::calculateCost()
{
	distance result = 0;

	int first = _state->cycle[_cycle][_pos[0]];
	int index = (_pos[0] + 1ll) % _state->cycle[_cycle].size();
	int first_next = _state->cycle[_cycle][index];

	int second = _state->cycle[_cycle][_pos[1]];
	index = (_pos[1] + 1ll) % _state->cycle[_cycle].size();
	int second_next = _state->cycle[_cycle][index];

	result += (*_state->graph.get())[first][second] - (*_state->graph.get())[first][first_next] +
		(*_state->graph.get())[first_next][second_next] - (*_state->graph.get())[second][second_next];

	return result;
}

std::string InnerEdgeSwap::getName()
{
	return "Inner Edge " + std::to_string(_cycle) + " " + std::to_string(_pos[0]) + " " + std::to_string(_pos[1]);
}
