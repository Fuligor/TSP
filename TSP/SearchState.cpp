#include "SearchState.h"
#include <iostream>

SearchState::SearchState(std::shared_ptr<Graph> graph, std::shared_ptr<Result> result, int n)
	:graph(graph), candidates_count(n)
{
	update(result);

	for (int i = 0; i < 2; i++)
	{
		for (auto j : result->cycle[i])
		{
			reference[i].push_back(j);
		}
	}

	reference_distance = getLength(reference);

	if (candidates_count > 0)
	{
		closests = new int* [graph->getSize()];
		for (unsigned int k = 0; k < graph->getSize(); k++)
		{
			closests[k] = new int[candidates_count];
			for (int i = 0; i < candidates_count; i++)
			{
				closests[k][i] = -1;
			}
		}


		for (unsigned int k = 0; k < graph->getSize(); k++)
		{
			for (unsigned int i = 0; i < graph->getSize(); i++)
			{
				if (i != k)
				{
					int mx = 0;
					for (int m = 0; m < candidates_count; m++)
					{
						if (closests[k][m] == -1)
						{
							closests[k][m] = i;
							mx = m;
							break;
						}
						else if ((*graph.get())[k][closests[k][mx]] < (*graph.get())[k][closests[k][m]])
						{
							mx = m;
						}
					}
					if ((*graph.get())[k][i] < (*graph.get())[k][closests[k][mx]])
					{
						closests[k][mx] = i;
					}
				}

			}
		}
	}
}

SearchState::~SearchState()
{
	if (candidates_count > 0)
	{
		for (unsigned int k = 0; k < graph->getSize(); k++)
		{
			delete[] closests[k];
		}

		delete[] closests;
	}
}

void SearchState::update(std::shared_ptr<Result> result)
{
	for (int i = 0; i < 2; i++)
	{
		cycle[i].clear();

		for (auto j : result->cycle[i])
		{
			cycle[i].push_back(j);
		}
	}
}

void SearchState::verify()
{
	distance actual_distance = getLength(cycle);

	if (actual_distance < reference_distance)
	{
		reference_distance = actual_distance;
		
		for (int i = 0; i < 2; ++i)
		{
			reference[i] = cycle[i];
		}
	}
	else
	{
		for (int i = 0; i < 2; ++i)
		{
			cycle[i] = reference[i];
		}
	}
}

void SearchState::verify(std::shared_ptr<Result> result)
{
	distance actual_distance = result->getLength(graph);

	if (actual_distance < reference_distance)
	{
		reference_distance = actual_distance;

		update(result);

		for (int i = 0; i < 2; ++i)
		{
			reference[i] = cycle[i];
		}
	}
}

std::shared_ptr<Result> SearchState::getResult() const
{
	auto result = std::make_shared <Result>();

	for (int i = 0; i < 2; i++) {
		auto pos = result->cycle[i].before_begin();
		for (auto j : cycle[i]) {
			pos = result->cycle[i].insert_after(pos, j);
		}
	}

	return result;
}

distance SearchState::getLength(std::vector<int> cycle[]) const
{
	distance result = 0;

	for (int i = 0; i < 2; ++i)
	{
		auto last = cycle[i].front();

		for (auto j : cycle[i])
		{
			result += (*graph.get())[j][last];
			last = j;
		}

		result += (*graph.get())[cycle[i].front()][last];
	}

	return result;
}
