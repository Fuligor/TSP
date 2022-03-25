#include "SearchState.h"

SearchState::SearchState(std::shared_ptr<Graph> graph, std::shared_ptr<Result> result)
	:graph(graph)
{
	for (int i = 0; i < 2; i++) {
		for (auto j : result->cycle[i]) {
			cycle[i].push_back(j);
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
