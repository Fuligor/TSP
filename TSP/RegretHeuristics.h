#pragma once
#include "GreedyAlgorithm.h"

class RegretHeuristics:
    public GreedyAlgorithm
{
protected:
    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual std::pair<distance, std::forward_list<int>::iterator> calculateCostToCycle(int node, int cycle) override;

public:
    RegretHeuristics(size_t candidates_count = 1);

    virtual std::string getName() override;
};

