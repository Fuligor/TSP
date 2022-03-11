#include "NearestNeighbor.h"

std::string NearestNeighbor::getName()
{
    return "Nearest Neighbor";
}

distance NearestNeighbor::calculateCost(int nodeA, std::list<int>::iterator nodeB)
{
    return (*_graph.get())[nodeA][*nodeB];
}
