#include "Graph.h"

Graph::Graph(const unsigned int size)
	:_size(size)
{
	adjacencyMatrix = new distance * [size];

	for(unsigned int i = 0; i < size; i++) {
		adjacencyMatrix[i] = new distance[size];
	}
}

Graph::~Graph()
{
	for (unsigned int i = 0; i < _size; i++)
	{
		delete[] adjacencyMatrix[i];
	}

	delete[] adjacencyMatrix;
}

const std::string& Graph::getName() const
{
	return _name;
}

const unsigned int Graph::getSize() const
{
	return _size;
}

void Graph::setName(const std::string& name)
{
	_name = name;
}

distance* Graph::operator[](unsigned int index)
{
	return adjacencyMatrix[index];
}
