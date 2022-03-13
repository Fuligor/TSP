#include <limits>
#include <iostream>
#include <fstream>

#include "Graph.h"
#include "Result.h"
#include "TSPLoader.h"

#include "NearestNeighbour.h"
#include "GreedyCycle.h"
#include "RegretHeuristics.h"

#include "DrawGraph.h"

std::string testAlgorithm(std::shared_ptr <Graph>& graph, std::shared_ptr <AbstractAlgorithm> algorithm, location* locations, std::string filename)
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
	
	DrawGraph draw = DrawGraph();
	draw.showGraph(locations, minCycle, algorithm->getName(), filename, graph->getSize());

	return algorithm->getName() + ": " + std::to_string(avg) + "(" + std::to_string(min) + " - " + std::to_string(max) + ")\n";
}

int main() {
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[2] = { "kroA100.tsp", "kroB100.tsp" };
	std::string algorithmsResults = "";
	for (int i = 0; i < 2; i++)
	{
		auto graph = loader->loadFile("Data/" + filenames[i]);

		std::cout << graph->getName() << std::endl;

		/*for(unsigned int i = 0; i < graph->getSize(); ++i) {
			for(unsigned int j = 0; j < graph->getSize(); ++j) {
				std::cout << (*graph.get())[i][j] << "\t";
			}

			std::cout << std::endl;
		}*/
		algorithmsResults += graph->getName() + "\n";
		algorithmsResults += testAlgorithm(graph, std::make_shared<NearestNeighbour>(), loader->getLocation(), filenames[i]);
		algorithmsResults += testAlgorithm(graph, std::make_shared<GreedyCycle>(), loader->getLocation(), filenames[i]);
		algorithmsResults += testAlgorithm(graph, std::make_shared<RegretHeuristics>(), loader->getLocation(), filenames[i]);
	}
	
	
	std::ofstream output;
	output.open("Results/Wyniki_algorytmow.txt");
	output << algorithmsResults;
	output.close();
	
}