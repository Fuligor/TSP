#include "SearchState.h"

#include <cmath>
#include <iostream>

SearchState::SearchState(std::shared_ptr<Graph> graph, std::shared_ptr<Result> result)
	:graph(graph), nodeToPosition(new int[graph->getSize()])
{
	for (int i = 0; i < 2; i++)
	{
		for (auto j : result->cycle[i])
		{
			cycle[i].push_back(j);
			nodeToPosition[j] = (2 * i - 1) * cycle[i].size();
		}
	}
}

SearchState::~SearchState()
{
}

std::shared_ptr<Result> SearchState::getResult() const
{
	auto result = std::make_shared <Result>();

	for (int i = 0; i < 2; i++)
	{
		auto pos = result->cycle[i].before_begin();
		for (auto j : cycle[i])
		{
			pos = result->cycle[i].insert_after(pos, j);
		}
	}

	return result;
}

void SearchState::recalculateNode(int node)
{
	// std::cout << "Recalculate node: " << node << std::endl;

	// std::cout << node << std::endl;

	int pos = getNodePosition(node);
	int iCycle = getNodeCycle(node);

	genereteMovesForNode(node);
}

int SearchState::getNodePosition(int node)
{
	return std::abs(nodeToPosition[node]) - 1;
}

int SearchState::getNodeCycle(int node)
{
	return nodeToPosition[node] > 0;
}

void SearchState::genereteBeginningMoves()
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < cycle[i].size(); ++j)
		{
			int j_next = (j + 1) % cycle[i].size();

			for (int k = j + 2; k < cycle[i].size(); ++k)
			{
				int k_next = (k + 1) % cycle[i].size();

				movesToCalculate.insert(Move(cycle[i][j], cycle[i][j_next], cycle[i][k], cycle[i][k_next]));
			}
		}
	}

	for (int i = 0; i < cycle[0].size(); ++i)
	{
		int i_prev = (i - 1 + cycle[0].size()) % cycle[0].size();
		int i_next = (i + 1) % cycle[0].size();

		for (int j = 0; j < cycle[1].size(); ++j)
		{
			int j_prev = (j - 1 + cycle[1].size()) % cycle[1].size();
			int j_next = (j + 1) % cycle[1].size();

			movesToCalculate.insert(Move(cycle[0][i], cycle[1][j], cycle[0][i_prev], cycle[0][i_next], cycle[1][j_prev], cycle[1][j_next]));
		}
	}
}

void SearchState::genereteMovesForNode(int node)
{
	int iCycle = getNodeCycle(node);
	int pos = getNodePosition(node);

	int node_next = (pos + 1) % cycle[iCycle].size();

	for (int i = 0; i < cycle[iCycle].size(); ++i)
	{
		int i_next = (i + 1) % cycle[iCycle].size();

		if (std::abs(pos - i) > 1)
		{
			movesToCalculate.insert(Move(node, cycle[iCycle][node_next], cycle[iCycle][i], cycle[iCycle][i_next]));
		}
	}

	int pos_prev = (pos - 1 + cycle[0].size()) % cycle[0].size();
	int pos_next = (pos + 1) % cycle[0].size();

	for (int i = 0; i < cycle[(iCycle + 1) % 2].size(); ++i)
	{
		int i_prev = (i - 1 + cycle[0].size()) % cycle[0].size();
		int i_next = (i + 1) % cycle[0].size();

		if (iCycle == 0)
		{
			movesToCalculate.insert(Move(node, cycle[1][i], cycle[0][pos_prev], cycle[0][pos_next], cycle[1][i_prev], cycle[1][i_next]));
		}
		else
		{
			movesToCalculate.insert(Move(cycle[0][i], node, cycle[0][i_prev], cycle[0][i_next], cycle[1][pos_prev], cycle[1][pos_next]));
		}
	}
}

void SearchState::genereteMovesForDirection(int iCycle, int pos1, int pos2)
{
	int size = cycle[iCycle].size();

	for (int i = pos1; i <= pos2; i++)
	{
		int node1 = cycle[iCycle][i];
		int node1_next = cycle[iCycle][(i + 1) % size];

		for (int j = 0; j < size; ++j)
		{
			int node2 = cycle[iCycle][j];
			int node2_next = cycle[iCycle][(j + 1) % size];
			movesToCalculate.insert(Move(node1, node1_next, node2, node2_next));
		}
	}
}
