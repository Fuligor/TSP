#include "InnerVertexSwapManager.h"

#include "InnerVertexSwap.h"
#include "SearchState.h"

std::string InnerVertexSwapManager::getName()
{
	return "Inner Vertex";
}

void InnerVertexSwapManager::generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves)
{
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < state->cycle[i].size(); ++j) {
			for (int k = j + 1; k < state->cycle[i].size(); ++k) {
				moves.push_back(std::shared_ptr <Move> (new InnerVertexSwap(state, i, j, k)));
			}
		}
	}
}
