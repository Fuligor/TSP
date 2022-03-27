#include "InnerEdgeSwapManager.h"

#include "InnerEdgeSwap.h"
#include "SearchState.h"

std::string InnerEdgeSwapManager::getName()
{
	return "Edge";
}

void InnerEdgeSwapManager::generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves)
{
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < state->cycle[i].size(); ++j) {
			for (int k = j + 2; k < state->cycle[i].size(); ++k) {
				moves.push_back(std::shared_ptr <Move> (new InnerEdgeSwap(state, i, j, k)));
			}
		}
	}
}
