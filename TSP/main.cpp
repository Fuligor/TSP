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
#include "GeneticAlgorithm.h"

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
		std::shared_ptr <AbstractAlgorithm>(new GreedyLocalSearch(baseAlgorithm,
			innerMove, std::make_shared <OuterVertexSwapManager>()))//,
		//std::shared_ptr <AbstractAlgorithm>(new SteepLocalSearch(baseAlgorithm,
			//innerMove, std::make_shared <OuterVertexSwapManager>()))
		//std::shared_ptr <AbstractAlgorithm>(new MSLS(baseAlgorithm,
			//innerMove, std::make_shared <OuterVertexSwapManager>()))
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
		//std::make_shared<RegretHeuristics>()
		std::make_shared<RandomCycle>()
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

void exercise4()
{
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[2] = { "kroA200.tsp", "kroB200.tsp" };
	std::string algorithmsResults = "";
	std::string timeResults = "";
	std::string resultDir = "ResultsLab5/";

	std::shared_ptr <AbstractAlgorithm> baseAlgorithms[] = {
		//std::make_shared<RegretHeuristics>()
		//std::make_shared<RandomCycle>()
		std::make_shared<NearestNeighbour>()
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
					if (max_time < time)
					{
						max_time = time;
					}

					delete[] result;
				}

				/*auto randomWalker = std::shared_ptr <AbstractAlgorithm>(new ILS1(
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
				timeResults += result[1];*/

				/*auto randomWalker = std::shared_ptr <AbstractAlgorithm>(new GeneticAlgorithm(1,
																						max_time, baseAlgorithms[j], innerMoves[k], std::make_shared <OuterVertexSwapManager>()
				));

				result = testAlgorithm(graph, randomWalker,
									   loader->getLocation(), resultDir + filenames[i]);
				algorithmsResults += result[0];
				timeResults += result[1];*/

				auto randomWalker = std::shared_ptr <AbstractAlgorithm>(new GeneticAlgorithm(2,
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

int similarityVertices(std::shared_ptr <Result> cycleA, std::shared_ptr <Result> cycleB)
{
	int result = 0;
	for (int i = 0; i < 2; i++)
	{
		int sum[2];
		sum[0] = 0;
		sum[1] = 0;
		for (int j = 0; j < 2; j++)
		{
			
			for (auto k : cycleA->cycle[i])
			{
				for (auto p : cycleB->cycle[j])
				{
					if (p == k)
					{
						sum[j]++;
					}
				}
			}

		}
		if (sum[0] > sum[1])
		{
			result += sum[0];
		}
		else
		{
			result += sum[1];
		}
	}
	return result;
}
int similarityEdges(std::shared_ptr <Result> cycleA, std::shared_ptr <Result> cycleB)
{
	int result = 0;
	for (int i = 0; i < 2; i++)
	{
		int sum = 0;
		for (int j = 0; j < 2; j++)
		{
			std::vector<int> vectorA(cycleA->cycle[i].begin(), cycleA->cycle[i].end());
			std::vector<int> vectorB(cycleB->cycle[j].begin(), cycleB->cycle[j].end());

			for (std::size_t k = 0; k < vectorA.size(); ++k) 
			{

				for (std::size_t p = 0; p < vectorB.size(); ++p)
				{
					if ((vectorA[k] == vectorB[p] && vectorA[(k + 1)% vectorA.size()] == vectorB[(p + 1)% vectorB.size()]) || (vectorA[k] == vectorB[(p + 1) % vectorB.size()] && vectorA[(k + 1) % vectorA.size()] == vectorB[p]))
					{
						sum++;
					}
				}
			}

		}
		result += sum;
	}
	return result;
}

std::string* testAlgorithm1000(std::shared_ptr <Graph>& graph, std::shared_ptr <AbstractAlgorithm> algorithm, location* locations, std::string filename)
{
	algorithm->setGraph(graph);

	distance min = std::numeric_limits<distance>::max();
	int minCycle = 0;


	std::shared_ptr <Result> *resultCycles = new std::shared_ptr <Result>[1000];

	int size = 1000;

	for (int i = 0; i < size; ++i)
	{
		std::cout << i << std::endl;

		algorithm->calculate(i%200);


		resultCycles[i] = algorithm->getResult();

		distance length = resultCycles[i]->getLength(graph);
		if (length < min)
		{
			min = length;
			minCycle = i;
		}
	
	}
	double averageVertSim[1000];
	int theBestVertSim[1000];
	int target[1000];
	double averageEdgSim[1000];
	int theBestEdgSim[1000];
	for (int k = 0; k < size; k++)
	{
		if (k != minCycle)
		{
			int bestVertSim = 0;
			double avgVertSim = 0;
			int bestEdgSim = 0;
			double avgEdgSim = 0;
			for (int p = 0; p < size; p++)
			{

				if (p != k)
				{
					int vertSim = similarityVertices(resultCycles[k], resultCycles[p]);
					int edgSim = similarityEdges(resultCycles[k], resultCycles[p]);
					avgVertSim += vertSim;
					avgEdgSim += edgSim;
					if (p == minCycle)
					{
						bestVertSim = vertSim;
						bestEdgSim = edgSim;
					}
				}
			}
			avgVertSim = avgVertSim / (size - 1);
			avgEdgSim = avgEdgSim / (size - 1);
			averageVertSim[k] = avgVertSim;
			theBestVertSim[k] = bestVertSim;
			target[k] = resultCycles[k]->getLength(graph);
			averageEdgSim[k] = avgEdgSim;
			theBestEdgSim[k] = bestEdgSim;
		}
		
	}

	for (int j = 0; j < 2; j++)
	{
		std::cout << j << ": ";

		for (auto k : resultCycles[minCycle]->cycle[j])
		{
			std::cout << k << ", ";
		}

		std::cout << std::endl;
	}

	//std::cout << algorithm->getName() << ": " << avg << "(" << min << " - " << max << ")" << std::endl;
	//std::cout << "Time" << ": " << avgTime << "(" << minTime << " - " << maxTime << ")" << std::endl;
	std::string avgVertSimString = "AverageVerticesSim = [";
	std::string bestVertSimString = "BestVerticesSim = [";
	std::string targetString = "Target = [";
	std::string avgEdgSimString = "AverageEdgesSim = [";
	std::string bestEdgSimString = "BestEdgesSim = [";
	for (int  i= 0; i < size; i++)
	{
		if (i != minCycle)
		{
			avgVertSimString += std::to_string(averageVertSim[i]) + ",";
			bestVertSimString += std::to_string(theBestVertSim[i]) + ",";
			targetString += std::to_string(target[i]) + ",";
			avgEdgSimString += std::to_string(averageEdgSim[i]) + ",";
			bestEdgSimString += std::to_string(theBestEdgSim[i]) + ",";
		}
		if (i == size - 1)
		{
			avgVertSimString.pop_back();
			bestVertSimString.pop_back();
			targetString.pop_back();
			avgEdgSimString.pop_back();
			bestEdgSimString.pop_back();

			avgVertSimString += "]";
			bestVertSimString += "]";
			targetString += "]";
			avgEdgSimString += "]";
			bestEdgSimString += "]";
		}
	}

	std::string* result = new std::string[5]{targetString, avgVertSimString, bestVertSimString, avgEdgSimString, bestEdgSimString };

	return result;
}
void exercise6()
{
	std::shared_ptr<TSPLoader> loader = std::make_shared<TSPLoader>();
	std::string filenames[2] = { "kroA200.tsp", "kroB200.tsp" };
	std::string algorithmsResults = "";

	std::string resultDir = "ResultsLab6/";

	std::shared_ptr <AbstractAlgorithm> baseAlgorithms[] = {
		std::make_shared<RandomCycle>()
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
		
		auto randomWalker = std::shared_ptr <AbstractAlgorithm>(createAlgorithms(baseAlgorithms[0], innerMoves[0])[0]);

		result = testAlgorithm1000(graph, randomWalker,
			loader->getLocation(), resultDir + filenames[i]);
		algorithmsResults += result[0] +"\n" + result[1] + "\n" + result[2] + "\n" + result[3] + "\n" + result[4] + "\n";



	}
		std::ofstream output, outputTime;
		output.open(resultDir + "Wyniki_algorytmow.txt");
		output << algorithmsResults;
		output.close();

}

int main() {
	//exercise1();
	//exercise2();
	//exercise3();
	exercise6();
}