#include "InnerEdgeSwap.h"

#include <iostream>

void InnerEdgeSwap::makeMove(std::shared_ptr<SearchState> state, int node[])
{
	int cycle = state->getNodeCycle(node[0]);

	int size = state->cycle[cycle].size();

	int pos[4];
	
	for (int i = 0; i < 4; ++i)
	{
		pos[i] = state->getNodePosition(node[i]);
	}

	int start = pos[1];
	int end = pos[2];
	int dist = std::abs(start - end);

	for(int i = 0; i < 4; ++i)
	{
		int temp = std::abs(pos[i / 2] - pos[2 + i % 2]);

		if(temp < dist) {
			dist = temp;
			start = pos[i / 2];
			end = pos[2 + i % 2];
		}
	}

	if (start > end)
	{
		std::swap(start, end);
	}

	// std::cout << pos[0] << " " << pos[1] << std::endl;

	for (int i = start, j = end; i < j; i = (i + 1) % size, j = (j - 1 + size) % size)
	{
		std::swap(state->cycle[cycle][i], state->cycle[cycle][j]);

		int node1 = state->cycle[cycle][i];
		int node2 = state->cycle[cycle][j];

		// std::cout << "Node " << node1 << " " << node2 << " position before: " << _state->nodeToPosition[node1] << " " << _state->nodeToPosition[node2] << std::endl;

		std::swap(state->nodeToPosition[node1], state->nodeToPosition[node2]);

		// std::cout << "Node " << node1 << " " << node2 << " position after: " << _state->nodeToPosition[node1] << " " << _state->nodeToPosition[node2] << std::endl;
	}

	state->genereteMovesForDirection(cycle, start, end);

	for (int i = 0; i < 4; ++i)
	{
		state->recalculateNode(node[i]);
	}
}

distance InnerEdgeSwap::calculateCost(std::shared_ptr<SearchState> state, int node[])
{
	distance result = 0;

	int cycle = state->getNodeCycle(node[0]);

	int pos[4];

	for (int i = 0; i < 4; ++i)
	{
		pos[i] = state->getNodePosition(node[i]);
	}

	if (pos[0] == pos[2])
	{
		return 100;
	}

	int first = state->cycle[cycle][pos[0]];
	int first_next = state->cycle[cycle][pos[1]];

	int second = state->cycle[cycle][pos[2]];
	int second_next = state->cycle[cycle][pos[3]];

	result += (*state->graph.get())[first][second] - (*state->graph.get())[first][first_next] +
		(*state->graph.get())[first_next][second_next] - (*state->graph.get())[second][second_next];

	return result;
}

bool InnerEdgeSwap::getDirection(std::shared_ptr<SearchState> state, int node[])
{
	int pos[4];

	for (int i = 0; i < 4; ++i)
	{
		pos[i] = state->getNodePosition(node[i]);
	}

	return pos[0] - pos[1] == pos[2] - pos[3];
}

bool InnerEdgeSwap::isClose(std::shared_ptr<SearchState> state, int cycle, int pos1, int pos2)
{
	return (pos1 == (pos2 + 1) % state->cycle[cycle].size() ||
			pos2 == (pos1 + 1) % state->cycle[cycle].size());
}

bool InnerEdgeSwap::isInvalid(std::shared_ptr<SearchState> state, int node[])
{
	int cycle = state->getNodeCycle(node[0]);

	for(int i = 1; i < 4; ++i)
	{
		if(state->getNodeCycle(node[i]) != cycle)
		{
			return true;
		}
	}

	int pos[4];

	for (int i = 0; i < 4; ++i)
	{
		pos[i] = state->getNodePosition(node[i]);
	}

	if (pos[0] > pos[1])
	{
		std::swap(pos[0], pos[1]);
	}

	if (pos[2] > pos[3])
	{
		std::swap(pos[2], pos[3]);
	}

	return !(isClose(state, cycle, pos[0], pos[1]) && isClose(state, cycle, pos[2], pos[3]));
}
