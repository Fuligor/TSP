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

#include "GreedyLocalSearch.h"
#include "SteepLocalSearch.h"
#include "RandomWalker.h"

#include "InnerEdgeSwapManager.h"
#include "InnerVertexSwapManager.h"
#include "OuterVertexSwapManager.h"

#include "MSLS.h"
#include "ILS1.h"
#include "ILS2.h"

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

	for (int i = 0; i < 10; ++i)
	{
		std::cout << i << std::endl;
		auto start = std::chrono::steady_clock::now();
		algorithm->calculate(i);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		double time = elapsed_seconds.count();

		auto result = algorithm->getResult();

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

void exercise1()
{
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[2] = { "kroA200.tsp", "kroB200.tsp" };
	std::string algorithmsResults = "";
	std::string* result;
	std::string timeResults = "";

	std::string resultDir = "ResultsLab3/";
	for (int i = 0; i < 2; i++)
	{
		auto graph = loader->loadFile("Data/" + filenames[i]);

		std::cout << graph->getName() << std::endl;

		algorithmsResults += graph->getName() + "\n";
		timeResults += graph->getName() + "\n";

		//algorithmsResults += testAlgorithm(graph, std::make_shared<NearestNeighbour>(), loader->getLocation(), resultDir + filenames[i])[0];
		//algorithmsResults += testAlgorithm(graph, std::make_shared<GreedyCycle>(), loader->getLocation(), resultDir + filenames[i])[0];
		result = testAlgorithm(graph, std::make_shared<RegretHeuristics>(), loader->getLocation(), resultDir + filenames[i]);
		algorithmsResults += result[0];
		timeResults += result[1];
		//algorithmsResults += testAlgorithm(graph, std::make_shared<RandomCycle>(), loader->getLocation(), resultDir + filenames[i])[0];

	}


	std::ofstream output, outputTime;
	output.open(resultDir + "Wyniki_algorytmow.txt");
	output << algorithmsResults;
	output.close();

	outputTime.open(resultDir + "Wyniki_czasowe.txt");
	outputTime << timeResults;
	outputTime.close();
}

std::vector <std::shared_ptr <AbstractAlgorithm>> createAlgorithms(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, std::shared_ptr <MovementManager> innerMove)
{
	return std::vector <std::shared_ptr <AbstractAlgorithm>> {
		//std::shared_ptr <AbstractAlgorithm>(new GreedyLocalSearch(baseAlgorithm,
		//	innerMove, std::make_shared <OuterVertexSwapManager>())),
		//std::shared_ptr <AbstractAlgorithm>(new SteepLocalSearch(baseAlgorithm,
			//innerMove, std::make_shared <OuterVertexSwapManager>()))
		std::shared_ptr <AbstractAlgorithm>(new MSLS(baseAlgorithm,
			innerMove, std::make_shared <OuterVertexSwapManager>()))
	};
}

void exercise2()
{
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[2] = { "kroA200.tsp", "kroB200.tsp" };
	std::string algorithmsResults = "";
	std::string timeResults = "";
	std::string resultDir = "ResultsLab3/";

	std::shared_ptr <AbstractAlgorithm> baseAlgorithms[] = {
		//std::make_shared<RegretHeuristics>(),
		std::make_shared<RandomCycle>()
	};

	std::shared_ptr <MovementManager> innerMoves[] = {
		std::make_shared <InnerEdgeSwapManager>()//,
		//std::make_shared <InnerVertexSwapManager>()
	};

	std::string* result;
	for (int i = 0; i < 2; i++)
	{
		auto graph = loader->loadFile("Data/" + filenames[i]);
		std::cout << graph->getName() << std::endl;
		algorithmsResults += graph->getName() + "\n";
		timeResults += graph->getName() + "\n";

		for (int j = 0; j < sizeof(baseAlgorithms) / sizeof(*baseAlgorithms); ++j)
		{
			for (int k = 0; k < sizeof(innerMoves) / sizeof(*innerMoves); ++k)
			{
				double max_time = 0;

				for (auto algorithm : createAlgorithms(baseAlgorithms[j], innerMoves[k]))
				{
					result = testAlgorithm(graph, algorithm,
						loader->getLocation(), resultDir + filenames[i]);
					algorithmsResults += result[0];
					timeResults += result[1];

					double time = std::stod(result[2]);
					if (max_time < time) {
						max_time = time;
					}

					delete[] result;
				}

				/*auto randomWalker = std::shared_ptr <AbstractAlgorithm>(new RandomWalker(
					max_time, baseAlgorithms[j], innerMoves[k], std::make_shared <OuterVertexSwapManager>()
				));

				result = testAlgorithm(graph, randomWalker,
					loader->getLocation(), resultDir + filenames[i]);
				algorithmsResults += result[0];
				timeResults += result[1];*/
			}
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
void exercise3()
{
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[2] = { "kroA200.tsp", "kroB200.tsp" };
	std::string algorithmsResults = "";
	std::string timeResults = "";
	std::string resultDir = "ResultsLab4/";

	std::shared_ptr <AbstractAlgorithm> baseAlgorithms[] = {
		std::make_shared<RegretHeuristics>()
		//std::make_shared<RandomCycle>()
	};

	std::shared_ptr <MovementManager> innerMoves[] = {
		std::make_shared <InnerEdgeSwapManager>()
	};

	std::string* result;
	for (int i = 0; i < 2; i++)
	{
		auto graph = loader->loadFile("Data/" + filenames[i]);
		std::cout << graph->getName() << std::endl;
		algorithmsResults += graph->getName() + "\n";
		timeResults += graph->getName() + "\n";

		for (int j = 0; j < sizeof(baseAlgorithms) / sizeof(*baseAlgorithms); ++j)
		{
			for (int k = 0; k < sizeof(innerMoves) / sizeof(*innerMoves); ++k)
			{
				double max_time = 0;

				for (auto algorithm : createAlgorithms(baseAlgorithms[j], innerMoves[k]))
				{
					result = testAlgorithm(graph, algorithm,
						loader->getLocation(), resultDir + filenames[i]);
					algorithmsResults += result[0];
					timeResults += result[1];

					double time = std::stod(result[2]);
					if (max_time < time) {
						max_time = time;
					}

					delete[] result;
				}

				auto randomWalker = std::shared_ptr <AbstractAlgorithm>(new ILS1(
					max_time, baseAlgorithms[j], innerMoves[k], std::make_shared <OuterVertexSwapManager>()
				));

				result = testAlgorithm(graph, randomWalker,
					loader->getLocation(), resultDir + filenames[i]);
				algorithmsResults += result[0];
				timeResults += result[1];
				randomWalker = std::shared_ptr <AbstractAlgorithm>(new ILS2(1,
					max_time, baseAlgorithms[j], innerMoves[k], std::make_shared <OuterVertexSwapManager>()
				));

				result = testAlgorithm(graph, randomWalker,
					loader->getLocation(), resultDir + filenames[i]);
				algorithmsResults += result[0];
				timeResults += result[1];
				randomWalker = std::shared_ptr <AbstractAlgorithm>(new ILS2(2,
					max_time, baseAlgorithms[j], innerMoves[k], std::make_shared <OuterVertexSwapManager>()
				));

				result = testAlgorithm(graph, randomWalker,
					loader->getLocation(), resultDir + filenames[i]);
				algorithmsResults += result[0];
				timeResults += result[1];
			}
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
	//exercise2();
	exercise3();
}