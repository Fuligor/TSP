#pragma once
#include "AbstractAlgorithm.h"
class RandomCycle:
    public AbstractAlgorithm
{
    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual void calculate(int startingNode) override;
};

