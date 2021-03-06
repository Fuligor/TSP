#pragma once
#include "AbstractAlgorithm.h"
class RandomCycle:
    public AbstractAlgorithm
{
public:
    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

protected:
    // Odziedziczono za pośrednictwem elementu AbstractAlgorithm
    virtual void calculate(int startingNode) override;
};

