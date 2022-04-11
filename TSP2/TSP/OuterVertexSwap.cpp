#include "OuterVertexSwap.h"

#include "SearchState.h"

/*void OuterVertexSwap::makeMove()
{
	
}

distance OuterVertexSwap::calculateCost()
{
	distance result = 0;
	int pos[] = { _state->getNodePosition(_node[0]), _state->getNodePosition(_node[1]) };

	for (int i = 0; i < 2; ++i)
	{
		int other_cycle = (i + 1) % 2;

		for (int j = pos[i] - 1; j <= pos[i] + 1; j += 2)
		{
			int index = (j + _state->cycle[i].size()) % _state->cycle[i].size();
			int second = _state->cycle[i][index];

			result += (*_state->graph.get())[_node[other_cycle]][second] - (*_state->graph.get())[_node[i]][second];
		}
	}

	return result;
}

std::string OuterVertexSwap::getName()
{
	return "Outer Vertex " + std::to_string(_node[0]) + " " + std::to_string(_node[1]);
}

void OuterVertexSwap::makeMoveWithInvalidation()
{
	int pos[] = { _state->getNodePosition(_node[0]), _state->getNodePosition(_node[1]) };

	for (int direction = 0; direction < 2; ++direction)
	{
		for (int cycle = 0; cycle < 2; ++cycle)
		{
			for (int i = 0; i < _state->cycle[cycle].size(); ++i)
			{
				_state->directionCalculated[direction][cycle][pos[cycle]][i] = false;
				_state->directionCalculated[direction][cycle][i][pos[cycle]] = false;
			}
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			int index = (pos[i] + j + _state->cycle[i].size()) % _state->cycle[i].size();

			int node = _state->cycle[i][index];

			_state->recalculateNode(node);
		}
	}

	makeMove();
}*/

void OuterVertexSwap::makeMove(std::shared_ptr<SearchState> state, int node[])
{
	int pos[] = { state->getNodePosition(node[0]), state->getNodePosition(node[1]) };

	std::swap(state->cycle[0][pos[0]], state->cycle[1][pos[1]]);
	std::swap(state->nodeToPosition[node[0]], state->nodeToPosition[node[1]]);

	for (int i = 0; i < 2; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			int index = (pos[i] + j + state->cycle[i].size()) % state->cycle[i].size();

			int node = state->cycle[i][index];

			state->recalculateNode(node);
		}
	}
}

distance OuterVertexSwap::calculateCost(std::shared_ptr<SearchState> state, int node[])
{
	distance result = 0;
	int pos[] = { state->getNodePosition(node[0]), state->getNodePosition(node[1]) };

	for (int i = 0; i < 2; ++i)
	{
		int other_cycle = (i + 1) % 2;

		for (int j = pos[i] - 1; j <= pos[i] + 1; j += 2)
		{
			int index = (j + state->cycle[i].size()) % state->cycle[i].size();
			int second = state->cycle[i][index];

			result += (*state->graph.get())[node[other_cycle]][second] - (*state->graph.get())[node[i]][second];
		}
	}

	return result;
}

bool OuterVertexSwap::getDirection(std::shared_ptr<SearchState> state, int node[])
{
	return true;
}

bool OuterVertexSwap::isInvalid(std::shared_ptr<SearchState> state, int node[])
{
	int cycle[] = { state->getNodeCycle(node[0]), state->getNodeCycle(node[1]) };


	for(int i = 0; i < 2; i++)
	{
		int pos = state->getNodePosition(node[i]);
		int neighbours[] = { (pos - 1 + state->cycle[cycle[i]].size()) % state->cycle[cycle[i]].size(), (pos + 1) % state->cycle[cycle[i]].size() };

		for(int j = 0; j < 2; j++)
		{
			if(state->cycle[cycle[i]][neighbours[j]] != node[2 + 2 * i] && state->cycle[cycle[i]][neighbours[j]] != node[2 + 2 * i + 1])
			{
				return true;
			}
		}
	}

	if(cycle[0] != 0)
	{
		return true;
	}

	return cycle[1] != 1;
}
