#include <limits>
#include <iostream>
#include <fstream>
#include <chrono>

#include "Graph.h"
#include "Result.h"
#include "TSPLoader.h"

#include "NearestNeighbour.h"
#include "GreedyCycle.h"
#include "RegretHeuristics.h"
#include "RandomCycle.h"

#include "LocalSearch.h"

#include "DrawGraph.h"

std::string* testAlgorithm(std::shared_ptr <Graph>& graph, std::shared_ptr <AbstractAlgorithm> algorithm, location* locations, std::string filename)
{
	algorithm->setGraph(graph);

	distance min = std::numeric_limits<distance>::max();
	std::shared_ptr <Result> minCycle;
	distance max = 0;
	double avg = 0.0;

	double minTime = std::numeric_limits<double>::max();
	double maxTime = 0;
	double avgTime = 0;

	for (int i = 0; i < 100; ++i)
	{
		auto start = std::chrono::steady_clock::now();
		algorithm->calculate(i);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		double time = elapsed_seconds.count();

		auto result = algorithm->getResult();

		std::cout << i << ": " << result->getLength(graph) << std::endl;

		distance length = result->getLength(graph);
		if (length < min)
		{
			min = length;
			minCycle = result;
		}
		if (length > max)
		{
			max = length;
		}
		if (time > maxTime)
		{
			maxTime = time;
		}
		if (time < minTime)
		{
			minTime = time;
		}

		avg = avg * i / (i + 1.0) + length / (i + 1.0);
		avgTime = avgTime * i / (i + 1.0) + time / (i + 1.0);
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
	std::cout << "Time" << ": " << avgTime << "(" << minTime << " - " << maxTime << ")" << std::endl;

	DrawGraph draw = DrawGraph();
	draw.showGraph(locations, minCycle, algorithm->getName(), filename, graph->getSize());

	std::string* result = new std::string[3]{ algorithm->getName() + ": " + std::to_string(avg) + "(" + std::to_string(min) + " - " + std::to_string(max) + ")\n",
	algorithm->getName() + " Time: " + std::to_string(avgTime) + "(" + std::to_string(minTime) + " - " + std::to_string(maxTime) + ")\n",
	std::to_string(avgTime)};

	return result;
}

void exercise2()
{
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[] = { "kroA200.tsp", "kroB200.tsp" };
	std::string algorithmsResults = "";
	std::string timeResults = "";
	std::string resultDir = "ResultsLab2/";

	std::shared_ptr <AbstractAlgorithm> baseAlgorithms[] = {
		//std::make_shared<RegretHeuristics>()
		std::make_shared<RandomCycle>()
	};

	std::string* result;
	for (int i = 0; i < 2; i++)
	{
		auto graph = loader->loadFile("Data/" + filenames[i]);
		//std::cout << graph->getName() << std::endl;
		algorithmsResults += graph->getName() + "\n";
		timeResults += graph->getName() + "\n";

		for (int j = 0; j < sizeof(baseAlgorithms) / sizeof(*baseAlgorithms); ++j)
		{
			auto memory = std::shared_ptr <AbstractAlgorithm>(new LocalSearchWithMemory(
				baseAlgorithms[j]
			));

			result = testAlgorithm(graph, memory,
								   loader->getLocation(), resultDir + filenames[i]);
			algorithmsResults += result[0];
			timeResults += result[1];
		}


		std::ofstream output, outputTime;
		output.open(resultDir + "Wyniki_algorytmow.txt");
		output << algorithmsResults;
		output.close();

		outputTime.open(resultDir + "Wyniki_czasowe.txt");
		outputTime << timeResults;
		outputTime.close();
	}
}

int main() {
	//exercise1();
	exercise2();
}