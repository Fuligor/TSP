#pragma once
#include "AbstractAlgorithm.h"
class RegretHeuristics:
    public AbstractAlgorithm
{
    // Odziedziczono za po�rednictwem elementu AbstractAlgorithm
    virtual std::pair<distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) override;
    virtual std::string getName() override;
};

