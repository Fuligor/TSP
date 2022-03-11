#pragma once
#include "AbstractAlgorithm.h"



class NearestNeighbor:
    public AbstractAlgorithm
{
    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual distance calculateCost(int nodeA, std::list<int>::iterator nodeB) override;
};

