#pragma once
#include "AbstractAlgorithm.h"
class RegretHeuristics:
    public AbstractAlgorithm
{
    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual std::pair<distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) override;
    virtual std::string getName() override;
};

