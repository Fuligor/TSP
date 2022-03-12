#pragma once
#include <string>

typedef long long distance;

class Graph
{
	distance** adjacencyMatrix = nullptr;
	unsigned int _size;
	std::string _name;
public:
	Graph(unsigned int size);
	~Graph();

	const std::string& getName() const;
	const unsigned int getSize() const;

	void setName(const std::string& name);

	distance* operator [](unsigned int index);
};

