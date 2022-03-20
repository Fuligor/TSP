#pragma once
#include "GreedyAlgorithm.h"

class NearestNeighbour:
    public GreedyAlgorithm
{
public:
    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual std::pair<distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) override;
    virtual std::string getName() override;
};

