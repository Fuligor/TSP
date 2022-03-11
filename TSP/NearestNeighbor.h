#pragma once
#include "AbstractAlgorithm.h"



class NearestNeighbor:
    public AbstractAlgorithm
{
    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual distance calculateCost(int nodeA, std::list<int>::iterator nodeB) override;
};

