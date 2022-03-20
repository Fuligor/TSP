#include "Move.h"

#include "Result.h"

Move::Move(std::shared_ptr<Graph> graph, std::shared_ptr<Result> initial_result)
	:_graph(graph), _result(initial_result)
{
}
