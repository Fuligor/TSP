#pragma once
#include <memory>
#include <string>

class Graph;

class AbstractLoader
{
public:
	virtual std::shared_ptr <Graph> loadFile(std::string fileName) = 0;
};
