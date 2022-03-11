#include <iostream>

#include "Graph.h"
#include "Result.h"
#include "TSPLoader.h"

#include "NearestNeighbor.h"

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

	std::shared_ptr <AbstractAlgorithm> algorithm = std::make_shared<NearestNeighbor>();

	algorithm->setGraph(graph);

	algorithm->calculate(0);

	auto result = algorithm->getResult();

	for(int j = 0; j < 2; j++) {
		std::cout << j << ": ";

		for(auto k: result->cycle[j]) {
			std::cout << k << ", ";
		}

		std::cout << std::endl;
	}

	// for(int i = 0; i < graph->getSize(); ++i)
}