#pragma once
#include "GreedyAlgorithm.h"

class RegretHeuristics:
    public GreedyAlgorithm
{
    // Odziedziczono za po�rednictwem elementu AbstractAlgorithm
    virtual std::pair<distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) override;
    virtual std::string getName() override;
};

