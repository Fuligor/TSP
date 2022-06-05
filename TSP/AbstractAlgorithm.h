#pragma once
#include <memory>
#include <string>

class Graph;
struct Result;

class AbstractAlgorithm
{
protected:
	std::shared_ptr <Result> _result = nullptr;
	std::shared_ptr <Graph> _graph;
public:
	virtual std::string getName() = 0;
	void setResult(std::shared_ptr <Result> result);
	virtual void reset();
	virtual void setGraph(std::shared_ptr <Graph> graph);
	virtual void calculate(int startingNode) = 0;
	virtual std::shared_ptr <Result> getResult();
};

