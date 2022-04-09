#include "InnerVertexSwapManager.h"

#include "InnerVertexSwap.h"
#include "SearchState.h"

std::string InnerVertexSwapManager::getName()
{
	return "Vertex";
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

void InnerVertexSwapManager::generateCanditatesMoves(std::shared_ptr<SearchState> state, std::vector<std::shared_ptr<Move>>& moves, int n)
{
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < state->cycle[i].size(); ++j) {
			//int* closest = getClosest(n, j, graph);
			for (int k = j + 1; k < state->cycle[i].size(); ++k) {
				for (int l = 0; l < n; l++)
				{
					if (state->closests[j][l] == state->cycle[1][k])
					{
						moves.push_back(std::shared_ptr <Move>(new InnerVertexSwap(state, i, j, k)));
						break;
					}
				}
				
			}
			//delete closest;
		}
	}
}
