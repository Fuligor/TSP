#include "SearchState.h"
#include <iostream>

SearchState::SearchState(std::shared_ptr<Graph> graph, std::shared_ptr<Result> result, int n)
	:graph(graph)
{
	for (int i = 0; i < 2; i++) {
		for (auto j : result->cycle[i]) {
			cycle[i].push_back(j);
		}
	}

	closests = new int* [graph->getSize()];
	for (unsigned int k = 0; k < graph->getSize(); k++)
	{
		closests[k] = new int[n];
		for (int i = 0; i < n; i++)
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
				for (int m = 0; m < n; m++)
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
