#include <limits>
#include <iostream>

#include "Graph.h"
#include "Result.h"
#include "TSPLoader.h"

#include "NearestNeighbor.h"
#include "GreedyCycle.h"
#include "RegretHeuristics.h"

void testAlgorithm(std::shared_ptr <Graph>& graph, std::shared_ptr <AbstractAlgorithm> algorithm)
{
	algorithm->setGraph(graph);

	distance min = std::numeric_limits<distance>::max();
	std::shared_ptr <Result> minCycle;
	distance max = 0;
	double avg = 0.0;

	for (int i = 0; i < 100; ++i)
	{
		algorithm->calculate(i);

		auto result = algorithm->getResult();

		distance length = result->getLength(graph);
		if(length < min)
		{
			min = length;
			minCycle = result;
		}
		if(length > max)
		{
			max = length;
		}

		avg = avg * i / (i + 1.0) + length / (i + 1.0);
	}

	for (int j = 0; j < 2; j++)
	{
		std::cout << j << ": ";

		for (auto k : minCycle->cycle[j])
		{
			std::cout << k << ", ";
		}

		std::cout << std::endl;
	}

	std::cout << algorithm->getName() << ": " << avg << "(" << min << " - " << max << ")" << std::endl;
}

int main() {
	std::shared_ptr<AbstractLoader> loader = std::make_shared<TSPLoader>();
	
	auto graph = loader->loadFile("kroB100.tsp");

	std::cout << graph->getName() << std::endl;

	for(unsigned int i = 0; i < graph->getSize(); ++i) {
		for(unsigned int j = 0; j < graph->getSize(); ++j) {
			std::cout << (*graph.get())[i][j] << "\t";
		}

		std::cout << std::endl;
	}

	testAlgorithm(graph, std::make_shared<NearestNeighbor>());
	testAlgorithm(graph, std::make_shared<GreedyCycle>());
	testAlgorithm(graph, std::make_shared<RegretHeuristics>());

	// for(int i = 0; i < graph->getSize(); ++i)
}