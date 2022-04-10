#include "OuterVertexSwapManager.h"

#include "OuterVertexSwap.h"
#include "SearchState.h"

std::string OuterVertexSwapManager::getName()
{
	return "Vertex";
}

void OuterVertexSwapManager::generateMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr <Move>>& moves) {
	for (int j = 0; j < state->cycle[0].size(); ++j) {
		for (int k = 0; k < state->cycle[1].size(); ++k) {
			moves.push_back(std::shared_ptr <Move> (new OuterVertexSwap(state, j, k)));
		}
	}
}

void OuterVertexSwapManager::generateCanditatesMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr<Move>>& moves, int n)
{
	for (int j = 0; j < state->cycle[0].size(); ++j) {
		//int* closest = getClosest(n, j, graph);
		for (int k = 0; k < state->cycle[1].size(); ++k) {
			for (int l = 0; l < n; l++)
			{
				if (state->closests[state->cycle[0][j]][l] == state->cycle[1][k] || state->closests[state->cycle[1][k]][l] == state->cycle[0][j])
				{
					moves.push_back(std::shared_ptr <Move>(new OuterVertexSwap(state, j, k)));
					break;
				}
			}
			
		}
		//delete closest;
	}
}
