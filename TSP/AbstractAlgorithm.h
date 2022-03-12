#pragma once
#include <memory>
#include <limits>
#include <forward_list>
#include <string>

#include "Graph.h"

struct Result;

class AbstractAlgorithm
{
protected:
	std::shared_ptr <Result> _result;
	std::shared_ptr <Graph> _graph;
	std::forward_list <int> _free_nodes;

	int getStartingNodes(int startingNode);
	void addBestNodeToCycle(int cycle);
	virtual std::pair <distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) = 0;
	void addToCycle(int node, int cycle);
	void addToCycle(int node, int cycle, std::forward_list<int>::iterator pos);
	void initCalculations(int startingNode);
public:
	virtual std::string getName() = 0;
	void setGraph(std::shared_ptr <Graph> graph);
	void calculate(int startingNode);
	std::shared_ptr <Result> getResult();
};

