#include "AbstractAlgorithm.h"

#include "Graph.h"
#include "Result.h"

void AbstractAlgorithm::setGraph(std::shared_ptr<Graph> graph)
{
	_graph = graph;
}

std::shared_ptr<Result> AbstractAlgorithm::getResult()
{
	return _result;
}
