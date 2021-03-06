#pragma once
#include "AbstractAlgorithm.h"
class RandomCycle:
    public AbstractAlgorithm
{
    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual void calculate(int startingNode) override;
};

