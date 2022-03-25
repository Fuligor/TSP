#include "OuterVertexSwapManager.h"

#include "OuterVertexSwap.h"
#include "SearchState.h"

std::string OuterVertexSwapManager::getName()
{
	return "Outer Vertex";
}

void OuterVertexSwapManager::generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves) {
	for (int j = 0; j < state->cycle[0].size(); ++j) {
		for (int k = 0; k < state->cycle[1].size(); ++k) {
			moves.push_back(std::shared_ptr <Move> (new OuterVertexSwap(state, j, k)));
		}
	}
}