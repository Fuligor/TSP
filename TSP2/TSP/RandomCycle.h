#pragma once
#include "AbstractAlgorithm.h"
class RandomCycle:
    public AbstractAlgorithm
{
    // Odziedziczono za po�rednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

    // Odziedziczono za po�rednictwem elementu AbstractAlgorithm
    virtual void calculate(int startingNode) override;
};

